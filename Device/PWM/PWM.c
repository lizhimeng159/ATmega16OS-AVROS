
#include "Global.h"

/************************************************************
Function Name: fast_PWM
Inputs: int percent
Outputs: none
Description:    快速PWM模式，占空比可调
Writer: WZY
*************************************************************/
void fast_PWM(int percent)
{
    DDRB |= (1<<3);
    PORTB &= ~(1<<3);
    TCNT0 = 0x00;
    OCR0 = percent*255/100;
    TCCR0 = 0b01101001;
}
