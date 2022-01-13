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
   
//��̬IP��ַ: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3
#define IP_ADDR0   ((uint8_t) 192U)
#define IP_ADDR1   ((uint8_t) 168U)
#define IP_ADDR2   ((uint8_t) 1U)
#define IP_ADDR3   ((uint8_t) 30U)
   
//��������
#define NETMASK_ADDR0   ((uint8_t) 255U)
#define NETMASK_ADDR1   ((uint8_t) 255U)
#define NETMASK_ADDR2   ((uint8_t) 255U)
#define NETMASK_ADDR3   ((uint8_t) 0U)

//����
#define GW_ADDR0   ((uint8_t) 192U)
#define GW_ADDR1   ((uint8_t) 168U)
#define GW_ADDR2   ((uint8_t) 1U)
#define GW_ADDR3   ((uint8_t) 1U) 

//ȫ�ֱ���
extern uint32_t Hz_Audio;      //��ƵƵ��Ҫ��
extern uint32_t Db_Audio;      //��Ƶ����Ҫ��
extern uint8_t Ear_Audio;      //��Ƶ������Ҫ��    1��left     2��right
extern uint8_t Mode_Switch;    //��׼ģʽ��У׼ģʽ���л���0����׼ģʽ     1��У׼ģʽ

char H7_encrypted(void);

static void udp_demo_Init(void);
void udp_lwip_check(void);
void Error_Handler(void);
static void SystemClock_Config(void);
static void MPU_Config(void);
#endif /* __MAIN_H */

