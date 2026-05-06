#ifndef __CONFIG_H
#define __CONFIG_H

#include <reg52.h>
#include <intrins.h>

// 系统晶振配置
#define MAIN_Fosc   11059200L  

// ===================== 超声波引脚 =====================
sbit TrigPin   = P2^1;   // 触发信号
sbit EchoPin   = P2^0;   // 回声信号

// ===================== 电机驱动引脚 =====================
sbit Left_moto_pwm  = P1^5;
sbit IN1            = P1^4;
sbit IN2            = P1^3;
sbit IN3            = P1^2;
sbit IN4            = P1^1;
sbit Right_moto_pwm = P1^0;

// ===================== 外设引脚 =====================
sbit beep    = P2^2;   // 蜂鸣器
sbit LED1    = P1^6;   // 无障指示灯
sbit LED2    = P1^7;   // 障碍报警灯

// ===================== 电机控制宏定义 =====================
#define left_motor_go      IN1=1; IN2=0
#define left_motor_back    IN1=0; IN2=1
#define left_motor_stops   IN1=0; IN2=0

#define right_motor_go     IN3=0; IN4=1
#define right_motor_back   IN3=1; IN4=0
#define right_motor_stops  IN3=0; IN4=0

// ===================== 定时器宏 =====================
#define Timer1On       TR1=1
#define Timer1Off      TR1=0
#define EA_on          EA=1

// ===================== PWM参数 =====================
#define PWM_DUTY        200
#define PWM_HIGH_MIN    70
#define PWM_HIGH_MAX    PWM_DUTY

#endif