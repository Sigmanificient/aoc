#include "aoc.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARD_COUNT 5

typedef struct {
    char cards[5];
    int bid;
} play_t;

const char CARDS[] = "23456789TJQKA";
const int CARDS_TYPES = sizeof(CARDS) - 1;


static
int ql_stridx(const char *str, char c)
{
    for (const char *p = str; *p != '\0'; p++)
        if (*p == c)
            return (int)(p - str);
    return -1;
}

static
int get_card_strength(const play_t *play)
{
    int cards[13] = { 0 };
    int count_pairs = 0;
    int count_three = 0;

    for (int i = 0; i < CARD_COUNT; i++)
        cards[ql_stridx(CARDS, play->cards[i])]++;
    for (int i = 0; i < CARDS_TYPES; i++) {
        if (cards[i] > 3)
            return (cards[i] + 1) * 100; // 500 or 600 for 4+ cards
        if (cards[i] == 3)
            count_three++;
        if (cards[i] == 2)
            count_pairs++;
    }
    return ((count_pairs * 1) + (count_three * 3)) * 100;
}

static
int compare_cards(const void *vleft, const void *vright)
{
    const play_t *pl_left = vleft;
    const play_t *pl_right = vright;
    int sdiff = get_card_strength(pl_left) - get_card_strength(pl_right);

    if (sdiff != 0)
        return sdiff;
    for (int i = 0; i < 5; i++)
        if (pl_left->cards[i] != pl_right->cards[i])
            return (
                ql_stridx(CARDS, pl_left->cards[i])
                - ql_stridx(CARDS, pl_right->cards[i])
            );
    return 0;
}

static
size_t parse_cards(play_t *plays, char *buff)
{
    char *line = strtok(buff, "\n");
    size_t play_count = 0;

    for (; line != NULL; line = strtok(NULL, "\n")) {
        memcpy(&plays[play_count].cards, line, CARD_COUNT * sizeof(char));
        line += CARD_COUNT + 1;
        plays[play_count].bid = strpnum(&line);
        play_count++;
    }
    return play_count;
}

void day7_solver(size_t size, char buff[size])
{
    play_t plays[1024];
    size_t play_count = parse_cards(plays, buff);
    int total = 0;

    qsort(plays, play_count, sizeof *plays, &compare_cards);
    for (size_t i = 0; i < play_count; i++)
        total += (i + 1) * (size_t)plays[i].bid;
    printf("Part 1: %d\n", total);
}
