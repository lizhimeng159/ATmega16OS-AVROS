
#include "Global.h"

//创建任务就绪表
//任务 优先级为 x x x x x x x x
//              7 6 5 4 3 2 1 0
//其中，0的优先级最高，7的优先级最低
UINT8 OSRdyTbl;

//当前任务就绪表中的最高位
UINT8 OSPrioHighRdy;

//当前的优先级
UINT8 OSPrioCur;

//定义一个空闲函数自增的变量
UINT32 Idle_Count = 0;

//定义空闲任务堆栈
UINT8 Idle_Task_Stk[64];

//提前声明函数
void OSSched(void);
void ATmega16OS_Task_Switch(void);
void ATmega16OS_Time_Delay(UINT16 Ticks);
void ATmega16OS_SysTick_Init(void);

//设置相应的任务为 就绪状态
void ATmega16OS_SetPrioRdy(UINT8 Prio)
{
	OSRdyTbl |= 0x01 << Prio;
}

//用于讲某任务在任务就绪表中删除
void ATmega16OS_DelPrioRdy(UINT8 Prio)
{
	OSRdyTbl &= ~(0x01 << Prio);
}

//从任务就绪表中选出优先级别最高的任务
void ATmega16OS_GetHighRdy(void)
{
	SINT8 Temp_OSNextTaskPrio  = 7;
	UINT8 Final_OSNextTaskPrio = 7;
	for (Temp_OSNextTaskPrio = 7; Temp_OSNextTaskPrio >= 0; Temp_OSNextTaskPrio--)
    {
		if (OSRdyTbl&(0x01 << Temp_OSNextTaskPrio))
		{
			Final_OSNextTaskPrio = Temp_OSNextTaskPrio;
		}
    }
	//赋值最高优先级任务
	OSPrioHighRdy = Final_OSNextTaskPrio;
}

//OS的任务创建函数
//变量依次如下
//函数指针 任务堆栈  任务优先级
void ATmega16OS_TaskCreate(void (*Task)(void), UINT8 *P_Stk, UINT8 Prio)
{
		*(P_Stk--) = (UINT16)Task   ;       
		*(P_Stk--) = (UINT16)Task>>8;      

		*(P_Stk--) = 0x00   ;                //R 1
		*(P_Stk--) = 0x00;                   //R 0 

		*(P_Stk--) = 0x00;                   //SREG
		*(P_Stk--) = 0x02;                   //R 2
		*(P_Stk--) = 0x03;                   //R 3
		*(P_Stk--) = 0x04;                   //R 4
		*(P_Stk--) = 0x05;                   //R 5
		*(P_Stk--) = 0x06;                   //R 6
		*(P_Stk--) = 0x07;                   //R 7
		*(P_Stk--) = 0x08;                   //R 8
		*(P_Stk--) = 0x09;                   //R 9
		*(P_Stk--) = 0x0A;                   //R10
		*(P_Stk--) = 0x0B;                   //R11
		*(P_Stk--) = 0x0C;                   //R12
		*(P_Stk--) = 0x0D;                   //R13
		*(P_Stk--) = 0x0E;                   //R14
		*(P_Stk--) = 0x0F;                   //R15
		*(P_Stk--) = 0x10;                   //R16
		*(P_Stk--) = 0x11;                   //R17
		*(P_Stk--) = 0x12;                   //R18
		*(P_Stk--) = 0x13;                   //R19
		*(P_Stk--) = 0x14;                   //R20
		*(P_Stk--) = 0x15;                   //R21
		*(P_Stk--) = 0x16;                   //R22
		*(P_Stk--) = 0x17;                   //R23
		*(P_Stk--) = 0x18;                   //R24
		*(P_Stk--) = 0x19;                   //R25
		*(P_Stk--) = 0x1A;                   //R26
		*(P_Stk--) = 0x1B;                   //R27
		*(P_Stk--) = 0x1C;                   //R28
		*(P_Stk--) = 0x1D;                   //R29
		*(P_Stk--) = 0x1E;                   //R30
		*(P_Stk--) = 0x1F;                   //R31
        
		//写入任务就绪表
		ATmega16OS_SetPrioRdy(Prio);
		
        //函数指针指向
		TCB[Prio].Function = Task;

		//任务相应的TCB堆栈指向这里
        TCB[Prio].StkPtr = (UINT16)P_Stk;  

		//置位任务的优先级
		TCB[Prio].Priority = Prio;

        //初始化任务节拍数
		TCB[Prio].DelayTick = 0;
}

