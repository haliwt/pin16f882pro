#ifndef __RUN_H_
#define __RUN_H_
#include "../../main.h"

typedef struct _CMDRUN_{
    uint8_t gCmd_KeyOrder;
	uint8_t gCmd_dispTimerTask;
	uint8_t gCmd_breathLed;


}CMDRUN_T;

extern CMDRUN_T cmd_t;

enum runcmd{

    powerOff = 0x0,
	powerOn  = 0x01,
	adjustIncreas = 0x02,
	adjustDecreas = 0x03,
	dispTiimer  = 0x04,
	timerOn = 0X05,


};

void CheckRun_Mode(unsigned char keyvalue);
void RunCommand(void);






#endif 
