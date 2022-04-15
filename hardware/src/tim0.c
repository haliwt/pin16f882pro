#include "../inc/tim0.h"


volatile uint8_t timer0ReloadVal;
void (*TMR0_InterruptHandler)(void);
static void TIMER0_CallBack_Fun(void);
/**
 * Tim  need timer times setup example 10 000us  
 * Freq = system osc frequency 8MHz
 *__XTAL-FREQ = 8000000 
 * prescale = 128 
 * TMR0 = [256-(__XTAL-FREQ/4)/prescaler * Timer0 overflow(s)]=256-[(800000/4)/128] * 0.01 -1=256-156.25=100=0x64
 * TMR0 = 256 - (Tim(us) * freq /(4 * prescale))  =256 - (1000us * 8)/(4*128)==256-156.25=100  =100 = 0x64
 * 
*/

void TMR0_Initialize(void)
{
    // Set TMR0 to the options selected in the User Interface
	
    // PSA assigned; PS 1:128; TMRSE Increment_hi_lo; mask the nWPUEN and INTEDG bits
    OPTION_REG = 0b00000110; 
	
    // TMR0 100; 
    TMR0 = 0x64;
	
    // Load the TMR value to reload variable
    timer0ReloadVal= 99;

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt
    INTCONbits.TMR0IE = 1;

    // Set Default Interrupt Handler
    TMR0_SetInterruptHandler(TMR0_DefaultInterruptHandler);
}

uint8_t TMR0_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR0;

    return readVal;
}

void TMR0_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer0 register
    TMR0 = timerVal;
}

void TMR0_Reload(void)
{
    // Write to the Timer0 register
    TMR0 = timer0ReloadVal;
}

void TMR0_ISR(void)
{

    // Clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    TMR0 = timer0ReloadVal;

    // ticker function call;
    // ticker is 1 -> Callback function gets called every time this ISR executes
    TMR0_CallBack();

    // add your TMR0 interrupt custom code
}

void TMR0_CallBack(void)
{
    // Add your custom callback code here
    TMR0_InterruptHandler=  TIMER0_CallBack_Fun;

    if(TMR0_InterruptHandler)
    {
        TMR0_InterruptHandler();
    }
}

void TMR0_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR0_InterruptHandler = InterruptHandler;
}

void TMR0_DefaultInterruptHandler(void){
    // add your TMR0 interrupt custom code
    // or set custom function using TMR0_SetInterruptHandler()
}
/******************************************************************
* 
*Function Name: 
*Function : timer0 is 10ms 
*
*
******************************************************************/
static void TIMER0_CallBack_Fun(void)
{
   static uint16_t j;
   static uint8_t jt;
   j++;
   if(j >0){
   	  j=0;
	  jt++;
      cmd_t.gCmd_breathLed++;
	  if(jt==1){
        cmd_t.gCmd_beepTimer =1 ;
	  }
	  else{
	  	jt=0;
		cmd_t.gCmd_beepTimer =0 ;

	  }
   }


}
