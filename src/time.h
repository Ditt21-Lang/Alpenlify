#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <stdlib.h>
#include "player.h"

/*
    IS: Detik diketahui
    FS: Jam diketahui

    Creator:Raff
*/

int hour_to_second(int hour);

/*
    IS: Menit diketahui
    FS: Jam diketahui

    Creator:Raff
*/

int minute_to_second(int minute);

/*
    IS: Detik diketahui
    FS: Menit diketahui

    Creator:Raff
*/

int second_to_minute(int *second);

/*
    IS: Menit diketahui
    FS: Jam diketahui

    Creator:Raff
*/

int second_to_hour(int *second);

/*
    IS: Detik diketahui 
    FS: Waktu dengan format jam:menit:detik diketahui

    Creator:Raff
*/

void second_to_time(int second);

/*
    IS: Waktu dengan format jam:menit:detik atau menit:detik atau detik diketahui
    FS: Detik dikethui

    Creator:Raff
*/

int time_to_second(char time[10]);

#endif