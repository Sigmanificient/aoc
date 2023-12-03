#include <ctype.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define TO_DIGIT(c) (int)(c & 0xf)

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

size_t get_last_digit(char *s)
{
    size_t len = strlen(s);

    for (len--; len >= 0; len--)
        if (isdigit(s[len]))
            return len;
    return -1;
}

void part_1(size_t size, char buff[size])
{
    char *line = strtok(buff, "\n");
    struct { int acc, curr, l, r; } res = { 0 };

    for (; line != NULL; line = strtok(NULL, "\n")) {
        res.l = TO_DIGIT(line[strcspn(line, "0123456789")]);
        res.r = TO_DIGIT(line[get_last_digit(line)]);
        res.curr = res.l * 10 + res.r;
        res.acc += res.curr;
        printf("%d : %d -> %d\n", res.l, res.r, res.curr);
    }
    printf("=> %d\n", res.acc);
}

int main(int argc, char **argv)
{
    struct stat st;
    char *buff;

    if (argc != 2)
        return EXIT_FAILURE;
    if (stat(argv[1], &st) < 0)
        return EXIT_FAILURE;
    buff = malloc((st.st_size + 1) * sizeof(char));
    if (buff == NULL)
        return EXIT_FAILURE;
    if (read_from_file(argv[1], buff, st.st_size) < 0)
        return EXIT_FAILURE;
    buff[st.st_size] = '\0';
    part_1(st.st_size, buff);
    return EXIT_SUCCESS;
}
