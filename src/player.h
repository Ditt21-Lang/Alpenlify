#ifndef PLAYER_H
#define PLAYER_H
#include <Windows.h>

typedef MusicNode* Info;

typedef struct MusicNode {
    char* name;
    struct MusicNode* parent;
    struct MusicNode* nbrother;
    struct MusicNode* fson;   
} MusicNode;

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