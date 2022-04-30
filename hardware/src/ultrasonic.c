#include "../inc/ultrasonic.h"

/*******************************************************************************************
*
*Function Name:void EPWM_Initialize(void)
*Function: 
*          PWM Period = [(PR2)+1]*4*Tosc*(TMR2 Prescale Value)=
*          Duty cycle ratio = [CCPRxL:CCPxCON<5:4>]/(4*(PR2+1))
*          PR2 =19,Tperiod =0.04ms
*          100% Duty = 80/(4*(19+1) =1 -> CCRxL:CCPxCON<5:4> = 80
*          50%  Duty = 80 *50%  =40      -> CCRxL:CCPxCON<5:4> = 40 = 0x28
*		   25%  Duty = 80 *25% = 20
*
*
*******************************************************************************************/

void EPWM_Initialize(void)
{
    // Set the EPWM to the options selected in the User Interface
	
	// CCP1M P1A: single output ; //P1B: active high; DC1B 3; P1M single; 
	CCP1CON = 0b00000001;//0x3C;    
	
	// CCP1ASE operating; PSS1BD low; PSS1AC low; CCP1AS disabled; 
	//ECCP1AS = 0x00;    
	
	// P1RSEN automatic_restart; P1DC 0; 
	//PWM1CON = 0x80;    
	
	// STR1B P1B_to_port; STR1A P1A_to_port; STR1SYNC start_at_begin; 
	//PSTR1CON = 0x00;    
	
	// CCPR1H 0; 
	CCPR1H = 0x00;    
	
	// CCPR1L 10; PWM duty Cycle 
	CCPR1L = 0x0A;    

}

void EPWM_LoadDutyValue(uint16_t dutyValue)
{
   // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR1L = ((dutyValue & 0x03FC)>>2);
    
   // Writing to 2 LSBs of pwm duty cycle in CCPCON register <5:4>
    CCP1CON = ((uint8_t)(CCP1CON & 0xCF) | ((dutyValue & 0x0003)<<4));
}
