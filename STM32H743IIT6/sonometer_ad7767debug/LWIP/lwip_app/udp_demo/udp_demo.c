#include "udp_demo.h" 
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "malloc.h"
#include "stdio.h"
#include "string.h" 
#include "usart.h"
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
 
//UDP�������ݻ�����
u8 udp_demo_recvbuf[UDP_DEMO_RX_BUFSIZE];	//UDP�������ݻ����� 
//UDP������������
uint8_t *tcp_demo_sendbuf;

struct udp_pcb *udp_demo_pcb;  	//����һ��TCP���������ƿ�

//UDP ����ȫ��״̬��Ǳ���
//bit7:û���õ�
//bit6:0,û���յ�����;1,�յ�������.
//bit5:0,û��������;1,��������.
//bit4~0:����
u8 udp_demo_flag;


//����Զ��IP��ַ
void udp_demo_set_remoteip(void)
{
	//ǰ����IP���ֺ�DHCP�õ���IPһ��
	lwipdev.remoteip[0]=192;
	lwipdev.remoteip[1]=168;
	lwipdev.remoteip[2]=1; 
	lwipdev.remoteip[3]=67;	
} 

//UDP����
void udp_demo_test(void)
{
 	err_t err;
	struct ip_addr rmtipaddr;  	//Զ��ip��ַ
 	struct ip_addr localipaddr;  	//Զ��ip��ַ
 	
//	udp_demo_set_remoteip();//��ѡ��IP 
	udp_demo_pcb=udp_new();
	if(udp_demo_pcb)//�����ɹ�
	{ 
        IP4_ADDR(&rmtipaddr,lwipdev.remoteip[0],lwipdev.remoteip[1],lwipdev.remoteip[2],lwipdev.remoteip[3]);
		err=udp_connect(udp_demo_pcb,&rmtipaddr,DEST_PORT);//UDP�ͻ������ӵ�ָ��IP��ַ�Ͷ˿ںŵķ�����
		if(err==ERR_OK)
		{
            IP4_ADDR(&localipaddr,lwipdev.ip[0],lwipdev.ip[1],lwipdev.ip[2],lwipdev.ip[3]);
            err = udp_bind(udp_demo_pcb,&localipaddr,UDP_DEMO_PORT);
//			err=udp_bind(udp_demo_pcb,IP_ADDR_ANY,UDP_DEMO_PORT);//�󶨱���IP��ַ��˿ں�
			if(err==ERR_OK)	//�����
			{
				udp_recv(udp_demo_pcb,udp_demo_recv,NULL);//ע����ջص����� 
                LED1(0); //����DS0��  
                
            }
		}	
	}
} 


//UDP�������ص�����
void udp_demo_recv(void *arg,struct udp_pcb *upcb,struct pbuf *p,struct ip_addr *addr,u16_t port)
{
	u32 data_len = 0;
	struct pbuf *q;
    
    LED1_Toggle;        ;
	if(p!=NULL)	//���յ���Ϊ�յ�����ʱ
	{
		memset(udp_demo_recvbuf,0,UDP_DEMO_RX_BUFSIZE);  //���ݽ��ջ���������
		for(q=p;q!=NULL;q=q->next)  //����������pbuf����
		{
			//�ж�Ҫ������UDP_DEMO_RX_BUFSIZE�е������Ƿ����UDP_DEMO_RX_BUFSIZE��ʣ��ռ䣬�������
			//�Ļ���ֻ����UDP_DEMO_RX_BUFSIZE��ʣ�೤�ȵ����ݣ�����Ļ��Ϳ������е�����
			if(q->len > (UDP_DEMO_RX_BUFSIZE-data_len)) memcpy(udp_demo_recvbuf+data_len,q->payload,(UDP_DEMO_RX_BUFSIZE-data_len));//��������
			else memcpy(udp_demo_recvbuf+data_len,q->payload,q->len);
			data_len += q->len;  	
			if(data_len > UDP_DEMO_RX_BUFSIZE) break; //����TCP�ͻ��˽�������,����	
		}
        /* ʵ��ָ��Ľ����빦�ܵ�ʵ�� */
		if(Instrument_Func_Conv() != SUCCESS)
		{
			return ;
		}
		pbuf_free(p);//�ͷ��ڴ�
	}else
	{
		udp_disconnect(upcb); 
	} 
} 
//UDP��������������
void udp_demo_senddata(struct udp_pcb *upcb)
{
	struct pbuf *ptr;
	ptr=pbuf_alloc(PBUF_TRANSPORT,strlen((char*)tcp_demo_sendbuf),PBUF_POOL); //�����ڴ�
	if(ptr)
	{
		ptr->payload=(void*)tcp_demo_sendbuf; 
		udp_send(upcb,ptr);	//udp�������� 
		pbuf_free(ptr);//�ͷ��ڴ�
	} 
} 
//�ر�tcp����
void udp_demo_connection_close(struct udp_pcb *upcb)
{
	udp_disconnect(upcb); 
	udp_remove(upcb);		//�Ͽ�UDP���� 
}


