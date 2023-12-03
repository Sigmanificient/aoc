#ifndef AOC_H
    #define AOC_H

    #include <stddef.h>

void day_1(size_t size, char buff[size]);

typedef void (*solver_fnc_t)(size_t size, char buff[size]);

const solver_fnc_t SOLVERS[] = {
    &day_1
};

const int SOLVER_COUNT = sizeof(SOLVERS) / sizeof(*SOLVERS);

int read_from_file(char const *filepath, char *buff, size_t size);

#endif
