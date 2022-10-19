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


uint32_t Hz_Audio = 0;      //音频频率要求
uint32_t Db_Audio = 0;      //音频幅度要求
uint8_t Ear_Audio = 0;      //音频单声道要求    1：left     2：right
double time = 0;            //音频播放时长
uint8_t Mode_Switch = 2;    //标准模式与校准模式的切换；0：标准模式     1：校准模式
uint8_t flag_ready = 0;     //准备标志位
uint8_t flag_feedback = 0;  //反馈接收标志位
uint8_t flag_udp_recv = 0;  //网口数据接收标志位
uint8_t flag_udp_send = 0;  //网口数据发送标志位

void H7_encrypted(void)
{
	int i;
    char ID_H7[12] = {0x01,0xF0,0x82,0xFF,0x38,0x68,0x40,0xF0,0x80,0x70,0x38,0x60};	
	char sys_id[12]={0}; //存储stm32芯片的ID号的数组
	for(i=0;i<12;i++)
	{
			sys_id[i]=*(uint8_t*)(0x1FF0F420+i); //读取STM32芯片的唯一ID
			if(sys_id[i] !=ID_H7[i])
			{
				while(1);
			}
	}
}

void udp_demo_init(void)
{
    while(lwip_comm_init());         //lwip初始化
    udp_demo_test();
}

void HMI_Init(void)
{
    Page_Switch(page1);
}



int main(void)
{
//	H7_encrypted();
    Write_Through();                        //开启强制透写！
    MPU_Memory_Protection();                //保护相关存储区域
    Cache_Enable();                         //打开L1-Cache
	HAL_Init();				        		//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);  		    //设置时钟,400Mhz 
	delay_init(400);						//延时初始化
	uart_init(115200);						//串口初始化

    printf("lishuyang");
    
    HMI_Init();								//界面初始化
	LED_Init();								//初始化LED
//	KEY_Init();								//初始化按键
	SDRAM_Init();                   		//初始化SDRAM
	PCF8574_Init();                         //初始化PCF8574
    
    
	/* ad7767 初始化 */
	AD7767_Init();
    udp_demo_init();
    
    /* pcm1794初始化 */
	PCM1794_Init();    
    
	while(1)
	{
		lwip_periodic_handle();
		delay_ms(2);
	} 	
}



