#include <stdio.h>


FILE* pin_initialize(void);
void pin_cleanup(FILE* pin);
void servo_rotate(double angle, int repeat, FILE* pin);
