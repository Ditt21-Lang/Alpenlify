#include "ui.h"

/*
    IS: Terminal kosong
    FS: Terminal menampilkan pilihan menu dan menanyakan pilihan user

    Creator: Raf
*/

void menu(MusicNode tree, QueueMusic *queue, PlayerHandle *handle){
    int x;
    while(1){
        printf("1. Lihat Musik\n2. Tambahkan musik ke queue\n3. Skip\n4. Replay\n5. Seek\n6. Keluar\n7. Check Queue\nMasukkan pilihan: ");
        scanf("%d", &x);
        switch(x){
        case 1: view_music(tree);break;
        case 2: add_music(tree,queue);break;
        case 3: skip(handle); break;
        case 4: replay(handle); break;
        case 5: seek(handle); break;
        case 6: return;
        case 7: PrintQueueMusic(*queue);
                getch();
                break;
        default: break;
    }
    system("cls");
    }
}

/*
    IS: Tree tidak kosong  
    FS: Tree ditampilkan ke layar

    Creator: Raf
*/

void view_music(MusicNode tree){
    system("cls");
    printf("Music");
    print_tree(&tree, 0);
    getch();
}

/*
    IS: Queue mungkin kosong
    FS: Musik dalam queue bertambah 

    Creator: Raf
*/

void add_music(MusicNode tree, QueueMusic *queue){
    char x[100];
    MusicTree temp1, temp2;
    temp1 = &tree;
    temp2 = temp1;
    while(1){
        print_children(temp1);
        printf("Masukkan nama musik atau folder: ");
        fgets(x, 100, stdin);
        int len = strlen(x);
        x[len-1] = '\0';
        temp1 = search_node(temp1, x);
        if(temp1==NULL){
            printf("Tidak ada file/direktori tersebut\n");
            temp1 = temp2;
            getch();
            continue;
        }
        if(len>=5){
            if (strcmp(&x[len - 5], ".mp3") == 0) {
                EnQueueMusic(queue,temp1);
                printf("Lagu %s berhasil dimasukkan\n", temp1->name);
                getch();
                return;
            } else {
                temp2 = temp1;
            }
        
        }
    system("cls");
    }
    search_node(&tree,x);
}

/*
    IS: Musik dijalankan
    FS: Musik dihentikan dan lanjut ke music berikutnya di queue jika ada

    Creator: Raf
*/

void skip(PlayerHandle *handle){
    skip_music(handle);
}

/*
    IS: Musik berjalan
    FS: Musik diulang dari awal

    Creator:Raf
*/

void replay(PlayerHandle *handle){
    rewind_music(handle);
}

/*
    IS: Musik berjalan
    FS: Musik berjalan di detik yang ditentukan

    Creator:Raff
*/

void seek(PlayerHandle *handle){
    int second = get_currently_player_music_length(handle);
    int detik = -1;
    char waktu[10];
    loop:
    while(detik < 0 || detik > second){
        system("cls");
        printf("Panjang lagu saat ini: ");
        second_to_time(second);
        printf("Contoh waktu seek:\n12 (detik saja)\n2:52 (menit:detik)\n1:53:23 (jam:menit:detik)\n");
        printf("Masukkan detik ke berapa: ");
        scanf("%s", waktu);
        for(int i=0;waktu[i]!='\0';i++){
            if(!isdigit(waktu[i]) && waktu[i] != ':'){
                printf("Hanya masukkan angka atau ':'\n");
                getch();
                goto loop;
            }
        }
        detik = time_to_second(waktu);
        if(detik > second){
            printf("Waktu yang diinputkan melebihi waktu lagu\n");
            getch();
            continue;
        }
    }
    seek_music(handle, detik);
}
