#ifndef _BEEP_H_
#define _BEEP_H_

#include <reg52.h>

sbit BEEP = P2^2;

void BEEP_On(void);
void BEEP_Off(void);

#endif