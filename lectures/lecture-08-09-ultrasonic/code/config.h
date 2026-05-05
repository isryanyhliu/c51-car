#ifndef __CONFIG_H
#define __CONFIG_H

#include <reg52.h>	   // 51单片机标准头文件
#include <intrins.h>   // 作用：提供_nop_()函数实现精确延时。原理：_nop_()函数执行时占用一个机器周期（12个时钟周期），在11.0592MHz晶振下约1.085微秒。

// ===================== 晶振定义 =====================
#define MAIN_Fosc 11059200L  // 晶振11.0592MHz

// ===================== 超声波引脚定义 =====================
sbit TrigPin  = P1^0;  // 超声波触发引脚（输出）
sbit EchoPin  = P1^1;  // 超声波回响引脚（输入）

// ===================== 电机引脚定义 =====================
sbit Left_moto_pwm   = P2^0;   // 左电机PWM控制
sbit Right_moto_pwm  = P2^1;   // 右电机PWM控制
sbit left_motor_go   = P2^2;   // 左电机前进
sbit left_motor_back = P2^3;   // 左电机后退
sbit right_motor_go  = P2^4;   // 右电机前进
sbit right_motor_back= P2^5;   // 右电机后退

// ===================== 蜂鸣器/LED引脚 =====================
sbit beep = P3^7;    // 蜂鸣器引脚
sbit LED1 = P3^0;    // 状态LED
sbit LED2 = P3^1;

// ===================== PWM参数定义 =====================
#define PWM_DUTY      200    // PWM周期
#define PWM_HIGH_MIN   70     // 最小占空比
#define PWM_HIGH_MAX   PWM_DUTY // 最大占空比

#endif