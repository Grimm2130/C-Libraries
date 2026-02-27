#if !defined(__LIST_TESTER_H__)
#define __LIST_TESTER_H__

#include <stdbool.h>
#include "List.h"
#include "TestUtils.h"
#include "Person.h"

#define PERSON_LEFT     1
#define PERSON_RIGHT    2

List_t      *gList;
ListNode_t  *gListNode;
ListNode_t  *gListNodeLeft;
ListNode_t  *gListNodeRight;

static const Person_t *gPersonLeft= &(gPersons[PERSON_LEFT]);
static const Person_t *gPersonRight = &(gPersons[PERSON_RIGHT]);
static const Person_t *gDefaultPerson = &(gPersons[0]);

static int PersonCmpWrapper( void * a, void *b );

static bool TestListNodeCreation();
static bool TestListNodeCreationWithCopy();
static bool TestListNodeConnectLeft();
static bool TestListNodeConnectRight();
static bool TestListNodeDetachFree();
static bool TestListNodeDetachFreeOnNode( ListNode_t *node );
static bool TestListNode();


static bool TestListCreate();
static bool TestListAppend();
static bool TestListPrepend();
static bool TestListInsert();
static bool TestListAppend_Prepend_Insert();
static bool TestListFind();
static bool TestListRemove();
static bool TestListFree();
static bool TestList();

bool RunTestsLists();

static int PersonCmpWrapper( void * a, void *b )
{
    Person_t *p1 = (Person_t *)a;
    Person_t *p2 = (Person_t *)b;
    return PersonCmp( p1, p2 );
}


bool RunTestsLists()
{
    bool res = false;

    INFO_MSG("Running Tests()...");

    if( TestListNode() )
    {
        if( TestList() )
        {
            PASS_MSG("Running Tests()...Passed");
            res = true;
        }
        else
        {
            FAIL_MSG("Running Tests()...Failed on List");
        }
    }
    else
    {
        FAIL_MSG("Running Tests()...Failed on ListNode");
    }

    return res;
}

static bool TestListNode()
{
    bool res = false;

    INFO_MSG("TestListNode()...");
    
    if( TestListNodeCreation() )
    {
        if( TestListNodeConnectLeft() )
        {
            if( TestListNodeConnectRight() )
            {
                if( TestListNodeDetachFree() )
                {
                    if( TestListNodeCreationWithCopy() )
                    {
                        if( TestListNodeConnectLeft() )
                        {
                            if( TestListNodeConnectRight() )
                            {
                                if( TestListNodeDetachFree() )
                                {
                                    res = true;
                                    PASS_MSG("TestListNode()...Passed");
                                }
                                else
                                {
                                    FAIL_MSG("TestListNode()...Failed on Detach");
                                }
                            }
                            else
                            {
                                FAIL_MSG("TestListNode()...Failed on Connect Right(copy)");
                            }
                        }
                        else
                        {
                            FAIL_MSG("TestListNode()...Failed on Connect Left(copy)");
                        }
                    }
                    else
                    {
                        FAIL_MSG("TestListNode()...Failed on Create(copy)");
                    }
                }
                else
                {
                    FAIL_MSG("TestListNode()...Failed on Detach");
                }
            }
            else
            {
                FAIL_MSG("TestListNode()...Failed on Connect Right");
            }
        }
        else
        {
            FAIL_MSG("TestListNode()...Failed on Connect Left");
        }
    }
    else
    {
        FAIL_MSG("TestListNode()...Failed on Create");
    }

    return res;
}

