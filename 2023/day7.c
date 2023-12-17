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

const char CARDS[] = "J23456789TJQKA";
const int CARDS_TYPES = sizeof(CARDS) - 1;
int USE_JOKER = 0;

const int RANK_UP[6][6] = {
    [0] = { 0, 1, 3, 5, 6, 6 },
    [1] = { 1, 3, 5, 6, 0, 0 },
    [2] = { 2, 4, 0, 0, 0, 0 },
    [3] = { 3, 5, 6, 0, 0, 0 },
    [4] = { 4, 6, 0, 0, 0, 0 },
    [5] = { 5, 6, 0, 0, 0, 0 },
};

static
int get_card_value(char card)
{
    const char *cards = CARDS + !USE_JOKER;

    for (int i = 0; i < CARDS_TYPES; i++)
        if (cards[i] == card)
            return i;
    return -1;
}

static
int get_card_strength(const play_t *play)
{
    int cards[14] = { 0 };
    int count_pairs = 0;
    int count_three = 0;
    int tmp = 0;

    for (int i = 0; i < CARD_COUNT; i++)
        cards[get_card_value(play->cards[i])]++;
    for (int i = USE_JOKER; i < CARDS_TYPES; i++) {
        count_three += (cards[i] == 3);
        count_pairs += (cards[i] == 2);
        if (cards[i] > 3) {
            tmp = (cards[i] + 1); // 500 or 600 for 4+ cards
            break;
        }
    }
    if (!tmp)
        tmp = count_pairs + (count_three * 3);
    if (USE_JOKER)
        tmp = RANK_UP[tmp][cards[0]];
    return tmp * 100;
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
                get_card_value(pl_left->cards[i])
                - get_card_value(pl_right->cards[i])
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
    size_t total;

    for (int part = 0; part < 2; part++) {
        USE_JOKER = part;
        total = 0;
        qsort(plays, play_count, sizeof *plays, &compare_cards);
        for (size_t i = 0; i < play_count; i++)
            total += (i + 1) * (size_t)plays[i].bid;
        printf("Part %d: %zu\n", part + 1, total);
    }
}
