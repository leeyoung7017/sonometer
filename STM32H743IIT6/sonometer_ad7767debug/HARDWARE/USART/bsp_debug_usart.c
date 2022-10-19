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
//数据接收
uint8_t RxBuffer[10] = {0};
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
    
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	PeriphClkInitStruct.Usart16ClockSelection = RCC_USART1CLKSOURCE_D2PCLK2;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
//		Error_Handler();
	}
        
    /* 使能串口1时钟 GPIO时钟*/
    __HAL_RCC_USART1_CLK_ENABLE();
	DEBUG_USART_RX_GPIO_CLK_ENABLE();
	DEBUG_USART_TX_GPIO_CLK_ENABLE();
        

	/* 配置Tx引脚为复用功能  */
	GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN|DEBUG_USART_RX_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

		
    /* 配置串DEBUG_USART 模式 */
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
	/* 使能串口中断 */
	// __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
	HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ);				//使能USART1中断通道
	HAL_NVIC_SetPriority(DEBUG_USART_IRQ,0,0);			//抢占优先级3，子优先级3
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
}

void USART_Transmit(uint8_t data)
{
	huart1.Instance->TDR = data;
}

///重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
//	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
	huart1.Instance->TDR = ch;
	while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TXE)==RESET);
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
//                LED1(1);
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
/*********************************************END OF FILE**********************/
