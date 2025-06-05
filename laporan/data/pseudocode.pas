FUNCTION main() -> integer
// kamus
Tree: MusicTree
queue: QueueMusic
handle: PlayerHandle
// algoritma
Tree <- NIL
CreateQueueMusic(address(queue))
populate_tree(address(Tree))
init_music_player(address(handle), address(queue))
print_tree(Tree, 0)

menu(Tree^, address(queue), address(handle))
destroy_tree(Tree)
destroy_queue(address(queue))
destroy_music_player(address(handle))

RETURN 0


ENDFUNCTION

PROCEDURE init_music_player(handle: ^PlayerHandle, music_queue: ^QueueMusic)
// kamus
r: ma_result
// algoritma
handle.music_queue <- music_queue
handle.is_loaded <- false
r <- ma_engine_init(NIL, address(handle.engine))
IF r != MA_SUCCESS THEN
WRITE "Failed to start engine"
exit(1)
ENDIF
handle.thread_handle <- CreateThread(NIL, 0, music_thread, handle, 0, NIL)
ENDPROCEDURE

FUNCTION music_thread(lpParam: ^void) -> DWORD
// kamus
handle: ^PlayerHandle
length: ma_uint64
result: ma_result
stack: Stack
cursor: MusicTree
music_path: ^char
music_path_len: integer
path_buffer: ^char
path_buffer_len: integer
path_len: integer

// algoritma
handle <- lpParam AS ^PlayerHandle
path_buffer_len <- 0
path_len <- 0
CreateEmpty(address(stack))
handle.is_loaded <- false
music_path <- get_music_folder_path()
music_path_len <- strlen(music_path)

WHILE (true) DO
    IF (NOT is_Empty(handle.music_queue^)) AND ((NOT handle.is_loaded) OR (NOT ma_sound_is_playing(address(handle.sound)))) THEN
        IF handle.is_loaded THEN
            ma_sound_stop(address(handle.sound))
            ma_sound_uninit(address(handle.sound))
        ENDIF
        deQueueMusic(handle.music_queue, address(cursor))
        WRITE "\nINFO: Memutar musik %s\n", cursor.name

        path_buffer_len <- 0
        path_len <- 0
        WHILE cursor.parent != NIL DO
            Push(address(stack), cursor)
            path_buffer_len <- path_buffer_len + strlen(cursor.name) + 1
            cursor <- cursor.parent
        ENDWHILE
        path_buffer_len <- path_buffer_len + music_path_len + 1

        path_buffer <- malloc(path_buffer_len) 
        strcpy(path_buffer, music_path)
        path_len <- path_len + music_path_len
        path_buffer[path_len] <- '/'
        path_len <- path_len + 1

        WHILE NOT IsEmpty(stack) DO
            Pop(address(stack), address(cursor))
            strcpy(address(path_buffer[path_len]), cursor.name)
            path_len <- path_len + strlen(cursor.name)
            path_buffer[path_len] <- '/'
            path_len <- path_len + 1
        ENDWHILE
        path_buffer[path_len - 1] <- '\0'

        result <- ma_sound_init_from_file(address(handle.engine), path_buffer, 0, NIL, NIL, address(handle.sound))
        IF result != MA_SUCCESS THEN
            RETURN -1
        ENDIF

        ma_sound_start(address(handle.sound))
        ma_sound_get_length_in_pcm_frames(address(handle.sound), address(length))
        ma_sound_get_length_in_seconds(address(handle.sound), address(handle._current_music_time_in_secs))
        handle.is_loaded <- true
    ENDIF

    IF handle._command != NONE THEN
        SWITCH handle._command
            CASE NONE:
                // Should be unreachable, do nothing
                BREAK 
            CASE REWIND:
                ma_sound_seek_to_pcm_frame(address(handle.sound), 0)
                WRITE "\nINFO: Musik di rewind\n"
                BREAK
            CASE SEEK:
                ma_sound_seek_to_second(address(handle.sound), handle._command_args[0])
                WRITE "\nINFO: Musik di seek ke: "
                second_to_time(handle._command_args[0])
                BREAK
            CASE SKIP:
                ma_sound_seek_to_pcm_frame(address(handle.sound), length)
                ma_sound_stop(address(handle.sound))
                WRITE "\nINFO: Musik di skip\n"
                BREAK
            DEFAULT:
                ASSERT(false)
        ENDSWITCH
        handle._command <- NONE
    ENDIF

    Sleep(16)
ENDWHILE


ENDFUNCTION

