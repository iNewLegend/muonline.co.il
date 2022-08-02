//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

#include "GIOCPHandler.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "..\..\include\DSX_protocol.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void	protocolCore	(TIOCPHandler * h, uint64_t cid, UCHAR * Packet, int PacketLen);
//-----------------------------------------------------------------------------------------------------------------------

void	startupMsg		(TIOCPHandler * h, uint64_t cid, MSG_STARTUP * lpMsg);
void	extraInfoMsg	(TIOCPHandler * h, uint64_t cid, MSG_S_EXTRAINFO * lpMsg);
void	goMsg			(TIOCPHandler * h, uint64_t cid, MSG_S_GO * lpMsg);
void	kandumMsg		(TIOCPHandler * h, uint64_t cid, MSG_S_KANDUM * lpMsg);
void	noticeMsg		(TIOCPHandler * h, uint64_t cid, MSG_S_POST * lpMsg);
void	noticeMsgGM		(TIOCPHandler * h, uint64_t cid, MSG_S_POST * lpMsg);
void	guildMsg		(TIOCPHandler * h, uint64_t cid, MSG_GUILD * lpMsg);
void	banMsg			(TIOCPHandler * h, uint64_t cid, MSG_BAN	* lpMsg);
void	infoMsg			(TIOCPHandler * h, uint64_t cid, MSG_S_INFO * lpMsg);
void	infoStateMsg	(TIOCPHandler * h, uint64_t cid, MSG_INFO_STATE * lpMsg);
void	CrewMsg			(TIOCPHandler * h, uint64_t cid, MSG_CREW * lpMsg);
void	delCharMsg		(TIOCPHandler * h, uint64_t cid, MSG_S_DELCHAR * lpMsg);
void	buyVipMsg		(TIOCPHandler * h, uint64_t cid, MSG_BUY_VIP_REQUEST	* lpMsg);
void	banOnCharMsg	(TIOCPHandler * h, uint64_t cid, MSG_BAN_CHAR * lpMsg);
void	banOnAccMsg		(TIOCPHandler * h, uint64_t cid, MSG_BAN_ACC * lpMsg);
void	advMsgMsg		(TIOCPHandler * h, uint64_t cid, MSG_ADVMSG * lpMsg);
void	doQueryMsg		(TIOCPHandler * h, uint64_t cid, MSG_DOQUERY * lpMsg);
void	ReportMsg		(TIOCPHandler * h, uint64_t cid, MSG_REPORT * lpMsg);

// roye access
void	unbanMsg				(TIOCPHandler * h, uint64_t cid, MSG_UNBAN * lpMsg);
void	doAccessCheck_Jump		(TIOCPHandler * h, uint64_t cid, MSG_ACCESS_JUMP * lpMsg);
void	doAccessCheck_Come		(TIOCPHandler * h, uint64_t cid, MSG_ACCESS_COME * lpMsg);
void	doAccessCheck_Move		(TIOCPHandler * h, uint64_t cid, MSG_ACCESS_MOVE * lpMsg);
void	doAccessCheck_GreenMSG	(TIOCPHandler * h, uint64_t cid, MSG_ACCESS_GREENMSG * lpMsg);
void	EventCommandGMS			(TIOCPHandler * h, uint64_t cid, MSG_EVENT_COMMAND * lpMsg);
// roye add
void	LogHackChangeStatus		(TIOCPHandler * h, uint64_t cid, MSG_LOG_HACK * lpMsg);
void	MsgChangeStatus			(TIOCPHandler * h, uint64_t cid, MSG_MSG_STATUS * lpMsg);
void	CharacterGotOnlineOrOffline (TIOCPHandler * h, uint64_t cid, MSG_CLIENT_STATUS * lpMsg);
//void	MarrigeInfo				(TIOCPHandler * h, uint64_t cid, MSG_MARRY_SYSTEM_INFO * lpMsg);
void	MarrigeUpdate			(TIOCPHandler * h, uint64_t cid, MSG_MARRY_SYSTEM_UPDATE * lpMsg);
void	SkinCheckStatus			(TIOCPHandler * h, uint64_t cid, MSG_SKIN_CHECK * lpMsg);
void	InvisiableChange		(TIOCPHandler * h, uint64_t cid, MSG_INVISIBLE_COMMAND * lpMsg);
void	InvisiableCrewChange	(TIOCPHandler * h, uint64_t cid, MSG_INVISIBLE_CREW_COMMAND * lpMsg);
void	GuildMemberCheckStatus	(TIOCPHandler * h, uint64_t cid, MSG_GUILD_MEMBER_STATUS * lpMsg);
void	GuildKickMemberCheck	(TIOCPHandler * h, uint64_t cid, MSG_GUILD_KICK_MEMBER * lpMsg);
void	GuildSetAssistCheck		(TIOCPHandler * h, uint64_t cid, MSG_GUILD_SET_ASSIST * lpMsg);
void	GuildJoinRequestAssist	(TIOCPHandler * h, uint64_t cid, MSG_GUILD_JOIN_REQUEST * lpMsg);
void	EventKillCheck			(TIOCPHandler * h, uint64_t cid, MSG_KILLEVENT_CHECKPOINTS * lpMsg);
void	ShopBuyRequest			(TIOCPHandler * h, uint64_t cid, MSG_SHOP_BUY_ITEM_REQUEST * lpMsg);
void	OffTradeRequest			(TIOCPHandler * h, uint64_t cid, MSG_S_OFFTRADE * lpMsg);
void	RedDragonRequest		(TIOCPHandler * h, uint64_t cid, MSG_S_REDDRAGON * lpMsg);
void	FixLevelBugRequest		(TIOCPHandler * h, uint64_t cid, MSG_S_FIX_LEVEL_BUG * lpMsg);
void	SendMessageToAllServers	(const char* szMessage);
void	AntiHackProcessNotify	(TIOCPHandler * h, uint64_t cid, MSG_ANTIHACK_PROCESS_NOTIFY * lpMsg);
// ------------------------------------------------------------------------------
// # Friend Memo Update
// ------------------------------------------------------------------------------

void PHPFriendMemoDelRequest	(TIOCPHandler * h, uint64_t cid, MSG_FREINDMEMO_DEL * lpMsg);
void FriendMemoDelSend			(char * Name, int MemoIndex);
void PHPFriendListAdd			(TIOCPHandler * h, uint64_t cid, MSG_FREINDMEMO_ADD * lpMsg);
void FriendMemoListAdd			(char * SendName, char * RecvName, USHORT MemoIndex, char * Subject);
void PHPFriendListRead			(TIOCPHandler * h, uint64_t cid, MSG_FREINDMEMO_READ * lpMsg);
void FriendMemoRead				(char * SendName, char * RecvName, USHORT MemoIndex, char * Subject);
//-----------------------------------------------------------------------------------------------------------------------