#include "config.h"
#include "delay.h"
#include "timer.h"
#include "motor.h"

// ===================== 全局变量 =====================
unsigned char pwm_val_left = 0, pwm_val_right = 0;
unsigned char pwm_left = 100, pwm_right = 100;

// ===================== 红外避障函数 =====================
void CarAvoid(void)
{
    // 1. 读避障传感器
    char left_flag  = left_ir;      // 左：0=有障，1=无障碍
    char right_flag = right_ir;     // 右：0=有障，1=无障碍

    // 2. 调试LED：检测到障碍时LED亮（低电平点亮）
    debug_left_led  = left_flag;   // left_flag=0(有障) -> LED亮
    debug_right_led = right_flag;  // right_flag=0(有障) -> LED亮

    // 3. 根据传感器状态决定动作
    if (right_flag == 0 && left_flag == 0) {
        // 两侧都有障 -> 后退 + 转向
        stop();
        Delay_Ms(50);
        back_run(120, 120);
        Delay_Ms(300);
        stop();
        Delay_Ms(50);
        left_run(120, 120);
        Delay_Ms(200);
    }
    else if (right_flag == 0) {
        // 右侧有障 -> 左转
        stop();
        Delay_Ms(30);
        left_run(120, 120);
    }
    else if (left_flag == 0) {
        // 左侧有障 -> 右转
        stop();
        Delay_Ms(30);
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
    beep = 1;
    debug_left_led  = 1;   // 调试LED初始熄灭
    debug_right_led = 1;

    // 主循环：不断执行避障（示例代码，实际需根据场地调整）
    while(1)
    {
        CarAvoid();       // 红外避障
        Delay_Ms(10);    // 10ms 采样周期
    }
}
