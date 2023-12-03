#ifndef AOC_H
    #define AOC_H

    #include <stddef.h>
    #include <unistd.h>

void day1_solver(size_t size, char buff[size]);
void day2_solver(size_t size, char buff[size]);
void day3_solver(size_t size, char buff[size]);

typedef void (*solver_fnc_t)(size_t size, char buff[size]);

ssize_t read_from_file(char const *filepath, char *buff, size_t size);
ssize_t read_input_file(char *filepath, char **buffp);

#endif
