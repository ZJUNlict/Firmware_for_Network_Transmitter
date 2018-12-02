//��    �ܣ����UDP�������շ�

#include "main.h"
extern unsigned char tmp_buf[33];
extern unsigned char tmp_buf_rx[33];
extern u8 frequency;	//24L01Ƶ��
extern u8 bandwidth;  //24L01����
u16 check;
extern u8 package_success, package_fail;
struct ip_addr destAddr;
u16_t Port;

//��    �ܣ�udp���ݽ��պͷ���
//ע    �⣺����һ���ص���������һ��udp�ε����������ʱ�ᱻ����
void udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
{
	int i=0;
//	struct ip_addr destAddr = *addr; /* ��ȡԶ������ IP��ַ */
	struct pbuf *p_temp = p;
	unsigned char* p2401;
	
	destAddr = *addr;
	Port = port;
	while(p_temp != NULL)
	{
		//udp_sendto(pcb,p_temp,&destAddr,port); /* ���յ��������ٷ��ͳ�ȥ */
		p2401 = (unsigned char*)p_temp->payload;
		if ((p_temp->len == 6) || (p_temp->len == 25)){
		if(p2401[0]==0xF0)	//���ð����
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
		}
	}
	else {
		LED2_ON;
	}
		p_temp = p_temp->next;
		
	}
	pbuf_free(p); 						/* �ͷŸ�UDP�� */
}


struct udp_pcb *pcb;		//pcbָ�붨��Ϊȫ�ֱ�������������ش����ݵ���λ��
void UDP_server_init(void)	//���ܣ����UDP�������ĳ�ʼ������Ҫ��ʹ��UDPͨѶ��������״̬
{
//	struct udp_pcb *pcb;
	pcb = udp_new();								//����udp���ƿ�
	udp_bind(pcb,IP_ADDR_ANY,UDP_LOCAL_PORT); 	    /* �󶨱���IP��ַ�Ͷ˿ںţ���Ϊudp�������� */
	udp_recv(pcb,udp_server_recv,NULL); 				/* ����UDP�ε�ʱ�Ļص����� */

}

//������24L01���ݺ���
void UDP_24L01_RX(void)
{
	//24L01����or����ģʽ���þ���UDP�ص�������
	while (1)
	{  
		//һֱ�ȴ����ص�����һ����Ӧ�Ͱ����ڽ��յ������ݷ����ȥ��һ���յ����ݾͻش�������
		if(NRF24L01_RxPacket(tmp_buf_rx) == 0)
		{
			udp_demo_senddata(pcb);		//UDP���������ƿ�pcbΪ֮ǰ�����ȫ�ֱ���
		}
	}
}

//�Զ���UDP�������������ݰ�����(�˺����Բ�������)
void udp_demo_senddata(struct udp_pcb *upcb)
{
	struct pbuf *ptr;
	ptr=pbuf_alloc(PBUF_TRANSPORT,strlen((char*)tmp_buf),PBUF_POOL); //�����ڴ�
	if(ptr)
	{
		ptr->payload=(void*)tmp_buf; //24L01����
		udp_sendto(pcb, ptr,&destAddr,Port);	//udp�������� 
		pbuf_free(ptr);//�ͷ��ڴ�
	}
}