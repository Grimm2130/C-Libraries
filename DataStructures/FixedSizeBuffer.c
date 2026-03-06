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

/// @brief Update the buffer memory of needed
/// @param obj
/// @param size
inline static void UpdateMem(FixedSizeBuffer_t *const obj, const int size)
{
    uint32_t currCapInBytes = obj->mCurrCapacity * obj->mItemSize;
    uint32_t totalCapInBytes = obj->mCapacity * obj->mItemSize;
    uint32_t bytesAvail = currCapInBytes - obj->mSize;
    uint32_t totalBytesAvail = totalCapInBytes - obj->mSize;

    // Cna fit daa in current sized buffer
    if (bytesAvail < size)
    {
        // Can Allocate more data in buffer
        if (totalBytesAvail < size)
        {
            ERROR_MSG("@(%p) out of capacity need %u (%u/%u)\n", (void *)obj, size, totalBytesAvail, totalCapInBytes);
        }

        // Update the size
        int newCap = MIN(obj->mCurrCapacity * 2, obj->mCapacity);
        obj->mData = (char *)realloc(obj->mData, newCap * obj->mItemSize);
        if (obj->mData == NULL)
        {
            ERROR_MSG("BuffeAppend@(%p) Mem reallocation failed\n", (void *)obj);
        }
        obj->mCurrCapacity = newCap;
    }
}

void FixedSizeBufferInit(FixedSizeBuffer_t *obj, const uint16_t tsize, const uint32_t capacity)
{
    obj->mSize = 0;
    obj->mItemSize = tsize;
    obj->mCapacity = capacity;
    obj->mCurrCapacity = MAX(MIN_BUFFER_CAPACITY, capacity / 100);
    obj->mData = (char *)calloc(tsize * capacity, sizeof(char));
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
        if (obj->mData)
            free(obj->mData);
        obj->mData = NULL;
    }
}

void FixedSizeBufferAppend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size)
{
    ValidateType(obj, size);
    UpdateMem(obj, size);

    int copied = Memncpy((obj->mData + obj->mSize), (char *)dataPtr, size, size);

    if (copied < size)
    {
        ERROR_MSG("FixedSizeBufferAppend@(%p) Append operation failed\n", ((void *)(obj)));
    }

    obj->mSize += size;
}

void FixedSizeBufferPrepend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size)
{
    ValidateType(obj, size);
    UpdateMem(obj, size);

    // Shift the data
    // if( obj->mSize )
    ShiftData(obj->mData, (obj->mCurrCapacity * obj->mItemSize), 0, size, obj->mSize);

    if (Memncpy(obj->mData, (char *)dataPtr, size, size) != size)
    {
        ERROR_MSG("FixedSizeBufferPrepend@(%p) Prepend operation failed\n", ((void *)(obj)));
    }

    obj->mSize += size;
}

void *FixedSizeBufferGet(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size)
{
    ValidateType(obj, size);

    uint32_t effSize = index * size;

    if (effSize >= obj->mSize)
    {
        return NULL;
    }

    return (void *)(obj->mData + effSize);
}

void FixedSizeBufferSet(FixedSizeBuffer_t *obj, const uint32_t index, void *dataPtr, const uint16_t size)
{
    ValidateType(obj, size);

    uint32_t effSize = index * size;

    if (effSize >= obj->mSize)
    {
        // WARN_MSG("FixedSizeBufferSet@(%p) Append operation failed\n", ((void *)(obj)));
        return;
    }

    char *ptr = obj->mData + effSize;

    if (Memncpy(ptr, (char *)dataPtr, size, size) == 0)
    {
        ERROR_MSG("FixedSizeBufferSet@(%p) Failed\n", ((void *)(obj)));
    }
}

void *FixedSizeBufferRemove(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size)
{
    ValidateType(obj, size);

    uint32_t effIndex = index * size;

    if (effIndex >= obj->mSize)
    {
        return NULL;
    }

    char *ptr = obj->mData + effIndex;
    char *dataPtr = (char *)calloc(size, sizeof(char));

    // Copy object at location
    if (Memncpy(dataPtr, ptr, size, size) == 0)
    {
        ERROR_MSG("FixedSizeBufferRemove@(%p) Failed on caching\n", ((void *)(obj)));
    }

    // Shift the remaining objects left
    int shiftSize = (obj->mSize - effIndex) - size;
    if (ShiftData(obj->mData, obj->mSize, effIndex + size, effIndex, shiftSize) != shiftSize)
    {
        ERROR_MSG("FixedSizeBufferRemove@(%p) Failed\n", ((void *)(obj)));
    }

    obj->mSize -= size;

    return dataPtr;
}

void *FixedSizeBufferGetLast(FixedSizeBuffer_t *obj, const uint32_t size)
{
    ValidateType(obj, size);

    uint32_t lastOffset = obj->mSize - size;

    if (lastOffset < 0)
        return NULL;
    else
    {
        int lastIndex = lastOffset / size;
        return FixedSizeBufferGet(obj, lastIndex, size);
    }
}

char *FixedSizeBufferGetDataPtr(FixedSizeBuffer_t *obj, bool copy)
{
    char *temp;

    if (copy)
    {
        temp = calloc(obj->mSize, sizeof(char));

        if (Memncpy(temp, obj->mData, obj->mSize, obj->mSize) != obj->mSize)
        {
            ERROR_MSG("FixedSizeBufferGetDataPtr@(%p) Failed\n", ((void *)(obj)));
        }
    }
    else
    {
        temp = obj->mData;
    }

    return temp;
}