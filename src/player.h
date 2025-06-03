#ifndef PLAYER_H
#define PLAYER_H
#include <Windows.h>
#include "miniaudio.h"


typedef struct MusicNode {
    char* name;
    struct MusicNode* parent;
    struct MusicNode* nbrother;
    struct MusicNode* fson;   
} MusicNode;
typedef MusicNode* MusicTree;

typedef struct Node {
    MusicTree info;
    struct Node* next;
} Node;

typedef struct QueueMusic {
    Node* front;
    Node* rear;
} QueueMusic;

typedef struct Stack{
    Node* Top;
} Stack ;

typedef enum MusicCommand {
    NONE,
    REWIND,
    SKIP,
    SEEK,
} MusicCommand;


typedef struct PlayerHandle {
    HANDLE thread_handle;
    ma_engine engine;
    ma_sound sound;
    MusicCommand _command;
    int _command_args[1];
    QueueMusic* music_queue;
} PlayerHandle; 

/*
IS: Music player belum diinisialisasi
FS: Music player sudah diinisialisasi

Creator: Andi Putra
*/
void init_music_player(PlayerHandle *handle, QueueMusic* music_queue);

/*
IS: Music player sudah terinisialisasi dan ada isinya 
FS: Music player hilang, gone, ter-deinisialisasi

Creator: Andi Putra
*/
void destroy_music_player(PlayerHandle *handle);

/*
IS: Music player sudah terinisialisasi
FS: mengembalikan panjang dari musik dalam detik. Jika error, mengembalikan -1

Creator: Andi Putra
*/
int get_currently_player_music_length(PlayerHandle *handle);

/*
IS: Thread terbuat
FS: -

Creator: Andi Putra
*/
DWORD WINAPI music_thread(LPVOID lpParam);

/*
IS: Thread terbuat
FS: merewind musik  dari awal

Creator: Andi Putra
 */
void rewind_music(PlayerHandle *handle);

/*
IS: Thread terbuat
FS: menskip musik dari awal

Creator: Andi Putra
 */
void skip_music(PlayerHandle *handle);

/*
IS: Thread terbuat
FS: seek musik ke detik yang ditentukan

Creator: Andi Putra
 */
void seek_music(PlayerHandle *handle, int secs);


#endif // PLAYER_H