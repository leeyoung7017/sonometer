#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "sys.h"
#include "delay.h"

void Audio_GPIO_Init(void); //Audio�˿�����
void Audio_Init(uint32_t Freq);      //Audioģ�⴫������
void Audio_Transmit(void);  //Audio������Ƶ����
void Audio_Send(void);      //Audio�����ֽ�����

#endif
