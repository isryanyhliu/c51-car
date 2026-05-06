#include "ultrasonic.h"
#include "timer.h"

// 触发超声波发射
static void Trig_Ultrasonic(void)
{
    TrigPin = 0;
    _nop_();
    TrigPin = 1;
    // 保持10us高电平触发
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
    TrigPin = 0;
}

// 测距函数：返回毫米
// 核心公式对应课件：距离(mm) = 时间 * 0.17
unsigned int Get_Distance(void)
{
    unsigned int Time = 0;
    unsigned int Distance = 0;

    Trig_Ultrasonic();
    while(!EchoPin);     // 等待回声开始
    Timer1On;            // 启动计时
    while(EchoPin);      // 等待回声结束
    Timer1Off;           // 停止计时

    Time = TH1*256 + TL1;
    TH1 = 0; TL1 = 0;

    // ===================== 课件对应公式 =====================
    // 0.17 = 课件 0.017 × 10（厘米转毫米）
    // 1.085 = 晶振校准系数
    Distance = (float)(Time * 1.085) * 0.17;

    return Distance;
}