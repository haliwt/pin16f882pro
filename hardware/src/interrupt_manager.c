#include "../inc/interrupt_manager.h"


void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
   if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
     {
            TMR1_ISR();
     } 
	else if(INTCONbits.PEIE == 1)
    {
        if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
	    {
	        TMR0_ISR();
	    }
        else
        {
            //Unhandled Interrupt
        }
    }      
    else
    {
        //Unhandled Interrupt
    }
}