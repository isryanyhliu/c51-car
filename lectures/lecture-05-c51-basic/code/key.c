#include "key.h"

unsigned char Key_Scan(void)
{
    if(KEY == 0)
    {
        // 简单消抖
        unsigned int i;
        for(i=0;i<1000;i++);
        if(KEY == 0)
        {
            while(KEY == 0); // 等待松开
            return 1;
        }
    }
    return 0;
}