static bool TestListNodeCreation()
{
    Person_t * personData;
    bool res = false;

    INFO_MSG("TestListNodeCreation()...");

    gListNode = ListNodeCreateCopyData( (void*)gDefaultPerson, PERSON_SIZE );

    if( gListNode )
    {
        personData = (Person_t*)gListNode->mData;

        if( PersonCmp( personData, gDefaultPerson ) == 0 )
        {
            PASS_MSG("TestListNodeCreation()...Passed");
            res = true;
        }
        else
        {
            FAIL_MSG("TestListNodeCreation()...Failed Compare");
            INFO_MSG("TestListNodeCreation()...{%s} != %s", PersonStr( personData ), PersonStr( gDefaultPerson ) );
        }
    }
    else
    {
        FAIL_MSG("TestListNodeCreation()...Failed");
    }
    return res;
}

static bool TestListNodeCreationWithCopy()
{
    Person_t * personData;
    bool res = false;

    INFO_MSG("TestListNodeCreationWithCopy()...");

    gListNode = ListNodeCreateCopyData( (void*)gDefaultPerson, PERSON_SIZE );

    if( gListNode )
    {
        personData = (Person_t*)gListNode->mData;

        if( personData != gDefaultPerson )
        {
            if( PersonCmp( personData, gDefaultPerson ) == 0 )
            {
                PASS_MSG("TestListNodeCreationWithCopy()...Passed");
                res = true;
            }
            else
            {
                FAIL_MSG("TestListNodeCreationWithCopy()...Failed Compare");
                INFO_MSG("TestListNodeCreationWithCopy()...{%s} != %s", PersonStr( personData ), PersonStr( gDefaultPerson ) );
            }
        }
        else
        {
            FAIL_MSG("TestListNodeCreationWithCopy()...Failed Reference the same object!");
        }
    }
    else
    {
        FAIL_MSG("TestListNodeCreationWithCopy()...Failed");
    }

    return res;
}

static bool TestListNodeConnectLeft()
{
    Person_t * personData;

    bool res = false;
    
    INFO_MSG("TestListNodeConnectLeft()...");
    
    gListNodeLeft = ListNodeCreate( (void *)gPersonLeft );

    if( gListNodeLeft )
    {
        personData = (Person_t*)gListNodeLeft->mData;
        if( PersonCmp( personData, gPersonLeft ) == 0 )
        {
            PASS_MSG("TestListNodeConnectLeft()...Passed");
            res = true;
        }
        else
        {
            FAIL_MSG("TestListNodeConnectLeft()...Failed Compare");
            INFO_MSG("TestListNodeConnectLeft()...{%s} != %s", PersonStr( personData ), PersonStr( gPersonLeft ) );
        }
    }
    else
    {
        INFO_MSG("TestListNodeConnectLeft()...Failed");
    }

    return res;
}

static bool TestListNodeConnectRight()
{
    Person_t * personData;
    
    bool res = false;
    
    INFO_MSG("TestListNodeConnectRight()...");
    
    gListNodeRight = ListNodeCreate( (void *)gPersonRight );

    if( gListNodeRight )
    {
        personData = (Person_t*)gListNodeRight->mData;
        if( PersonCmp( personData, gPersonRight ) == 0 )
        {
            PASS_MSG("TestListNodeConnectRight()...Passed");
            res = true;
        }
        else
        {
            FAIL_MSG("TestListNodeConnectRight()...Failed Compare");
            INFO_MSG("TestListNodeConnectRight()...{%s} != %s", PersonStr( personData ), PersonStr( gPersonRight ) );
        }
    }
    else
    {
        FAIL_MSG("TestListNodeConnectRight()...Failed on Create");
    }

    return res;
}

static bool TestListNodeDetachFree()
{
    bool res = false;

    INFO_MSG("TestListNodeDetachFree()...");

    if( TestListNodeDetachFreeOnNode( gListNode ) )
    {
        if( TestListNodeDetachFreeOnNode( gListNodeLeft ) )
        {
            if( TestListNodeDetachFreeOnNode( gListNodeRight ) )
            {
                PASS_MSG("TestListNodeDetachFree()...Pass" );
                gListNode = gListNodeLeft = gListNodeRight = NULL;
                res = true;
            }
            else
            {
                FAIL_MSG("TestListNodeDetachFree()...Failed on Right" );
            }
        }
        else
        {
            FAIL_MSG("TestListNodeDetachFree()...Failed on Left" );
        }
    }
    else
    {
        FAIL_MSG("TestListNodeDetachFree()...Failed on Main" );
    }

    return res;
}

