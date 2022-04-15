#include "../inc/led.h"

static void Delay(uint16_t t);

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

void Breath_Led(void)
{
    
    static uint16_t pwm =0;
    for(pwm=500;pwm>0;pwm--){
		  
        Breath_RA0_LED =1 ;//On
        Delay(pwm);//__delay_ms(pwm);
        //__delay_ms(pwm);
        Breath_RA0_LED=0 ; //off
        Delay(500-pwm);//__delay_ms(500-pwm);


   }

   for(pwm=0;pwm<500;pwm++){

        Breath_RA0_LED =1 ;//On
        Delay(pwm);//__delay_ms(pwm);
        Breath_RA0_LED=0 ; //off
        Delay(500-pwm);//__delay_ms(500-pwm);

     }



}


void PowerOn_LED_Fun(void)
{
	Breath_RA0_LED  =1; 	   	
    powerOn_RA1_LED  =1;    	
  //  PTC_RA2_LED         	
   // Temp_RB1_LED  =1;      	 
   // Hum_RB2_LED         
   Smart_RA3_LED  =1;     	



}


static void Delay(uint16_t t)
{
    while(--t);
}


