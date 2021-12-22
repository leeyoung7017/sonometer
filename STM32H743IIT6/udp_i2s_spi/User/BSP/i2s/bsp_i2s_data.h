#ifndef __BSP_I2S_DATA_H__
#define __BSP_I2S_DATA_H__

#include "stm32h7xx_hal.h"
#include "main.h"

extern uint32_t data_audio_20Hz[2206];

void Convert24To16(uint32_t* data_array,int length);

#endif

