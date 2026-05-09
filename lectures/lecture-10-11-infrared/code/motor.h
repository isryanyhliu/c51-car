#ifndef __MOTOR_H
#define __MOTOR_H
#include "config.h"

void forward(unsigned char LeftSpeed, unsigned char RightSpeed);
void back_run(unsigned char LeftSpeed, unsigned char RightSpeed);
void left_run(unsigned char LeftSpeed, unsigned char RightSpeed);
void right_run(unsigned char LeftSpeed, unsigned char RightSpeed);
void stop(void);

#endif
