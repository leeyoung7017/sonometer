#ifndef _USART_H
#define _USART_H
#include "sys.h"
#include "stdio.h"	
#include "stm32h7xx.h"
#include <stdio.h>
#include "main.h"
#include "udp_demo.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32H7开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.csom
//修改日期:2017/6/8
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.0修改说明 
////////////////////////////////////////////////////////////////////////////////// 	
//#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	


//如果想串口中断接收，请不要注释以下宏定义
extern uint8_t RxBuffer[10];

typedef enum{
    page1 = 0u,
    page2 = 1u,
    page3 = 2u
}PageNum;

typedef enum{
    KeyReady = 0x1111,
    KeyAudio = 0x2222
}KeyAddr;


void uart_init(u32 bound);
void USART1_Opera(void);
void Page_Switch(PageNum page);
void Key_Change(KeyAddr addr,uint32_t KeyValue);
void Key_Read(KeyAddr addr);
void USART_Printf(void);
#endif
