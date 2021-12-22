#include "bsp_i2s.h"
#include "bsp_i2s_data.h"


I2S_HandleTypeDef I2S_HandleStructure = {0};

/*I2S_STANDARD_PHILIPS/I2S_DATAFORMAT_24B/I2S_AUDIOFREQ_44K*/
void I2S2_Init(void)
{
	

	 __HAL_RCC_SPI2_CLK_ENABLE();
	I2S_HandleStructure.Instance = SPI2;
	I2S_HandleStructure.Init.Mode = I2S_MODE_MASTER_TX;
	I2S_HandleStructure.Init.Standard = I2S_STANDARD_PHILIPS;
	I2S_HandleStructure.Init.DataFormat = I2S_DATAFORMAT_24B;
	I2S_HandleStructure.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
	I2S_HandleStructure.Init.AudioFreq = I2S_AUDIOFREQ_44K;
	I2S_HandleStructure.Init.CPOL = I2S_CPOL_LOW;
	I2S_HandleStructure.Init.FirstBit = I2S_FIRSTBIT_MSB;
	I2S_HandleStructure.Init.WSInversion = I2S_WS_INVERSION_DISABLE;
	I2S_HandleStructure.Init.Data24BitAlignment = I2S_DATA_24BIT_ALIGNMENT_LEFT;
	I2S_HandleStructure.Init.MasterKeepIOState = I2S_MASTER_KEEP_IO_STATE_DISABLE;
	if (HAL_I2S_Init(&I2S_HandleStructure) != HAL_OK)
	{
		Error_Handler();
	}
} 

/**
* @brief I2S MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2s: I2S handle pointer
* @retval None
    PC3_C     ------> I2S2_SDO
    PB10     ------> I2S2_CK
    PC6     ------> I2S2_MCK
    PA11     ------> I2S2_WS
*/
void I2S2_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
 
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
   
    GPIO_InitStruct.Pin = I2S2_MCK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(I2S2_MCK_GPIO_Port, &GPIO_InitStruct);
	
	  GPIO_InitStruct.Pin = I2S2_DATA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(I2S2_DATA_GPIO_Port, &GPIO_InitStruct);
    //位时钟
    GPIO_InitStruct.Pin = I2S2_BCK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(I2S2_BCK_GPIO_Port, &GPIO_InitStruct);

  //WS，左右声道切换
    GPIO_InitStruct.Pin = I2S2_LRCK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;//下拉电阻，默认左声道传输
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(I2S2_LRCK_GPIO_Port, &GPIO_InitStruct);
	
}
void I2S_DMA_Init(void)
{
    /* I2S2 DMA Init */
	DMA_HandleTypeDef hdma_spi2_tx;
    /* SPI2_TX Init */
    hdma_spi2_tx.Instance = DMA1_Stream0;
    hdma_spi2_tx.Init.Request = DMA_REQUEST_SPI2_TX;
    hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.Mode = DMA_CIRCULAR;
    hdma_spi2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_spi2_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_spi2_tx.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_spi2_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;
    if (HAL_DMA_Init(&hdma_spi2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(&I2S_HandleStructure,hdmatx,hdma_spi2_tx);

  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
}

 

/**
  * Enable DMA controller clock
  */
void I2S_DMA_ENABLE(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

}

/**
 * @brief I2S & GPIO Configuration
 * 
 * @param None
 * 
 * @return None
 */
void PCM1794_Init(void)
{
	/*GPIO Configuration*/
	I2S2_GPIO_Init();
	
	/*I2S DMA Configuration*/
//	I2S_DMA_Init(); 

	
	/*I2S Initialization*/
	I2S2_Init();
	
}



/**
 *@brief 播放音频 
 * 
 *@par Hz   正弦信号的频率
 *
 *@par Db   正弦信号的幅值 
 * 
 */
uint32_t data_Hz[8824] = {0}; //存储相应频率的音频数据

void Audio_Play(uint32_t Hz,uint32_t Db)
{
    /* 间隔采样 数据获取 */
    int n = 0;//在250Hz存在错误
    uint32_t index = 0;
		uint16_t data_Hz_16[8824] = {0};//(uint16_t *)malloc(44000/Hz_Audio*4); //存储相应频率的音频数据
    n = Hz / 20;

     
		memset(data_Hz,0,8824);
    //清空播放数组  
    memset(data_Hz_16,0,44000/Hz_Audio*4); 
    //获取相应频率的数据
    for(int i = 0;i<sizeof(data_audio_20Hz)/sizeof(uint32_t);i++)
    {
        if(i % n == 0)
        {
          data_Hz[index*4] = data_audio_20Hz[i];
          index++;
        }
    }

  /* 将音频数据转化为16位 默认单声道为左声道 */
  Convert24To16(data_Hz,44000/Hz_Audio*4);
		
  /* 切换左右声道 */
  Channel_Switch(Ear_Audio,44000/Hz_Audio*4);
		
		/*将32位存储转化为16位存储*/
  for(n = 0;n<44000/Hz_Audio*4;n++)
		{
			data_Hz_16[n] = data_Hz[n];
		}
  /*********************************************************************************/
  //音频数据传输，传输1s的数据，即为传递Hz个24位数据
//	for(n = 0;n<Hz_Audio;n++)
		while(1)
	{
		HAL_I2S_Transmit(&I2S_HandleStructure,data_Hz_16,44000/Hz_Audio*2,HAL_MAX_DELAY);
//		HAL_I2S_Transmit(&I2S_HandleStructure,data1_16,8,HAL_MAX_DELAY);
	}
  
  /*********************************************************************************/
}

/**
 *@brief 用于左右声道的切换 
 *@par channel 用于判断左右声道使能
 */
void Channel_Switch(uint8_t channel,int length)
{
    int i = 0;
    if(Ear_Audio & 0x01)//左声道
    {
      return;
    }
    else if(Ear_Audio & 0x02)//右声道
    {
        for(i = 0;i<length;i=i+4)//切换右声道
      {
        data_Hz[i+2] = data_Hz[i];
        data_Hz[i+3] = data_Hz[i+1];
        data_Hz[i+1] = 0x00;
        data_Hz[i] = 0x00;
      }
      return;
    }
    return;
}

