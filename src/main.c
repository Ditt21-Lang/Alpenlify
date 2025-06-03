#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include "util.h"
#include "player.h"
#include "tree.h"
#include "ui.h"

int main() {
    MusicTree Tree;
    QueueMusic queue;
    Tree = NULL;
    CreateQueueMusic(&queue);
    populate_tree(&Tree);
    init_music_player(&queue);
    print_tree(Tree, 4);

    // print_children(Tree->fson);
    // test = search_node(Tree, "Dangdut");
    // printf("%s\n", test->name);
    // print_tree(Tree, 0);

    menu(*Tree,&queue);
    destroy_tree(Tree);
    destroy_queue(&queue);
    destroy_music_player();

    return 0;
}