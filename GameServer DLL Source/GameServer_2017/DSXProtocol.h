//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "..\..\include\DSX_protocol.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void vDSProtocolCore					(unsigned char * pRecv, int aLen);
void vDSSubProtocolCoreEXERCISESYSTEM	(unsigned char * pRecv, VDS_SUBPACKET_EXERCISESYSTEM_HEADERS Head);
void vDSSubProtocolCoreVOTESYSTEM		(unsigned char * pRecv, VDS_SUBPACKET_VOTESYSTEM_HEADERS Head);
void vDSSubProtocolCoreRUNEVENT			(unsigned char * pRecv, VDS_SUBPACKET_RUNEVENT_HEADERS Head); 
void vDSSubProtocolCoreWROTEEVENT		(unsigned char * pRecv, VDS_SUBPACKET_WROTEEVENT_HEADERS Head); 
void vDSSubProtocolCoreCONFUSEEEVENT	(unsigned char * pRecv, VDS_SUBPACKET_CONFUSEEVENT_HEADERS Head);
void vDSSubProtocolCoreLOTTERYEVENT		(unsigned char * pRecv, VDS_SUBPACKET_LOTTERYEVENT_HEADERS Head);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// # GameServer -> DataServerX
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDExtraInfo				(int aIndex, char * sAccountID);
void GDSBanSet					(char * GMName, char * PlayerName, int Days, int ibanReason, int isBanAllUsers);
void GDGoRequest				(int aIndex, int Target, int Credits, char * AccountID);
void GDKandumRequest			(int aIndex, int Credits, char * AccountID);
void GDSendPost					(char * Name, int Credits, char * Message, char * AccountID);
void GDSendPostGM				(char * Name, char * Message, char * AccountID);
void GDSendGuildMsg				(std::string Name, std::string GuildName, std::string Message);
void GDSendStartupMSG			(BYTE ServerCode);
void DGInfoMsg					(MSG_R_INFO * lpMsg);
void GDSendInfoMsg				(int aIndex, char * Name);
void GDSendInfoStateMsg			(char * szName, bool state);
void GDSendBuyVipMsg			(std::string szAccountID, std::string szNick, int VipLevel, int VipDays, int VipPrice);
void GDSetBanOnChar				(std::string szGameMaster, std::string szNick, bool status, int ID);
void GDSetBanOnAcc				(std::string szGameMaster, std::string szAccountID, bool status, int ID);
void GDAdvMsgMsg				(std::string PakahName);
void GDRunEventWinnerSend		(int aIndex);
void GDWroteEventWinnerSend		(int aIndex);
void GDConfuseEventWinnerSend(int aIndex);
void GDSendQuery				(std::string Query);
void GDLotteryEventWinnerSend	(int aIndex);
void GDLotteryEventSenderSend	(int aIndex, UINT Number);
void GDSUnBanSet				(char * GMName, char * PlayerName, int ibanReason);
void GDCheckAccess_Jump			(int srcIndex, char * TargetName, BYTE TeleportID, char * command);
void GDCheckAccess_Come			(int aIndex, char * TargetName, char * command);
void GDCheckAccess_Move			(int aIndex, char * command, char * Message);
void GDCheckAccess_GreenMSG		(int aIndex, char * Name, char * command);
void GDMsgStatus				(char * Name, int time, int status);
void GDLogHack					(int aIndex, char * Name);
void GDCharacterGotOnlineOrOffline(int aIndex, char * sAccountID, OFFLINE_ONLINE_STATUS status);
void GDCharacterGotDelOrCreated	(int aIndex, char * sAccountID, char * sName, OFFLINE_ONLINE_STATUS status);
void GDEventCommandGMS			(int aIndex);
void GDCrewMsgReq				(int aIndex);
void GDMarryUpdate				(char * MarryName1, char * MarryName2, bool MarrigeStatus);
void GDSkinCheck				(char * GMName, char * AccountID, char * szName, int MID);
void GDInvisibleChange			(char * GMName, char * AccountID, bool status);
void GDInvisibleCrewChange		(char * GMName, char * AccountID, bool status);
void GDAssistCheckRequest		(char * AssistName, char * MemberName, char * GuildName, int Type);
void GDKickCheckRequest			(char * AssistName, char * MemberName, char * GuildName);
void GDSetAssistCheckRequest	(char * ManagerName, char * GuildName, BYTE Type);
void GDGuildJoinRequestByAssist	(char * AssistName, char * ReqName);
void GDKillEventCheck			(char * Name, char * tName);
void GDShopBuyItemRequest		(std::string sAccountId, std::string sName, int iShopId, BYTE bProductPos, int iPrice);
void GDOffTradeRequest			(int aIndex, int Credits, char * AccountID);
void GDRedDragonRequest			(int aIndex, char * AccountID);
void GDFixLevelBugRequest		(int aIndex, char * szName);
void GDSendReportMsg			(char * ReporterName, char * Name, char * Reason);
void GDAntiHackProcessNotify	(std::string sAccountId, std::string sIpAddress, std::string sProcess, ULONGLONG uChecksum);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// # DataServerX -> GameServer
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void DGShopBuyItemResult		(MSG_SHOP_BUY_ITEM_RESULT * pMsg);
void DGSendMessageAllRecive		(MSG_R_GLOAL_MSG* pMsg);
