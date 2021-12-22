#include "timer.h"

TIM_HandleTypeDef htimx;


/* TIM6 所在的时钟总线为 APB1 (APB1 Clock  120MHz) */
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
	
	/* NVIC 配置 */
	HAL_NVIC_SetPriority(TIM2_IRQn,1,0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

//int flag = 0;
void TIM2_IRQHandler(void)
{
	if(__HAL_TIM_GET_FLAG(&htimx,TIM_FLAG_UPDATE) != RESET)
	{
		if(__HAL_TIM_GET_IT_SOURCE(&htimx,TIM_IT_UPDATE) !=RESET)
		{
//			if(flag)
//        {
//          flag = 0;
//			
//          //调用网卡接收函数
//          ethernetif_input(&gnetif);
//        }
//        /* 处理 LwIP 超时 */
//        sys_check_timeouts();
//			
//			/* 定时器更新中断处理 */
//			if(Mode_Switch == 0)//判断切换模式：标准模式	校准模式
//			{
//				//标准模式下，播放音频1s
//				Audio_Play(Hz_Audio,Db_Audio);
//				Mode_Switch = 2;

//			}
//			else if(Mode_Switch == 1)
//			{
//				//校准模式下操作 
//			}
			/*********************/
		}
		__HAL_TIM_CLEAR_IT(&htimx,TIM_IT_UPDATE);
	}
	__HAL_TIM_CLEAR_FLAG(&htimx,TIM_FLAG_UPDATE);
}

