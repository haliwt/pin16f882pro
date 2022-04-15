#include "../inc/tim1.h"

/**
  Section: Global Variables Definitions
*/
volatile uint16_t timer1ReloadVal;
void (*TMR1_InterruptHandler)(void);

static void TIMER1_CallBack_Fun(void);

/**
 **
*
*Functin Name: void TIMER1_Init(void)
*Funciton : timer1 is 1ms 
            prescaler =1
*           Timer0 overflow = 256 * prescaler * (__XTAL_FREQ / 4)= 256 * 4 * 1us = 1024us = 1.024ms
*           TMR1H:TMR1L = [65536-(__XTAL-FREQ/4)/prescaler * Timer0 overflow(s)]
*				 =(65536 - [(8000000/4)/prscaler] * 0.001s) -1 = 65536 - 2000= 63535
*           Tim is need timer ,explame 1000us -unit us
*           Freq = system clock frequency is = 8MHz 
*           prescaler = 1,2,4,8,
			prscale=1
*           TMR1H:TMR1L = 65536-[(Tim*Freq)/(4*precals)] -1=65536-((1000 * 8)/(4*1))=63536-2000=63536 =0xF830
            prscaler = 8 
*           TMR1H:TMR1L = 65536-[(Tim*Freq)/(4*precals)] -1=65536-((1000 * 8)/(4*8))=65536-250 =65286 =0xff06
*
*           prescaler = 8:
*           TMR1H:TMR1L =65536 -(Times)/(4x1/freq * prescaler) = 65536- 1000us/(4*0.125 * 8) =65536-250 =65286
*/

void TMR1_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //T1GSS T1G_pin; TMR1GE disabled; T1GTM disabled; T1GPOL low; T1GGO done; T1GSPM disabled; 
  

    //TMR1H 248; 
    TMR1H = 0xF8;

    //TMR1L 48; 
    TMR1L = 0x30;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR1IF = 0;

    // Load the TMR value to reload variable
    timer1ReloadVal=(uint16_t)((TMR1H << 8) | TMR1L);

    // Enabling TMR1 interrupt.
    PIE1bits.TMR1IE = 1;

    // Set Default Interrupt Handler
    TMR1_SetInterruptHandler(TMR1_DefaultInterruptHandler);

    // T1CKPS 1:1; T1OSCEN disabled; nT1SYNC synchronize; TMR1CS FOSC/4; TMR1ON enabled; 
    T1CON = 0x01;
}

void TMR1_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

void TMR1_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

uint16_t TMR1_ReadTimer(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
	
    readValLow = TMR1L;
    readValHigh = TMR1H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

void TMR1_WriteTimer(uint16_t timerVal)
{
    if (T1CONbits.nT1SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (uint8_t)(timerVal >> 8);
        TMR1L = (uint8_t)timerVal;

        // Start the Timer after writing to the register
        T1CONbits.TMR1ON =1;
    }
    else
    {
        // Write to the Timer1 register
        TMR1H = (uint8_t)(timerVal >> 8);
        TMR1L = (uint8_t)timerVal;
    }
}

void TMR1_Reload(void)
{
    TMR1_WriteTimer(timer1ReloadVal);
}

void TMR1_ISR(void)
{

    // Clear the TMR1 interrupt flag
    PIR1bits.TMR1IF = 0;
    TMR1_WriteTimer(timer1ReloadVal);

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    TMR1_CallBack();
}

void TMR1_CallBack(void)
{
    // Add your custom callback code here
    if(TMR1_InterruptHandler)
    {
        TMR1_InterruptHandler();
    }
}

void TMR1_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR1_InterruptHandler = InterruptHandler;
}

void TMR1_DefaultInterruptHandler(void){
    // add your TMR1 interrupt custom code
    // or set custom function using TMR1_SetInterruptHandler()
}
/*********************************************************************
*
*Functin Name:static void TIMER1_CallBack_Fun(void)
*Function:
*Input Ref:NO
*Return Ref:NO
*
**********************************************************************/
static void TIMER1_CallBack_Fun(void)
{
	
     static uint16_t i,ti;
	 i++ ;
	 
	 if(i>999){ //1s

       i=0;
	   ti++;
	   if(ti==1){
           cmd_t.gCmd_dispTimerTask=1;
	   }
	   else{
           cmd_t.gCmd_dispTimerTask=0;
           ti=0;

	   }

	 }
	 
	 


}
