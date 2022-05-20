#include "../inc/dht11.h"
#include <string.h>

DHT11_info dht11_t;

uint8_t  dht_dat[5];    //存储读取的温湿度信息


 void  Delay_10us(void);

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
    DHT11_DQ_DATA =1 ; 
	DHT11_DQ_DATA =0 ;    //A
    __delay_ms(20);
	DHT11_DQ_DATA=1; //C
	//__delay_us(50); //40 <data<100us
   // DHT11_DQ_DATA=1;//
	
}

//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在  
uint8_t DHT11_IsOnLine(void)
{
     uint8_t retry =0;

	TRISAbits.TRISA5 =1;
    while((DHT11_DQ_DATA==1) && retry < 100)//dq pull down low 40~80us
		{
			retry ++;
			__delay_us(1);
		}
	  
	  if(retry >=100){
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
uint8_t DHT11_ReadBit(uint8_t *pdat) 			 
{
 	uint8_t timeout,count,i,dat; 
	for(i=0;i<8;i++){
		timeout= 55;
		while((DHT11_DQ_DATA==0) && timeout) //等待变成高电平
		{
			timeout ++;
			__delay_us(1);
		}
		if (!timeout) 
			{
				//printk("timeout %d\n", __LINE__);         
				return 0;           /* 超时 */
			}

		timeout= 90;

		while((DHT11_DQ_DATA==1) && timeout)// 等待变成高电平
		{
		
			__delay_us(1);
			timeout--;
			count++;
		}
		if (!timeout) 
			{
			// printk("timeout %d\n", __LINE__);
			return 0;           /* 超时 */
			}
		
		dat = dat << 1; 
		if(count>30){
			
			dat |= 0x01;
		
			
		}
	
		count= 0;
		
	
	}
    *pdat = dat;
    return dat;
}



uint8_t DHT11_ReadByte(uint8_t *pdt)    
{        
    uint8_t i,dat;
    dat = 0;
	for (i = 0; i < 8; i ++) 
	{
   		dat = dat << 1; 
	    dat |= DHT11_ReadBit(pdt) ;
    }
	*pdt = dat;			    
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
			//DHT11_One_ReadByte(&buf[i]);
			// DHT11_ReadByte(&buf[0]);
            // DHT11_ReadByte(&buf[1]);
            // DHT11_ReadByte(&buf[2]);
            // DHT11_ReadByte(&buf[3]);
            // DHT11_ReadByte(&buf[4]);
			// dht11_read_byte(&buf[0]);
			// dht11_read_byte(&buf[1]);
			// dht11_read_byte(&buf[2]);
			// dht11_read_byte(&buf[3]);
			// dht11_read_byte(&buf[4]);
			DHT11_ReadBit(&buf[i]); 	
		
		}
		if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
		{
			*humi = buf[0];
			*temp = buf[2];
			dht_dat[0] = buf[0];
			dht_dat[1] = buf[1];
			dht_dat[2] = buf[2];
			dht_dat[3] = buf[3];
			Breath_RA0_LED =1;
           // return 1;
		}
	}
	else 
	{
		*humi = 0xff;
		*temp = 0xff;
		TIMEER_RA1_LED =1;
		Breath_RA0_LED =0;
		return 0;
	}
	
	return 0;	    
}

/**
 * @brief 
 * 
 *
 * 
 */
uint8_t dht11_read_byte(uint8_t *byte)
{
    unsigned char i;
    unsigned char bit = 0;
    unsigned char data = 0;
    int timeout = 0;   
    TRISAbits.TRISA5 =1;
    for (i = 0; i < 8; i++)
    {
        timeout = 55;  
        while (DHT11_DQ_DATA==1 && timeout) ;  /* 等待变为低电平 */
        {
           NOP(); //__delay_us(1);
            --timeout;
        }
        if (!timeout) 
        {
            //printk("timeout %d\n", __LINE__);         
            return 0;           /* 超时 */
        }

        timeout = 90;
        while ((DHT11_DQ_DATA==0) && timeout)    /* 等待变为高电平 */
        {
             __delay_us(1);
            --timeout;
        }
        if (!timeout) 
        {
           // printk("timeout %d\n", __LINE__);
           return 0;           /* 超时 */
        }
       // __delay_us(40); //level high  of time
	    Delay_10us();
		 Delay_10us();
		  Delay_10us();
        
      //  bit = DHT11_DQ_DATA;

        //dht11_t.data<<=1;
		data <<= 1;            
        if (DHT11_DQ_DATA==1)
		{
			//dht11_t.data |= 0x01; 
			data |= 0x01;
		} 
     //  *byte = data;
	}
	  *byte = data;
        return 0;	
		
	
}


