/***********************************************************************
�ļ����ƣ�UDP_SERVER.C
��    �ܣ����UDP�������շ�
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "main.h"
extern unsigned char tmp_buf[33];
extern unsigned char tmp_buf_rx[33];
extern u8 frequency;	//24L01Ƶ��
extern u8 bandwidth;  //24L01����
u8 package_success;
u16 check;
struct ip_addr destAddr;
u16_t Port;
struct udp_pcb *pcb_current;		//pcbָ�붨��Ϊȫ�ֱ�������������ش����ݵ���λ��

/***********************************************************************
�������ƣ�udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
��    �ܣ�udp���ݽ��պͷ���
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺����һ���ص���������һ��udp�ε����������ʱ�ᱻ����
***********************************************************************/
void udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
{
//	struct ip_addr destAddr = *addr; /* ��ȡԶ������ IP��ַ */
	int i=0;
	struct pbuf *p_temp = p;
	unsigned char* p2401;
	pcb_current = pcb;
	destAddr = *addr;
	Port = port;
	//while(p_temp != NULL)
	{
		/******������ԭ������*******************/
//		udp_sendto(pcb,p_temp,&destAddr,port); /* ���յ��������ٷ��ͳ�ȥ */
		p2401 = (unsigned char*) p_temp->payload;
		if(p2401[0]==0xF0)	//���ð����
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
	pbuf_free(p); 						/* �ͷŸ�UDP�� */
}


/***********************************************************************
�������ƣ�UDP_server_init(void)
��    �ܣ����UDP�������ĳ�ʼ������Ҫ��ʹ��UDPͨѶ��������״̬
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/

void UDP_server_init(void)
{
	struct udp_pcb *pcb;
	pcb = udp_new();								//����udp���ƿ�
	udp_bind(pcb,IP_ADDR_ANY,UDP_LOCAL_PORT); 	    /* �󶨱���IP��ַ�Ͷ˿ںţ���Ϊudp�������� */
	udp_recv(pcb,udp_server_recv,NULL); 				/* ����UDP�ε�ʱ�Ļص����� */

}

//�Զ���UDP�������������ݰ�����(�˺����Բ�������)
void udp_demo_senddata()
{
	struct pbuf *ptr;
	ptr=pbuf_alloc(PBUF_TRANSPORT,RX_PLOAD_WIDTH,PBUF_RAM); //�����ڴ�
	if(ptr != NULL)
	{
		memcpy(ptr->payload, tmp_buf, RX_PLOAD_WIDTH);  //24L01����
		udp_sendto(pcb_current, ptr,&destAddr,Port);	  //udp�������� 
		pbuf_free(ptr);//�ͷ��ڴ�
	}
}