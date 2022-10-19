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
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32H7������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.csom
//�޸�����:2017/6/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.0�޸�˵�� 
////////////////////////////////////////////////////////////////////////////////// 	
//#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	


//����봮���жϽ��գ��벻Ҫע�����º궨��
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
