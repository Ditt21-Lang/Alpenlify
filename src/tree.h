#ifndef TREE_H
#define TREE_H
#include "player.h"

/*
    IS: Tree belum ada
    FS: Tree ada dengan isi direktori musik user

    Creator: Gilang Aditya
*/
void populate_tree(MusicNode* root);

/*
    IS: Tree ada
    FS: Tree ditebang gess tidakkkk kacau

    Creator: Gilang Aditya
*/
void destory_tree(MusicNode* root);

/*
    IS: Tree sudah terbuat
    FS: children sari sebuah parent ditampilkan

    Creator: Gilang Aditya
*/
void print_children(MusicNode parent);


/*
    IS: Tree sudah terbuat
    FS: Tree ditampilkan dengan bentuk pre order tapi dari kanan

    Creator: Gilang Aditya
*/
void print_tree(MusicNode root, int height);


/*
    IS: Tree sudah terbuat 
    FS: Node yang dicari dikembalikan

    Creator: Gilang Aditya
*/
MusicNode search_node(MusicNode root, char* target);


/*
    IS: Root diketahui 
    FS: children bertambah (music atau driektori)

    Creator: Gilang Aditya
*/
void add_children(MusicNode* root, char* ingfo);


#endif