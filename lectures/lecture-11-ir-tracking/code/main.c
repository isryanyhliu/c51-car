#include "config.h"
#include "delay.h"
#include "timer.h"
#include "motor.h"

// ===================== 全局变量 =====================
unsigned char pwm_val_left = 0, pwm_val_right = 0;
unsigned char pwm_left = 100, pwm_right = 100;

// ===================== 红外避障函数 =====================
// 学生实验：完善此函数
void IRAvoid(void)
{
    // 1. 读避障传感器
    char left  = left_led2;      // 左：0=有障，1=无障碍
    char right = right_led2;     // 右：0=有障，1=无障碍

    // 2. 根据状态决定动作
    if (right == 0) {            // 右侧检测到障碍物
        left_run(120, 120);     // 向左转避开
    }
    else if (left == 0) {        // 左侧检测到障碍物
        right_run(120, 120);    // 向右转避开
    }
    else {                       // 两侧都无障碍
        forward(120, 120);      // 前进
    }
}

// ===================== 主函数 =====================
void main(void)
{
    Timer0_Init();   // 初始化电机 PWM
    EA_on;           // 开启总中断

    // 初始状态
    LED1 = 1;
    LED2 = 1;
    beep = 1;

    // 主循环：不断执行避障
    while(1)
    {
        IRAvoid();       // 红外避障
        Delay_Ms(10);    // 10ms 采样周期
    }
}
