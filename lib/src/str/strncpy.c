#include <str.h>
#include <stdbool.h>

char * strncpy(char * dst, const char * src, size_t count)
{
    bool is_end = false;
    for(size_t c = 0; c < count; c++)
    {
        if(!src[c])
        {
            is_end = true;
        }

        if(is_end)
        {
            //fill with terminating char
            dst[c] = '\0';
        }
        else
        {
            dst[c] = src[c];
        }
    }

    return dst;
}