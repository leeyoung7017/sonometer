#include "udp_demo.h"
#include "lwip/udp.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"
#include "string.h"
#include "bsp_led.h"
#include "bsp_i2s.h"

struct udp_pcb *udp_demo_pcb;
char udp_demo_recvbuf[UDP_DEMO_RX_BUFSIZE];
char udp_demo_sendbuf[UDP_DEMO_TX_BUFSIZE];
char* tcp_demo_sendbuf = "OK\n";

void Udp_Receive_Callback(void *arg,struct udp_pcb *upcb,struct pbuf *p, ip_addr_t *addr,uint16_t port) 
{
	uint32_t data_len = 0;
	struct pbuf *q;
	if(p != NULL)	//接收非空时
	{
		memset(udp_demo_recvbuf,0,UDP_DEMO_RX_BUFSIZE);
		for(q=p;q!=NULL;q=q->next)
		{
			if(q->len > (UDP_DEMO_RX_BUFSIZE-data_len)) 
				memcpy(udp_demo_recvbuf+data_len,q->payload,(UDP_DEMO_RX_BUFSIZE-data_len));
			else 
				memcpy(udp_demo_recvbuf+data_len,q->payload,q->len);
			data_len += q->len;  	
			if(data_len > UDP_DEMO_RX_BUFSIZE) 
				break;
		}
		
		/* 指示已经完成一次数据的接收 */
		LED_ONOFF(LED(2));

		/*解析ETH接收指令*/
		if(Instruction_Parsed_ETH() == SUCCESS)		//解析正确
		{
			tcp_demo_sendbuf = "OK\n";
			udp_demo_senddata(udp_demo_pcb);
		}
		else if(Instruction_Parsed_ETH() == ERROR)	//解析错误
		{
			tcp_demo_sendbuf = "ERR";
			udp_demo_senddata(udp_demo_pcb);
		}
		/* 定时器更新中断处理 */
				if(Mode_Switch == 0)//判断切换模式：标准模式	校准模式
				{
					Mode_Switch = 2;
					// 标准模式下，播放音频1s
					Audio_Play(Hz_Audio,Db_Audio);
				}
				else if(Mode_Switch == 1)
				{
					//校准模式下操作
					 
				}
		pbuf_free(p);
	}
	else
	{
		udp_disconnect(udp_demo_pcb);
	}
}

//UDP发送数据
void udp_demo_senddata(struct udp_pcb *upcb)
{
	struct pbuf *ptr;
	ptr=pbuf_alloc(PBUF_TRANSPORT,strlen((char*)tcp_demo_sendbuf),PBUF_POOL);
	if(ptr)
	{
		pbuf_take(ptr,(char*)tcp_demo_sendbuf,strlen((char*)tcp_demo_sendbuf));
		udp_send(upcb,ptr);
		pbuf_free(ptr);
	} 
} 

void UDP_Init(void)
{

	err_t err;
	ip_addr_t ipaddr;
	ip_addr_t ipaddr_dest;
 
	IP_ADDR4(&ipaddr,IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
	IP_ADDR4(&ipaddr_dest,DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3);
	
	udp_demo_pcb = udp_new();
	if(udp_demo_pcb != NULL)
	{
		err = udp_bind(udp_demo_pcb,&ipaddr,DEST_PORT);
		if(err == ERR_OK)
		{
			err = udp_connect(udp_demo_pcb,&ipaddr_dest,DEST_PORT);
			if(err == ERR_OK)
			{
				/* 配置接收回调函数 */
				udp_recv(udp_demo_pcb,(udp_recv_fn)Udp_Receive_Callback,NULL);
				
				/* 指示udp网口已连接 */
				LED2(1);
			}
			else
			{
				udp_remove(udp_demo_pcb);	//删除udp控制块
			}
		}
		else
		{
			udp_remove(udp_demo_pcb);	//删除udp控制块
		}
		
	}
}

/**
 *@brief 解析网口指令 
 *@return 返回枚举类型，判断解析指令是否错误
 *
 */
ErrorStatus Instruction_Parsed_ETH(void)
{

	/* 解析音频传输指令 标准模式*/
	if(udp_demo_recvbuf[0] == 0)
	{
		Mode_Switch = 0;//标准模式
		if(udp_demo_recvbuf[1] == 'H' && udp_demo_recvbuf[2] == 'Z')	//音频频率
		{
			Hz_Audio = (udp_demo_recvbuf[3]<<8) + (udp_demo_recvbuf[4] & 0xffff);
			if(udp_demo_recvbuf[5] == 'D' && udp_demo_recvbuf[6] == 'B')	//音频幅度
			{
				Db_Audio = (udp_demo_recvbuf[7]<<8) + (udp_demo_recvbuf[8] & 0xffff);
				if(udp_demo_recvbuf[9] != 0)	//音频单声道测试
				{
					Ear_Audio = udp_demo_recvbuf[9];
					return SUCCESS;
				}
			}
		}
	}
	/* 解析音频传输指令 校准模式*/
	else if(udp_demo_recvbuf[0] == 0x01)
	{
		Mode_Switch = 1;//校准模式
		/*************启动AD7767开启**************/

	
		
		/****************************************/
	}
	
	return ERROR;
}


