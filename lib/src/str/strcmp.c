#include <str.h>

int strcmp(const char * left, const char * right)
{
    size_t c = 0;
    while(left[c] || right[c])
    {
        if(left[c] > right[c])
        {
            return 1;
        }

        else if(left[c] < right[c])
        {
            return -1;
        }
        c++;
    }

    return 0;
}