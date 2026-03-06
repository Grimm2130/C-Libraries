#if !defined(_FIXED_SIZE_BUFFERH__)
#define _FIXED_SIZE_BUFFERH__

#include <stdint.h>
#include <stdbool.h>

typedef struct FixedSizeBuffer
{
    uint16_t mItemSize;
    uint32_t mSize;
    uint32_t mCurrCapacity;
    uint32_t mCapacity;
    char *mData;
} FixedSizeBuffer_t;

#define MIN_BUFFER_CAPACITY 1000U

void FixedSizeBufferInit(FixedSizeBuffer_t *obj, const uint16_t tsize, const uint32_t capacity);
FixedSizeBuffer_t *FixedSizeBufferCreate(const uint16_t typeSize, const uint32_t capacity);
void FixedSizeBufferDestroy(FixedSizeBuffer_t *obj);
void FixedSizeBufferAppend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size);
void FixedSizeBufferPrepend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size);
void *FixedSizeBufferGet(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size);
void FixedSizeBufferSet(FixedSizeBuffer_t *obj, const uint32_t index, void *dataPtr, const uint16_t size);
void *FixedSizeBufferRemove(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size);
void *FixedSizeBufferGetLast(FixedSizeBuffer_t *obj, const uint32_t size);
char *FixedSizeBufferGetDataPtr(FixedSizeBuffer_t *obj, bool copy);

#endif // _FIXED_SIZE_BUFFERH__
