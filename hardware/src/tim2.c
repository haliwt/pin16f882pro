#include "../inc/tim2.h"



void (*TMR2_InterruptHandler)(void);


/*****************************************************************************************
*
*Function Name:void TMR2_Initialize(void)
*Function : Frequency is 25KHz , Tperiod = 0.04ms,Freq =8MHz ,prescale = 
*           need timers is  0.04ms = 40us ,prescale = 4 
*TMR2 = 256 - (40us)/(4 * (1/Freq) * prescale) = 256 -40/(4 * 0.125 *4)=256-20=236= 0xEC
*prescale = 4
* PR2 = PWM Period /(4 * Tosc * prescale) -1 = 40us / (4*0.125 *4) -1=20 -1  =19 =0X13
*
*
*****************************************************************************************/

void TMR2_Initialize(void)
{
    // Set TMR2 to the options selected in the User Interface

   // TMR2 236; 
    TMR2 =0xEC;

    // PR2 19; 
     PR2 = 0x13;
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;

	  // Set Default Interrupt Handler
    TMR2_SetInterruptHandler(TMR2_DefaultInterruptHandler);
   
   // T2CKPS 1:4; T2OUTPS 1:1; TMR2ON on; 
    T2CON = 0B00000101;//0x80;

   

}




void TMR2_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

void TMR2_StartTimer(void)
{
    TMR2_Start();
}

void TMR2_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

void TMR2_StopTimer(void)
{
    TMR2_Stop();
}

uint8_t TMR2_Counter8BitGet(void)
{
    uint8_t readVal;

    readVal = TMR2;

    return readVal;
}

uint8_t TMR2_ReadTimer(void)
{
    return TMR2_Counter8BitGet();
}

void TMR2_Counter8BitSet(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;
}

void TMR2_WriteTimer(uint8_t timerVal)
{
    TMR2_Counter8BitSet(timerVal);
}

void TMR2_Period8BitSet(uint8_t periodVal)
{
   PR2 = periodVal;
}

void TMR2_LoadPeriodRegister(uint8_t periodVal)
{
   TMR2_Period8BitSet(periodVal);
}

void TMR2_ISR(void)
{

    // clear the TMR2 interrupt flag
    PIR1bits.TMR2IF = 0;

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    TMR2_CallBack();
}

void TMR2_CallBack(void)
{
    // Add your custom callback code here
    // this code executes every TMR2_INTERRUPT_TICKER_FACTOR periods of TMR2
    if(TMR2_InterruptHandler)
    {
        TMR2_InterruptHandler();
    }
}


void TMR2_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR2_InterruptHandler = InterruptHandler;
}

void TMR2_DefaultInterruptHandler(void){
    // add your TMR2 interrupt custom code
    // or set custom function using TMR2_SetInterruptHandler()
}


