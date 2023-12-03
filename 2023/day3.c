#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "aoc.h"

typedef struct {
    int width;
    int height;
} dim_t;


const struct { int dx, dy; } POINT_NEIGHBORS[8] = {
    { -1, -1 }, { -1, 0 },
    { -1, 1 }, { 0, -1 },
    { 0, 1 }, { 1, -1 },
    { 1, 0 }, { 1, 1 },
};

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
int find_digits(
    dim_t *dim, char map[dim->height][dim->width + 1], int y, int x)
{
    int k;
    char *p;

    if (x < 0 || y < 0)
        return 0;
    if (x > dim->width || y > dim->height)
        return 0;
    if (!isdigit(map[y][x]))
        return 0;
    while (isdigit(map[y][x]) && x >= 0)
        x--;
    p = &map[y][x + 1];
    k = strpnum(&p);
    for (int i = 1; isdigit(map[y][x + i]); i++)
        map[y][x + i] = '.';
    return k;
}

static
int count_symbol_in_map(dim_t *dim, char map[dim->height][dim->width + 1])
{
    int total = 0;

    for (int y = 0; y < dim->height; y++) {
        for (int x = 0; x < dim->width; x++) {
            if (isdigit(map[y][x]) || map[y][x] == '.')
                continue;
            for (int d = 0; d < 8; d++)
                total += find_digits(
                    dim, map,
                    y + POINT_NEIGHBORS[d].dy,
                    x + POINT_NEIGHBORS[d].dx
                );
        }
    }
    return total;
}

void day3_solver(size_t size, char buff[size])
{
    dim_t dim = {
        .width = (int)(strchr(buff, '\n') - buff),
        .height = 0
    };

    for (size_t i = 0; i < size; i++)
        if (buff[i] == '\n')
            dim.height++;
    printf("map size: (%d, %d)\n", dim.width, dim.height);
    printf(
        "%d\n",
        count_symbol_in_map(&dim, *(char (*)[dim.height][dim.width + 1])buff)
    );
}
