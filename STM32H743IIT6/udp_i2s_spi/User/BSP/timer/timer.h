#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32h7xx_hal.h"
#include "main.h"
#include "bsp_led.h"
#include "bsp_i2s.h"
#include "udp_demo.h"
#include "lwip/init.h"
#include "timer.h"
#include "udp_demo.h"
#include "bsp_key.h"
#include "app_ethernet.h"
#include "ethernetif.h"
#include "lwip/timeouts.h"
#include "./delay/core_delay.h"  

#define __TIMx_CLK_ENABLE()	__TIM2_CLK_ENABLE()
#define TIMx TIM2


extern TIM_HandleTypeDef htimx;
void TIMx_Init(uint32_t psc,uint32_t per);


#endif	//timer.h

