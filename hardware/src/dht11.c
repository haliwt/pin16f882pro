#include "../inc/dht11.h"
#include <string.h>

DHT11_info dht11_t;


uint8_t DHT11_ReadBit(uint8_t *pdat) ;

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
	DHT11_DQ_DATA =0 ;    //A
    __delay_ms(20);
	DHT11_DQ_DATA=1; //C
	//__delay_us(30); //40 <data<100us
   // TRISAbits.TRISA5 =1;
	
}

//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在  
uint8_t DHT11_IsOnLine(void)
{
     uint8_t retry =0;
	TRISAbits.TRISA5 =1;
	retry = 40;
    while((DHT11_DQ_DATA==1) && retry )//dq pull down low 40~80us
		{
			__delay_us(1);
			retry --;
		}
	  
	  if(!retry){
		  return 1;
	   }
	 
		retry =100;
	  while((DHT11_DQ_DATA==0) && retry  )// dq pull up again  40~80us
	  {
		 
		  __delay_us(1);
		  retry --;
	  }
	  if(!retry){ // if(retry >=1000){
		  return 1;
	   }
	   retry = 100;

	   while((DHT11_DQ_DATA==1) && retry )// wait high level 
	   {
		  
		  __delay_us(1);
		  retry --;
	   }
	  if(!retry){
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
 	 int retry;
	 uint8_t i,dat; 
	for(i=0;i<8;i++){

		retry = 100;
		while(DHT11_DQ_DATA==1 && retry ); //&& retry < 100) //等待变成低电平
		{
			__delay_us(1);
			retry --;
		}
		if (!retry) 
        {
            //printk("timeout %d\n", __LINE__);         
            return 0;           /* 超时 */
        }
		retry =100;

		while((DHT11_DQ_DATA==0) && retry )// 等待变成高电平
		{
		
			__delay_us(1);
			retry --;
		}
		if (!retry) 
        {
            //printk("timeout %d\n", __LINE__);         
            return 0;           /* 超时 */
        }
		__delay_us(40);
		dat = dat << 1; 

		if(DHT11_DQ_DATA==1){
			
			dat |=0x01;
			//return 1;
		}
		else{
			dat |= 0x0;
			//return 0;
		}
	}
	*pdat = dat;
    return dat;
    
}



uint8_t DHT11_ReadByte(void)    
{        
    uint8_t i,dat;
    dat = 0;
	for (i = 0; i < 8; i ++) 
	{
   		dat = dat << 1; 
	   // dat |= DHT11_ReadBit() ;
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
		    buf[i]	=DHT11_ReadBit(&vr) ;	//DHT11_ReadByte();
		   // dht11_read_byte(&buf[i]);
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

        timeout = 100;
        while ((DHT11_DQ_DATA==0) && timeout)    /* 等待变为高电平 */
        {
            NOP();// __delay_us(1);
            --timeout;
        }
        if (!timeout) 
        {
           // printk("timeout %d\n", __LINE__);
           return 0;           /* 超时 */
        }
        //__delay_us(40); //level high  of time
	    Delay_10us();
		Delay_10us();
		Delay_10us();
        
        bit = DHT11_DQ_DATA;
		data = data << 1;            
        if (bit)
		{
			//dht11_t.data |= 0x01; 
			data |= 0x01;
		} 
		else{
			data |= 0x00;
		}
     //  *byte = data;
	}
	  *byte = data;
        return 0;	
		
	
}


/**
	* @brief DHT11 读取字节
	*/
uint8_t DHT11_One_ReadByte(void)
{
	uint8_t j,retry=0,data;
	for(j=0;j<8;j++)
	{
		while((DHT11_DQ_DATA==0) && retry <100)//等待拉高
		{
			__delay_us(1);
			retry++;
		}
		if(retry>= 100)
		{
		
			retry = 0;
			return 0 ;
		}else{
			retry = 0;
		}
		
		__delay_us(40);
		if(DHT11_DQ_DATA==0)
		{
			data &= ~(1<<(7-j));
		}
        else{
			data |= 1<<(7-j);
			while((DHT11_DQ_DATA==1) && retry <100)//等待拉低
			{
				__delay_us(1);
				retry++;
			}
			if(retry>= 100)
			{
				//printf("time out5\r\n");
				retry = 0;
				return 0;
			}else{
				retry = 0;
			}
		}
	}
	return data;
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

/* 
 * 从DHT11读取一个字节，MSB先行
 */
uint8_t Read_Byte(void)
{
	uint8_t i, temp=0;

	for(i=0;i<8;i++)    
	{	 
		/*每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束*/  
		while(DHT11_DQ_DATA==0);

		/*DHT11 以26~28us的高电平表示“0”，以70us高电平表示“1”，
		 *通过检测 x us后的电平即可区别这两个状 ，x 即下面的延时 
		 */
		__delay_us(40); //延时x us 这个延时需要大于数据0持续的时间即可	   	  
        temp <<= 1;            
		if(DHT11_DQ_DATA==1)/* x us后仍为高电平表示数据“1” */
		{
			/* 等待数据1的高电平结束 */
			while(DHT11_DQ_DATA==1);
             temp |= 0x01;
			//temp|=(uint8_t)(0x01<<(7-i));  //把第7-i位置1，MSB先行 
		}
		
	}
	//SmgDisplay_Numbers(0x0b,temp/10,temp%10);
	return temp;
}

/*
 * 一次完整的数据传输为40bit，高位先出
 * 8bit 湿度整数 + 8bit 湿度小数 + 8bit 温度整数 + 8bit 温度小数 + 8bit 校验和 
 */
uint8_t Read_DHT11(void)
{  
	 uint8_t check_sum;
	
	DHT11_Reset();
//	DHT11_IsOnLine();

	if(DHT11_IsOnLine() == 0) 
	{
	
		/*开始接收数据*/   
		//DHT11_Data->humi_int= Read_Byte();
		dht_dat[0]= Read_Byte();
		// //DHT11_Data->humi_deci= Read_Byte();
        // dht_dat[1]= Read_Byte();
		// //DHT11_Data->temp_int= Read_Byte();
		// dht_dat[2]= Read_Byte();
		// //DHT11_Data->temp_deci= Read_Byte();
		// dht_dat[3]= Read_Byte();
		// //DHT11_Data->check_sum= Read_Byte();
		// check_sum = Read_Byte();

		SmgDisplay_Numbers(0x0b,dht_dat[0]/10,dht_dat[0]%10);
		/*检查读取的数据是否正确*/
		if(check_sum == dht_dat[0]+ dht_dat[1]+ dht_dat[2]+ dht_dat[3])
		{
			Breath_RA0_LED =1;
			return 1;
		}
		else 
			return 0;
	}
	else
	{		
		dht_dat[0]=0x32;
		dht_dat[2]= 0x47;
		return 0;
	}   
}
