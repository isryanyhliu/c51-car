#include "motor.h"

// 前进
void forward(unsigned char LeftSpeed, unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_go;
    right_motor_go;
}

// 后退
void back_run(unsigned char LeftSpeed, unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_back;
    right_motor_back;
}

// 左转（左轮退，右轮进）
void left_run(unsigned char LeftSpeed, unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_back;
    right_motor_go;
}

// 右转（左轮进，右轮退）
void right_run(unsigned char LeftSpeed, unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_go;
    right_motor_back;
}

// 停车
void stop(void)
{
    left_motor_stops;
    right_motor_stops;
}
