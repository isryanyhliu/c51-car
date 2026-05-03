#include <reg52.h>  // 适配STC89C52RC的头文件，Keil完全兼容

sbit LED = P1^6;  // 定义P1.6引脚接LED（低电平点亮）

// 简单延时函数
void delay(unsigned int t) {
    unsigned int i,j;
    for(i = t; i > 0; i--)
        for(j = 110; j > 0; j--);
}

void main(void) {
    while(1) {
        LED = 0;  // 灯亮
        delay(500);
        LED = 1;  // 灯灭
        delay(500);
    }
}