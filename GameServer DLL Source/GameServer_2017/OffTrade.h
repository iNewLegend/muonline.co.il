#pragma once

#include "StdAfx.h"

#define MAX_BUXCCODE				3

static BYTE	bBuxCode[MAX_BUXCCODE] = { 0xFC, 0xCF, 0xAB };


void OffTradeLogin(int aIndex, LPBYTE aRecv);

class COFFTrade
{
public:

	void Init();
	void RequestOfflineTrade(int aIndex);
	void CreateOfflineTrade(int Type, int aIndex, int Credits, int Code);
	void CGPShopAnsClose(int aIndex, BYTE btResult);
	void CloseClient(int aIndex);
	void ResponErrorCloseClient(int aIndex);
	void gObjDel(int aIndex);
	static void CloseClient2(_PER_SOCKET_CONTEXT * lpPerSocketContext, int result);
	static void OffTradeLogin(int aIndex, PMSG_IDPASS* lpMsg);
	static void BuxConvert(char *buf, int size);	

	bool EnableOff;
	bool MapAllow;
	bool MessageAll;
	bool OnlyVIP;
	int Map1;
	int Map2;
	int Map3;
	int Map1Cost;
	int Map2Cost;
	int Map3Cost;

};

extern COFFTrade g_OffTrade;

struct OFFLINETRADE
{
	int IsOffTrade;
}; extern OFFLINETRADE OfflineShop[OBJECT_MAX_INDEX];


