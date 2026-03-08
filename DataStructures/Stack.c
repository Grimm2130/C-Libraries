#include "Stack.h"
#include "FixedSizeBuffer.h"
#include <stdlib.h>

#define STACK_ITEM_SIZE( st )   ( (st)->mBuffer->mItemSize )
#define STACK_ITEM_SIZE_THIS( )   ( STACK_ITEM_SIZE( this ) )
#define STACK_ITEM_CAPACITY( st )   ( (st)->mBuffer->mItemCapacity )
#define STACK_ITEM_CAPACITY_THIS( )   ( STACK_ITEM_CAPACITY( this ) )

Stack_t * StackCreate( const size_t itemSize, const uint32_t capacity )
{
    Stack_t* st = calloc( 1, sizeof( Stack_t) );
    StackInit( st, itemSize, capacity );
    return st;
}

void StackInit( Stack_t * this, const size_t itemSize, const uint32_t capacity )
{
    this->mCount = 0;
    this->mBuffer = FixedSizeBufferCreate( itemSize, capacity );
}

void StackRelease( Stack_t * this)
{
    if( this->mBuffer )
    {
        this->mCount = 0;
        FixedSizeBufferDestroy( this->mBuffer );
        this->mBuffer = NULL;
    }
}

void * StackTop( Stack_t * this )
{
    if( StackIsEmpty( this ) == false  )
    {
        return FixedSizeBufferGet( this->mBuffer, 0, STACK_ITEM_SIZE_THIS() );
    }
    return NULL;
}

bool StackPop( Stack_t *this)
{
    if( StackIsEmpty( this ) == false )
    {
        FixedSizeBufferRemove( this->mBuffer, 0, STACK_ITEM_SIZE_THIS() );
        this->mCount--;
        return true;
    }
    return false;
}

bool StackPush( Stack_t * this, void * data, const size_t dataSize )
{
    if( StackIsFull(this) == false )
    {
        FixedSizeBufferPrepend( this->mBuffer, data, dataSize );
        this->mCount++;
        return true;
    }
    return false;
}

bool StackIsEmpty( Stack_t * this)
{
    return (this->mCount == 0);
}   

bool StackIsFull( Stack_t * this )
{
    return (this->mCount ==  STACK_ITEM_CAPACITY_THIS() );
}