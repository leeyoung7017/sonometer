#ifndef __DEBUG_USART_H
#define	__DEBUG_USART_H

#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include <stdio.h>
#include "main.h"
#include "udp_demo.h"
#include "led.h"



//引脚定义
/*******************************************************/
#define DEBUG_USART                             USART1
#define DEBUG_USART_CLK_ENABLE()                __USART1_CLK_ENABLE();

#define DEBUG_USART_RX_GPIO_PORT                GPIOA
#define DEBUG_USART_RX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define DEBUG_USART_RX_PIN                      GPIO_PIN_10
#define DEBUG_USART_RX_AF                       GPIO_AF7_USARTA


#define DEBUG_USART_TX_GPIO_PORT                GPIOA
#define DEBUG_USART_TX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define DEBUG_USART_TX_PIN                      GPIO_PIN_9
#define DEBUG_USART_TX_AF                       GPIO_AF7_USART1

#define DEBUG_USART_IRQHandler                  USART1_IRQHandler
#define DEBUG_USART_IRQ                 		USART1_IRQn
/************************************************************/


//串口参数配置
#define DEBUG_USART_BAUDRATE                    115200
#define USART_WORDLENGTH 						USART_WORDLENGTH_8B
#define USART_STOPBITS							USART_STOPBITS_1
#define USART_PARITY							USART_PARITY_NONE
#define USART_MODE								USART_MODE_TX_RX

extern uint8_t RxBuffer[10];

typedef enum{
    page1 = 0u,
    page2 = 1u,
    page3 = 2u
}PageNum;

typedef enum{
    KeyReady = 0x1111,
    KeyAudio = 0x2222
}KeyAddr;

void Usart_SendString(uint8_t *str);
void DEBUG_USART_Config(void);
void UART_Transmit(uint32_t data);
void USART_Transmit(uint8_t data);
void USART1_Opera(void);
void Page_Switch(PageNum page);
void Key_Change(KeyAddr addr,uint32_t KeyValue);
void Key_Read(KeyAddr addr);
void USART_Printf(void);
int fputc(int ch, FILE *f);
#endif /* __USART1_H */
