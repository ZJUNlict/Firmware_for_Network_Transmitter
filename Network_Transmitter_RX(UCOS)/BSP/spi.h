#ifndef __SPI_H
#define __SPI_H

#define SPI_WIRELESS     SPI3
																					  
void WIRELESS_SPI_Init(void);			 //��ʼ��SPI�� 
//void SPIx_SetSpeed(u8 SpeedSet); //����SPI�ٶ�
u8 SPI_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif

