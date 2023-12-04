#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "aoc.h"

typedef struct {
    int win;
    int trials;
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
int get_score(char *line, int nb_win, int nb_test)
{
    int winnings[nb_win];
    int player[nb_test];
    int score = 0;

    line = strchr(line, ':') + 1;
    for (int i = 0; i < nb_win; i++)
        winnings[i] = parse_number_pad(&line);
    line += 2;
    for (int i = 0; i < nb_test; i++)
        player[i] = parse_number_pad(&line);
    for (int i = 0; i < nb_win; i++)
        for (int j = 0; j < nb_test; j++)
            if (player[j] == winnings[i])
                score++;
    return (score) ? 1 << (score - 1) : 0;
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

void day4_solver(size_t size, char buff[size])
{
    char *line = strtok(buff, "\n");
    int total = 0;
    game_size_t gs;

    if (line == NULL)
        return;
    parse_game_size(&gs, line);
    for (; line != NULL; line = strtok(NULL, "\n"))
        total += get_score(line, gs.win, gs.trials);
    printf("-> %d\n", total);
}
