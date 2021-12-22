#ifndef __I2S_H__
#define __I2S_H__
//#include "sys.h"  
#include "stm32h7xx_hal.h"
#include "main.h"
#include "string.h"
#include "stdlib.h"


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

extern I2S_HandleTypeDef I2S_HandleStructure;
//extern I2S_HandleTypeDef I2S_HandleStructure;

void I2S2_Init(void);
void I2S2_GPIO_Init(void);
void I2S_DMA_Init(void);
void I2S_DMA_ENABLE(void);
void PCM1794_Init(void);


///*24位数据扩展32位，转为16位数据数组*/
//void Convert24To16(uint32_t* data_array,int length);
/*完成音频信号的播放*/
void Audio_Play(uint32_t Hz,uint32_t Db);
/* 单声道切换 */
void Channel_Switch(uint8_t channel,int length);
#endif
/* i2s WS 低电平 左声道 高电平 右声道 */



