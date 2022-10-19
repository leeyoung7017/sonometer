#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "sys.h"
#include "delay.h"

void Audio_GPIO_Init(void); //Audio端口配置
void Audio_Init(uint32_t Freq);      //Audio模拟传输配置
void Audio_Transmit(void);  //Audio传输音频数据
void Audio_Send(void);      //Audio发送字节数据

#endif
