#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoc.h"

typedef struct {
    int count;
    long vals[8][255];
    int dim;
} seeder_t;

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
void fill_missing_values(seeder_t *s)
{
    for (int i = 0; i < s->count; i++)
        if (s->vals[s->dim][i] == 0)
            s->vals[s->dim][i] = s->vals[s->dim - 1][i];
}

static
void parse_seeds_values(seeder_t *s, const long range[3])
{
    for (int j = 0; j < s->count; j++) {
        if (
            s->vals[s->dim - 1][j] < range[1]
            || s->vals[s->dim - 1][j] >= (range[1] + range[2])
        )
            continue;
        s->vals[s->dim][j] = range[0] + (s->vals[s->dim - 1][j] - range[1]);
    }
}

static
long get_min_value(seeder_t *s)
{
    long min = s->vals[s->dim][0];

    for (int i = 1; i < s->count; i++)
        if (s->vals[s->dim][i] < min)
            min = s->vals[s->dim][i];
    return min;
}

static
void populate_seeeder(seeder_t *s, size_t size, char *buff)
{
    char *line = strtok(buff, "\n");
    long range[3];

    line = strtok(NULL, "\n");
    for (; line != NULL; line = strtok(NULL, "\n")) {
        if (!isdigit(*line)) {
            fill_missing_values(s);
            s->dim++;
        } else {
            ssv_parse(3, range, line);
            parse_seeds_values(s, range);
        }
    }
    fill_missing_values(s);
    for (size_t i = 0; i < size; i++)
        if (buff[i] == '\0')
            buff[i] = '\n';
}

static
long get_min_range_value(seeder_t *s, size_t size, char buff[size])
{
    long min = (long)1e10 - 1;

    for (int k = 0; k < s->count; k += 2) {
        long start = s->vals[0][k];
        long max = s->vals[0][k + 1];
        long tmp;

        // Brute force
        s->count = 1;
        for (long i = 0; i <= max; i++) {
            for (int j = 1; j < 8; j++)
                s->vals[j][0] = 0;
            s->dim = 0;
            s->vals[0][0] = start + i;
            populate_seeeder(s, size, buff);
            tmp = get_min_value(s);
            if (tmp < min)
                min = tmp;
            printf("%09ld -> tmp: %-12ld | min: %-12ld\n", i, tmp, min);
        }
    }
    return min;
}

void day5_solver(size_t size, char buff[size])
{
    seeder_t s = {
        .count = count_seeds(buff),
        .dim = 0,
        .vals = {{ 0 }}
    };

    ssv_parse(s.count, s.vals[0], strchr(buff, ':') + 1);
    populate_seeeder(&s, size, buff);
    printf("Part 1: %ld\n", get_min_value(&s));
    printf("Part 2: %ld\n", get_min_range_value(&s, size, buff));
}
