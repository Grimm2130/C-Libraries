#if !defined(__LIST_H__)
#define __LIST_H__

#include <stdio.h>
#include <stdint.h>

/*===================================  List Node  ==================================*/

typedef struct ListNode ListNode_t;

struct ListNode
{
    size_t      mDataSize;
    ListNode_t *mLeft; 
    ListNode_t *mRight;
    void *mData;
};

ListNode_t *ListNodeCreate( void *data );
ListNode_t *ListNodeCreateCopyData( void *data, const size_t dataSize);
void ListNodeInit( ListNode_t * node, void *data );
void ListNodeInitCopyData( ListNode_t * node, void *data, const size_t dataSize );
void ListNodeConnectLeft( ListNode_t * node, ListNode_t *otherNode );
void ListNodeConnectRight( ListNode_t * node, ListNode_t *otherNode );
void ListNodeDetach( ListNode_t *node );
void ListNodeFree( ListNode_t *node );

/*===================================  List  ==================================*/

typedef struct List
{
    uint32_t mCount;
    ListNode_t * mHead;
    ListNode_t * mTail;
    int (*Cmp)( void* _a, void *_b );
} List_t;

List_t *ListCreate( int (*cmpFn)( void *a, void *b ) );
void ListInit( List_t* list, int (*cmpFn)( void *a, void *b ) );

void ListAppendData( List_t* list, void* data );
void ListAppendDataCopy( List_t* list, void* data, const size_t size );
void ListAppendNode( List_t* list, ListNode_t* node );

void ListPrependData( List_t* list, void* data );
void ListPrependDataCopy( List_t* list, void* data, const size_t size );
void ListPrependNode( List_t* list, ListNode_t* node );

void ListInsertData( List_t* list, void* data );
void ListInsertDataCopy( List_t* list, void* data, const size_t size );
void ListInsertNode( List_t* list, ListNode_t* node );

void *ListRemove( List_t* list, void *key );
ListNode_t *ListRemoveNode( List_t* list, void *key );
void ListRemoveThisNode( List_t *list, ListNode_t *node );

void *ListFind( List_t* list, void *key );
ListNode_t *ListFindNode( List_t* list, void *key );

void ListFree( List_t* list );

#define LIST_ITER_START( listPtr, nodePtr ) \
{                                           \
    (nodePtr) = (listPtr)->mHead;           \
    while( (nodePtr) )                      \
    {
        
        
#define LIST_ITER_END( nodePtr )    \
        nodePtr = nodePtr->mRight;  \
    }                               \
}

#define LIST_REV_ITER_START( listPtr, nodePtr ) \
{                                               \
    (nodePtr) = (listPtr)->mTail;               \
    while( (nodePtr) )                          \
    {
        
#define LIST_REV_ITER_END( nodePtr )    \
        nodePtr = nodePtr->mLeft;       \
    }                                   \
}


#endif // __LIST_H__
