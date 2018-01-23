/******************包含系统头文件***************/
#include "App.h"
/****************主函数***************/

//创建任务堆栈
UINT8 LED_Task_Stk[64];
UINT8 Tube_Task_Stk[64];
UINT8 Buzzer_Task_Stk[64];

//定义数码管变量
UINT16  Right_Value = 0;
UINT16  Left_Value  = 0;

UINT8 One;
UINT8 Two;
UINT8 Three;
UINT8 Four;
UINT8 Five;
UINT8 Six;
UINT8 Seven;
UINT8 Eight;

//创建LED灯任务
void LED_Task(void)
{
    while(1)
    {
        PORTC=0b11111111;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11111110;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11111100;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11111000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11110000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11100000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11000000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b10000000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b00000000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;

		ATmega16OS_Task_Sem_Post(Buzzer_Task);

		PORTC=0b10000000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11000000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11100000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11110000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11111000;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11111100;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11111110;
		ATmega16OS_Time_Delay(20);
		Right_Value++;
		PORTC=0b11111111;
		ATmega16OS_Time_Delay(20);
		Right_Value++;	
    }
}

//创建数码管任务
void Tube_Task(void)
{
    while(1)
    {   
	    One   = Left_Value/1000;
		Two   = Left_Value/100%10;
		Three = Left_Value/10%10;
		Four  = Left_Value%10;

		Five  = Right_Value/1000;
		Six   = Right_Value/100%10;
		Seven = Right_Value/10%10;
		Eight = Right_Value%10;

	    display_74HC595(0,One);
	    display_74HC595(1,Two);
		display_74HC595(2,Three);
		display_74HC595(3,Four);
		display_74HC595(4,Five);
		display_74HC595(5,Six);
		display_74HC595(6,Seven);
		display_74HC595(7,Eight);
    }
}

//创建蜂鸣器任务
void Buzzer_Task(void)
{
    while(1)
	{
	    ATmega16OS_Task_Sem_Suspend();
	    fast_PWM(50);
		Left_Value++;
		Left_Value = Left_Value%10000;
	    ATmega16OS_Time_Delay(20);
		TCCR0 = 0b00000000;
	}
}

void Bsp_Init(void)
{
    MCUCSR=0x80;
    MCUCSR=0x80;
	DDRC=0xff;
	DDRB=0xff;
}
