#include "motion.h"

// 前进
void Car_Forward(void)
{
    Left_Forward();
    Right_Forward();
}

// 后退
void Car_Backward(void)
{
    Left_Backward();
    Right_Backward();
}

// 左转
void Car_Left(void)
{
    Left_Stop();
    Right_Forward();
}

// 右转
void Car_Right(void)
{
    Right_Stop();
    Left_Forward();
}

// 停止
void Car_Stop(void)
{
    Left_Stop();
    Right_Stop();
}