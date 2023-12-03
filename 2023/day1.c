#include <ctype.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "aoc.h"

#define TO_DIGIT(c) (int)(c & 0xf)
#define SSTR_UNPACK(s) s, sizeof(s) - 1

const struct {
    const char *name;
    size_t size;
} DIGITS_NAMES[] = {
    { SSTR_UNPACK("one") },
    { SSTR_UNPACK("two") },
    { SSTR_UNPACK("three") },
    { SSTR_UNPACK("four") },
    { SSTR_UNPACK("five") },
    { SSTR_UNPACK("six") },
    { SSTR_UNPACK("seven") },
    { SSTR_UNPACK("eight") },
    { SSTR_UNPACK("nine") },
};

const size_t DIGITS_COUNT = sizeof(DIGITS_NAMES) / sizeof DIGITS_NAMES[0];

static __attribute__((pure))
ssize_t get_last_digit(char *s)
{
    ssize_t len = (ssize_t)strlen(s);

    for (len--; len >= 0; len--)
        if (isdigit(s[len]))
            return len;
    return -1;
}

static
void str_untok(char *tokens, size_t size, char rep)
{
    for (size_t i = 0; i < size; i++)
        if (tokens[i] == '\0')
            tokens[i] = rep;
}

static
int sum_line_bound_digits(size_t size, char buff[size])
{
    char *line = strtok(buff, "\n");
    struct { int acc, curr, left, right; } res = { 0 };

    for (; line != NULL; line = strtok(NULL, "\n")) {
        res.left = TO_DIGIT(line[strcspn(line, "0123456789")]);
        res.right = TO_DIGIT(line[get_last_digit(line)]);
        res.curr = res.left * 10 + res.right;
        res.acc += res.curr;
    }
    return res.acc;
}

void day1_solver(size_t size, char buff[size])
{
    printf("Part 1: %d\n", sum_line_bound_digits(size, buff));
    str_untok(buff, size, '\n');
    for (int i = 0; buff[i] != '\0'; i++)
        for (size_t j = 0; j < DIGITS_COUNT; j++)
            if (!strncmp(buff + i, DIGITS_NAMES[j].name, DIGITS_NAMES[j].size))
                buff[i] = (char)((j + 1) | '0');
    printf("Part 2: %d\n", sum_line_bound_digits(size, buff));
}
