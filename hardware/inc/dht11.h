#ifndef __DHT11_H_
#define __DHT11_H_
#include "../../main.h"


#define DHT11_DQ_IN          PORTAbits.RA5
#define DHT11_DQ_DATA                  PORTAbits.RA5 

uint8_t  dat[5]={0x00,0x00,0x00,0x00,0x00};    //存储读取的温湿度信息

typedef unsigned char uint8_t ;
typedef unsigned int  uint16_t ;

typedef struct _DHT11_{

    unsigned char Humidity;
    unsigned char Temperature;
   
    unsigned char DHT11_CAC;


}DHT11_info;

extern DHT11_info dht11_t;

void DHT11_Init(void);

 void DHT11_Reset(void);





void DHT11_DispSmg_Value(void);

void Temperature_AddValue(void);
void Temperature_DecValue(void);

void Time_AddValue(void);
void Time_DecValue(void);

void DHT11_DispSmg_HumidityValue(void);
void DHT11_DispSmg_TemperatureValue(void);

uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi)  ;


uint8_t dht11_read_byte(uint8_t *byte);

uint8_t DHT11_IsOnLine(void);

uint8_t DHT11_One_ReadByte(void);

#endif 
