#include "motor.h"

// 前进（示例代码，实际速度需根据场地调整）
void forward(unsigned char LeftSpeed, unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_go;
    right_motor_go;
}

// 后退（示例代码，实际速度需根据场地调整）
void back_run(unsigned char LeftSpeed, unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_back;
    right_motor_back;
}

// 左转（左轮退，右轮进）（示例代码，实际速度需根据场地调整）
void left_run(unsigned char LeftSpeed, unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_back;
    right_motor_go;
}

// 右转（左轮进，右轮退）（示例代码，实际速度需根据场地调整）
void right_run(unsigned char LeftSpeed, unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_go;
    right_motor_back;
}

// 停车（示例代码）
void stop(void)
{
    left_motor_stops;
    right_motor_stops;
}
