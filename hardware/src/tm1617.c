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

   // for(i=0;i<8;i++){

   //    TM1617_SCL =0 ;
     
   //    if(onebyte & (1<<i)){

	// 	  TM1617_SDA =1;
        
      
	//   }
	//   else{

	// 	 TM1617_SDA =0;
      
	//   }
   
	//   TM1617_SCL =1;
  


   // }
   
  for(i=0;i<8;i++)
  {	
  	TM1617_SCL=0;
    if(onebyte&0x01) 
	   TM1617_SDA=1;
	else         
	   TM1617_SDA=0;
	//_nop_();
	//_nop_();
	//_nop_();
   __delay_us(3);
	TM1617_SCL=1;	 
	onebyte>>=1;	 
  }
  TM1617_SCL=0;
  TM1617_SDA=0;

}


/******************发送控制命令***********************/
void send_command(uint8_t com)                             //发送命令字节
{
 TM1617_STB=1;	                                                 //STB置高
 //nop;
 __delay_us(1);
 TM1617_STB=0;	                                                //STB置低
 Tm1617_SendData(com);    
 TM1617_STB =1;                                     //发送8bit数据
}



