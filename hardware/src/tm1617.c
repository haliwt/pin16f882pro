#include "../inc/tm1617.h"




void TM1617_GPIO_Iint(void)
{
   //TRISB = 0b11000000; //PB7,PB6 don't be used to gpio.
   TRISBbits.TRISB5 = 0;
   TRISBbits.TRISB4 =0 ;
   TRISBbits.TRISB3 = 0;
   
   ANSELHbits.ANS13 = 0 ; //as digital gpio
    
   ANSELHbits.ANS11 =0 ;
   ANSELHbits.ANS9 =0;
 
}




void Tm1617_SendData(uint8_t onebyte)
{
   uint8_t i;

   for(i=0;i<8;i++){

      TM1617_SCL =0 ;

      if(onebyte & (1<<i)){

		TM1617_SDA =1;

	  }
	  else{

		 TM1617_SDA =0;
	  }

	  TM1617_SCL =1;


   }
   	



}






