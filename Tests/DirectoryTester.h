#if !defined(__DIRECTORY_TESTER_H__)
#define __DIRECTORY_TESTER_H__

#include "Directory.h"
#include "TestUtils.h"

#include <stdbool.h>
#include <stdio.h>

const char *gFile1 = "Readable.txt";
const char *gFile2 = "Writable.txt";
const char *gFile3 = "Executable.txt";
const char *gFileDne = "DoesNotExist.txt";
const char *gFilePath = "/home/chima-ochiagha/Projects/ShellImpl/codecrafters-shell-c/Tests/TestFiles";

static bool TestDirectoryContainsFiles( const char *file );
static bool TestDirectoryDoesNotContainsFiles( const char *file );
static bool TestDirectoryGetEntry();

bool RunTestDirectoryTester()
{
    bool res = false;

    INFO_MSG("Running Directory tests...");

    if( TestDirectoryContainsFiles( gFile1 ) )
    {
        if( TestDirectoryContainsFiles( gFile2 ) )
        {
            if( TestDirectoryContainsFiles( gFile3 ) )
            {
                if( TestDirectoryDoesNotContainsFiles( gFileDne ) )
                {
                    if( TestDirectoryGetEntry( ) )
                    {
                        res = true;
                        PASS_MSG("Running Directory tests...Passed");
                    }
                    else
                    {    
                        ERROR_MSG("Running Directory tests...Failed Get Entry (%s)", gFileDne);
                    }
                }
                else
                {
                    ERROR_MSG("Running Directory tests...Failed on Does not contain file (%s)", gFileDne);
                }
            }
            else
            {
                ERROR_MSG("Running Directory tests...Failed on contains file (%s)", gFile3);
            }
        }
        else
        {
            ERROR_MSG("Running Directory tests...Failed on contains file (%s)", gFile2);
        }
    }
    else
    {
        ERROR_MSG("Running Directory tests...Failed on contains file (%s)", gFile1);
    }

    return res;
}

static bool TestDirectoryContainsFiles( const char *file )
{
    bool res = false;

    if( DirectoryContainsFile(gFilePath, file) )
    {
        res = true;
        PASS_MSG("TestDirectoryContainsFiles()...Passed" );
    }
    else
    {
        ERROR_MSG("TestDirectoryContainsFiles()...Failed %s does not exist", file );
    }

    return res;
}

static bool TestDirectoryDoesNotContainsFiles( const char *file )
{
    bool res = false;

    if( DirectoryContainsFile(gFilePath, file) == false )
    {
        res = true;
        PASS_MSG("TestDirectoryDoesNotContainsFiles()...Passed" );
    }
    else
    {
        ERROR_MSG("TestDirectoryDoesNotContainsFiles()...Failed %s exists and SHOULDN'T", file );
    }

    return res;
}

static bool TestDirectoryGetEntry( )
{
    bool res = false;
    
    dirent_t *entry = NULL;

    if( (entry = DirectoryGetEntry( gFilePath, gFile1 )) )
    {
        INFO_MSG("Successfully retrieved - %s | %s", entry->d_name, gFile1 );
        
        if( (entry = DirectoryGetEntry( gFilePath, gFile2 )) )
        {
            INFO_MSG("Successfully retrieved - %s | %s", entry->d_name, gFile2 );
            
            if( (entry = DirectoryGetEntry( gFilePath, gFile3 )) )
            {
                INFO_MSG("Successfully retrieved - %s | %s", entry->d_name, gFile3 );
                
                if( (entry = DirectoryGetEntry( gFilePath, gFileDne )) == NULL )
                {
                    INFO_MSG("Successfully failed to retrieved - %s", gFileDne );
                    res = true;
                }
                else
                {

                }
            }
            else
            {
                
            }
        }
        else
        {

        }
    }
    else
    {

    }

    return res;
}

#endif // __DIRECTORY_TESTER_H__
