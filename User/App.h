#ifndef _APP_H_
#define _APP_H_

#include "Global.h"

extern UINT8 LED_Task_Stk[64];
extern UINT8 Tube_Task_Stk[64];
extern UINT8 Buzzer_Task_Stk[64];

extern void LED_Task(void);
extern void Tube_Task(void);
extern void Buzzer_Task(void);
extern void Bsp_Init(void);


#endif
