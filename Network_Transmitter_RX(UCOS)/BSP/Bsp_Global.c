/***********************************************************************
文件名称：
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#include "main.h"

/*
 * 功能：
 *       板级初始化
 * 参数：
 *       无
 * 返回：
 *       无
 * 说明：
 *       可用与模块中初始化的尽量使用模块初始化
 */
void BSP_Init(void)
{
	LED_Configuration();
	NVIC_Configuration();
	USART_Configuration();
	NRF24L01_Init();    			//初始化处理器与NRF24L01连接的管脚
	Key_Configuration();
  while(NRF24L01_Check())			//24L01在线检测
  {
     printf("没有检测到NRF24L01，请确认NRF24L01是否连接上！\n\r");
//		 delay_ms(2000);
  }
	LED3_OFF;
}

