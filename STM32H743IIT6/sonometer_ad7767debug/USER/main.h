/**
  ******************************************************************************
  * @file    Templates/Inc/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    21-April-2017
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H_
#define __MAIN_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#define DEST_IP_ADDR0   ((uint8_t)192U)
#define DEST_IP_ADDR1   ((uint8_t)168U)
#define DEST_IP_ADDR2   ((uint8_t)1U)
#define DEST_IP_ADDR3   ((uint8_t)67U)

#define DEST_PORT       ((uint16_t)8080U)   //远端udp连接的端口
#define UDP_DEMO_PORT	((uint16_t)8080U)	//定义udp连接的端口 
   
//静态IP地址: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3
#define IP_ADDR0   ((uint8_t) 192U)
#define IP_ADDR1   ((uint8_t) 168U)
#define IP_ADDR2   ((uint8_t) 1U)
#define IP_ADDR3   ((uint8_t) 30U)
   
//子网掩码
#define NETMASK_ADDR0   ((uint8_t) 255U)
#define NETMASK_ADDR1   ((uint8_t) 255U)
#define NETMASK_ADDR2   ((uint8_t) 255U)
#define NETMASK_ADDR3   ((uint8_t) 0U)

//网关
#define GW_ADDR0   ((uint8_t) 192U)
#define GW_ADDR1   ((uint8_t) 168U)
#define GW_ADDR2   ((uint8_t) 1U)
#define GW_ADDR3   ((uint8_t) 1U) 

//全局变量
extern uint32_t Hz_Audio;      //音频频率要求
extern uint32_t Db_Audio;      //音频幅度要求
extern uint8_t Ear_Audio;      //音频单声道要求    1：left     2：right
extern double time;
extern uint8_t Mode_Switch;    //标准模式与校准模式的切换；0：标准模式     1：校准模式
extern uint8_t flag_ready;  		   //准备标志位
extern uint8_t flag_feedback;  	 //反馈接收标志位
extern uint8_t flag_udp_recv;  //网口数据接收标志位
extern uint8_t flag_udp_send;  //网口数据发送标志位


void H7_encrypted(void);
void udp_demo_init(void);
void HMI_Init(void);

#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
