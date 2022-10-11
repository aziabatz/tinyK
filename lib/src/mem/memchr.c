#include <mem.h>


void * memchr(const void * ptr, unsigned char ch, size_t count)
{
	for(size_t c = 0; c < count; c++)
	{
		if(CAST(ptr,char*)[c] == ch)
		{
			return ptr+c;
		}
	}
	return NULL;
}