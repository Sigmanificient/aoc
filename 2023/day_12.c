#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoc.h"

#define LIMIT 32

static
size_t csv_parse(size_t size, long array[size], char *line)
{
    size_t i = 0;

    for (; *line == ','; line++);
    for (; i < size; i++) {
        array[i] = strplnum(&line);
        for (; *line == ','; line++);
    }
    return i;
}

static
void create_arrangement(size_t count, char *ptrs[static count], size_t i)
{
    for (size_t k = 0; k < count; k++) {
        *(ptrs[k]) = (i & 1) ? '#' : '.';
        i >>= 1;
    }
}

static __attribute_pure__
bool match_requirements(
    const char *line,
    size_t digit_count, const long digits[static digit_count])
{
    long seq;

    for (size_t i = 0; i < digit_count; i++) {
        for (; *line == '.'; line++);
        seq = (long)strspn(line, "#");
        if (seq != digits[i])
            return false;
        line += seq;
    }
    return strchr(line, '#') == NULL;
}

static
size_t sum_possible_arrangements(char *line)
{
    char *ptrs[LIMIT];
    long digits[LIMIT] = { 0 };
    size_t count = 0;
    size_t commas = 0;
    size_t valid = 0;
    size_t total;
    char *digit_start = strchr(line, ' ') + 1;

    for (char *p = strchr(line, '?'); p != NULL; p = strchr(p + 1, '?'))
        ptrs[count++] = p;
    for (char *p = digit_start; *p != '\0'; p++)
        commas += *p == ',';
    csv_parse(commas + 1, digits, digit_start);

    total = 1 << count;
    for (size_t i = 0; i < total; i++) {
        create_arrangement(count, ptrs, i);
        if (match_requirements(line, commas + 1, digits))
            valid++;
    }
    return valid;
}

void day12_solver(size_t size, char buff[size])
{
    char *line = strtok(buff, "\n");
    size_t total = 0;

    for (; line != NULL; line = strtok(NULL, "\n"))
        total += sum_possible_arrangements(line);
    printf("Part 1: %zu", total);
}
