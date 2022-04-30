#ifndef __KEY_H_
#define __KEY_H_

#include "../../main.h"

#define KEY_POWER_RC3_SetDigitalInput()    		do { TRISCbits.TRISC3 = 1; } while(0)

#define KEY_TIMER_RC0_SetDigitalInput()         do { TRISCbits.TRISC0 = 1; } while(0)  //gpio as input 
#define KEY_INC_RB6_SetDigitalInput()           do { TRISBbits.TRISB6 = 1; } while(0)  //gpio as input 
#define KEY_DEC_RB5_SetDigitalInput()           do { TRISBbits.TRISB5 = 1; } while(0)  //gpio as input



#define KEY_POWER_RC2_GetValue()           PORTCbits.RC3
#define KEY_TIMER_RC0_GetValue()		   PORTCbits.RC0
#define KEY_INC_RB6_GetValue()             PORTBbits.RB6//PORTAbits.RA6  -PIC16F73 don't has RA6, RA7
#define KEY_DEC_RB5_GetValue()			   PORTBbits.RB5//PORTAbits.RA7


#define		_KEY_ALL_OFF				    0X1F

//normal times be pressed key
#define		_KEY_TRG_1_POWER     			0x01  //POER
#define		_KEY_TRG_2_TIMER     			0x02  //TIMER
#define		_KEY_TRG_3_ADD    			    0x04   //+
#define		_KEY_TRG_4_DEC     			    0x08   //-
// combination of buttons 
#define		_KEY_TRG_5_WINDTI   			0x11   //?????
#define		_KEY_TRG_6_WINDTI   			0x12   //?????
#define		_KEY_TRG_7_WINDTI   			0x14   //?????
#define		_KEY_TRG_8_WINDTI   			0x18   //?????

//long times be pressed
#define		_KEY_CONT_1_POWER     	     0x81    //??????--???
#define		_KEY_CONT_2_TIMER    		 0x82    //??????--???
#define		_KEY_CONT_3_ADD     	     0x84    //?????? ?????
#define		_KEY_CONT_4_DEC    	         0x88    //??? --?????
#define		_KEY_CONT_5_WINDTI     		 0x89




#define		_KEY_CONT_1     	    0x81    //?????
#define		_KEY_CONT_2     		0x82
#define		_KEY_CONT_3     		0x84
#define		_KEY_CONT_4     	    0x88

#define		_KEY_COM_1    		    0x91
#define		_KEY_COM_2    		    0x92
#define		_KEY_COM_3    		    0x94
#define		_KEY_COM_4    		    0x98

typedef  struct  _state_
{
 unsigned char          read;
 unsigned char         buffer;
 unsigned char        value;
 unsigned char        off_time;
 unsigned long        on_time;

 enum{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;
}key_types;

key_types key;




void KEY_Init(void);
unsigned char  KEY_Scan(void);














#endif 
