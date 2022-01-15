#include "timer.h"

TIM_HandleTypeDef htimx;


/* TIM6 ���ڵ�ʱ������Ϊ APB1 (APB1 Clock  120MHz) */
void TIMx_Init(uint32_t psc,uint32_t per)
{
	__TIMx_CLK_ENABLE();
	
	htimx.Instance = TIMx;
	htimx.Init.Period = per;
	htimx.Init.Prescaler = psc;
	htimx.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htimx.Init.CounterMode = TIM_COUNTERMODE_UP;
	
	if(HAL_TIM_Base_Init(&htimx) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_TIM_Base_Start_IT(&htimx);
	
	/* NVIC ���� */
	HAL_NVIC_SetPriority(TIM2_IRQn,1,0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

/**
 * @brief ��ʱ���жϷ��������ж��Ƿ���
 * @param {*}
 * @return {*}
 */
void TIM2_IRQHandler(void)
{
	if(__HAL_TIM_GET_FLAG(&htimx,TIM_FLAG_UPDATE) != RESET)
	{
		if(__HAL_TIM_GET_IT_SOURCE(&htimx,TIM_IT_UPDATE) !=RESET)
		{
			USART1_Opera();//����������ָ��
			/* �жϴ�����ָ�� */
			if(flag_feedback == 1)
			{
				/* ���ݷ��� */
				tcp_demo_sendbuf = "OK\n";
				udp_demo_senddata(udp_demo_pcb);
				flag_feedback = 0;
				memset(RxBuffer,'\0',sizeof(RxBuffer));
			}
		}
		__HAL_TIM_CLEAR_IT(&htimx,TIM_IT_UPDATE);
	}
	__HAL_TIM_CLEAR_FLAG(&htimx,TIM_FLAG_UPDATE);
}

