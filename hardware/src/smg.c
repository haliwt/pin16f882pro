#include "../inc/smg.h"

const unsigned char segNumber_high[]={
	
     
         seg_a+seg_b+seg_c+seg_d,        		// char "0"  0x00
         seg_b+seg_c,                           // char "1"  0x01
         seg_a+seg_b+seg_d,              		// char "2"  0x02
         seg_a+seg_b+seg_c+seg_d,               // char "3"  0x03
         seg_b+seg_c,                   	    // char "4"  0x04
         seg_a+seg_c+seg_d,              		// char "5"  0x05
         seg_a+seg_c+seg_d,              		// char "6"  0x06
         seg_a+seg_b+seg_c,                    	// char "7"  0x07
         seg_a+seg_b+seg_c+seg_d,  				// char "8"  0x08
         seg_a+seg_b+seg_c+seg_d,        		// char "9"  0x09
		 seg_b+seg_c,                           // char "H"  0x0A
         0                                      // char "10"  0x0B
                                               
                                             
};

const unsigned char segNumber_low[]={
	
     
         seg_e+seg_f,        			// char "0"  0x00
         0,                             // char "1"  0x01
         seg_e+seg_g,              		// char "2"  0x02
         seg_g,              			// char "3"  0x03
         seg_f+seg_g,                   // char "4"  0x04
         seg_f+seg_g,              		// char "5"  0x05
         seg_e+seg_f+seg_g,             // char "6"  0x06
         seg_f,                    		// char "7"  0x07
         seg_e+seg_f+seg_g,  			// char "8"  0x08
         seg_f+seg_g,        			// char "9"  0x09
         seg_e+seg_f+seg_g,             // char "H"  0x0A
         0                              // char "10"  0x0B
                                       
                                             
};

		 
#define CHAR_H_HI     seg_b+seg_c         //char "H"	
#define CHAR_H_LO     seg_e+seg_f+seg_g   //char "H"



/****************************************************************************************************
 * 	*
	*函数名称：void SmgDisplay_Numbers(uint8_t disdat3,uint8_t disdat2,uint8_t disdat1)
	*函数功能：
	*入口参数：disdat1 - 第一位数字 disdat2 -数码管第二位数字 disdat2 -数码管第三位数字
	*出口参数：NO
	*
*******************************************************************************************************/
void SmgDisplay_Numbers(uint8_t num1,uint8_t num2,uint8_t num3)
{
        TM1617_STB =0 ;  
        Tm1617_SendData(ModeDispTM1617); //写数据到显示寄存器
	    TM1617_STB =1; 
	
        TM1617_STB=0;   
		Tm1617_SendData(AddrFixed);//AddrFixed 写固定地址
		//写显示，固定定制模式
		TM1617_STB=1; 
		
        TM1617_STB=0;   
		Tm1617_SendData(Addr00H);
		//指向地址00H  
	    Tm1617_SendData(segNumber_high[num1]); //主显示.DIG - 1
	    //display address is 01H
	    Tm1617_SendData(Addr01H);
		Tm1617_SendData(segNumber_low[num1]); //主显示.DIG - 1
	    TM1617_STB=1; 
		
        TM1617_STB=0;   
		Tm1617_SendData(Addr02H);
		//指向地址2   
	    Tm1617_SendData(segNumber_high[num2]); //主显示.DIG- 2
        //display address is 03H
		Tm1617_SendData(Addr03H);
		Tm1617_SendData(segNumber_low[num2]); //主显示.DIG - 2
	    TM1617_STB=1; 
		
       //unit bit 
         TM1617_STB=0;   
		Tm1617_SendData(Addr0CH);
		//指向地址0CH  
        Tm1617_SendData(segNumber_high[num3]); //主显示.DIG - 1
		//display address 0DH
		Tm1617_SendData(Addr0DH);
		Tm1617_SendData(segNumber_low[num3]); //主显示.DIG - 1
		TM1617_STB=1; 


	
       TM1617_STB =0; 
       Tm1617_SendData(OpenDispTM1617|Set14_16TM1617); //开显示，显示，设置脉冲宽带 14/16
       TM1617_STB =1; 	 
	
}






