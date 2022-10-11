#include <mem.h>


void * memset(void * dst, unsigned char ch, size_t count)
{
	for(size_t c = 0; c < count; c++)
	{
		CAST(dst,char*)[c] = ch;
	}
	return dst;
}
