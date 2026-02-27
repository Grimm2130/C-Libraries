#include "File.h"
#include "MemUtils.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


File_t *FileCreate(const char *path, const char *name )
{
    size_t pathlen, namelen;
    char fullPath[PATH_MAX + FILENAME_MAX + 1];

    File_t *file = (File_t *)calloc(1, sizeof(File_t));

    FileInit(file, path, name);

    return file;
}

void FileInit(File_t *file, const char *path, const char *name)
{
    size_t pathlen, namelen;
    char fullPath[PATH_MAX + FILENAME_MAX + 1];

    file->perm = 0;

    if (path)
    {
        pathlen = strlen(path);
        Strncpy(file->path, path, pathlen, pathlen);
    }
    if (name)
    {
        namelen = strlen(name);
        Strncpy(file->name, name, namelen, namelen);
    }

    int len = snprintf(fullPath, PATH_MAX + FILENAME_MAX, "%s/%s", path, name);

    if (len >= 0)
    {
        // Check that the file exists

        if (access(fullPath, R_OK) == F_OK)
        {
            file->perm |= _CAN_READ_MASK;
        }
        if (access(fullPath, W_OK) == F_OK)
        {
            file->perm |= _CAN_WRITE_MASK;
        }
        if (access(fullPath, X_OK) == F_OK)
        {
            file->perm |= _CAN_EXECUTE_MASK;
        }
    }
}

void FileRelease(File_t *file)
{
    if( file )
    {
        file->perm = 0;
        file->path[0] = file->name[0] = '\0';
    }
}

bool FileTypeIsExecutable(File_t *file)
{ 
    return (file->perm & _CAN_READ_MASK);
}

bool FileTypeIsReadable(File_t *file)
{
    return (file->perm & _CAN_WRITE_MASK);
}

bool FileTypeIsWritable(File_t *file)
{ 
    return (file->perm & _CAN_EXECUTE_MASK);
}

int FileCheckAccess( const char *path, const char* name, const int mode )
{
    int res = ENOENT;

    if( path && name )
    {
        char fullPath[FULL_PATH_LEN];
        snprintf( fullPath, FULL_PATH_LEN, "%s/%s", path, name );
        res = access( fullPath, mode );
    }

    return res;
}

bool FileIsExecutable( const char *path, const char *name )
{
    return (FileCheckAccess( path, name, X_OK ) == F_OK);
}

bool FileIsReadable( const char *path, const char *name )
{
    return (FileCheckAccess( path, name, R_OK ) == F_OK);
}

bool FileIsWritable( const char *path, const char *name )
{
    return (FileCheckAccess( path, name, W_OK ) == F_OK);
}
