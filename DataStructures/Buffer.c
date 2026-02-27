#include "Buffer.h"
#include "Utils.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

/// @brief  Validate the buffer type size
/// @param obj
/// @param size
inline static void ValidateType(Buffer_t *const obj, const int size)
{
    if (obj->mItemSize != size)
    {
        ERROR_MSG("BuffeAppend@(%p) Unexpected type size\n", (void *)obj);
    }
}

/// @brief Update the buffer memory of needed
/// @param obj
/// @param size
inline static void UpdateMem(Buffer_t *const obj, const int size)
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

void BufferInit(Buffer_t *obj, const uint16_t tsize, const uint32_t capacity)
{
    obj->mSize = 0;
    obj->mItemSize = tsize;
    obj->mCapacity = capacity;
    obj->mCurrCapacity = MAX(MIN_BUFFER_CAPACITY, capacity / 100);
    obj->mData = (char *)calloc(tsize * capacity, sizeof(char));
}

Buffer_t *BufferCreate(const uint16_t typeSize, const uint32_t capacity)
{
    Buffer_t *objPtr = (Buffer_t *)calloc(1, sizeof(Buffer_t));
    BufferInit(objPtr, typeSize, capacity);
    return objPtr;
}

void BufferDestroy(Buffer_t *obj)
{
    if (obj)
    {
        if (obj->mData)
            free(obj->mData);
        obj->mData = NULL;
    }
}

void BufferAppend(Buffer_t *obj, void *dataPtr, const uint16_t size)
{
    ValidateType(obj, size);
    UpdateMem(obj, size);

    int copied = Memncpy((obj->mData + obj->mSize), (char *)dataPtr, size, size);

    if (copied < size)
    {
        ERROR_MSG("BufferAppend@(%p) Append operation failed\n", ((void *)(obj)));
    }

    obj->mSize += size;
}

void BufferPrepend(Buffer_t *obj, void *dataPtr, const uint16_t size)
{
    ValidateType(obj, size);
    UpdateMem(obj, size);

    // Shift the data
    // if( obj->mSize )
    ShiftData(obj->mData, (obj->mCurrCapacity * obj->mItemSize), 0, size, obj->mSize);

    if (Memncpy(obj->mData, (char *)dataPtr, size, size) != size)
    {
        ERROR_MSG("BufferPrepend@(%p) Prepend operation failed\n", ((void *)(obj)));
    }

    obj->mSize += size;
}

void *BufferGet(Buffer_t *obj, const uint32_t index, const uint16_t size)
{
    ValidateType(obj, size);

    uint32_t effSize = index * size;

    if (effSize >= obj->mSize)
    {
        return NULL;
    }

    return (void *)(obj->mData + effSize);
}

void BufferSet(Buffer_t *obj, const uint32_t index, void *dataPtr, const uint16_t size)
{
    ValidateType(obj, size);

    uint32_t effSize = index * size;

    if (effSize >= obj->mSize)
    {
        // WARN_MSG("BufferSet@(%p) Append operation failed\n", ((void *)(obj)));
        return;
    }

    char *ptr = obj->mData + effSize;

    if (Memncpy(ptr, (char *)dataPtr, size, size) == 0)
    {
        ERROR_MSG("BufferSet@(%p) Failed\n", ((void *)(obj)));
    }
}

void *BufferRemove(Buffer_t *obj, const uint32_t index, const uint16_t size)
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
        ERROR_MSG("BufferRemove@(%p) Failed on caching\n", ((void *)(obj)));
    }

    // Shift the remaining objects left
    int shiftSize = (obj->mSize - effIndex) - size;
    if (ShiftData(obj->mData, obj->mSize, effIndex + size, effIndex, shiftSize) != shiftSize)
    {
        ERROR_MSG("BufferRemove@(%p) Failed\n", ((void *)(obj)));
    }

    obj->mSize -= size;

    return dataPtr;
}

void *BufferGetLast(Buffer_t *obj, const uint32_t size)
{
    ValidateType( obj, size );

    uint32_t lastOffset = obj->mSize - size;

    if( lastOffset < 0 ) return NULL;
    else
    {
        int lastIndex = lastOffset / size;
        return BufferGet( obj, lastIndex, size );
    }
}

char *BufferGetDataPtr(Buffer_t *obj, bool copy)
{
    char *temp;

    if (copy)
    {
        temp = calloc(obj->mSize, sizeof(char));

        if (Memncpy(temp, obj->mData, obj->mSize, obj->mSize) != obj->mSize)
        {
            ERROR_MSG("BufferGetDataPtr@(%p) Failed\n", ((void *)(obj)));
        }
    }
    else
    {
        temp = obj->mData;
    }

    return temp;
}