#if !defined(__MEM_UTILS_H__)
#define __MEM_UTILS_H__

#include <stdio.h>

int Memncpy( char *dst, const char *src, const size_t dstSize, const size_t srcSize );
int Strncpy( char *dst, const char *src, const size_t dstSize, const size_t srcSize );

#endif // __MEM_UTILS_H__
