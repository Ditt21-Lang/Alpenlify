#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include "util.h"
#include "player.h"

int main() {

    init_music_player(NULL);

    destroy_music_player();

    return 0;
}