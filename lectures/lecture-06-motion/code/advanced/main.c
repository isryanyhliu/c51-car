#include "motion.h"

// 毫秒延时函数
void Delay_ms(unsigned int ms)
{
    unsigned int i,j;
    for(i=0; i<ms; i++)
        for(j=110; j>0; j--);
}

void main(void)
{
    Motor_Init();      // 初始化：定时器PWM + 电机
    Car_Stop();
    Motor_SetSpeed(0, 0); // 初始停止
    
    while(1)
    {
        // ======================
        // 1. 全速前进 2秒
        // ======================
        Car_Forward();
        Motor_SetSpeed(100, 100);
        Delay_ms(2000);
        
        // ======================
        // 2. 停止 1秒
        // ======================
        Car_Stop();
        Motor_SetSpeed(0, 0);
        Delay_ms(1000);
        
        // ======================
        // 3. PWM调速演示
        // ======================
        Car_Forward();
        // 全速 2秒
        Motor_SetSpeed(100, 100);
        Delay_ms(2000);
        
        // 半速 2秒
        Motor_SetSpeed(50, 50);
        Delay_ms(2000);
        
        // 低速 2秒
        Motor_SetSpeed(20, 20);
        Delay_ms(2000);
        
        // 停止
        Car_Stop();
        Motor_SetSpeed(0, 0);
        Delay_ms(1000);
    }
}