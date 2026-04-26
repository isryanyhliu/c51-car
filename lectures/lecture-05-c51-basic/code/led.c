#include "led.h"


void LED_On(void)
{
    LED = 0;
}

void LED_Off(void)
{
    LED = 1;
}

void LED_Flash(unsigned int t)
{
    unsigned int i,j;
    for(i=0;i<t;i++)
    {
        LED = 0;
        for(j=0;j<110;j++);
        LED = 1;
        for(j=0;j<110;j++);
    }
}