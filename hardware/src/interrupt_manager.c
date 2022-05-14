#include "../inc/interrupt_manager.h"


void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
   if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
     {
            TMR1_ISR();
     } 
   //  else if(PIE1bits.TMR2IE == 1 && PIR1bits.TMR2IF == 1)
   //  {
   //         TMR2_ISR();
   //  }
    else{
    
    
    }
       

}