void SmgDisplay_H_Char(void)
{
	    TM1617_STB =0 ;  
        Tm1617_SendData(ModeDispTM1617); //写数据到显示寄存器
	    TM1617_STB =1; 
	
        TM1617_STB=0;   
		Tm1617_SendData(AddrFixed);//AddrFixed 写固定地址
		//写显示，固定定制模式
		TM1617_STB=1; 
		
		//DIG3 
		TM1617_STB=0;   
		Tm1617_SendData(Addr00H);
		//指向地址00H  
	    Tm1617_SendData(CHAR_H_HI); //主显示.DIG - 1
	    //display address is 01H
	    Tm1617_SendData(Addr01H);
		Tm1617_SendData(CHAR_H_LO); //主显示.DIG -1
	    TM1617_STB=1; 
		
		
	   TM1617_STB =0; 
       Tm1617_SendData(OpenDispTM1617|Set14_16TM1617); //开显示，显示，设置脉冲宽带 14/16
       TM1617_STB =1; 	 
    

}


void SmgDisplay_DynamicTemperatureNum(void)
{

	    TM1617_STB =0 ;  
        Tm1617_SendData(ModeDispTM1617); //写数据到显示寄存器
	    TM1617_STB =1; 
	
        TM1617_STB=0;   
		Tm1617_SendData(AddrFixed);//AddrFixed 写固定地址
		//写显示，固定定制模式
		TM1617_STB=1; 

	    TM1617_STB=0;   
		Tm1617_SendData(Addr00H);
		//指向地址00H  
	    Tm1617_SendData(segNumber_high[0x0B]); //主显示.DIG - 1
	    //display address is 01H
	    Tm1617_SendData(Addr01H);
		Tm1617_SendData(segNumber_low[0x0B]); //主显示.DIG -1
	    TM1617_STB=1; 
		
	     if(cmd_t.tempTotal < 30){

			//decade
			TM1617_STB=0;   
			Tm1617_SendData(Addr02H);
			//指向地址2   
		    Tm1617_SendData(segNumber_high[2]); //主显示2位---十位

			//display address is 03H
			Tm1617_SendData(Addr03H);
			Tm1617_SendData(segNumber_low[2]); //主显示2 位---十位
	        TM1617_STB=1; 


		    //unit bit 
	        TM1617_STB=0;   
			Tm1617_SendData(Addr0CH);
			//指向地址0CH  
		
			Tm1617_SendData(segNumber_high[cmd_t.tempTotal]); //主显示.DIG -1
			//display address 0DH
			Tm1617_SendData(Addr0DH);
			Tm1617_SendData(segNumber_low[cmd_t.tempTotal]); //主显示.DIG - 1
			TM1617_STB=1; 
			
			
		}

		if(cmd_t.tempTotal < 40 && cmd_t.tempTotal > 29){

			//decade
			TM1617_STB=0;   
			Tm1617_SendData(Addr02H);
			//指向地址2   
		    Tm1617_SendData(segNumber_high[3]); //主显示2位---十位

			//display address is 03H
			Tm1617_SendData(Addr03H);
			Tm1617_SendData(segNumber_low[3]); //主显示2 位---十位
	        TM1617_STB=1; 


		    //unit bit 
	        TM1617_STB=0;   
			Tm1617_SendData(Addr0CH);
			
			//指向地址0CH  
			Tm1617_SendData(segNumber_high[cmd_t.tempTotal]); //主显示1位---个位
			//display address 0DH
			Tm1617_SendData(Addr0DH);
			Tm1617_SendData(segNumber_low[cmd_t.tempTotal]); //主显示1位---个位
			TM1617_STB=1;
		 
			
		
		
		}

		
	   if(cmd_t.tempTotal > 39){
	   
		   //decade
		   TM1617_STB=0;   
		   Tm1617_SendData(Addr02H);
		   //指向地址2	 
		   Tm1617_SendData(segNumber_high[4]); //主显示2位---十位

		   //display address is 03H
		   Tm1617_SendData(Addr03H);
		   Tm1617_SendData(segNumber_low[4]); //主显示2 位---十位
		   TM1617_STB=1; 


		   //unit bit 
		   TM1617_STB=0;   
		   Tm1617_SendData(Addr0CH);
		   //指向地址0CH  
		   Tm1617_SendData(segNumber_high[cmd_t.tempTotal]); //主显示1位---个位
		   //display address 0DH
		   Tm1617_SendData(Addr0DH);
		   Tm1617_SendData(segNumber_low[cmd_t.tempTotal]); //主显示1位---个位
			TM1617_STB=1; 
	   }
		
	  TM1617_STB =0; 
       Tm1617_SendData(OpenDispTM1617|Set14_16TM1617); //开显示，显示，设置脉冲宽带 14/16
       TM1617_STB =1; 	 

}


