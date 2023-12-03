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


const struct { int dx, dy; } POINT_NGBS[8] = {
    { -1, -1 }, { -1, 0 },
    { -1, 1 }, { 0, -1 },
    { 0, 1 }, { 1, -1 },
    { 1, 0 }, { 1, 1 },
};

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
void count_symbol_in_map(dim_t *dim, char map[dim->height][dim->width + 1])
{
    int total = 0;
    int tmp[8];
    int found;
    int total2 = 0;

    for (int y = 0; y < dim->height; y++) {
        for (int x = 0; x < dim->width; x++) {
            if (isdigit(map[y][x]) || map[y][x] == '.')
                continue;
            memset(tmp, 0, sizeof(tmp));
            found = 0;
            for (int d = 0; d < 8; d++) {
                tmp[found] = find_digits(
                    dim, map, y + POINT_NGBS[d].dy, x + POINT_NGBS[d].dx);
                found += tmp[found] != 0;
            }
            for (int i = 0; i < found; i++)
                total += tmp[i];
            if (found == 2 && map[y][x] == '*')
                total2 += tmp[0] * tmp[1];
        }
    }
    printf("Part 1: %d\n", total);
    printf("Part 2: %d\n", total2);
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
    count_symbol_in_map(&dim, *(char (*)[dim.height][dim.width + 1])buff);
}
