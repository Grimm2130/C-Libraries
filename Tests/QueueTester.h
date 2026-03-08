#if !defined(__QUEUE_TESTER_H__)
#define __QUEUE_TESTER_H__

#include "Queue.h"
#include "Person.h"
#include "TestUtils.h"
#include <stdint.h>
#include <stdbool.h>

static Queue_t *queue = NULL;

static bool TestQueueCreate();
static bool TestQueueRelease();
static bool TestQueuePop();
static bool TestQueuePush();
static bool TestQueueIsEmpty();
static bool TestQueueIsFull();

bool RunTestsQueueTester()
{
    bool res = false;

    INFO_MSG("Testing Queue...");

    if( TestQueueCreate() )
    {
        if( TestQueueIsEmpty() )
        {
            if( TestQueuePush() )
            {
                if( TestQueueIsFull() )
                {
                    if( TestQueuePop() )
                    {
                        if( TestQueueRelease() )
                        {
                            res = true;
                            PASS_MSG("Testing Queue...Passed");
                        }
                        else
                        {
                            FAIL_MSG("Testing Queue...Failed on Release");
                        }
                    }
                    else
                    {
                        FAIL_MSG("Testing Queue...Failed on Pop");
                    }
                }
                else
                {
                    FAIL_MSG("Testing Queue...Failed on IsFull");
                }
            }
            else
            {
                FAIL_MSG("Testing Queue...Failed on Push");
            }
        }
        else
        {
            FAIL_MSG("Testing Queue...Failed on IsEmpty");
        }
    }
    else
    {
        FAIL_MSG("Testing Queue...Failed on Create");
    }

    return res;
}

static bool TestQueueCreate()
{
    bool res = false;

    queue = QueueCreate( PERSON_SIZE, PERSONS_COUNT );

    if( queue )
    {
        if( queue->mCount == 0 )
        {
            if( queue->mBuffer )
            {
                if( (queue->mBuffer->mItemSize) == PERSON_SIZE )
                {
                    res = true;
                    PASS_MSG("Testing Queue Create...Passed");
                }
                else
                {
                    FAIL_MSG("Testing Queue Create...Failed on itemSize mismatch");
                }
            }
            else
            {
                FAIL_MSG("Testing Queue Create...Failed on Buffer allocation");
            }
        }
        else
        {
            FAIL_MSG("Testing Queue Create...Failed on item count initialization");
        }
    }
    else
    {
        FAIL_MSG("Testing Queue Create...Failed on queue allocation");
    }

    return res;
}

static bool TestQueueRelease()
{
    bool res = false;

    if( queue )
    {
        QueueRelease( queue );

        if( queue->mCount == 0 )
        {
            if( queue->mBuffer == NULL )
            {
                res = true;
                PASS_MSG("Testing Queue Release...Passed");
            }
            else
            {
                FAIL_MSG("Testing Queue Release...Failed. Queue Buffer not nulled");
            }
        }
        else
        {
            FAIL_MSG("Testing Queue Release...Failed. Queue not empty");
        }
    }
    else
    {
        FAIL_MSG("Testing Queue Release...Failed. Queue is null");
    }

    return res;
}

static bool TestQueuePop()
{
    int cmp;
    Person_t *person, *front;
    bool res = false;

    INFO_MSG("Testing Queue Push...");

    for( int i = 0; i < PERSONS_COUNT; i++ )
    {
        person = (Person_t *)(&gPersons[i]);
        front = (Person_t *)QueueFront( queue );

        if( front )
        {
            if( (cmp = PersonCmp( person, front )) )
            {
                char p1[0x100];
                Strncpy( p1, PersonStr( front ), 0x100, 0x100 );

                FAIL_MSG("Testing Queue Pop...Failed. [%d] %d Front{%s} != Expected{%s}", i, cmp, p1, PersonStr( person ) );
                break;
            }

            if( QueuePop( queue ) == false )
            {
                FAIL_MSG("Testing Queue Pop...Failed on pop");
                break;
            }
        }
        else
        {
            FAIL_MSG("Testing Queue Pop...Failed. Unable to retrieve front element");
            break;
        }
    }
    
    if( queue->mCount == 0 )
    {
        res = true;
        PASS_MSG("Testing Queue Pop...Passed");
    }
    else
    {
        FAIL_MSG("Testing Queue Pop...Failed not all items popped");
    }

    return res;
}

static bool TestQueuePush()
{
    Person_t *person;
    bool res = false;

    INFO_MSG("Testing Queue Push...");

    for( int i = 0; i < PERSONS_COUNT; i++ )
    {
        person = (Person_t *)(&(gPersons[i]));
        if(QueuePush( queue, person, PERSON_SIZE ) == false)
        {
            FAIL_MSG("Testing Queue Push...Failed push operation failed");
            break;
        }
    }
    
    if( queue->mCount == PERSONS_COUNT )
    {
        res = true;
        PASS_MSG("Testing Queue Push...Passed");
    }
    else
    {
        FAIL_MSG("Testing Queue Push...Failed not all items pushed");
    }

    return res;
}

static bool TestQueueIsEmpty()
{
    bool res = false;

    INFO_MSG("Testing Queue IsEmpty...");

    if( queue )
    {
        if( QueueIsEmpty( queue ) )
        {
            res = true;
            PASS_MSG("Testing Queue IsEmpty...Passed");
        }
        else
        {
            FAIL_MSG("Testing Queue IsEmpty...Failed on queue allocation");
        }
    }
    else
    {
        FAIL_MSG("Testing Queue IsEmpty...Failed on queue allocation");
    }

    return res;
}

static bool TestQueueIsFull()
{
    bool res = false;

    INFO_MSG("Testing Queue IsFull...");

    if( queue )
    {
        if( QueueIsFull( queue ) )
        {
            res = true;
            PASS_MSG("Testing Queue IsFull...Passed");
        }
        else
        {
            FAIL_MSG("Testing Queue IsFull...Failed on queue allocation");
        }
    }
    else
    {
        FAIL_MSG("Testing Queue IsFull...Failed on queue allocation");
    }

    return res;
}



#endif // __QUEUE_TESTER_H__
