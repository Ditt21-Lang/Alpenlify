#ifndef UI_H
#define UI_H

#include "player.h"

/*
    IS: Terminal kosong
    FS: Terminal menampilkan pilihan menu dan menanyakan pilihan user

    Creator: Andi Putra
*/
void menu(); 

/*
    IS: Meminta user input pilihan 
    FS: Mengembalikkan value yang diinput

    Creator:
*/

void input_user(char* buffer);

/*
    IS: Tree tidak kosong  
    FS: Tree ditampilkan ke layar

    Creator: 
*/

void view_music(MusicNode tree);

/*
    IS: Queue mungkin kosong
    FS: Musik dalam queue bertambah 

    Creator:
*/

void add_music(MusicNode tree, QueueNode queue);

/*
    IS: Musik dijalankan
    FS: Musik dihentikan dan lanjut ke music berikutnya di queue jika ada

    Creator:
*/

void skip();

/*
    IS: Musik berjalan
    FS: Musik diulang dari awal

    Creator:
*/

void rewind();

/*
    IS: Musik berjalan
    FS: Musik berjalan di detik yang ditentukan

    Creator:
*/

void seek(int detik);



#endif // PLAYER_H