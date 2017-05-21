#include "packet_func.h"

int iLoop = 0;

int mygetch(void)
{
	struct termios oldt,
				   newt;
	int ch;

	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

	return ch;
}

void Stop_Capture(int iNum)
{
	if(iLoop != 0)
	{
		iLoop = 0;
		printf("\n\nTerminated...\n\n");
	}
}

void Capture(int iPort, pcap_t * stpDS, struct pcap_pkthdr * stpInfo)
{
	unsigned char const *   ucpData;
	struct tcphdr *         stTcp;
	struct ip *             stpIp;

	while(iLoop)
	{
		ucpData = pcap_next(stpDS, stpInfo);

		if(ucpData == 0)
		{
			continue;
		}

		if( 0 == Check_Header(ucpData) )
		{
			continue;
		}
		stpIp = (struct ip *) (ucpData + sizeof(struct ether_header));
		stTcp = (struct tcphdr *)(ucpData + sizeof(struct ether_header)
				+ (  (*(ucpData + sizeof(struct ether_header)))&0x0F  )*4);
		if( 0 == Check_Port(stTcp, iPort) )
		{
			continue;
		}

		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		Print_TcpCap(stpIp, stTcp);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		if( iLoop > 0 )
		{
			iLoop--;
		}
	}
	printf("Stop Packet Capture...\n\n");
}

void Single_Capture(int iPort, pcap_t * stpDS, struct pcap_pkthdr * stpInfo)
{
	unsigned char const *   ucpData;
	struct tcphdr *         stTcp;
	struct ip *             stpIp;
	char cIn;

	while(iLoop)
	{
		ucpData = pcap_next(stpDS, stpInfo);

		if(ucpData == 0)
		{
			continue;
		}
		
		iLoop = 0;

		if( 0 == Check_Header(ucpData) )
		{
			continue;
		}
		stpIp = (struct ip *) (ucpData + sizeof(struct ether_header));
		stTcp = (struct tcphdr *)(ucpData + sizeof(struct ether_header)
				+ (  (*(ucpData + sizeof(struct ether_header)))&0x0F  )*4);
		if( 0 == Check_Port(stTcp, iPort) )
		{
			continue;
		}

		putchar('\n');
		printEther(ucpData);
		putchar('\n');
		printIP(stpIp);
		putchar('\n');
		printTcp(stTcp);

		printf("Print Hexa?[Y/N]: ");
		cIn = mygetch();
		cIn = toupper(cIn);

		putchar('\n');
		if(cIn != 'N')
		{
			Print_Hexa(ucpData);
		}

		break;
	}
}

