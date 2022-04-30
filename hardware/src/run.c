#include "../inc/run.h"
#include "../../main.h"

//CMDRUN_T cmd_t;

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
					  cmd_t.keyOn++;
					  cmd_t.keyShutOff++;

				    

					 }
				  
				   cmd_t.gCmd_KeyOrder= 1;
			   	}
			    else{
					ipowerOn=0;
					cmd_t.gCmd_PowerOn =powerOff;
					cmd_t.gCmd_KeyOrder++;
					
				}
			 

		break;

		case adjustIncrease : //temperature regulation "+"
		     if(cmd_t.gCmd_PowerOn ==powerOn){
			  
			    if(currKeyInc != cmd_t.keyInc){
					  
					currKeyInc = cmd_t.keyInc;
					
 					Beep_Fun();
					if(cmd_t.setTimeStyle ==0){ //Temperature add value
					  cmd_t.gCmd_KeyOrder=dispTemperature ;
					  Temperature_AddValue();
		
		
					}
					else if(cmd_t.timeNormal ==1){ // Timer to time add value 


					    cmd_t.blankNum =0;
						Time_AddValue();
					}
					
				}
}
				

		break;

		case adjustDecrease: //temperature regulation "-"
			  if(cmd_t.gCmd_PowerOn ==powerOn){

                   if(currKeyDec != cmd_t.keyDec){

						currKeyDec = cmd_t.keyDec;
						
				        Beep_Fun();
						if(cmd_t.setTimeStyle ==0){//Temperature add value
							
					   		cmd_t.gCmd_KeyOrder=dispTemperature ; //switch to Diplay Temperature 
							Temperature_DecValue();
							
					
						}
						else if(cmd_t.timeNormal ==1){// Timer to time add value 
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
		

		case timerOn: //long time be pressed input setup timer timing
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
			cmd_t.gCmd_KeyOrder =0xFE;
		
		break;
	}


}

void RunCommand(void)
{
   
	uint8_t currkeyOff= 0xff,currkeyOn=0xff;
	switch(cmd_t.gCmd_KeyOrder){

		case 0:
            if(currkeyOff !=cmd_t.keyShutOff){
				currkeyOff = cmd_t.keyShutOff;
				Beep_Fun();
				PowerOn_LED_Off();
				TMR2_StopTimer(); //turn off ultrasonic 
				FAN_OffFun();
			}
			Breath_Led();

		break;

		case powerOn: //power On
		if( cmd_t.gCmd_dispTemperatureTask==1){
			   dht11_t.Humidity_high  = DHT11ReadBuyte();
	           dht11_t.Humidify_low   = DHT11ReadBuyte();

	         dht11_t.Temperature_high = DHT11ReadBuyte();
	         dht11_t.Temperature_low   =  DHT11ReadBuyte();
			 PTC_SetTemperature_Fun();
		  }
		   if(currkeyOn != cmd_t.keyOn){
				 currkeyOn = cmd_t.keyOn;
				   PTC_PowerOn_SetFun();

				    Beep_Fun();
					PowerOn_LED_On(); //include plasma
					TMR2_Start();  //turn on ultrasonic
	                Fan_RC5_Out=1;//FAN_OnFun();
			 }
		     DHT11_DispSmg_Value(); // alternate temperature and humidity 
		     cmd_t.timer = 0;
			 cmd_t.blankNum=0;
			
        break;

		case dispTemperature :
           SetTemperature_Numbers();
			cmd_t.keyDec++ ;
			cmd_t.keyLongTimer++;
			cmd_t.keyTimer++;
			cmd_t.keyInc++;
			if(cmd_t.timer == 10){
				cmd_t.gCmd_KeyOrder= powerOn;
				cmd_t.timer = 0;
			}

		break;

		case dispTiimer : //display 2s switch display temperature

		    SetTimer_Timing();
			cmd_t.keyDec++ ;
			cmd_t.keyLongTimer++;
			cmd_t.keyInc++;
			if(cmd_t.timer == 10){
				cmd_t.gCmd_KeyOrder= powerOn;
				cmd_t.timer = 0;
			}
			  
		break;
		case timerOn: //long time be pressed by save data start timer 
		   
		    SetTimer_Timing();

		    //after 5s start timer  blank Smg .
           if(cmd_t.blankNum < 3){
			    if(cmd_t.gCmd_dispTemperatureTask ==0){
                  SmgDisplay_Numbers(0x0B,0x0B,0x0B);
				   
			    }
				else{
				  
				  SetTimer_Timing();
				  cmd_t.blankNum ++;
              }
			 cmd_t.gCmd_timeToTime = 60 * cmd_t.timeTotal; //24hours
			 if(cmd_t.gCmd_timeToTime != 0){
					cmd_t.timeStart =1;
					
			}
			else{
					cmd_t.timeStart =0;
					
			    }
           }
		   if(cmd_t.blankNum >=3)cmd_t.gCmd_KeyOrder= powerOn;
			cmd_t.keyDec++ ;
			cmd_t.keyTimer++;
			cmd_t.keyInc++;
		break;

		default:
			

		break;
	}
}

   








