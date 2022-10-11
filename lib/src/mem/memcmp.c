#include <mem.h>
#include <cast.h>

int memcmp(const void * left, const void * right, size_t count)
{
	for(size_t c = 0; c < count; c++)
	{
		 if(CAST(left,char*)[c] > CAST(right,char*)[c])
		 {
			 return 1;
		 }
		 else if(CAST(right,char*)[c] > CAST(left,char*)[c])
		 {
			 return -1;
		 }
	}
	return 0;
}
