#include "main.h"	

#define SYSTEMTICK_PERIOD_MS  10

unsigned char tmp_buf[33]={'a','b','c'};
unsigned char tmp_buf_rx[33]={'a','b','c'};
u8 package_success=0, package_fail=0;

__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
uint32_t timingdelay;
void Delay(uint32_t nCount);

int main(void)
{
	/* configure ethernet (GPIOs, clocks, MAC, DMA) */ 
	ETH_BSP_Config();
	/* Initilaize the LwIP stack */
	LwIP_Init();
	UDP_server_init();
	
  SysTick_Configuration();		//延时初始化  
	//USART_Configuration();	
  Key_Configuration();
	LED_Configuration();
  NRF24L01_Init();    			//初始化处理器与NRF24L01连接的管脚
	
  while(NRF24L01_Check())			//24L01在线检测
  {
		//printf("没有检测到NRF24L01，请确认NRF24L01是否连接上！\n\r");
		delay_ms(1000);
		LED2_ON;
		delay_ms(1000);
		LED2_OFF;
  }	
	LED3_ON;
	TX_Mode();
	
	while(1);
	
	return 0;
}


/**
  * @brief  Inserts a delay time.
  * @param  nCount: number of 10ms periods to wait for.
  * @retval None
  */
void Delay(uint32_t nCount)
{
  /* Capture the current local time */
  timingdelay = LocalTime + nCount;  

  /* wait until the desired delay finish */  
  while(timingdelay > LocalTime)
  {     
  }
}

/**
  * @brief  Updates the system local time
  * @param  None
  * @retval None
  */
void Time_Update(void)
{
  LocalTime += SYSTEMTICK_PERIOD_MS;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

