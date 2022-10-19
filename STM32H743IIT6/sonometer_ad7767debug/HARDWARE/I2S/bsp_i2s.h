/*
 * @Descripttion: 
 * @version: 
 * @Author: leeyoung7017
 * @Date: 2021-12-11 16:13:00
 * @Email: leeyoung7017@163.com
 */
#ifndef __I2S_H__
#define __I2S_H__
//#include "sys.h"  
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_conf.h"
#include "main.h"
#include <math.h>
#include "string.h"
#include "stdlib.h"
//#include "timer.h"


#define I2S2_DATA_Pin GPIO_PIN_1
#define I2S2_DATA_GPIO_Port GPIOC
#define I2S2_BCK_Pin GPIO_PIN_10
#define I2S2_BCK_GPIO_Port GPIOB
#define I2S2_MCK_Pin GPIO_PIN_6
#define I2S2_MCK_GPIO_Port GPIOC
#define I2S2_LRCK_Pin GPIO_PIN_12
#define I2S2_LRCK_GPIO_Port GPIOB

/* I2S数据传输 timeout */
#define HAL_I2S_DELAY 1000
#define DataSize_20   2200
#define DataSize_20_4   8800

//extern I2S_HandleTypeDef I2S_HandleStructure;

void I2S2_Init(void);
void I2S2_GPIO_Init(void);
void I2S_DMA_Init(void);
void I2S_DMA_ENABLE(void);
void PCM1794_Init(void);
void I2S_ENABLE(FunctionalState flag);


/*完成音频信号的播放*/
void Audio_Play(uint32_t Hz,uint32_t Db);
#endif
/* i2s WS 低电平 左声道 高电平 右声道 */



