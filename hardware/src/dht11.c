#include "../inc/dht11.h"
#include <string.h>

#define NUMBER 50
 
DHT11_info dht11_t;
void delay(uint16_t i);

uint8_t  dht_dat[5];    //存储读取的温湿度信息

uint8_t status = 1;
 void  Delay_10us(void);

void DHT11_Init(void)
{
     DHT11_Reset();
 
}
//reset DHT11


void delay(uint16_t i)
{

	while(i--){

		__nop();
	}
}



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
 	uint8_t count,i,dat; 
	uint16_t timeout;
	dat=0;
	
	for(i=10;i>0;i--){

        TRISAbits.TRISA5 =1;
        while(DHT11_DQ_DATA==1);
		TRISAbits.TRISA5 =1;
		dat <<=1;
		timeout = 0;
		while((DHT11_DQ_DATA==0)&& (timeout< 55)) //等待变成高电平
	    {
            delay(1);
            timeout++;
            if(timeout < 55 && timeout > 45){

                goto RTC;
            }

        }
		if (timeout > 55) 
		{
			//printk("timeout %d\n", __LINE__); 
		    status = 0;  
			TIMEER_RA1_LED  =1;    
            dat=0;
			return 0;           /* 超时 */

		}
        
RTC:    TRISAbits.TRISA5 =1;
        timeout =10 ;
         while(DHT11_DQ_DATA==0 && timeout){
              delay(1);
              timeout -- ;
        }
        if(!timeout){
            TIMEER_RA1_LED  =1;  
         
            dat =0;
            return 0;
        }
        delay(40);
		timeout = 0;
		if(DHT11_DQ_DATA == 1){

            dat++;
			while((DHT11_DQ_DATA == 1) && (timeout++ < 100));
			if(timeout >70){
				status = 0;
				return 0;
			}

		}
		
	
		
	
	}
    *pdat = dat & 0xff;

	TIMEER_RA1_LED  =0;
	Hum_RB2_LED  =0;  
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
        if(status ==0){
                *humi = 0;
                *temp = 0; 
                return 0;
        }
        else if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
		{
		    
            buf[0]=buf[0]>>2;
            *humi = buf[0];
             buf[2]=buf[2]>>2;
			*temp = buf[2];
			dht_dat[0] = buf[0];
			dht_dat[1] = buf[1];
			dht_dat[2] = buf[2];
			dht_dat[3] = buf[3];
			Breath_RA0_LED =1;
           
          
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



unsigned char DHT11_Read_Char(void)
 {
      unsigned char count,value = 0,i;
      //GPIO0DIR_in();
      TRISAbits.TRISA5 =1;
      for(i=8;i>0;i--)
      {
          value<<=1;  //高位在先
          count = 0;
          //每一位数据之前都会有50us的低电平时间，等待50us低电平结束
          while((! DHT11_DQ_DATA)&&(count++<NUMBER));
          if(count>=NUMBER)
          {
              status = 0;
              return 0;
          }
          /********26-28us的高电平为0,70us的高电平为1********/
          //while(DATA_PIN); //这里一直都是高电平，则跟下面的延时无关
              
          delay(45);     //延时30us
                      //30--28.7us
                       //35--33.2us
                       //40--37.7us
                       //45--42.2us
  
          //判断数据线是否还是为高
		  count =0 ;
          if( DHT11_DQ_DATA)
          {
              value++;
              //等待剩余的高电平（约40us）结束
              while(( DHT11_DQ_DATA)&&(count++<(NUMBER+50)));
              if(count>=(NUMBER+20))
              {
                  status = 0;
                  return 0;
              }
             //while(DATA_PIN);
          }
      }
      return(value);

 }


unsigned int DHT11_Read_Humidity(void)
{ 
      unsigned char i = 0,check_value = 0;
      unsigned int  count = 0;
      unsigned int  temp_value,humi_value_L,humi_value_H,humi_value;
      unsigned char value_array[5];
     // GPIO0DIR_out();
	  TRISAbits.TRISA5= 0;
	  DHT11_DQ_DATA=0;
      //DATA0();
      delay(22000);     //主机拉低(必须大于)18ms ，以保证DHT11能检测到起始信号
                       //20000--18ms
                       //25000--22ms
                       //30000--27ms
      //DATA1();
	  DHT11_DQ_DATA=1;
      //总线由上拉电阻拉高 主机延时(20us-40us)
                                 //25--23us
                                 //30--27us
                                 //35--33us
                                 //40--37us
      //GPIO0DIR_in();
	  TRISAbits.TRISA5= 1;
      delay(65);          
      //主机设为输入 判断从机响应信号 
      
      //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行      
      if(!DHT11_DQ_DATA)    //       
      {
          //判断从机是否发出 80us 的低电平响应信号是否结束     
          while((!DHT11_DQ_DATA)&&(count++<(NUMBER+20)));
          if(count>=(NUMBER+20))
          {
              return 0;
          }
         //while(DATA_BACK_0());
         count = 0;
         //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
         while((DHT11_DQ_DATA)&&(count++<(NUMBER+20)));
         if(count>=(NUMBER+20))
         {
             return 0;
         }
         //while(DATA_PIN);
         // while(!DATA_BACK_0());
         /***********读取温度的值*************/
         for(i=0;i<5;i++)
         {
             value_array[i] = DHT11_Read_Char(); 
 
             if(status == 0)
             {
                 return 0;
             }
             if(i<4)
             {
                 check_value+=value_array[i];    
            }
         }
         /************************************/
         //数据校验 
         if(check_value == value_array[4])
         {
             //将湿度保存起来
             humi_value_H = value_array[0];
             humi_value_L = value_array[1];
             humi_value_H<<=8;
             humi_value = humi_value_H |    humi_value_L;
         }
     }//
     //return humi_value;
      return value_array[2];

 }