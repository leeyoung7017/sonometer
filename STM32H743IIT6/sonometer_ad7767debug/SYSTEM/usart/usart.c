#include "usart.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��os,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32H7������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2017/6/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.0�޸�˵�� 
////////////////////////////////////////////////////////////////////////////////// 	  
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
#if 1
//#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 


UART_HandleTypeDef UART1_Handler; //UART���

//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
//	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
	UART1_Handler.Instance->TDR = ch;
	while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TXE)==RESET);
	return ch;
}
#endif 

#if EN_USART1_RX   //���ʹ���˽���

uint8_t RxBuffer[10] = {0};


//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound)
{	
	//UART ��ʼ������
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()��ʹ��UART1
	
//	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
  
}

//UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
//�˺����ᱻHAL_UART_Init()����
//huart:���ھ��

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO�˿�����
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//����Ǵ���1�����д���1 MSP��ʼ��
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//����ΪUSART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA10
		
#if EN_USART1_RX
        HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART1_IRQn,0,0);			//��ռ���ȼ�3�������ȼ�3
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
 * @brief ��������ָ��ʵ����Ӧ���� 
 * @param NULL
 * @return NULL
 * @note
 *          5A A5 08 83 11 11 00 01 00 00   �л���һҳ��
 *          5A A5 08 83 22 22 00 01 00 00   ���շ���
 */
void USART1_Opera(void)
{
	int16_t Rx_addr = ((RxBuffer[4] << 8) & 0xff00) + (RxBuffer[5] & 0xff);
	switch(Rx_addr)
	{
		case 0x1111:
			if(RxBuffer[7] == 0x01)
			{
//				flag_ready = 1;			//׼������
                LED1_Toggle;
//				Key_Change(KeyReady,0);   //������ֵ��λ
                /* ���ݷ��� */
                udp_send_buf("ready");
			}
			break;
		case 0x2222:
			if(RxBuffer[7] == 0x01)
			{
//				flag_feedback = 1;		//���յ�����
                LED1_Toggle;
//                Key_Change(KeyAudio,0);   //������ֵ��λ 
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
 * @brief �л�������ҳ��
 * @param uint16_t �л���ָ��ҳ��
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


/* �������ڴ���������֮ǰʹ�� */
void USART_Printf(void)
{
    if(Mode_Switch==0)
    {
        printf("�����׼ģʽ\r\n");
        printf("��ƵƵ��Ϊ%dHZ\r\n",Hz_Audio);
        printf("��Ƶ����Ϊ%dDB\r\n",Db_Audio);
        switch(Ear_Audio)
        {
            case 0x01:
                printf("������Ϊ������\r\n");
                break;
            case 0x02:
                printf("������Ϊ������\r\n");
                break;
            default:
                printf("δѡ������\r\n");
                break;
        }
        printf("����ʱ��Ϊ%fs\r\n",time);
    }
    else if(Mode_Switch == 1)
    {
         printf("����У׼ģʽ\r\n");
    }
}

#endif
/*********************************************END OF FILE**********************/

 

 

 




