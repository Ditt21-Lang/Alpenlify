#include "player.h"
#include <windows.h>
#include "miniaudio.h"
#include <stdio.h>
#include <util.h>

ma_engine _music_engine;
HANDLE _thread_handle;

void init_music_player(QueueMusic* music_queue){
    ma_result r;
    r = ma_engine_init(NULL, &_music_engine);
    if (r != MA_SUCCESS) {
        printf("Failed to start engine\n");
        exit(1);
    }
    _thread_handle = CreateThread(NULL, 0, music_thread, music_queue, 0, NULL);
}


DWORD WINAPI music_thread(LPVOID lpParam){
    UNUSED(lpParam);
    while(1) {
        printf("FOO BAR\n");
        Sleep(1000);
    }
}

void destroy_music_player(){
    ma_engine_uninit(&_music_engine);
    CloseHandle(_thread_handle);
}