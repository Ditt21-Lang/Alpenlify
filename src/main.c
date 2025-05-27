#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include "util.h"
#include "player.h"
#include "tree.h"

int main() {
    MusicTree Tree, test;
    Tree = NULL;
    populate_tree(&Tree);
    init_music_player(NULL);
    print_children(Tree->fson);
    test = search_node(Tree, "Dangdut");
    printf("%s\n", test->name);
    print_tree(Tree, 0);

    getchar();

    destroy_music_player();

    return 0;
}