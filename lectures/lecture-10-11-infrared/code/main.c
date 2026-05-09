#include "config.h"
#include "delay.h"
#include "timer.h"
#include "motor.h"

// ===================== 全局变量 =====================
unsigned char pwm_val_left = 0, pwm_val_right = 0;
unsigned char pwm_left = 100, pwm_right = 100;
unsigned char mode = 0;

// ===================== 循迹函数 =====================
void Tracking(void)
{
    char data1, data2, data3;

    data2 = left_led1;       // 左传感器：0=白线，1=黑线
    data3 = right_led1;      // 右传感器：0=白线，1=黑线
    data1 = data2 * 10 + data3;  // 拼接状态

    if (data1 == 11) {       // 两传感器都在线（黑线）
        forward(120, 120);   // 前进
    }
    else if (data1 == 10) {  // 左白右黑 -> 偏左
        left_run(80, 160);   // 右转纠偏
    }
    else if (data1 == 1) {   // 左黑右白 -> 偏右
        right_run(160, 80);  // 左转纠偏
    }
    else {                   // 两传感器都离线
        stop();              // 停车
    }
}

// ===================== 红外避障函数 =====================
void IRAvoid(void)
{
    if (right_led2 == 0) {   // 右侧检测到障碍物
        left_run(120, 120);  // 向左转
    }
    else if (left_led2 == 0) { // 左侧检测到障碍物
        right_run(120, 120); // 向右转
    }
    else {
        forward(120, 120);   // 无障碍，前进
    }
}

// ===================== 主函数 =====================
void main(void)
{
    Timer0_Init();   // 电机 PWM 定时器
    EA_on;           // 开启总中断

    // 初始状态
    LED1 = 1;
    LED2 = 1;
    beep = 1;

    // 主循环
    while(1)
    {
        switch(mode)
        {
            case 0:    // 模式0：纯循迹
                LED1 = 1, LED2 = 1;
                Tracking();
                break;
            case 1:    // 模式1：红外避障
                LED1 = 0, LED2 = 1;
                IRAvoid();
                break;
            default:
                stop();
                mode = 0;
                break;
        }
        Delay_Ms(10);
    }
}
