#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H
#include "config.h"

void QXMBOT_TrigUltrasonic(void);  // 触发超声波发射
unsigned int QXMBOT_GetDistance(void); // 获取距离（单位：毫米）

#endif