#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "aoc.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct { int red, blue, green; } cubes_t;
const cubes_t ALLOWED = { .red = 12, .green = 13, .blue = 14 };

static
int strpnum(char **strp)
{
    char *s = *strp;
    int n = 0;

    for (; isdigit(*s); s++) {
        if (n > ((INT_MAX / 10) - (*s & ~'0')))
            return -1;
        n = n * 10 + (*s & ~'0');
    }
    if (!n && s == *strp)
        return -1;
    *strp = s;
    return n;
}

static
void cubes_count(cubes_t *cubes, char *line)
{
    int count;

    for (char *p = line; p != NULL; p = strchr(p + 1, ' ')) {
        p++;
        count = strpnum(&p);
        switch (p[1]) {
            case 'b':
                cubes->blue = count;
                break;
            case 'g':
                cubes->green = count;
                break;
            case 'r':
                cubes->red = count;
                break;
        }
    }
}

static
void get_game_max_colors(cubes_t *cubes, char *line)
{
    char *rest;
    char *segment = strtok_r(line + 1, ";", &rest);
    cubes_t max = { 0 };

    memset(cubes, 0, sizeof(*cubes));
    for (; segment != NULL; segment = strtok_r(NULL, ";", &rest)) {
        cubes_count(cubes, segment);
        max.green = MAX(max.green, cubes->green);
        max.blue = MAX(max.blue, cubes->blue);
        max.red = MAX(max.red, cubes->red);
    }
    memcpy(cubes, &max, sizeof(*cubes));
}

void day2_solver(size_t size, char buff[size])
{
    char *rest;
    char *line = strtok_r(buff, "\n", &rest);
    cubes_t cubes;
    int game_id;
    int total = 0;

    for (; line != NULL; line = strtok_r(NULL, "\n", &rest)) {
        line = strchr(line, ' ') + 1;
        game_id = strpnum(&line);
        get_game_max_colors(&cubes, line);
        if (
            ALLOWED.red >= cubes.red
            && ALLOWED.blue >= cubes.blue
            && ALLOWED.green >= cubes.green
        )
            total += game_id;
        else
            printf("Invalidate game %d\n", game_id);
    }
    printf("%d\n", total);
}
