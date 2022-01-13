/*
 * @Descripttion: 
 * @version: 
 * @Author: leeyoung7017
 * @Date: 2021-12-11 16:13:00
 * @Email: leeyoung7017@163.com
 */
#include "bsp_key.h"
#include "ad7767.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	KEY_CTR_GPIO_CLK_ENABLE();
	
	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStruct.Pin = KEY_CTR_Pin;	

	/*设置引脚的输出类型为外部中断下降沿*/
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;  

	/*设置引脚为上拉模式*/
	GPIO_InitStruct.Pull  = GPIO_PULLUP;

	/*设置引脚速率为高速 */   
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; 

	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	HAL_GPIO_Init(KEY_CTR_GPIO_PORT, &GPIO_InitStruct);	
	
	//中断线0
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,0,0);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);             //使能中断线0

	// HAL_EXTI_DISABLE(GPIO_PIN_11);
//	printf("KEY initialization completed\r\n");
}




