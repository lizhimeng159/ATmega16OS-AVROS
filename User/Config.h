#ifndef _Config_h_
#define _Config_h_

typedef signed char   SINT8 ;
typedef unsigned char UINT8 ;
typedef unsigned int  UINT16 ;
typedef signed int    SINT16 ;
typedef unsigned long UINT32 ;
typedef signed long   SINT32 ;

#define TRUE 	1
#define FALSE 	0
#define ON   	1
#define OFF 	0

#define   CLI()  cli()
#define   SEI()  sei()
#define   NOP()   __asm__ __volatile__("nop          \n\t")

#endif
