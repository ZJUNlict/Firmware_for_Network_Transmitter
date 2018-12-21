//功    能：完成UDP的数据收发

#include "main.h"
extern unsigned char tmp_buf[33];
extern unsigned char tmp_buf_rx[33];
extern u8 frequency;	//24L01频率
extern u8 bandwidth;  //24L01带宽
u16 check;
extern u8 package_success, package_fail;
struct ip_addr destAddr;
u16_t Port;

//功    能：udp数据接收和发送
//注    意：这是一个回调函数，当一个udp段到达这个连接时会被调用
void udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
{
	int i=0;
	int Configuration_Delay=0;
//	struct ip_addr destAddr = *addr; /* 获取远程主机 IP地址 */
	struct pbuf *p_temp = p;
	unsigned char* p2401;
	
	destAddr = *addr;
	Port = port;
	while(p_temp != NULL)
	{
		//udp_sendto(pcb,p_temp,&destAddr,port); /* 将收到的数据再发送出去 */
		p2401 = (unsigned char*)p_temp->payload;
		if ((p_temp->len == 6) || (p_temp->len == 25)){
		if(p2401[0]==0xF0)	//配置包解包
		{
			check = 0;
			for(i=0;i<5;i++){
				check =  check + p2401[i];
			}
			check =  check & 0xFF;
			if(check==p2401[5])
			{
				frequency = p2401[1];
				if(p2401[4]==0x01)
					bandwidth = 0x26;
				else if(p2401[4]==0x02)
					bandwidth = 0x06;
				else if(p2401[4]==0x03)
					bandwidth = 0x0F;
				if(p2401[3]==0x01){
					TX_Mode();
					Configuration_Delay=10000;
					while (Configuration_Delay>=0){
						Configuration_Delay--;
					}
					LED_Blink();
				}
			}
		}
		else
		{
			memcpy((char*)tmp_buf,p2401,25);
			if(NRF24L01_TxPacket(tmp_buf) == TX_OK){
				package_success++;
				if (package_success==32){
					LED1_OFF;
				}
				if (package_success==64){
					LED1_ON;
					package_success=0;
				}
			}
			else{
					LED3_ON;					//NRF24L01P Transmit Fail
			}
		}
	}
	else {
		LED2_ON;
	}
		p_temp = p_temp->next;
	}
	LED4_ON;
	pbuf_free(p); 						/* 释放该UDP段 */
}


struct udp_pcb *pcb;		//pcb指针定义为全局变量，方便后续回传数据到上位机
void UDP_server_init(void)	//功能：完成UDP服务器的初始化，主要是使得UDP通讯快进入监听状态
{
//	struct udp_pcb *pcb;
	pcb = udp_new();								//申请udp控制块
	udp_bind(pcb,IP_ADDR_ANY,UDP_LOCAL_PORT); 	    /* 绑定本地IP地址和端口号（作为udp服务器） */
	udp_recv(pcb,udp_server_recv,NULL); 				/* 设置UDP段到时的回调函数 */

}

//主接收24L01数据函数
void UDP_24L01_RX(void)
{
	//24L01发送or接收模式配置均在UDP回调函数里
	while (1)
	{  
		//一直等待，回调函数一有响应就把网口接收到的数据发射出去，一接收到数据就回传给电脑
		if(NRF24L01_RxPacket(tmp_buf_rx) == 0)
		{
			udp_demo_senddata(pcb);		//UDP服务器控制块pcb为之前定义的全局变量
		}
	}
}

//自定义UDP服务器发送数据包函数(此函数以测试能用)
void udp_demo_senddata(struct udp_pcb *upcb)
{
	struct pbuf *ptr;
	ptr=pbuf_alloc(PBUF_TRANSPORT,strlen((char*)tmp_buf),PBUF_POOL); //申请内存
	if(ptr)
	{
		ptr->payload=(void*)tmp_buf; //24L01数据
		udp_sendto(pcb, ptr,&destAddr,Port);	//udp发送数据 
		pbuf_free(ptr);//释放内存
	}
}
