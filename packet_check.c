#include "packet_func.h"

int Check_Header(unsigned char const * ucpData)
{
	if(ETH_P_IP != ntohs(*(unsigned short*)(ucpData+12)))
	{
		return 0;
	}
	if(IPPROTO_TCP != *(ucpData+23))
	{
		return 0;
	}

	return 1;
}

int Check_Port(struct tcphdr * stTcp, int iPort)
{
	if( iPort != 0)
	{
		if( iPort != ntohs(stTcp -> source) )
		{
			if(  iPort != ntohs(stTcp -> dest)  )
			{
				return 0;
			}
		}
	}

	return 1;
}
