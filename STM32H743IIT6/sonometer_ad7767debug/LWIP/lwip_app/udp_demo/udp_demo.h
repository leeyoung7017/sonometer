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
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//UDP 测试代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/25
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//*******************************************************************************
//修改信息
//无
////////////////////////////////////////////////////////////////////////////////// 	   
 
#define UDP_DEMO_RX_BUFSIZE		200		//定义udp最大接收数据长度 


extern u8 udp_demo_recvbuf[UDP_DEMO_RX_BUFSIZE];	//UDP接收数据缓冲区 
//UDP发送数据内容
extern uint8_t *tcp_demo_sendbuf;
extern struct udp_pcb *udp_demo_pcb;  	//定义一个TCP服务器控制块

void udp_demo_test(void);
void udp_demo_recv(void *arg,struct udp_pcb *upcb,struct pbuf *p,struct ip_addr *addr,u16_t port);
void udp_demo_senddata(struct udp_pcb *upcb);
void udp_demo_connection_close(struct udp_pcb *upcb);
void udp_send_buf(uint8_t* buf);
ErrorStatus Instruction_Parsed_ETH(void);
ErrorStatus Instrument_Func_Conv(void);
void USART_Printf(void);

#endif

