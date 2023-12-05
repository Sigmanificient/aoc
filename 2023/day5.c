#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "aoc.h"

static
int ssv_parse(int size, long array[size], char *line)
{
    int i = 0;

    for (; *line == ' '; line++);
    for (; i < size; i++) {
        array[i] = strplnum(&line);
        for (; *line == ' '; line++);
    }
    return i;
}

static __attribute__((pure))
int count_seeds(char *seeds)
{
    int i = 0;

    for (; *seeds != '\n'; seeds++)
        i += *seeds == ' ';
    return i;
}

static
void fill_missing_values(long seeds[8][255], int scount, int dim)
{
    for (int i = 0; i < scount; i++)
        if (seeds[dim][i] == 0)
            seeds[dim][i] = seeds[dim - 1][i];
}

static
void parse_seeds_values(long seeds[8][255], int scount, int dim, const long range[3])
{
    for (int j = 0; j < scount; j++) {
        if (
            seeds[dim - 1][j] < range[1]
            || seeds[dim - 1][j] > (range[1] + range[2])
        )
            continue;
        seeds[dim][j] = range[0] + (seeds[dim - 1][j] - range[1]);
    }
}

static
long get_min_value(long seeds[8][255], int scount, int dim)
{
    long min = seeds[dim][0];

    for (int i = 1; i < scount; i++)
        if (seeds[dim][i] < min)
            min = seeds[dim][i];
    return min;
}

void day5_solver(size_t size, char buff[size])
{
    char *line = strtok(buff, "\n");
    int scount = count_seeds(line);
    long seeds[8][255] = { 0 };
    long range[3];
    int dim = 0;

    ssv_parse(scount, seeds[0], strchr(line, ':') + 1);
    line = strtok(NULL, "\n");
    for (; line != NULL; line = strtok(NULL, "\n")) {
        printf("[%s]\n", line);

        if (*line == '\0')
            break;
        if (!isdigit(*line)) {
            fill_missing_values(seeds, scount, dim++);
        } else {
            ssv_parse(3, range, line);
            parse_seeds_values(seeds, scount, dim, range);
        }
    }
    fill_missing_values(seeds, scount, dim);
    printf("%ld\n", get_min_value(seeds, scount, dim));
    for (int i = 0; i < scount; i++) {
        printf(
            "[%ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld]\n",
            seeds[0][i], seeds[1][i], seeds[2][i], seeds[3][i],
            seeds[4][i], seeds[5][i], seeds[6][i], seeds[7][i]
        );
    }
}