void udp_send_buf(uint8_t* buf)
{
    tcp_demo_sendbuf = buf;
    udp_demo_senddata(udp_demo_pcb);
}


/**
 *@brief ��������ָ�� 
 *@return ����ö�����ͣ��жϽ���ָ���Ƿ����
 *
 */
ErrorStatus Instruction_Parsed_ETH(void)
{
    if(udp_demo_recvbuf[0] == 'O' && udp_demo_recvbuf[1] == 'V' && udp_demo_recvbuf[2] == 'E' && udp_demo_recvbuf[3] == 'R')
    {
        Page_Switch(page1);
        return SUCCESS;
    }

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
					if(udp_demo_recvbuf[10] == 'T' && udp_demo_recvbuf[11] == 'I' && udp_demo_recvbuf[12] == 'M' && udp_demo_recvbuf[13] == 'E')
                    {
                        time = (double)udp_demo_recvbuf[14]/10;
                        return SUCCESS;
                    }
				}
			}
		}
		else if(udp_demo_recvbuf[1] == 0 && udp_demo_recvbuf[2] == '\0')//У׼ģʽ�رմ���,�ر�EXTI�ⲿ�ж�
		{
			HAL_EXTI_DISABLE(GPIO_PIN_14);
			return SUCCESS;
		}
	}
	/* ������Ƶ����ָ�� У׼ģʽ*/
	else if(udp_demo_recvbuf[0] == 0x01)
	{
		Mode_Switch = 1;//У׼ģʽ
		/*************����AD7767����**************/

		/****************************************/
		return SUCCESS;
	}	
	return ERROR;
}


/**
 *@brief ָ������빦��ʵ�� 
 *@param none
 *@return ����ö�����ͣ��жϽ���ָ���Ƿ����
 *
 */
ErrorStatus Instrument_Func_Conv(void)
{
	/*����ETH����ָ��*/
	if(Instruction_Parsed_ETH() == SUCCESS)		//������ȷ
	{
//        USART_Printf();//�����ڴ���������֮ǰ
	}
	else if(Instruction_Parsed_ETH() == ERROR)	//��������
	{
		tcp_demo_sendbuf = (u8*)"ERR";
		udp_demo_senddata(udp_demo_pcb);
		return ERROR;
	}
	/* ��ʱ�������жϴ��� */
	if(Mode_Switch == 0)//��׼ģʽ
	{
		Mode_Switch = 2;
		//��AD7767�ⲿ�ж�ʧ��
		HAL_EXTI_DISABLE(DRDY_Pin);
		//AD7767 CSƬѡʧ��
		CS_DISABLE;
		// ��׼ģʽ�£�������Ƶ1s
		Audio_Play(Hz_Audio,Db_Audio);
	}
	else if(Mode_Switch == 1)//У׼ģʽ�²���
	{
//		HAL_TIM_Base_Stop_IT(&htimx);
//        TIM_ENABLE_IT(DISABLE);
		//AD7767 �ⲿ�ж�ʹ��
		HAL_EXTI_ENABLE(DRDY_Pin);
		//AD7767 CSƬѡʹ��
		CS_ENABLE;
		//�����ⲿ�ж�ʧ��
//		HAL_EXTI_DISABLE(KEY_CTR_Pin);
	}
	return SUCCESS;
}



















