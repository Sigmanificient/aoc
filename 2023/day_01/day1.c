#include <ctype.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define TO_DIGIT(c) (int)(c & 0xf)
#define SSTR_UNPACK(s) s, sizeof(s) - 1

typedef struct {
    char *name;
    size_t size;
} cmps;

const cmps DIGITS_NAMES[] = {
    SSTR_UNPACK("one"),
    SSTR_UNPACK("two"),
    SSTR_UNPACK("three"),
    SSTR_UNPACK("four"),
    SSTR_UNPACK("five"),
    SSTR_UNPACK("six"),
    SSTR_UNPACK("seven"),
    SSTR_UNPACK("eight"),
    SSTR_UNPACK("nine"),
};

const size_t DIGITS_COUNT = sizeof(DIGITS_NAMES) / sizeof DIGITS_NAMES[0];

size_t get_last_digit(char *s)
{
    size_t len = strlen(s);

    for (len--; len >= 0; len--)
        if (isdigit(s[len]))
            return len;
    return -1;
}

void part_1(size_t size, char buff[size])
{
    char *line = strtok(buff, "\n");
    struct { int acc, curr, l, r; } res = { 0 };

    for (; line != NULL; line = strtok(NULL, "\n")) {
        res.l = TO_DIGIT(line[strcspn(line, "0123456789")]);
        res.r = TO_DIGIT(line[get_last_digit(line)]);
        res.curr = res.l * 10 + res.r;
        res.acc += res.curr;
    }
    printf("=> %d\n", res.acc);
}

void part_2(size_t size, char buff[size])
{
    for (size_t i = 0; i < size; i++)
        if (buff[i] == '\0')
            buff[i] = '\n';
    for (int i = 0; buff[i] != '\0'; i++)
        for (int j = 0; j < DIGITS_COUNT; j++)
            if (!strncmp(buff + i, DIGITS_NAMES[j].name, DIGITS_NAMES[j].size))
                buff[i] = (j + 1) + '0';
    part_1(size, buff);
}

void day_1(size_t size, char buff[size])
{
    part_1(size, buff);
    part_2(size, buff);
}
