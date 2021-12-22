#ifndef __LED_H
#define	__LED_H

#include "stm32h7xx.h"

//引脚定义
/*******************************************************/
//LED1
#define LED1_PIN                  GPIO_PIN_6                 
#define LED1_GPIO_PORT            GPIOB                      
#define LED1_GPIO_CLK_ENABLE()    __GPIOB_CLK_ENABLE()

//LED2
#define LED2_PIN                  GPIO_PIN_7                
#define LED2_GPIO_PORT            GPIOB                      
#define LED2_GPIO_CLK_ENABLE()    __GPIOB_CLK_ENABLE()

//LED3
#define LED3_PIN                  GPIO_PIN_4                
#define LED3_GPIO_PORT            GPIOH                      
#define LED3_GPIO_CLK_ENABLE()    __GPIOH_CLK_ENABLE()

//LED4
#define LED4_PIN                  GPIO_PIN_8                 
#define LED4_GPIO_PORT            GPIOI                       
#define LED4_GPIO_CLK_ENABLE()    __GPIOI_CLK_ENABLE()
/************************************************************/


/** 控制LED灯亮灭的宏，
	* LED低电平亮，设置ON=0，OFF=1
	* 若LED高电平亮，把宏设置成ON=1 ，OFF=0 即可
	*/
#define ON  GPIO_PIN_RESET
#define OFF GPIO_PIN_SET

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_PIN,a?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LED1_Toggle HAL_GPIO_TogglePin(LED1_GPIO_PORT,LED1_PIN)


#define LED2(a)	HAL_GPIO_WritePin(LED2_GPIO_PORT,LED2_PIN,a?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LED2_Toggle HAL_GPIO_TogglePin(LED2_GPIO_PORT,LED2_PIN)

#define LED3(a)	HAL_GPIO_WritePin(LED2_GPIO_PORT,LED3_PIN,a?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LED3_Toggle HAL_GPIO_TogglePin(LED3_GPIO_PORT,LED3_PIN)

#define LED4(a)	HAL_GPIO_WritePin(LED4_GPIO_PORT,LED4_PIN,a?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LED4_Toggle HAL_GPIO_TogglePin(LED4_GPIO_PORT,LED4_PIN)

#define LED(a)	1<<(a-1)

void LED_GPIO_Config(void);
void LED_ONOFF(uint8_t flag_LED);
#endif /* __LED_H */
