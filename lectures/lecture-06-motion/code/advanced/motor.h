#ifndef __MOTOR_H
#define __MOTOR_H

#include <reg52.h>

// 小车硬件引脚（和你主板完全匹配）
sbit Left_moto_pwm  = P1^5;  // ENA 左电机PWM
sbit IN1            = P1^4;  // 左电机方向
sbit IN2            = P1^3;
sbit IN3            = P1^2;  // 右电机方向
sbit IN4            = P1^1;
sbit Right_moto_pwm = P1^0;  // ENB 右电机PWM

// 函数声明
void Motor_Init(void);       // 电机+定时器初始化
void Left_Forward(void);     // 左电机正转
void Right_Forward(void);    // 右电机正转
void Left_Stop(void);        // 左电机停止
void Right_Stop(void);       // 右电机停止
void Motor_SetSpeed(unsigned char left, unsigned char right); // 设置PWM占空比 0~100

#endif