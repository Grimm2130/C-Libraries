#include "String.h"
#include "Buffer.h"
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
        this->mBuffer = BufferCreate( DEFAULT_STRING_BUFFER_CAPACITY );
        BufferAppend( this->mBuffer, (void*) str, len );
    }
    else
    {
        exit(ENOBUFS);
    }
}

bool StringAppend( String_t * this, const char * str, const size_t len )
{
    bool res;

    if( (res = BufferAppend( this->mBuffer, (void*) str, len )) )
    {
        this->mLen += len;
    }

    return res;
}

bool StringPrepend( String_t *this, const char *str, const size_t len )
{
    bool res;

    if( (res = BufferPrepend( this->mBuffer, (void*) str, len )) )
    {
        this->mLen += len;
    }
    
    return res;
}

void StringClear( String_t * this )
{
    this->mLen = 0;
    if( this->mBuffer )
    {
        // delete buffer and reinstantiate
        BufferDestroy( this->mBuffer );
        this->mBuffer = BufferCreate( DEFAULT_STRING_BUFFER_CAPACITY );
    }
}

bool StringInsert( String_t *this, const uint32_t index, const char *str, const size_t len )
{
    bool res;

    if( (res = BufferInsert( this->mBuffer, index, (void*) str, len )) )
    {
        this->mLen += len;
    }
    
    return res;
}

bool StringContains( String_t * this, const char * str, const size_t len )
{
    return (StringFind( this, str, len ) >= 0);
}

int StringFind( String_t *this, const char *str, const size_t len )
{
    int i;
    bool found = false;
    char * s = (char*) BufferGetDataPtr( this->mBuffer, false );

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

        if( Memncpy( buf, BufferGetDataPtr( this->mBuffer, false ), this->mLen, len-1 ) == copylen )
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
            BufferDestroy( this->mBuffer );
            this->mBuffer = NULL;
        }
    }
}
