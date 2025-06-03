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
    int colonCount=0;
    char num[2];
    int temp;
    int second = 0;
    for(int i=0;i<len;i++){
        if(time[i] == ':'){
            colonCount++;
        }
    }
    if(colonCount>=2){
        num[0] = time[0];
        num[1] = time[1];
        temp = atoi(num);
        second += hour_to_second(temp);
        num[0] = time[3];
        num[1] = time[4];
        temp = atoi(num);
        second += minute_to_second(temp);
        num[0] = time[6];
        num[1] = time[7];
        second += atoi(num);
    } else if (colonCount>=1){
        num[0] = time[0];
        num[1] = time[1];
        temp = atoi(num);
        second += minute_to_second(temp);
        num[0] = time[3];
        num[1] = time[4];
        second += atoi(num);
    } else {
        num[0] = time[0];
        num[1] = time[1];
        second += atoi(num);
    }
    
    return second;
}