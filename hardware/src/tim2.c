#include "../inc/tim2.h"

/*****************************************************************************************
*
*Function Name:void TMR2_Initialize(void)
*Function : Frequency is 25KHz , Tperiod = 0.04ms,freq =8MHz ,prescale = 
*           need timers is  0.04ms = 40us ,prescale = 4 
*TMR2 = 256 - (40us)/(4 * 1/freq * prescale) = 256 -40/(4 * 0.125 *4)=256-20=236= 0xEC
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

    // T2RSEL T2CKIPPS pin; 

    // PR2 19; 
     PR2 = 0x13;

    
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

