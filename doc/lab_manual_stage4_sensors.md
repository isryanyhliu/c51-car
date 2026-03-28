# 实训手册 Stage 4：传感器读取 (测距与循迹)

## 1. 理论引导：传感器时序
- **超声波 (HC-SR04)**：需要通过软件捕捉 `Echo` 引脚的高电平持续时间。这需要使用 **定时器 1**。
- **循迹 (IR Tracking)**：这是数字逻辑信号。`0` 代表感应到黑色，`1` 代表未感应。

## 2. 实践 A：超声波测距函数
**目标**：掌握时序控制与公式换算。

```c
#include <reg52.h>
#include <intrins.h> // 提供 _nop_() 函数用于短延时

sbit Trig = P2^1; 
sbit Echo = P2^0;

unsigned int Get_Distance() {
    unsigned int time;
    
    // 1. 发出 10us 的触发信号
    Trig = 1;
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    Trig = 0;
    
    // 2. 等待 Echo 变高并启动定时器 1
    while(!Echo);
    TR1 = 1; TH1 = 0; TL1 = 0; 
    
    // 3. 等待 Echo 变低并停止定时器
    while(Echo);
    TR1 = 0;
    
    // 4. 计算距离
    time = (TH1 * 256) + TL1;
    // 公式近似：距离(cm) = 时间(us) * 0.017
    return (unsigned int)(time * 0.017 * 1.085); 
}

void main() {
    TMOD |= 0x10; // 设定定时器 1 为模式 1 (16位)
    while(1) {
        unsigned int dis = Get_Distance();
        // 此处可结合串口或 LCD 显示距离，或根据 dis 控制动作
    }
}
```

## 3. 实践 B：简单的双路循迹逻辑
**目标**：掌握条件判断与路径校正。

```c
#include <reg52.h>

sbit L_Track = P3^4; // 左循迹传感器接口映射
sbit R_Track = P3^5; // 右循迹传感器接口映射

void main() {
    while(1) {
        if(L_Track == 0 && R_Track == 0) {
            // 两路都在线上 -> 直行
        }
        else if(L_Track == 1 && R_Track == 0) {
            // 左路脱离 -> 需要向右转来回正
        }
        else if(L_Track == 0 && R_Track == 1) {
            // 右路脱离 -> 需要向左转来回正
        }
    }
}
```

---
## 4. 教师点拨
*   **计算溢出**：注意 `TH1/TL1` 两个 8 位寄存器组合成 16 位值的位移操作。
*   **盲区问题**：提醒学生超声波有约 2cm 的盲区，且由于声波反射角度，测量侧面墙壁可能不准。
