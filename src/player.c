#include "player.h"
#include <windows.h>
#include "miniaudio.h"
#include <stdio.h>
#include "util.h"
#include "queue.h"
#include <assert.h>
#include "stack.h"
#include "math.h"


void init_music_player(PlayerHandle *handle, QueueMusic* music_queue){
    ma_result r;
    
    handle->music_queue = music_queue;
    r = ma_engine_init(NULL, &handle->engine);
    if (r != MA_SUCCESS)
    {
        printf("Failed to start engine\n");
        exit(1);
    }
    handle->thread_handle = CreateThread(NULL, 0, music_thread, handle, 0, NULL);
}

DWORD WINAPI music_thread(LPVOID lpParam)
{
    PlayerHandle *handle = lpParam;
    ma_uint64 length;
    ma_result result;
    Stack stack;
    MusicTree cursor;
    char *music_path;
    size_t music_path_len;
    char *path_buffer;
    size_t path_buffer_len = 0;
    size_t path_len = 0;
    bool is_loaded = false;
    CreateEmpty(&stack);

    music_path = get_music_folder_path();
    music_path_len = strlen(music_path);
    (void)result;   
   
    // Infinity loop
    while (1)
    {
        if(!is_Empty(*handle->music_queue) && (!ma_sound_is_playing(&handle->sound))) {
            if (is_loaded) {
                ma_sound_stop(&handle->sound);
                ma_sound_uninit(&handle->sound);
            }
            deQueueMusic(handle->music_queue, &cursor);
            printf("\nMendequeue musik %s\n", cursor->name);
            // ambil path
            path_buffer_len = 0;
            path_len = 0;
            while(cursor->parent != NULL) {
                // Push ke stack
                Push(&stack, cursor);
                // tambahkan panjang ke buffer + 1 buat taruh / setelah nama folder
                // Jika di akhir, + 1 byte akan jadi null terminator
                path_buffer_len += strlen(cursor->name) + 1;
                cursor = cursor->parent;
            }
            // sama, +1 itu buat taruh / 
            path_buffer_len += music_path_len + 1;
            
            path_buffer = malloc(sizeof(char) * path_buffer_len);
            strcpy(path_buffer, music_path);
            path_len += music_path_len;
            *(path_buffer + path_len) = '/';
            // Karena kita append / di akhir sebelumnya
            path_len += 1;
            
            while(!IsEmpty(stack)) {
                Pop(&stack, &cursor);
                strcpy(path_buffer + path_len, cursor->name);
                path_len += strlen(cursor->name);
                *(path_buffer + path_len ) = '/';
                path_len += 1;
            }
            // override '/' jadi null terminator
            *(path_buffer + path_len - 1) = '\0';
            // Load Music.
            result = ma_sound_init_from_file(&handle->engine, path_buffer, 0, NULL, NULL, &handle->sound);
            if (result != MA_SUCCESS)
            {
                return -1;
            }

            ma_sound_start(&handle->sound);
            ma_sound_get_length_in_pcm_frames(&handle->sound, &length);
            is_loaded = true;
        }

        if (handle->_command != NONE)
        {
            switch (handle->_command)
            {
            case NONE:
                // Should be unreachable, do nothing
                break;
            case REWIND:
                ma_sound_seek_to_pcm_frame(&handle->sound, 0);
                break;
            case SEEK:
                ma_sound_seek_to_second(&handle->sound, handle->_command_args[0]);
                break;
            case SKIP:
                ma_sound_seek_to_pcm_frame(&handle->sound, length);
                ma_sound_stop(&handle->sound);
                break;
            default:
                assert(false || "Unreachable Case music_thread");
            }
            handle->_command = NONE;
        }

        // Biar gak busy loop. Loop 60 frame per second
        Sleep(16);
    }
}

int get_currently_player_music_length(PlayerHandle *handle) {
    float outLen;
    ma_result res;
    res = ma_sound_get_length_in_seconds(&(handle->sound), &outLen);

    if (res != MA_SUCCESS) {
        printf("ERROR: %s", ma_result_description(res));
        return -1;
    }
    
    return (int)floorf(outLen);
}


void destroy_music_player(PlayerHandle *handle)
{
    ma_engine_uninit(&handle->engine);
    CloseHandle(handle->thread_handle);
}

void rewind_music(PlayerHandle *handle){
    handle->_command = REWIND;
}

void skip_music(PlayerHandle *handle){
    handle->_command = SKIP;
}


void seek_music(PlayerHandle *handle, int secs){
    handle->_command = SEEK;
    handle->_command_args[0] = secs;
}
