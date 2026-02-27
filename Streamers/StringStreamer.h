#if !defined(__STRING_STREAMER_H__)
#define __STRING_STREAMER_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define SOF ((char)128U)

/// @brief String streamer class
typedef struct StringStreamer
{
    bool mCopied;
    uint32_t mRow;
    uint32_t mCol;
    uint32_t mIndex;
    size_t  mSize;
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
