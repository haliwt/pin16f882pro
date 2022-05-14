#include "../inc/led.h"

static void Delay(uint16_t t);

void LED_Init(void)
{
	
   
	

	TRISAbits.TRISA0 = 0; //as output I/O
	TRISAbits.TRISA1 = 0;
	TRISAbits.TRISA2 = 0;
	TRISAbits.TRISA3 = 0;

	TRISBbits.TRISB1 = 0;
	TRISBbits.TRISB2 = 0;
    
    
    PORTAbits.RA0=0;
	PORTAbits.RA1 =0;
    PORTAbits.RA2 =0;
    PORTAbits.RA3 =0;
    
    PORTBbits.RB1 =0;
    PORTBbits.RB2 = 0;
    

 }

void Breath_Led(void)
{
    
    static uint16_t i,t;

 #if 1
   
        for(i = 0; i < 600; i++){
            Breath_RA0_LED =1 ; //LED1?             delay_us(t); //??t us
            Delay(i);
            Breath_RA0_LED =0 ; //LED1?
            Delay(600-i); //??501-t us
        }
       
    

      for(i = 600; i > 0; i--){
           
            Breath_RA0_LED =1 ; //??t
             Delay(i); //LED1?
            Breath_RA0_LED =0; //LED1?
             Delay(600-i); //??501-t
        }
      
#endif 


}


void PowerOn_LED_On(void)
{
	Breath_RA0_LED  =1; 	   	
    TIMEER_RA1_LED  =1;    	
  //  PTC_RA2_LED         	
   // Temp_RB1_LED  =1;      	 
   // Hum_RB2_LED         
   Smart_RA3_LED  =1;     	



}
void PowerOn_LED_Off(void )
{
	Breath_RA0_LED   =0; 	   	
    TIMEER_RA1_LED  =0;    	
  //  PTC_RA2_LED         	
   // Temp_RB1_LED  =1;      	 
   // Hum_RB2_LED         
   Smart_RA3_LED  =0;     

}



static void Delay(uint16_t t)
{
   
    while(t--);
     
    
     
}


