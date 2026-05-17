#include "config.h"
#include "delay.h"
#include "timer.h"
#include "motor.h"

// ===================== 全局变量 =====================
unsigned char pwm_val_left = 0, pwm_val_right = 0;
unsigned char pwm_left = 100, pwm_right = 100;

// ===================== 红外避障函数（示例） =====================
void CarAvoid(void)
{
    // 1. 读避障传感器（示例代码，实际需根据场地调整）
    char left_led  = left_ir;      // 左：0=有障，1=无障碍
    char right_led = right_ir;     // 右：0=有障，1=无障碍

    // 2. 根据状态决定动作（示例逻辑，实际需根据场地调整）
    if (right_led == 0 && left_led == 0) {
        // 两侧都有障 -> 后退 + 转向
        back_run(120, 120);
        Delay_Ms(300);
        left_run(120, 120);
        Delay_Ms(200);
    }
    else if (right_led == 0) {
        // 右侧有障 -> 左转
        left_run(120, 120);
    }
    else if (left_led == 0) {
        // 左侧有障 -> 右转
        right_run(120, 120);
    }
    else {
        // 两侧都无障碍 -> 前进
        forward(120, 120);
    }
}

// ===================== 主函数 =====================
void main(void)
{
    Timer0_Init();   // 初始化电机 PWM
    EA_on;           // 开启总中断

    // 初始状态
    led1 = 1;
    led2 = 1;
    beep = 1;

    // 主循环：不断执行避障（示例代码，实际需根据场地调整）
    while(1)
    {
        CarAvoid();       // 红外避障
        Delay_Ms(10);    // 10ms 采样周期
    }
}
