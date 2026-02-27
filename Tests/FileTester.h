#if !defined(__FILE_TESTER_H__)
#define __FILE_TESTER_H__

#include "File.h"
#include "TestUtils.h"
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

File_t *gFile = NULL;
const char *gReadableFile = "Readable.txt";
const char *gWriteable = "Writable.txt";
const char *gExecutableFile = "Executable.txt";
const char *gTestFilePath = "/home/chima-ochiagha/Projects/CLibs/Tests/TestFiles";

#define RESET_FILE_PTR  \
do  \
{ free( gFile ); gFile = NULL; }    \
while(0)

bool RunTestsFileTester();
static bool TestFileCreate( const char* fileName);
static bool TestFileRelease();
static bool TestFileTypeIsExecutable();
static bool TestFileTypeIsReadable();
static bool TestFileTypeIsWritable();
static bool TestFileIsExecutable();
static bool TestFileIsReadable();
static bool TestFileIsWritable();

bool RunTestsFileTester()
{
    bool res = false;
    INFO_MSG("Running File Tests....");

    if (TestFileIsReadable())
    {
        if (TestFileIsWritable())
        {
            if (TestFileIsExecutable())
            {
                if (TestFileCreate( gReadableFile ))
                {
                    if (TestFileTypeIsReadable())
                    {
                        if (TestFileRelease())
                        {
                            if (TestFileCreate( gWriteable))
                            {
                                if (TestFileTypeIsWritable())
                                {
                                    if (TestFileRelease())
                                    {
                                        if (TestFileCreate( gExecutableFile ))
                                        {
                                            if (TestFileTypeIsExecutable())
                                            {
                                                if (TestFileRelease())
                                                {
                                                    PASS_MSG("Running File Tests...Passed");
                                                    res = true;
                                                }
                                                else
                                                {
                                                    FAIL_MSG("Running File Tests...Failed on TestFileRelease(X)");
                                                }
                                            }
                                            else
                                            {
                                                FAIL_MSG("Running File Tests...Failed on TestFileTypeIsExecutable");
                                            }
                                        }
                                        else
                                        {
                                            FAIL_MSG("Running File Tests...Failed on TestFileCreate( X )");
                                        }
                                    }
                                    else
                                    {
                                        FAIL_MSG("Running File Tests...Failed on TestFileRelease(W)");
                                    }
                                }
                                else
                                {
                                    FAIL_MSG("Running File Tests...Failed on TestFileTypeIsWritable");
                                }
                            }
                            else
                            {
                                FAIL_MSG("Running File Tests...Failed on TestFileCreate( W )");
                            }
                        }
                        else
                        {
                            FAIL_MSG("Running File Tests...Failed on TestFileRelease(R)");
                        }
                    }
                    else
                    {
                        FAIL_MSG("Running File Tests...Failed on TestFileTypeIsReadable");
                    }
                }
                else
                {
                    FAIL_MSG("Running File Tests...Failed on TestFileCreate( R )");
                }
            }
            else
            {
                FAIL_MSG("Running File Tests...Failed on TestFileIsExecutable");
            }
        }
        else
        {
            FAIL_MSG("Running File Tests...Failed on TestFileIsWritable");
        }
    }
    else
    {
        FAIL_MSG("Running File Tests...Failed on TestFileIsReadable");
    }

    return res;
}

/// @brief Test file creation
/// @return
static bool TestFileCreate(const char* fileName)
{
    bool res = false;

    gFile = FileCreate( gTestFilePath, fileName );

    if( gFile->perm )
    {
        if( strcmp( gTestFilePath, gFile->path ) == 0 )
        {
            if( strcmp( fileName, gFile->name ) == 0 )
            {
                res = true;
                PASS_MSG("TestFileCreate()...Passed");
            }
            else
            {
                ERROR_MSG("TestFileCreate()...Failed. Filename mismatch %s <> %s", fileName, gFile ? gFile->name : "----" );
            }
        }
        else
        {
            ERROR_MSG("TestFileCreate()...Failed. Filepath mismatch %s <> %s", gTestFilePath, gFile ? gFile->path : "----" );
        }
    }
    else
    {
        ERROR_MSG("TestFileCreate()...Failed. File permissions not set");
    }

    return res;
}

static bool TestFileRelease()
{
    bool res = false;

    if( gFile )
    {
        FileRelease( gFile );

        if( gFile->perm == 0 )
        {
            if( strlen(gFile->path) == 0 )
            {
                if( strlen(gFile->name) == 0 )
                {
                    res = true;
                    RESET_FILE_PTR;
                    PASS_MSG("TestFileRelease()...Passed");
                }
                else
                {
                    ERROR_MSG("TestFileRelease()...Failed. Did not dereference 'Path' field");
                }
            }
            else
            {   
                ERROR_MSG("TestFileRelease()...Failed. Did not dereference 'Path' field");
            }
        }
        else
        {
            ERROR_MSG("TestFileRelease()...Failed. Did not clear permissions");
        }
    }
    else
    {
        ERROR_MSG("TestFileRelease()...Failed. Invalid File object");
    }

    return res;
}

