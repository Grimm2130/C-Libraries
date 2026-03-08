#if !defined(__STACK_H__)
#define __STACK_H__

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct FixedSizeBuffer FixedSizeBuffer_t;

typedef struct Stack
{
    uint32_t          mCount;
    FixedSizeBuffer_t *mBuffer;
} Stack_t;

Stack_t * StackCreate( const size_t itemSize, const uint32_t capacity );
void StackInit( Stack_t *, const size_t itemSize, const uint32_t capacity );
void StackRelease( Stack_t *);
void * StackTop( Stack_t *);
bool StackPop( Stack_t *);
bool StackPush( Stack_t *, void *, const size_t );
bool StackIsEmpty( Stack_t * );
bool StackIsFull( Stack_t * );

#endif // __STACK_H__