void SmgDisplay_DynamicTimeNum(void)

{
	 	TM1617_STB =0 ;  
        Tm1617_SendData(ModeDispTM1617); //写数据到显示寄存器
	    TM1617_STB =1; 
	
        TM1617_STB=0;   
		Tm1617_SendData(AddrFixed);//AddrFixed 写固定地址
		//写显示，固定定制模式
		TM1617_STB=1; 
		
		//DIG3 
		TM1617_STB=0;   
		Tm1617_SendData(Addr00H);
		//指向地址00H  
	    Tm1617_SendData(CHAR_H_HI); //主显示3 位---百位
	    //display address is 01H
	    Tm1617_SendData(Addr01H);
		Tm1617_SendData(CHAR_H_LO); //主显示3 位---百位
	    TM1617_STB=1; 

		
	     if(cmd_t.timeTotal < 10 ){
	
			 //decade
			 TM1617_STB=0;	 
			 Tm1617_SendData(Addr02H);
			 //指向地址2   
			 Tm1617_SendData(segNumber_high[0]); //主显示2位---十位
	
			 //display address is 03H
			 Tm1617_SendData(Addr03H);
			 Tm1617_SendData(segNumber_low[0]); //主显示2 位---十位
			 TM1617_STB=1; 
	
	
			 //unit bit 
			 TM1617_STB=0;	 
			 Tm1617_SendData(Addr0CH);
			 //指向地址0CH	
			 Tm1617_SendData(segNumber_high[cmd_t.timeTotal]); //主显示1位---个位
				 //display address 0DH
			 Tm1617_SendData(Addr0DH);
			  Tm1617_SendData(segNumber_low[cmd_t.timeTotal]); //主显示1位---个位
				TM1617_STB=1; 
			 
			
		 }
	
		 if(cmd_t.timeTotal < 20  && cmd_t.timeTotal > 9 ){
	
			 //decade
			 TM1617_STB=0;	 
			 Tm1617_SendData(Addr02H);
			 //指向地址2   
			 Tm1617_SendData(segNumber_high[1]); //主显示2位---十位
	
			 //display address is 03H
			 Tm1617_SendData(Addr03H);
			 Tm1617_SendData(segNumber_low[1]); //主显示2 位---十位
			 TM1617_STB=1; 
	
	
			 //unit bit 
			 TM1617_STB=0;	 
			 Tm1617_SendData(Addr0CH);
			
				 //指向地址0CH	
				 Tm1617_SendData(segNumber_high[cmd_t.timeTotal]); //主显示1位---个位
				 //display address 0DH
				 Tm1617_SendData(Addr0DH);
				 Tm1617_SendData(segNumber_low[cmd_t.timeTotal]); //主显示1位---个位
				 TM1617_STB=1;
		
		 
		 
		 }
	
		 
		if(cmd_t.timeTotal > 19){
		
			//decade
			TM1617_STB=0;	
			Tm1617_SendData(Addr02H);
			//指向地址2   
			Tm1617_SendData(segNumber_high[2]); //主显示2位---十位
	
			//display address is 03H
			Tm1617_SendData(Addr03H);
			Tm1617_SendData(segNumber_low[2]); //主显示2 位---十位
			TM1617_STB=1; 
	
	
			//unit bit 
			TM1617_STB=0;	
			Tm1617_SendData(Addr0CH);
			//指向地址0CH  
			Tm1617_SendData(segNumber_high[cmd_t.timeTotal]); //主显示1位---个位
			//display address 0DH
			Tm1617_SendData(Addr0DH);
			Tm1617_SendData(segNumber_low[cmd_t.timeTotal]); //主显示1位---个位
			 TM1617_STB=1; 
		}
		 
	   TM1617_STB =0; 
		Tm1617_SendData(OpenDispTM1617|Set14_16TM1617); //开显示，显示，设置脉冲宽带 14/16
		TM1617_STB =1;	  


}

void SmgDisplay_Off(void)
{




}


