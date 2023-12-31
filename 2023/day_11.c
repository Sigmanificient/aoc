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

enum {
    AXIS_X,
    AXIS_Y,
    AXIS_COUNT
};

static
size_t compute_galaxy_distance(
    pos_t *ga, pos_t *gb,
    pos_t *exp_lut, size_t exp_factor)
{
    pos_t r_ga = {
        .x = exp_lut[ga->x].x * exp_factor + ga->x,
        .y = exp_lut[ga->y].y * exp_factor + ga->y
    };
    pos_t r_gb = {
        .x = exp_lut[gb->x].x * exp_factor + gb->x,
        .y = exp_lut[gb->y].y * exp_factor + gb->y
    };

    return (
        ((r_ga.x > r_gb.x) ? (r_ga.x - r_gb.x) : (r_gb.x - r_ga.x))
        + ((r_ga.y > r_gb.y) ? (r_ga.y - r_gb.y) : (r_gb.y - r_ga.y))
    );
}

static
pos_t *expand_lut_create(array_t *sp)
{
    size_t count = 0;
    size_t height = sp->width > sp->height ? sp->width : sp->height;
    pos_t *lut = malloc(height * sizeof *lut);

    if (lut == NULL)
        return NULL;

    for (size_t i = 0; i < sp->width; i++) {
        count += is_col_empty(i, sp->height, sp->vals);
        lut[i].x = count;
    }
    count = 0;
    for (size_t i = 0; i < sp->height; i++) {
        count += is_line_empty(sp->width, sp->vals[i]);
        lut[i].y = count;
    }
    return lut;
}

static
size_t sum_distance(
    pos_t *galaxies, size_t galaxy_count,
    pos_t *exp_lut, size_t exp_fac)
{
    size_t total = 0;

    for (size_t i = 0; i < galaxy_count; i++)
        for (size_t j = i; j < galaxy_count; j++)
            total += compute_galaxy_distance(
                &galaxies[i], &galaxies[j], exp_lut, exp_fac);
    return total;
}

void day11_solver(size_t size, char buff[size])
{
    array_t *space = space_create(size, buff);
    pos_t *galaxies = NULL;
    pos_t *exp_lut = NULL;
    size_t gal_count;

    if (space == NULL)
        goto end;

    exp_lut = expand_lut_create(space);
    if (exp_lut == NULL)
        goto end;

    gal_count = space_count_galaxies(space);
    galaxies = register_galaxy_positions(space, gal_count);
    if (galaxies == NULL)
        goto end;

    printf("Part 1: %zu\n", sum_distance(galaxies, gal_count, exp_lut, 1));
    printf("Part 2: %zu\n", sum_distance(galaxies, gal_count, exp_lut, 999999));
end:
    free(galaxies);
    free(exp_lut);
    free(space);
}
