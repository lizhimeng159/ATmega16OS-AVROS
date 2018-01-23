
#include "Global.h"

int tube[10] = { 0x3f , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d , 0x7d , 0x07 , 0x7f , 0x6f };  ///数码管数字0~9

/************************************************************
Function Name: init_tube
Inputs: none
Outputs: 0
Description:    数码管初始化，P3的a~p接PD0~7，阳极控制段选；P4的0~7接PB的0~7，阴极控制位选
Writer: WZY
*************************************************************/
int init_tube(void)
{
    DDRB = 0XFF ;    ///寄存器设置为输出
    DDRD = 0XFF ;
    PORTB = 0xff ;   ///数码管共阴接法，阴极位选输出高电平，数码管不导通
    return 0 ;
}

/************************************************************
Function Name: tube_on
Inputs: int t
Outputs: none
Description:    8位数码管显示同一个数字0~9之间的给定int值t
Writer: WZY
*************************************************************/
void tube_on(int t)
{
    init_tube();
    PORTB = 0x00 ;   ///阴极电平拉低
    PORTD = tube[t] ;    ///阳极高电平时导通
    delay_ms(1000);
}

/************************************************************
Function Name: tube_circle
Inputs: int c
Outputs: none
Description:    8位数码管从左至右循环显示0~7,循环c次
Writer: WZY
*************************************************************/
void tube_circle(int c)
{
    int i,j ;
    init_tube();
    for( j=0 ; j<c ; j++ )  ///控制循环次数
    {
        for( i=0 ; i<8 ; i++ )
        {
            PORTB = ~(1<<i) ;   ///移位导通二极管
            PORTD = tube[i] ;
            delay_ms(300);
        }
    }
    PORTB = 0xff ;
}
