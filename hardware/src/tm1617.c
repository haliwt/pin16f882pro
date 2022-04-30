#include "../inc/tm1617.h"




void TM1617_GPIO_Iint(void)
{
  
   TRISBbits.TRISB2 = 0;
   TRISBbits.TRISB4 =0 ;
   TRISBbits.TRISB3 = 0;
   
  
 
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






