/*********************************************************************************
* 【编写时间】： 2021年5月12日
* 【作    者】： 清翔电子:03
* 【版    本】： 1.0
* 【网    站】： http://www.QXMBOT.com/ 
* 【淘宝店铺】： http://qxmcu.taobao.com/ (直销店)
* 【实验平台】： QX-A11亚克力智能小车  
* 【外部晶振】： 11.0592mhz	
* 【主控芯片】： 12T 51单片机
* 【编译环境】： Keil μVisio4
*	版权所有，盗版必究。
*	Copyright(C) QXMBOT
*	All rights reserved
***********************************************************************************
* 【接线说明】：请参考资料内图文说明书
* 【程序功能】：QX-A11智能小车黑线循迹+红外避障+超声波避障	   			            			    
* 【注意事项】：红外避障会被自然光干扰
**********************************************************************************/
//通过按开发板上KEY按键切换模式，默认为模式0超声波避障LED1,LED2灭，模式1红外避障+超声波避障LED1亮,LED2灭，
//模式2红外循迹+超声波避障LED1灭,LED2亮，模式3红外循迹LED1亮,LED2亮
#include <reg52.h> //51头文件
#include <QX_A11.h>//QX_A11智能小车配置文件
#include <intrins.h>

bit Timer1Overflow;	//计数器1溢出标志位
unsigned char disbuff[4]={0,0,0,0};//用于分别存放距离的值米，厘米，毫米
unsigned int LeftDistance = 0, RightDistance = 0, FrontDistance = 0; //云台测距距离缓存
unsigned int DistBuf[5] = {0};//distance data buffer
unsigned char	pwm_val_left,pwm_val_right;	//中间变量，用户请勿修改。
unsigned char 	pwm_left,pwm_right;			//定义PWM输出高电平的时间的变量。用户操作PWM的变量。
unsigned char mode;//模式设置变量
#define		PWM_DUTY		200			//（用于舵机时不可修改）定义PWM的周期，数值为定时器0溢出周期，假如定时器溢出时间为100us，则PWM周期为20ms。
#define		PWM_HIGH_MIN	70			//限制PWM输出的最小占空比。用户请勿修改。
#define		PWM_HIGH_MAX	PWM_DUTY	//限制PWM输出的最大占空比。用户请勿修改。

void Timer0_Init(void); //定时器0初始化
void Timer1_Init(void);//定时器1初始化
void LoadPWM(void);//装入PWM输出值 
void Delay_Ms(unsigned int ms);//毫秒级延时函数
void forward(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车前进 
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车左转  
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车右转
void back_run(unsigned char LeftSpeed,unsigned char RightSpeed);//QX_A11智能小车后退
void stop(void);//QX_A11智能小车停车
unsigned int QXMBOT_GetDistance(void);//获取超声波距离
void QXMBOT_TrigUltrasonic(void);// 触发超声波
void Tracking();//黑线循迹函数
void UltrasonicAvoid(unsigned int val);//超声波避障
void ULT_TrakAvoid(unsigned int val);//红外循迹超声波避障
void ULT_IRAvoid(unsigned int val);//红外避障+超声波避障

/*主函数*/     
void main(void)
{
	Timer0_Init();//定时0初始化
	Timer1_Init();//定时0初始化
	IT1 = 1;                        //set INT1 int type (1:Falling only 0:Low level)
  EX1 = 1;                        //enable INT1 interrupt
	EA_on;	//开中断
	while(1)
	{
		switch(mode)
		{
			case 0:	 LED1=1,LED2=1; UltrasonicAvoid(300); break; //超声波避障模式,LED1,LED2状态指示灯熄灭
			case 1:	 LED1=0,LED2=1; ULT_IRAvoid(300); break;  //红外避障+超声波避障,LED1亮,LED2灭
			case 2:	 LED1=1,LED2=0; ULT_TrakAvoid(200); break;//红外循迹超声波避障模式,LED1灭,LED2亮
			case 3:	 LED1=0,LED2=0; Tracking(); break;//黑线循迹模式,LED1亮,LED2亮
			default: stop(); /*停车*/	 break;
		}		
	}	
}
//External interrupt1 service routine
void exint1() interrupt 2           //(location at 0013H)
{
	if(KEY==0)//判断KEY是否按下
	{
		stop();//停车
		Delay_Ms(10); //软件消抖
		if(KEY==0)//再次判断KEY是否按下
		{
			mode++;
			while(!KEY);//松手检测
		}
	}
	if(mode > 3)	mode = 0;
}

/*********************************************
QX_A11智能小车前进
入口参数：LeftSpeed，RightSpeed
出口参数: 无
说明：LeftSpeed，RightSpeed分别设置左右车轮转速
**********************************************/
void forward(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//设置速度
	left_motor_go; //左电机前进
	right_motor_go; //右电机前进
}
/*小车左转*/
/*********************************************
QX_A11智能小车左转
入口参数：LeftSpeed，RightSpeed
出口参数: 无
说明：LeftSpeed，RightSpeed分别设置左右车轮转速
**********************************************/
void left_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//设置速度
	left_motor_back; //左电机后退
	right_motor_go; //右电机前进	
}

