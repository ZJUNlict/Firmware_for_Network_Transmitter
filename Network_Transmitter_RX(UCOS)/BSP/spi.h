#ifndef __SPI_H
#define __SPI_H

#define SPI_WIRELESS     SPI3
																					  
void WIRELESS_SPI_Init(void);			 //初始化SPI口 
//void SPIx_SetSpeed(u8 SpeedSet); //设置SPI速度
u8 SPI_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
		 
#endif

