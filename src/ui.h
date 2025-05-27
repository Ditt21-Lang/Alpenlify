#ifndef UI_H
#define UI_H

#include "player.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>

/*
    IS: Terminal kosong
    FS: Terminal menampilkan pilihan menu dan menanyakan pilihan user

    Creator: Raf
*/
void menu(MusicNode tree, QueueMusic queue); 

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

void replay();

/*
    IS: Musik berjalan
    FS: Musik berjalan di detik yang ditentukan

    Creator:Raff
*/

void seek(int detik);



#endif // PLAYER_H