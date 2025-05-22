#ifndef UI_H
#define UI_H

#include "player.h"

/*
    IS: Terminal kosong
    FS: Terminal menampilkan pilihan menu dan menanyakan pilihan user

    Creator: Raf
*/
void menu(); 

/*
    IS: Meminta user input pilihan 
    FS: Mengembalikkan value yang diinput

    Creator: Raf
*/

void input_user(char* buffer);

/*
    IS: Tree tidak kosong  
    FS: Tree ditampilkan ke layar

    Creator: Raf
*/

void view_music(MusicNode tree);

/*
    IS: Queue mungkin kosong
    FS: Musik dalam queue bertambah 

    Creator: Raf
*/

void add_music(MusicNode tree, QueueMusic queue);

/*
    IS: Musik dijalankan
    FS: Musik dihentikan dan lanjut ke music berikutnya di queue jika ada

    Creator: Raf
*/

void skip();

/*
    IS: Musik berjalan
    FS: Musik diulang dari awal

    Creator:Raf
*/

void rewind();

/*
    IS: Musik berjalan
    FS: Musik berjalan di detik yang ditentukan

    Creator:Raff
*/

void seek(int detik);



#endif // PLAYER_H