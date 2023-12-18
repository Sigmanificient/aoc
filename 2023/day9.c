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

static
void revlst(int *vals, int count)
{
    int half = count >> 1;
    int swp;

    for (int i = 0; i < half; i++) {
        swp = vals[i];
        vals[i] = vals[count - i - 1];
        vals[count - i - 1] = swp;
    }
}

void day9_solver(size_t size, char buff[size])
{
    char *line = strtok(strdup(buff), "\n");
    int vals[1024];
    int cpy[1024];
    int count;
    int total[2] = { 0 };

    for (; line != NULL; line = strtok(NULL, "\n")) {
        for (count = 0; *line != '\0'; strnum(&line, &vals[count++]))
            for (; *line == ' '; line++);
        memcpy(cpy, vals, (size_t)count * sizeof(int));
        reduce_line(vals, count);
        total[0] += extrapolate_value(vals, count);
        revlst(cpy, count);
        reduce_line(cpy, count);
        total[1] += extrapolate_value(cpy, count);
    }
    printf("Part 1: %d\n", total[0]);
    printf("Part 2: %d\n", total[1]);
}
