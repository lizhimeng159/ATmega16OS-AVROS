
#ifndef _ATMEGA16OS_H_
#define _ATMEGA16OS_H_

#define OS_ENTER_CRITICAL() cli()
#define OS_EXIT_CRITICAL()  sei()

//任务控制块的定义
struct Os_Tcb
{
	UINT16  StkPtr;        //储存任务堆栈
	void    (*Function)(); //指向函数指针
	UINT8   Priority;      //任务优先级
	UINT16  DelayTick;     //延时节拍数 10ms为一个节拍
	UINT8   SemFlag;
};

//定义任务控制块
struct Os_Tcb TCB[8];

extern void ATmega16OS_Start(void);
extern void ATmega16OS_Init(void);
extern void ATmega16OS_TaskCreate(void (*Task)(void), UINT8 *P_Stk, UINT8 Prio);
extern void ATmega16OS_Time_Delay(UINT16 Ticks);
extern void ATmega16OS_Task_Sem_Suspend(void);
extern void ATmega16OS_Task_Sem_Post(void (*Task)(void));

extern UINT8 Idle_Task_Stk[64];

extern void ATmega16OS_Idle_Task(void);
#endif
