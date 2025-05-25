#ifndef UTIL_H
#define UTIL_H
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <shlobj.h>      // For SHGetKnownFolderPath
#include <shobjidl.h>    // For KNOWNFOLDERID definitions

/*
    IS: -
    FS: Path ke folder dikembalikan

    Creator: Andiputraw
*/
char* get_music_folder_path();


#endif