#include "BufferTester.h"
#include "FixedSizeBufferTester.h"
#include "TestUtils.h"
#include "ListTester.h"
#include "TrieTester.h"
#include "FileTester.h"
#include "DirectoryTester.h"
#include "StackTester.h"
#include "QueueTester.h"
#include "StringStreamerTester.h"
#include "StringTester.h"

int main()
{
    int res = 1;

    if (RunTestsBuffer())
    {
        if (RunFixedSizeBuffersFixedSizeBuffer())
        {
            if (RunTestsStackTester())
            {
                if (RunTestsQueueTester())
                {
                    if (RunTestsLists())
                    {
                        // Test Trie Functionality
                        if (RunTestsTrie())
                        {
                            if (RunTestsFileTester())
                            {
                                if (RunTestDirectoryTester())
                                {
                                    if (RunTestStringStreamerTester())
                                    {
                                        if( RunTestsStringTester() )
                                        {
                                            res = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return res;
}