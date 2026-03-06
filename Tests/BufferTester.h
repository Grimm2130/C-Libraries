#if !defined(_BUFFERTESTER_H__)
#define _BUFFERTESTER_H__

#include "Buffer.h"
#include "Utils.h"
#include "Person.h"
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>

static bool BufferTestCreate();
static bool BufferTestAppend();
static bool BufferTestRemove();
static bool BufferTestDestroy();
static bool BufferTestGetter();
static bool BufferTestSetter();
static bool BufferTestPrepend();

static const int gBufferCapacity = PERSONS_COUNT * PERSON_SIZE;
Buffer_t *gBufferPtr = NULL;

bool RunTestsBuffer()
{
    bool res = false;

    if (BufferTestCreate())
    {
        if (BufferTestAppend())
        {
            if (BufferTestGetter())
            {
                if (BufferTestSetter())
                {
                    if (BufferTestRemove())
                    {
                        if (BufferTestPrepend())
                        {
                            if (BufferTestRemove())
                            {
                                if (BufferTestDestroy())
                                {
                                    gBufferPtr = NULL;
                                    res = true;
                                }
                                else
                                {
                                }
                            }
                            else
                            {
                            }
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                    }
                }
                else
                {
                }
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
    }

    return res;
}

static bool BufferTestCreate()
{
    bool res = false;

    INFO_MSG("Buffer Creation...");
    gBufferPtr = BufferCreate(gBufferCapacity);

    if (gBufferPtr)
    {
        if (gBufferPtr->mSize == 0)
        {
            if (gBufferPtr->mData)
            {
                if ((gBufferPtr->mCurrCapacity == gBufferCapacity / 100) || (gBufferPtr->mCurrCapacity == MIN_BUFFER_CAPACITY))
                {
                    if (gBufferPtr->mCapacity == gBufferCapacity)
                    {
                        res = true;
                        INFO_MSG("Buffer Creation...Passed");
                    }
                    else
                    {
                        FAIL_MSG("Buffer Created with capacity %d, actual %d", gBufferCapacity, gBufferPtr->mCurrCapacity);
                    }
                }
                else
                {
                    FAIL_MSG("Buffer Created with capacity %d, actual %d", gBufferCapacity, gBufferPtr->mCurrCapacity);
                }
            }
            else
            {
                FAIL_MSG("Buffer Created without actual data space");
            }
        }
        else
        {
            FAIL_MSG("Buffer Created without empty buffer");
        }
    }
    else
    {
        FAIL_MSG("Buffer Creation Failed");
    }

    return res;
}

static bool BufferTestAppend()
{
    bool res = true;

    uint32_t currSize = 0;
    uint32_t finalSize = PERSON_SIZE * PERSONS_COUNT;

    INFO_MSG("Buffer Append...");

    for (int i = 0; i < PERSONS_COUNT; i++)
    {
        BufferAppend(gBufferPtr, (void *)&gPersons[i], PERSON_SIZE);
        currSize += PERSON_SIZE;

        if (gBufferPtr->mSize != currSize)
        {
            FAIL_MSG("Buffer Append...Failed @ index %d", i);
            break;
        }
    }

    if (gBufferPtr->mSize == finalSize)
    {
        PASS_MSG("Buffer Append...Passed");
        res = true;
    }
    else
    {
        FAIL_MSG("Buffer Append...Failed");
    }

    return res;
}

static bool BufferTestPrepend()
{
    uint32_t index;
    bool res = true;
    Person_t *person;

    INFO_MSG("Buffer Prepend...");

    for (int i = PERSONS_COUNT - 1; i >= 0; i--)
    {
        BufferPrepend(gBufferPtr, (void *)&gPersons[i], PERSON_SIZE);
        person = (Person_t *)gBufferPtr->mData;
        INFO_MSG("\t-Prepended From index %d - %s", i, PersonStr(person) );
    }

    for (int i = 0; i < 100; i++)
    {
        index = rand() % PERSONS_COUNT;
        person = (Person_t *)BufferGet(gBufferPtr, (index * PERSON_SIZE), PERSON_SIZE);

        // INFO_MSG("Retrieved From index %d - %s", index, PersonStr(person) );

        if (PersonCmp(person, &gPersons[index]))
        {
            FAIL_MSG("\t-Buffer Prepend...Failed @ index %d", index);
            res = false;
            break;
        }
    }

    PASS_MSG("Buffer Prepend...Done");

    return res;
}

static bool BufferTestGetter()
{
    uint32_t index;
    uint32_t effAddr;

    bool res = true;

    INFO_MSG("Buffer Getter...");

    for (int i = 0; i < 100; i++)
    {
        index = rand() % PERSONS_COUNT;
        Person_t *person = (Person_t *)BufferGet(gBufferPtr, (index * PERSON_SIZE), PERSON_SIZE);

        // INFO_MSG("Retrieved From index %d - %s", index, PersonStr(person) );

        if (PersonCmp(person, &gPersons[index]))
        {
            FAIL_MSG("Buffer Getter...Failed");
            res = false;
            break;
        }
    }

    PASS_MSG("Buffer Getter...Passed");

    return res;
}
static bool BufferTestSetter()
{
    uint32_t index;

    INFO_MSG("Buffer Setter...");

    bool res = true;

    for (int i = 0; i < PERSONS_COUNT; i++)
    {
        BufferSet(gBufferPtr, (i * PERSON_SIZE), (void *)&gPersons[i], PERSON_SIZE);
    }

    for (int i = 0; i < 100; i++)
    {
        index = rand() % PERSONS_COUNT;
        Person_t *person = (Person_t *)BufferGet(gBufferPtr, (index * PERSON_SIZE), PERSON_SIZE);

        // INFO_MSG("Retrieved From index %d - %s", index, PersonStr(person) );

        if (PersonCmp(person, &gPersons[index]))
        {
            FAIL_MSG("Buffer Setter...Failed @ index %d", index);
            res = false;
            break;
        }
    }

    if (res)
    {
        PASS_MSG("Buffer Setter...Passed");
    }

    return res;
}
static bool BufferTestRemove()
{
    bool res = true;
    int index = 0;

    INFO_MSG("Buffer Remove....");

    while (gBufferPtr->mSize > 0)
    {
        Person_t *person = (Person_t *)BufferRemove(gBufferPtr, 0, PERSON_SIZE);
        // INFO_MSG("Buffer Remove...Removed @ index %d - %s | %d", 0, PersonStr( person ), gBufferPtr->mSize );
        fflush(stdout);

        if (PersonCmp(person, &gPersons[index++]))
        {
            FAIL_MSG("Buffer Remove...Failed @ index %d", index);
            res = false;
        }

        free(person);
    }

    if (gBufferPtr->mSize != 0)
    {
        res = false;
        FAIL_MSG("Buffer Remove...Not empty");
    }

    if (res)
    {
        PASS_MSG("Buffer Remove...Passed");
    }

    return res;
}
static bool BufferTestDestroy()
{
    bool res = true;

    INFO_MSG("Buffer Destroy...");

    if (gBufferPtr->mSize)
    {
        while (gBufferPtr->mSize > 0)
        {
            BufferRemove(gBufferPtr, 0, PERSON_SIZE);
        }
    }

    BufferDestroy(gBufferPtr);

    if (gBufferPtr->mData == NULL)
    {
        PASS_MSG("Buffer Destroy...Passed");
    }

    return res;
}

#endif // _BUFFERTESTER_H__
