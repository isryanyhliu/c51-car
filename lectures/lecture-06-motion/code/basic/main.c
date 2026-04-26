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
    // 【关键修复】C51必须在函数开头定义所有变量！
    unsigned int t;

    Motor_Init();
    Car_Stop();
    
    while(1)
    {
        // 1. 全速前进1秒
        Car_Forward();
        Delay_ms(1000);

        // 2. 停止1秒
        Car_Stop();
        Delay_ms(1000);


        
        // 3. PWM调速演示（持续输出）
        Car_Forward(); // 先设置方向
        
        // 全速 2秒
        for(t=0;t<2000;t++) 
            Motor_Run(100,100);
        
        // 半速 2秒
        for(t=0;t<2000;t++) 
            Motor_Run(50,50);
        
        // 低速 2秒
        for(t=0;t<2000;t++) 
            Motor_Run(20,20);
        
        // 停止
        Car_Stop();
        Delay_ms(1000);
    }
}