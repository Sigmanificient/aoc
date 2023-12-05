#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
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
            || s->vals[s->dim - 1][j] > (range[1] + range[2])
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
void populate_seeeder(seeder_t *s, char *buff)
{
    char *line = strtok(buff, "\n");
    long range[3];

    ssv_parse(s->count, s->vals[0], strchr(line, ':') + 1);
    line = strtok(NULL, "\n");
    for (; line != NULL; line = strtok(NULL, "\n")) {
        printf("[%s]\n", line);
        if (!isdigit(*line)) {
            fill_missing_values(s);
            s->dim++;
        } else {
            ssv_parse(3, range, line);
            parse_seeds_values(s, range);
        }
    }
    fill_missing_values(s);
}

void day5_solver(size_t size, char buff[size])
{
    seeder_t s = {
        .count = count_seeds(buff),
        .dim = 0,
        .vals = {{ 0 }}
    };

    populate_seeeder(&s, buff);
    printf("Part 1: %ld\n", get_min_value(&s));
}
