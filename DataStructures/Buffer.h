#if !defined(__BUFFER_H__)
#define __BUFFER_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct Buffer
{
    uint16_t mItemSize;
    uint32_t mSize;
    uint32_t mCurrCapacity;
    uint32_t mCapacity;
    char *mData;
} Buffer_t;

#define MIN_BUFFER_CAPACITY 1000U

void BufferInit(Buffer_t *obj, const uint16_t tsize, const uint32_t capacity);
Buffer_t *BufferCreate(const uint16_t typeSize, const uint32_t capacity);
void BufferDestroy(Buffer_t *obj);
void BufferAppend(Buffer_t *obj, void *dataPtr, const uint16_t size);
void BufferPrepend(Buffer_t *obj, void *dataPtr, const uint16_t size);
void *BufferGet(Buffer_t *obj, const uint32_t index, const uint16_t size);
void BufferSet(Buffer_t *obj, const uint32_t index, void *dataPtr, const uint16_t size);
void *BufferRemove(Buffer_t *obj, const uint32_t index, const uint16_t size);
void *BufferGetLast(Buffer_t *obj, const uint32_t size);
char *BufferGetDataPtr(Buffer_t *obj, bool copy);

#endif // __BUFFER_H__
