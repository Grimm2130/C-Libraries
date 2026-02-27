#if !defined(__TRIE_TESTER_H__)
#define __TRIE_TESTER_H__

#include "Trie.h"
#include "TestUtils.h"
#include "Words.h"

#include <stdio.h>

static Trie_t * gTrie;

static bool TestTrieCreate();
static bool TestTrieInsert();
static bool TestTrieContains();
static bool TestTrieFind();
static bool TestTrieFindData();
static bool TestTrieRemove();

bool RunTestsTrie()
{
    bool res = false;

    INFO_MSG("Running Trie Test...");

    if (TestTrieCreate())
    {
        if (TestTrieInsert())
        {
            if (TestTrieContains())
            {
                if (TestTrieFind())
                {
                    if (TestTrieFindData())
                    {
                        if (TestTrieRemove())
                        {
                            res = true;
                            PASS_MSG("Running Trie Test...Passed");
                        }
                        else
                        {
                            FAIL_MSG("Running Trie Test...Failed on Remove");
                        }
                    }
                    else
                    {
                        FAIL_MSG("Running Trie Test...Failed on Find Data");
                    }
                }
                else
                {
                    FAIL_MSG("Running Trie Test...Failed on Find");
                }
            }
            else
            {
                FAIL_MSG("Running Trie Test...Failed on Contains");
            }
        }
        else
        {
            FAIL_MSG("Running Trie Test...Failed on Insert");
        }
    }
    else
    {
        FAIL_MSG("Running Trie Test...Failed on Create");
    }

    return res;
}

static bool TestTrieCreate()
{
    bool res = true;

    INFO_MSG("TestTrieCreate()...");
    
    gTrie = TrieCreate();

    if( gTrie )
    {
        res = true;
        PASS_MSG("TestTrieCreate()...Passed");
    }
    else
    {
        FAIL_MSG("TestTrieCreate()...Failed");
    }

    return res;
}

static bool TestTrieInsert()
{
    Word_t *word;
    bool res = true;

    INFO_MSG("TestTrieInsert()...");

    for( int i = 0; i < WORDS_COUNT; i++ )
    {
        word = (Word_t *)&(gWords[i]);
        TrieInsert( gTrie, word->word, (void *) word );
    }

    PASS_MSG("TestTrieInsert()...Passed");

    return res;
}

static bool TestTrieContains()
{
    Word_t *expected;
    
    INFO_MSG("TestTrieContains()...");

    bool res = true;

    for( int i = 0; i < WORDS_COUNT; i++ )
    {
        expected = (Word_t *)&(gWords[i]);

        if( TrieContains( gTrie, expected->word ) == false )
        {
            res = false;
            FAIL_MSG("TestTrieContains()...Failed on %s", expected->word );
            break;
        }
    }

    if( res )
    {
        PASS_MSG("TestTrieContains()...Passed");
    }

    return res;
}

static bool TestTrieFind()
{

    Word_t *expected;
    Trie_t *actual;
    Word_t *actualData;
    
    INFO_MSG("TestTrieContains()...");

    bool res = true;

    for( int i = 0; i < WORDS_COUNT; i++ )
    {
        expected = (Word_t *)&(gWords[i]);

        if( (actual = TrieFind( gTrie, expected->word )) )
        {
            actualData = actual->mData;
         
            if( actualData )
            {
                actualData->print( actualData->word );
            }
            else
            {
                res = false;
                FAIL_MSG("TestTrieFind()...Failed on Data reference" );
                break;
            }
        }
        else
        {
            res = false;
            FAIL_MSG("TestTrieFind()...Failed on %s", expected->word );
            break;
        }
    }

    if( res )
    {
        PASS_MSG("TestTrieFind()...Passed");
    }

    return res;
}

static bool TestTrieFindData()
{
    Word_t *expected;
    Trie_t *actual;
    Word_t *actualData;
    
    INFO_MSG("TestTrieFindData()...");

    bool res = true;

    for( int i = 0; i < WORDS_COUNT; i++ )
    {
        expected = (Word_t *)&(gWords[i]);

        if( (actualData = TrieFindData( gTrie, expected->word )) )
        {
            actualData->print( actualData->word );
        }
        else
        {
            res = false;
            FAIL_MSG("TestTrieFindData()...Failed on Data reference" );
            break;
        }
    }

    if( res )
    {
        PASS_MSG("TestTrieFindData()...Passed");
    }

    return res;
}

static bool TestTrieRemove()
{
    bool res = false;

    // TODO: Implement removal
    INFO_MSG("TestTrieRemove()...");
    INFO_MSG("TestTrieRemove()...Not Implemented");
    res = true;

    return res;
}

void PrintStr( const char * str )
{
    INFO_MSG("-> %s <-", str );
}

#endif // __TRIE_TESTER_H__
