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
inline static void ValidateType(FixedSizeBuffer_t *const obj, const int size)
{
    if (obj->mItemSize != size)
    {
        ERROR_MSG("BuffeAppend@(%p) Unexpected type size\n", (void *)obj);
    }
}

inline static uint32_t FixedSizeBufferComputeEffectiveIndex( const uint32_t index, const uint16_t size )
{
    return (index * (uint32_t)size);
}


/// @brief Update the buffer memory of needed
/// @param obj
/// @param size
inline static void UpdateMem(FixedSizeBuffer_t *const obj, const int size)
{
    uint32_t currCapInBytes = obj->mBuffer->mCurrCapacity * obj->mItemSize;
    uint32_t totalCapInBytes = obj->mBuffer->mCapacity * obj->mItemSize;
    uint32_t bytesAvail = currCapInBytes - obj->mBuffer->mSize;
    uint32_t totalBytesAvail = totalCapInBytes - obj->mBuffer->mSize;

    // Cna fit daa in current sized buffer
    if (bytesAvail < size)
    {
        // Can Allocate more data in buffer
        if (totalBytesAvail < size)
        {
            ERROR_MSG("@(%p) out of capacity need %u (%u/%u)\n", (void *)obj, size, totalBytesAvail, totalCapInBytes);
        }

        // Update the size
        int newCap = MIN(obj->mBuffer->mCurrCapacity * 2, obj->mBuffer->mCapacity);
        obj->mBuffer->mData = (char *)realloc(obj->mBuffer->mData, newCap * obj->mItemSize);
        if (obj->mBuffer->mData == NULL)
        {
            ERROR_MSG("BuffeAppend@(%p) Mem reallocation failed\n", (void *)obj);
        }
        obj->mBuffer->mCurrCapacity = newCap;
    }
}

void FixedSizeBufferInit(FixedSizeBuffer_t *obj, const uint16_t tsize, const uint32_t capacity)
{
    obj->mItemSize = tsize;
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

void FixedSizeBufferAppend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size)
{
    ValidateType(obj, size);
    // UpdateMem(obj, size);

    BufferAppend( obj->mBuffer, dataPtr, size );
}

void FixedSizeBufferPrepend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size)
{
    ValidateType(obj, size);

    BufferPrepend( obj->mBuffer, dataPtr, size );
}

void *FixedSizeBufferGet(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size)
{
    ValidateType(obj, size);

    return BufferGet( obj->mBuffer, FixedSizeBufferComputeEffectiveIndex( index, size ), size );
}

void FixedSizeBufferSet(FixedSizeBuffer_t *obj, const uint32_t index, void *dataPtr, const uint16_t size)
{
    ValidateType(obj, size);

    BufferSet( obj->mBuffer, FixedSizeBufferComputeEffectiveIndex( index, size ), dataPtr, size );
}

void *FixedSizeBufferRemove(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size)
{
    ValidateType(obj, size);

    void *dataPtr = BufferRemove( obj->mBuffer, FixedSizeBufferComputeEffectiveIndex( index, size ), size );

    return dataPtr;
}

void *FixedSizeBufferGetLast(FixedSizeBuffer_t *obj, const uint32_t size)
{
    ValidateType(obj, size);

    void *dataPtr = BufferGetLast( obj->mBuffer, size );

    return dataPtr;
}

char *FixedSizeBufferGetDataPtr(FixedSizeBuffer_t *obj, bool copy)
{
    char *temp = BufferGetDataPtr( obj->mBuffer, copy );
    return temp;
}