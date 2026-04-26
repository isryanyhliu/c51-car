#include "beep.h"

void BEEP_On(void)
{
    BEEP = 0;
}

void BEEP_Off(void)
{
    BEEP = 1;
}