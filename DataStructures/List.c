#include "List.h"
#include "Utils.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>




ListNode_t *ListNodeCreateCopyData( void *data, const size_t dataSize )
{
    ListNode_t *node = (ListNode_t*)calloc( 1, sizeof(ListNode_t));
    ListNodeInitCopyData( node, data, dataSize );
    return node;
}

ListNode_t *ListNodeCreate( void *data )
{
    ListNode_t *node = (ListNode_t*)calloc( 1, sizeof(ListNode_t));
    ListNodeInit( node, data );
    return node;
}


void ListNodeInit( ListNode_t * node, void *data )
{
    node->mDataSize = -1;
    node->mLeft = node->mRight = NULL;
    node->mData = data;
}

void ListNodeInitCopyData( ListNode_t * node, void *data, const size_t dataSize )
{
    node->mLeft = node->mRight = NULL;
    node->mDataSize = dataSize;
    node->mData = calloc( dataSize, sizeof(char) );
    Memncpy( node->mData, data, dataSize, dataSize );
}


void ListNodeConnectLeft( ListNode_t * node, ListNode_t *otherNode )
{
    // Store current left node 
    ListNode_t *left = node->mLeft;
    
    node->mLeft = otherNode;
    otherNode->mRight = node;
    otherNode->mLeft = left;

    if( left )
    {
        left->mRight = otherNode;
    }
}

void ListNodeConnectRight( ListNode_t * node, ListNode_t *otherNode )
{
     // Store current left node 
    ListNode_t *right = node->mRight;
    
    node->mRight = otherNode;
    otherNode->mLeft = node;
    otherNode->mRight = right;

    if( right )
    {
        right->mLeft = otherNode;
    }
}


void ListNodeDetach( ListNode_t * node )
{
    ListNode_t *left = node->mLeft;
    ListNode_t *right = node->mRight;

    node->mLeft = node->mRight = NULL;

    if( left ) left->mRight = right;
    if( right ) right->mLeft = left;
}

void ListNodeFree( ListNode_t * node )
{
    if( node->mLeft || node->mRight )
    {
        ListNodeDetach(node);
    }
    
    if( node->mDataSize != -1 )
    {
        free( node->mData );
    }
    
    node->mData = NULL;
}

/*
*	================================== List ==================================
*/

List_t *ListCreate( int (*cmpFn)( void *a, void *b ) )
{
    List_t *list = calloc( 1, sizeof(List_t) );
    ListInit( list, cmpFn );
    return list;
}

void ListInit( List_t* list, int (*cmpFn)( void *a, void *b ) )
{
    list->mCount = 0;
    list->mHead = list->mTail = NULL;
    list->Cmp = cmpFn;
}

void ListAppendData( List_t* list, void* data )
{
    ListNode_t *node = ListNodeCreate( data );
    ListAppendNode( list, node );
}

void ListAppendDataCopy( List_t* list, void* data, const size_t size )
{
    ListNode_t *node = ListNodeCreateCopyData( data, size );
    ListAppendNode( list, node );
}

void ListAppendNode( List_t* list, ListNode_t* node )
{
    if( list->mTail == NULL )
    {
        assert( list->mHead == NULL );
        list->mTail = list->mHead = node;
    }
    else
    {
        ListNodeConnectRight( list->mTail, node );
        list->mTail = node;
    }

    list->mCount++;
}

void ListPrependData( List_t* list, void* data )
{
    ListNode_t *node = ListNodeCreate( data );
    ListPrependNode( list, node );
}

void ListPrependDataCopy( List_t* list, void* data, const size_t size )
{
    ListNode_t *node = ListNodeCreateCopyData( data, size );
    ListPrependNode( list, node );
}

void ListPrependNode( List_t* list, ListNode_t* node )
{
    if( list->mHead == NULL )
    {
        assert( list->mTail == NULL );
        list->mHead = list->mTail = node;
    }
    else
    {
        ListNodeConnectLeft( list->mHead, node );
        list->mHead = node;
    }

    list->mCount++;
}

void ListInsertData( List_t* list, void* data )
{
    ListNode_t * node = ListNodeCreate( data );
    ListInsertNode( list, node );
}


void ListInsertDataCopy( List_t* list, void* data, const size_t size )
{
    ListNode_t * node = ListNodeCreateCopyData( data, size );
    ListInsertNode( list, node );
}

void ListInsertNode( List_t* list, ListNode_t* node )
{
    ListNode_t *curr;
    char inserted = 0;

    LIST_ITER_START( list, curr )
    {
        if( list->Cmp( curr->mData, node->mData) > 0 )
        {
            ListNodeConnectRight( curr, node );
            list->mCount++;
            inserted = 1;
            break;
        }
    }
    LIST_ITER_END( curr )

    if( inserted == 0 )
    {
        ListAppendNode( list, node );
    }
}


void *ListRemove( List_t* list, void *key )
{
    ListNode_t *curr = ListRemoveNode( list, key );
    return curr ? curr->mData : NULL;
}

ListNode_t *ListRemoveNode( List_t* list, void *key )
{
    ListNode_t *curr = ListFindNode( list, key );

    if( curr )
    {
        // update head node if necessary
        if( curr == list->mHead )
        {
            list->mHead = list->mHead->mRight;
        }
        
        if( curr == list->mTail )
        {
            list->mTail = list->mTail->mLeft;
        }

        ListNodeDetach( curr );

        list->mCount--;
    }

    return curr;
}


void *ListFind( List_t* list, void *key )
{
    ListNode_t *curr = ListFindNode( list, key );

    return curr ? curr->mData : NULL;
}

ListNode_t *ListFindNode( List_t* list, void* key )
{
    ListNode_t *curr;
    
    LIST_ITER_START( list, curr )
    {
        if( list->Cmp( curr->mData, key ) == 0 )
        {
            break;
        }
    }
    LIST_ITER_END( curr )

    return curr;
}

void ListFree( List_t* list )
{
    ListNode_t *curr;
    ListNode_t *prev = NULL;
    
    LIST_ITER_START( list, curr )
    {
        if( prev )
        {
            ListRemoveThisNode( list, prev );
            ListNodeFree( prev );
        }
        prev = curr;
    }
    LIST_ITER_END( curr )

    if( prev )
    {
        ListRemoveThisNode( list, prev );
        ListNodeFree( prev );
    }

    assert( list->mCount == 0 );
    assert( list->mHead == NULL );
    assert( list->mTail == NULL );

    list->mHead = list->mTail = NULL;
}

void ListRemoveThisNode( List_t *list, ListNode_t *node )
{
    if( node )
    {
        // update head node if necessary
        if( node == list->mHead )
        {
            list->mHead = list->mHead->mRight;
        }
        
        if( node == list->mTail )
        {
            list->mTail = list->mTail->mLeft;
        }

        ListNodeDetach( node );

        list->mCount--;
    }
}