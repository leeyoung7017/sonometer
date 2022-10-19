/*
 * @Descripttion: 
 * @version: 
 * @Author: leeyoung7017
 * @Date: 2021-12-11 16:39:28
 * @Email: leeyoung7017@163.com
 */
#ifndef __AD7767_H__
#define __AD7767_H__

#include "stm32h7xx_hal.h"
#include "main.h"
#include <stdio.h>
#include "usart.h" 

#define SIZE_ACQUIRED 750

#define DRDY_GPIO_Port	GPIOB
#define DRDY_Pin	GPIO_PIN_14
#define DRDY_EXTI_IRQn EXTI15_10_IRQn

#define SYNC_PD_Pin     GPIO_PIN_15
#define SYNC_PD_Port    GPIOB
#define SYNC_PD(n)   HAL_GPIO_WritePin(SYNC_PD_Port,SYNC_PD_Pin,n?GPIO_PIN_SET:GPIO_PIN_RESET)

#define SPI3_MISO_Pin		GPIO_PIN_11
#define SPI3_MOSI_Pin		GPIO_PIN_2
#define SPI3_SCK_Pin		GPIO_PIN_10
#define SPI3_CS_Pin			GPIO_PIN_1
#define SPI3_MISO_Port	GPIOC
#define SPI3_MOSI_Port	GPIOB
#define SPI3_SCK_Port		GPIOC
#define SPI3_CS_Port		GPIOB

#define CS(n)		HAL_GPIO_WritePin(SPI3_CS_Port,SPI3_CS_Pin,n?GPIO_PIN_SET:GPIO_PIN_RESET)
#define CS_ENABLE   CS(0)
#define CS_DISABLE  CS(1)

void AD7767_Init(void);
void AD7767_GPIO_Init(void);
void AD7767_EXTI_Config(void);
void AD7767_SPI_Config(void);
void AD7767_Reset(void);
void SPI_Tx_Byte(uint8_t Tx);
void HAL_EXTI_ENABLE(uint16_t GPIO_PIN_X);
void HAL_EXTI_DISABLE(uint16_t GPIO_PIN_X);
uint32_t Convert_8to24(uint8_t *pdata);

#endif
