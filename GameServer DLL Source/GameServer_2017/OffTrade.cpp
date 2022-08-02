#include "StdAfx.h"
#include <WinSock2.h>
#include "OffTrade.h"
#include "TMessages.h"
#include "TConfig.h"
#include "User.h"
#include "TDataServerSocket.h"
#include "DSXProtocol.h"
#include "VIPSystem.h"

//==================================================================================================
// Offline Trade System
//==================================================================================================

CRITICAL_SECTION criti;
COFFTrade g_OffTrade;
OFFLINETRADE OfflineShop[OBJECT_MAX_INDEX];


//==========================
// Functions Hook
//==========================
void COFFTrade::Init()
{
#ifdef GS_99_60T
	g_OffTrade.EnableOff = g_Config.IsOffTradeOn;
	g_OffTrade.MapAllow = g_Config.IsOffTradeRestricedMap;
	g_OffTrade.Map1 = g_Config.nOffTradeMapNumber1;
	g_OffTrade.Map2 = g_Config.nOffTradeMapNumber2;
	g_OffTrade.Map3 = g_Config.nOffTradeMapNumber3;
	g_OffTrade.Map1Cost = g_Config.nOffTradeMapNumber1Cost;
	g_OffTrade.Map2Cost = g_Config.nOffTradeMapNumber2Cost;
	g_OffTrade.Map3Cost = g_Config.nOffTradeMapNumber3Cost;
	g_OffTrade.OnlyVIP = g_Config.nOffTradeOnlyVIP;
#endif
}

//==========================
// OffTrade Create
//==========================
void COFFTrade::RequestOfflineTrade(int aIndex)
{
#ifdef GS_99_60T

	_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];

	if (g_DataServer.getStatus() == false)
	{
		g_Msg.Msg(aIndex, "@[OffTrade] DataServer error , please try again later");
	}

	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	if (g_OffTrade.EnableOff == false)
	{
		g_Msg.Msg(aIndex, "@[OffTrade] System is Disabled!");
		return;
	}

	if (gObj->m_bPShopOpen == false)
	{
		g_Msg.Msg(aIndex, "@[OffTrade] You need create Personal Store to use this command");
		return;
	}

	if (MapAllow == true)
	{
		if (gObj->MapNumber != g_OffTrade.Map1 && gObj->MapNumber != g_OffTrade.Map2 && gObj->MapNumber != g_OffTrade.Map3)
		{
			g_Msg.Msg(aIndex, "@[OffTrade] OffTrade work only special maps");
			return;
		}
	}

	if (OnlyVIP == true)
	{
		if (g_VIPSystem.RequestVIPBonus(aIndex, 1) == false || nObject->isVip == false)
		{
			g_Msg.Msg(aIndex, "@[OffTrade] OffTrade work only for VIP members");
			return;
		}
	}

	int price = 0;
	if (gObj->MapNumber == g_OffTrade.Map1) price = g_OffTrade.Map1Cost;
	if (gObj->MapNumber == g_OffTrade.Map2) price = g_OffTrade.Map2Cost;
	if (gObj->MapNumber == g_OffTrade.Map3) price = g_OffTrade.Map3Cost;

	GDOffTradeRequest(aIndex, price, gObj->AccountID);
#endif
	return;
}

void COFFTrade::CreateOfflineTrade(int Type, int aIndex, int Credits, int Code)
{
#ifdef GS_99_60T
	if (Code == 2)
	{
		g_Msg.Msg(aIndex, "[OffTrade] You dont have enought Credits for OffTrade");
		return; 
	}

	OfflineShop[aIndex].IsOffTrade = 1;
	g_GS.CloseClient(aIndex);
#endif
	return;
}
//==========================
// Shop Close
//==========================
void COFFTrade::CGPShopAnsClose(int aIndex, BYTE btResult)
{
#ifdef GS_99_60T
	g_GS.CGPShopAnsClose(aIndex, btResult);


	if (OfflineShop[aIndex].IsOffTrade == 1)
	{
		g_OffTrade.gObjDel(aIndex);
		OfflineShop[aIndex].IsOffTrade = 0;
	}
#endif
}

//==========================
// Client Close
//==========================
void COFFTrade::CloseClient(int aIndex)
{
#ifdef GS_99_60T
	if (aIndex < 0 || aIndex > OBJECT_MAX_INDEX - 1)
	{
		return;
	}

	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if (gObj->Connected == 0)
	{
		return;
	}

	if (OfflineShop[aIndex].IsOffTrade == 1)
	{
		return;
	}
#endif
}

//==========================
// Error Checker
//==========================
void COFFTrade::ResponErrorCloseClient(int aIndex)
{
#ifdef GS_99_60T
	if (aIndex < 0 || aIndex > OBJECT_MAX_INDEX - 1)
	{
		return;
	}

	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if (gObj->Connected == 0)
	{
		return;
	}

	if (OfflineShop[aIndex].IsOffTrade == 1)
	{
		return;		
	}

	//#############################################

	g_GS.ResponErrorCloseClient(aIndex);
#endif
}

//==========================
// Client Close 2
//==========================
void COFFTrade::CloseClient2(_PER_SOCKET_CONTEXT * lpPerSocketContext, int result)
{
#ifdef GS_99_60T
	int index = -1;
	index = lpPerSocketContext->nIndex;

	if (index >= OBJECT_START_INDEX && index < OBJECT_MAX_INDEX)
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(index);
		if (gObj->m_socket != INVALID_SOCKET)
		{
			if (closesocket(gObj->m_socket) == -1)
				if (WSAGetLastError() != WSAENOTSOCK)
					return;
			gObj->m_socket = INVALID_SOCKET;
		}
		g_OffTrade.gObjDel(index);
	}
#endif
}

void COFFTrade::gObjDel(int aIndex)
{
#ifdef GS_99_60T
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if (OfflineShop[aIndex].IsOffTrade == 1)
	{
		return;
	}

	g_GS.gObjDel(aIndex);
#endif
}

void COFFTrade::BuxConvert(char *buf, int size)
{
	for (int n = 0; n<size; n++) buf[n] ^= (char)bBuxCode[n%MAX_BUXCCODE];
}

void COFFTrade::OffTradeLogin(int aIndex, PMSG_IDPASS* lpMsg)
{
#ifdef GS_99_60T
	char AccountID[11];
	AccountID[10] = 0;
	char Password[11];
	Password[10] = 0;

	memcpy(AccountID, lpMsg->Id, sizeof(lpMsg->Id));
	memcpy(Password, lpMsg->Pass, sizeof(lpMsg->Pass));
	BuxConvert(AccountID, 10);
	BuxConvert(Password, 10);

	for (int i = OBJECT_START_INDEX; i<OBJECT_MAX_INDEX; i++)
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

		// IF gObj is with the same username
		if (strcmp(AccountID, gObj->AccountID) == 0 && gObj->Connected == 3 && OfflineShop[i].IsOffTrade == 1)
		{
			g_GS.GJPUserClose(gObj->AccountID);
			g_GS.gObjDel(i);
			OfflineShop[i].IsOffTrade = 0;
			g_GS.CloseClient(i);
			break;
		}
	}
#endif
}

