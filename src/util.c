#include "util.h"

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <shlobj.h>      // For SHGetKnownFolderPath
#include <shobjidl.h>    // For KNOWNFOLDERID definitions
#include <stdio.h>
#include <stdlib.h>

char* _music_folder_path_cache = NULL;

char* get_music_folder_path(){
    PWSTR widePath = NULL;
    HRESULT result ;
    
    if (_music_folder_path_cache != NULL) {
        // Cache hit..
        return _music_folder_path_cache;
    }

    result = SHGetKnownFolderPath(&FOLDERID_Music, 0, NULL, &widePath);

    if (SUCCEEDED(result)) {
        int size = WideCharToMultiByte(CP_ACP, 0, widePath, -1, NULL, 0, NULL, NULL);
        if (_music_folder_path_cache == NULL) {
            _music_folder_path_cache = (char *)malloc(size);
        }else {
            // Cache hit..
            return _music_folder_path_cache;
        }

        if(_music_folder_path_cache == NULL) {
            printf("Cannot allocate music path");
            exit(1);    
        }

        WideCharToMultiByte(CP_ACP, 0, widePath, -1, _music_folder_path_cache, size, NULL, NULL);
        CoTaskMemFree(widePath);
        
        return _music_folder_path_cache;
    } else {
        printf("FAILED");
        exit(1);
    }
}