FUNCTION get_currently_player_music_length(handle: ^PlayerHandle) -> integer
// kamus
// algoritma
IF NOT handle.is_loaded THEN
RETURN -1
ENDIF
IF NOT ma_sound_is_playing(address(handle.sound)) THEN
RETURN -1
ENDIF

RETURN floor(handle._current_music_time_in_secs)


ENDFUNCTION

PROCEDURE destroy_music_player(handle: ^PlayerHandle)
// kamus
// algoritma
ma_engine_uninit(address(handle.engine))
CloseHandle(handle.thread_handle)
ENDPROCEDURE

PROCEDURE rewind_music(handle: ^PlayerHandle)
// kamus
// algoritma
handle._command <- REWIND
ENDPROCEDURE

PROCEDURE skip_music(handle: ^PlayerHandle)
// kamus
// algoritma
handle._command <- SKIP
ENDPROCEDURE

PROCEDURE seek_music(handle: ^PlayerHandle, secs: integer)
// kamus
// algoritma
handle._command <- SEEK
handle._command_args[0] <- secs
ENDPROCEDURE

FUNCTION end_with_mp3(filename: ^char) -> boolean
// kamus
exit_str: ^char
// algoritma
exit_str <- strrchr(filename, '.')
RETURN exit_str != NIL AND _stricmp(exit_str, ".mp3") = 0
ENDFUNCTION

PROCEDURE read_dir_music(base_path: ^char, root: ^MusicNode)
// kamus
find_data: WIN32_FIND_DATA
hFind: HANDLE
search_path: char[1024]
name: ^char
full_path: char[1024]
child: ^MusicNode
// algoritma
snprintf(search_path, 1024, "%s\*", base_path)

hFind <- FindFirstFile(search_path, address(find_data))

IF hFind = INVALID_HANDLE_VALUE THEN
    WRITE "Gagal membuka direktori: %s\n", base_path
    RETURN
ENDIF

LOOP // Emulates do-while loop
    name <- find_data.cFileName

    IF NOT (strcmp(name, ".") = 0 OR strcmp(name, "..") = 0) THEN
        snprintf(full_path, 1024, "%s\\%s", base_path, name)
        
        IF (find_data.dwFileAttributes (BITWISEAND) FILE_ATTRIBUTE_DIRECTORY) THEN 
            add_children(root, strdup(name))
            
            child <- root.fson
            WHILE child.nbrother != NIL DO
                child <- child.nbrother
            ENDWHILE
            read_dir_music(full_path, child)
        ELSEIF end_with_mp3(name) THEN
            add_children(root, strdup(name))
        ENDIF
    ENDIF
UNTIL NOT FindNextFile(hFind, address(find_data))
ENDLOOP

FindClose(hFind)


ENDPROCEDURE

PROCEDURE populate_tree(root_ptr: ^^MusicNode) 
// kamus
// algoritma
root_ptr^ <- malloc(SIZEOF MusicNode) 
root_ptr^.fson <- NIL
root_ptr^.nbrother <- NIL
root_ptr^.parent <- NIL
root_ptr^.name <- strdup("")
read_dir_music(get_music_folder_path(), root_ptr^)
ENDPROCEDURE

PROCEDURE print_tree(root: ^MusicNode, height: integer)
// kamus
i: integer
// algoritma
IF root = NIL THEN
RETURN
ELSE
FOR i FROM 0 TO height - 1 DO
WRITE " "
ENDFOR
WRITE root.name, NEWLINE 
print_tree(root.fson, height + 2)
print_tree(root.nbrother, height)
ENDIF
ENDPROCEDURE

FUNCTION search_node(root: ^MusicNode, target: ^char) -> ^MusicNode
// kamus
found_in_fson: ^MusicNode
// algoritma
IF root = NIL THEN
RETURN NIL
ENDIF

IF strcmp(root.name, target) = 0 THEN
    RETURN root
ENDIF

found_in_fson <- search_node(root.fson, target)
IF found_in_fson != NIL THEN
    RETURN found_in_fson
ENDIF

RETURN search_node(root.nbrother, target)


ENDFUNCTION

PROCEDURE input_specific_search(root: ^MusicNode)
// kamus
input_str: char[1024]
found: ^MusicNode
idx: integer
// algoritma
WRITE "Masukkan Nama file: "
READ input_str
idx <- strcspn(input_str, "\n") 
input_str[idx] <- '\0' 
found <- specific_search(root, input_str)
IF found != NIL THEN
print_specific_search(found)
ELSE
WRITE "Musik/Direktorimu tidak ditemukan"
ENDIF
ENDPROCEDURE

FUNCTION specific_search(root: ^MusicNode, target: ^char) -> ^MusicNode
// kamus
found: ^MusicNode
// algoritma
IF root = NIL THEN
RETURN NIL
ENDIF

