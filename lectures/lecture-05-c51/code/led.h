#ifndef _LED_H_ // 防止重复包含头文件(固定写法)
#define _LED_H_ // 头文件内容（固定写法）

#include <reg52.h> //调用官方头文件（必须）

sbit LED = P1^6; //sbit是51单片机特有的关键字，用于定义位变量
/* 
* 这里我们定义了一个名为LED的位变量，它位于P1端口的第6位（P1.6）。
* 通过这个变量，我们可以直接控制P1.0引脚的电平状态，从而控制连接在该引脚上的LED灯的开关状态。 
*/

void LED_On(void); 
void LED_Off(void);
void LED_Flash(unsigned int t); 

#endif // 结束头文件内容（固定写法）