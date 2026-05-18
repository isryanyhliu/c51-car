#include "timer.h"

extern unsigned char pwm_val_left, pwm_val_right;
extern unsigned char pwm_left, pwm_right;
extern bit Timer1Overflow;

void Timer0_Init(void)
{
    TMOD |= 0x02;   // 定时器0，8位自动重装
    TH0 = 164;
    TL0 = 164;       // 11.0592MHz，约100us中断
    TR0 = 1;
    ET0 = 1;         // 允许定时器0中断

    // 初始化电机方向引脚为低电平（确保电机初始不转）
    IN1 = 0; IN2 = 0;
    IN3 = 0; IN4 = 0;
    Left_moto_pwm  = 0;
    Right_moto_pwm = 0;
}

/* 定时器0中断：生成 PWM（示例代码） */
void timer0_int(void) interrupt 1
{
    pwm_val_left++;
    pwm_val_right++;

    if (pwm_val_left <= pwm_left)
        Left_moto_pwm = 1;
    else
        Left_moto_pwm = 0;

    if (pwm_val_left >= PWM_DUTY)
        pwm_val_left = 0;

    if (pwm_val_right <= pwm_right)
        Right_moto_pwm = 1;
    else
        Right_moto_pwm = 0;

    if (pwm_val_right >= PWM_DUTY)
        pwm_val_right = 0;
}
