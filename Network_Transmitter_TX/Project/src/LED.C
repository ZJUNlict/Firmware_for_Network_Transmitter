/***********************************************************************
�ļ����ƣ�LED.C
��    �ܣ�led  IO��ʼ��
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "main.h"

/***********************************************************************
�������ƣ�LED_Configuration(void)
��    �ܣ����LED������
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void LED_Configuration(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Enable the GPIO_LED Clock */
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE); 						 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*****Ϩ���ĸ�led��******/
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
}

/***********************************************************************
�������ƣ�LED_Blink(void)
��    �ܣ����LED��˸
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void LED_Blink(void)
{
	/*****Ϩ���ĸ�led��******/
	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
	LED_Delay(0x4fffff);
	/*****�����ĸ�led��******/
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
}
/***********************************************************************
�������ƣ�One_LED_ON(unsigned char led_num)
��    �ܣ�ʵ�ֵ���һ��LED��
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void One_LED_ON(unsigned char led_num)
{	
	/*****Ϩ���ĸ�led��******/
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	switch(led_num)
	{
//		case 1:
//		{
//			LED1_ON;
//			break;
//		}
//		case 2:
//		{
//			LED2_ON;
//			break;		
//		}
//		case 3:
//		{
//			LED3_ON;
//			break;		
//		}
//		case 4:
//		{
//			LED4_ON;
//			break;		
//		}
		case 1:
		{
			LED1_ON;
			break;
		}
		case '2':
		{
			LED2_ON;
			break;		
		}
		case '3':
		{
			LED3_ON;
			break;		
		}
		case '4':
		{
			LED4_ON;
			break;		
		}
		default:
		{
			break;	
		}
	}		
}

void static LED_Delay(uint32_t nCount)
{ 
  while(nCount > 0)
  { 
  	  nCount --;   
  }
}