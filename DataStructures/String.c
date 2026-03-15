#include "String.h"
#include "FixedSizeBuffer.h"
#include "MemUtils.h"
#include "MathUtils.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

String_t *StringCreate( const char * str, const size_t len )
{
    String_t *this = (String_t*)calloc(1, sizeof(String_t));
    StringInit( this, str, len );
    return this;
}

void StringInit( String_t * this, const char * str, const size_t len )
{
    if( this )
    {
        this->mLen = len;
        this->mBuffer = FixedSizeBufferCreate( sizeof(char), DEFAULT_STRING_BUFFER_CAPACITY );
        FixedSizeBufferAppend( this->mBuffer, (void*) str, len );
    }
    else
    {
        exit(ENOBUFS);
    }
}

bool StringAppend( String_t * this, const char * str, const size_t len )
{
    return FixedSizeBufferAppend( this->mBuffer, (void*) str, len );
}

bool StringPrepend( String_t *this, const char *str, const size_t len )
{
    return FixedSizeBufferPrepend( this->mBuffer, (void*) str, len );
}

void StringClear( String_t * this )
{
    this->mLen = 0;
    if( this->mBuffer )
    {
        // delete buffer and reinstantiate
        FixedSizeBufferDestroy( this->mBuffer );
        this->mBuffer = FixedSizeBufferCreate( sizeof(char), DEFAULT_STRING_BUFFER_CAPACITY );
    }
}

bool StringInsert( String_t *this, const uint32_t index, const char *str, const size_t len )
{
    return FixedSizeBufferPrepend( this->mBuffer, (void*) str, len );
}

bool StringContains( String_t * this, const char * str, const size_t len )
{
    return (StringFind( this, str, len ) >= 0);
}

uint32_t StringFind( String_t *this, const char *str, const size_t len )
{
    int i;
    bool found = false;
    char * s = (char*) FixedSizeBufferGetDataPtr( this->mBuffer, false );

    for( i = 0; i < this->mLen; i++ )
    {
        // first occurence
        if( s[i] == str[0] )
        {
            
            if( Memncmp( s + i, str, (this->mLen - i), len ) == 0 )
            {
                found = true;
                break;
            }
        }
    }

    return found ? i : -1;
}

uint32_t StringCopyToBuffer( String_t *this, char * buf, const size_t len )
{
    int copylen = -1;

    if( buf )
    {
        copylen = MIN( this->mLen, len-1 );

        if( Memncpy( buf, FixedSizeBufferGetDataPtr( this->mBuffer, false ), this->mLen, len-1 ) == copylen )
        {
            buf[copylen] = '\0';
        }
    }

    return copylen;
}

char *StringCopyToBufferAlloc( String_t *this )
{
    char * buf = (char*)calloc( this->mLen + 1, sizeof(char));

    if( StringCopyToBuffer( this, buf, this->mLen + 1 ) == this->mLen )
    {
        return buf;
    }
    else
    {
        if( buf ) free( buf );
        return NULL;   
    }
}

void StringRelease( String_t * this )
{
    if( this )
    {
        this->mLen = 0;
        if( this->mBuffer )
        {
            FixedSizeBufferDestroy( this->mBuffer );
            this->mBuffer = NULL;
        }
    }
}
