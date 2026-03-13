#if !defined(__STRING_H__)
#define __STRING_H__

#include  <stdio.h>
#include  <stdint.h>
#include  <stdbool.h>

typedef struct FixedSizeBuffer FixedSizeBuffer_t;

typedef struct String
{
    uint32_t mLen;
    FixedSizeBuffer_t * mBuffer;
} String_t;

#define DEFAULT_STRING_BUFFER_CAPACITY 0x1000

String_t *StringCreate( const char * str, const size_t len );
void StringInit( String_t *, const char * str, const size_t len );
bool StringAppend( String_t *, const char *, const size_t len );
bool StringPrepend( String_t *, const char *, const size_t len );
bool StringInsert( String_t *, const uint32_t, const char *, const size_t len );
bool StringContains( String_t *, const char *, const size_t len );
uint32_t StringFind( String_t *, const char *, const size_t len );
uint32_t StringCopyToBuffer( String_t *, char *, const size_t len );
char *StringCopyToBufferAlloc( String_t * );
void StringRelease( String_t * );

#endif // __STRING_H__
