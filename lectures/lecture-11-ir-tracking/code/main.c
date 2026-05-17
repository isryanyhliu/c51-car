#include "config.h"
#include "delay.h"
#include "timer.h"
#include "motor.h"

// ===================== 全局变量 =====================
unsigned char pwm_val_left = 0, pwm_val_right = 0;
unsigned char pwm_left = 100, pwm_right = 100;

// ===================== 循迹函数（示例代码，实际需根据场地调整） =====================
void car_track(void)
{
    unsigned char s_l, s_r, state;

    // 1. 读取传感器（示例代码，实际需根据场地调整）
    s_r = left_track;       // 左：0=白线，1=黑线
    s_l = right_track;      // 右：0=白线，1=黑线

    // 2. 拼接状态（用十进制模拟二进制拼接）
    state = s_l * 10 + s_r;

    // 3. 根据状态决定动作（示例逻辑，实际需根据场地调整）
    if (state == 11) {       // 两传感器都在线（黑线）
        forward(120, 120);   // 前进
    }
    else if (state == 10) {  // 左白右黑 -> 偏左，需要右转
        right_run(80, 160);  // 右转纠偏
    }
    else if (state == 1) {   // 左黑右白 -> 偏右，需要左转
        left_run(160, 80);   // 左转纠偏
    }
    else {                   // 两传感器都离线
        stop();              // 停车
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

    // 主循环：不断执行循迹（示例代码，实际需根据场地调整）
    while(1)
    {
        car_track();      // 循迹
        Delay_Ms(10);    // 10ms 采样周期
    }
}
