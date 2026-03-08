#include "Queue.h"
#include "FixedSizeBuffer.h"
#include <stdlib.h>


#define QUEUE_ITEM_SIZE( q )   ( (q)->mBuffer->mItemSize )
#define QUEUE_ITEM_SIZE_THIS( )   ( QUEUE_ITEM_SIZE( this ) )
#define QUEUE_ITEM_CAPACITY( q )   ( (q)->mBuffer->mItemCapacity )
#define QUEUE_ITEM_CAPACITY_THIS( )   ( QUEUE_ITEM_CAPACITY( this ) )

Queue_t *QueueCreate( const uint32_t itemSize, const uint32_t capacity )
{
    Queue_t * q = (Queue_t*)calloc( 1, sizeof(Queue_t));
    QueueInit( q, itemSize, capacity );
    return q;
}

void QueueInit( Queue_t * this, const uint32_t itemSize, const uint32_t capacity )
{
    this->mCount = 0;
    this->mBuffer = FixedSizeBufferCreate( itemSize, capacity );
}

void QueueRelease( Queue_t * this )
{
    if( this->mBuffer )
    {
        this->mCount = 0;
        FixedSizeBufferDestroy( this->mBuffer );
        this->mBuffer = NULL;
    }
}

void *QueueFront( Queue_t * this )
{
    if( QueueIsEmpty( this ) == false )
    {
        return FixedSizeBufferGet( this->mBuffer, 0, QUEUE_ITEM_SIZE_THIS() );
    }
    return NULL;
}

bool QueuePop( Queue_t * this )
{
    if( QueueIsEmpty( this ) == false )
    {
        FixedSizeBufferRemove( this->mBuffer, 0, QUEUE_ITEM_SIZE_THIS() );
        this->mCount--;
        return true;
    }
    return false;
}

bool QueuePush( Queue_t *this, void * data, const uint32_t size )
{
    if( QueueIsFull( this ) == false )
    {
        FixedSizeBufferAppend( this->mBuffer, data, size );
        this->mCount++;
        return true;
    }

    return false;
}

bool QueueIsEmpty( Queue_t * this )
{
    return (this->mCount == 0);
}

bool QueueIsFull( Queue_t * this )
{
    return (this->mCount == QUEUE_ITEM_CAPACITY_THIS());
}

