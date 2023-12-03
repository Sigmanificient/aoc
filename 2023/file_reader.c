#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "aoc.h"

ssize_t read_from_file(char const *filepath, char *buff, size_t size)
{
    int fd = open(filepath, O_RDONLY);
    ssize_t rd;

    if (fd < 0)
        return fd;
    rd = read(fd, buff, size);
    for (; close(fd) < 0;);
    return rd;
}

ssize_t read_input_file(char *filepath, char **buffp)
{
    struct stat st;
    char *buff;

    if (stat(filepath, &st) < 0)
        return -1;
    buff = malloc((size_t)(st.st_size + 1) * sizeof(char));
    if (buff == NULL)
        return -1;
    if (read_from_file(filepath, buff, (size_t)st.st_size) < 0) {
        free(buff);
        return -1;
    }
    buff[st.st_size] = '\0';
    *buffp = buff;
    return st.st_size;
}
