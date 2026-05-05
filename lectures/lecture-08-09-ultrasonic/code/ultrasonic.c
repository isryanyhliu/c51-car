#include "ultrasonic.h"
#include "timer.h"

/*
  函数功能：触发HC-SR04发射超声波
  原理：给Trig引脚 ≥10us高电平脉冲
*/
void QXMBOT_TrigUltrasonic()
{
    TrigPin = 0;  // 先拉低复位
    _nop_();
    TrigPin = 1;  // 拉高触发
    // 保持20us高电平（满足模块要求）
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
    TrigPin = 0;  // 拉低结束
}

/*
  函数功能：读取超声波测量距离
  返回值：距离（单位：毫米）
  核心：定时器1测量回声时间 → 公式计算距离
*/
unsigned int QXMBOT_GetDistance()
{
    unsigned int Distance = 0;  // 最终距离
    unsigned int Time = 0;      // 声波往返时间

    QXMBOT_TrigUltrasonic();   // 1. 触发超声波

    while(!EchoPin);           // 2. 等待回声开始（Echo变高）
    TR1 = 1;                   // 启动定时器1 开始计时
    while(EchoPin);            // 3. 等待回声结束（Echo变低）
    TR1 = 0;                   // 关闭定时器1 停止计时

    Time = TH1*256 + TL1;      // 读取计时值
    TH1 = 0; TL1 = 0;          // 清空定时器

    Distance = (float)(Time*1.085)*0.17; // 公式计算距离（毫米）。
    //1.085是因为晶振11.0592MHz下每计时单位约1.085微秒；
    
    return Distance;
}