#ifndef  __SMG_H_
#define  __SMG_H_
#include "../../main.h"

//#define  DEBUG_PROCESS   1

//extern volatile uint8_t DispData[3];//显示LED位数
#define		BitSET(x,y)		x|=(1<<y)				//置1
#define		BitCLR(x,y)		x&=~(1<<y)				//置0


#define ModeDispTM1617      0x40 //写数据到显示寄存器
		
#define AddrAutoAdd        0x40//写显示，自动累加地址  
#define AddrFixed 	    0x44//写显示，固定地址  
 

#define OpenDispTM1617           	0x88//开显示
#define CloseDisTM1617		    0x00//关显示
#define Dsip_Mode                   0x03 //显示 3位7段
 
 //Display Address 
#define Addr00H  	0xC0//地址00H
#define Addr01H  	0xC1//地址01H
#define Addr02H  	0xC2//地址02H
#define Addr03H  	0xC3//地址03H
#define Addr0CH         0xCC//地址0CH
#define Addr0DH         0xCD//地址0DH



 
#define Set1_16TM1617 			0X00//设置脉冲宽度为 1/16 
#define Set2_16TM1617 			0X01//设置脉冲宽度为 2/16 
#define Set4_16TM1617			0X02//设置脉冲宽度为 4/16 
#define Set10_16TM1617 		    0X03//设置脉冲宽度为 10/16 
#define Set11_16TM1617 		    0X04//设置脉冲宽度为 11/16 
#define Set12_16TM1617		    0X05//设置脉冲宽度为 12/16 
#define Set13_16TM1617 		    0X06//设置脉冲宽度为 13/16 
#define Set14_16TM1617 		    0X07//设置脉冲宽度为 14/16 



/**************************************************
	//                a
        //            ---------
        //           |         |
        //         f |         | b
        //           |    g    |
        //            ---------
        //           |         |
        //         e |         | c
        //           |    d    |
        //            ---------   O <- h
        //
**************************************************/
//偶数地址，SEG1~SEG8
//TM1629
// #define   seg_a  0x01       //seg_a   //seg_e = 0x10  
// #define   seg_b  0x02      //seg_b , //seg_f = 0x20
// #define   seg_c  0x04      //seg_c , //seg_g = 0x40
// #define   seg_d  0x08      //seg_d , //seg_d = 0x08
// #define   seg_e  0x10      //seg_e , //seg_c = 0x04
// #define   seg_f  0x20      //seg_f   //seg_a = 0x01
// #define   seg_g  0x40      //seg_g   //seg_b = 0x02 

//TM1617
#define   seg_a  0x10      
#define   seg_b  0x20     
#define   seg_c  0x40      
#define   seg_d  0x80      
#define   seg_e  0x01      
#define   seg_f  0x02      
#define   seg_g  0x04      









void SmgDisplay_Numbers(uint8_t num1,uint8_t num2,uint8_t num3);



void SmgDisplay_H_Char(void);


void SmgDisplay_DynamicTemperatureNum(void);

void SmgDisplay_DynamicTimeNum(void);


void SmgDisplay_Off(void);


void SetTemperature_Numbers(void);
void SetTimer_Timing(void);

void SmgDisplay_Single_DIG1(uint8_t num);
void SmgDisplay_Single_DIG2(uint8_t num);
void SmgDisplay_Single_DIG3(uint8_t num);
#ifdef DEBUG_PROCESS
        void Smg_TestPro(void);
#endif 

#endif 
