#include "StringStreamer.h"
#include "Utils.h"
#include "Stack.h"
#include <stdio.h>

#include <memory.h>

static bool StringStreamerEmpty(StringStreamer_t * streamObj );
static bool StringStreamerFull(StringStreamer_t * streamObj );
static void StringStreamerProcessNext(StringStreamer_t * streamObj, const char next );
static void StringStreamerProcessPrev(StringStreamer_t * streamObj, const char next );

static bool StringStreamerEmpty(StringStreamer_t * streamObj )
{
    return streamObj->mIndex >= streamObj->mSize;
}

static bool StringStreamerFull(StringStreamer_t * streamObj )
{
    return streamObj->mIndex == 0;
}

static void StringStreamerProcessNext(StringStreamer_t * streamObj, const char next )
{
    switch( next )
    {
    case '\n':
        // Store the last position
        StackPush( streamObj->mLastPos, &(streamObj->mPos), STREAMER_POSITION_SIZE );
        streamObj->mPos.col = 0;
        streamObj->mPos.row++;
    break;
        
    default:    
        streamObj->mPos.col++;
    break;
    }
}

static void StringStreamerProcessPrev(StringStreamer_t * streamObj, const char next )
{
    StreamerPosition_t *last;
    
    switch( next )
    {
    case '\n':
        if( StackIsEmpty( streamObj->mLastPos ) == false )
        {
            if( (last = (StreamerPosition_t*)StackTop( streamObj->mLastPos )) )
            {
                streamObj->mPos.col = last->col;
                streamObj->mPos.row = last->row;
                StackPop( streamObj->mLastPos );
            }
        }
    break;
        
    default:    
        streamObj->mPos.col--;
    break;
    }
}

void StringStreamerInit( StringStreamer_t * streamObj, const char* stream, bool copy )
{
    size_t len = strlen(stream);
    
    streamObj->mPos.col = streamObj->mPos.row = streamObj->mIndex = 0;

    if( copy )
    {
        streamObj->mCopied = true;
        streamObj->mStream = (char*)calloc( len, sizeof(char) );
        if( Memncpy( streamObj->mStream, stream, len, len ) != len )
        {
            ERROR_MSG("String Stream Initialization failed");
        }
    }
    else
    {
        streamObj->mStream = (char*)stream;
    }

    // Allocate stack for tracking last position
    streamObj->mLastPos = StackCreate( STREAMER_POSITION_SIZE, 1000U );
    streamObj->mSize = len;
}

StringStreamer_t *StringStreamerCreate( const char* stream, bool copy )
{
    StringStreamer_t *obj = (StringStreamer_t*)calloc( 1, sizeof(StringStreamer_t) );
    StringStreamerInit( obj, stream, copy );
    return obj;
}

void StringStreamerRelease( StringStreamer_t * stream )
{

}

// get the next character in the stream
char StringStreamerNext( StringStreamer_t* streamObj )
{
    char res = StringStreamerPeekFront( streamObj );
    
    StringStreamerProcessNext( streamObj, res );
    
    if( res != EOF ) streamObj->mIndex++;
    
    return res;
}


char StringStreamerPeekFront( StringStreamer_t* streamObj )
{
    char res;

    if(  StringStreamerEmpty(streamObj) )
    {
        res = '\0';
    }
    else
    {
        res = streamObj->mStream[ streamObj->mIndex ];
    }

    return res;
}

char StringStreamerPeekBack( StringStreamer_t* streamObj )
{
    char res;

    if(  StringStreamerFull(streamObj) )
    {
        res = '\0';
    }
    else
    {
        res = streamObj->mStream[ (streamObj->mIndex - 1) ];
    }

    StringStreamerProcessPrev( streamObj, res );

    return res;
}


char StringStreamerPrev( StringStreamer_t* streamObj )
{
    char res = StringStreamerPeekBack( streamObj );
    if( res != SOF ) streamObj->mIndex--;
    return res;
}

