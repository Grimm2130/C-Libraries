#if !defined(__STACK_TESTER_H__)
#define __STACK_TESTER_H__

#include "Stack.h"
#include "Person.h"
#include "TestUtils.h"
#include <stdint.h>
#include <stdbool.h>

static Stack_t * stack = NULL;

static bool TestStackCreate();
static bool TestStackPop();
static bool TestStackPush();
static bool TestStackIsEmpty();
static bool TestStackIsFull();
static bool TestStackRelease();

bool RunTestsStackTester()
{
    bool res = false;

    INFO_MSG("Testing Stack...");

    if( TestStackCreate() )
    {
        if( TestStackIsEmpty() )
        {
            if( TestStackPush() )
            {
                if( TestStackIsFull() )
                {
                    if( TestStackPop() )
                    {
                        if( TestStackRelease() )
                        {
                            res = true;
                            PASS_MSG("Testing Stack...Passed");
                        }
                        else
                        {
                            FAIL_MSG("Testing Stack....Failed on Release");
                        }
                    }
                    else
                    {
                        FAIL_MSG("Testing Stack....Failed on Pop");
                    }
                }
                else
                {
                    FAIL_MSG("Testing Stack....Failed on Full");
                }
            }
            else
            {
                FAIL_MSG("Testing Stack....Failed on Push");
            }
        }
        else
        {
            FAIL_MSG("Testing Stack....Failed on Empty");
        }
    }
    else
    {
        FAIL_MSG("Testing Stack....Failed on Create");
    }

    return res;
}

static bool TestStackCreate()
{
    bool res = false;

    INFO_MSG("Testing Stack Create....");

    if( (stack = StackCreate( PERSON_SIZE, PERSONS_COUNT )) )
    {
        if( stack->mCount == 0 )
        {
            if( stack->mBuffer )
            {
                if( stack->mBuffer->mItemSize == PERSON_SIZE )
                {
                    res = true;
                    PASS_MSG("Testing Stack Create....Passed");
                }
                else
                {
                    FAIL_MSG("Testing Stack Create....Failed. ItemSize mismatch %d != %d", stack->mBuffer->mItemSize, PERSON_SIZE );
                }
            }
            else
            {
                FAIL_MSG("Testing Stack Create....Failed Buffer not initialized.");
            }
        }
        else
        {
            FAIL_MSG("Testing Stack Create....Failed. Intial Count invalid (%d)", stack->mCount );
        }
    }
    else
    {
        FAIL_MSG("Testing Stack Create....Failed. Stack Allocation Failed");
    }

    return res;
}

static bool TestStackPop()
{
    bool res = true;

    Person_t *person, *top;

    INFO_MSG("Testing Stack Pop....");

    for( int i = PERSONS_COUNT-1; i >= 0; i-- )
    {
        person = (Person_t *)&gPersons[i];
        top = (Person_t*)StackTop(stack);

        if( PersonCmp( top, person) )
        {
            FAIL_MSG("Test Stack Pop...Failed on Pop Top{%s} != Curr{%s}", PersonStr(top), PersonStr(person) );
            res = false;
            break;
        }
        
        // INFO_MSG("Testing Stack Pop...Removing %d, %s", i, PersonStr( top ) );
        
        if( StackPop( stack ) == false )
        {
            FAIL_MSG("Test Stack Pop...Failed on pop %s", PersonStr(person) );
            res = false;
            break;
        }

    }

    if( res )
    {
        PASS_MSG("Test Stack Pop...Passed");
    }

    return res;
}

static bool TestStackPush()
{
    bool res = true;

    Person_t *person, *top;

    INFO_MSG("Testing Stack Push....");

    for( size_t i = 0; i < PERSONS_COUNT; i++ )
    {
        person = (Person_t *)&gPersons[i];

        if( StackPush( stack, person, PERSON_SIZE ) == false )
        {
            FAIL_MSG("Test Stack Push...Failed on push %s", PersonStr(person) );
            res = false;
            break;
        }

        top = (Person_t*)StackTop(stack);

        if( PersonCmp( top, person) )
        {
            FAIL_MSG("Test Stack Push...Failed on push Top{%s} != Curr{%s}", PersonStr(top), PersonStr(person) );
            res = false;
            break;
        }
    }

    if( stack->mCount != PERSONS_COUNT )
    {
        res = false;
        FAIL_MSG("Test Stack Push...Failed Person count mismatch %d != %d", stack->mCount, PERSONS_COUNT );
    }

    if( res )
    {
        PASS_MSG("Test Stack Push...Passed");
    }

    return res;
}

static bool TestStackIsEmpty()
{
    bool res = false;

    INFO_MSG("Testing Stack IsEmpty....");
    
    if( StackIsEmpty( stack ) == true )
    {
        res = true;
        PASS_MSG("Testing Stack IsEmpty....Passed");
    }
    else
    {
        FAIL_MSG("Testing Stack IsEmpty....Failed");
    }

    return res;
}

static bool TestStackIsFull()
{
    bool res = false;

    INFO_MSG("Testing Stack IsFull....");
    
    if( StackIsFull( stack ) == true )
    {
        res = true;
        PASS_MSG("Testing Stack IsFull....Passed");
    }
    else
    {
        FAIL_MSG("Testing Stack IsFull....Failed");
    }

    return res;
}

static bool TestStackRelease()
{
    bool res = false;

    INFO_MSG("Testing Stack Release....");
    
    if( stack )
    {
        StackRelease(stack);

        if( stack->mCount == 0 )
        {
            if( stack->mBuffer == NULL )
            {
                res = true;
                PASS_MSG("Testing Stack Release...Passed");
            }
            else
            {
                ERROR_MSG("Testing Stack Release...Failed, Buffer not deallocated");
            }
        }
        else
        {
            ERROR_MSG("Testing Stack Release...Failed, Item count not zero");
        }
    }

    return res;
}


#endif // __STACK_TESTER_H__
