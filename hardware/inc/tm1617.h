#ifndef __TM1617_H_
#define __TM1617_H_
#include "../../main.h"

#define TM1617_SDA             PORTBbits.RB2/// P24   //OUTPUT
#define TM1617_SCL             PORTBbits.RB3//   P25 //OUTPUT 
#define TM1617_STB  	       PORTBbits.RB4// P26	 //片选信号




#define ModeDispTM1617      0x40 //写数据到显示寄存器
		
#define AddrAutoAdd		   0x40//写显示，自动累加地址  
#define AddrFixed 		   0x44//写显示，固定地址  
 

#define OpenDispTM1617           	0x88//开显示
#define CloseDisTM1617			 	0x00//关显示
#define Dsip_Mode                   0x03 //显示 3位7段
 
#define Addr00H  			0xC0//地址00H
#define Addr01H  			0xC1//地址01H
#define Addr02H  			0xC2//地址02H
#define Addr03H  			0xC3//地址03H
#define Addr04H  			0xC4//地址04H
#define Addr05H  			0xC5//地址05H
#define Addr06H  			0xC6//地址06H
#define Addr07H  			0xC7//地址07H
#define Addr08H  			0xC8//地址08H
#define Addr09H  			0xC9//地址09H
#define Addr0AH  			0xCA//地址0AH
#define Addr0BH  			0xCB//地址0BH
#define Addr0CH             0xCC//地址0CH
#define Addr0DH             0xCD//地址0DH



 
#define Set1_16TM1617 			0X00//设置脉冲宽度为 1/16 
#define Set2_16TM1617 			0X01//设置脉冲宽度为 2/16 
#define Set4_16TM1617			0X02//设置脉冲宽度为 4/16 
#define Set10_16TM1617 		0X03//设置脉冲宽度为 10/16 
#define Set11_16TM1617 		0X04//设置脉冲宽度为 11/16 
#define Set12_16TM1617		0X05//设置脉冲宽度为 12/16 
#define Set13_16TM1617 		0X06//设置脉冲宽度为 13/16 
#define Set14_16TM1617 		0X07//设置脉冲宽度为 14/16 



void TM1617_GPIO_Iint(void);

void Tm1617_SendData(uint8_t onebyte);





#endif 
