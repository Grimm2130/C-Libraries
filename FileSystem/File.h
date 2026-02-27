#if !defined(__FILE_H__)
#define __FILE_H__

#include <stdbool.h>
#include <stdint.h>

// #define FULL_PATH_LEN (FILENAME_MAX)
#define FULL_PATH_LEN ( 0x800 )

/// @brief File object
typedef struct File
{
    uint32_t perm;              // Permissions
    char path[FULL_PATH_LEN];   // Path
    char name[FULL_PATH_LEN];   // Name
} File_t;

typedef enum FileAcessMask
{
    FILE_ACCESS_MASK_READ,
    FILE_ACCESS_MASK_WRITE,
    FILE_ACCESS_MASK_EXECUTE
} FileAcessMask_t;

#define _CAN_READ_MASK ((1U << (int)FILE_ACCESS_MASK_READ))
#define _CAN_WRITE_MASK ((1U << (int)FILE_ACCESS_MASK_WRITE))
#define _CAN_EXECUTE_MASK ((1U << (int)FILE_ACCESS_MASK_EXECUTE))

File_t *FileCreate(const char *path, const char *name );
void FileInit(File_t *file, const char *path, const char *name);
void FileRelease(File_t *file);
bool FileTypeIsExecutable(File_t *file);
bool FileTypeIsReadable(File_t *file);
bool FileTypeIsWritable(File_t *file);
int FileCheckAccess( const char *path, const char* name, const int mode );
bool FileIsExecutable( const char *path, const char *name );
bool FileIsReadable( const char *path, const char *name );
bool FileIsWritable( const char *path, const char *name );

#endif // __FILE_H__
