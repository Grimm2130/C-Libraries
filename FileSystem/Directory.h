#if !defined(__DIRECTORY_H__)
#define __DIRECTORY_H__

#include <dirent.h>
#include <stdbool.h>

typedef struct dirent dirent_t;

bool DirectoryExists( const char* pathName );
int DiretoryChange( const char* pathName );
bool DirectoryContainsFile(const char *dirName, const char *entryName);
dirent_t *DirectoryGetEntry(const char *dirName, const char *entryName);
const dirent_t *DirectoryGetEntryConst(const char *dirName, const char *entryName);

#endif // __DIRECTORY_H__
