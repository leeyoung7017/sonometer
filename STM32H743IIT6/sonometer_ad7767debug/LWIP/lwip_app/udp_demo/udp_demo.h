#ifndef __UDP_DEMO_H
#define __UDP_DEMO_H
#include "sys.h"
#include "main.h"
#include "ad7767.h"
#include "bsp_i2s.h"
#include "lwip_comm.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//UDP ���Դ���	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/25
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   
 
#define UDP_DEMO_RX_BUFSIZE		200		//����udp���������ݳ��� 


extern u8 udp_demo_recvbuf[UDP_DEMO_RX_BUFSIZE];	//UDP�������ݻ����� 
//UDP������������
extern uint8_t *tcp_demo_sendbuf;
extern struct udp_pcb *udp_demo_pcb;  	//����һ��TCP���������ƿ�

void udp_demo_test(void);
void udp_demo_recv(void *arg,struct udp_pcb *upcb,struct pbuf *p,struct ip_addr *addr,u16_t port);
void udp_demo_senddata(struct udp_pcb *upcb);
void udp_demo_connection_close(struct udp_pcb *upcb);
void udp_send_buf(uint8_t* buf);
ErrorStatus Instruction_Parsed_ETH(void);
ErrorStatus Instrument_Func_Conv(void);
void USART_Printf(void);

#endif

