#include "TestUtils.h"
#include "ListTester.h"
#include "BufferTester.h"
#include "TrieTester.h"
#include "FileTester.h"
#include "DirectoryTester.h"

int main()
{
    int res = 1;
    
    if( RunTestsBuffer() )
    {
        if( RunTestsLists() )
        {
            // Test Trie Functionality
            if( RunTestsTrie() )
            {
                if( RunTestsFileTester() )
                {
                    if( RunTestDirectoryTester() )
                    {
                        res = 0;
                    }
                }
            }
        }
    }


    return res;
}   