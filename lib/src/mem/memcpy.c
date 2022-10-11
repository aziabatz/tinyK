#include <mem.h>
#include <cast.h>

void * memcpy(void * dst, const void * src, size_t count)
{
	for(size_t c = 0; c < count; c++)
	{
		//fixme declare aux variables??
		CAST(dst,char*)[c] = CAST(src,char*)[c];
	}
	return dst;
}
