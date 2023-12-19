#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "aoc.h"
#define INVALID ((pos_t){ 0 })

typedef enum {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
} cardinal_t;

typedef struct {
    int x;
    int y;
    cardinal_t card;
} pos_t;

typedef struct {
    size_t width;
    size_t height;
} dim_t;

static
const char CURRENT_TILE_LUT[16] = {
    [0x5] = 'J',
    [0x6] = 'L',
    [0x9] = '7',
    [0xa] = 'F',
};


static
const cardinal_t BASE_CARD_LUT[CHAR_MAX] = {
    ['J'] = EAST,
    ['L'] = SOUTH,
    ['7'] = EAST,
    ['F'] = NORTH
};

static
const pos_t MOVEMENT_LUT[CHAR_MAX][4] = {
    ['J'] = {
        [EAST] = { 0, -1, NORTH },
        [SOUTH] = { -1, 0, WEST },
    },
    ['L'] = {
        [WEST] = { 0, -1, NORTH },
        [SOUTH] = { 1, 0, EAST },
    },
    ['7'] = {
        [NORTH] = { -1, 0, WEST },
        [EAST] = { 0, 1, SOUTH },
    },
    ['F'] = {
        [NORTH] = { 1, 0, EAST },
        [WEST] = { 0, 1, SOUTH },
    },
    ['-'] = {
        [EAST] = { 1, 0, EAST },
        [WEST] = { -1, 0, WEST },
    },
    ['|'] = {
        [NORTH] = { 0, -1, NORTH },
        [SOUTH] = { 0, 1, SOUTH },
    },
};

static
int get_pos(
    dim_t *dim, char buff[dim->height][dim->width + 1],
    int x, int y)
{
    if (x < 0 || y < 0)
        return '.';
    if (x > (int)dim->width || y > (int)dim->height)
        return '.';
    return buff[y][x];
}

static
void find_animal(
    dim_t *dim, char buff[dim->height][dim->width + 1],
    pos_t *p)
{
    int dir = 0;
    ptrdiff_t offset = strchr((char *)buff, 'S') - (char *)buff;

    p->y = (int)offset / (int)(dim->width + 1);
    p->x = (int)offset % (int)(dim->width + 1);
    dir += (strchr("LF-", get_pos(dim, buff, p->x - 1, p->y)) != NULL) << 0;
    dir += (strchr("7J-", get_pos(dim, buff, p->x + 1, p->y)) != NULL) << 1;
    dir += (strchr("7F|", get_pos(dim, buff, p->x, p->y - 1)) != NULL) << 2;
    dir += (strchr("LJ|", get_pos(dim, buff, p->x, p->y + 1)) != NULL) << 3;
    buff[p->y][p->x] = CURRENT_TILE_LUT[dir];
}

static
int solve_pipe_maze(dim_t *dim, char buff[dim->height][dim->width + 1])
{
    pos_t p = { 0 };
    pos_t dir = { .x = 1, .y = 1 };
    pos_t mov;
    pos_t target;
    int count = 0;

    find_animal(dim, buff, &p);
    p.card = BASE_CARD_LUT[(int)buff[p.y][p.x]];
    target.x = p.x;
    target.y = p.y;
    do {
        mov = MOVEMENT_LUT[(int)buff[p.y][p.x]][p.card];
        buff[p.y][p.x] = '!';
        p.x += mov.x * dir.x;
        p.y += mov.y * dir.y;
        p.card = mov.card;
        count++;
    } while (p.x != target.x || p.y != target.y);
    return count;
}

void day10_solver(size_t size, char buff[size])
{
    int count;
    dim_t dim = {
        .width = strcspn(buff, "\n"),
        .height = 0
    };

    for (size_t i = 0; buff[i] != '\0'; i++)
        if (buff[i] == '\n')
            dim.height++;
    count =solve_pipe_maze(&dim, *(char (*)[dim.height][dim.width + 1])(buff));
    printf("Part 1: %d\n", count >> 1);
}
