/***********************************************************************
文件名称：main.C
功    能：
编写时间：
编 写 人：北京智嵌物联网电子技术团队
注    意：
***********************************************************************/
#include "main.h"


int main(void)
{
	//初始化板子
	BSP_Init();
	//初始化系统
	OSInit();
	//创建启动任务
	OSTaskCreate(	Task_StartUp,               		    				//指向任务代码的指针
                  	(void *) 0,												//任务开始执行时，传递给任务的参数的指针
					(OS_STK *)&Stk_TaskStartUp[TASK_STARTUP_STK_SIZE - 1],	//分配给任务的堆栈的栈顶指针   从顶向下递减
					(INT8U) OS_USER_PRIO_LOWEST);							//分配给任务的优先级  

	//节拍计数器清0  
	OSTimeSet(0);

	//启动UCOS-II内核
	OSStart();

	return 0;
}
//启动任务堆栈
OS_STK Stk_TaskStartUp[TASK_STARTUP_STK_SIZE];

void Task_StartUp(void *pdata)
{

	//初始化UCOS时钟
	//OS_TICKS_PER_SEC 为 UCOS-II 每秒嘀嗒数
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC - 1);

	//优先级说明，使用OS_USER_PRIO_GET(n)宏来获取
	//OS_USER_PRIO_GET(0)最高,OS_USER_PRIO_GET(1)次之，依次类推
	//OS_USER_PRIO_GET(0)：最高的优先级，主要用于在处理紧急事务，需要将优先处理的任务设置为最高这个优先级  

	//OSTaskCreate(	Task_Xxx,               		    					//指向任务代码的指针
    //              (void *)0,												//任务开始执行时，传递给任务的参数的指针
	//				(OS_STK *)&Stk_TaskXxx[TASK_XXX_STK_SIZE - 1],			//分配给任务的堆栈的栈顶指针   从顶向下递减
	//				(INT8U) OS_USER_PRIO_GET(N));							//分配给任务的优先级  

	 
	OSTaskCreate(Task_UDP_Server, (void *)0, &Stk_Task_UDP_Server[TASK_UDP_SREVER_STK_SIZE-1], OS_USER_PRIO_GET(5));
//OSTaskCreate(Task_LED, (void *)0, &Stk_Task_LED[TASK_TEST_LED_STK_SIZE-1], OS_USER_PRIO_GET(6));
	OSTaskCreate(Task_24L01, (void *)0, &Stk_Task_24L01[TASK_24L01_STK_SIZE-1], OS_USER_PRIO_GET(4));
	
	while (1)
	{
		//循环看守程序执行情况
		//通常情况下这里使一个系统状态灯闪烁，表示系统正在运行
		GPIO_ToggleBits(CPU_LED);
		OSTimeDlyHMSM(0, 0, 0, 500);//500ms
	}
}
