#include "config.h"
#include "delay.h"
#include "timer.h"
#include "motor.h"
#include "ultrasonic.h"

/*
  函数功能：超声波避障逻辑
  入口参数：val = 避障阈值（单位：毫米）
  逻辑：距离 < 阈值 → 停车→后退→左转；否则前进
*/
void UltrasonicAvoid(unsigned int val)
{
    unsigned int Dis;
    Delay_Ms(60);  // 超声波测距必须间隔≥60ms

    Dis = QXMBOT_GetDistance();  // 获取距离

    if(Dis < val)  // 检测到障碍物
    {
        stop();          // 停车
        beep = 0;        // 蜂鸣器报警
        Delay_Ms(100);
        beep = 1;        // 关闭蜂鸣器

        back_run(120,120);   // 后退
        Delay_Ms(50);
        left_run(120,120);  // 左转
        Delay_Ms(100);
    }
    else  // 无障碍物
    {
        forward(120,120);    // 前进
    }
}

/*
  主函数：程序入口
*/
void main(void)
{
    // 初始化
    Timer0_Init();  // 定时器0（电机PWM）
    Timer1_Init();  // 定时器1（超声波计时）
    EA = 1;         // 开启总中断

    LED1 = 0; LED2 = 1;  // 工作状态指示灯

    // 主循环
    while(1)
    {
        UltrasonicAvoid(300);  // 避障阈值：300毫米（30厘米）
    }	
}