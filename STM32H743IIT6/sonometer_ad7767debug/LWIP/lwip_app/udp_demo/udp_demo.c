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
 
//UDP接收数据缓冲区
u8 udp_demo_recvbuf[UDP_DEMO_RX_BUFSIZE];	//UDP接收数据缓冲区 
//UDP发送数据内容
uint8_t *tcp_demo_sendbuf;

struct udp_pcb *udp_demo_pcb;  	//定义一个TCP服务器控制块

//UDP 测试全局状态标记变量
//bit7:没有用到
//bit6:0,没有收到数据;1,收到数据了.
//bit5:0,没有连接上;1,连接上了.
//bit4~0:保留
u8 udp_demo_flag;


//设置远端IP地址
void udp_demo_set_remoteip(void)
{
	//前三个IP保持和DHCP得到的IP一致
	lwipdev.remoteip[0]=192;
	lwipdev.remoteip[1]=168;
	lwipdev.remoteip[2]=1; 
	lwipdev.remoteip[3]=67;	
} 

//UDP测试
void udp_demo_test(void)
{
 	err_t err;
	struct ip_addr rmtipaddr;  	//远端ip地址
 	struct ip_addr localipaddr;  	//远端ip地址
 	
//	udp_demo_set_remoteip();//先选择IP 
	udp_demo_pcb=udp_new();
	if(udp_demo_pcb)//创建成功
	{ 
        IP4_ADDR(&rmtipaddr,lwipdev.remoteip[0],lwipdev.remoteip[1],lwipdev.remoteip[2],lwipdev.remoteip[3]);
		err=udp_connect(udp_demo_pcb,&rmtipaddr,DEST_PORT);//UDP客户端连接到指定IP地址和端口号的服务器
		if(err==ERR_OK)
		{
            IP4_ADDR(&localipaddr,lwipdev.ip[0],lwipdev.ip[1],lwipdev.ip[2],lwipdev.ip[3]);
            err = udp_bind(udp_demo_pcb,&localipaddr,UDP_DEMO_PORT);
//			err=udp_bind(udp_demo_pcb,IP_ADDR_ANY,UDP_DEMO_PORT);//绑定本地IP地址与端口号
			if(err==ERR_OK)	//绑定完成
			{
				udp_recv(udp_demo_pcb,udp_demo_recv,NULL);//注册接收回调函数 
                LED1(0); //点亮DS0灯  
                
            }
		}	
	}
} 


//UDP服务器回调函数
void udp_demo_recv(void *arg,struct udp_pcb *upcb,struct pbuf *p,struct ip_addr *addr,u16_t port)
{
	u32 data_len = 0;
	struct pbuf *q;
    
    LED1_Toggle;        ;
	if(p!=NULL)	//接收到不为空的数据时
	{
		memset(udp_demo_recvbuf,0,UDP_DEMO_RX_BUFSIZE);  //数据接收缓冲区清零
		for(q=p;q!=NULL;q=q->next)  //遍历完整个pbuf链表
		{
			//判断要拷贝到UDP_DEMO_RX_BUFSIZE中的数据是否大于UDP_DEMO_RX_BUFSIZE的剩余空间，如果大于
			//的话就只拷贝UDP_DEMO_RX_BUFSIZE中剩余长度的数据，否则的话就拷贝所有的数据
			if(q->len > (UDP_DEMO_RX_BUFSIZE-data_len)) memcpy(udp_demo_recvbuf+data_len,q->payload,(UDP_DEMO_RX_BUFSIZE-data_len));//拷贝数据
			else memcpy(udp_demo_recvbuf+data_len,q->payload,q->len);
			data_len += q->len;  	
			if(data_len > UDP_DEMO_RX_BUFSIZE) break; //超出TCP客户端接收数组,跳出	
		}
        /* 实现指令的解析与功能的实现 */
		if(Instrument_Func_Conv() != SUCCESS)
		{
			return ;
		}
		pbuf_free(p);//释放内存
	}else
	{
		udp_disconnect(upcb); 
	} 
} 
//UDP服务器发送数据
void udp_demo_senddata(struct udp_pcb *upcb)
{
	struct pbuf *ptr;
	ptr=pbuf_alloc(PBUF_TRANSPORT,strlen((char*)tcp_demo_sendbuf),PBUF_POOL); //申请内存
	if(ptr)
	{
		ptr->payload=(void*)tcp_demo_sendbuf; 
		udp_send(upcb,ptr);	//udp发送数据 
		pbuf_free(ptr);//释放内存
	} 
} 
//关闭tcp连接
void udp_demo_connection_close(struct udp_pcb *upcb)
{
	udp_disconnect(upcb); 
	udp_remove(upcb);		//断开UDP连接 
}


