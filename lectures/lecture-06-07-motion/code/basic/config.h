#ifndef __CONFIG_H
#define __CONFIG_H

#include <reg52.h>

// ===================== 电机驱动引脚 =====================
sbit Left_moto_pwm  = P1^5;  // ENA 左电机PWM
sbit IN1            = P1^4;  // 左电机方向
sbit IN2            = P1^3;
sbit IN3            = P1^2;  // 右电机方向
sbit IN4            = P1^1;
sbit Right_moto_pwm = P1^0;  // ENB 右电机PWM

#endif
