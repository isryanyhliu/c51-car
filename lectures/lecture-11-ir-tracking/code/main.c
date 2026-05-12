#include "config.h"
#include "delay.h"
#include "timer.h"
#include "motor.h"

// ===================== 全局变量 =====================
unsigned char pwm_val_left = 0, pwm_val_right = 0;
unsigned char pwm_left = 100, pwm_right = 100;

// ===================== 循迹函数 =====================
void Tracking(void)
{
    char data1, data2, data3;

    // 1. 读取传感器
    data2 = left_led1;       // 左传感器：0=白线，1=黑线
    data3 = right_led1;      // 右传感器：0=白线，1=黑线

    // 2. 拼接状态（用十进制模拟二进制拼接）
    data1 = data2 * 10 + data3;

    // 3. 根据状态决定动作
    if (data1 == 11) {       // 两传感器都在线（黑线）
        forward(120, 120);   // 前进
    }
    else if (data1 == 10) {  // 左白右黑 -> 偏左，需要右转
        left_run(80, 160);   // 右转纠偏
    }
    else if (data1 == 1) {   // 左黑右白 -> 偏右，需要左转
        right_run(160, 80);  // 左转纠偏
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
    LED1 = 1;
    LED2 = 1;
    beep = 1;

    // 主循环：不断执行循迹
    while(1)
    {
        Tracking();      // 循迹
        Delay_Ms(10);    // 10ms 采样周期
    }
}
