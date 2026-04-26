
/*
* reg52.h是Intel官方给出的头文件，包含了51单片机的寄存器定义
* 通过包含这个头文件，我们可以直接使用寄存器的名字来访问它们，而不需要记住它们的地址
* 例如，我们可以直接使用P0来访问端口0寄存器，而不需要记住它的地址是0x80
* 这使得编程更加方便和易读
* 需要注意的是，reg52.h是针对特定型号的51单片机编写的，如果使用不同型号的单片机，可能需要使用不同的头文件
* 例如，如果使用的是STC系列的单片机，可能需要使用stc15.h头文件来包含寄存器定义
*/
#include <REG52.H>


#include "led.h"
#include "beep.h"
#include "key.h"

void DelayMs(unsigned int ms)
{
    unsigned int i,j;
    for(i=ms;i>0;i--)
        for(j=110;j>0;j--);
}

void main(void)
{
    // 初始状态
    LED_Off();
    BEEP_Off();

    while(1)
    {
        // 按键触发：灯闪烁 + 蜂鸣器短响
        if(Key_Scan() == 1)
        {
            BEEP_On();
            LED_Flash(3);
            BEEP_Off();
        }
        DelayMs(20);
    }
}