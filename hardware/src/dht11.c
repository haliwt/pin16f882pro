#include "../inc/dht11.h"

static uint8_t DHT11ReadBuyte(void);

void DHT11_Init(void)
{





}



void DHT11_ReadInfo_Value(DHT11_info *temp)
{

    temp->Humidity_high  = DHT11ReadBuyte();
    temp->Humidify_low   = DHT11ReadBuyte();

    temp->Temperature_high = DHT11ReadBuyte();
    temp ->Temperature_low   =  DHT11ReadBuyte();

    temp->DHT11_CAC = DHT11ReadBuyte();



}

static uint8_t DHT11ReadBuyte(void)
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