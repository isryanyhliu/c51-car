#include "motor.h"
#include "timer.h"

// 小车前进（固定速度）
void forward(void)
{
    pwm_left = 120;
    pwm_right = 120;
    left_motor_go;
    right_motor_go;
}

// 小车停车
void stop(void)
{
    left_motor_stops;
    right_motor_stops;
}