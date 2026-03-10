#if !defined(__STREAMER_POSITION_H__)
#define __STREAMER_POSITION_H__

#include <stdint.h>

typedef struct StreamerPosition
{
    uint16_t row;
    uint16_t col;
} StreamerPosition_t;

#define STREAMER_POSITION_SIZE  (sizeof(StreamerPosition_t))

#endif // __STREAMER_POSITION_H__