/*********************************************
QX_A11智能小车右转
入口参数：LeftSpeed，RightSpeed
出口参数: 无
说明：LeftSpeed，RightSpeed分别设置左右车轮转速
**********************************************/
void right_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//设置速度
	right_motor_back;//右电机后退
	left_motor_go;    //左电机前进
}
/*********************************************
QX_A11智能小车后退
入口参数：LeftSpeed，RightSpeed
出口参数: 无
说明：LeftSpeed，RightSpeed分别设置左右车轮转速
**********************************************/
void back_run(unsigned char LeftSpeed,unsigned char RightSpeed)
{
	pwm_left = LeftSpeed,pwm_right =  RightSpeed;//设置速度
	right_motor_back;//右电机后退
	left_motor_back; //左电机后退
}
/*********************************************
QX_A11智能小车停车
入口参数：无
出口参数: 无
说明：QX_A11智能小车停车
**********************************************/
void stop(void)
{
	left_motor_stops;
	right_motor_stops;
}

/*====================================
函数：void Delay_Ms(INT16U ms)
参数：ms，毫秒延时形参
描述：12T 51单片机自适应主时钟毫秒级延时函数
====================================*/
void Delay_Ms(unsigned int ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 96000; 
		  while(--i);   //96T per loop
     }while(--ms);
}
/*********************************************
QX_A11智能小车PWM输出
入口参数：无
出口参数: 无
说明：装载PWM输出,如果设置全局变量pwm_left,pwm_right分别配置左右输出高电平时间
**********************************************/
void LoadPWM(void)
{
	if(pwm_left > PWM_HIGH_MAX)		pwm_left = PWM_HIGH_MAX;	//如果左输出写入大于最大占空比数据，则强制为最大占空比。
	if(pwm_left < PWM_HIGH_MIN)		pwm_left = PWM_HIGH_MIN;	//如果左输出写入小于最小占空比数据，则强制为最小占空比。
	if(pwm_right > PWM_HIGH_MAX)	pwm_right = PWM_HIGH_MAX;	//如果右输出写入大于最大占空比数据，则强制为最大占空比。
	if(pwm_right < PWM_HIGH_MIN)	pwm_right = PWM_HIGH_MIN;	//如果右输出写入小于最小占空比数据，则强制为最小占空比。
	if(pwm_val_left<=pwm_left)		Left_moto_pwm = 1;  //装载左PWM输出高电平时间
	else Left_moto_pwm = 0; 						    //装载左PWM输出低电平时间
	if(pwm_val_left>=PWM_DUTY)		pwm_val_left = 0;	//如果左对比值大于等于最大占空比数据，则为零

	if(pwm_val_right<=pwm_right)	Right_moto_pwm = 1; //装载右PWM输出高电平时间
	else Right_moto_pwm = 0; 							//装载右PWM输出低电平时间
	if(pwm_val_right>=PWM_DUTY)		pwm_val_right = 0;	//如果右对比值大于等于最大占空比数据，则为零
}
/*超声波触发*/
void QXMBOT_TrigUltrasonic()
{
	TrigPin = 0; //超声波模块Trig	控制端
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TrigPin = 1; //超声波模块Trig	控制端
	_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();
	TrigPin = 0; //超声波模块Trig	控制端
}
/*====================================
函数名	：QXMBOT_GetDistance
参数	：无
返回值	：获取距离单位毫米
描述	：超声波测距
通过发射信号到收到回响信号的时间测试距离
单片机晶振11.0592Mhz
注意测距周期为60ms以上
====================================*/
unsigned int QXMBOT_GetDistance()
{
	unsigned int Distance = 0;	//超声波距离
	unsigned int  Time=0;		//用于存放定时器时间值
	QXMBOT_TrigUltrasonic();	//超声波触发
	while(!EchoPin);  	//判断回响信号是否为低电平
	Timer1On;			//启动定时器1
	while(EchoPin);		//等待收到回响信号
	Timer1Off;			//关闭定时器1
	Time=TH1*256+TL1;	//读取时间
	TH1=0;
	TL1=0;				//清空定时器
    Distance = (float)(Time*1.085)*0.17;//算出来是MM
	return(Distance);//返回距离				
}
/*====================================
函数名	：UltrasonicAvoid
参数	：val设置避障触发距离
返回值	：无
描述	：智能小车超声波避障
距离单位：毫米
====================================*/
void UltrasonicAvoid(unsigned int val)
{
	unsigned int Dis;//距离暂存变量
	Delay_Ms(60);//延时60ms超声波测距需要间隔60ms
	Dis = QXMBOT_GetDistance();//获取超声波测距距离,单位：毫米
	if(Dis < val)
	{	
		do{
			stop();	//停车
			beep = 0;//鸣笛
			Delay_Ms(100);
			beep = 1;//静音
			back_run(120, 120);//后退
			Delay_Ms(50);//延时50ms
			left_run(120, 120);//原地左转
			Delay_Ms(100);//延时100ms
			Dis = QXMBOT_GetDistance();//获取超声波测距距离,单位：毫米
		}while(Dis < val);
		forward(120, 120);//前进
		Delay_Ms(60);//延时60ms
	}
	else
	{
		forward(120, 120);//前进	
	}
}
/*====================================
函数名	：ULT_TrakAvoid
参数	：val设置避障触发距离
返回值	：无
描述	：智能小车循迹+超声波避障
距离单位：毫米
====================================*/
void ULT_TrakAvoid(unsigned int val)
{
	unsigned int i;
	unsigned int Dis;//距离暂存变量
	for(i=0; i<6000; i++)		Tracking();//循环执行黑线循迹达到延时执行读取超声波距离的效果，超声波测距间隔需要大于60ms
	Dis = QXMBOT_GetDistance();//获取超声波测距距离,单位：毫米
	if(Dis < val)//毫米
	{	
		do{
			stop();	//停车
			beep = 0;//鸣笛
			Delay_Ms(100);
			Dis = QXMBOT_GetDistance();//获取超声波测距距离,单位：毫米
		}while(Dis < val);
		beep = 1;//静音
	}
}

