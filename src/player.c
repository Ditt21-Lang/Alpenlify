#include "player.h"
#include <windows.h>
#include "miniaudio.h"
#include <stdio.h>
#include "util.h"
#include "queue.h"
#include <assert.h>

ma_engine _music_engine;
HANDLE _thread_handle;

MusicCommand music_command = NONE;
int music_command_args[2] = {0};

void init_music_player(QueueMusic *music_queue)
{
    ma_result r;
    r = ma_engine_init(NULL, &_music_engine);
    if (r != MA_SUCCESS)
    {
        printf("Failed to start engine\n");
        exit(1);
    }
    _thread_handle = CreateThread(NULL, 0, music_thread, music_queue, 0, NULL);
}

DWORD WINAPI music_thread(LPVOID lpParam)
{
    UNUSED(lpParam);
    // QueueMusic* queue = lpParam;
    ma_sound sound = {0};
    ma_uint64 length;
    ma_result result;

    result = ma_sound_init_from_file(&_music_engine, "C:\\Users\\andip\\Music\\Balatro.mp3", 0, NULL, NULL, &sound);

    if (result != MA_SUCCESS)
    {
        printf("Failed to load music");
        return -1;
    }

    // Infinity loop
    while (1)
    {
        // if(!is_Empty(*queue) && ma_sound_at_end(&sound)) {
        if (!ma_sound_is_playing(&sound))
        {
            {
                // Load Music. Blocking sampai tree nya udah jadi
                ma_sound_start(&sound);
                ma_sound_get_length_in_pcm_frames(&sound, &length);
            }
        }

        if (music_command != NONE)
        {
            switch (music_command)
            {
            case NONE:
                // Should be unreachable, do nothing
                break;
            case REWIND:
                ma_sound_seek_to_pcm_frame(&sound, 0);
                break;
            case SEEK:
                ma_sound_seek_to_second(&sound, music_command_args[0]);
                break;
            case SKIP:
                ma_sound_seek_to_pcm_frame(&sound, length);
                break;
            default:
                assert(false || "Unreachable Case music_thread");
            }
        }

        // Biar gak busy loop
        Sleep(1000);
    }
}

void destroy_music_player()
{
    ma_engine_uninit(&_music_engine);
    CloseHandle(_thread_handle);
}