#include "tree.h"
#include "util.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

boolean end_with_mp3(const char *filename){
    const char *exit = strrchr(filename, '.');
    return exit && _stricmp(exit, ".mp3") == 0;
}

void read_dir_music(const char *base_path, MusicNode* root){
    WIN32_FIND_DATA find_data;
    HANDLE hFind;

    char search_path[1024];
    snprintf(search_path, sizeof(search_path), "%s\\*", base_path);

    hFind = FindFirstFile(search_path, &find_data);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Gagal membuka direktori: %s\n", base_path);
        return;
    }

    do {
         const char *name = find_data.cFileName;

        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
            continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s\\%s", base_path, name);
        
        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            add_children(root, strdup(name));
            
            MusicNode* child = root->fson;
            while (child->nbrother != NULL){
                child = child->nbrother;
            }
            read_dir_music(full_path, child);
        } else if (end_with_mp3(name)){
            add_children(root, strdup(name));
        }


    } while (FindNextFile(hFind, &find_data));

    FindClose(hFind);
}


void populate_tree(MusicNode** root){
    *root = (MusicNode*)malloc(sizeof(MusicNode));
    (*root)->fson = NULL;
    (*root)->nbrother = NULL;
    (*root)->parent = NULL;
    (*root)->name = strdup("");
    read_dir_music(get_music_folder_path(), *root);
}

void print_tree(MusicNode* root, int height){
    if(root == NULL){
        return;
    } else {
        for (int i = 0; i < height; i++){
            printf(" ");
        }
        printf("%s\n", root->name);
        print_tree(root->fson, height + 2);
        print_tree(root->nbrother, height);
    }
}

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

void specific_search(MusicTree root){
    char input[1024];
    MusicTree found;
    printf("Masukkan Nama file: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    found = search_node(root, input);
    if(found != NULL){
        print_specific_search(found);
    } else {
        printf("Musik/Direktorimu tidak ditemukan");
    }
        
}

void print_specific_search(MusicTree node){
    
    printf("Musik/Direktori yang kamu cari yaitu: %s\n", node->name);
    printf("Musik/Direktori tersebut berada di:\n");
    Stack stack;
    CreateEmpty(&stack);
    
    MusicNode *current = node;

    while (current != NULL){
        Push(&stack, current);
        current = current->parent; 
    }
    
    MusicNode *mn;
    printf("Music");
    while (!IsEmpty(stack)){
        Pop(&stack, &mn);

        int level = 0;
        MusicNode* temp = mn;
        while (temp != NULL){
            level = level + 1;
            temp = temp->parent;
        }
        for(int i = 0; i < level * 2; i++){
            printf(" ");
        }
        printf("%s\n", mn->name);

    }
    printf("\n");
}

void destroy_tree(MusicNode* root){
    if (root == NULL){
        return;
    } else {
        destroy_tree(root->fson);
        destroy_tree(root->nbrother);
        free(root);
    }
}

void print_children(MusicNode* parent){
    if (parent != NULL){
        MusicNode* child = parent->fson;
        if(child != NULL){
            printf("%s\n", child->name);
            while (child->nbrother != NULL){
                child = child->nbrother;
                printf("%s\n", child->name);
            }
        } else {
            printf("Parent tidak memiliki anak\n");
        }
    }
}

void add_children(MusicTree root, char* ingfo){
    if(root != NULL){
        MusicNode* new_child = (MusicNode*)malloc(sizeof(MusicNode));
        new_child->name = ingfo;
        new_child->fson = NULL;
        new_child->nbrother = NULL;
        new_child->parent = root;
        if(root->fson == NULL){
            root->fson = new_child;
        } else {
            MusicNode* temp = root->fson;
            while (temp->nbrother != NULL){
                temp = temp->nbrother;
            }
            temp->nbrother = new_child;
        }
    }
}