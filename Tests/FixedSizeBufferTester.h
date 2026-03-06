#if !defined(_FIXED_SIZE_BUFFERTESTER_H__)
#define _FIXED_SIZE_BUFFERTESTER_H__

#include "FixedSizeBuffer.h"
#include "Utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>

static bool TestCreate();
static bool TestAppend();
static bool TestRemove();
static bool TestDestroy();
static bool TestGetter();
static bool TestSetter();
static bool TestPrepend();

static const int gFixedSizeBufferCapacity = PERSONS_COUNT;
FixedSizeBuffer_t *gFixedSizeBufferPtr = NULL;

bool RunTestsFixedSizeBuffer()
{
    bool res = false;

    if (TestCreate())
    {
        if (TestAppend())
        {
            if (TestGetter())
            {
                if (TestSetter())
                {
                    if (TestRemove())
                    {
                        if (TestPrepend())
                        {
                            if (TestRemove())
                            {
                                if (TestDestroy())
                                {
                                    gFixedSizeBufferPtr = NULL;
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

static bool TestCreate()
{
    bool res = false;

    INFO_MSG("FixedSizeBuffer Creation...");
    gFixedSizeBufferPtr = FixedSizeBufferCreate(PERSON_SIZE, gFixedSizeBufferCapacity);

    if (gFixedSizeBufferPtr)
    {
        if (gFixedSizeBufferPtr->mSize == 0)
        {
            if (gFixedSizeBufferPtr->mData)
            {
                if (gFixedSizeBufferPtr->mItemSize == PERSON_SIZE)
                {
                    if ((gFixedSizeBufferPtr->mCurrCapacity == gFixedSizeBufferCapacity / 100) || (gFixedSizeBufferPtr->mCurrCapacity == MIN_BUFFER_CAPACITY))
                    {
                        if (gFixedSizeBufferPtr->mCapacity == gFixedSizeBufferCapacity)
                        {
                            res = true;
                            INFO_MSG("FixedSizeBuffer Creation...Passed");
                        }
                        else
                        {
                            FAIL_MSG("FixedSizeBuffer Created with capacity %d, actual %d", gFixedSizeBufferCapacity, gFixedSizeBufferPtr->mCurrCapacity);
                        }
                    }
                    else
                    {
                        FAIL_MSG("FixedSizeBuffer Created with capacity %d, actual %d", gFixedSizeBufferCapacity, gFixedSizeBufferPtr->mCurrCapacity);
                    }
                }
                else
                {
                    FAIL_MSG("FixedSizeBuffer Created for invalid object type. Expected type of size %d, Actual %d", PERSON_SIZE, gFixedSizeBufferPtr->mItemSize);
                }
            }
            else
            {
                FAIL_MSG("FixedSizeBuffer Created without actual data space");
            }
        }
        else
        {
            FAIL_MSG("FixedSizeBuffer Created without empty buffer");
        }
    }
    else
    {
        FAIL_MSG("FixedSizeBuffer Creation Failed");
    }

    return res;
}

static bool TestAppend()
{
    bool res = true;

    uint32_t currSize = 0;
    uint32_t finalSize = PERSON_SIZE * PERSONS_COUNT;

    INFO_MSG("FixedSizeBuffer Append...");

    for (int i = 0; i < PERSONS_COUNT; i++)
    {
        FixedSizeBufferAppend(gFixedSizeBufferPtr, (void *)&gPersons[i], PERSON_SIZE);
        currSize += PERSON_SIZE;

        if (gFixedSizeBufferPtr->mSize != currSize)
        {
            FAIL_MSG("FixedSizeBuffer Append...Failed @ index %d", i);
            break;
        }
    }

    if (gFixedSizeBufferPtr->mSize == finalSize)
    {
        PASS_MSG("FixedSizeBuffer Append...Passed");
        res = true;
    }
    else
    {
        FAIL_MSG("FixedSizeBuffer Append...Failed");
    }

    return res;
}

static bool TestPrepend()
{
    uint32_t index;
    bool res = true;
    Person_t *person;

    INFO_MSG("FixedSizeBuffer Prepend...");

    for (int i = PERSONS_COUNT - 1; i >= 0; i--)
    {
        FixedSizeBufferPrepend(gFixedSizeBufferPtr, (void *)&gPersons[i], PERSON_SIZE);
        person = (Person_t *)gFixedSizeBufferPtr->mData;
        // INFO_MSG("Prepended From index %d - %s", i, PersonStr(person) );
    }

    for (int i = 0; i < 100; i++)
    {
        index = rand() % PERSONS_COUNT;
        person = (Person_t *)FixedSizeBufferGet(gFixedSizeBufferPtr, index, PERSON_SIZE);

        // INFO_MSG("Retrieved From index %d - %s", index, PersonStr(person) );

        if (PersonCmp(person, &gPersons[index]))
        {
            FAIL_MSG("FixedSizeBuffer Prepend...Failed @ index %d", index);
            res = false;
            break;
        }
    }

    PASS_MSG("FixedSizeBuffer Prepend...Done");

    return res;
}

static bool TestGetter()
{
    uint32_t index;
    uint32_t effAddr;

    bool res = true;

    INFO_MSG("FixedSizeBuffer Getter...");

    for (int i = 0; i < 100; i++)
    {
        index = rand() % PERSONS_COUNT;
        Person_t *person = (Person_t *)FixedSizeBufferGet(gFixedSizeBufferPtr, index, PERSON_SIZE);

        // INFO_MSG("Retrieved From index %d - %s", index, PersonStr(person) );

        if (PersonCmp(person, &gPersons[index]))
        {
            FAIL_MSG("FixedSizeBuffer Getter...Failed");
            res = false;
            break;
        }
    }

    PASS_MSG("FixedSizeBuffer Getter...Passed");

    return res;
}
static bool TestSetter()
{
    uint32_t index;

    INFO_MSG("FixedSizeBuffer Setter...");

    bool res = true;

    for (int i = 0; i < PERSONS_COUNT; i++)
    {
        FixedSizeBufferSet(gFixedSizeBufferPtr, i, (void *)&gPersons[i], PERSON_SIZE);
    }

    for (int i = 0; i < 100; i++)
    {
        index = rand() % PERSONS_COUNT;
        Person_t *person = (Person_t *)FixedSizeBufferGet(gFixedSizeBufferPtr, index, PERSON_SIZE);

        // INFO_MSG("Retrieved From index %d - %s", index, PersonStr(person) );

        if (PersonCmp(person, &gPersons[index]))
        {
            FAIL_MSG("FixedSizeBuffer Setter...Failed @ index %d", index);
            res = false;
            break;
        }
    }

    if (res)
    {
        PASS_MSG("FixedSizeBuffer Setter...Passed");
    }

    return res;
}
static bool TestRemove()
{
    bool res = true;
    int index = 0;

    INFO_MSG("FixedSizeBuffer Remove....");

    while (gFixedSizeBufferPtr->mSize > 0)
    {
        Person_t *person = (Person_t *)FixedSizeBufferRemove(gFixedSizeBufferPtr, 0, PERSON_SIZE);
        // INFO_MSG("FixedSizeBuffer Remove...Removed @ index %d - %s | %d", 0, PersonStr( person ), gFixedSizeBufferPtr->mSize );
        fflush(stdout);

        if (PersonCmp(person, &gPersons[index++]))
        {
            FAIL_MSG("FixedSizeBuffer Remove...Failed @ index %d", index);
            res = false;
        }

        free(person);
    }

    if (gFixedSizeBufferPtr->mSize != 0)
    {
        res = false;
        FAIL_MSG("FixedSizeBuffer Remove...Not empty");
    }

    if (res)
    {
        PASS_MSG("FixedSizeBuffer Remove...Passed");
    }

    return res;
}
static bool TestDestroy()
{
    bool res = true;

    INFO_MSG("FixedSizeBuffer Destroy...");

    if (gFixedSizeBufferPtr->mSize)
    {
        while (gFixedSizeBufferPtr->mSize > 0)
        {
            FixedSizeBufferRemove(gFixedSizeBufferPtr, 0, PERSON_SIZE);
        }
    }

    FixedSizeBufferDestroy(gFixedSizeBufferPtr);

    if (gFixedSizeBufferPtr->mData == NULL)
    {
        PASS_MSG("FixedSizeBuffer Destroy...Passed");
    }

    return res;
}

#endif // _FIXED_SIZE_BUFFERTESTER_H__
