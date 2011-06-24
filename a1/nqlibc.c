#include "nqlibc.h"
#include <ctype.h>
#ifdef LINUX
#include <strings.h>
#endif
int strcmpl(const char *a, const char * b)
{
    return strcasecmp(a, b);
}

int memicmp(const char * a, const char * b, size_t s)
{
    return strncasecmp(a, b, s);
}

char * strlwr(char * a)
{
    char * x;
    for (x=a;*x;++x) {
        *x = tolower(*x);
    }
    return a;
}