IF strcmp(root.name, target) = 0 THEN
    RETURN root
ENDIF

found <- specific_search(root.fson, target)
IF found != NIL THEN
    RETURN found
ENDIF

RETURN specific_search(root.nbrother, target)


ENDFUNCTION

PROCEDURE print_specific_search(node: ^MusicNode)
// kamus
stack: Stack
current: ^MusicNode
full_path: char[2048]
mn: ^MusicNode
level: integer
temp: ^MusicNode
i: integer
// algoritma
WRITE "Musik/Direktori yang kamu cari yaitu: %s\n", node.name
WRITE "Musik/Direktori tersebut berada di:\n"
CreateEmpty(address(stack))

current <- node

WHILE current != NIL DO
    Push(address(stack), current)
    current <- current.parent 
ENDWHILE

snprintf(full_path, 2048, "%s", get_music_folder_path()) 

WRITE "Music"
WHILE NOT IsEmpty(stack) DO 
    Pop(address(stack), address(mn)) 

    level <- 0
    temp <- mn
    WHILE temp != NIL DO
        level <- level + 1
        temp <- temp.parent
    ENDWHILE
    FOR i FROM 0 TO (level * 2) - 1 DO
        WRITE " "
    ENDFOR
    WRITE mn.name, NEWLINE
ENDWHILE
WRITE NEWLINE


ENDPROCEDURE

PROCEDURE destroy_tree(root: ^MusicNode)
// kamus
// algoritma
IF root = NIL THEN
RETURN
ELSE
destroy_tree(root.fson)
destroy_tree(root.nbrother)
free(root)
ENDIF
ENDPROCEDURE

PROCEDURE print_children(parent: ^MusicNode)
// kamus
child: ^MusicNode
// algoritma
IF parent != NIL THEN
child <- parent.fson
IF child != NIL THEN
WRITE child.name, NEWLINE
WHILE child.nbrother != NIL DO
child <- child.nbrother
WRITE child.name, NEWLINE
ENDWHILE
ELSE
WRITE "Parent tidak memiliki anak\n"
ENDIF
ENDIF
ENDPROCEDURE

PROCEDURE add_children(root: ^MusicNode, ingfo: ^char)
// kamus
new_child: ^MusicNode
temp: ^MusicNode
// algoritma
IF root != NIL THEN
new_child <- malloc(SIZEOF MusicNode)
new_child.name <- ingfo
new_child.fson <- NIL
new_child.nbrother <- NIL
new_child.parent <- root
IF root.fson = NIL THEN
root.fson <- new_child
ELSE
temp <- root.fson
WHILE temp.nbrother != NIL DO
temp <- temp.nbrother
ENDWHILE
temp.nbrother <- new_child
ENDIF
ENDIF
ENDPROCEDURE

PROCEDURE menu(tree: MusicNode, queue: ^QueueMusic, handle: ^PlayerHandle)
// kamus
x: integer
// algoritma
WHILE (true) DO
WRITE "1. Lihat Musik\n2. Tambahkan musik ke queue\n3. Skip\n4. Replay\n5. Seek\n6. Check Queue\n7. Search Musik\n8. Keluar\nMasukkan pilihan: "
READ x
// getchar() is typically for consuming newline, omitted in pseudocode
SWITCH x
CASE 1:
view_music(tree)
BREAK
CASE 2:
add_music(tree, queue)
BREAK
CASE 3:
skip(handle)
BREAK
CASE 4:
replay(handle)
BREAK
CASE 5:
seek(handle)
BREAK
CASE 6:
PrintQueueMusic(queue^)
getch()
BREAK
CASE 7:
input_specific_search(address(tree))
getchar()
BREAK
CASE 8:
return
DEFAULT:
BREAK
ENDSWITCH
system("cls")
ENDWHILE
ENDPROCEDURE

PROCEDURE view_music(tree: MusicNode)
// kamus
// algoritma
system("cls")
WRITE "Music"
print_tree(address(tree), 0)
getch()
ENDPROCEDURE

PROCEDURE add_music(tree: MusicNode, queue: ^QueueMusic)
// kamus
x: char[1024]
temp1, temp2: MusicTree
len: integer
// algoritma
temp1 <- address(tree)
temp2 <- temp1
WHILE (true) DO
print_children(temp1)
WRITE "Masukkan nama musik atau folder: "
READ x
len <- strlen(x)
x[len - 1] <- '\0'
temp1 <- search_node(temp1, x) 
// Example was temp1 = search_node(temp1, x) -> temp1 <- search_node(temp1, x)
// The example's final search_node(address(tree),x) had a semicolon.
// This implies standalone calls get semicolons.
IF temp1 = NIL THEN
WRITE "Tidak ada file/direktori tersebut\n"
temp1 <- temp2
getch()
continue
ENDIF

