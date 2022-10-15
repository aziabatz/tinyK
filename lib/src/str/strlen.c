#include <str.h>

size_t strlen(const char * src)
{
    size_t c = 0;
    while(src[c])
    {
        c++;
    }
    return c;
}