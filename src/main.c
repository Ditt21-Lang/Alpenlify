#include <stdio.h>
#include "util.h"

int main() {
    char *f = get_music_folder_path();
    printf("%s\n", f);
    return 0;
}