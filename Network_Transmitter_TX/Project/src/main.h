/***********************************************************************
文件名称：main.h
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4x7_eth.h"
#include "stm32f4x7_eth_bsp.h"
#include "netconf.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "string.h"
#include "UDP_SERVER.h"

#include "stm32f4xx.h"
#include "LCD_12864.H"
#include "delay.h"
#include "NRF24l01.h"
#include <stdio.h>
#include "KEY.H"
#include "LED.H"
#include "spi.h"
#include "sci.h"
#define RMII_MODE

void Time_Update(void);

void udp_demo_senddata(struct udp_pcb *upcb);

#endif
