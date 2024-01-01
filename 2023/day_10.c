#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoc.h"

#define TILESIZE 3

static
const char MAZE_GROWTH[CHAR_MAX][TILESIZE][TILESIZE] = {
    ['J'] = { ".X.", "XX.", "..." },
    ['L'] = { ".X.", ".XX", "..." },
    ['F'] = { "...", ".XX", ".X." },
    ['7'] = { "...", "XX.", ".X." },
    ['-'] = { "...", "XXX", "..." },
    ['|'] = { ".X.", ".X.", ".X." },
    ['.'] = { "...", "...", "..." },
    ['S'] = { "...", ".S.", "..." }
};

typedef struct {
    size_t x;
    size_t y;
} pos_t;

typedef struct {
    size_t height;
    size_t width;
    char **vals;
    pos_t animal;
} array_t;

static
void maze_set_animal_tile(array_t *maze)
{
    pos_t a = maze->animal;

    if (a.x <= TILESIZE || a.y >= TILESIZE)
        __builtin_unreachable();
    if (a.x == maze->width - TILESIZE || a.y >= maze->height - TILESIZE)
        __builtin_unreachable();

    maze->vals[a.y][a.x] = 'X';
    maze->vals[a.y - 1][a.x] = maze->vals[a.y - 2][a.x];
    maze->vals[a.y + 1][a.x] = maze->vals[a.y + 2][a.x];
    maze->vals[a.y][a.x - 1] = maze->vals[a.y][a.x - 2];
    maze->vals[a.y][a.x + 1] = maze->vals[a.y][a.x + 2];
}

static
void maze_paint_from_string(array_t *maze, const char *buff)
{
    const char (*p)[TILESIZE];
    size_t x = 0;
    size_t y = 0;

    maze->animal.x = 0;
    maze->animal.y = 0;
    for (size_t i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == '\n') {
            y += TILESIZE;
            x = 0;
            continue;
        }

        if (buff[i] == 'S') {
            maze->animal.x = x + 1;
            maze->animal.y = y + 1;
        }

        p = MAZE_GROWTH[(int)buff[i]];
        for (size_t off = 0; off < TILESIZE; off++)
            memcpy(&maze->vals[y + off][x], p[off], TILESIZE);
        x += TILESIZE;
    }

    maze_set_animal_tile(maze);
}

static
array_t *maze_create(size_t size, char buff[size])
{
    size_t height = 0;
    size_t width = 0;
    array_t *maze;
    char *p;

    width = TILESIZE * strcspn(buff, "\n");
    for (size_t i = 0; i < size; i++)
        height += buff[i] == '\n';

    height *= 3;
    if (!width || !height)
        return NULL;

    maze = malloc(sizeof *maze
        + sizeof(char **) * height
        + sizeof(char) * (height + 1) * width);
    if (maze == NULL)
        return NULL;

    maze->vals = (char **)&maze[1];
    maze->width = width;
    maze->height = height;

    p = (char *)&maze->vals[height];
    for (size_t i = 0; i < height; i++)
        maze->vals[i] = &p[i * width];

    width /= TILESIZE;
    maze_paint_from_string(maze, buff);
    return maze;
}

static
size_t maze_flood(
    array_t *restrict maze,
    size_t y, size_t x,
    const char cell[static 2])
{
    size_t hit = 0;

    if (maze->vals[y][x] != cell[0])
        return 0;
    maze->vals[y][x] = cell[1];
    if (y > 0)
        hit += maze_flood(maze, y - 1, x, cell);
    if ((y + 1) < maze->height)
        hit += maze_flood(maze, y + 1, x, cell);
    if (x > 0)
        hit += maze_flood(maze, y, x - 1, cell);
    if ((x + 1) < maze->width)
        hit += maze_flood(maze, y, x + 1, cell);
    return hit + 1;
}

static
void maze_char_swap(array_t *maze, const char swp[static 2])
{
    for (size_t y = 0; y < maze->height; y++)
        for (size_t x = 0; x < maze->width; x++)
            if (maze->vals[y][x] == swp[0])
                maze->vals[y][x] = swp[1];
}

static
void maze_flood_outer_layer(array_t *maze)
{
    const char cell[] = ".~";

    maze_char_swap(maze, "X.");
    for (size_t x = 0; x < maze->width; x++) {
        maze_flood(maze, 0, x, cell);
        maze_flood(maze, maze->height - 1, x, cell);
    }

    for (size_t y = 0; y < maze->height; y++) {
        maze_flood(maze, y, 0, cell);
        maze_flood(maze, y, maze->width - 1, cell);
    }
}

static __attribute_pure__
size_t maze_count_inner_blocks(array_t *maze)
{
    size_t mid = TILESIZE / 2;
    size_t count = 0;

    for (size_t y = 0; y < maze->height; y += TILESIZE)
        for (size_t x = 0; x < maze->width; x += TILESIZE)
            if (maze->vals[y + mid][x + mid] == '.')
                count++;
    return count;
}

void day10_solver(size_t size, char buff[size])
{
    array_t *maze = maze_create(size, buff);
    size_t length;

    if (maze == NULL)
        return;

    length = maze_flood(maze, maze->animal.y, maze->animal.x, "X@");
    printf("Part 1: %zu\n", length / (TILESIZE << 1));

    maze_flood_outer_layer(maze);
    printf("Part 2: %zu\n", maze_count_inner_blocks(maze));

    free(maze);
}
