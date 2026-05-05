#include "timer.h"

unsigned char pwm_val_left,pwm_val_right;  // PWM计数变量
unsigned char pwm_left,pwm_right;           // PWM占空比变量

/*
  函数功能：定时器0初始化 → 用于电机PWM调速
  溢出时间：100微秒
*/
void Timer0_Init(void) 
{
    TMOD |= 0x02;  // 定时器0：8位自动重装模式
    TH0 = 164;     // 初值配置
    TL0 = 164;
    TR0 = 1;       // 启动定时器0
    ET0 = 1;       // 开定时器0中断
}

/*
  函数功能：定时器1初始化 → 用于测量超声波回声时间
  工作模式：16位定时模式
*/
void Timer1_Init(void)		
{
    TMOD |= 0x10;	// 定时器1 模式1
    TH1 = 0;       // 初值清零
    TL1 = 0;
    ET1 = 1;       // 开定时器1中断
}

/*
  函数功能：配置PWM输出，控制电机转速
*/
void LoadPWM(void)
{
    // 限制PWM占空比范围
    if(pwm_left > PWM_HIGH_MAX)    pwm_left = PWM_HIGH_MAX;
    if(pwm_left < PWM_HIGH_MIN)    pwm_left = PWM_HIGH_MIN;
    if(pwm_right > PWM_HIGH_MAX)   pwm_right = PWM_HIGH_MAX;
    if(pwm_right < PWM_HIGH_MIN)   pwm_right = PWM_HIGH_MIN;

    // 左电机PWM输出
    if(pwm_val_left<=pwm_left)   Left_moto_pwm = 1;
    else Left_moto_pwm = 0;
    if(pwm_val_left>=PWM_DUTY)   pwm_val_left = 0;

    // 右电机PWM输出
    if(pwm_val_right<=pwm_right) Right_moto_pwm = 1;
    else Right_moto_pwm = 0;
    if(pwm_val_right>=PWM_DUTY)   pwm_val_right = 0;
}

// ===================== 定时器0中断服务函数 =====================
void timer0_int (void) interrupt 1
{
    pwm_val_left++;     // PWM计数
    pwm_val_right++;
    LoadPWM();          // 刷新PWM输出
}

// ===================== 定时器1中断服务函数 =====================
void tm1_isr() interrupt 3 using 1
{
    EchoPin = 0;  // 超时强制关闭回声检测
}