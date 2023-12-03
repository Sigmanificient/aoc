#include <fcntl.h>
#include <unistd.h>

int read_from_file(char const *filepath, char *buff, size_t size)
{
    int fd = open(filepath, O_RDONLY);
    int rd;

    if (fd < 0)
        return fd;
    rd = read(fd, buff, size);
    for (; close(fd) < 0;);
    return rd;
}
