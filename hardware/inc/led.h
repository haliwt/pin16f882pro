#ifndef __LED_H_
#define __LED_H_
#include "../../main.h"

#define Breath_RA0_LED   	   	 PORTAbits.RA0 
#define powerOn_RA1_LED      	 PORTAbits.RA1
#define PTC_RA2_LED         	 PORTAbits.RA2 
#define Temp_RB1_LED        	 PORTBbits.RB1
#define Hum_RB2_LED         	 PORTBbits.RB2
#define Smart_RA3_LED       	 PORTAbits.RA3



void LED_Init(void);
void Breath_Led(void);

void PowerOn_LED_On(void);

void PowerOn_LED_Off(void);



#endif 
