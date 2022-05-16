#ifndef __TM1617_H_
#define __TM1617_H_
#include "../../main.h"

#define TM1617_SDA             PORTBbits.RB2/// P24   //OUTPUT
#define TM1617_SCL             PORTBbits.RB3//   P25 //OUTPUT 
#define TM1617_STB  	       PORTBbits.RB4// P26	 //片选信号







void TM1617_GPIO_Iint(void);

void Tm1617_SendData(uint8_t onebyte);

void send_command(uint8_t com)  ;



#endif 