IF len >= 5 THEN
        IF strcmp(address(x[len - 5]), ".mp3") = 0 THEN 
            EnQueueMusic(queue, temp1)
            WRITE "Lagu %s berhasil dimasukkan\n", temp1->name
            getch()
            return
        ELSE
            temp2 <- temp1
        ENDIF
    ENDIF
    system("cls")
ENDWHILE
search_node(address(tree), x) 


ENDPROCEDURE

PROCEDURE skip(handle: ^PlayerHandle)
// kamus
// algoritma
skip_music(handle)
ENDPROCEDURE

PROCEDURE replay(handle: ^PlayerHandle)
// kamus
// algoritma
rewind_music(handle)
ENDPROCEDURE

PROCEDURE seek(handle: ^PlayerHandle)
// kamus
second: integer
detik: integer
waktu: char[10]
i: integer
// algoritma
second <- get_currently_player_music_length(handle)
detik <- -1

IF second = -1 THEN
    WRITE "\nTidak ada musik yang sedang dijalankan\n"
    getch()
    return
ENDIF

loop:
WHILE (detik < 0) OR (detik > second) DO
    system("cls")
    WRITE "Panjang lagu saat ini: "
    second_to_time(second)
    WRITE "Contoh waktu seek:\n12 (detik saja)\n2:52 (menit:detik)\n1:53:23 (jam:menit:detik)\n"
    WRITE "Masukkan detik ke berapa: "
    READ waktu
    i <- 0
    WHILE waktu[i] != '\0' DO
        IF (NOT isdigit(waktu[i])) AND (waktu[i] != ':') THEN
            WRITE "Hanya masukkan angka atau ':'\n"
            getch()
            GOTO loop
        ENDIF
        i <- i + 1
    ENDWHILE
    detik <- time_to_second(waktu)
    IF detik > second THEN
        WRITE "Waktu yang diinputkan melebihi waktu lagu\n"
        getch()
        continue
    ENDIF
ENDWHILE
seek_music(handle, detik)


ENDPROCEDURE

FUNCTION hour_to_second(hour: integer) -> integer
// kamus
// algoritma
RETURN hour * 3600
ENDFUNCTION

FUNCTION minute_to_second(minute: integer) -> integer
// kamus
// algoritma
RETURN minute * 60
ENDFUNCTION

FUNCTION second_to_hour(second: ^integer) -> integer
// kamus
hour: integer
// algoritma
hour <- 0
hour <- second^ / 3600
second^ <- second^ MOD 3600
RETURN hour
ENDFUNCTION

FUNCTION second_to_minute(second: ^integer) -> integer
// kamus
minute: integer
// algoritma
minute <- 0
minute <- second^ / 60
second^ <- second^ MOD 60
RETURN minute
ENDFUNCTION

PROCEDURE second_to_time(second_param: integer) 
// kamus
hour: integer
minute: integer
second_local: integer 
// algoritma
second_local <- second_param
hour <- second_to_hour(address(second_local))
minute <- second_to_minute(address(second_local))
IF hour != 0 THEN
WRITE "%02d:%02d:%02d\n", hour, minute, second_local
ELSEIF minute != 0 THEN
WRITE "%02d:%02d\n", minute, second_local
ELSE
WRITE "%02d\n", second_local
ENDIF
ENDPROCEDURE

FUNCTION time_to_second(time: char[10]) -> integer
// kamus
len: integer
second: integer
minute: integer
hour: integer
totalsec: integer
colonCount: integer
i: integer
// algoritma
len <- strlen(time)
totalsec <- 0
colonCount <- 0
FOR i FROM 0 TO len - 1 DO
IF time[i] = ':' THEN
colonCount <- colonCount + 1
ENDIF
ENDFOR

IF colonCount = 2 THEN
    sscanf(time, "%d:%d:%d", address(hour), address(minute), address(second))
    totalsec <- totalsec + hour_to_second(hour)
    totalsec <- totalsec + minute_to_second(minute)
    totalsec <- totalsec + second
ELSEIF colonCount = 1 THEN
    sscanf(time, "%d:%d", address(minute), address(second))
    totalsec <- totalsec + minute_to_second(minute)
    totalsec <- totalsec + second
ELSE
    sscanf(time, "%d", address(second))
    totalsec <- totalsec + second
ENDIF

RETURN totalsec


ENDFUNCTION