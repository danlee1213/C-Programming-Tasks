
// C implementation of digital clock
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    time_t s = 1; //val = 1;
    struct tm* current_time;

    // time in seconds
    s = time(NULL);

    // to get current time
    current_time = localtime(&s);

    // print time in minutes,
    // hours and seconds
    while(1){
    system("cls");

    printf("%02d:%02d:%02d",
           current_time->tm_hour,
           current_time->tm_min,
           current_time->tm_sec);

    current_time->tm_sec++;

    if(current_time->tm_sec == 60){
        current_time->tm_min += 1;
        current_time->tm_sec = 0;
    }
    if(current_time->tm_min == 60){
        current_time->tm_hour += 1;
        current_time->tm_min = 0;
    }
    if(current_time->tm_hour == 24){
        current_time->tm_hour = 0;
        current_time->tm_min = 0;
        current_time->tm_sec = 0;
    }
    sleep(1);

    }

    return 0;
}
