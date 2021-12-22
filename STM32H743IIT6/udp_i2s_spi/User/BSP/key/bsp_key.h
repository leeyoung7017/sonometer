#ifndef __KEY_H__
#define __KEY_H__

#include "stm32h7xx_hal.h"
#include "main.h"
#include "bsp_led.h"
#include "./delay/core_delay.h"   

#define KEY_CTR_GPIO_CLK_ENABLE()   	__GPIOI_CLK_ENABLE()
#define KEY_CTR_GPIO_PORT				GPIOI
#define KEY_CTR_Pin						GPIO_PIN_11

void KEY_Init(void);


#endif	//bsp_key.h

