#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "aoc.h"

typedef struct {
    long time;
    long distance;
} race_t;

static
int parse_line(long *arr, size_t dt, char *line)
{
    int count = 0;

    for (; *line != '\0';) {
        for (; *line == ' '; line++);
        *arr = strpnum(&line);
        arr = (long *)(((char *)arr) + dt);
        count++;
    }
    return count;
}

static
int compute_win_scenarios(race_t *race)
{
    int count = 0;

    for (int t = 0; t < race->time; t++)
        if (((race->time - t) * t) > race->distance)
            count++;
    return count;
}

static
void concat_digit(long *out, long i)
{
    int base = 1;
    long tmp = i;

    for (; tmp != 0; tmp /= 10)
        base *= 10;
    *out *= base;
    *out += i;
}

static
void concat(race_t *out, race_t *in)
{
    concat_digit(&out->time, in->time);
    concat_digit(&out->distance, in->distance);
}

void day6_solver(size_t size, char buff[size])
{
    race_t race[CHAR_MAX] = { 0 };
    char *line = strtok(buff, "\n");
    int total = 1;
    int race_count = parse_line(
        &race[0].time, sizeof *race,
        strchr(line, ':') + 1
    );

    line = strtok(NULL, "\n");
    parse_line(&race[0].distance, sizeof *race, strchr(line, ':') + 1);
    for (int i = 0; i < race_count; i++)
        total *= compute_win_scenarios(&race[i]);
    printf("Part 1: %d\n", total);
    for (int i = 1; i < race_count; i++)
        concat(&race[0], &race[i]);
    printf("Part 2: %d\n", compute_win_scenarios(&race[0]));
}
