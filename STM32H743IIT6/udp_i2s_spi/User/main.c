/**
  ******************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   ��V1.2.0�汾�⽨�Ĺ���ģ��
  ******************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32H743������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
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

uint32_t Hz_Audio = 0;      //��ƵƵ��Ҫ��
uint32_t Db_Audio = 0;      //��Ƶ����Ҫ��
uint8_t Ear_Audio = 0;      //��Ƶ������Ҫ��    1��left     2��right
uint8_t Mode_Switch = 2;    //��׼ģʽ��У׼ģʽ���л���0����׼ģʽ     1��У׼ģʽ
uint8_t flag_ready = 0;     //׼����־λ
uint8_t flag_feedback = 0;  //�������ձ�־λ

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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* ������� */
	H7_encrypted();
  /* ��ETHʹ�õ��ڴ濪������*/
	MPU_Config(); 
  /* Enable I-Cache */
  SCB_EnableICache();
  /* Enable D-Cache */
  SCB_EnableDCache();  
  //��Cache����write-through��ʽ
  SCB->CACR|=1<<2;
	HAL_Init();
	
  /* ����ϵͳʱ��Ϊ480MHz */
  SystemClock_Config();	
  /* ��ʼ��RGB�ʵ� */
//  LED_GPIO_Config();
	
	/* ��ʼ��USART1 ����ģʽΪ 115200 8-N-1 */
  DEBUG_USART_Config();
	// printf("STM32H743IIT6\n");
  /* �����ⲿ�жϳ�ʼ�� */
//  KEY_Init();

	/* ad7767 ��ʼ�� */
	AD7767_Init();

	/* ��ʼ��udp����ͨ�� */
	udp_demo_Init();
	
	/* pcm1794��ʼ�� */
	PCM1794_Init();

	/* ��ʱ����ʼ�� */
	TIMx_Init(1000000-1,120-1);
	
	while (1)
	{  
		
		/************************* ���ڲ��� **************************/
		//      USART_Transmit(data);
		//      HAL_Delay(1);
		/************************* ���ڲ��� **************************/

		/* ����̫���������ж�ȡ���ݰ�������LwIP���� */
		udp_lwip_check();				
	}	
	
}

void H7_encrypted(void)
{
	int i;	
	char sys_id[12]={0}; //�洢stm32оƬ��ID�ŵ�����
	for(i=0;i<12;i++)
	{
			sys_id[i]=*(uint8_t*)(0x1FF0F420+i); //��ȡSTM32оƬ��ΨһID
			if(sys_id[i] !=ID_H7[i])
			{
				while(1);
			}
	}
}


/**
 * @brief  ����̫���������ж�ȡ���ݰ�������LwIP���д���
 * @param  flag ��Ҫ�õ��ⲿ��ȫ�ֱ������б�־λ������������������
 * @return None
 */
void udp_lwip_check(void)
{
  if(flag)
  {
    flag = 0;
    //�����������պ���
    ethernetif_input(&gnetif);
  }
  /* ���� LwIP ��ʱ */
  sys_check_timeouts();
}

/**
  *@brief	UDP Configuration
  *@param None
  *@return None
*/
void udp_demo_Init(void)
{
	/* ��ʼ��LwIPЭ��ջ*/
  lwip_init();
	
  /* ����ӿ����� */
  Netif_Config();
    
  User_notification(&gnetif);
	
	/* udpͨ�ŵĳ�ʼ�� */
	UDP_Init();
  //IP��ַ�Ͷ˿ڿ���main.h�ļ��޸�
  // printf("����IP�Ͷ˿�: %d.%d.%d.%d\r\n",IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
}



/**
  * @brief  System Clock ����
  *         system Clock ��������: 
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
  
  /*ʹ�ܹ������ø��� */
  MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

  /* ��������ʱ��Ƶ�ʵ������ϵͳƵ��ʱ����ѹ���ڿ����Ż����ģ�
		 ����ϵͳƵ�ʵĵ�ѹ����ֵ�ĸ��¿��Բο���Ʒ�����ֲᡣ  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
 
  /* ����HSE������ʹ��HSE��ΪԴ����PLL */
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
 
	/* ѡ��PLL��Ϊϵͳʱ��Դ����������ʱ�ӷ�Ƶ��������ʱ�ӷ��� */
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
  * @brief  ����MPU���� 
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