/**
	* @brief DHT11 读取字节
	*/
uint8_t DHT11_One_ReadByte(uint8_t *pda)
{
	uint8_t j,retry=0,data;
	retry=0;
	for(j=0;j<8;j++)
	{
		
		while(DHT11_DQ_DATA==1);
		
		while((DHT11_DQ_DATA==0) && retry <100)//等待拉高
		{
			__delay_us(1);
			retry++;
		}
		__delay_us(40);
		
	
		if(DHT11_DQ_DATA==0)
		{
			data &= ~(1<<(7-j));
		}
        else{
			data |= 1<<(7-j);
		
			
		}
	}
	*pda = data;
	return 1;
}




 void  Delay_10us(void)
{
    NOP();
     NOP();
	 NOP();
	  NOP();
     NOP();
	 NOP();
	  NOP();
     NOP();
	 NOP();
    NOP();   
}



uint8_t DHT11_Read_One_Byte(uint8_t *pdata)
{
  uint8_t data = 0;
  uint8_t i;
  uint16_t timeout=0,count=0;       
   TRISAbits.TRISA5 =1;
        for(i=0;i<8;i++)
        {
                timeout = 55;  
                while((DHT11_DQ_RA5() ==0) && timeout )    // 输出位头，低电平
                {
                        NOP();//
						//__delay_us(1);       
                        --timeout;
                }
				 if (!timeout) 
				{
				// printk("timeout %d\n", __LINE__);
				return 0;           /* 超时 */
				}
                timeout=1000;
                while((DHT11_DQ_RA5() ==1) && timeout ) //等待低电平
                {
                       // NOP();
						__delay_us(1);
                        --timeout;
                        count++;
                }
				if (!timeout) 
				{
				// printk("timeout %d\n", __LINE__);
				        return 0;           /* 超时 */
				}
                data <<= 1;                    // 先移位
                if(count > 500)                // 大于30uS的为 1
                {
                    data = data| 0x01;
                }
				else{
                    data = data| 0x00;

				}
                count = 0;
        }
        //printf("DHT11 Reader Value = 0x%02X\r\n",data);
		*pdata = data;
        return 1;
}

void DHT11_Start2(void)
{
	TRISAbits.TRISA5 =0;
    DHT11_DQ_DATA =1 ; 
	DHT11_DQ_DATA =0 ;    //A
    __delay_ms(20);
	DHT11_DQ_DATA=1; //C

    TRISAbits.TRISA5 =1;
	if(DHT11_DQ_DATA==0){ //has a signale 
	   while(!DHT11_DQ_DATA); //跳过ME
	   while(DHT11_DQ_DATA);
	   //led1=0;  //has a signale is OK
	   Breath_RA0_LED =1;
	}
	else{

	    //led1=1; //don't a signale is NG
		 Breath_RA0_LED =0;
	}
}


uint8_t  DHT11_Read_Byte(void)
{
	uint8_t i,flag,byteRead =0;

	for(i=0;i<8;i++){

	  while(!DHT11_DQ_DATA);  //跳过50us
	  __delay_us(33);

	  if(DHT11_DQ_DATA ==1){ //read as "1" 70us ->high

	       flag =1; //
	       while(DHT11_DQ_DATA);
	  }
	  else{ //read "0" 26~28us -> low 

	  	   flag =0;
	  }
	  byteRead <<=1;

	  byteRead |= flag;

	}
	return byteRead;
}