static bool TestListNodeDetachFreeOnNode( ListNode_t *node )
{
    bool res = false;

    INFO_MSG("TestListNodeDetachFreeOnNode()...");

    if( node )
    {
        ListNodeDetach( node );

        if( (node->mLeft == NULL) && (node->mRight == NULL) )
        {
            if( node->mData )
            {
                ListNodeFree( node );

                if( node->mData == NULL )
                {
                    PASS_MSG("TestListNodeDetachFreeOnNode()...Passed");
                    res = true;
                }
                else
                {
                    FAIL_MSG("TestListNodeDetachFreeOnNode()...Failed Data release" );
                }
            }
            else
            {
                FAIL_MSG("TestListNodeDetachFreeOnNode()...Failed Data corruption" );
            }
        }
        else
        {
            FAIL_MSG("TestListNodeDetachFreeOnNode()...Failed (%p, %p)", node->mLeft, node->mRight );
        }
    }
    else
    {
        FAIL_MSG( "TestListNodeDetachFreeOnNode()...Null Node" );
    }

    return res;
}

static bool TestListCreate()
{
    bool res = false;

    INFO_MSG("TestListCreate()...");

    gList = ListCreate( PersonCmpWrapper );

    if( gList )
    {
        if( gList->Cmp == PersonCmpWrapper )
        {
            if( gList->mHead == gList->mTail )
            {
                if( gList->mCount == 0 )
                {
                    res = true;
                    PASS_MSG("TestListCreate()...Passed");
                }
                else
                {
                    FAIL_MSG( "TestListCreate()...Failed Count != 0" );
                }
            }
            else
            {
                FAIL_MSG( "TestListCreate()...Failed Head != Tail" );
            }
        }
        else
        {
            FAIL_MSG( "TestListCreate()...Failed Cmp function invalid" );
        }
    }
    else
    {
        FAIL_MSG( "TestListCreate()...Failed Create" );
    }

    return res;
}


static bool TestListAppend()
{
    Person_t *person;

    bool res = false;
    int count = 0;

    INFO_MSG("TestListAppend()...");

    for( int i = 0; i < PERSONS_COUNT; i++ )
    {
        count++;
        person = (Person_t *)&(gPersons[i]);
        ListAppendDataCopy( gList, person, PERSON_SIZE );

        if( gList->mCount == count )
        {
            if( gList->mTail )
            {
                if( PersonCmpWrapper(gList->mTail->mData, (void *)person ) )
                {
                    FAIL_MSG("TestListAppend()...Failed %s != %s", PersonStr((Person_t *)gList->mTail->mData), PersonStr(person) );
                    break;
                }
            }
            else
            {
                FAIL_MSG("TestListAppend()...Failed Tail invalid" );
            }
        }
        else
        {
            FAIL_MSG("TestListAppend()...Failed Count Actual %d; Expected %d", gList->mCount, count );
        }
    }
    
    if( count == PERSONS_COUNT )
    {
        res = true;
        PASS_MSG("TestListAppend()...Passed");
    }
    
    return res;
}


static bool TestListPrepend()
{   
    Person_t *person;

    int count = 0;
    bool res = false;

    INFO_MSG("TestListPrepend()...");

    for( int i = PERSONS_COUNT - 1; i >= 0; i-- )
    {
        count++;
        person = (Person_t *)&(gPersons[i]);
        ListPrependDataCopy( gList, person, PERSON_SIZE );

        if( gList->mCount == count )
        {
            if( gList->mHead )
            {
                if( PersonCmpWrapper(gList->mHead->mData, (void *)person ) )
                {
                    FAIL_MSG("ListPrependData()...Failed %s != %s", PersonStr((Person_t *)gList->mHead->mData), PersonStr(person) );
                    break;
                }
            }
            else
            {
                FAIL_MSG("ListPrependData()...Failed Tail invalid" );
            }
        }
        else
        {
            FAIL_MSG("ListPrependData()...Failed Count Actual %d; Expected %d", gList->mCount, count );
        }
    }
    
    if( count == PERSONS_COUNT )
    {
        res = true;
        PASS_MSG("ListPrependData()...Passed");
    }
    
    return res;
}


