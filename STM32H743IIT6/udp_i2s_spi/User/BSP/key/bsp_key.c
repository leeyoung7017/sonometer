#include "bsp_key.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	KEY_CTR_GPIO_CLK_ENABLE();
	
	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStruct.Pin = KEY_CTR_Pin;	

	/*�������ŵ��������Ϊ�ⲿ�ж��½���*/
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;  

	/*��������Ϊ����ģʽ*/
	GPIO_InitStruct.Pull  = GPIO_PULLUP;

	/*������������Ϊ���� */   
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; 

	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	HAL_GPIO_Init(KEY_CTR_GPIO_PORT, &GPIO_InitStruct);	
	
	//�ж���0
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,0,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);             //ʹ���ж���0

}




