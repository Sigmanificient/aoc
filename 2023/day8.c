#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "aoc.h"

typedef struct path path_t;

typedef struct path {
    char *code;
    char *left;
    char *right;
} path_t;

static
path_t *find_path(path_t *paths, const char *name, size_t count_path)
{
    for (size_t i = 0; i < count_path; i++)
        if (!strncmp(paths[i].code, name, 3))
            return &paths[i];
    return NULL;
}

static
size_t parse_file(path_t *paths)
{
    char *line = strtok(NULL, "\n");
    size_t count_path = 0;

    for (; line != NULL; line = strtok(NULL, "\n")) {
        paths[count_path].code = line;
        paths[count_path].left = strchr(line, '(') + 1;
        paths[count_path].right = strchr(paths[count_path].left, ' ') + 1;
        count_path++;
    }
    return count_path;
}

static
size_t get_map_length(path_t *paths, size_t count_path, const char *ins)
{
    size_t len = strlen(ins);
    size_t i = 0;

    if (find_path(paths, "ZZZ", count_path) == NULL)
        return 0;
    for (
        path_t *c = find_path(paths, "AAA", count_path);
        strncmp(c->code, "ZZZ", 3) != 0;
    )
        c = find_path(
            paths, (ins[i++ % len] == 'L') ? c->left : c->right,
            count_path
        );
    return i;
}

static
unsigned int ngcd(const unsigned int *n, size_t count)
{
    unsigned int res = *n;
    unsigned int x;
    unsigned int y;

    for (size_t i = 1; i < count; i++) {
        x = n[i];
        while (x % res) {
            y = x % res;
            x = res;
            res = y;
        }
    }
    return res;
}

static
unsigned long compute_map_length(unsigned int *vals, size_t count)
{
    unsigned int gcd = ngcd(vals, count);
    unsigned long res = 1;

    for (size_t i = 0; i < count; i++)
        res *= vals[i] / gcd;
    return res * gcd;
}

static
size_t get_ghost_map_legnth(path_t *paths, size_t count_path, const char *ins)
{
    path_t *ghosts[1024];
    unsigned int count[1024];
    size_t ghosts_count = 0;
    size_t len = strlen(ins);
    char *path;

    for (size_t i = 0; i < count_path; i++)
        if (paths[i].code[2] == 'A')
            ghosts[ghosts_count++] = &paths[i];
    for (size_t i = 0; i < ghosts_count; i++) {
        for (; ghosts[i]->code[2] != 'Z'; count[i]++) {
            path = ((ins[count[i] % len] == 'L')
                ? ghosts[i]->left : ghosts[i]->right);
            ghosts[i] = find_path(paths, path, count_path);
        }
    }
    return compute_map_length(count, ghosts_count);
}

void day8_solver(size_t size, char buff[size])
{
    path_t paths[1024];
    char *ins = strtok(buff, "\n");
    size_t count_path = parse_file(paths);

    printf("Part 1: %zu\n", get_map_length(paths, count_path, ins));
    printf("Part 2: %zu\n", get_ghost_map_legnth(paths, count_path, ins));
}
