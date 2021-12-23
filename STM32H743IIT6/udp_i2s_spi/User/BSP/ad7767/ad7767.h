#ifndef __AD7767_H__
#define __AD7767_H__

#include "stm32h7xx_hal.h"
#include "main.h"
#include "bsp_key.h"
#include "./delay/core_delay.h"  

#define DRDY_GPIO_Port	GPIOB
#define DRDY_Pin	GPIO_PIN_14
#define DRDY_EXTI_IRQn EXTI15_10_IRQn

#define SYNC_PD_Pin     GPIO_PIN_15
#define SYNC_PD_Port    GPIOB
#define SYNC_PD(n)   HAL_GPIO_WritePin(SPI3_CS_Port,SPI3_CS_Pin,n?GPIO_PIN_SET:GPIO_PIN_RESET)

#define SPI3_MISO_Pin		GPIO_PIN_11
#define SPI3_MOSI_Pin		GPIO_PIN_2
#define SPI3_SCK_Pin		GPIO_PIN_10
#define SPI3_CS_Pin			GPIO_PIN_1
#define SPI3_MISO_Port	GPIOC
#define SPI3_MOSI_Port	GPIOB
#define SPI3_SCK_Port		GPIOC
#define SPI3_CS_Port		GPIOB

#define CS(n)		HAL_GPIO_WritePin(SPI3_CS_Port,SPI3_CS_Pin,n?GPIO_PIN_SET:GPIO_PIN_RESET)


void AD7767_Init(void);
void AD7767_GPIO_Init(void);
void AD7767_EXTI_Config(void);
void AD7767_SPI_Config(void);
void AD7767_Reset(void);
void SPI_Tx_Byte(uint8_t Tx);
void HAL_EXTI_ENABLE(int GPIO_PIN_X);
void HAL_EXTI_DISABLE(int GPIO_PIN_X);
uint32_t Convert_8to24(uint8_t *pdata);

#endif
