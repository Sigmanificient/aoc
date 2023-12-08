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
path_t *find_path(path_t *paths, const char *name, int count_path)
{
    for (int i = 0; i < count_path; i++)
        if (!strncmp(paths[i].code, name, 3))
            return &paths[i];
    return NULL;
}

void day8_solver(size_t size, char buff[size])
{
    path_t paths[1024];
    char *instructions = strtok(buff, "\n");
    char *line = strtok(NULL, "\n");
    int count_path = 0;

    for (; line != NULL; line = strtok(NULL, "\n")) {
        paths[count_path].code = line;
        paths[count_path].left = strchr(line, '(') + 1;
        paths[count_path].right = strchr(paths[count_path].left, ' ') + 1;
        count_path++;
    }

    size_t len = strlen(instructions);
    size_t i = 0;
    for (
        path_t *c = find_path(paths, "AAA", count_path);
        strncmp(c->code, "ZZZ", 3) != 0;
    ) {
        printf("Going %.3s\n", (instructions[i] == 'L') ? c->left : c->right);
        c = find_path(
            paths,
            (instructions[i % len] == 'L') ? c->left : c->right,
            count_path
        );
        i++;
    }
    printf("Part 1: %zu\n", i);
}
