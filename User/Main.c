/******************包含系统头文件***************/
#include "Global.h"
/****************主函数***************/
int main(void)
{
	 CLI();
     Bsp_Init();
	 ATmega16OS_Init();
	 ATmega16OS_TaskCreate(LED_Task, &LED_Task_Stk[63] ,0);
	 ATmega16OS_TaskCreate(Buzzer_Task, &Buzzer_Task_Stk[63] ,1);
	 ATmega16OS_TaskCreate(Tube_Task,&Tube_Task_Stk[63],2);
	 SEI();
	 ATmega16OS_Start();
	 while(1)
	 {
	     ;
	 }
}
