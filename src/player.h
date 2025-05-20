#ifndef PLAYER_H
#define PLAYER_H

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
    IS: Thread music belum terinisialisasi
    FS: Thread music terinisialisasi

    Creator: Andi Putra
*/
void init_music_player();

/*
    IS: Thread music telah terinisialisasi. Queue music mungkin kosong.
    FS: Music masuk ke queue

    Creator: Andi Putra
*/
void enqueue_music(MusicNode *node);

#endif // PLAYER_H