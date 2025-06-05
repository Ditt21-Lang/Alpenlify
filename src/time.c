#include "time.h"

/*
    IS: Detik diketahui
    FS: Jam diketahui

    Creator:Raff
*/

int hour_to_second(int hour){
    return hour*3600;
}

/*
    IS: Menit diketahui
    FS: Jam diketahui

    Creator:Raff
*/

int minute_to_second(int minute){
    return minute*60;
}

/*
    IS: Detik diketahui
    FS: Menit diketahui

    Creator:Raff
*/

int second_to_hour(int *second){
    int hour = 0;
    hour = *second/3600;
    *second = *second%3600;
    return hour;
}

/*
    IS: Menit diketahui
    FS: Jam diketahui

    Creator:Raff
*/

int second_to_minute(int *second){
    int minute = 0;
    minute = *second/60;
    *second = *second%60;
    return minute;
}

/*
    IS: Detik diketahui 
    FS: Waktu dengan format jam:menit:detik diketahui

    Creator:Raff
*/

void second_to_time(int second){
    int hour = second_to_hour(&second);
    int minute = second_to_minute(&second);
    if(hour!=0){
        printf("%02d:%02d:%02d\n", hour, minute, second);
    } else if (minute!=0){
        printf("%02d:%02d\n", minute, second);
    } else {
        printf("%02d\n", second);
    }
}

/*
    IS: Waktu dengan format jam:menit:detik atau menit:detik atau detik diketahui
    FS: Detik dikethui

    Creator:Raff
*/

int time_to_second(char time[10]){
    int len = strlen(time);
    int second, minute, hour;
    int totalsec=0;
    int colonCount = 0;
    for(int i=0;i<len;i++){
        if(time[i] == ':'){
            colonCount++;
        }
    }
    if(colonCount==2){
        sscanf(time, "%d:%d:%d", &hour, &minute, &second);
        totalsec += hour_to_second(hour);
        totalsec += minute_to_second(minute);
        totalsec += second;
    } else if (colonCount==1){
        sscanf(time, "%d:%d", &minute, &second);
        totalsec += minute_to_second(minute);
        totalsec += second;
    } else {
        sscanf(time, "%d", &second);
        totalsec += second;
    }
    
    return totalsec;
}