/*====================================
函数名	：ULT_IRAvoid
参数	：val设置避障触发距离
返回值	：无
描述	：智能小车红外+超声波避障
距离单位：毫米
====================================*/
void ULT_IRAvoid(unsigned int val)
{
	unsigned int Dis;//距离暂存变量
	unsigned int i;
	for(i=0; i<6000; i++)//循环执行红外避障达到延时执行读取超声波距离的效果，超声波测距间隔需要大于60ms
	{
		if(right_led2 == 0)//右检测到障碍物，左转
		{
			left_run(120,120);//左转
		}
		if(left_led2 == 0)//左检测到障碍物，右转
		{
			right_run(120,120);//右转
		}
	}
	Dis = QXMBOT_GetDistance();//获取超声波测距距离,单位：毫米
	if(Dis < val)
	{	
		do{
			stop();	//停车
			beep = 0;//鸣笛
			Delay_Ms(100);
			beep = 1;//静音
			back_run(120, 120);//后退
			Delay_Ms(50);//延时50ms
			left_run(120, 120);//原地左转
			Delay_Ms(100);//延时100ms
			Dis = QXMBOT_GetDistance();//获取超声波测距距离,单位：毫米
		}while(Dis < val);
		forward(120, 120);//前进
		Delay_Ms(60);//延时60ms
	}
	else
	{
		forward(120, 120);//前进	
	}
}
void Tracking()//黑线循迹函数
{
	//为0 没有识别到黑线 为1识别到黑线
	char data1,data2 = left_led1,data3 = right_led1;
	data1 = data2*10+data3;
	if(data1 == 11)//在黑线上，前进
	{
		forward(120,120);//前进
	}
	else
	{
	 	if(data1 == 10)//小幅偏右，左转
		{
			left_run(80,160);//左转
		}
		if(data1 == 1)//小幅偏左，右转
		{
			right_run(160,80);//右转
		}
		if(data1 == 0)//大幅偏左或偏右，已脱离轨道
		{
			stop();	
		}
	}
}
/********************* Timer0初始化************************/
void Timer0_Init(void)
{
	TMOD |= 0x02;//定时器0，8位自动重装模块
	TH0 = 164;
	TL0 = 164;//11.0592M晶振，12T溢出时间约等于100微秒
	TR0 = 1;//启动定时器0
	ET0 = 1;//允许定时器0中断	
}
/*定时器1初始化*/
void Timer1_Init(void)		
{
	TMOD |= 0x10;	//定时器1工作模式1,16位定时模式。T1用测ECH0脉冲长度
	TH1 = 0;		   
    TL1 = 0;
	ET1 = 1;             //允许T1中断
}
 
/********************* Timer0中断函数************************/
void timer0_int (void) interrupt 1
{
	 pwm_val_left++;
	 pwm_val_right++;
	 LoadPWM();//装载PWM输出
}
/* Timer0 interrupt routine */
void tm1_isr() interrupt 3 using 1
{
	Timer1Overflow = 1;	//计数器1溢出标志位
	EchoPin = 0;		//超声波接收端	
}	
