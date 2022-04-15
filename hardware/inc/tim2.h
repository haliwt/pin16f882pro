#ifndef __TIM2_H_
#define __TIM2_H_
#include "../../main.h"

void PWM2_Initialize(void);


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
