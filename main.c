/* 
 * File:   main.c
 * Author: YYJ-2
 *
 * Created on April 12, 2022, 3:30 PM
 */


#include "main.h"
#pragma config FOSC = 0x1, WDTE = 0x0, PWRTE = 0x1, CP = 0x1, BOREN = 0x0
/*
 * 
 */
void  main(void) 
{
      
    uint8_t keyValue;
	LED_Init();
	Peripheral_Init();
	DHT11_Init();
	EPWM_Initialize();
	TMR0_Initialize();
	TM1617_GPIO_Iint();
    
    TMR1_StartTimer();
	cmd_t.gCmd_KeyOrder =0xFE;
    while(1)
    {
    	keyValue = KEY_Scan();
		CheckRun_Mode(keyValue);
		RunCommand();
		Check_TimeTotime_Fun(); //timer be check auto shut down
		
    
    }
    
    
    
}

