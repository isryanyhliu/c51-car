#ifndef __MOTOR_H
#define __MOTOR_H
#include "config.h"

// 电机停止宏
#define left_motor_stops   {left_motor_go=1;left_motor_back=1;}
#define right_motor_stops  {right_motor_go=1;right_motor_back=1;}

void forward(unsigned char LeftSpeed,unsigned char RightSpeed);
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed);
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed);
void back_run(unsigned char LeftSpeed,unsigned char RightSpeed);
void stop(void);

#endif