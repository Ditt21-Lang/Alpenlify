#ifndef TREE_H
#define TREE_H
#include "player.h"

/*
    IS: Diketahui nama file
    FS: Mengembalikan nilai true jika ada file dengan ekstensi "".mp3"

    Creator: Gilang Aditya
*/
boolean end_with_mp3(const char *filename);

/*
    IS: Direktori Musik ada di user
    FS: Tree ada dengan isi direktori musik user

    Creator: Gilang Aditya
*/
void read_dir_music(const char *base_path, MusicNode* root);

/*
    IS: Tree belum ada
    FS: Tree ada dengan isi direktori musik user

    Creator: Gilang Aditya
*/
void populate_tree(MusicNode** root);

/*
    IS: Tree ada
    FS: Tree ditebang gess tidakkkk kacau

    Creator: Gilang Aditya
*/
void destroy_tree(MusicNode* root);

/*
    IS: Tree sudah terbuat
    FS: children dari sebuah parent ditampilkan

    Creator: Gilang Aditya
*/
void print_children(MusicNode* parent);


/*
    IS: Tree sudah terbuat
    FS: Tree ditampilkan dengan bentuk pre order tapi dari kanan

    Creator: Gilang Aditya
*/
void print_tree(MusicNode* root, int height);


/*
    IS: Tree sudah terbuat 
    FS: Node yang dicari dikembalikan

    Creator: Gilang Aditya
*/
MusicTree search_node(MusicTree root, char* target);


/*
    IS: Nama file yang ingin dicari belum diketahui
    FS: User Mengetik file yang ingin dicari

    Creator: Gilang Aditya
*/
void input_specific_search(MusicTree root);

/*
    IS: Tree Musik ada
    FS: Mengembalikan node music yang dicari

    Creator: Gilang Aditya
*/
MusicTree specific_search(MusicTree root, char* target);


/*
    IS: Node musik yang dicari ada
    FS: Menampilkan music yang dicari dan direktorinya

    Creator: Gilang Aditya
*/
void print_specific_search(MusicTree node);

/*
    IS: Root diketahui 
    FS: children bertambah (music atau driektori)

    Creator: Gilang Aditya
*/
void add_children(MusicTree root, char* ingfo);


#endif