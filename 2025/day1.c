#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *buff;
    size_t sz;

    int dial = 50;
    int count_zero = 0;
    int lapcount = 0;

    int sum = dial;

    while (getline(&buff, &sz, stdin) > 0) {
        int direction = (*buff == 'R') - (*buff == 'L');
        int rotation = strtol(buff+1, NULL, 10);
        if (!direction || rotation <= 0)
            continue;

        for (int i = 0; i < rotation; i++) {
            dial = (dial + 100 + (direction)) % 100;
            lapcount += (dial == 0);
        }

        if (dial == 0)
            count_zero++;
    }

    printf("Part 1: %d\n", count_zero);
    printf("Part 2: %d\n", lapcount);
}
