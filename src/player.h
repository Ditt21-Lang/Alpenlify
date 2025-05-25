#ifndef PLAYER_H
#define PLAYER_H
#include <Windows.h>


typedef struct MusicNode {
    char* name;
    struct MusicNode* parent;
    struct MusicNode* nbrother;
    struct MusicNode* fson;   
} MusicNode;
typedef MusicNode* Info;

typedef struct Node {
    Info info;
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

extern MusicCommand music_command;
extern int music_command_args[2];

/*
    IS: Music player belum diinisialisasi
    FS: Music player sudah diinisialisasi

    Creator: Andi Putra
*/
void init_music_player(QueueMusic* music_queue);

/*
    IS: Music player sudah terinisialisasi dan ada isinya 
    FS: Music player hilang, gone, ter-deinisialisasi

    Creator: Andi Putra
*/
void destroy_music_player();

/*
    IS: Thread terbuat
    FS: -

    Creator: Andi Putra
*/
DWORD WINAPI music_thread(LPVOID lpParam);

#endif // PLAYER_H