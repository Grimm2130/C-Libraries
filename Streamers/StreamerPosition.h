#if !defined(__STREAMER_POSITION_H__)
#define __STREAMER_POSITION_H__

#include <stdint.h>
#include <stdio.h>
#define STREAMER_POSITION_STR_BUFFER_LEN (20U)

typedef struct StreamerPosition
{
    uint16_t row;
    uint16_t col;
} StreamerPosition_t;

#define STREAMER_POSITION_RESET( pos )  (pos.row = pos.col = 0)


#define STREAMER_POSITION_SIZE  (sizeof(StreamerPosition_t))

#endif // __STREAMER_POSITION_H__
