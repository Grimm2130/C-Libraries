#if !defined(__STRING_STREAMER_H__)
#define __STRING_STREAMER_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "StreamerPosition.h"

#define SOF ((char)128U)

typedef struct Stack Stack_t;

/// @brief String streamer class
typedef struct StringStreamer
{
    bool mCopied;
    uint32_t mIndex;
    uint32_t mSize;
    StreamerPosition_t mPos;
    Stack_t *mLastPos;
    char * mStream;
} StringStreamer_t;

void StringStreamerInit( StringStreamer_t * streamObj, const char* stream, bool copy );
StringStreamer_t *StringStreamerCreate( const char* stream, bool copy );
void StringStreamerRelease( StringStreamer_t * );
char StringStreamerNext( StringStreamer_t* streamObj );
char StringStreamerPeekFront( StringStreamer_t* streamObj );
char StringStreamerPeekBack( StringStreamer_t* streamObj );
char StringStreamerPrev( StringStreamer_t* streamObj );

#endif // __STRING_STREAMER_H__
