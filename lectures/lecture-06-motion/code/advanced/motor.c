#include "motor.h"

// PWM占空比变量（0~100）
unsigned char left_duty  = 0;
unsigned char right_duty = 0;

// 定时器0初始化（11.0592M晶振，PWM周期固定）
void Motor_Init(void)
{
    // 定时器模式1：16位定时器
    TMOD |= 0x01;
    // 初值：定时200us，PWM周期稳定
    TH0  = 0xFF;
    TL0  = 0x9C;
    // 开中断+启动定时器
    ET0  = 1;
    TR0  = 1;
    EA   = 1;  // 总中断
    
    // 电机引脚初始状态
    Left_moto_pwm  = 0;
    Right_moto_pwm = 0;
    IN1 = 0; IN2 = 0;
    IN3 = 0; IN4 = 0;
}

// 方向控制函数
void Left_Forward(void)  { IN1 = 1; IN2 = 0; }
void Right_Forward(void) { IN3 = 0; IN4 = 1; }
void Left_Stop(void)     { IN1 = 0; IN2 = 0; }
void Right_Stop(void)    { IN3 = 0; IN4 = 0; }

// 设置电机速度（0~100）
void Motor_SetSpeed(unsigned char left, unsigned char right)
{
    left_duty  = left;
    right_duty = right;
}

// ======================
// 定时器0中断 → 自动生成PWM
// ======================
void Timer0_ISR(void) interrupt 1
{
    static unsigned char pwm_cnt = 0;
    // 重装初值
    TH0 = 0xFF;
    TL0 = 0x9C;
    
    pwm_cnt++;
    if(pwm_cnt >= 100) pwm_cnt = 0;
    
    // 左电机PWM输出
    Left_moto_pwm  = (pwm_cnt < left_duty)  ? 1 : 0;
    // 右电机PWM输出
    Right_moto_pwm = (pwm_cnt < right_duty) ? 1 : 0;
}