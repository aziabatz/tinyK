#include <str.h>

char * strchr(const char * src, char ch)
{
    size_t c = 0;
    char _ch;
    while(_ch = src[c])
    {
        if(_ch == ch)
        {
            return src+c;
        }

        c++;
    }
    return NULL;
}