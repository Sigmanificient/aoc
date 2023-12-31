#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoc.h"

typedef struct {
    size_t x;
    size_t y;
} pos_t;

typedef struct {
    size_t height;
    size_t width;
    char **vals;
    char *valp;
    pos_t animal;
} array_t;

static
array_t *array_create(size_t height, size_t width)
{
    array_t *space = malloc(sizeof *space
        + sizeof(char *) * height
        + sizeof(char) * height * width + 1);

    if (space == NULL)
        return NULL;

    space->vals = (char **)&space[1];
    space->height = height;
    space->width = width;
    space->valp = (char *)&space->vals[height];

    for (size_t i = 0; i < height; i++)
        space->vals[i] = &space->valp[i * width];
    return space;
}

static
array_t *space_create(size_t size, char buff[size])
{
    array_t *sp;
    size_t width = strcspn(buff, "\n");
    size_t line = width + 1;
    size_t height = 0;

    for (size_t i = 0; i < size; i++)
        height += buff[i] == '\n';
    if (!width || !height)
        return NULL;

    sp = array_create(height << 1, (width << 1) + 1);
    if (sp == NULL)
        return NULL;

    memset(sp->valp, '.', sp->height * sp->width);
    sp->valp[sp->height * sp->width] = '\0';

    sp->width = width;
    sp->height = height;
    for (size_t y = 0; y < sp->height; y++)
        memcpy(sp->vals[y], &buff[y * line], line);
    return sp;
}

static
bool is_line_empty(size_t width, const char *line)
{
    for (size_t i = 0; i < width; i++)
        if (line[i] != '.')
            return false;
    return true;
}

static
bool is_col_empty(size_t x, size_t height, char **arr)
{
    for (size_t i = 0; i < height; i++)
        if (arr[i][x] != '.')
            return false;
    return true;
}

static
void space_expand_empty_lines(array_t *sp)
{
    char *swp;
    const char newline[] = "\n";
    for (size_t y = 0; y < sp->height; y++) {
        if (!is_line_empty(sp->width, sp->vals[y]))
            continue;
        swp = sp->vals[sp->height];
        memmove(&sp->vals[y + 1], &sp->vals[y], (sp->height - y) * sizeof(char *));
        sp->vals[y] = swp;
        sp->height++;
        y++;
    }

    for (size_t x = 0; x < sp->width; x++) {
        if (!is_col_empty(x, sp->height, sp->vals))
            continue;
        for (size_t y = 0; y < sp->height; y++) {
            memmove(&sp->vals[y][x + 1], &sp->vals[y][x], sp->width - x);
            sp->vals[y][x] = '.';
        }
        sp->width++;
        x++;
    }

    for (size_t y = 0; y < sp->height; y++)
        memcpy(&sp->vals[y][sp->width], newline, sizeof(newline));
}

static __attribute_pure__
size_t space_count_galaxies(array_t *sp)
{
    size_t count = 0;

    for (size_t y = 0; y < sp->height; y++)
        for (size_t x = 0; x < sp->width; x++)
            count += sp->vals[y][x] == '#';
    return count;
}

static
pos_t *register_galaxy_positions(array_t *sp, size_t count)
{
    pos_t *gpos = malloc(count * sizeof *gpos);
    size_t i = 0;

    if (gpos == NULL)
        return NULL;

    for (size_t y = 0; y < sp->height; y++) {
        for (size_t x = 0; x < sp->width; x++) {
            if (sp->vals[y][x] != '#')
                continue;
            gpos[i].x = x;
            gpos[i].y = y;
            i++;
        }
    }

    return gpos;
}

static
size_t compute_galaxy_distance(pos_t *ga, pos_t *gb)
{
    return (
        ((ga->x > gb->x) ? (ga->x - gb->x) : (gb->x - ga->x))
        + ((ga->y > gb->y) ? (ga->y - gb->y) : (gb->y - ga->y))
    );
}

void day11_solver(size_t size, char buff[size])
{
    array_t *space = space_create(size, buff);
    pos_t *galaxies = NULL;
    size_t galaxy_count;
    size_t total = 0;

    if (space == NULL)
        goto end;
    galaxy_count = space_count_galaxies(space);
    space_expand_empty_lines(space);
    galaxies = register_galaxy_positions(space, galaxy_count);
    if (galaxies == NULL)
        goto end;

    for (size_t i = 0; i < galaxy_count; i++)
        for (size_t j = i; j < galaxy_count; j++)
            total += compute_galaxy_distance(&galaxies[i], &galaxies[j]);
    printf("Part 1: %zu\n", total);
end:
    free(galaxies);
    free(space);
}
