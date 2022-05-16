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
      
    uint8_t keyValue;
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
      //  keyValue = KEY_Scan();
	//	CheckRun_Mode(keyValue);
	//	RunCommand();
	
	 
        SmgDisplay_Numbers(0,0,0);// SmgDisplay_Numbers(1,1,1);
	  __delay_ms(1000);
      SmgDisplay_Numbers(1,1,1);// SmgDisplay_Numbers(1,1,1);
	  __delay_ms(1000);
	  SmgDisplay_Numbers(2,2,2);//SmgDisplay_Numbers(2,2,2);
	  __delay_ms(1000);
	 SmgDisplay_Numbers(3,3,3); // SmgDisplay_Numbers(3,3,3);
	  __delay_ms(1000);
	 SmgDisplay_Numbers(4,4,4);//  SmgDisplay_Numbers(4,4,4);
	  __delay_ms(1000);
	 SmgDisplay_Numbers(5,5,5);//   SmgDisplay_Numbers(5,5,5);
	  __delay_ms(1000);
	SmgDisplay_Numbers(6,6,6);//  SmgDisplay_Numbers(6,6,6);
	  __delay_ms(1000);
	SmgDisplay_Numbers(7,7,7);//   SmgDisplay_Numbers(7,7,7);
	  __delay_ms(1000);
 
	  SmgDisplay_Numbers(8,8,8);
	  __delay_ms(1000);
	  SmgDisplay_Numbers(9,9,9);
	  __delay_ms(1000);
	  SmgDisplay_Numbers(10,10,10);
	  __delay_ms(1000);
	  SmgDisplay_Numbers(0x0b,0x0b,0x0b);
	 __delay_ms(1000);
	  
		
	}
    
    
    
}

