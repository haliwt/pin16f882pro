#include "../inc/key.h"


void KEY_Init(void)
{
	 KEY_POWER_RC3_SetDigitalInput() ;   		
	 KEY_TIMER_RC0_SetDigitalInput() ;   
	 KEY_INC_RB6_SetDigitalInput()  ;    
	 KEY_DEC_RB5_SetDigitalInput()  ;     
}

uint8_t KEY_Scan(void)
{
    uint8_t  reval = 0;

	key.read = _KEY_ALL_OFF; //0x1F 
   if(KEY_POWER_RC2_GetValue()   ==0)
	{
		
        key.read &= ~0x01; // 0x1f & 0xfe =  0x1E = 0b 1110
	}
	else if( KEY_TIMER_RC0_GetValue()   ==0){ //long times be pressed 0x82

        key.read &= ~0x02; // 0x1f & 0xfd =  0x1d -0b 1101

	}
	else if( KEY_INC_RB6_GetValue()   ==0){

        key.read &= ~0x04; // 0x1f & 0xfB =  0x1b -0b 1011

	}
	else if( KEY_DEC_RB5_GetValue()   ==0){

        key.read &= ~0x08; // 0x1f & 0xf7 =  0x17 -0b 0111

	}
    
	
	
	switch(key.state )
	{
		case start:
		{
			if(key.read != _KEY_ALL_OFF)
			{
				key.buffer   = key.read; //??:key.buffer = 0x1E  POWER KEY 
				key.state    = first;
				key.on_time  = 0;
				key.off_time = 0;
            
            }
			break;
		}
		case first:
		{
			if(key.read == key.buffer) // adjust key be down 
			{
				if(++key.on_time> 1000) //??  0.5us
				{
					key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01, com = 0x0E ^ 0x1f = 0x11
					key.on_time = 0;
                   
					key.state   = second;
                   
                }
			}
			else
			{
				key.state   = start;
			}
			break;
		}
		case second:
		{
			if(key.read == key.buffer) //again adjust key if be pressed down 
			{
				if(++key.on_time>10000)//long key be down
				{
					
					key.value = key.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key.on_time = 0;
					key.state   = finish;
               
                   
				}
			}
			else if(key.read == _KEY_ALL_OFF)  // loose hand 
				{
					if(++key.off_time>30) //don't holding key dithering
					{
						key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
						
						key.state   = finish; // loose hand
					}
				}
		   
			break;
		}
		case finish:
		{
			
			reval = key.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81
			key.state   = end;
         
			break;
		}
		case end:
		{
			if(key.read == _KEY_ALL_OFF)
			{
				if(++key.off_time>100)
				{
					key.state   = start;
                  
				}
			}
			break;
		}
		default:
		{
			key.state   = start;
         
			break;
		}
	}
	return  reval;


}




