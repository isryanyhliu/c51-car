# 实训手册 Stage 3：电机驱动与速度控制 (PWM)

## 1. 理论引导：H 桥与占空比
- **H 桥逻辑**：电机不是简单的开关，而是需要控制电流方向。`IN1, IN2` 是一组，控制左轮；`IN3, IN4` 控制右轮。
- **PWM (脉冲宽度调制)**：通过高频地“通电-断电”，利用电机的惯性实现调速。开启时间占总时间的比例越长，速度越快。

## 2. 实践 A：基础运动函数库
**目标**：模块化编程，封装底层引脚操作。

```c
#include <reg52.h>

// 引脚映射 (基于 QX_A11 标准)
sbit IN1 = P1^0; sbit IN2 = P1^1;
sbit IN3 = P1^2; sbit IN4 = P1^3;
sbit EN1 = P1^4; sbit EN2 = P1^5;

void Car_Forward() {
    IN1 = 1; IN2 = 0; // 左轮前进
    IN3 = 1; IN4 = 0; // 右轮前进
    EN1 = 1; EN2 = 1; // 全速运行
}

void Car_Stop() {
    EN1 = 0; EN2 = 0; // 关闭使能，小车滑行停止
}

void main() {
    while(1) {
        Car_Forward();
    }
}
```

## 3. 实践 B：软件脉宽调制 (Timer-based PWM)
**目标**：通过定时器中断实现 50% 的中速运行。

```c
#include <reg52.h>

sbit EN1 = P1^4; 
unsigned char pwm_count = 0;
unsigned char target_speed = 50; // 0-100 范围的分级速度

// 定时器 0 初始化：每 100 微秒产生一次中断
void Timer0_Init() {
    TMOD |= 0x02; // 8位自动重装模式
    TH0 = 0x9C;   // 11.0592M 晶振下对应约 100us
    TL0 = 0x9C;
    ET0 = 1;      // 开启定时器 0 中断
    EA = 1;       // 开启全局中断
    TR0 = 1;      // 启动定时器
}

// 中断服务程序：控制引脚开关频率
void Timer0_ISR() interrupt 1 {
    pwm_count++;
    if(pwm_count >= 100) pwm_count = 0;
    
    // 如果计数器还在目标速度内，输出高电平，否则输出低电平
    if(pwm_count < target_speed) EN1 = 1;
    else EN1 = 0;
}

void main() {
    Timer0_Init();
    while(1); // 主循环保持空闲，所有控制都在后台中断中完成
}
```

---
## 4. 教师点拨
*   **前后台机制**：这是学生第一次接触“后台任务”（中断）。强调 `main` 函数虽然是空的，但 `Timer0_ISR` 正在以极高的频率抢占 CPU 来控制引脚。
*   **硬件惯性**：解释为什么 50Hz 到 200Hz 左右的 PWM 最适合这种微电机。
 Riverside,
