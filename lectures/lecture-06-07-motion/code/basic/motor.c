#include "motor.h"


// 初始化：所有引脚默认为0
void Motor_Init(void)
{
    Left_moto_pwm  = 0;
    Right_moto_pwm = 0;
    IN1 = 0; 
    IN2 = 0;
    IN3 = 0; 
    IN4 = 0;
}

// 左电机正转
void Left_Forward(void)
{
    IN1 = 1;
    IN2 = 0;
}

// 左电机反转
void Left_Backward(void)
{
    IN1 = 0;
    IN2 = 1;
}

// 左电机停止
void Left_Stop(void)
{
    IN1 = 0;
    IN2 = 0;
}

// 右电机正转
void Right_Forward(void)
{
    IN3 = 0;
    IN4 = 1;
}

// 右电机反转
void Right_Backward(void)
{
    IN3 = 1;
    IN4 = 0;
}

// 右电机停止
void Right_Stop(void)
{
    IN3 = 0;
    IN4 = 0;
}



void Delay_us(unsigned int t)
{
    while(t--);
}

// PWM调速核心函数
void Motor_Run(unsigned char left_speed, unsigned char right_speed)
{
    // 左电机PWM
    Left_moto_pwm = 1;
    Delay_us(left_speed);
    Left_moto_pwm = 0;
    Delay_us(100 - left_speed);

    // 右电机PWM
    Right_moto_pwm = 1;
    Delay_us(right_speed);
    Right_moto_pwm = 0;
    Delay_us(100 - right_speed);
}
