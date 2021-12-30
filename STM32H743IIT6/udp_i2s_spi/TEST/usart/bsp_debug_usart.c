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

UART_HandleTypeDef huart1;
USART_HandleTypeDef husart1;
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
        
    /* ʹ�ܴ���1ʱ�� GPIOʱ��*/
    __HAL_RCC_USART1_CLK_ENABLE();
	DEBUG_USART_RX_GPIO_CLK_ENABLE();
	DEBUG_USART_TX_GPIO_CLK_ENABLE();
    
    /* ���ô���1ʱ��Դ*/
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	PeriphClkInitStruct.Usart16ClockSelection = RCC_USART1CLKSOURCE_D2PCLK2;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
    

    /* ����Tx����Ϊ���ù���  */
    GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN|DEBUG_USART_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

		
    /* ���ô�DEBUG_USART ģʽ */
	  huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT;
	huart1.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
	huart1.AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
}

void USART_Transmit(uint8_t data)
{
		huart1.Instance->TDR = data;
}
///�ض���c�⺯��printf������DEBUG_USART���ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
//	/* ����һ���ֽ����ݵ�����DEBUG_USART */
//		HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
//		while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET);
//		while (__HAL_USART_GET_FLAG(&husart1, USART_FLAG_TC) == RESET);
//		HAL_USART_Transmit(&husart1, (uint8_t *)&ch, 1, 0xFFFF); 	
		return ch;
	
//		while((USART1->ISR&0X40)==0);//ѭ������,ֱ���������   
//		USART1->TDR=(uint8_t)ch;      
//		return ch;
}

///�ض���c�⺯��scanf������DEBUG_USART����д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		
	int ch;
	HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}


void USART1_IRQHandler(void)
{
//	uint8_t data;
	if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)!=RESET)
	{
		if(__HAL_UART_GET_IT(&huart1,UART_IT_RXNE)!=RESET)
		{
//				data = huart1.Instance->RDR;
				
		}
		__HAL_UART_CLEAR_IT(&huart1,UART_IT_RXNE);
	}
	
	__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);
}

/*********************************************END OF FILE**********************/
