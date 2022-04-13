#ifndef __DHT11_H_
#define __DHT11_H_
#include "../../main.h"

#define _XTAL_FREQ  8000000

#define DHT11_RA5_GetValue()           PORTAbits.RA5
#define DHT11_DATA_BIT()               PORTAbits.RA5 

typedef unsigned char uint8_t ;


typedef struct{

    unsigned char Humidity_high;
    unsigned char Humidify_low;
    unsigned char Temperature_high;
    unsigned char Temperature_low;
    unsigned char DHT11_CAC;


}DHT11_info;

void DHT11_Init(void);


void DHT11_ReadInfo_Value(DHT11_info *temp);






#endif 
