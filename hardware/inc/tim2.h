#ifndef __TIM2_H_
#define __TIM2_H_
#include "../../main.h"

void PWM2_Initialize(void);



void TMR2_LoadPeriodRegister(uint8_t periodVal);

/**
  @Summary
    Timer Interrupt Service Routine

  @Description
    Timer Interrupt Service Routine is called by the Interrupt Manager.

  @Preconditions
    Initialize  the TMR2 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
void TMR2_ISR(void);

/**
  @Summary
    CallBack function

  @Description
    This function is called from the timer ISR. User can write your code in this function.

  @Preconditions
    Initialize  the TMR2 module with interrupt before calling this function.

  @Param
    None

  @Returns
    None
*/
 void TMR2_CallBack(void);
/**
  @Summary
    Set Timer Interrupt Handler

  @Description
    This sets the function to be called during the ISR

  @Preconditions
    Initialize  the TMR2 module with interrupt before calling this.

  @Param
    Address of function to be set

  @Returns
    None
*/
 void TMR2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Timer Interrupt Handler

  @Description
    This is a function pointer to the function that will be called during the ISR

  @Preconditions
    Initialize  the TMR2 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
extern void (*TMR2_InterruptHandler)(void);

/**
  @Summary
    Default Timer Interrupt Handler

  @Description
    This is the default Interrupt Handler function

  @Preconditions
    Initialize  the TMR2 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
void TMR2_DefaultInterruptHandler(void);



void PWM2_LoadDutyValue(uint16_t dutyValue);

/**
  @Summary
    Read pwm output status.

  @Description
    This routine returns the pwm output status.

  @Preconditions
    PWM2_Initialize() function should have been
    called before calling this function.

  @Param
    None

  @Returns
    true : output high
    false: output low

  @Example
    <code>
    uint16_t dutyCycle;
    bool status;
    PWM2_Initialize();
    PWM2_LoadDutyValue(dutyCycle);
    while(1)
    {
            status = PWM2_OutputStatusGet();
    }
    </code>
*/


void TMR2_Start(void);

void TMR2_StopTimer(void);







#endif 
