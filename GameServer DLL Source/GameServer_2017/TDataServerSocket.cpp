#include "stdafx.h"
#include "TDataServerSocket.h"
#include "DSXProtocol.h"
#include "TSetup.h"
#include "TLogToFile.h"
#include "TConfig.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # Made By f1x

CDataServerSocket g_DataServer;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CDataServerSocket::OnConnect(const char * sIpAddr, int aPort)
{
	GDSendStartupMSG(g_Config.nServerCode);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CDataServerSocket::OnReceive(SOCKET uSocket, sockaddr_in InetSenderAddr, char *pRecv, int aLen)
{
	int aTotalLen	= 0;
	int uPacketLen	= 0;
	// ----
	do
	{
		switch(pRecv[0])
		{
			case 1:
			{
				MSG_HEADER * lpHead = (MSG_HEADER * ) pRecv;

				uPacketLen			 = lpHead->Len;
			}
			break;

			case 2:
			{
				MSG_HEADER2 * lpHead = (MSG_HEADER2 * ) pRecv;

				uPacketLen			 = lpHead->Len;
			}
			break;


			case 3:
			{
				MSG_HEADER3 * lpHead = (MSG_HEADER3 * ) pRecv;

				uPacketLen			 = lpHead->Len;
			}
			break;

			case 4:
			{
				MSG_HEADER4 * lpHead = (MSG_HEADER4 * ) pRecv;

				uPacketLen			 = lpHead->Len;
			}
			break;

			default:
			{
				return;
			}
			break;
		}
		// ----
		UCHAR *pTmpRecv		= new unsigned char[aLen];
		// ----
		memcpy(pTmpRecv, & pRecv[aTotalLen], uPacketLen);
		// ----
		vDSProtocolCore(pTmpRecv, uPacketLen);
		// ----
		delete [] pTmpRecv;
		// ----
		aTotalLen += uPacketLen;
	}
	while(aTotalLen < aLen);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CDataServerSocket::OnClose(SOCKET uSocket)
{
	Cleanup();
	// ----
	Startup(SOCK_TCP, PROTO_TCP);
	// ----
	while(getStatus() == false)
	{
		Connect("127.0.0.1", g_Config.nPort);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int CDataServerSocket::DataSend(unsigned char *pMsg, int aLen)
{
	int iReturn = 0;
	// ----
	if(getStatus() == true)
	{
		 iReturn = send(getSocket(), (const char*)pMsg, aLen, 0);
	}
	// ----
	return iReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------