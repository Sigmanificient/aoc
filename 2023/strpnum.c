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

long strplnum(char **strp)
{
    char *s = *strp;
    long n = 0;

    for (; isdigit(*s); s++) {
        if (n > ((LONG_MAX / 10) - (*s & ~'0')))
            return -1;
        n = n * 10 + (*s & ~'0');
    }
    if (!n && s == *strp)
        return -1;
    *strp = s;
    return n;
}

int strnum(char **strp, int *val)
{
    int n = (**strp == '-');
    int absv;

    *strp += n;
    absv = strpnum(strp);
    if (absv == -1)
        return -1;
    *val = n ? -absv : absv;
    return 0;
}
