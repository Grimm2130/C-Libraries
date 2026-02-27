#if !defined(__STREAMER_H__)
#define __STREAMER_H__

#include <stdbool.h>

typedef enum StreamerType
{
    STREAMER_STRING
} StreamerType_t;

typedef struct Streamer
{
    StreamerType_t mType;
    void * mStreamerObjPtr;
    char (*Next)( void* streamer );
    char (*Peek)( void* streamer );
    void (*Push)( void* streamer, const char c );
} Streamer_t;

Streamer_t *StreamerCreate_SS( const char * stream, bool copyStream );
void StreamerRelease( Streamer_t * );


#endif // __STREAMER_H__
