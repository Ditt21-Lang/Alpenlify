#include "tree.h"
#include <string.h>

MusicTree search_node(MusicTree root, char* target){
    if (root == NULL){
        return NULL;
    }
    
    if (strcmp(root->name, target) == 0){
        return root;
    }

    MusicTree found_in_fson = search_node(root->fson, target);
    if (found_in_fson != NULL){
        return found_in_fson;
    }
    
    return search_node(root->nbrother, target);
}

void destory_tree(MusicNode* root){
    if (root == NULL){
        return;
    } else {
        destroy_tree(root->fson);
        destory_tree(root->nbrother);
        free(root);
    }
}