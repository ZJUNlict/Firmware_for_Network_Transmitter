/***********************************************************************
�ļ����ƣ�LCD_12864.C
��    �ܣ�
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "main.h"

/*************LCD io������******************/
void LCD_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable GPIOD and GPIOE clocks */
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);  
	                    
	/* PE.00(D0), PE.01(D1), PE.02(D2), PE.03(D3), PE.04(D4), PE.05(D5), PE.06(D6), PE.07(D7), PE.08(D8)
	 PE.09(D9), PE.10(D10), PE.11(D11), PE.12(D12), PE.13(D13), PE.14(D14), PE.15(D15)   */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/* PD.13(RS), PD.14(WR), PD.15(RD) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
//д����
void WriteDataLCD(unsigned char WDLCD)
{
	ReadStatusLCD(); //���æ 
	LCD_RS_SET;
	LCD_RW_CLR;
	GPIOE->ODR = WDLCD;
	LCD_E_SET;
	LCD_E_SET;
	LCD_E_SET;
	LCD_E_CLR;
}

//дָ��
void WriteCommandLCD(unsigned char WCLCD,unsigned char BuysC) //BuysCΪ0ʱ����æ���
{
	if (BuysC) ReadStatusLCD(); //������Ҫ���æ 
	LCD_RS_CLR;
	LCD_RW_CLR; 
	GPIOE->ODR = WCLCD;
	LCD_E_SET; 
	LCD_E_SET;
	LCD_E_SET;
	LCD_E_CLR;  
}

//��״̬
unsigned char ReadStatusLCD(void)
{

	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
// 	GPIOE->BSRRH = 0x44444444;
// 	GPIOE->BSRRL = 0x44444444;

	LCD_RS_CLR;
	LCD_RW_SET; 
	LCD_E_SET;
	while (GPIO_ReadInputData(GPIOE) & Busy) //���æ�ź�
	{
		;
	}
	LCD_E_CLR;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
// 	GPIOE->BSRRH = 0x33333333;
// 	GPIOE->BSRRL = 0x33333333;
	return(GPIO_ReadInputData(GPIOE));
}

void LCDInit(void) //LCM��ʼ��
{
	LCD_Configuration();
	WriteCommandLCD(0x30,1); //��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
	WriteCommandLCD(0x01,1); //��ʾ����
	WriteCommandLCD(0x06,1); // ��ʾ����ƶ�����
	WriteCommandLCD(0x0C,1); // ��ʾ�����������
}
void LCDClear(void) //����
{
	WriteCommandLCD(0x01,1); //��ʾ����
	WriteCommandLCD(0x34,1); // ��ʾ����ƶ�����
	WriteCommandLCD(0x30,1); // ��ʾ�����������
}
void LCDFlash(void)	//��˸Ч��
{
	WriteCommandLCD(0x08,1); //��ʾ����
	Delay400Ms();
	WriteCommandLCD(0x0c,1); // ��ʾ�����������
	Delay400Ms();
	WriteCommandLCD(0x08,1); //��ʾ����
	Delay400Ms();
	WriteCommandLCD(0x0c,1); // ��ʾ�����������
	Delay400Ms();
	WriteCommandLCD(0x08,1); //��ʾ����
	Delay400Ms();
}
//��ָ��λ����ʾһ���ַ�
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
	if(Y<1)
	{
		Y=1;
	}
	
	if(Y>4)
	{
		Y=4;
	}
	X &= 0x0F; //����X���ܴ���16��Y���ܴ���1
	switch(Y)
	{
		case 1:
		{
			X|=0X80;
			break;
		}
		case 2:
		{
			X|=0X90;
			break;
		}
		case 3:
		{
			X|=0X88;
			break;
		}
		case 4:
		{
			X|=0X98;
			break;
		}
		default :
		{
			break;
		}
	}
	WriteCommandLCD(X, 0); //���ﲻ���æ�źţ����͵�ַ��
	WriteDataLCD(DData);
	Delay5Ms();
}

//��ָ��λ����ʾһ���ַ�
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char  *DData)
{
	unsigned char ListLength,X2;
	ListLength = 0;
	X2=X;
	if(Y<1)
	{
		Y=1;
	}
	if(Y>4)
	{
		Y=4;
	}
	X &= 0x0F; //����X���ܴ���16��Y��1-4֮��
	switch(Y)
	{
		case 1:
		{
			X2|=0X80;
			break;	//����������ѡ����Ӧ��ַ
		}
		case 2:
		{
			X2|=0X90;
			break;
		}
		case 3:
		{	
			X2|=0X88;
			break;
		}
		case 4:
		{
			X2|=0X98;
			break;
		}
		default :
		{
			break;
		}
	}
	WriteCommandLCD(X2, 1); //���͵�ַ��
	while (DData[ListLength]>=0x20) //�������ִ�β���˳�
	{
		if (X <= 0x0F) //X����ӦС��0xF
		{
			WriteDataLCD(DData[ListLength]); //
			ListLength++;
			X++;
			Delay5Ms();
		}
	}
}

//ͼ����ʾ122*32
void DisplayImage (unsigned char *DData)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	for(i=0;i<9;)
	{		//���������ϰ������°�������Ϊ��ʼ��ַ��ͬ����Ҫ�ֿ�
		for(x=0;x<32;x++)
		{				//32��
			WriteCommandLCD(0x34,1);
			WriteCommandLCD((0x80+x),1);//�е�ַ
			WriteCommandLCD((0x80+i),1);	//�е�ַ���°������������е�ַ0X88
			WriteCommandLCD(0x30,1);		
			for(y=0;y<16;y++)
			{	
				WriteDataLCD(DData[tmp+y]);//��ȡ����д��LCD
			}
			tmp+=16;		
		}
		i+=8;
	}
	WriteCommandLCD(0x36,1);	//���书���趨
	WriteCommandLCD(0x30,1);
}

//5ms��ʱ
void Delay5Ms(void)
{
	unsigned int TempCyc = 5552 * 2;
	while(TempCyc--);
}

//400ms��ʱ
void Delay400Ms(void)
{
	unsigned char TempCycA = 5 * 2;
	unsigned int TempCycB;
	while(TempCycA--)
	{
		TempCycB = 7269;
		while(TempCycB--);
	}
}