void udp_send_buf(uint8_t* buf)
{
    tcp_demo_sendbuf = buf;
    udp_demo_senddata(udp_demo_pcb);
}


/**
 *@brief 解析网口指令 
 *@return 返回枚举类型，判断解析指令是否错误
 *
 */
ErrorStatus Instruction_Parsed_ETH(void)
{
    if(udp_demo_recvbuf[0] == 'O' && udp_demo_recvbuf[1] == 'V' && udp_demo_recvbuf[2] == 'E' && udp_demo_recvbuf[3] == 'R')
    {
        Page_Switch(page1);
        return SUCCESS;
    }

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
					if(udp_demo_recvbuf[10] == 'T' && udp_demo_recvbuf[11] == 'I' && udp_demo_recvbuf[12] == 'M' && udp_demo_recvbuf[13] == 'E')
                    {
                        time = (double)udp_demo_recvbuf[14]/10;
                        return SUCCESS;
                    }
				}
			}
		}
		else if(udp_demo_recvbuf[1] == 0 && udp_demo_recvbuf[2] == '\0')//校准模式关闭窗口,关闭EXTI外部中断
		{
			HAL_EXTI_DISABLE(GPIO_PIN_14);
			return SUCCESS;
		}
	}
	/* 解析音频传输指令 校准模式*/
	else if(udp_demo_recvbuf[0] == 0x01)
	{
		Mode_Switch = 1;//校准模式
		/*************启动AD7767开启**************/

		/****************************************/
		return SUCCESS;
	}	
	return ERROR;
}


/**
 *@brief 指令解析与功能实现 
 *@param none
 *@return 返回枚举类型，判断解析指令是否错误
 *
 */
ErrorStatus Instrument_Func_Conv(void)
{
	/*解析ETH接收指令*/
	if(Instruction_Parsed_ETH() == SUCCESS)		//解析正确
	{
//        USART_Printf();//适用于串口屏连接之前
	}
	else if(Instruction_Parsed_ETH() == ERROR)	//解析错误
	{
		tcp_demo_sendbuf = (u8*)"ERR";
		udp_demo_senddata(udp_demo_pcb);
		return ERROR;
	}
	/* 定时器更新中断处理 */
	if(Mode_Switch == 0)//标准模式
	{
		Mode_Switch = 2;
		//将AD7767外部中断失能
		HAL_EXTI_DISABLE(DRDY_Pin);
		//AD7767 CS片选失能
		CS_DISABLE;
		// 标准模式下，播放音频1s
		Audio_Play(Hz_Audio,Db_Audio);
	}
	else if(Mode_Switch == 1)//校准模式下操作
	{
//		HAL_TIM_Base_Stop_IT(&htimx);
//        TIM_ENABLE_IT(DISABLE);
		//AD7767 外部中断使能
		HAL_EXTI_ENABLE(DRDY_Pin);
		//AD7767 CS片选使能
		CS_ENABLE;
		//按键外部中断失能
//		HAL_EXTI_DISABLE(KEY_CTR_Pin);
	}
	return SUCCESS;
}



















