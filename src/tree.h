#ifndef TREE_H
#define TREE_H
#include "player.h"

/*
    IS: Tree belum ada
    FS: Tree ada dengan isi direktori musik user

    Creator: Gilag
*/
void populate_tree(MusicNode* root);

/*
    IS: Tree ada
    FS: Tree ditebang gess tidakkkk kacau

    Creator: Gilag
*/
void destory_tree(MusicNode* root);

/*
    IS: Tree sudah terbuat
    FS: children sari sebuah parent ditampilkan

    Creator:Gilag
*/
void print_children(MusicNode parent);


/*
    IS: Tree sudah terbuat
    FS: Tree ditampilkan dengan bentuk pre order tapi dari kanan

    Creator: Gilag
*/
void print_tree(MusicNode root, int height);


/*
    IS: Tree sudah terbuat 
    FS: Node yang dicari dikembalikan

    Creator: Gilag
*/
MusicNode search_node(MusicNode root, char* target);


/*
    IS: Root diketahui 
    FS: children bertambah (music atau driektori)

    Creator: Gilag
*/
void add_children(MusicNode* root, char* ingfo);


#endif