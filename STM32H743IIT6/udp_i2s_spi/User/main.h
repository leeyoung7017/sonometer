/*
 * @Descripttion: 
 * @version: 
 * @Author: leeyoung7017
 * @Date: 2021-12-30 21:58:41
 * @Email: leeyoung7017@163.com
 */
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32h7xx_hal.h"
#include "ad7767.h"
#include "stdint.h"

#define DEST_IP_ADDR0   ((uint8_t)192U)
#define DEST_IP_ADDR1   ((uint8_t)168U)
#define DEST_IP_ADDR2   ((uint8_t)1U)
#define DEST_IP_ADDR3   ((uint8_t)67U)

#define DEST_PORT       ((uint16_t)8080U)
   
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
extern uint8_t Mode_Switch;    //标准模式与校准模式的切换；0：标准模式     1：校准模式
extern uint8_t flag_ready;     //准备标志位
extern uint8_t flag_feedback;  //反馈接收标志位
extern double  time = 0;              //音频播放时间

void H7_encrypted(void);

static void udp_demo_Init(void);
void udp_lwip_check(void);
void Error_Handler(void);
static void SystemClock_Config(void);
static void MPU_Config(void);
#endif /* __MAIN_H */

