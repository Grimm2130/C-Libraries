#include "Streamer.h"
#include "StringStreamer.h"

static char SSNext( void* streamer )
{
    StringStreamer_t *ssPtr = ((Streamer_t*)streamer)->mStreamerObjPtr;
    return StringStreamerNext( ssPtr );
}

static char SSPeek( void* streamer )
{
    StringStreamer_t *ssPtr = ((Streamer_t*)streamer)->mStreamerObjPtr;
    return StringStreamerPeekFront( ssPtr );
}

static void SSPush( void* streamer, const char c )
{
    StringStreamer_t *ssPtr = ((Streamer_t*)streamer)->mStreamerObjPtr;
    StringStreamerPrev( ssPtr );
}


void StreamerInit_SS( Streamer_t* streamerObj, const char * stream, bool copyStream )
{
    streamerObj->mType = STREAMER_STRING;
    streamerObj->mStreamerObjPtr = StringStreamerCreate( stream, copyStream );
    streamerObj->Next = SSNext;
    streamerObj->Peek = SSPeek;
    streamerObj->Push = SSPush;
}

/// @brief Create a string streamer object
/// @param stream string to be operated on
/// @param copyStream Flag to indicate that the object should be copid
/// @return return Streamer object
Streamer_t *StreamerCreate_SS( const char * stream, bool copyStream )
{
    Streamer_t *ptr = (Streamer_t*)calloc( 1, sizeof(Streamer_t) );
    StreamerInit_SS( ptr, stream, copyStream );
    return ptr;
}

void StreamerRelease( Streamer_t * stream )
{
    switch( stream->mType )
    {
        case STREAMER_STRING:
            StringStreamerRelease( (StringStreamer_t*)stream->mStreamerObjPtr );
        break;
    }
}