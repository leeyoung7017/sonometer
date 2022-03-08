/**
  ******************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   用V1.2.0版本库建的工程模板
  ******************************************************************
  * @attention
  *
  * 实验平台:野火  STM32H743开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************
  */  
#include "stm32h7xx.h"
#include "stdio.h"
#include "main.h"
#include "bsp_led.h"
#include "bsp_i2s.h"
#include "bsp_debug_usart.h"
#include "lwip/init.h"
#include "timer.h"
#include "udp_demo.h"
#include "bsp_key.h"
#include "app_ethernet.h"
#include "ethernetif.h"
#include "lwip/timeouts.h"
#include "./delay/core_delay.h"  
#include "ad7767.h"

uint32_t Hz_Audio = 0;      //音频频率要求
uint32_t Db_Audio = 0;      //音频幅度要求
uint8_t Ear_Audio = 0;      //音频单声道要求    1：left     2：right
uint8_t Mode_Switch = 2;    //标准模式与校准模式的切换；0：标准模式     1：校准模式
uint8_t flag_ready = 0;     //准备标志位
uint8_t flag_feedback = 0;  //反馈接收标志位
double  time = 0;           //音频播放时间
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}



char ID_H7[12] = {
	0x01,0xF0,0x82,0xFF,0x38,0x68,0x40,0xF0,0x80,0x70,0x38,0x60
};
int flag = 0;
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* 代码加密 */
	H7_encrypted();
  /* 对ETH使用的内存开启保护*/
	MPU_Config(); 
  /* Enable I-Cache */
  SCB_EnableICache();
  /* Enable D-Cache */
  SCB_EnableDCache();  
  //将Cache设置write-through方式
  SCB->CACR|=1<<2;
	HAL_Init();
	
  /* 配置系统时钟为480MHz */
  SystemClock_Config();	
  /* 初始化RGB彩灯 */
//  LED_GPIO_Config();
	
	/* 初始化USART1 配置模式为 115200 8-N-1 */
  DEBUG_USART_Config();
	// printf("STM32H743IIT6\n");
  /* 按键外部中断初始化 */
//  KEY_Init();

	/* ad7767 初始化 */
	AD7767_Init();

	/* 初始化udp网口通信 */
	udp_demo_Init();
	
	/* pcm1794初始化 */
	PCM1794_Init();

	/* 定时器初始化 */
	TIMx_Init(1000000-1,120-1);
	
	while (1)
	{  
		
		/************************* 串口测试 **************************/
		//      USART_Transmit(data);
		//      HAL_Delay(1);
		/************************* 串口测试 **************************/

		/* 从以太网缓冲区中读取数据包，交给LwIP处理 */
		udp_lwip_check();				
	}	
	
}

void H7_encrypted(void)
{
	int i;	
	char sys_id[12]={0}; //存储stm32芯片的ID号的数组
	for(i=0;i<12;i++)
	{
			sys_id[i]=*(uint8_t*)(0x1FF0F420+i); //读取STM32芯片的唯一ID
			if(sys_id[i] !=ID_H7[i])
			{
				while(1);
			}
	}
}


/**
 * @brief  从以太网缓冲区中读取数据包，交给LwIP进行处理
 * @param  flag 需要用到外部的全局变量进行标志位，进行网卡接收数据
 * @return None
 */
void udp_lwip_check(void)
{
  if(flag)
  {
    flag = 0;
    //调用网卡接收函数
    ethernetif_input(&gnetif);
  }
  /* 处理 LwIP 超时 */
  sys_check_timeouts();
}

/**
  *@brief	UDP Configuration
  *@param None
  *@return None
*/
void udp_demo_Init(void)
{
	/* 初始化LwIP协议栈*/
  lwip_init();
	
  /* 网络接口配置 */
  Netif_Config();
    
  User_notification(&gnetif);
	
	/* udp通信的初始化 */
	UDP_Init();
  //IP地址和端口可在main.h文件修改
  // printf("本地IP和端口: %d.%d.%d.%d\r\n",IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
}



/**
  * @brief  System Clock 配置
  *         system Clock 配置如下: 
	*            System Clock source  = PLL (HSE)
	*            SYSCLK(Hz)           = 480000000 (CPU Clock)
	*            HCLK(Hz)             = 240000000 (AXI and AHBs Clock)
	*            AHB Prescaler        = 2
	*            D1 APB3 Prescaler    = 2 (APB3 Clock  120MHz)
	*            D2 APB1 Prescaler    = 2 (APB1 Clock  120MHz)
	*            D2 APB2 Prescaler    = 2 (APB2 Clock  120MHz)
	*            D3 APB4 Prescaler    = 2 (APB4 Clock  120MHz)
	*            HSE Frequency(Hz)    = 8000000
	*            PLL_M                = 1
	*            PLL_N                = 120
	*            PLL_P                = 2
	*            PLL_Q                = 2
	*            PLL_R                = 2
	*            VDD(V)               = 3.3
	*            Flash Latency(WS)    = 4
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  HAL_StatusTypeDef ret = HAL_OK;
  
  /*使能供电配置更新 */
  MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

  /* 当器件的时钟频率低于最大系统频率时，电压调节可以优化功耗，
		 关于系统频率的电压调节值的更新可以参考产品数据手册。  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
 
  /* 启用HSE振荡器并使用HSE作为源激活PLL */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  /* HSE / PLLM * PLLN * PLLP = PLLCLK(SYSCLK) */
  /* HSE / PLLM * PLLQ =  PLL1Q(SPI2)*/
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
 
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
 
	/* 选择PLL作为系统时钟源并配置总线时钟分频器，外设时钟分配 */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK  | \
																 RCC_CLOCKTYPE_HCLK    | \
																 RCC_CLOCKTYPE_D1PCLK1 | \
																 RCC_CLOCKTYPE_PCLK1   | \
                                 RCC_CLOCKTYPE_PCLK2   | \
																 RCC_CLOCKTYPE_D3PCLK1);
  /* SYSCLK /  SYSCLKDivider = CPU Clock*/
  /* SYSCLK /  SYSCLKDivider / AHBCLKDivider / APB1CLKDivider = APB1_Peripheral_Clock*/
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;  
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2; 
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2; 
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2; 
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
	 PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI2;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  配置MPU外设 
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;
  
  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as Device not cacheable 
     for ETH DMA descriptors */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x30040000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256B;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  
  /* Configure the MPU attributes as Cacheable write through 
     for LwIP RAM heap which contains the Tx buffers */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x30044000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_16KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  
  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/****************************END OF FILE***************************/
