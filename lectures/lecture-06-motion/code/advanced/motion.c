#include "motion.h"

// 小车前进（设置方向，速度由定时器PWM控制）
void Car_Forward(void)
{
    Left_Forward();
    Right_Forward();
}

// 小车停止
void Car_Stop(void)
{
    Left_Stop();
    Right_Stop();
}