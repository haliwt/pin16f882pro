#include "../inc/dht11.h"

DHT11_info* dht11_t;


void DHT11_Init(void)
{
    TRISAbits.TRISA5 = 1 ; //gpio as input port
    ANSELbits.ANS4 = 0 ;  //gpio as digital port

}



void DHT11_DispSmg_Value(void)
{

    dht11_t->Humidity_high  = DHT11ReadBuyte();
    dht11_t->Humidify_low   = DHT11ReadBuyte();

    dht11_t->Temperature_high = DHT11ReadBuyte();
    dht11_t ->Temperature_low   =  DHT11ReadBuyte();

    dht11_t->DHT11_CAC = DHT11ReadBuyte();

	//Smg display Digital -Temp
	if(cmd_t.gCmd_dispTemperatureTask ==0){
		 Temp_RB1_LED  =1;      	 
         Hum_RB2_LED  =0; 
	    SmgDisplay_Numbers(0x0A,dht11_t->Temperature_high,dht11_t ->Temperature_low);
	}
	else{
     //Smg display Digital - humidity 
      Temp_RB1_LED  =0;      	 
      Hum_RB2_LED  =1; 
     SmgDisplay_Numbers(0X0A, dht11_t->Humidity_high ,dht11_t->Humidify_low);

	}

}

uint8_t DHT11ReadBuyte(void)
{
    uint8_t j=0;
    uint8_t i,datCode;

    for(i=0;i<8;i++){

        datCode <<=1;
        j=0;

        while((!DHT11_DATA_BIT()) && (j<250)){

            j++;
            
        }
        __delay_us(10);
        __delay_us(10);
        __delay_us(10);
        __delay_us(10);
        if(DHT11_DATA_BIT()){

             datCode |= 0x01;
             j=0;
             while((DHT11_DATA_BIT()) &&(j<250)){

                 j++;
             }
        }
    }

    return datCode;



}

void Temperature_AddValue(void)
{
   static uint8_t i ;
   i++;
   cmd_t.tempTotal= 20 + i;
   if(cmd_t.tempTotal  >40){
      cmd_t.tempTotal=40;
      i=0;
   }
   

}
void Temperature_DecValue(void)
{
	cmd_t.tempTotal--;
	if(cmd_t.tempTotal< 20 ){
        cmd_t.tempTotal=20;

	}


}

void Time_AddValue(void)
{
    cmd_t.timeTotal ++ ;
	
	if(cmd_t.timeTotal > 24){ //hours 
		cmd_t.timeTotal =0;

	}

}
void Time_DecValue(void)
{
     cmd_t.timeTotal --;
	if(cmd_t.timeTotal < 0){

	   cmd_t.timeTotal= 24;

	}


}



