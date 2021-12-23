/**
*@author leeyoung7017
*@created	2021.12.11
*@completed		
*
*/
#include "ad7767.h"
#include "main.h"

void AD7767_Init(void)
{
	/* ad7767 gpio config */
	AD7767_GPIO_Init();

	/* AD7767 Reset */
	AD7767_Reset();
	
	/* DRDY EXTI Configuration */
	AD7767_EXTI_Config();
	
	/* ad7767 spi Configuration */
	AD7767_SPI_Config();
	

}


void AD7767_GPIO_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//MOSI
	GPIO_InitStruct.Pin = SPI3_MOSI_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_SPI3;
	HAL_GPIO_Init(SPI3_MOSI_Port, &GPIO_InitStruct);
	
	//MISO
	GPIO_InitStruct.Pin = SPI3_MISO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(SPI3_MISO_Port, &GPIO_InitStruct);
	
	//SCK
	GPIO_InitStruct.Pin = SPI3_SCK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(SPI3_SCK_Port, &GPIO_InitStruct);
	
	//CS
	GPIO_InitStruct.Pin = SPI3_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SPI3_CS_Port, &GPIO_InitStruct);
	CS(0);//选通信号处于低电平时，这样可以只看DRDY下降沿判断读取数据

	//SYNC_PD
	GPIO_InitStruct.Pin = SYNC_PD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SYNC_PD_Port, &GPIO_InitStruct);
	SYNC_PD(1);//初始状态为高点平
}

void AD7767_EXTI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	//DRDY PB14
	GPIO_InitStruct.Pin = DRDY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;//下降沿触发
	GPIO_InitStruct.Pull = GPIO_NOPULL;//GPIO_PULLUP
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DRDY_GPIO_Port, &GPIO_InitStruct);
	
	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(DRDY_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DRDY_EXTI_IRQn);

//	HAL_EXTI_DISABLE(DRDY_Pin);
/*********************TEST USED*****************************/
	HAL_EXTI_ENABLE(DRDY_Pin);
/***********************************************************/
}

/**
 * @brief 使能/失能外部中断
 * 
 * @par GPIO_InitTypeDef *GPIO_InitStructure	所对引脚的外部中断
 * 
 * */
void HAL_EXTI_ENABLE(uint16_t GPIO_PIN_X)
{
	//外部中断使能
	EXTI->IMR1 |= GPIO_PIN_X;
}

void HAL_EXTI_DISABLE(uint16_t GPIO_PIN_X)
{
	//外部中断失能
	EXTI->IMR1 &= ~(GPIO_PIN_X);
}
SPI_HandleTypeDef hspi3;	
void AD7767_SPI_Config(void)
{
//	SPI_HandleTypeDef hspi3  = {0};
	
	/* APB1 时钟使能  100MHz*/
	__HAL_RCC_SPI3_CLK_ENABLE();
	
	hspi3.Instance = SPI3;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.DataSize = SPI_DATASIZE_24BIT;

	//上升沿采集信号		时钟初始默认状态为低电平，
	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;

	//软件出发片选
	hspi3.Init.NSS = SPI_NSS_SOFT;
	//波特率
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	//中断使能
	hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
	//CRC校验失能
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi3.Init.CRCPolynomial = 7;

	hspi3.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	hspi3.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi3.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi3.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi3.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi3.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_02CYCLE;
	hspi3.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_02CYCLE;
	hspi3.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_ENABLE;
	hspi3.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi3.Init.IOSwap = SPI_IO_SWAP_DISABLE;

	if (HAL_SPI_Init(&hspi3) != HAL_OK)
	{
		Error_Handler();
	}	
}




/**
 * 
 * @brief 复位AD7767
 */
void AD7767_Reset(void)
{
	SYNC_PD(0);
	while(HAL_GPIO_ReadPin(DRDY_GPIO_Port,DRDY_Pin) == RESET);//等待DRDY上升沿
	HAL_Delay_us(3);
	SYNC_PD(1);
	//建立时间
	// HAL_Delay_us(2370);
	while(HAL_GPIO_ReadPin(DRDY_GPIO_Port,DRDY_Pin) != RESET);//等待DRDY下降沿
}

/**
 *@brief SPI MOSI 传输数据一个字节	
 * 
 *@par uint8_t 传输的一个字节的数据
 *
 *@return NULL
 */
void SPI_Tx_Byte(uint8_t Tx)
{
	HAL_SPI_Transmit(&hspi3,&Tx,1,10);
}


uint32_t i = 0;
/**
 * @brief 外部中断处理函数
 * 			主要处理SPI接收数据，如果DRDY引脚发生外部下降沿中断，开启数据SPI MISO接收数据
 * 
 */
uint32_t rx_from_ad7767[3000] = {0};
void EXTI15_10_IRQHandler(void)
{
	//AD7767 DRDY 引脚外部中断，接收数据
	if(__HAL_GPIO_EXTI_GET_IT(DRDY_Pin) != RESET)
	{	
		
		uint8_t data[3] = {0};//SPI 获取三个字节数据
		HAL_SPI_Receive(&hspi3,data,3,10);
		__HAL_GPIO_EXTI_CLEAR_IT(DRDY_EXTI_IRQn);
		rx_from_ad7767[i] = Convert_8to24(data);
		i++;
		if(i == 100) i=0;

	}
	
	// 按键反馈 外部中断
	if(__HAL_GPIO_EXTI_GET_IT(KEY_CTR_Pin) != RESET)
	{
		static uint8_t flag_led = 1;
		HAL_Delay(10);
	/******按键中断操作********/
		if(flag_led)
			LED2(1);
		else
			LED2(0);
	/*************************/
		
		__HAL_GPIO_EXTI_CLEAR_IT(KEY_CTR_Pin);
	}
}



/**
 * 
 * @brief 将8位数据的数据转化为24位数据
 * 
 */
uint32_t Convert_8to24(uint8_t *pdata)
{
	uint32_t rx = 0;
	rx = (pdata[0]<<(8*2)) + (pdata[1]<<(8*1)) + pdata[2];
	return rx;
}

