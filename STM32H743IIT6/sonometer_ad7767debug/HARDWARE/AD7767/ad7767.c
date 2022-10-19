/**
*@author 	leeyoung7017
*@data		2021.12.11
*@Email 	leeyoung7017@163.com
*
*/
#include "ad7767.h"
#include "main.h"
#include "stdio.h"
#include "udp_demo.h"

void AD7767_Init(void)
{
	/* ad7767 gpio config */
	AD7767_GPIO_Init();

	/* AD7767 Reset */
//	AD7767_Reset();
	
	/* DRDY EXTI Configuration */
	AD7767_EXTI_Config();
	
	/* ad7767 spi Configuration */
	AD7767_SPI_Config();

	// printf("AD7767 initialization completed\r\n");
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
	
	//SCK==
	GPIO_InitStruct.Pin = SPI3_SCK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(SPI3_SCK_Port, &GPIO_InitStruct);
	
	//CS
	GPIO_InitStruct.Pin = SPI3_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SPI3_CS_Port, &GPIO_InitStruct);
	CS_DISABLE;//ѡͨ�źŴ��ڵ͵�ƽʱ����������ֻ��DRDY�½����ж϶�ȡ����

	//SYNC_PD
	GPIO_InitStruct.Pin = SYNC_PD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SYNC_PD_Port, &GPIO_InitStruct);
	SYNC_PD(1);//��ʼ״̬Ϊ�ߵ�ƽ
}

void AD7767_EXTI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	//DRDY PB14
	GPIO_InitStruct.Pin = DRDY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;//�½��ش���
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
 * @brief ʹ��/ʧ���ⲿ�ж�
 * 
 * @par GPIO_InitTypeDef *GPIO_InitStructure	�������ŵ��ⲿ�ж�
 * 
 * */
void HAL_EXTI_ENABLE(uint16_t GPIO_PIN_X)
{
	//�ⲿ�ж�ʹ��
//	EXTI->IMR1 |= GPIO_PIN_X;
}

void HAL_EXTI_DISABLE(uint16_t GPIO_PIN_X)
{
	//�ⲿ�ж�ʧ��
//	EXTI->IMR1 &= ~(GPIO_PIN_X);
}

/**
 * @brief AD7767 SPI ����
 * @param  None
 * @return None
 */
SPI_HandleTypeDef hspi3;
	
void AD7767_SPI_Config(void)
{
	/* APB1 ʱ��ʹ��  100MHz*/
	__HAL_RCC_SPI3_CLK_ENABLE();
	
	hspi3.Instance = SPI3;
	//����ģʽ
	hspi3.Init.Mode = SPI_MODE_MASTER;
	//ȫ˫��
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	//24λ����
	hspi3.Init.DataSize = SPI_DATASIZE_24BIT;
	//�����زɼ��ź�		ʱ�ӳ�ʼĬ��״̬Ϊ�ߵ�ƽ��
	hspi3.Init.CLKPolarity = SPI_POLARITY_High;
	//�����ض�ȡ
	hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
	//�������Ƭѡ
	hspi3.Init.NSS = SPI_NSS_SOFT;
	//�����ʣ�480MHz / 64 = 7.5M
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	/* �����ʵ�ϵͳʱ��Ϊ153.6M�����ⲿ���� / PLLM * PLLN /PLLQ �� 8/1*120/2=480M*/
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	//�ж�ʹ��
	hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
	//CRCУ��ʧ��
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi3.Init.CRCPolynomial = 10;
	/* ���� */
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
//		Error_Handler();
	}	
}




/**
 * @brief ��λAD7767
 * @param  None
 * @return None
 * @note Ŀǰ��ad7767��demo�����޷�ʹ��SYNC/PD����
 */
void AD7767_Reset(void)
{
	SYNC_PD(0);
	while(HAL_GPIO_ReadPin(DRDY_GPIO_Port,DRDY_Pin) == RESET);//�ȴ�DRDY������
	HAL_Delay(3);//3ms
	SYNC_PD(1);
}



/**
 *@brief SPI MOSI ��������һ���ֽ�	
 *@par uint8_t �����һ���ֽڵ�����
 *@return NULL
 */
void SPI_Tx_Byte(uint8_t Tx)
{
	hspi3.Instance->TXDR = Tx;
}

/**
 * @brief SPI MISO ��������һ���ֽ� 
 * @param {*}
 * @return {*}
 */
void SPI_Rx_Byte(uint8_t Rx)
{
	hspi3.Instance->RXDR = Rx;
}

uint32_t i = 0;
/**
 * @brief �ⲿ�жϴ�����
 * 			��Ҫ����SPI�������ݣ����DRDY���ŷ����ⲿ�½����жϣ���������SPI MISO��������
 * 			ͬʱ�����ڲ�������KEY�������ⲿ�жϴ�����
 */
uint32_t rx_from_ad7767[3000] = {0};
void EXTI15_10_IRQHandler(void)
{
	//AD7767 DRDY �����ⲿ�жϣ���������
	if(__HAL_GPIO_EXTI_GET_IT(DRDY_Pin) != RESET)
	{	
		static uint16_t times = 0;
		uint8_t   spi3_rxbuf[3];        /* spi2 receive buffer */
		uint32_t adval = 0;					/* spi2 receive data */
		/* SPI 8bit ���ݴ��� */
		if(HAL_SPI_TransmitReceive_IT(&hspi3,(uint8_t*)spi3_rxbuf,
                                      (uint8_t*)spi3_rxbuf,3) != HAL_OK);
		 /* waiting receive finshed */
        while (HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY);
		adval = (int32_t)(spi3_rxbuf[0]<<24 | spi3_rxbuf[1]<<16 | spi3_rxbuf[2]<<8);
		adval /= 256;
/*****************************���ڴ���****************************************/
		tcp_demo_sendbuf[times * 3] = spi3_rxbuf[0];
		tcp_demo_sendbuf[times * 3 + 1] = spi3_rxbuf[1];
		tcp_demo_sendbuf[times * 3 + 2] = spi3_rxbuf[2];
/****************************************************************************/		
/*****************************���ڴ���****************************************/
//		rx_from_ad7767[times++] = Convert_8to24(data);
//		printf("%d\r\n",rx_from_ad7767);
/****************************************************************************/	
		__HAL_GPIO_EXTI_CLEAR_IT(DRDY_Pin);
		if(times == SIZE_ACQUIRED)
		{
			CS_DISABLE;
			HAL_EXTI_DISABLE(DRDY_Pin);
/*****************************���ڴ���***********************************************/
			udp_demo_senddata(udp_demo_pcb);
/***********************************************************************************/
			times = 0;
		}
	}
	
	// �������� �ⲿ�ж�
//	if(__HAL_GPIO_EXTI_GET_IT(KEY_CTR_Pin) != RESET)
//	{
//		static uint8_t flag_led = 1;
//		HAL_Delay(10);
//	/******�����жϲ���********/
//		if(flag_led)
//			LED0(ON);
//		else
//			LED0(ON);
//	/*************************/	
//		__HAL_GPIO_EXTI_CLEAR_IT(KEY_CTR_Pin);
//	}
}



/**
 * @brief ��8λ���ݵ�����ת��Ϊ24λ����
 * @param pdata ��Ҫ��ת����8λ���ݵ�����
 * @return ����24�ֽڵ�����
 */
uint32_t Convert_8to24(uint8_t *pdata)
{
	uint32_t rx = 0;
	rx = (pdata[2]<<(8*2)) + (pdata[1]<<(8*1)) + pdata[0];
	return rx;
}

