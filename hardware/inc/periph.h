#ifndef __PERIPH_H_
#define __PERIPH_H_
#include "../../main.h"

#define Beep_RC1_Out 		PORTCbits.RC1 
#define Fan_RC5_Out         PORTCbits.RC5
#define PTC_RC4_Out         PORTCbits.RC4 

void Peripheral_Init(void);

void Beep_Fun(void);

void PTC_Fun(void);




#endif 
