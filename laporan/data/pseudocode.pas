procedure init_music_player(MusicQueue: ^QueueMusic);
var
  R: ma_result;
algoritma
  R <- ma_engine_init(nil, _music_engine);
  if R != MA_SUCCESS then
    WriteLn('Failed to start engine');
    exit(1);
  endif;

  _thread_handle <- CreateThread(nil, 0, music_thread, MusicQueue, 0, nil);
endprocedure;
procedure destroy_music_player()
algoritma
    ma_engine_uninit(address(_music_engine));
    CloseHandle(_thread_handle);
endprocedure
