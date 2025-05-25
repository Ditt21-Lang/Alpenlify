#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include "util.h"
#include "player.h"

int main() {
    char *music_path = get_music_folder_path();
    printf("%s", music_path);
    init_music_player(NULL);
    
    getchar();

    destroy_music_player();

    return 0;
}