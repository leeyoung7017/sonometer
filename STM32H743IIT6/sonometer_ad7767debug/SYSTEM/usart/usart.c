#include "usart.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用os,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32H7开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2017/6/8
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.0修改说明 
////////////////////////////////////////////////////////////////////////////////// 	  
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
#if 1
//#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 


UART_HandleTypeDef UART1_Handler; //UART句柄

//重定义fputc函数 
int fputc(int ch, FILE *f)
{
//	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
	UART1_Handler.Instance->TDR = ch;
	while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TXE)==RESET);
	return ch;
}
#endif 

#if EN_USART1_RX   //如果使能了接收

uint8_t RxBuffer[10] = {0};


//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound)
{	
	//UART 初始化设置
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //波特率
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()会使能UART1
	
//	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
  
}

//UART底层初始化，时钟使能，引脚配置，中断配置
//此函数会被HAL_UART_Init()调用
//huart:串口句柄

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//复用为USART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
#if EN_USART1_RX
        HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,0,0);			//抢占优先级3，子优先级3
        __HAL_UART_ENABLE_IT(&UART1_Handler,UART_IT_RXNE);
#endif	
	}

}



void USART1_IRQHandler(void)
{
	static uint8_t i = 0;
	if(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE) != RESET)
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler,UART_FLAG_RXNE);
		if(__HAL_UART_GET_IT_SOURCE(&UART1_Handler,UART_IT_RXNE) != RESET)
		{
            
              __HAL_UART_CLEAR_IT(&UART1_Handler,UART_IT_RXNE);
			// RxBuffer[0] = UART1_Handler.Instance->RDR;
//				if(UART1_Handler.Instance->RDR == 0x5A)	i = 0;
				RxBuffer[i] = UART1_Handler.Instance->RDR;
				i++;
				if(i==10)
                {
                    i = 0;	
                    USART1_Opera();
//                    TIM_ENABLE_IT(ENABLE);
                }
            
		}
	}
    
    
}



/**
 * @brief 解析串口指令实现相应功能 
 * @param NULL
 * @return NULL
 * @note
 *          5A A5 08 83 11 11 00 01 00 00   切换下一页面
 *          5A A5 08 83 22 22 00 01 00 00   接收反馈
 */
void USART1_Opera(void)
{
	int16_t Rx_addr = ((RxBuffer[4] << 8) & 0xff00) + (RxBuffer[5] & 0xff);
	switch(Rx_addr)
	{
		case 0x1111:
			if(RxBuffer[7] == 0x01)
			{
//				flag_ready = 1;			//准备就绪
                LED1_Toggle;
//				Key_Change(KeyReady,0);   //按键键值复位
                /* 数据反馈 */
                udp_send_buf("ready");
			}
			break;
		case 0x2222:
			if(RxBuffer[7] == 0x01)
			{
//				flag_feedback = 1;		//接收到反馈
                LED1_Toggle;
//                Key_Change(KeyAudio,0);   //按键键值复位 
                udp_send_buf("OK");
//                LED3(1);
			}
			break;
		default:
			break;
	}
    memset(RxBuffer,'\0',sizeof(RxBuffer));

}

/**
 * @brief 切换串口屏页面
 * @param uint16_t 切换到指定页面
 * @return NULL
 */
void Page_Switch(PageNum page)
{
    int i=0;
	uint8_t PageSwitch_array[6] = {0x5A, 0xA5, 0x03, 0x80, 0x04, 0};
	PageSwitch_array[5] = (page & 0xff);
	for(i=0;i<6;i++)
	{
		printf("%c",PageSwitch_array[i]&0xFF);
	}
    
//        HAL_UART_Transmit(&UART1_Handler,PageSwitch_array,6,1000);
	
}


void Key_Change(KeyAddr addr,uint32_t KeyValue)
{
    int i=0;
    uint8_t buf[10] = {0x5A,0xA5,0x08,0x82,0x11,0x11,0x00,0x00,0x00,0x00};
    buf[4] = (addr >> 8) & 0xff;
    buf[5] =  addr & 0xff;
    buf[7] = KeyValue;
    for(i=0;i<10;i++)
	{
		printf("%c",buf[i]&0xFF);
	}
}
void Key_Read(KeyAddr addr)
{
    int i=0;
    uint8_t buf[7] = {0x5A,0xA5,0x04,0x83,0x11,0x11,0x02};
    buf[4] = (addr >> 8) & 0xff;
    buf[5] =  addr & 0xff;
    for(i=0;i<7;i++)
	{
		printf("%c",buf[i]&0xFF);
	}
}


/* 仅限于在串口屏连接之前使用 */
void USART_Printf(void)
{
    if(Mode_Switch==0)
    {
        printf("进入标准模式\r\n");
        printf("音频频率为%dHZ\r\n",Hz_Audio);
        printf("音频音量为%dDB\r\n",Db_Audio);
        switch(Ear_Audio)
        {
            case 0x01:
                printf("单声道为左声道\r\n");
                break;
            case 0x02:
                printf("单声道为右声道\r\n");
                break;
            default:
                printf("未选择单声道\r\n");
                break;
        }
        printf("播放时长为%fs\r\n",time);
    }
    else if(Mode_Switch == 1)
    {
         printf("进入校准模式\r\n");
    }
}

#endif
/*********************************************END OF FILE**********************/

 

 

 




