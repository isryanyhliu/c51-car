#ifndef __CONFIG_H
#define __CONFIG_H

#include <reg52.h>
#include <intrins.h>

// 系统晶振配置
#define MAIN_Fosc   11059200L

// ===================== 循迹传感器引脚 =====================
sbit left_track  = P3^5;   // 左循迹传感器（本实验测得：白=0，黑=1，以实测为准）
sbit right_track = P3^4;   // 右循迹传感器（本实验测得：白=0，黑=1，以实测为准）

// ===================== 电机驱动引脚 =====================
sbit left_pwm   = P1^5;
sbit IN1            = P1^4;
sbit IN2            = P1^3;
sbit IN3            = P1^2;
sbit IN4            = P1^1;
sbit right_pwm  = P1^0;

// ===================== 外设引脚 =====================
sbit beep    = P2^2;   // 蜂鸣器
sbit led1    = P1^6;   // 模式指示灯
sbit led2    = P1^7;   // 状态指示灯
sbit KEY     = P3^3;   // 模式切换按键

// ===================== 电机控制宏 =====================
#define left_motor_go      IN1=1, IN2=0
#define left_motor_back    IN1=0, IN2=1
#define left_motor_stops   IN1=0, IN2=0

#define right_motor_go     IN3=0, IN4=1
#define right_motor_back   IN3=1, IN4=0
#define right_motor_stops  IN3=0, IN4=0

// ===================== 定时器宏 =====================
#define Timer1On       TR1=1
#define Timer1Off      TR1=0
#define EA_on          EA=1

// ===================== PWM 参数 =====================
#define PWM_DUTY        200
#define PWM_HIGH_MIN    70
#define PWM_HIGH_MAX    PWM_DUTY

#endif
