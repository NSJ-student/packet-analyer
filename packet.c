#include "packet_func.h"

int main(void)
{
	char* 					cpNICName;
	char 					caErrMSG[PCAP_ERRBUF_SIZE];
	int 					iCnt;
	unsigned char const * 	ucpData;
	pcap_t* 				stpDS;
	struct pcap_pkthdr 		stInfo;
	int iCmd;
	int iPort, iNum;

	signal(SIGINT, Stop_Capture);

	cpNICName = pcap_lookupdev(caErrMSG);

	if(0 == cpNICName)
	{
		printf("ERRMSG  : [%s]\n",caErrMSG);
		return 100;
	}

	iPort = Select_Port();
	stpDS = pcap_open_live(cpNICName, ETH_DATA_LEN, 1, 100, caErrMSG);

	printf("Packet Monitoring Start....\n");


	while(1)
	{
		iCmd = Select_Menu();

		switch(iCmd)
		{
			case '1':	printf("port = %d\n", iPort);
						iLoop = 1;
						Single_Capture(iPort, stpDS, &stInfo);
						break;
			case '2': 	iNum = Select_Number();
						printf("port = %d/ Num = %d\n", iPort, iNum);
						iLoop = iNum;
						Capture(iPort, stpDS, &stInfo);	
					  	break;
			case '3':   printf("port = %d\n", iPort);
						iLoop = -1;
						Capture(iPort, stpDS, &stInfo);
						break;
			case '4':	iPort = Select_Port();
						break;
			defualt: break;
		}
		if(iCmd == '5')
		{
			break;
		}
	}

	printf("Packet Monitoring End....\n");
	pcap_close(stpDS);

	return 0;
}
