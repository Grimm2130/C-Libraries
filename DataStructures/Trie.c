#include "Trie.h"
#include <stdio.h>
#include <stdlib.h>

static inline void TrieRemoveInner( Trie_t* trie, const char * key );
static inline bool TrieContainsOthers( Trie_t* trie, const char c );


Trie_t *TrieCreate()
{
    Trie_t *trie = (Trie_t*) calloc(1, sizeof(Trie_t));
    TrieInit( trie );
    return trie;
}

void TrieInit( Trie_t* trie )
{
    trie->mCount = 0;
    trie->mData = NULL;
    for( int i = 0; i < TRIE_NODE_SIZE; i++ )
    {
        trie->mNodes[i] = NULL;
    }
}

void TrieInsert( Trie_t* trie, const char* key, void *data )
{
    char c;
    int i = 0;
    Trie_t *next;
    Trie_t *iter = trie;
    
    while( (c = key[i++]) != '\0' )
    {
        if( iter->mNodes[c] == NULL )
        {
            iter->mNodes[c] = TrieCreate();
            iter->mCount++;
        }
        next = iter->mNodes[c]; 
        iter = next;
    }

    // Set the data
    iter->mData = data;

}

bool TrieContains( Trie_t* trie, const char* key )
{
    char c;
    int i = 0;
    Trie_t *next;
    Trie_t *iter = trie;
    
    while( (c = key[i++]) != '\0' )
    {
        iter = iter->mNodes[c]; 
        if( iter == NULL )
        {
            break;
        }
    }

    if( iter ) return (iter->mData != NULL);

    return false;
}

Trie_t *TrieFind( Trie_t* trie, const char* key )
{
    char c;
    int i = 0;
    Trie_t *next;
    Trie_t *iter = trie;
    
    while( (c = key[i++]) != '\0' )
    {
        iter = iter->mNodes[c]; 
        if( iter == NULL )
        {
            break;
        }
    }

    return iter;
}

void *TrieFindData( Trie_t* trie, const char* key )
{
    Trie_t *iter = TrieFind( trie, key );
    return iter ? iter->mData : NULL;
}

void TrieRemove( Trie_t* trie, const char* key )
{
    int i = 0;
    Trie_t *next;
    Trie_t *iter = trie;

    if( TrieContains( trie, key ) )
    {
        TrieRemoveInner( trie, key );
    }
}

/// @brief Recursive removal of trie elements
/// @param trie 
/// @param key 
static inline void TrieRemoveInner( Trie_t* trie, const char * key )
{
    // if( trie )
    // {
    //     char c = (*key);
    //     if( c != '\0' ) TrieRemoveInner( trie->mNodes[c], key + 1 );
       
    //     // release
    //     if( TrieContainsOthers(trie, c) == false )
    //     {
    //         trie->mData = NULL;
    //         free(trie );
    //     }
    // }
}

/// @brief Trie contains others
/// @param trie 
/// @param c 
/// @return 
static inline bool TrieContainsOthers( Trie_t* trie, const char c )
{
    bool res = false;

    for( int i = 0; i < TRIE_NODE_SIZE; i++ )
    {
        if( ((char)i != c) && trie->mNodes[i] )
        {
            res = true;
            break;
        }
    }

    return res;
}