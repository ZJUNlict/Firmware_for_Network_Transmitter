
/***********************************************************************
文件名称：UDP_SERVER.h
功    能：完成UDP的数据收发
编写时间：2013.4.25
编 写 人：北京智嵌物联网电子技术团队
注    意：
***********************************************************************/
#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

/* MAC ADcontinue;continue;DRESS: MAC_ADDR0:MAC_ADDR1:MAC_ADDR2:MAC_ADDR3:MAC_ADDR4:MAC_ADDR5 */
#define MAC_ADDR0   2
#define MAC_ADDR1   3
#define MAC_ADDR2   6
#define MAC_ADDR3   7
#define MAC_ADDR4   9
#define MAC_ADDR5   10
 
/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0   10
#define IP_ADDR1   12
#define IP_ADDR2   225
#define IP_ADDR3   110
   
/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   10
#define GW_ADDR1   12
#define GW_ADDR2   225
#define GW_ADDR3   1  
#define UDP_LOCAL_PORT     		1030 

void UDP_server_init(void);
void udp_demo_senddata(void);

#endif

