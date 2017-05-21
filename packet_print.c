#include "packet_func.h"

void Print_TcpCap(struct ip * stpIp, struct tcphdr * stTcp)
{
	printf("[%s : %d] ---> "
			, inet_ntoa(stpIp -> ip_src)
			, ntohs(stTcp -> source)
		  );

	printf("[%s : %d]\n"
			, inet_ntoa(stpIp -> ip_dst)
			, ntohs(stTcp -> dest)
		  );
	printf("----------------------------------------------------\n");

	printf("SYN[%d] ACK[%d] FIN[%d] Seq[%010u] Ack[%010u]\n"
			, stTcp -> syn
			, stTcp -> ack
			, stTcp -> fin
			, ntohl(stTcp -> seq)
			, ntohl(stTcp -> ack_seq)
		  );

	return;
}

void printIP(const void *vp)
{
	const struct ip *v = vp;

	printf("-------- IP Header ---------\n");
	printf("IP version      : %d \n", v->ip_v);
	printf("Header Length   : %d byte \n", v->ip_hl * 4);
	printf("Type of Service : 0x%02X \n", v->ip_tos);
	printf("Total Length    : %d byte \n", ntohs(v->ip_len));
	printf("ID              : %d \n", v->ip_id);
	printf("TTL             : %d \n", v->ip_ttl);


	printf("Src IP          : %s \n", inet_ntoa(v->ip_src));
	printf("Dst IP          : %s \n", inet_ntoa(v->ip_dst));

	return;
}

void printEther(const void *vp)
{
	int iCnt;

	printf("-------- Ethernet Header ---------\n");
	printf("Dest MAC   : ");
	for(iCnt = 0; iCnt < ETH_ALEN; iCnt++)
	{
		printf("%02X", ((struct ether_header *)vp)->ether_dhost[iCnt]);
		printf(":");
	}
	printf("\b \n");

	printf("Src  MAC   : ");
	for(iCnt = 0; iCnt < ETH_ALEN; iCnt++)
	{
		printf("%02X", ((struct ether_header *)vp)->ether_shost[iCnt]);
		printf(":");
	}
	printf("\b \n");

	return;
}
void printTcp(const void *vp)
{
	struct tcphdr * stTcp = (struct tcphdr *)vp;

	printf("-------- TCP Header ---------\n");
	printf("Src Port : %d\n", ntohs(stTcp -> source ));
	printf("Dest Port: %d\n", ntohs(stTcp -> dest ));


	printf("SYN[%d] ACK[%d] FIN[%d]\n"
			, stTcp -> syn
			, stTcp -> ack
			, stTcp -> fin);
	printf("Seq[%010u] Ack[%010u]\n"
			, ntohl(stTcp -> seq)
			, ntohl(stTcp -> ack_seq));
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

}

void Print_Hexa(unsigned char const * aucpData)
{
	int i;
	int j = 0;
	unsigned char * ucpData = (unsigned char *)aucpData;

	printf("===============================================================================\n");
	for(j=0; j<5; j++ )
	{
		printf("0x%0x08X  ", ucpData);
		for(i=0; i<16; i++, ucpData++)
		{
			printf("%02X ", *ucpData);
		}

		ucpData = ucpData-16;
		putchar(' ');
		for(i=0; i<16; i++, ucpData++)
		{
			if(*ucpData >= ' ')
			{
				if(*ucpData <= 127)
				{
					printf("%c", *ucpData);
					continue;
				}
			}
			putchar('.');
		}
		putchar('\n');
	}
	printf("===============================================================================\n\n");

	return;
}
