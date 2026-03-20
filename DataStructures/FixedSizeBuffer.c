#include "Buffer.h"
#include "FixedSizeBuffer.h"
#include "Utils.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

/// @brief  Validate the buffer type size
/// @param obj
/// @param size
inline static bool ValidateType(FixedSizeBuffer_t *const obj, const int size)
{
    bool res = true;

    if (obj->mItemSize != size)
    {
        res = false;
        ERROR_MSG("BuffeAppend@(%p) Unexpected type size\n", (void *)obj);
    }

    return res;
}

inline static uint32_t FixedSizeBufferComputeEffectiveIndex( const uint32_t index, const uint16_t size )
{
    return (index * (uint32_t)size);
}

void FixedSizeBufferInit(FixedSizeBuffer_t *obj, const uint16_t tsize, const uint32_t capacity)
{
    obj->mItemSize = tsize;
    obj->mItemCapacity = capacity;
    // printf("For item of size %u, %u blocks requested. Total Expected %u\n", tsize, capacity, tsize * capacity );
    obj->mBuffer = BufferCreate( tsize * capacity );
}

FixedSizeBuffer_t *FixedSizeBufferCreate(const uint16_t typeSize, const uint32_t capacity)
{
    FixedSizeBuffer_t *objPtr = (FixedSizeBuffer_t *)calloc(1, sizeof(FixedSizeBuffer_t));
    FixedSizeBufferInit(objPtr, typeSize, capacity);
    return objPtr;
}

void FixedSizeBufferDestroy(FixedSizeBuffer_t *obj)
{
    if (obj)
    {
        if( obj->mBuffer )
        {
            BufferDestroy( obj->mBuffer );
        }
        obj->mBuffer = NULL;
    }
}

bool FixedSizeBufferAppend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size)
{
    if( ValidateType(obj, size) )
    {
        return BufferAppend( obj->mBuffer, dataPtr, size );
    }
    
    return false;
}

bool FixedSizeBufferPrepend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size)
{
    if( ValidateType(obj, size) )
    {
        return BufferPrepend( obj->mBuffer, dataPtr, size );
    }
    
    return false;
}

bool FixedSizeBufferInsert(FixedSizeBuffer_t *obj, const uint32_t index, void *dataPtr, const uint16_t size)
{
    if( ValidateType(obj, size) )
    {
        return BufferInsert( obj->mBuffer, FixedSizeBufferComputeEffectiveIndex( index, size ), dataPtr, size );
    }
    
    return false;
}

void *FixedSizeBufferGet(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size)
{
    if( ValidateType(obj, size) )
    {
        return BufferGet( obj->mBuffer, FixedSizeBufferComputeEffectiveIndex( index, size ), size );
    }
    
    return NULL;
}

bool FixedSizeBufferSet(FixedSizeBuffer_t *obj, const uint32_t index, void *dataPtr, const uint16_t size)
{
    if( ValidateType(obj, size) )
    {
        return BufferSet( obj->mBuffer, FixedSizeBufferComputeEffectiveIndex( index, size ), dataPtr, size );
    }

    return false;
}

void *FixedSizeBufferRemove(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size)
{
    void *dataPtr = NULL;
    
    if( ValidateType(obj, size) )
    {
        dataPtr = BufferRemove( obj->mBuffer, FixedSizeBufferComputeEffectiveIndex( index, size ), size );
    }

    return dataPtr;
}

void *FixedSizeBufferGetLast(FixedSizeBuffer_t *obj, const uint32_t size)
{
    void *dataPtr = NULL;

    if(ValidateType(obj, size))
    {
        dataPtr = BufferGetLast( obj->mBuffer, size );
    }

    return dataPtr;
}

char *FixedSizeBufferGetDataPtr(FixedSizeBuffer_t *obj, bool copy)
{
    char *temp = BufferGetDataPtr( obj->mBuffer, copy );
    return temp;
}