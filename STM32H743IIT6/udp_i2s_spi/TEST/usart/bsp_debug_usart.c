/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author  fire
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   使用串口1，重定向c库printf函数到usart端口，中断接收模式
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F746 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_debug_usart.h"
#include <string.h>

UART_HandleTypeDef huart1;
USART_HandleTypeDef husart1;
//数据接收
uint8_t RxBuffer[9] = {0};
extern uint8_t ucTemp;  
 /**
  * @brief  DEBUG_USART GPIO 配置,工作模式配置。115200 8-N-1
  * @param  无
  * @retval 无
  */  
void DEBUG_USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
        
    /* 使能串口1时钟 GPIO时钟*/
    __HAL_RCC_USART1_CLK_ENABLE();
	DEBUG_USART_RX_GPIO_CLK_ENABLE();
	DEBUG_USART_TX_GPIO_CLK_ENABLE();
    
    /* 配置串口1时钟源*/
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	PeriphClkInitStruct.Usart16ClockSelection = RCC_USART1CLKSOURCE_D2PCLK2;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
    

	/* 配置Tx引脚为复用功能  */
	GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN|DEBUG_USART_RX_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

		
    /* 配置串DEBUG_USART 模式 */
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
	/* 使能串口中断 */
	// __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
	HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ);				//使能USART1中断通道
	HAL_NVIC_SetPriority(DEBUG_USART_IRQ,3,3);			//抢占优先级3，子优先级3
	__HAL_USART_ENABLE_IT(&huart1,USART_IT_RXNE);
}

void USART_Transmit(uint8_t data)
{
	huart1.Instance->TDR = data;
}

///重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
//	huart1.Instance->TDR = ch;
//	while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TXE)==RESET);
	return ch;
}

///重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
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
		if(__HAL_UART_GET_IT_SOURCE(&huart1,UART_IT_RXNE) != RESET)
		{
			// RxBuffer[0] = huart1.Instance->RDR;
				if(huart1.Instance->RDR == 0x5A)	i = 0;
				RxBuffer[i] = huart1.Instance->RDR;
				i++;
				if(i==9) i = 0;
			__HAL_UART_CLEAR_IT(&huart1,UART_IT_RXNE);
		}
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);
	}
}

/**
 * @brief 解析串口指令实现相应功能 
 * @param NULL
 * @return NULL
 */
void USART1_Opera(void)
{
	int16_t Rx_addr = ((RxBuffer[4] << 8) & 0xff00) + (RxBuffer[5] & 0xff);
	switch(Rx_addr)
	{
		case 0x1111:
			if(RxBuffer[8] == 0x01)
			{
				flag_ready = 1;			//准备就绪
				Page_Switch(0x0002);	//切换到第2页面
			}
			break;
		case 0x2222:
			if(RxBuffer[8] == 0x01)
			{
				flag_feedback = 1;		//接收到反馈
			}
			break;
		default:
			break;
	}

}

/**
 * @brief 切换串口屏页面
 * @param uint16_t 切换到指定页面
 * @return NULL
 */
void Page_Switch(uint16_t page)
{
	uint8_t PageSwitch_array[8] = {0x5A, 0xA5, 0x05, 0x80, 0x03, 0x02, 0,0};
	PageSwitch_array[6] = (page >> 8) & 0xff;
	PageSwitch_array[7] = page & 0x00ff; 
	for(char i=0;i<8;i++)
	{
		printf("%x",PageSwitch_array[i]);
	}
	memset(RxBuffer,'\0',sizeof(RxBuffer));
}
/*********************************************END OF FILE**********************/
