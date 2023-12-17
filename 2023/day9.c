#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "aoc.h"

static
int extrapolate_value(int *vals, int count)
{
    int i = 0;

    for (; vals[i] == 0; i++);
    for (; i < count; i++)
        vals[i] = vals[i - 1] + vals[i];
    return vals[i - 1];
}

static
void reduce_line(int *vals, int count)
{
    int diffsum = 0;

    if (count == 0)
        return;
    for (int i = 1; i < count; i++) {
        vals[i - 1] = vals[i] - vals[i - 1];
        diffsum += vals[i - 1];
    }
    if (diffsum != 0)
        reduce_line(vals, count - 1);
}

void day9_solver(size_t size, char buff[size])
{
    char *line = strtok(buff, "\n");
    int vals[1024];
    int count;
    int total = 0;

    for (; line != NULL; line = strtok(NULL, "\n")) {
        for (count = 0; *line != '\0'; strnum(&line, &vals[count++]))
            for (; *line == ' '; line++);
        reduce_line(vals, count);
        total += extrapolate_value(vals, count);
    }
    printf("Part 1: %d\n", total);
}
