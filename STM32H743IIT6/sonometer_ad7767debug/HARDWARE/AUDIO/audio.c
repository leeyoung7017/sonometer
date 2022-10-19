#include "audio.h"

uint32_t Freq_Audio = 0;

void Audio_GPIO_Init(void)
{
     GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();					//����GPIOBʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();					//����GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_2;			        //I2S_DATA����
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		//�������
    GPIO_Initure.Pull=GPIO_PULLDOWN;         		//����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);     		//��ʼ��
    
    GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_12;      //I2S_BCK���� I2S2_LRCK����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     		//��ʼ��
}

void Audio_Init(uint32_t Freq)
{
    //��Ƶ������
    Freq_Audio = Freq;
    Audio_GPIO_Init();
    
    
}

