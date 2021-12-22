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
	if(p != NULL)	//���շǿ�ʱ
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
		
		/* ָʾ�Ѿ����һ�����ݵĽ��� */
		LED_ONOFF(LED(2));

		/*����ETH����ָ��*/
		if(Instruction_Parsed_ETH() == SUCCESS)		//������ȷ
		{
			tcp_demo_sendbuf = "OK\n";
			udp_demo_senddata(udp_demo_pcb);
		}
		else if(Instruction_Parsed_ETH() == ERROR)	//��������
		{
			tcp_demo_sendbuf = "ERR";
			udp_demo_senddata(udp_demo_pcb);
		}
		/* ��ʱ�������жϴ��� */
				if(Mode_Switch == 0)//�ж��л�ģʽ����׼ģʽ	У׼ģʽ
				{
					Mode_Switch = 2;
					// ��׼ģʽ�£�������Ƶ1s
					Audio_Play(Hz_Audio,Db_Audio);
				}
				else if(Mode_Switch == 1)
				{
					//У׼ģʽ�²���
					 
				}
		pbuf_free(p);
	}
	else
	{
		udp_disconnect(udp_demo_pcb);
	}
}

//UDP��������
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
				/* ���ý��ջص����� */
				udp_recv(udp_demo_pcb,(udp_recv_fn)Udp_Receive_Callback,NULL);
				
				/* ָʾudp���������� */
				LED2(1);
			}
			else
			{
				udp_remove(udp_demo_pcb);	//ɾ��udp���ƿ�
			}
		}
		else
		{
			udp_remove(udp_demo_pcb);	//ɾ��udp���ƿ�
		}
		
	}
}

/**
 *@brief ��������ָ�� 
 *@return ����ö�����ͣ��жϽ���ָ���Ƿ����
 *
 */
ErrorStatus Instruction_Parsed_ETH(void)
{

	/* ������Ƶ����ָ�� ��׼ģʽ*/
	if(udp_demo_recvbuf[0] == 0)
	{
		Mode_Switch = 0;//��׼ģʽ
		if(udp_demo_recvbuf[1] == 'H' && udp_demo_recvbuf[2] == 'Z')	//��ƵƵ��
		{
			Hz_Audio = (udp_demo_recvbuf[3]<<8) + (udp_demo_recvbuf[4] & 0xffff);
			if(udp_demo_recvbuf[5] == 'D' && udp_demo_recvbuf[6] == 'B')	//��Ƶ����
			{
				Db_Audio = (udp_demo_recvbuf[7]<<8) + (udp_demo_recvbuf[8] & 0xffff);
				if(udp_demo_recvbuf[9] != 0)	//��Ƶ����������
				{
					Ear_Audio = udp_demo_recvbuf[9];
					return SUCCESS;
				}
			}
		}
	}
	/* ������Ƶ����ָ�� У׼ģʽ*/
	else if(udp_demo_recvbuf[0] == 0x01)
	{
		Mode_Switch = 1;//У׼ģʽ
		/*************����AD7767����**************/

	
		
		/****************************************/
	}
	
	return ERROR;
}


