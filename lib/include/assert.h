#ifndef MINLIB_ASSERT_H
#define MINLIB_ASSERT_H

extern void __assert(const char * msg, const char * file, unsigned int line);

#define assert(exp) (void)((exp) || (__assert(#exp, __FILE__, __LINE__), 0))

#endif
