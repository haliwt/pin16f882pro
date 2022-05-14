#ifndef __RUN_H_
#define __RUN_H_
#include "../../main.h"

typedef struct _CMDRUN_{
    uint8_t gCmd_PowerOn;
    uint8_t gCmd_KeyOrder;
	uint8_t gCmd_dispTemperatureTask;
	uint8_t gCmd_beepTimer;
	uint8_t gCmd_setTemp;

	//breath LED
	uint8_t gCmd_breathLed;
   
   //key
	uint8_t keyInc;
	uint8_t keyDec;
	uint8_t keyTimer;
	uint8_t keyLongTimer;

	//temperature 
	uint8_t tempTotal;

	//PTC 
	uint8_t ptcTotal;


	//timer to time
	uint8_t setTimeStyle;
	uint8_t timerTotime;
	uint8_t timeStop;
	uint8_t timeNormal;
    int8_t  timeTotal;

	//smg
	 uint8_t blankSmg ;
	 uint8_t blankNum;


	uint16_t gCmd_timeToTime;

}CMDRUN_T;

extern CMDRUN_T cmd_t;

enum runcmd{

    powerOff = 0x0,
	powerOn  = 0x01,
	dispTiimer  = 0x02,
	adjustIncreas = 0x04,
	adjustDecreas = 0x08,
	dispTemperature = 0x5,
	timerOn = 0X82


};

void CheckRun_Mode(unsigned char keyvalue);
void RunCommand(void);

void Check_TimeTotime_Fun(void);




#endif 
