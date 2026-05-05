#ifndef __TIMER_H
#define __TIMER_H
#include "config.h"

// 全局变量声明（PWM调速用）
extern unsigned char pwm_val_left,pwm_val_right;
extern unsigned char pwm_left,pwm_right;

void Timer0_Init(void);  // 定时器0初始化（PWM电机控制）
void Timer1_Init(void);  // 定时器1初始化（超声波计时）
void LoadPWM(void);      // PWM占空比配置

#endif