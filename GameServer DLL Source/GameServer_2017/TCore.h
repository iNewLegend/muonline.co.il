//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef CORE_H
#define CORE_H
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "TMessages.h"
#include <iostream>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "..\..\include\DSX_protocol.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define PACKET_ENCYRPTION 1
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define REFRESH_INVENTORY _beginthread(GCTeleportSendWorker, 4 , (LPVOID)aIndex)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum GS_PACKET_HEADERS
{
	HEAD_CHAT		= 0x00,
	HEAD_WHISP		= 0x02,
	HEAD_ONMAP		= 0x03,
	HEAD_REFILL		= 0x26,
	HEAD_MANASEND   = 0x27,
	HEAD_LAHAPMIX	= 0xBC,
	HEAD_NEWAUTH	= 0xEE,
	HEAD_DUELREQ	= 0xAC,
	HEAD_ATTACK		= ATTACK_PROTOCOL,
	HEAD_MOVE		= MOVE_PROTOCOL,
	HEAD_IMPORTANT	= 0xF3,
	HEAD_ACCOUNTTEST= 0xFE,
	HEAD_CASTOUMBT	= 0xFF,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum GS_SUB_PACKET_HEADERS_IMPORTANT
{
	HEAD_IMPORTANT_GETCHARLIST = 0x00,
	HEAD_IMPORTANT_CREATECHAR,
	HEAD_IMPORTANT_DELCHAR,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CCore
{
public:
	static bool isFirstTimeConnect;
	// ----
	static void handlePackt				(LPBYTE Packet, int Size);
	static void RecvDataParse			(_PER_IO_CONTEXT * lpIOContext, int uIndex);
	// ----
	static void ProtocolCore			(DWORD protoNum,LPBYTE aRecv,int aLen,int aIndex,DWORD Encrypt,DWORD Serial);
	static void OnConnect				(int aIndex);
	static void OnDisconnect			(int aIndex);
	static void OnCloseClient			(int aIndex);
	static void ResponErrorCloseClient	(int aIndex);
	static BOOL OngObjAdd				(SOCKET aSocket, char * ip, int aIndex);
	// ----
	static void OnTeleport				(int aIndex, int map, int x, int y);
	static BOOL OnMoveGate				(int aIndex, int gt);
	static BOOL OnPointAdd				(BYTE type, OBJECTSTRUCT * lpObj);
	static void OnTraceCancel			(int aIndex);
	static void PMoveProc				(DWORD unk,  int aIndex);
	// ----
	static BOOL gObjAttack				(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj, DWORD lpMagic, BOOL magicsend, BYTE MSBFlag, int AttackDamage, BOOL bCombo);
	static void gObjUserDie				(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj);
	static void gObjPlayerKiller		(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj);
	static void gObjMonsterDieGiveItem	(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj);
	// ----
	static void CGInventoryItemMove		(PMSG_INVENTORYITEMMOVE * lpMsg, int aIndex);
	static void GDGuildMemberDelResult	(SDHP_GUILDMEMBERDEL_RESULT * lpMsg);
	static void GDGuildMemberAddResult	(SDHP_GUILDMEMBERADD_RESULT * lpMsg);
	static void CGPCharDel				(PMSG_CHARDELETE * lpMsg,int aIndex);
	static BOOL gObjSetCharacter		(DWORD Msg, int aIndex);
	static void DGGetWarehouseList		(SDHP_GETWAREHOUSEDB_SAVE * lpMsg);
	// ----
	static BOOL DataSend				(int aIndex, UCHAR * lpMsg, DWORD dwSize);
	static void GCJoinResult			(BYTE result, int aIndex);
	static void JGPGetCharList  		(UCHAR * lpRecv);
	static void CGPCharacterCreate		(PMSG_CHARCREATE * lpMsg, int aIndex);
	static void gObjCloseSetEx			(int aIndex,int Flag);
	static void FriendMemoSend			(PMSG_FRIEND_MEMO * lpMsg, int aIndex);
	static void CGGuildRequestResultRecv(PMSG_GUILDQRESULT * lpMsg, int aIndex);
	// ----
	static void GCTradeResponseSend		(BYTE response, int aIndex, LPSTR id, WORD level, int GuildNumber);
	static void CGPShopReqSetItemPrice	(PMSG_REQ_PSHOP_SETITEMPRICE * lpMsg, int aIndex);
	static void CGPShopReqBuyItem		(PMSG_REQ_BUYITEM_FROM_PSHOP * lpMsg, int aSourceIndex);
	static void CGPShopAnsSoldItem		(int aSourceIndex, int aTargetIndex, int iItemPos);
	static void CGPShopAnsOpen			(int aIndex, BYTE btResult);
	static void CGPShopAnsClose			(int aIndex, BYTE btResult);
	static void CGTradeRequestSend		(PMSG_TRADE_REQUEST * lpMsg, int aIndex);
	// ----
	static void CGLiveClient			(PMSG_CLIENTTIME * lpClientTime, int aIndex);
	// ----
	static void gObjSavePetItemInfo		(int aIndex, int inventype);
	// ----
	static void	GCReFillSend			(int aIndex, int Life, BYTE Ipos);
	static void GCManaSend				(int aIndex, int Mana, BYTE Ipos, BYTE flag, int BP);
	static void GCDamageSend			(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage);
	static void GCKillPlayerExpSend		(int aIndex, int TargetIndex, int exp, int AttackDamage, int MSBFlag);
	// ----
	static void CGBuyRequestRecv		(PMSG_BUYREQUEST * lpMsg, int aIndex);
	static bool ShopDataLoad			();
	// ----
	static void  CSPJoinIdPassRequest	(PMSG_IDPASS *lpMsg, int aIndex);
	static void  gObjSecondProc			();
	// ----
	static void GCTeleportSendWorker	(LPVOID lParam)
	{
		int aIndex = (int)lParam;
		// ----
		Sleep(6000);
		// ----
		g_GS.GCItemListSend(aIndex);
		g_GS.GCEquipmentSend(aIndex);
	};
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

extern int g_GMLOGINID;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif /* CORE_H */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

