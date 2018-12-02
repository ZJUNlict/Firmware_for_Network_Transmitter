/***********************************************************************
文件名称：UDP_SERVER.C
功    能：完成UDP的数据收发
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
#include "main.h"
extern unsigned char tmp_buf[33];
extern unsigned char tmp_buf_rx[33];
extern u8 frequency;	//24L01频率
extern u8 bandwidth;  //24L01带宽
u8 package_success;
u16 check;
struct ip_addr destAddr;
u16_t Port;
struct udp_pcb *pcb_current;		//pcb指针定义为全局变量，方便后续回传数据到上位机

/***********************************************************************
函数名称：udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
功    能：udp数据接收和发送
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：这是一个回调函数，当一个udp段到达这个连接时会被调用
***********************************************************************/
void udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
{
//	struct ip_addr destAddr = *addr; /* 获取远程主机 IP地址 */
	int i=0;
	struct pbuf *p_temp = p;
	unsigned char* p2401;
	pcb_current = pcb;
	destAddr = *addr;
	Port = port;
	//while(p_temp != NULL)
	{
		/******将数据原样返回*******************/
//		udp_sendto(pcb,p_temp,&destAddr,port); /* 将收到的数据再发送出去 */
		p2401 = (unsigned char*) p_temp->payload;
		if(p2401[0]==0xF0)	//配置包解包
		{
			check = 0;
			for(i=0;i<5;i++)
				check =  check+p2401[i];
			check = check&0xFF;
			if(check == p2401[5])
			{
				frequency = p2401[2];
				if(p2401[4]==0x01)
					bandwidth = 0x26;
				else if(p2401[4]==0x02)
					bandwidth = 0x06;
				else if(p2401[4]==0x03)
					bandwidth = 0x0F;
				
				if(p2401[3]==0x02){
					LED_Blink();
					RX_Mode();
				}
			}
		}
		p_temp = p_temp->next;
	}
	pbuf_free(p); 						/* 释放该UDP段 */
}


/***********************************************************************
函数名称：UDP_server_init(void)
功    能：完成UDP服务器的初始化，主要是使得UDP通讯快进入监听状态
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/

void UDP_server_init(void)
{
	struct udp_pcb *pcb;
	pcb = udp_new();								//申请udp控制块
	udp_bind(pcb,IP_ADDR_ANY,UDP_LOCAL_PORT); 	    /* 绑定本地IP地址和端口号（作为udp服务器） */
	udp_recv(pcb,udp_server_recv,NULL); 				/* 设置UDP段到时的回调函数 */

}

//自定义UDP服务器发送数据包函数(此函数以测试能用)
void udp_demo_senddata()
{
	struct pbuf *ptr;
	ptr=pbuf_alloc(PBUF_TRANSPORT,RX_PLOAD_WIDTH,PBUF_RAM); //申请内存
	if(ptr != NULL)
	{
		memcpy(ptr->payload, tmp_buf, RX_PLOAD_WIDTH);  //24L01数据
		udp_sendto(pcb_current, ptr,&destAddr,Port);	  //udp发送数据 
		pbuf_free(ptr);//释放内存
	}
}