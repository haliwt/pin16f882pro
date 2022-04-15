   #include "../inc/run.h"
#include "../../main.h"

CMDRUN_T cmd_t;

void CheckRun_Mode(unsigned char keyvalue)
{
    static uint8_t currKeyPower = 0xff,currKeyInc =0xff,currKeyDec= 0xff,currKeyTimer= 0xff,ipowerOn=0;

	switch(keyvalue){
     

		case powerOff: //breathe led blnk
		
				if(cmd_t.gCmd_PowerOn == powerOff){
	                  cmd_t.gCmd_KeyOrder=0;

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
                       cmd_t.gCmd_PowerOn =ipowerOn;
				   
					   PowerOn_LED_Fun();
	                   Beep_Fun();
					   
				   	}
				   
				   cmd_t.gCmd_KeyOrder= 1;
			   	}
			    else{
					ipowerOn=0;
					cmd_t.keyPoewr++;
					cmd_t.gCmd_PowerOn =powerOff;

				    cmd_t.gCmd_KeyOrder=0;


				}
			 

		break;

		case adjustDecreas:
			  if(cmd_t.gCmd_PowerOn ==powerOn){

                   if(currKeyDec != cmd_t.keyDec){

						currKeyDec = cmd_t.keyDec;
						cmd_t.gCmd_KeyOrder=adjustDecreas;
				   		 Beep_Fun();
				   }


			  }


		break;

		case adjustIncreas :
				

		break;

		case dispTiimer :



		break;
		

		case timerOn: //long time be pressed

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
             DHT11_ReadInfo_Value();


		break;

		case adjustDecreas:
			cmd_t.keyDec++ ;

		break;

		case adjustIncreas :


		break;

		case dispTiimer :



		break;


		case timerOn: //long time be pressed

		break;

		default:

		break;







	 }

   
}






