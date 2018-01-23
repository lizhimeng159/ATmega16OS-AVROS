/********************************************************************************************************/
#ifndef _USART_H
#define _USART_H
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "../Headers/Global.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

//UCSRA相关宏定义
//标志位
#define USART_FLAG_RXC     0x80   //接收结束
#define USART_FLAG_TXC     0x40   //发送结束
#define USART_FLAG_UDRE    0x20   //数据寄存器空
//控制位
#define USART_U2X          0x02   //倍速发送

//UCSRB相关宏定义
//控制位
#define USART_RXCIE        0x80   //接收结束中断使能
#define USART_TXCIE        0x40   //发送结束中断使能
#define USART_UDRIE        0x20   //数据寄存器空中断使能
#define USART_RXEN         0x10   //接收使能
#define USART_TXEN         0x08   //发送使能
#define USART_UCSZ2        0x04   //字符长度  和其他位配合使用

//UCSRC相关宏定义
//控制位
#define UCSRC_URSEL        0x80   //寄存器选择
#define USART_UMSEL        0x40   //USART模式选择
#define USART_UPM          0x30   //奇偶校验模式选择
#define USART_USBS         0x08   //停止位选择
#define USART_UCSZ1        0x04   //字符长度
#define USART_UCSZ0        0x02   //字符长度

//UBRRH相关宏定义
#define UBRRH_URSEL        0x8000 //寄存器选择

/*--------------------------------------  D E C L A R A T I O N  --------------------------------------*/
/* Internal Variable */

/* External Variable */

/* Internal Function */

/* External Function */
extern void USART_Init(UINT16 baud);
extern  UINT8 USART_Rx(void);
extern void USART_Tx(UINT8 buf);

#endif /*_USART_H*/
//===========================================  End Of File  ===========================================//