//操作系统启动函数
void ATmega16OS_Start(void)
{
	//先找到优先级别做高的任务
	ATmega16OS_GetHighRdy();
    //赋值当前优先级
	OSPrioCur = OSPrioHighRdy;
    //更改SP指向，准备弹出，PC更改至最高优先级堆栈的函数入口
    SP = TCB[OSPrioCur].StkPtr + 33;

}

//任务切换函数
void ATmega16OS_Task_Switch(void)
{
	//找到优先级别做高的任务
	ATmega16OS_GetHighRdy();
    //这里执行任务切换函数
	OSSched();
}

//操作系统初始化函数
void ATmega16OS_Init(void)
{
	//创建系统心脏
	ATmega16OS_SysTick_Init();
	//创建空闲任务
	ATmega16OS_TaskCreate(ATmega16OS_Idle_Task,&Idle_Task_Stk[63],7);
}

//运行的空闲任务
void ATmega16OS_Idle_Task(void)
{
	while (ON)
	{
		Idle_Count++;
	}
}

//系统心跳初始化 用的TIM2 10ms一次
void ATmega16OS_SysTick_Init(void)
{    
     //打开定时器中断使能
     MCUCR |=(1<<TOIE2);	
     //定时器中断使能
     TIMSK|=(1<<TOIE2);
	 //定时器赋初值 
     TCNT2 =0;
	 //64分频
     TCCR2 |= ((1 << CS01)|(1 << CS00));
}

//系统心脏定时器任务钩子函数 10ms进入一次
void ATmega16OS_Tick_Hook(void)
{
	UINT8 i = 0;
	for(i = 0;i < 8;i++)
	{
	   if(TCB[i].DelayTick != 0)
	   {
	      TCB[i].DelayTick--;
		  if(TCB[i].DelayTick == 0)
		  {
		     ATmega16OS_SetPrioRdy(i);
		  }
	   }
	}
	//找到优先级别做高的任务，并进行任务调度
	ATmega16OS_Task_Switch();
}

//任务挂起函数
void ATmega16OS_Task_Sem_Suspend(void)
{
    //删除目前优先级最高的任务
	ATmega16OS_DelPrioRdy(OSPrioCur);
	//进行任务调度
	ATmega16OS_Task_Switch();
}

//发送信号量函数
void ATmega16OS_Task_Sem_Post(void (*Task)(void))
{
    UINT8 Temp_Pro;
	//获取优先级
	for(Temp_Pro = 0;Temp_Pro < 8;Temp_Pro++)
	{
	    if(TCB[Temp_Pro].Function == Task)
		{
		    break;
		}
	}
    //置位相应的优先级
	ATmega16OS_SetPrioRdy(Temp_Pro);
	//进行任务调度
	ATmega16OS_Task_Switch();
}

//定时器延时函数
void ATmega16OS_Time_Delay(UINT16 Ticks)
{
	//更新任务就绪表
	ATmega16OS_DelPrioRdy(OSPrioCur);
	//设置始终节拍数
	TCB[OSPrioCur].DelayTick = Ticks;
	//有关任务切换
	ATmega16OS_Task_Switch();
}

