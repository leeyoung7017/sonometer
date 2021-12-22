/**
  ******************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   led应用函数接口
  ******************************************************************
  * @attention
  *
  * 实验平台:野火 STM32H743开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************
  */  
  
#include "./bsp_led.h"   
#include "./delay/core_delay.h" 

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef  GPIO_InitStruct;

	/*开启LED相关的GPIO外设时钟*/
	LED1_GPIO_CLK_ENABLE();
	LED2_GPIO_CLK_ENABLE();
	LED3_GPIO_CLK_ENABLE();
//	LED4_GPIO_CLK_ENABLE();

	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStruct.Pin = LED1_PIN;	
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;  
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; 
	HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);	

	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStruct.Pin = LED2_PIN;	
	HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);	

	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStruct.Pin = LED3_PIN;	
	HAL_GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStruct);	

	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStruct.Pin = LED4_PIN;	
	HAL_GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStruct);	

	/*关闭LED灯*/
	LED1(0);
	LED2(0);
	LED3(0);
	LED4(0);

		
}

/**
*@brief LED闪烁,500ms
*@para 	flag_LED
*				bit0: LED1
*				bit1: LED2
*				bit2: LED3
*				bit3: LED4
*
*/
void LED_ONOFF(uint8_t flag_LED)
{
	if(flag_LED & 0x01)	LED1(0);
	if(flag_LED & 0x02) LED2(0);
	if(flag_LED & 0x04) LED3(0);
	if(flag_LED & 0x08) LED4(0);
	
	HAL_Delay(100);
	
	if(flag_LED & 0x01)	LED1(1);
	if(flag_LED & 0x02) LED2(1);
	if(flag_LED & 0x04) LED3(1);
	if(flag_LED & 0x08) LED4(1);
}
/*********************************************END OF FILE**********************/

