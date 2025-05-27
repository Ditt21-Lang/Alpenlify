#include "player.h"
#include <windows.h>
#include "miniaudio.h"
#include <stdio.h>
#include "util.h"
#include "queue.h"
#include <assert.h>
#include "stack.h"

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
    QueueMusic* queue = lpParam;
    ma_sound sound = {0};
    ma_uint64 length;
    ma_result result;
    Stack stack;
    MusicTree cursor;
    char *music_path;
    size_t music_path_len;
    char *path_buffer;
    size_t path_buffer_len = 0;
    size_t path_len = 0;
    CreateEmpty(&stack);

    music_path = get_music_folder_path();
    music_path_len = strlen(music_path);
    (void)result;   
   
    // Infinity loop
    while (1)
    {
        if(!is_Empty(*queue) && (!ma_sound_is_playing(&sound))) {
            if (!ma_sound_is_playing(&sound)) {
                ma_sound_stop(&sound);
                ma_sound_uninit(&sound);
            }
            deQueueMusic(queue, &cursor);
            printf("\nMendequeue musik %s", cursor->name);
            // ambil path
            path_buffer_len = 0;
            path_len = 0;
            while(cursor->parent != NULL) {
                Push(&stack, cursor);
                path_buffer_len += strlen(cursor->name) + 1;
                cursor = cursor->parent;
            }
            path_buffer_len += music_path_len;
            path_buffer = malloc(sizeof(char) * path_buffer_len);
            strcpy(path_buffer, music_path);
            path_len += music_path_len;
            *(path_buffer + path_len) = '/';
            path_len += 1;
            while(!IsEmpty(stack)) {
                Pop(&stack, &cursor);
                strcpy(path_buffer + path_len, cursor->name);
                path_len += strlen(cursor->name);
                *(path_buffer + path_len ) = '/';
                path_len += 1;
            }
            *(path_buffer + path_len - 1) = '\0';
            // Load Music.
            result = ma_sound_init_from_file(&_music_engine, path_buffer, 0, NULL, NULL, &sound);
            if (result != MA_SUCCESS)
            {
                return -1;
            }

            ma_sound_start(&sound);
            ma_sound_get_length_in_pcm_frames(&sound, &length);
            
        }

        if (music_command != NONE)
        {
            printf("Melakukan %d", music_command);
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
                ma_sound_stop(&sound);
                break;
            default:
                assert(false || "Unreachable Case music_thread");
            }
            music_command = NONE;
        }

        // Biar gak busy loop
        Sleep(16);
    }
}

void destroy_music_player()
{
    ma_engine_uninit(&_music_engine);
    CloseHandle(_thread_handle);
}