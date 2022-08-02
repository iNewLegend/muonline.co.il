#include "StdAfx.h"
#include "TSetup.h"
#include "TCore.h"
#include "TDataServerSocket.h"
#include "TIniFile.h"
#include "TLogToFile.h"
#include "DSXProtocol.h"
#include "TBotSystem.h"
#include "TConfig.h"
#include "OffTrade.h"
#include "RedDragon.h"
#include "EventItemManager.h"
#include "VIPSystem.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # Made By Leo123[BoR] -> GS 99.60T -> Only for MuOnline.co.il

CSetup				g_Setup;
//CMiniDumper 		g_Dumper("GS_DUMP");
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CSetup::CSetup(void)
{
	memset(m_szTemp, 0x00, sizeof(m_szTemp));
	// -----
	g_Config.nNoobServerCsResets = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CSetup::Parse()
{
	g_Timer.Init();
	g_OffTrade.Init();
	g_RedDragon.Init();
	g_VIPSystem.Init();
	LoadItemBag();
	// ----
	HookJMP((DWORD)& CCore::OngObjAdd,				g_GS.ofgObjAddJmp());
	HookJMP((DWORD)& CCore::RecvDataParse,			g_GS.ofRecvDataParseJmp());
	HookJMP((DWORD)& CCore::ProtocolCore,			g_GS.ofPrtocolCoreJmp());
	HookJMP((DWORD)& CCore::OnDisconnect,			g_GS.ofgObjDelJmp());
	HookJMP((DWORD)& CCore::OnTeleport,				g_GS.ofgObjTeleportJmp());
	HookJMP((DWORD)& CCore::OnMoveGate,				g_GS.ofgObjMoveGateJmp());
	HookJMP((DWORD)& CCore::OnPointAdd,				g_GS.ofgObjLevelUpPointAddJmp());
	HookJMP((DWORD)& CCore::OnTraceCancel,			g_GS.ofgObjTradeCancelJmp());
	HookJMP((DWORD)& CCore::gObjAttack,				g_GS.ofgObjAttackJmp());
	HookJMP((DWORD)& CCore::gObjUserDie,			g_GS.ofgObjUserDieJmp());
	HookJMP((DWORD)& CCore::DataSend,				g_GS.ofDataSendJmp());
	HookJMP((DWORD)& CCore::gObjSetCharacter,		g_GS.ofgObjSetCharacterJmp());
	HookJMP((DWORD)& CCore::DGGetWarehouseList,		g_GS.ofDGGetWarehouseListJmp());
	HookJMP((DWORD)& CCore::JGPGetCharList,			g_GS.ofJGPGetCharListJmp());
	HookJMP((DWORD)& CCore::CGPCharacterCreate,		g_GS.ofCGPCharacterCreateJmp());
	HookJMP((DWORD)& CCore::FriendMemoSend,			g_GS.ofFriendMemoSendJmp());
	HookJMP((DWORD)& CCore::GCTradeResponseSend,	g_GS.ofGCTradeResponseSendJmp());
	HookJMP((DWORD)& CCore::CGPShopAnsSoldItem,		g_GS.ofCGPShopAnsSoldItemJmp());
	HookJMP((DWORD)& CCore::CGPShopAnsOpen,			g_GS.ofCGPShopAnsOpenJmp());
	HookJMP((DWORD)& CCore::CGPShopAnsClose,		g_GS.ofCGPShopAnsCloseJmp());
	HookJMP((DWORD)& CCore::CGTradeRequestSend,		g_GS.ofCGTradeRequestSendJmp());
	// ----
	HookJMP((DWORD)& CCore::CGInventoryItemMove,	g_GS.ofCGInventoryItemMoveJmp());
	HookJMP((DWORD)& CCore::CGLiveClient,			g_GS.ofCGLiveClientJmp());
	// ----
	// # Season3
	// ---
	#ifdef SEASAON3
	{
		HookJMP((DWORD)& JGPGetCharList,		g_GS.ofJGPGetCharListJmp());
		HookJMP((DWORD)& SEASON3_DATASEND::DataSend,	g_GS.ofDataSendJmp());
	}	
	#endif
	// ----
	#ifdef GS_99_60T
	{
		// # Custom offset
		// ---
		SetOffset(0x569FFD , (DWORD)& CCore::OnConnect);
		// ----
		HookJMP((DWORD)& CCore::PMoveProc,					g_GS.ofPMoveProcJmp());
		HookJMP((DWORD)& CCore::GDGuildMemberDelResult,		g_GS.ofGDGuildMemberDelResultJmp());
		HookJMP((DWORD)& CCore::GDGuildMemberAddResult,		g_GS.ofGDGuildMemberAddResultJmp());
		HookJMP((DWORD)& CCore::OnCloseClient,				g_GS.ofCloseCliseJmp());
		HookJMP((DWORD)& CCore::ResponErrorCloseClient,		g_GS.ofResponErrorCloseClientJmp());
		HookJMP((DWORD)& CCore::GCJoinResult,				g_GS.ofGCJoinResultJmp());
		HookJMP((DWORD)& CCore::gObjCloseSetEx,				g_GS.ofgObjCloseSetJum());
		HookJMP((DWORD)& CCore::CGGuildRequestResultRecv,	g_GS.ofCGGuildRequestResultRecvJmp());
		HookJMP((DWORD)& CCore::CGPShopReqBuyItem,			g_GS.ofCGPShopReqBuyItemJmp());
		HookJMP((DWORD)& CCore::CGPShopReqSetItemPrice,		g_GS.ofCGPShopReqSetItemPriceJmp());
		HookJMP((DWORD)& CCore::gObjPlayerKiller,			g_GS.ofgObjPlayerKillerJmp());
		HookJMP((DWORD)& CCore::gObjMonsterDieGiveItem,		g_GS.ofgObjMonsterDieGiveItemJmp());
		HookJMP((DWORD)& CCore::CGBuyRequestRecv,			g_GS.ofCGBuyRequestRecvJmp());
		HookJMP((DWORD)& CCore::ShopDataLoad,				g_GS.ofShopDataLoadJmp());
		// ----
		// # Visual Fix
		// ----
		HookJMP((DWORD)& CCore::GCReFillSend,			g_GS.ofGCReFillSendJmp());
		HookJMP((DWORD)& CCore::GCManaSend,				g_GS.ofGCManaSendJmp());
		HookJMP((DWORD)& CCore::GCDamageSend,			g_GS.ofGCDamageSendJmp());
		HookJMP((DWORD)& CCore::GCKillPlayerExpSend,	g_GS.ofGCKillPlayerExpSendJmp());
		// ----
		// # OffTrade
		// ----
		if (g_OffTrade.EnableOff == true)
		{
			HookJMP((DWORD)& COFFTrade::CloseClient2, g_GS.ofCloseClient2Jmp());
			HookJMP((DWORD)& CCore::CSPJoinIdPassRequest, g_GS.ofCSPJoinIdPassRequestJmp());
			HookJMP((DWORD)& CCore::gObjSecondProc, g_GS.ofgObjSecondProcJmp());
		}
		// ----
		// # leo123: 2019-03-17
		// ----
		HookJMP((DWORD)& CCore::gObjSavePetItemInfo, g_GS.ofgObjSavePetItemInfoJmp());
	}
	#else
	{
		// # Castoum Offset
		// ---
		SetOffset(0x60001E , (DWORD)& CCore::OnConnect);
		// ----
		g_Config.isGSCastle = true;
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CSetup::Run()
{
	g_DataServer.Startup(SOCK_TCP, PROTO_TCP);

	// will wait till it has connection to DataServerX
	while(g_DataServer.getStatus() == false) {
		g_DataServer.Connect
		("127.0.0.1", g_Config.nPort);
	} 

	GDSendStartupMSG(g_Config.nServerCode);

	boost::thread workerThread(& CSetup::Worker);

	// Addons

	#ifdef GS_99_62T
	{
		HMODULE hMod= LoadLibraryA("StormCS.dll");
		if (hMod == NULL)
		{
			MessageBoxA(0, "Error to load StormCS",0,0);
		}
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CSetup::MsgBox(const char * szFormat, ...)
{
	va_list pArguments;
	va_start(pArguments, szFormat);
	vsprintf(m_szTemp, szFormat, pArguments);
	va_end(pArguments);
	// ----
	MessageBox(NULL, m_szTemp, "error", MB_OK | MB_APPLMODAL);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CSetup::Worker()
{
	for(;;)
	{
		if(g_DataServer.getStatus() == true)
		{
			g_DataServer.DataMonitor(g_DataServer.getSocket());
			// ----
			Sleep(1);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------