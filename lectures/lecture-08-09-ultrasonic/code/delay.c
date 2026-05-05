#include "delay.h"

/*
  函数功能：毫秒级延时函数
  适配晶振：11.0592MHz 12T 51单片机
*/
void Delay_Ms(unsigned int ms)
{
    unsigned int i;
    do{ // 作用： 外层循环控制总延时，内层循环实现1ms延时。原理：每次循环内i递减，直到0 → 1ms延时
        i = MAIN_Fosc / 96000; 
        while(--i);   
    }while(--ms);
}