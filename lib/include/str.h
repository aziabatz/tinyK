#ifndef MINLIB_STR_H
#define MINLIB_STR_H

char * strcpy(char * dst, const char * src);

char * strncpy(char * dst, const char * src, size_t count);

char * strcat(char * dst, const char * src);

char * strchr(const char * ch, size_t count);

int strcmp(const char * left, const char * right);

char * strdup(const char * src);

size_t strlen(const char * src);

//TODO strerror in system utils

#endif
