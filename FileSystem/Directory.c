#include "Directory.h"
#include "PrintUtils.h"
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

typedef struct stat stat_t;

bool DirectoryExists( const char* pathName )
{
    stat_t info;

    if( stat( pathName, &info ) )
    {
        return false;
    }

    return S_ISDIR( info.st_mode );
}

int DiretoryChange( const char* pathName )
{
    if( DirectoryExists(pathName) )
    {
        return chdir( pathName );
    }

    return ENOTDIR;
}

bool DirectoryContainsFile(const char *dirName, const char *entryName)
{
    dirent_t *entry;
    bool res = false;
    DIR *dir = opendir(dirName);

    if (dir)
    {
        do
        {
            // read the directory
            entry = readdir(dir);

            // check the entry
            if (entry)
            {
                if (strcmp(entry->d_name, entryName) == 0)
                {
                    res = true;
                    break;
                }
            }
        } while (entry);
    }
    return res;
}

dirent_t *DirectoryGetEntry(const char *dirName, const char *entryName)
{
    dirent_t *entry = NULL;
    DIR *dir = opendir(dirName);

    if (dir)
    {
        do
        {
            // read the directory
            entry = readdir(dir);

            // check the entry
            if (entry)
            {
                if (strcmp(entry->d_name, entryName) == 0)
                {
                    break;
                }
            }
        } while (entry);
    }

    return entry;
}

const dirent_t *DirectoryGetEntryConst(const char *dirName, const char *entryName)
{
    return DirectoryGetEntry(dirName, entryName);
}
