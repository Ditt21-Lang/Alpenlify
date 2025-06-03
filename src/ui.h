#ifndef UI_H
#define UI_H

#include "player.h"
#include "tree.h"
#include "queue.h"
#include "time.h"
#include <ctype.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

/*
    IS: Terminal kosong
    FS: Terminal menampilkan pilihan menu dan menanyakan pilihan user

    Creator: Raf
*/
void menu(MusicNode tree, QueueMusic *queue, PlayerHandle *handle); 

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

void add_music(MusicNode tree, QueueMusic *queue);

/*
    IS: Musik dijalankan
    FS: Musik dihentikan dan lanjut ke music berikutnya di queue jika ada

    Creator: Raf
*/

void skip(PlayerHandle *handle);

/*
    IS: Musik berjalan
    FS: Musik diulang dari awal

    Creator:Raf
*/

void replay(PlayerHandle *handle);

/*
    IS: Musik berjalan
    FS: Musik berjalan di detik yang ditentukan

    Creator:Raff
*/

void seek(PlayerHandle *handle);



#endif // PLAYER_H