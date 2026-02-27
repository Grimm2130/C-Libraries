#include "MemUtils.h"
#include "MathUtils.h"
#include <string.h>
#include <stdlib.h>

int Memncpy( char *dst, const char *src, const size_t dstSize, const size_t srcSize )
{
    int copySize = 0;

    if( dst )
    {
        if( src )
        {
            copySize = MIN(dstSize, srcSize);
            if( memcpy(dst, src, copySize) == NULL )
            {
                copySize = 0;
            }
        }
    }

    return copySize;
}


int Strncpy( char *dst, const char *src, const size_t dstSize, const size_t srcSize )
{
    int len = Memncpy( dst, src, dstSize, srcSize );

    // Null terminate string
    dst[len] = '\0';

    return len;
}

int ShiftData( char *buf, const int bufSize, const int srcOffset, const int dstOffset, const int size )
{
    char *ptr;
    char *temp;
    temp = ptr = NULL;

    if( size == 0 )
    {
        return size;
    }

    // Store the source data
    if( (srcOffset + size) <= bufSize )
    {
        temp = calloc( size, sizeof(char) );
        ptr = buf + srcOffset;
        
        if( Memncpy( temp, ptr, size, size ) == 0 )
        {
            free(temp);
            return 0;
        }
    }

    if( temp == NULL )
    {
        return 0;
    }

    // Check if data can fit in destination
    if( (dstOffset + size) <= bufSize )
    {
        ptr = buf + dstOffset;

        if( Memncpy( ptr, temp, size, size ) == 0 )
        {
            free(temp);
            return 0;
        }
    }

    free(temp);

    return size;
}