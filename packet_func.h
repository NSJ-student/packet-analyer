#ifndef __PACKET_FUNC_H__
#define __PACKET_FUNC_H__

#include <stdio.h>
#include <netinet/in.h>
#include <pcap/pcap.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

#include <termios.h>
#include <unistd.h>

#include <signal.h>
#include <stdlib.h>

#include <ctype.h>

#define PORT    7779

extern int iLoop;

int mygetch(void);

void Stop_Capture(int);

int Select_Menu(void);
int Select_Port(void);
int Select_Number(void);
int Select_Timeout();

void All_Capture(int iPort, pcap_t * stpDS, struct pcap_pkthdr * stpInfo);
void Capture(int iPort, pcap_t * stpDS, struct pcap_pkthdr * stpInfo);

void Print_TcpCap(struct ip *, struct tcphdr * stTcp);
void Print_Hexa(unsigned char const * ucpData);
int Check_Header(unsigned char const * ucpData);
int Check_Port(struct tcphdr * stTcp, int iPort);

void printIP(const void *vp);
void printEther(const void *vp);
void printTcp(const void *vp);

#endif /*__PACKET_FUNC_H__*/
