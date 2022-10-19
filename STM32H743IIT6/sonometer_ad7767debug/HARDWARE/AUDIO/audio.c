#include "audio.h"

uint32_t Freq_Audio = 0;

void Audio_GPIO_Init(void)
{
     GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();					//开启GPIOB时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();					//开启GPIOB时钟
	
    GPIO_Initure.Pin=GPIO_PIN_2;			        //I2S_DATA引脚
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		//推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;         		//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);     		//初始化
    
    GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_12;      //I2S_BCK引脚 I2S2_LRCK引脚
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     		//初始化
}

void Audio_Init(uint32_t Freq)
{
    //音频采样率
    Freq_Audio = Freq;
    Audio_GPIO_Init();
    
    
}

