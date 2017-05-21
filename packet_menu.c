#include "packet_func.h"

int Select_Menu(void)
{
	int iCmd;

	printf("========================== Menu ======================\n");
	printf(" 1. Single / 2.Number / 3. All / 4. Setting / 5. End /\n");

	while(1)
	{
		iCmd = mygetch();
		if( ('0' < iCmd)&&(iCmd < '6') )
		{
			break;
		}
	}

	return iCmd;
}

int Select_Port(void)
{
	unsigned char caPort[6];
	int iPort;
	int iRet;

	write(1, "Input Port Number(0: all port): "
			, sizeof("Input Port Number(0: all port): "));

	while(1)
	{
		iRet = read(0, caPort, 6);
		caPort[iRet-1]=0;
		if(caPort[0] == '0')
		{
			return 0;
		}
		iPort = atoi(caPort);
		if( iPort != 0 )
		{
			break;
		}
	}
	putchar('\n');

	return iPort;
}

int Select_Number(void)
{
	unsigned char caNum[6];
	int iNum;
	int iRet;

	write(1, "Input Number(0: end): "
			, sizeof("Input Number(0: end): "));

	while(1)
	{
		iRet = read(0, caNum, 6);
		caNum[iRet-1]=0;
		if(caNum[0] == '0')
		{
			return 0;
		}
		iNum = atoi(caNum);
		if( iNum != 0 )
		{
			break;
		}
	}

	return iNum;
}

int Select_Timeout(void)
{
	unsigned char caNum[6];
	int iNum;
	int iRet;

	write(1, "Set Timeout(ms)(0: infinite): "
			, sizeof("Set Timeout(ms)(0: infinite): "));

	while(1)
	{
		iRet = read(0, caNum, 6);
		caNum[iRet-1]=0;
		if(caNum[0] == '0')
		{
			return 0;
		}
		iNum = atoi(caNum);
		if( iNum != 0 )
		{
			break;
		}
	}

	return iNum;
}
