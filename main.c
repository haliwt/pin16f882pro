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
      
    uint8_t keyValue,temp0,i;
	uint8_t  vt[2],vh[2],data[5];
	LED_Init();
	Peripheral_Init();
	DHT11_Init();
	//EPWM_Initialize();
	TM1617_GPIO_Iint();
    TMR1_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    TMR1_StartTimer();
	cmd_t.gCmd_KeyOrder =0xFE;
	 
    while(1)
    {
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

       
  
	__delay_ms(500);
	__delay_ms(500);
#if 1
   DHT11_Reset();
   DHT11_IsOnLine();
    /* ??5???? */
    for (i = 0; i < 5; i++)    
    {
       //data[i]= DHT11_One_ReadByte();
       dht11_read_byte(&temp0);
        
    }
   if (data[4] == (data[0]+data[1]+data[2]+data[3]))
    {
       Breath_RA0_LED  =1;
    }
#endif 

	// DHT11_Read_Data(vt,vh);
	// vh[0] = temp0/100;
	// vt[0] = temp0 / 10 ;
	// vt[1] = temp0 % 10;
  // temp0 = data[2];
   	 vt[0] = (temp0 /10)%10;
	 vt[1] = temp0 %10;
     vh[0] = (temp0/100)%10;
    SmgDisplay_Numbers(vh[0],vt[0],vt[1]);
    
	 
		
	}
    
    
    
}

