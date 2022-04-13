#ifndef __DHT11_H_
#define __DHT11_H_
#include "../../main.h"

#define _XTAL_FREQ  8000000

#define DHT11_RA5_GetValue()           PORTAbits.RA5
#define DHT11_DATA_BIT()               PORTAbits.RA5 

typedef unsigned char uint8_t ;
typedef unsigned int  uint16_t ;

typedef struct _DHT11_{

    unsigned char Humidity_high;
    unsigned char Humidify_low;
    unsigned char Temperature_high;
    unsigned char Temperature_low;
    unsigned char DHT11_CAC;


}DHT11_info;

extern DHT11_info* dht11_t;

void DHT11_Init(void);


void DHT11_ReadInfo_Value(void);


#endif 
