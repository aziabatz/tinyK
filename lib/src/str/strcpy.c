#include <str.h>

char * strcpy(char * dst, const char * src)
{
    size_t c = 0;
    while(src[c])
    {
        dst[c] = src[c];
        c++;
    }

    return dst;
}