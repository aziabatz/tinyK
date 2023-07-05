#ifndef MINLIB_STR_H
#define MINLIB_STR_H

#include "stddef.h"

char * strcpy(char * dst, const char * src);

char * strncpy(char * dst, const char * src, size_t count);

char * strcat(char * dst, const char * src);

char * strchr(const char * src, char ch);

int strcmp(const char * left, const char * right);

char * strdup(const char * src);

size_t strlen(const char * src);


#endif
