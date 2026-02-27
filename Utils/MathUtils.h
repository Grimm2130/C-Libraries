#if !defined(__MATH_UTILS_H__)
#define __MATH_UTILS_H__

#include <math.h>

#define MIN( a, b ) ( (a) < (b) ? (a) : (b) )
#define MAX( a, b ) ( (a) >= (b) ? (a) : (b) )
#define INT_CMP( a, b ) ( (a) == (b) ? 0 : (((a) > (b)) ? 1 : -1) )

#define     FLT_EPSILON     (1E-3) 
#define     FLT_MAX( a, b ) (((a) - (b)) > FLT_EPSILON) ? (a) : (b)
#define     FLT_MIN( a, b ) FLT_MAX( b, a )
#define     FLT_CMP( a, b ) ( (a) == (b) ? 0 : ((FLT_MIN((a), (b)) == a) ? -1 : 1) )

int ShiftData( char *buf, const int bufSize, const int srcOffset, const int dstOffset, const int size );

#endif // __MATH_UTILS_H__
