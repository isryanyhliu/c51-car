#include "config.h"

// 毫秒延时（示例代码）
void Delay_Ms(unsigned int ms)
{
    unsigned int i;
    do {
        i = MAIN_Fosc / 96000;
        while (--i);
    } while (--ms);
}
