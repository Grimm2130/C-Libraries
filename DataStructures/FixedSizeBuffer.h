#if !defined(_FIXED_SIZE_BUFFERH__)
#define _FIXED_SIZE_BUFFERH__

#include <stdint.h>
#include <stdbool.h>

typedef struct Buffer Buffer_t;

/**
 * Fixed size buffer. Enforces fixed size contraints on all objects appended to memory. Used the variable sized buffer for memory operations.
 */

typedef struct FixedSizeBuffer
{
    uint16_t mItemSize;         // Item size for fixed size buffer
    uint16_t mItemCapacity;         // Item size for fixed size buffer
    Buffer_t *mBuffer;          // Pointer to variable sized buffer object
} FixedSizeBuffer_t;

#define MIN_BUFFER_CAPACITY 1000U

void FixedSizeBufferInit(FixedSizeBuffer_t *obj, const uint16_t tsize, const uint32_t capacity);
FixedSizeBuffer_t *FixedSizeBufferCreate(const uint16_t typeSize, const uint32_t capacity);
void FixedSizeBufferDestroy(FixedSizeBuffer_t *obj);
bool FixedSizeBufferAppend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size);
bool FixedSizeBufferPrepend(FixedSizeBuffer_t *obj, void *dataPtr, const uint16_t size);
bool FixedSizeBufferInsert(FixedSizeBuffer_t *obj, const uint32_t index, void *dataPtr, const uint16_t size);
void *FixedSizeBufferGet(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size);
bool FixedSizeBufferSet(FixedSizeBuffer_t *obj, const uint32_t index, void *dataPtr, const uint16_t size);
void *FixedSizeBufferRemove(FixedSizeBuffer_t *obj, const uint32_t index, const uint16_t size);
void *FixedSizeBufferGetLast(FixedSizeBuffer_t *obj, const uint32_t size);
char *FixedSizeBufferGetDataPtr(FixedSizeBuffer_t *obj, bool copy);

#endif // _FIXED_SIZE_BUFFERH__
