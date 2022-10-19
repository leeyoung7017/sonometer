#ifndef __BSP_I2S_DATA_H__
#define __BSP_I2S_DATA_H__

#include "stm32h7xx_hal.h"
#include "main.h"

extern int32_t data_audio_20Hz[2200];

void Convert24To16(int16_t* data_array_out,int32_t* data_array,uint8_t channel,int length);

#endif

