
/***********************************************************************
�ļ����ƣ�UDP_SERVER.h
��    �ܣ����UDP�������շ�
��дʱ�䣺2013.4.25
�� д �ˣ���־��
ע    �⣺
***********************************************************************/
#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_



/***************������ip��MAC����*************************/
#define BOARD_IP  			 	10,12,225,78   		//������ip 
#define BOARD_NETMASK   	 	255,255,255,0   		//��������������
#define BOARD_WG		   	 	10,12,225,1   			//������������
#define BOARD_MAC_ADDR      	0xFA,0x8E,0x58,0x6D,0x83,0xBA				//������MAC��ַ

//#define BOARD_IP  			 	192,168,1,252   		//������ip 
//#define BOARD_NETMASK   	 	255,255,255,0   		//��������������
//#define BOARD_WG		   	 	192,168,1,1   			//������������
//#define BOARD_MAC_ADDR      	0,0,0,0,0,1				//������MAC��ַ

#define UDP_LOCAL_PORT     		1030

void UDP_server_init(void);
void UDP_24L01_RX(void);

#endif

