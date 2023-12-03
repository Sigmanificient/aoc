#include <stdlib.h>
#include <sys/stat.h>

#include "aoc.h"

ssize_t read_input_file(char *filepath, char **buffp)
{
    struct stat st;
    char *buff;

    if (stat(filepath, &st) < 0)
        return -1;
    buff = malloc((st.st_size + 1) * sizeof(char));
    if (buff == NULL)
        return -1;
    if (read_from_file(filepath, buff, st.st_size) < 0) {
        free(buff);
        return -1;
    }
    buff[st.st_size] = '\0';
    *buffp = buff;
    return 0;
}

int main(int argc, char **argv)
{
    int i;
    char *buff;
    size_t buffsize;

    if (argc != 3)
        return EXIT_FAILURE;
    i = atoi(argv[1]);
    if (i > SOLVER_COUNT)
        return EXIT_FAILURE;
    buffsize = read_input_file(argv[2], &buff);
    if (buffsize < 0)
        return EXIT_FAILURE;
    SOLVERS[i](buffsize, buff);
    return EXIT_SUCCESS;
}