void OSSched(void)
{
	OS_ENTER_CRITICAL();

	if (OSPrioHighRdy != OSPrioCur)
	{
		__asm__ __volatile__("PUSH __zero_reg__          \n\t");
		__asm__ __volatile__("PUSH __tmp_reg__           \n\t");
		__asm__ __volatile__("IN   __tmp_reg__,__SREG__  \n\t");
		__asm__ __volatile__("PUSH __tmp_reg__           \n\t");
		__asm__ __volatile__("PUSH R2                    \n\t");
		__asm__ __volatile__("PUSH R3                    \n\t");
		__asm__ __volatile__("PUSH R4                    \n\t");
		__asm__ __volatile__("PUSH R5                    \n\t");
		__asm__ __volatile__("PUSH R6                    \n\t");
		__asm__ __volatile__("PUSH R7                    \n\t");
		__asm__ __volatile__("PUSH R8                    \n\t");
		__asm__ __volatile__("PUSH R9                    \n\t");
		__asm__ __volatile__("PUSH R10                   \n\t");
		__asm__ __volatile__("PUSH R11                   \n\t");
		__asm__ __volatile__("PUSH R12                   \n\t");
		__asm__ __volatile__("PUSH R13                   \n\t");
		__asm__ __volatile__("PUSH R14                   \n\t");
		__asm__ __volatile__("PUSH R15                   \n\t");
		__asm__ __volatile__("PUSH R16                   \n\t");
		__asm__ __volatile__("PUSH R17                   \n\t");
		__asm__ __volatile__("PUSH R18                   \n\t");
		__asm__ __volatile__("PUSH R19                   \n\t");
		__asm__ __volatile__("PUSH R20                   \n\t");
		__asm__ __volatile__("PUSH R21                   \n\t");
		__asm__ __volatile__("PUSH R22                   \n\t");
		__asm__ __volatile__("PUSH R23                   \n\t");
		__asm__ __volatile__("PUSH R24                   \n\t");
		__asm__ __volatile__("PUSH R25                   \n\t");
		__asm__ __volatile__("PUSH R26                   \n\t");
		__asm__ __volatile__("PUSH R27                   \n\t");
		__asm__ __volatile__("PUSH R28                   \n\t");
		__asm__ __volatile__("PUSH R29                   \n\t");
		__asm__ __volatile__("PUSH R30                   \n\t");
		__asm__ __volatile__("PUSH R31                   \n\t");  //入栈完成

        TCB[OSPrioCur].StkPtr = SP;
        OSPrioCur = OSPrioHighRdy;
        SP = TCB[OSPrioCur].StkPtr;

		__asm__ __volatile__("POP  R31                   \n\t");
		__asm__ __volatile__("POP  R30                   \n\t");
		__asm__ __volatile__("POP  R29                   \n\t");
		__asm__ __volatile__("POP  R28                   \n\t");
		__asm__ __volatile__("POP  R27                   \n\t");
		__asm__ __volatile__("POP  R26                   \n\t");
		__asm__ __volatile__("POP  R25                   \n\t");
		__asm__ __volatile__("POP  R24                   \n\t");
		__asm__ __volatile__("POP  R23                   \n\t");
		__asm__ __volatile__("POP  R22                   \n\t");
		__asm__ __volatile__("POP  R21                   \n\t");
		__asm__ __volatile__("POP  R20                   \n\t");
		__asm__ __volatile__("POP  R19                   \n\t");
		__asm__ __volatile__("POP  R18                   \n\t");
		__asm__ __volatile__("POP  R17                   \n\t");
		__asm__ __volatile__("POP  R16                   \n\t");
		__asm__ __volatile__("POP  R15                   \n\t");
		__asm__ __volatile__("POP  R14                   \n\t");
		__asm__ __volatile__("POP  R13                   \n\t");
		__asm__ __volatile__("POP  R12                   \n\t");
		__asm__ __volatile__("POP  R11                   \n\t");
		__asm__ __volatile__("POP  R10                   \n\t");
		__asm__ __volatile__("POP  R9                    \n\t");
		__asm__ __volatile__("POP  R8                    \n\t");
		__asm__ __volatile__("POP  R7                    \n\t");
		__asm__ __volatile__("POP  R6                    \n\t");
		__asm__ __volatile__("POP  R5                    \n\t");
		__asm__ __volatile__("POP  R4                    \n\t");
		__asm__ __volatile__("POP  R3                    \n\t");
		__asm__ __volatile__("POP  R2                    \n\t");
		__asm__ __volatile__("POP  __tmp_reg__           \n\t");
		__asm__ __volatile__("OUT  __SREG__,__tmp_reg__  \n\t");
		__asm__ __volatile__("POP  __tmp_reg__           \n\t"); 
		__asm__ __volatile__("POP  __zero_reg__          \n\t"); 
	}

	OS_EXIT_CRITICAL();
}


SIGNAL(SIG_OVERFLOW2)
{
    OS_ENTER_CRITICAL();

	TCNT2 = 100;
	ATmega16OS_Tick_Hook();

	OS_EXIT_CRITICAL();
}
