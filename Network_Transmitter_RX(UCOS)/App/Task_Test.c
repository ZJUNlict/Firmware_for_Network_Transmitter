#include "main.h"  

OS_STK Stk_Task_LED[TASK_TEST_LED_STK_SIZE];
OS_STK Stk_Task_UDP_Server[TASK_UDP_SREVER_STK_SIZE];
OS_STK Stk_Task_24L01[TASK_24L01_STK_SIZE];

unsigned char tmp_buf[32];
/***********************************************************************
函数名称：void Task_LED(void *pdata)
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
***********************************************************************/
void Task_LED(void *pdata)
{		 
  while(1)
	{
		OSTimeDlyHMSM(0, 0, 0, 100);//
		GPIO_ToggleBits(LED1);
		OSTimeDlyHMSM(0, 0, 0, 100);//
		GPIO_ToggleBits(LED2);
//		OSTimeDlyHMSM(0, 0, 0, 100);//
//		GPIO_ToggleBits(LED3);
//		OSTimeDlyHMSM(0, 0, 0, 100);//
//		GPIO_ToggleBits(LED4);
	}
}
/***********************************************************************
函数名称：void Task_UDP_Server(void *pdata)
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
***********************************************************************/
void Task_UDP_Server(void *pdata)
{
	__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
	/* configure ethernet (GPIOs, clocks, MAC, DMA) */ 
	ETH_BSP_Config();
	LwIP_Init();

	/* UDP_server Init */
	UDP_server_init();
	while(1)
	{  
		LocalTime += 2;
		LwIP_Periodic_Handle(LocalTime);		
		OSTimeDlyHMSM(0, 0, 0, 5);//挂起5ms，以便其他线程运行
	}
}

int package_received = 0;
void Task_24L01(void *pdata)
{
	RX_Mode();	  				//默认接收模式				    	
  while(1)
	{
		if(NRF24L01_RxPacket(tmp_buf) == 0)
		{
			package_received++;
//			printf("%d\n",i);
			if (package_received==32){
					LED4_OFF;
				}
			if (package_received==64){
					LED4_ON;
					package_received=0;
				}
		 udp_demo_senddata();
		}
		OSTimeDlyHMSM(0, 0, 0, 1);//挂起1ms，以便其他线程运行
	}
}
