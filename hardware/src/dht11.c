#include "../inc/dht11.h"
#include <string.h>

DHT11_info dht11_t;


uint8_t DHT11ReadByte(void);



void DHT11_Init(void)
{
     DHT11_Reset();
 
}
//reset DHT11






void DHT11_DispSmg_TemperatureValue(void)
{
     static uint8_t temp0,temp1;

     temp0= dht11_t.Temperature /10;
     temp1 = dht11_t.Temperature % 10;

   Temp_RB1_LED  =1;      	 
         Hum_RB2_LED  =0; 
	    SmgDisplay_Numbers(0x0b,temp0,temp1);
	
   
}

void DHT11_DispSmg_HumidityValue(void)
{
     static uint8_t temp0,temp1;

    

     temp0= dht11_t.Humidity / 10;
     temp1 = dht11_t.Humidity % 10;

   

     //Smg display Digital - humidity 
      Temp_RB1_LED  =0;      	 
      Hum_RB2_LED  =1; 
     SmgDisplay_Numbers(0X0b, temp0 ,temp0);

	

}

//读取一个字节









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
/**
 * @brief 
 * 
 */



/**
 * @brief  
 * 
 */


void DHT11_Reset(void)
{
	TRISAbits.TRISA5 =0;
	DHT11_DQ_DATA =0 ;    //A
    __delay_ms(20);
	DHT11_DQ_DATA=1; //C
	__delay_us(30); //40 <data<100us
    TRISAbits.TRISA5 =1;
	
}

//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在  
uint8_t DHT11_IsOnLine(void)
{
     uint8_t retry =0;
	  
    while((DHT11_DQ_DATA==1) && retry < 40)//dq pull down low 40~80us
		{
			retry ++;
			__delay_us(1);
		}
	  
	  if(retry >=40){
		  return 1;
	   }
	 
		retry =0;
	  while((DHT11_DQ_DATA==0) && retry <100 )// dq pull up again  40~80us
	  {
		  retry ++;
		  __delay_us(1);
	  }
	  if(retry > 100){ // if(retry >=1000){
		  return 1;
	   }
	   retry = 0;

	   while((DHT11_DQ_DATA==1) && retry < 100)// wait high level 
	   {
		    retry ++;
		  __delay_us(1);
	   }
	  if(retry >=100){
		  return 1;
	   }
	   
	 return 0;
	   
    

}
/**
 * @brief 
 * 
 */



/************************************************************************
************************************************************************/
uint8_t DHT11_ReadBit(void) 			 
{
 	uint8_t retry = 0,bit;
	while((DHT11_DQ_DATA==1) && retry < 100) //等待变成低电平
	{
		retry ++;
		__delay_us(1);
	}
	retry = 0;

	while((DHT11_DQ_DATA==0) && retry < 100)// 等待变成高电平
	{
		retry ++;
		__delay_us(1);
	}
	
   __delay_us(40);

    bit = DHT11_DQ_DATA;

	if(bit){
		return 1;
	}
	else{
		return 0;
	}

    
}

//读一字节数据
uint8_t DHT11ReadByte(void)
{
	uint8_t i;
	uint8_t byt = 0;
	
	
	for(i=0; i<8; i++)
	{
		while(DHT11_DQ_DATA);
		while(!DHT11_DQ_DATA);
		__delay_us(40);
		byt <<= 1;
		if(DHT11_DQ_DATA)
		{
			byt |= 0x01;
		}
	}
	
	return byt;
}


uint8_t DHT11_ReadByte(void)    
{        
    uint8_t i,dat;
    dat = 0;
	for (i = 0; i < 8; i ++) 
	{
   		dat <<= 1; 
	    dat |= DHT11_ReadBit() ;
    }						    
    return dat;
}

//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi)    
{        
 	uint8_t buf[5];
	uint8_t i,vr;
	
	DHT11_Reset();
	
	if(DHT11_IsOnLine() == 0) 
	{
		for(i = 0; i < 5; i ++)//读取40位数据
		{
			buf[i] =DHT11_ReadBit() ;
		}
		if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
		{
			*humi = buf[0];
			*temp = buf[2];
			Breath_RA0_LED =1;
		}
	}
	else 
	{
		*humi = 0x30;
		*temp = 0x47;
		TIMEER_RA1_LED =1;
		Breath_RA0_LED =0;
		return 1;
	}
	
	return 0;	    
}

/**
 * @brief 
 * 
 */
uint8_t dht11_read_byte(uint8_t *byte)
{
    unsigned char i;
    unsigned char bit = 0;
    unsigned char data = 0;
    int timeout = 0;   
    
    for (i = 0; i < 8; i++)
    {
        timeout = 1000;  
        while (DHT11_DQ_DATA && timeout)   /* 等待变为低电平 */
        {
            __delay_us(1);
            --timeout;
        }
        if (!timeout) 
        {
           // printk("timeout %d\n", __LINE__);         
            return 0;           /* 超时 */
        }

        timeout = 1000;
        while (!DHT11_DQ_DATA && timeout)    /* 等待变为高电平 */
        {
            __delay_us(1);
            --timeout;
        }
        if (!timeout) 
        {
           // printk("timeout %d\n", __LINE__);
            return 0;           /* 超时 */
        }
        __delay_us(40);
        
        bit = DHT11_DQ_DATA;

        data <<= 1;            
        if (bit)
		{
			data |= 0x01;
		} 

		*byte = data;
		return 0;
	}
}






