#if !defined(__QUEUE_H__)
#define __QUEUE_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct FixedSizeBuffer FixedSizeBuffer_t;

typedef struct Queue 
{
    uint32_t mCount;
    FixedSizeBuffer_t * mBuffer;
} Queue_t;

Queue_t *QueueCreate( const uint32_t itemSize, const uint32_t capacity );
void QueueInit( Queue_t *, const uint32_t itemSize, const uint32_t capacity );
void QueueRelease( Queue_t * );
void *QueueFront( Queue_t * );
bool QueuePop( Queue_t * );
bool QueuePush( Queue_t *, void *, const uint32_t size );
bool QueueIsEmpty( Queue_t * );
bool QueueIsFull( Queue_t * );

#endif // __QUEUE_H__
