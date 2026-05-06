#include "config.h"
#include "delay.h"
#include "timer.h"
#include "motor.h"
#include "ultrasonic.h"

// 避障阈值：300毫米（30厘米）
#define OBSTACLE_LIMIT  300

void main(void)
{
    // 1. 初始化
    Timer0_Init();   // 电机PWM定时器
    Timer1_Init();   // 超声波计时定时器
    EA_on;           // 开启总中断

    // 初始状态
    LED1 = 0;
    LED2 = 1;
    beep = 1;        // 蜂鸣器默认关闭

    // 2. 主循环
    while(1)
    {
        unsigned int dis = Get_Distance();  // 读取距离
        Delay_Ms(60);                      // 测距必须间隔60ms

        // ===================== 核心逻辑 =====================
        if(dis > OBSTACLE_LIMIT)  // 无障碍物
        {
            LED1 = 0;             // 亮LED1
            LED2 = 1;             // 灭LED2
            beep = 1;             // 关闭蜂鸣器
            forward();            // 小车前进
        }
        else                     // 检测到障碍物
        {
            LED1 = 1;             // 灭LED1
            LED2 = 0;             // 亮LED2
            beep = 0;             // 蜂鸣器响
            stop();               // 原地停车
        }
    }
}