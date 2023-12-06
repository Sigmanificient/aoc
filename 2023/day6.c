#include <limits.h>
#include <stddef.h>
#include <string.h>

#include "aoc.h"

typedef struct {
    char count;
    int time[CHAR_MAX];
    int distance[CHAR_MAX];
} race_t;

static
int parse_ints(int *arr, char *line)
{
    int count = 0;

    for (; *line != '\0';) {
        for (; *line == ' '; line++);
        arr[count++] = strpnum(&line);
    }
    return count;
}

void day6_solver(size_t size, char buff[size])
{
    race_t race = { 0 };
    char *line = strtok(buff, "\n");
    int total = 1;
    int count;

    race.count = (char)parse_ints(race.time, strchr(line, ':') + 1);
    line = strtok(NULL, "\n");
    parse_ints(race.distance, strchr(line, ':') + 1);
    for (int i = 0; i < race.count; i++) {
        count = 0;
        for (int t = 0; t < race.time[i]; t++) {
            if (((race.time[i] - t) * t) > race.distance[i])
                count++;
        }
        total *= count;
    }
    printf("Part 1: %d\n", total);
}
