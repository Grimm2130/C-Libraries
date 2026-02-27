#if !defined(__TRIE_H__)
#define __TRIE_H__

#include <stdint.h>
#include <stdbool.h>

#define TRIE_NODE_SIZE  128U

typedef struct Trie Trie_t;

struct Trie
{
    uint32_t mCount;
    void *mData;                    // Trie data object (only available at leaf)
    Trie_t* mNodes[ TRIE_NODE_SIZE ]; // Pointer to other trie nodes
};

Trie_t *TrieCreate();
void TrieInit( Trie_t* trie );
void TrieInsert( Trie_t* trie, const char* key, void *data );
bool TrieContains( Trie_t* trie, const char* key );
Trie_t *TrieFind( Trie_t* trie, const char* key );
void *TrieFindData( Trie_t* trie, const char* key );
void TrieRemove( Trie_t* trie, const char* key );

#endif // __TRIE_H__
