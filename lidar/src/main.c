#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
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

    FILE* pin = fopen("/sys/class/gpio/gpio11/value", "w");

    for(int i = 0; i < 250; i++)
    {
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = (long) (1000000 * atof(argv[1]));

        fseek(pin, 0, 0);
        fwrite("1", sizeof(char), 1, pin);
        fflush(pin);

        nanosleep(&ts,NULL);

        fseek(pin, 0, 0);
        fwrite("0", sizeof(char), 1, pin);
        fflush(pin);

        ts.tv_nsec = 20000000 - ts.tv_nsec;
        nanosleep(&ts,NULL);
    }

    fclose(pin);

    FILE* unexport = fopen("/sys/class/gpio/unexport", "w");

    if(!fwrite("11", sizeof(char), 2, unexport))
        printf("Could not unexport the gpio pin");
    fflush(unexport);

    fclose(unexport);
}