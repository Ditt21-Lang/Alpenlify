#include "ui.h"

/*
    IS: Terminal kosong
    FS: Terminal menampilkan pilihan menu dan menanyakan pilihan user

    Creator: Raf
*/

void menu(MusicNode tree, QueueMusic queue){
    int x, detik = -1;
    while(1){
        printf("1. Lihat Musik\n2. Tambahkan musik ke queue\n3. Skip\n4. Replay\n5. Skip\nMasukkan pilihan: ");
        scanf("%d", &x);
        switch(x){
        case 1: view_music(tree);break;
        case 2: add_music(tree,queue);break;
        case 3: skip(); break;
        case 4: replay(); break;
        case 5: printf("Masukkan detik ke berapa");
                scanf("%d", &detik);
                while(detik<0){
                    system("cls");
                    printf("Detik tidak boleh kurang dari 0\n");
                    printf("Masukkan detik ke berapa: ");
                    scanf("%d", &detik);
                }seek(detik); break;
        default: break;
    }
    system("cls");
    }
}

/*
    IS: Tree tidak kosong  
    FS: Tree ditampilkan ke layar

    Creator: Raf
*/

void view_music(MusicNode tree){
    print_tree(tree, 0);
}

/*
    IS: Queue mungkin kosong
    FS: Musik dalam queue bertambah 

    Creator: Raf
*/

void add_music(MusicNode tree, QueueMusic queue){
    printf("Ini add music");
    (void)tree;(void)queue;
    getch();
}

/*
    IS: Musik dijalankan
    FS: Musik dihentikan dan lanjut ke music berikutnya di queue jika ada

    Creator: Raf
*/

void skip(){
    printf("Ini skip");
    getch();
}

/*
    IS: Musik berjalan
    FS: Musik diulang dari awal

    Creator:Raf
*/

void replay(){
    printf("Ini replay");
    getch();
}

/*
    IS: Musik berjalan
    FS: Musik berjalan di detik yang ditentukan

    Creator:Raff
*/

void seek(int detik){
    printf("Ini seeks");
    printf("%d", detik);
    getch();
}
