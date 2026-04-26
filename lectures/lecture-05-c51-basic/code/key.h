#ifndef _KEY_H_
#define _KEY_H_

#include <reg52.h>

sbit KEY = P3^3;

unsigned char Key_Scan(void);

#endif