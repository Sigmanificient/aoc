#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "aoc.h"

typedef struct {
    int win;
    int trials;
    int lines;
} game_size_t;

static
int parse_number_pad(char **linep)
{
    int tmp;
    char *line = *linep;

    for (; *line == ' '; line++);
    tmp = strpnum(&line);
    for (; *line == ' '; line++);
    *linep = line;
    return tmp;
}

static
int get_match_count(game_size_t *gs, char *line)
{
    int winnings[gs->win];
    int player[gs->trials];
    int count = 0;

    line = strchr(line, ':') + 1;
    for (int i = 0; i < gs->win; i++)
        winnings[i] = parse_number_pad(&line);
    line += 2;
    for (int i = 0; i < gs->trials; i++)
        player[i] = parse_number_pad(&line);
    for (int i = 0; i < gs->win; i++)
        for (int j = 0; j < gs->trials; j++)
            if (player[j] == winnings[i])
                count++;
    return count;
}

static
void parse_game_size(game_size_t *gs, char *anyline)
{
    char *p = anyline;

    p = strchr(p, ':') + 1;
    gs->win = (int)(strchr(p, '|') - p - 1) / 3;
    p = strchr(p, '|') + 1;
    gs->trials = (int)(strlen(p) / 3);
}

static
void compute_game_score(game_size_t *gs, char *line)
{
    int total = 0;
    int score;
    int wsize = gs->lines + gs->win;
    int weights[wsize];
    int sum = 0;
    int i = 0;

    for (int j = 0; j < wsize; j++)
        weights[j] = 1;
    for (; line != NULL; line = strtok(NULL, "\n")) {
        score = get_match_count(gs, line);
        total += (score) ? 1 << (score - 1) : 0;
        sum += weights[i];
        for (int j = 0; j < score; j++)
            weights[i + j + 1] += weights[i];
        i++;
    }
    printf("Part 1: %d\n", total);
    printf("Part 2: %d\n", sum);
}

static __attribute__((pure))
int count_lines(char *buff)
{
    int i = 0;

    for (; *buff != '\0'; buff++)
        if (*buff == '\n')
            i++;
    return i;
}

void day4_solver(size_t size, char buff[size])
{
    game_size_t gs = { .lines = count_lines(buff) };
    char *line = strtok(buff, "\n");

    parse_game_size(&gs, line);
    compute_game_score(&gs, line);
}
