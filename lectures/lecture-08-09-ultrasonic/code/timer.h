#ifndef __TIMER_H
#define __TIMER_H
#include "config.h"

extern unsigned char pwm_val_left, pwm_val_right;
extern unsigned char pwm_left, pwm_right;
extern bit Timer1Overflow;

void Timer0_Init(void);
void Timer1_Init(void);
void LoadPWM(void);

#endif