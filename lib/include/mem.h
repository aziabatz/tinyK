#ifndef MINLIB_MEM_H
#define MINLIB_MEM_H

#include <stddef.h>
#include <cast.h>

//copia n caracteres hasta terminar o encontrar char de terminacion
void * memccpy(void * dst, const void * src, unsigned char stop, size_t count);

//busca un byte en n caracteres desde ptr
void * memchr(const void * ptr, unsigned char ch, size_t count);

//compara n caraceteres
int memcmp(const void * left, const void * right, size_t count);

void * memcpy(void * dst, const void * src, size_t count);

//igual que cpy pero con overlap
void * memmove(void * dst, const void * src, size_t count);

void * memset(void * dst, unsigned char ch, size_t count);

#endif
