/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author  fire
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   ʹ�ô���1���ض���c��printf������usart�˿ڣ��жϽ���ģʽ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F746 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_debug_usart.h"
#include <string.h>

UART_HandleTypeDef huart1;
//���ݽ���
uint8_t RxBuffer[10] = {0};
extern uint8_t ucTemp;  
 /**
  * @brief  DEBUG_USART GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */  
void DEBUG_USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	PeriphClkInitStruct.Usart16ClockSelection = RCC_USART1CLKSOURCE_D2PCLK2;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
//		Error_Handler();
	}
        
    /* ʹ�ܴ���1ʱ�� GPIOʱ��*/
    __HAL_RCC_USART1_CLK_ENABLE();
	DEBUG_USART_RX_GPIO_CLK_ENABLE();
	DEBUG_USART_TX_GPIO_CLK_ENABLE();
        

	/* ����Tx����Ϊ���ù���  */
	GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN|DEBUG_USART_RX_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

		
    /* ���ô�DEBUG_USART ģʽ */
	huart1.Instance = DEBUG_USART;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
//	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT;
	huart1.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
	huart1.AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
//		Error_Handler();
	}
    
//	if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
//	{
//		Error_Handler();
//	}
	/* ʹ�ܴ����ж� */
	// __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
	HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ);				//ʹ��USART1�ж�ͨ��
	HAL_NVIC_SetPriority(DEBUG_USART_IRQ,0,0);			//��ռ���ȼ�3�������ȼ�3
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
}

void USART_Transmit(uint8_t data)
{
	huart1.Instance->TDR = data;
}

///�ض���c�⺯��printf������DEBUG_USART���ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
//	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
	huart1.Instance->TDR = ch;
	while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TXE)==RESET);
	return ch;
}

///�ض���c�⺯��scanf������DEBUG_USART����д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{	
	int ch;
	ch = huart1.Instance->RDR;
	return (ch);
}

void USART1_IRQHandler(void)
{
	static uint8_t i = 0;
	if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE) != RESET)
	{
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);
		if(__HAL_UART_GET_IT_SOURCE(&huart1,UART_IT_RXNE) != RESET)
		{
            
              __HAL_UART_CLEAR_IT(&huart1,UART_IT_RXNE);
			// RxBuffer[0] = huart1.Instance->RDR;
//				if(huart1.Instance->RDR == 0x5A)	i = 0;
				RxBuffer[i] = huart1.Instance->RDR;
				i++;
				if(i==10)
                {
                    LED0_Toggle;
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
//                LED1(1);
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
    
//        HAL_UART_Transmit(&huart1,PageSwitch_array,6,1000);
	
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
/*********************************************END OF FILE**********************/
