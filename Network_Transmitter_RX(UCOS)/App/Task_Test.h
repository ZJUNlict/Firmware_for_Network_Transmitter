/***********************************************************************
文件名称：
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#ifndef _APP_TASK_TEST_H_
#define _APP_TASK_TEST_H_

#define TASK_TEST_LED_STK_SIZE	400
#define TASK_UDP_SREVER_STK_SIZE	2000
#define TASK_24L01_STK_SIZE 3000

extern OS_STK Stk_Task_LED[TASK_TEST_LED_STK_SIZE];
extern OS_STK Stk_Task_UDP_Server[TASK_UDP_SREVER_STK_SIZE];
extern OS_STK Stk_Task_24L01[TASK_24L01_STK_SIZE];
	
void Task_LED(void *pdata);
void Task_UDP_Server(void *pdata);
void Task_24L01(void *pdata);

#endif
