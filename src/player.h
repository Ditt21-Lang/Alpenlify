#ifndef PLAYER_H
#define PLAYER_H

typedef MusicNode MusicNode;

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