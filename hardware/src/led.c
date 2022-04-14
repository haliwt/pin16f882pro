#include "../inc/led.h"

void LED_Init(void)
{
	ANSELbits.ANS0 = 0 ; //as digital I/O
	ANSELbits.ANS1 = 0;
	ANSELbits.ANS2 = 0;
	ANSELbits.ANS3 =0 ;

	ANSELHbits.ANS10 = 0; //RB1
	ANSELHbits.ANS8  =0;   //RB2

	TRISAbits.TRISA0 = 0; //as output I/O
	TRISAbits.TRISA1 = 0;
	TRISAbits.TRISA2 = 0;
	TRISAbits.TRISA3 = 0;

	TRISBbits.TRISB1 = 0;
	TRISBbits.TRISB2 = 0;

	PORTA = 0x0;
	PORTC = 0x0;
	

	
}


