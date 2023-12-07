#include <stddef.h>
#include <stdlib.h>

#include "aoc.h"

const solver_fnc_t SOLVERS[] = {
    &day1_solver,
    &day2_solver,
    &day3_solver,
    &day4_solver,
    &day5_solver,
    &day6_solver,
    &day7_solver,
};

const int SOLVER_COUNT = sizeof(SOLVERS) / sizeof(*SOLVERS);

int main(int argc, char **argv)
{
    int i;
    char *buff;
    ssize_t buffsize;

    if (argc != 3)
        return EXIT_FAILURE;
    i = atoi(argv[1]);
    if (!i)
        return EXIT_FAILURE;
    i -= 1;
    if (i > SOLVER_COUNT)
        return EXIT_FAILURE;
    buffsize = read_input_file(argv[2], &buff);
    if (buffsize < 0)
        return EXIT_FAILURE;
    SOLVERS[i]((size_t)buffsize, buff);
    free(buff);
    return EXIT_SUCCESS;
}
