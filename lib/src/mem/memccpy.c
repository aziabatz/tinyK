#include <mem.h>

void * memccpy(void * dst, const void * src, unsigned char stop, size_t count)
{
	for(size_t c = 0; c < count; c++)
	{
		if(CAST(src,char*)[c] == stop)
		{
			return dst;
		}

		CAST(dst,char*)[c] = CAST(src,char*)[c];
	}
	return dst;
}
