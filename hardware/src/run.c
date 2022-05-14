#include "../inc/run.h"
#include "../../main.h"

CMDRUN_T cmd_t;

void CheckRun_Mode(unsigned char keyvalue)
{
    static uint8_t currKeyPower = 0xff,currKeyInc =0xff,currKeyDec= 0xff,
	            currKeyTimer= 0xff,currKeyLongTimer=0xff,ipowerOn=0;

	switch(keyvalue){
     

		
        case powerOn :
			   
			ipowerOn = ipowerOn ^ 0x01;
			if(ipowerOn ==1){
			   	   
				cmd_t.gCmd_PowerOn =powerOn;
				cmd_t.keyDec++ ;
				cmd_t.keyLongTimer++;
				cmd_t.keyTimer++;
				cmd_t.keyInc++;
				
				Beep_Fun();
				PowerOn_LED_On(); //include plasma
				// TMR2_Start();  //turn on ultrasonic
				FAN_OnFun();
					
				cmd_t.gCmd_KeyOrder=powerOn;
				
						
				
			}
			else{

               cmd_t.gCmd_KeyOrder=powerOff;
			   Beep_Fun();
			

			}
				   
			


		break;

		case adjustIncreas : //temperature regulation "+"
		     if(cmd_t.gCmd_PowerOn ==powerOn){
			  
			    if(currKeyInc != cmd_t.keyInc){
					  
					currKeyInc = cmd_t.keyInc;
					
 					Beep_Fun();
					if(cmd_t.setTimeStyle ==0){ //Temperature add value
					  cmd_t.gCmd_KeyOrder=dispTemperature ;
					  Temperature_AddValue();
					  PTC_ControlFun();
		
					}
					else if(cmd_t.timeNormal ==1){ // Timer to time add value 

						cmd_t.blankSmg=0;
					    cmd_t.blankNum =0;
						Time_AddValue();
					}
					
				}
					

			 }
				

		break;

		case adjustDecreas: //temperature regulation "-"
			  if(cmd_t.gCmd_PowerOn ==powerOn){

                   if(currKeyDec != cmd_t.keyDec){

						currKeyDec = cmd_t.keyDec;
						
				        Beep_Fun();
						if(cmd_t.setTimeStyle ==0){//Temperature add value
							
					   		cmd_t.gCmd_KeyOrder=dispTemperature ;
							Temperature_DecValue();
							PTC_ControlFun();
					
						}
						else if(cmd_t.timeNormal ==1){// Timer to time add value 
						     cmd_t.blankSmg=0;
							 cmd_t.blankNum =0;
							Time_DecValue();
							

						}
				   }
					
				}


		break;

		case dispTiimer : //short time be pressed display timer times
           if(cmd_t.gCmd_PowerOn ==powerOn){
			   if(currKeyTimer != cmd_t.keyTimer){
				   	  currKeyTimer = cmd_t.keyTimer ;
					  cmd_t.timeNormal = 0;
					  cmd_t.setTimeStyle = 0xff;
					  cmd_t.gCmd_KeyOrder=dispTiimer;
						Beep_Fun();

			   }
				
		   }
		break;
		

		case timerOn: //long time be pressed-0x82
             if(cmd_t.gCmd_PowerOn ==powerOn){
			   if(currKeyLongTimer != cmd_t.keyTimer){
				   	  currKeyLongTimer = cmd_t.keyLongTimer ;
					  cmd_t.timeNormal = 1;
					  cmd_t.gCmd_KeyOrder=timerOn;
			          cmd_t.setTimeStyle =1; //set timer modle 
					Beep_Fun();

			   }
				
		   }
		break;

		default:
	
		
		break;
	}


}

void RunCommand(void)
{
   
	switch(cmd_t.gCmd_KeyOrder){

		case powerOff: //breathe led blnk
		
			
	                  cmd_t.gCmd_KeyOrder=0;
					  cmd_t.setTimeStyle =0;

				Beep_Fun();
			
				TMR2_StopTimer(); //turn off ultrasonic 
				
				PowerOn_LED_Off();
				FAN_OffFun();

		
				
				
	
	    break;

		case powerOn: //power On
		     Breath_RA0_LED =1 ; //on
			 TIMEER_RA1_LED  =1 ; //on
			 Temp_RB1_LED  =1;      	 
             Hum_RB2_LED  =0; 
		   //  DHT11_DispSmg_Value();
		
        break;

		case dispTemperature :

			SmgDisplay_DynamicTemperatureNum();
			cmd_t.keyDec++ ;
			cmd_t.keyLongTimer++;
			cmd_t.keyTimer++;
			cmd_t.keyInc++;

		break;

		case dispTiimer : //display 2s switch display temperature

			
			SmgDisplay_DynamicTimeNum();
			cmd_t.keyDec++ ;
			cmd_t.keyLongTimer++;
			cmd_t.keyInc++;
			
			  
		break;
		case timerOn: //long time be pressed
		   
		    SmgDisplay_DynamicTimeNum();

		    //after 5s start timer  blank Smg .
            if(cmd_t.blankSmg > 4 && cmd_t.blankNum < 3){
			    if(cmd_t.gCmd_beepTimer ==0){
		           SmgDisplay_Numbers(0x0b,0x0b,0x0b);
			    }
				else{
				  SmgDisplay_DynamicTimeNum();

               }
			  cmd_t.blankNum ++;

	            cmd_t.gCmd_timeToTime = (cmd_t.timerTotime * 60);
				if(cmd_t.gCmd_timeToTime == 0){
					cmd_t.timeStop =1;
				}
				else{
					cmd_t.timeStop =0;
					cmd_t.timerTotime=0;
				}
            }
			cmd_t.keyDec++ ;
			cmd_t.keyTimer++;
			cmd_t.keyInc++;
		break;

		default:
			

		break;
	}

   
}







