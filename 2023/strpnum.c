#include <ctype.h>
#include <limits.h>
#include <stddef.h>

#include "aoc.h"

int strpnum(char **strp)
{
    char *s = *strp;
    int n = 0;

    for (; isdigit(*s); s++) {
        if (n > ((INT_MAX / 10) - (*s & ~'0')))
            return -1;
        n = n * 10 + (*s & ~'0');
    }
    if (!n && s == *strp)
        return -1;
    *strp = s;
    return n;
}
