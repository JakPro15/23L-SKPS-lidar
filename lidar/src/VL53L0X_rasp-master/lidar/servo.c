#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include "servo.h"

#define DELAY 0

FILE* pin_initialize(void)
{
    FILE* export = fopen("/sys/class/gpio/export", "w");

    if(!fwrite("11", sizeof(char), 2, export))
        printf("Could not export the gpio pin");
    fflush(export);
    fclose(export);

    FILE* direction = fopen("/sys/class/gpio/gpio11/direction", "w");

    if(!fwrite("low", sizeof(char), 3, export))
        printf("Could not set the pin direction");
    fflush(direction);
    fclose(direction);

    return fopen("/sys/class/gpio/gpio11/value", "w");
}

void pin_cleanup(FILE* pin)
{
    fclose(pin);

    FILE* unexport = fopen("/sys/class/gpio/unexport", "w");

    if(!fwrite("11", sizeof(char), 2, unexport))
        printf("Could not unexport the gpio pin");
    fflush(unexport);

    fclose(unexport);
}

void servo_rotate(double angle, int repeat, FILE* pin)
{
    if(angle > 270 || angle < 0)
        return;

    // struct timeval tval_before, tval_after, tval_result;

    struct timespec ts;
    ts.tv_sec = 0;
    
    long time_up = (long) (((angle / 135) + 0.5 - DELAY) * 1000000);
    long time_down = (20 - 2 * DELAY) * 1000000 - time_up;

    for(int i = 0; i < repeat; i++)
    {
        // gettimeofday(&tval_before, NULL);

        ts.tv_nsec = time_up;

        fseek(pin, 0, 0);
        fwrite("1", sizeof(char), 1, pin);
        fflush(pin);

        nanosleep(&ts, NULL);

        // gettimeofday(&tval_after, NULL);
        // timersub(&tval_after, &tval_before, &tval_result);
        // printf("1: %f\n", (double)tval_result.tv_usec / 1000);

        // gettimeofday(&tval_before, NULL);

        fseek(pin, 0, 0);
        fwrite("0", sizeof(char), 1, pin);
        fflush(pin);

        ts.tv_nsec = time_down;
        nanosleep(&ts, NULL);

        // gettimeofday(&tval_after, NULL);
        // timersub(&tval_after, &tval_before, &tval_result);
        // printf("1: %f\n", (double)tval_result.tv_usec / 1000);
    }
}
