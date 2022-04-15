   #include "../inc/run.h"
#include "../../main.h"

CMDRUN_T cmd_t;

void CheckRun_Mode(unsigned char keyvalue)
{
    static uint8_t currKeyPower = 0xff,currKeyInc =0xff,currKeyDec= 0xff,
	                    currKeyTimer= 0xff,currKeyLongTimer=0xff,ipowerOn=0;

	switch(keyvalue){
     

		case powerOff: //breathe led blnk
		
				if(cmd_t.gCmd_PowerOn == powerOff){
	                  cmd_t.gCmd_KeyOrder=0;
					  cmd_t.keyPoewr++;
					  cmd_t.setTimeStyle =0;

				}
				else{
					
					return ;

				}
	
	    break;
        case powerOn :
			   
			   ipowerOn ++ ;
			   if(ipowerOn ==1){
			   	
				   if(currKeyPower != cmd_t.keyPoewr){
				   	   currKeyPower = cmd_t.keyPoewr ;
                       cmd_t.gCmd_PowerOn =powerOn;
					  cmd_t.keyDec++ ;
					  cmd_t.keyLongTimer++;
					  cmd_t.keyTimer++;
					  cmd_t.keyInc++;

				       Beep_Fun();
					   PowerOn_LED_On(); //include plasma
					   TMR2_Start();  //turn on ultrasonic
	                   FAN_OnFun();

					   
				   	}
				   
				   cmd_t.gCmd_KeyOrder= 1;
			   	}
			    else{
					Beep_Fun();
					ipowerOn=0;
					cmd_t.gCmd_PowerOn =powerOff;
					TMR2_StopTimer(); //turn off ultrasonic 
				    cmd_t.gCmd_KeyOrder=0;
					PowerOn_LED_Off();
					FAN_OffFun();
				}
			 

		break;

		case adjustIncreas : //temperature regulation "+"
		     if(cmd_t.gCmd_PowerOn ==powerOn){
			  
			    if(currKeyInc != cmd_t.keyInc){
					  
					currKeyInc = cmd_t.keyInc;
					cmd_t.gCmd_KeyOrder=adjustIncreas ;
 					Beep_Fun();
					if(cmd_t.setTimeStyle ==0){
					  Temperature_AddValue();
					}
					else{

						Time_AddValue();
					}
					
				}


			 }
				

		break;

		case adjustDecreas: //temperature regulation "-"
			  if(cmd_t.gCmd_PowerOn ==powerOn){

                   if(currKeyDec != cmd_t.keyDec){

						currKeyDec = cmd_t.keyDec;
						cmd_t.gCmd_KeyOrder=adjustDecreas;
				        Beep_Fun();
						if(cmd_t.setTimeStyle ==0){
							
					   		
							Temperature_DecValue();
						}
						else{
						   
						    Time_DecValue();
							

						}
				   }

				}


		break;

		case dispTiimer : //short time be pressed display timer times
           if(cmd_t.gCmd_PowerOn ==powerOn){
			   if(currKeyTimer != cmd_t.keyTimer){
				   	  currKeyTimer = cmd_t.keyTimer ;
					  cmd_t.setTimeStyle =0;
					  cmd_t.gCmd_KeyOrder=dispTiimer;
						Beep_Fun();

			   }

		   }
		break;
		

		case timerOn: //long time be pressed
             if(cmd_t.gCmd_PowerOn ==powerOn){
			   if(currKeyLongTimer != cmd_t.keyTimer){
				   	  currKeyLongTimer = cmd_t.keyLongTimer ;
					  cmd_t.gCmd_KeyOrder=timerOn;
			          cmd_t.setTimeStyle =1; //set timer modle 
						Beep_Fun();

			   }

		   }
		break;

		default:
			cmd_t.gCmd_KeyOrder =0xFE;
		
		break;
	}


}

void RunCommand(void)
{
	switch(cmd_t.gCmd_KeyOrder){

		case 0:

			Breath_Led();

		break;

		case powerOn: //power On
		     DHT11_DispSmg_Value();
		
        break;

		case adjustIncreas : //"+"
		  
		    if(cmd_t.setTimeStyle ==0){
			   SmgDisplay_DynamicTemperatureNum();

		    }
			else{
				SmgDisplay_TimesNum();

			}
			cmd_t.keyDec++ ;
			cmd_t.keyLongTimer++;
			cmd_t.keyTimer++;
			cmd_t.keyInc++;
		

		break;

		case adjustDecreas: //"-"
			
		   if(cmd_t.setTimeStyle ==0){

				SmgDisplay_DynamicTemperatureNum();
		   }
		   else{
				SmgDisplay_TimesNum();

		   }
		
				cmd_t.keyLongTimer++;
				cmd_t.keyTimer++;
				cmd_t.keyInc++;
			    cmd_t.keyDec++ ;
			

		break;

		case dispTiimer : //
			cmd_t.keyDec++ ;
			 cmd_t.keyLongTimer++;
			  cmd_t.keyInc++;
			
			  


		break;
		case timerOn: //long time be pressed
		   
			cmd_t.keyDec++ ;
			cmd_t.keyTimer++;
			cmd_t.keyInc++;
		break;

		default:

		break;
	}

   
}






