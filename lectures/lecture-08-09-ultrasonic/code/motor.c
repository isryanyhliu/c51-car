#include "motor.h"
#include "timer.h"  // 修复：声明pwm_left/pwm_right变量，解决编译报错

/* 前进 */
void forward(unsigned char LeftSpeed,unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_go = 1;
    right_motor_go = 1;
}

/* 左转 */
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    left_motor_back = 1;
    right_motor_go = 1;	
}

/* 右转 */
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    right_motor_back = 1;
    left_motor_go = 1;    
}

/* 后退 */
void back_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
    pwm_left = LeftSpeed;
    pwm_right = RightSpeed;
    right_motor_back = 1;
    left_motor_back = 1;
}

/* 停车 */
void stop(void)
{
    left_motor_stops;
    right_motor_stops;
}