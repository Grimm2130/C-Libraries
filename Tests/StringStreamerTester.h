#if !defined(__STRING_STREAMER_TESTER_H__)
#define __STRING_STREAMER_TESTER_H__

#include "TestUtils.h"
#include "StringStreamer.h"
#include "StringSequence.h"
#include "StreamerPosition.h"
#include  <stdint.h>
#include  <stdbool.h>

static StringStreamer_t * sStreamer = NULL;

extern char * gStringSequence;

static bool TestStringStreamerCreate();
static bool TestStringStreamerRelease();
static bool TestStringStreamerNext();
static bool TestStringStreamerPrev();

bool RunTestStringStreamerTester()
{
    bool res = false;

    INFO_MSG("Testing String Streamer...");

    if( TestStringStreamerCreate() )
    {
        if( TestStringStreamerNext() )
        {
            if( TestStringStreamerPrev() )
            {
                if( TestStringStreamerRelease() )
                {
                    res = true;
                    PASS_MSG("Testing String Streamer...Passed");
                }
                else
                {
                    FAIL_MSG("Testing String Streamer...Failed on Release");
                }
            }
            else
            {
                FAIL_MSG("Testing String Streamer...Failed on Prev");
            }
        }
        else
        {
            FAIL_MSG("Testing String Streamer...Failed on Next");
        }
    }
    else
    {
        FAIL_MSG("Testing String Streamer...Failed on Create");
    }

    return res;
}

static bool TestStringStreamerCreate()
{
    bool res = false;

    INFO_MSG("Testing String Stream Create...");

    sStreamer = StringStreamerCreate( gStringSequence, false );

    if( sStreamer )
    {
        if( sStreamer->mCopied == false )
        {
            if( sStreamer->mIndex == 0 )
            {
                if( sStreamer->mSize == strlen( gStringSequence) )
                {
                    if( (sStreamer->mPos.col == 0) && (sStreamer->mPos.row == 0) )
                    {
                        if( sStreamer->mLastPos )
                        {
                            if( sStreamer->mStream )
                            {
                                res = true;
                                PASS_MSG("Testing String Stream Create...Passed");
                            }
                            else
                            {
                                FAIL_MSG("Testing String Stream Create...Failed string stream not initialized");
                            }
                        }
                        else
                        {
                            FAIL_MSG("Testing String Stream Create...Failed streamer stack not initialized");
                        }
                    }
                    else
                    {
                        FAIL_MSG("Testing String Stream Create...Failed Streamer Position not initialized");
                    }
                }
                else
                {
                    FAIL_MSG("Testing String Stream Create...Failed Size not initialized");
                }
            }
            else
            {
                FAIL_MSG("Testing String Stream Create...Failed Index not initialized");
            }
        }
        else
        {
            FAIL_MSG("Testing String Stream Create...Failed Copied flag should be false");
        }
    }
    else
    {
        FAIL_MSG("Testing String Stream Create...Failed Streamer object not initialized");
    }

    return res;
}

static bool TestStringStreamerRelease()
{
    bool res = false;

    INFO_MSG("Testing String Streamer Release...Passed");

    if( sStreamer )
    {
        StringStreamerRelease( sStreamer );

        if( sStreamer->mLastPos == NULL )
        {
            if( sStreamer->mStream == NULL )
            {
                res = true;
                PASS_MSG("Testing String Streamer Release...Passed");
            }
            else
            {
                FAIL_MSG("Testing String Stream Release...Failed Streamer's stream object not deinitialized");
            }
        }
        else
        {
            FAIL_MSG("Testing String Stream Release...Failed Streamer's last position object not deinitialized");
        }
    }

    return res;
}

static bool TestStringStreamerNext()
{
    char c, n;
    uint16_t row, col, lastRow, lastCol;
    
    bool res = true;
    StreamerPosition_t *lastPos = NULL;

    INFO_MSG("Testing String Streamer Next...");

    for( size_t i = 0; i < strlen( gStringSequence); i++ )
    {
        c = StringStreamerPeekFront( sStreamer );

        if( c == gStringSequence[i] )
        {
            switch(c)
            {
            case '\n':
                lastRow = sStreamer->mPos.row;
                lastCol = sStreamer->mPos.col;
                
                if( (n = StringStreamerNext( sStreamer )) != c )
                {
                    FAIL_MSG("Testing String Streamer Next...Failed Next{%c} != Prev{%c}", n, c);
                    res = false;
                    break;
                }

                row = sStreamer->mPos.row;
                col = sStreamer->mPos.col;
                
                if( (row != lastRow + 1) && (col != 0) )
                {
                    FAIL_MSG("Testing String Streamer Next...Failed New-Position mismatch Expected {%u, %u} != Actual{%u, %u}", lastRow + 1, 0, row, col );
                    res = false;
                    break;
                }

                lastPos = StackTop( sStreamer->mLastPos );

                if( (lastPos->row != lastRow) || (lastPos->col != lastCol) )
                {
                    FAIL_MSG("Testing String Streamer Next...Failed Last-Position Mismatch (%u, %u), (%u, %u)",
                        lastPos->row,
                        lastPos->col,
                        lastRow,
                        lastCol
                    );
                    res = false;
                    break;
                }
            break;

            default:
            break;
            }
        }
    }

    if( res )
    {
        PASS_MSG("Testing String Streamer Next...Passed" );
    }

    return res;
}

static bool TestStringStreamerPrev()
{
    char c, n;
    uint16_t row, col, lastRow, lastCol;
    
    bool res = true;
    StreamerPosition_t *lastPos = NULL;

    INFO_MSG("Testing String Streamer Prev...");

    for( int i = (int)strlen( gStringSequence) - 1; i >= 0; i-- )
    {
        c = StringStreamerPeekBack( sStreamer );

        if( c == gStringSequence[i] )
        {
            switch(c)
            {
            case '\n':

                // Store the last row and column (to be retrieved)
                lastPos = StackTop( sStreamer->mLastPos );

                if( (n = StringStreamerPrev( sStreamer )) != c )
                {
                    FAIL_MSG("Testing String Streamer Prev...Failed Next{%c} != Prev{%c}", n, c);
                    res = false;
                    break;
                }
                
                // Get current row and column
                row = sStreamer->mPos.row;
                col = sStreamer->mPos.col;

                if( (row != lastPos->row) && (col != lastPos->col) )
                {
                    FAIL_MSG("Testing String Streamer Prev...Failed New-Position mismatch Expected {%u, %u} != Actual{%u, %u}", lastRow + 1, 0, row, col );
                    res = false;
                    break;
                }

            break;

            default:
            break;
            }
        }
    }

    if( res )
    {
        PASS_MSG("Testing String Streamer Prev...Passed" );
    }

    return res;
}



#endif // __STRING_STREAMER_TESTER_H__