static bool TestFileTypeIsExecutable()
{
    bool res = false;

    if( gFile )
    {
        if( (gFile->perm & _CAN_EXECUTE_MASK) == _CAN_EXECUTE_MASK )
        {
            res = true;
            PASS_MSG("TestFileTypeIsExecutable()...Passed" );
        }
        else
        {
            ERROR_MSG("TestFileTypeIsExecutable()...Failed. File '%s' does not have executable permissions", gFile ? gFile->name : "---" );
        }
    }
    else
    {
        ERROR_MSG("TestFileTypeIsExecutable()...Failed. Invalid File object" );
    }

    return res;
}

static bool TestFileTypeIsReadable()
{
    bool res = false;

    if( gFile )
    {
        if( (gFile->perm & _CAN_READ_MASK) == _CAN_READ_MASK )
        {
            res = true;
            PASS_MSG("TestFileTypeIsReadable()...Passed" );
        }
        else
        {
            ERROR_MSG("TestFileTypeIsReadable()...Failed. File '%s' does not have read permissions", gFile ? gFile->name : "---" );
        }
    }
    else
    {
        ERROR_MSG("TestFileTypeIsReadable()...Failed. Invalid File object" );
    }
    return res;
}

static bool TestFileTypeIsWritable()
{
    bool res = false;

    if( gFile )
    {
        if( (gFile->perm & _CAN_WRITE_MASK) == _CAN_WRITE_MASK )
        {
            res = true;
            PASS_MSG("TestFileTypeIsWritable()...Passed" );
        }
        else
        {
            ERROR_MSG("TestFileTypeIsWritable()...Failed. File '%s' does not have write permissions", gFile ? gFile->name : "---" );
        }
    }
    else
    {
        ERROR_MSG("TestFileTypeIsWritable()...Failed. Invalid File object" );
    }

    return res;
}

static bool TestFileIsExecutable()
{
    bool res = false;

    if (FileIsExecutable(gTestFilePath, gExecutableFile) == true)
    {
        if (FileIsExecutable(gTestFilePath, gWriteable) == false)
        {
            if (FileIsExecutable(gTestFilePath, gReadableFile) == false)
            {
                PASS_MSG("TestFileIsExecutable()...Passed");
                res = true;
            }
            else
            {
                ERROR_MSG("TestFileIsExecutable()...%s/%s is executable", gTestFilePath, gReadableFile);
            }
        }
        else
        {
            ERROR_MSG("TestFileIsExecutable()...%s/%s is executable", gTestFilePath, gWriteable);
        }
    }
    else
    {
        ERROR_MSG("TestFileIsExecutable()...%s/%s is not executable", gTestFilePath, gExecutableFile);
    }

    return res;
}

static bool TestFileIsReadable()
{
    bool res = false;

    if (FileIsReadable(gTestFilePath, gReadableFile) == true)
    {
        if (FileIsReadable(gTestFilePath, gWriteable) == false)
        {
            if (FileIsReadable(gTestFilePath, gExecutableFile) == false)
            {
                PASS_MSG("TestFileIsReadable()...Passed");
                res = true;
            }
            else
            {
                ERROR_MSG("TestFileIsReadable()...%s/%s is readable", gTestFilePath, gExecutableFile);
            }
        }
        else
        {
            ERROR_MSG("TestFileIsReadable()...%s/%s is readable", gTestFilePath, gWriteable);
        }
    }
    else
    {
        ERROR_MSG("TestFileIsReadable()...%s/%s is not readable", gTestFilePath, gReadableFile);
    }

    return res;
}

static bool TestFileIsWritable()
{
    bool res = false;

    if (FileIsWritable(gTestFilePath, gWriteable) == true)
    {
        if (FileIsWritable(gTestFilePath, gReadableFile) == false)
        {
            if (FileIsWritable(gTestFilePath, gExecutableFile) == false)
            {
                PASS_MSG("TestFileIsWritable()...Passed");
                res = true;
            }
            else
            {
                ERROR_MSG("TestFileIsWritable()...%s/%s is writable", gTestFilePath, gExecutableFile);
            }
        }
        else
        {
            ERROR_MSG("TestFileIsWritable()...%s/%s is writable", gTestFilePath, gReadableFile);
        }
    }
    else
    {
        ERROR_MSG("TestFileIsWritable()...%s/%s is not writable %s", gTestFilePath, gWriteable, strerror(errno));
    }
    return res;
}

#endif // __FILE_TESTER_H__
