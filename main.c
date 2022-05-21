/* 
 * File:   main.c
 * Author: YYJ-2
 *
 * Created on April 12, 2022, 3:30 PM
 */


#include "main.h"
#pragma config FOSC = 0x01, WDTE = 0x0, PWRTE = 0x1, CP = 0x1, BOREN = 0x0
/*
 * 
 */
void  main(void) 
{
      
    uint8_t keyValue,temp0,temp1,temp2,temp3,temp4,i;
	uint8_t  vt[3],vh[3],vt0[3],vh0[3],vhl0[3],data[5],ver;
	LED_Init();
	Peripheral_Init();
	DHT11_Init();
    TMR2_Initialize();
	//EPWM_Initialize();
	TM1617_GPIO_Iint();
    TMR1_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    TMR1_StartTimer();
	cmd_t.gCmd_KeyOrder =0xFE;
	 
    while(1)
    {
        
        
        __delay_ms(500);
	__delay_ms(500);

#if 0
        if(cmd_t.gCmd_dispTemperatureTask==1 && cmd_t.gCmd_PowerOn !=powerOn ){
            Breath_Led();
		}
		else{
		   keyValue = KEY_Scan();
		}
#endif 
       // keyValue = KEY_Scan();
	//	CheckRun_Mode(keyValue);
	//	RunCommand();
     


  
	
#if 0
   DHT11_Reset();
   //DHT11_IsOnLine();
    if(DHT11_IsOnLine()==0){
   // for (i = 0; i < 5; i++)    
    {
      
       DHT11_Read_One_Byte(&data[0]);
        DHT11_Read_One_Byte(&data[1]);
         DHT11_Read_One_Byte(&data[2]);
         DHT11_Read_One_Byte(&data[3]);
         DHT11_Read_One_Byte(&data[4]);
       //data[i] =DHT11_ReadByte() ;  
       //data[i] = Read_Byte(); 
    //    dht11_read_byte(&data[0]);
    //     dht11_read_byte(&data[1]);
    //      dht11_read_byte(&data[2]);
    //       dht11_read_byte(&data[3]);
    //        dht11_read_byte(&data[4]);
     
   
        
    }

   if (data[4] == (data[0]+data[1]+data[2]+data[3]))
    {
       Breath_RA0_LED  =1;
    }
   }
#endif 
#if 1
   __delay_ms(500);
	__delay_ms(500);

    //DHT11_Read_Data(&temp0,&temp1)    ;
 	DHT11_Reset();
	
	if(DHT11_IsOnLine() == 0){
    DHT11_ReadBit(&temp0); 	
    // temp0 = DHT11_Read_Humidity();
   	vt[0] = (temp0 /10)%10;
	vt[1] = temp0 %10;
    vt[2] = (temp0/100)%10;
    SmgDisplay_Numbers(vt[2],vt[0],vt[1]);
   __delay_ms(1000);
    
     temp2 = dht_dat[1];//data[1];
   	 vt0[0] = (temp2 /10)%10;
	 vt0[1] = temp2 %10;
     vt0[2] = (temp2/100)%10;
    SmgDisplay_Numbers(vt0[2],vt0[0],vt0[1]);
    __delay_ms(1000);
    
   // temp1 = dht_dat[2]  ; //data[2];
   	 vh[0] = (temp1 /10)%10;
	 vh[1] = temp1 %10;
     vh[2] = (temp1/100)%10;
     SmgDisplay_Numbers( vh[2],vh[0],vh[1]);
	 __delay_ms(1000);
     
      temp3 = dht_dat[3]; //data[3];
   	 vh0[0] =  (temp3 /10)%10;
	 vh0[1] = temp3 %10;
     vh0[2] = (temp3/100)%10;
     SmgDisplay_Numbers(vh0[2],vh0[0],vh0[1]);
	 __delay_ms(1000);

    //  temp4 =dht_dat[1] ;// data[4];
   	//  vhl0[0] =  (temp4 /10)%10;
	//  vhl0[1] = temp4 %10;
    //  vhl0[2] = (temp4/100)%10;
    //  SmgDisplay_Numbers(vhl0[2],vhl0[0],vhl0[1]);
	//  __delay_ms(1000);
    }
#endif 		
	
    }
    
    
    
}



