/*
 * @Descripttion: 
 * @version: 
 * @Author: leeyoung7017
 * @Date: 2021-12-11 16:13:00
 * @Email: leeyoung7017@163.com
 */
#ifndef __UDP_DEMO_H__
#define __UDP_DEMO_H__

#include "stm32h7xx_hal.h"
#include "main.h"
#include "lwip/udp.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "string.h"
#include "ad7767.h"
#include "bsp_key.h"
#include "timer.h"


#define UDP_DEMO_RX_BUFSIZE 1500
#define UDP_DEMO_TX_BUFSIZE 1500

extern char* tcp_demo_sendbuf;
extern struct udp_pcb *udp_demo_pcb;

void udp_demo_senddata(struct udp_pcb *upcb);
void UDP_Init(void);
ErrorStatus Instruction_Parsed_ETH(void);
ErrorStatus Instrument_Func_Conv(void);

#endif //udp_demo.h