static bool TestListInsert()
{
    Person_t *person;

    int count = 0;
    bool res = false;

    INFO_MSG("TestListInsert()...");

    for( int i = 0; i < PERSONS_COUNT; i++ )
    {
        count++;
        person = (Person_t *)&(gPersons[i]);
        ListInsertDataCopy( gList, person, PERSON_SIZE );

        if( gList->mCount != count )
        {
            FAIL_MSG("ListInsertData()...Failed Count Actual %d; Expected %d", gList->mCount, count );
            break;
        }
    }
    
    if( count == PERSONS_COUNT )
    {
        res = true;
        PASS_MSG("TestListInsert()...Passed");
    }
    
    return res;
}


static bool TestListAppend_Prepend_Insert()
{
    Person_t *person;

    bool res = false;
    int count = 0;

    for( int i = 0; (i + 2) < PERSONS_COUNT; i += 3 )
    {
        // Append
        {
            count++;
            person = (Person_t *)&(gPersons[i]);
            ListAppendData( gList, person );
            if( gList->mCount != count )
            {
                FAIL_MSG("ListAppendData()...Failed Count Actual %d; Expected %d", gList->mCount, count );
                break;
            }
        }
        {
            count++;
            person = (Person_t *)&(gPersons[i + 1]);
            ListInsertData( gList, person );
            if( gList->mCount != count )
            {
                FAIL_MSG("ListInsertData()...Failed Count Actual %d; Expected %d", gList->mCount, count );
                break;
            }
        }
        {
            count++;
            person = (Person_t *)&(gPersons[i + 2]);
            ListPrependData( gList, person );
            if( gList->mCount != count )
            {
                FAIL_MSG("ListPrependData()...Failed Count Actual %d; Expected %d", gList->mCount, count );
                break;
            }
        }
    }
    
    if( count == PERSONS_COUNT )
    {
        res = true;
        PASS_MSG("TestListInsert()...Passed");
    }
    
    return res;
}




static bool TestListFind()
{
    Person_t *searched;
    Person_t *found;
    bool res = true;

    INFO_MSG("TestListFind()...");

    for( int i = 0; i < PERSONS_COUNT; i++ )
    {
        searched = (Person_t *)&(gPersons[i]);

        found = (Person_t *) ListFind( gList, searched );

        if( found )
        {
            if( PersonCmpWrapper( (void*)searched, (void *)found ) )
            {
                res = false;
                FAIL_MSG("TestListFind()...Failed  [%d] %s != %s", i, PersonStr(searched), PersonStr(found) );
                break;
            }
            else
            {
                // INFO_MSG("TestListFind()...[%d] {%s == %s}", i, PersonStr(searched), PersonStr(found) );
            }
        }
        else
        {
            res = false;
            FAIL_MSG("TestListFind()...Failed No Entry match" );
            break;
        }
    }

    if( res )
    {
        PASS_MSG("TestListFind()...Passed");
    }
    
    return res;

}


