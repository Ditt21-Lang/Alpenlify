#ifndef PLAYER_H
#define PLAYER_H

typedef struct MusicNode {
    char* name;
    struct MusicNode* parent;
    struct MusicNode* nbrother;
    struct MusicNode* fson;   
} MusicNode;

typedef struct QueueNode {
    MusicNode* ingfo;
    struct QueueNode* next;
} QueueNode;

typedef struct MusicQueue {
    QueueNode* front;
    QueueNode* rear;
} MusicQueue;


typedef struct StackNode{
    MusicNode* info;
    QueueNode* next;    
} StackNode;



typedef struct Stack{
    StackNode* Top;
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