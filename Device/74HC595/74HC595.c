
#include "Global.h"

/************************************************************
Function Name: init_74HC595
Inputs: none
Outputs: none
Description:    移位寄存器端口初始化，PB0(数据线)、PB1(锁存线)、PB2(时钟线)三端口为控制线
Writer: WZY
*************************************************************/
void init_74HC595(void)
{
    DDRB |= 0x07;       ///PB0~2初始化为输出状态
    LCLK_HIGH ;         ///锁存线拉高
}

/************************************************************
Function Name: send_data_to_74HC595
Inputs: int data
Outputs: none
Description:    发送数据给移位寄存器
Writer: XZ,WZY,WH
*************************************************************/
void send_data_to_74HC595(int data)
{
    int i , data_temp=0 ;
    data_temp = data ;
    for (i=0;i<8;i++)                       ///一次只能发送一个字节的数据（8位）
    {
        if( data_temp & (1<<(7-i)) )        ///从高位开始发送
            DATA_HIGH;                      ///数据线拉高
        else
            DATA_LOW;                       ///数据线拉低
        SCLK_HIGH ;                         ///时钟线拉高
        NOP() ; NOP() ;

        SCLK_LOW ;                          ///时钟线拉低
    }
}

/************************************************************
Function Name: display_74HC595
Inputs: int sit, int seg
Outputs: none
Description:    向74HC595发送两次数据,前8位为段选，后八位为位选（选一位）
Writer: XZ,WH,WZY
*************************************************************/
void display_74HC595(int sit, int seg)    ///situation为位,segment为段
{
    init_74HC595();
    LCLK_LOW ;
    send_data_to_74HC595( ~(1<<sit) );
    send_data_to_74HC595( tube[seg] );
    LCLK_HIGH ;
}

/************************************************************
Function Name: tube_0_to_9
Inputs: none
Outputs: none
Description:    8位数码管从0~9循环显示
Writer: WZY,DSY
*************************************************************/
void tube_0_to_9(void)
{
    int i=0,j=0,k=0;
    while (1)
    {
        for( i=0; i<10; i++ )
        {
            for (k=0;k<50;k++)
                {
                    for(j=0;j<8;j++)
                        {
                            display_74HC595(j,i) ;
                        }
                }
            delay_ms(1);
        }
    }
}

/************************************************************
Function Name: tube_liushui
Inputs: int t
Outputs: none
Description:    移位寄存器实现数字流水效果,t控制移位时间(ms)
Writer: WZY
*************************************************************/
void tube_liushui(int t)
{
//    int i=0,j=0;
    while (1)
    {
 //       for( i=0; i<8; i++ )
 //       {
 //           display_74HC595(i,i) ;
   //         delay_ms(t);
  //      }
    }
}

/************************************************************
Function Name:  tube_decimal_num
Inputs: long dec_num
Outputs: none
Description:    用数码管显示一个十进制整数，右对齐
Writer: WZY
*************************************************************/
void tube_decimal_num(long dec_num)
{
    int weishu=0,i=0;
    long num_temp=0;
    num_temp=dec_num;
    do
    {
        num_temp = num_temp/10;
        weishu++;
    }
    while( num_temp!=0 );
  //  while(1)
 //   {
        num_temp=dec_num;
        for( i=0; i<weishu; i++ )
        {
            display_74HC595( 7-i, (num_temp%10) );
            num_temp = num_temp/10;
          //  delay_ms(1);
        }
 //   }
}
