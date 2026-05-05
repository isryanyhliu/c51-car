#ifndef __MOTOR_H
#define __MOTOR_H

#include <reg52.h>

// 硬件引脚定义
sbit Left_moto_pwm  = P1^5;
sbit IN1            = P1^4;
sbit IN2            = P1^3;
sbit IN3            = P1^2;
sbit IN4            = P1^1;
sbit Right_moto_pwm = P1^0;

// 函数声明（ANSI 标准格式）
void Motor_Init(void);
void Left_Forward(void);
void Right_Forward(void);
void Left_Stop(void);
void Right_Stop(void);
void Motor_Run(unsigned char left_speed, unsigned char right_speed);
void Delay_us(unsigned int t);

#endif