static bool TestListRemove()
{
    Person_t *searched;
    ListNode_t *foundNode;
    
    bool res = true;
    int count = PERSONS_COUNT;

    INFO_MSG("TestListRemove()...");

    for( int i = 0; i < PERSONS_COUNT; i++ )
    {
        count--;
        searched = (Person_t *)&(gPersons[i]);

        foundNode = ListRemoveNode( gList, searched );

        if( foundNode )
        {
            if( PersonCmpWrapper( (void*)searched, foundNode->mData ) == 0 )
            {
                // release the node
                ListNodeFree( foundNode );

                // verify the count of the elements in the list
                if( gList->mCount != count )
                {
                    res = false;
                    FAIL_MSG("TestListRemove()...Failed Actual %d; Expected %d", gList->mCount, count);
                    break;
                }
            }
            else
            {
                res = false;
                FAIL_MSG("TestListRemove()...Failed  [%d] %s != %s", i, PersonStr(searched), PersonStr((Person_t *)foundNode->mData) );
                break;
            }
        }
        else
        {
            res = false;
            FAIL_MSG("TestListRemove()...Failed No Entry match" );
            break;
        }
    }

    if( count != 0 )
    {
        FAIL_MSG("TestListRemove()...Failed Final-Actual %d; Final-Expected %d", gList->mCount, count);
        res = false;
    }

    if( res )
    {
        PASS_MSG("TestListRemove()...Passed");
    }
    
    return res;
}


static bool TestListFree()
{
    bool res = false;

    INFO_MSG("TestListFree()...");

    ListFree( gList );

    if( gList->mCount == 0 )
    {
        if( !(gList->mHead || gList->mTail) )
        {
            res = true;
            PASS_MSG("TestListFree()...Passed");
        }
        else
        {
            FAIL_MSG("TestListFree()...Failed Head | Tail dereference");
        }
    }
    else
    {
        FAIL_MSG("TestListFree()...Failed Count");
    }
    
    return res;
}



static bool TestList()
{
    bool res = false;

    INFO_MSG("TestList()...");

    if( TestListCreate() )
    {
        if( TestListAppend() )
        {
            if( TestListFind() )
            {
                if(TestListRemove() )
                {
                    if( TestListPrepend() )
                    {
                        if( TestListFind() )
                        {
                            if( TestListRemove() )
                            {
                                if( TestListInsert() )
                                {
                                    if( TestListFind() )
                                    {
                                        if( TestListRemove() )
                                        {
                                            if( TestListAppend_Prepend_Insert() )
                                            {
                                                if( TestListFind() )
                                                {
                                                    if( TestListRemove() )
                                                    {
                                                        if( TestListFree() )
                                                        {
                                                            res = true;
                                                            PASS_MSG("TestList()...Passed");
                                                        }
                                                        else
                                                        {
                                                            FAIL_MSG("TestList()...Failed on Free(3)");
                                                        }
                                                    }
                                                    else
                                                    {
                                                        FAIL_MSG("TestList()...Failed on Remove(3)");
                                                    }
                                                }
                                                else
                                                {
                                                    FAIL_MSG("TestList()...Failed on Find(3)");
                                                }
                                            }
                                            else
                                            {
                                                FAIL_MSG("TestList()...Failed on Append_Prepend_Insert");
                                            }
                                        }
                                        else
                                        {
                                            FAIL_MSG("TestList()...Failed on Remove(2)");
                                        }
                                    }
                                    else
                                    {
                                        FAIL_MSG("TestList()...Failed on Find(2)");
                                    }
                                }
                                else
                                {
                                    FAIL_MSG("TestList()...Failed on Insert");
                                }
                            }
                            else
                            {
                                FAIL_MSG("TestList()...Failed on Remove(1)");
                            }
                        }
                        else
                        {
                            FAIL_MSG("TestList()...Failed on Find(1)");
                        }
                    }
                    else
                    {
                        FAIL_MSG("TestList()...Failed on Prepend");
                    }
                }
                else
                {
                    FAIL_MSG("TestList()...Failed on Remove(0)");
                }
            }
            else
            {
                FAIL_MSG("TestList()...Failed on Find(0)");
                
            }
        }
        else
        {
            FAIL_MSG("TestList()...Failed on Append");
        }
    }
    else
    {
        FAIL_MSG("TestList()...Failed on Create");
    }

    return res;
}

#endif // __LIST_TESTER_H__
