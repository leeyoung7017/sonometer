#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h"
//#include "key.h"
//#include "lcd.h"
#include "sdram.h"
#include "usmart.h"
#include "pcf8574.h"
#include "timer.h"
#include "mpu.h"
#include "malloc.h"
#include "lwip/netif.h"
#include "lwip_comm.h"
#include "lwipopts.h"
#include "udp_demo.h"
#include "ad7767.h"
#include "bsp_i2s.h"
#include "usart.h"


uint32_t Hz_Audio = 0;      //��ƵƵ��Ҫ��
uint32_t Db_Audio = 0;      //��Ƶ����Ҫ��
uint8_t Ear_Audio = 0;      //��Ƶ������Ҫ��    1��left     2��right
double time = 0;            //��Ƶ����ʱ��
uint8_t Mode_Switch = 2;    //��׼ģʽ��У׼ģʽ���л���0����׼ģʽ     1��У׼ģʽ
uint8_t flag_ready = 0;     //׼����־λ
uint8_t flag_feedback = 0;  //�������ձ�־λ
uint8_t flag_udp_recv = 0;  //�������ݽ��ձ�־λ
uint8_t flag_udp_send = 0;  //�������ݷ��ͱ�־λ

void H7_encrypted(void)
{
	int i;
    char ID_H7[12] = {0x01,0xF0,0x82,0xFF,0x38,0x68,0x40,0xF0,0x80,0x70,0x38,0x60};	
	char sys_id[12]={0}; //�洢stm32оƬ��ID�ŵ�����
	for(i=0;i<12;i++)
	{
			sys_id[i]=*(uint8_t*)(0x1FF0F420+i); //��ȡSTM32оƬ��ΨһID
			if(sys_id[i] !=ID_H7[i])
			{
				while(1);
			}
	}
}

void udp_demo_init(void)
{
    while(lwip_comm_init());         //lwip��ʼ��
    udp_demo_test();
}

void HMI_Init(void)
{
    Page_Switch(page1);
}



int main(void)
{
//	H7_encrypted();
    Write_Through();                        //����ǿ��͸д��
    MPU_Memory_Protection();                //������ش洢����
    Cache_Enable();                         //��L1-Cache
	HAL_Init();				        		//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);  		    //����ʱ��,400Mhz 
	delay_init(400);						//��ʱ��ʼ��
	uart_init(115200);						//���ڳ�ʼ��

    printf("lishuyang");
    
    HMI_Init();								//�����ʼ��
	LED_Init();								//��ʼ��LED
//	KEY_Init();								//��ʼ������
	SDRAM_Init();                   		//��ʼ��SDRAM
	PCF8574_Init();                         //��ʼ��PCF8574
    
    
	/* ad7767 ��ʼ�� */
	AD7767_Init();
    udp_demo_init();
    
    /* pcm1794��ʼ�� */
	PCM1794_Init();    
    
	while(1)
	{
		lwip_periodic_handle();
		delay_ms(2);
	} 	
}



