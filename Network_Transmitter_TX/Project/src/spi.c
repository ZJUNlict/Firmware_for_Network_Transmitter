
#include "main.h"

//��������ӿ�SPI�ĳ�ʼ����SPI���ó���ģʽ							  
//������ѡ������ϵ�п����崦������SPI��NRF24L01���ж�д�������ȶ�SPI���г�ʼ��
void WIRELESS_SPI_Init(void)
{	 
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_DeInit(SPI3);
    // Enable SPI and GPIO clocks
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI3);        
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI3); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI3); 
    ////SPI�ڳ�ʼ�� Set PC10,11,12 as Output push-pull - SCK, MISO and MOSI
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //��ʼ��SPI�ṹ��
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ����ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                //����SPIΪ��ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		            //SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                    //����ʱ���ڲ�����ʱ��ʱ��Ϊ�͵�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                    //��һ��ʱ���ؿ�ʼ��������
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                    //NSS�ź��������ʹ��SSIλ������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPI������Ԥ��ƵֵΪ8
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	                        //CRCֵ����Ķ���ʽ

	SPI_Init(SPI_WIRELESS, &SPI_InitStructure);   //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPI2�Ĵ���
	
	/* Enable SPI3  */
	SPI_Cmd(SPI_WIRELESS, ENABLE);                                      //ʹ��SPI����
	
	SPI_ReadWriteByte(0xff);                                            //��������		 
}  

u8 SPI_ReadWriteByte(u8 TxData)                                        //SPI��д���ݺ���
{		
	u8 retry=0;				 	
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI_WIRELESS, SPI_I2S_FLAG_TXE) == RESET)      //���ͻ����־λΪ��
		{
		retry++;
		if(retry>200)return 0;
		}			  
	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI_WIRELESS, TxData);                                    //ͨ������SPI1����һ������
	retry=0;
	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI_WIRELESS, SPI_I2S_FLAG_RXNE) == RESET);   //���ջ����־λ��Ϊ��
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI_WIRELESS);                                 //ͨ��SPI1���ؽ�������				    
}

