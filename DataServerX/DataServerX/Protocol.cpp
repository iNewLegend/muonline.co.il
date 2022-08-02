//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Protocol.h"
#include "Object.h"
#include "GConfig.h"
#include "GMain.h"
#include "SExerciseEvent.h"
#include "SEventManager.h"
#include "SRunEvent.h"
#include "SFastWrote.h"
#include "SLotteryEvent.h"
#include "SConfusedEvent.h"
#include "SGoldenEvent.h"
#include "GMsgDisable.h"
#include "VoteSystem.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "Protocol"
//-----------------------------------------------------------------------------------------------------------------------

void protocolCore(TIOCPHandler * h, uint64_t cid, UCHAR * Packet, int PacketLen)
{
	if(Packet[0] == 1)
	{
		MSG_HEADER * lpHead = (MSG_HEADER *) Packet;
		// ----
		switch(lpHead->ProtocolId)
		{
			case HEAD_GETSTARTUP:
			{
				startupMsg(h, cid, (MSG_STARTUP *) Packet);
			}
			break;

			case HEAD_EXTRAINFO:
			{
				extraInfoMsg(h, cid, (MSG_S_EXTRAINFO *) Packet);
			}
			break;
		
			case HEAD_GO:
			{
				goMsg(h, cid, (MSG_S_GO *) Packet);
			}
			break;

			case HEAD_KUADNM:
			{
				kandumMsg(h, cid, (MSG_S_KANDUM *) Packet);
			}
			break;

			case HEAD_NOTICEALL:
			{
				noticeMsg(h, cid, (MSG_S_POST *) Packet);
			}
			break;

			case HEAD_NOTICEALLGM:
			{
				noticeMsgGM(h, cid, (MSG_S_POST *) Packet);
			}
			break;

			case HEAD_BAN:
			{
				banMsg(h, cid, (MSG_BAN * ) Packet);
			}
			break;

			case HEAD_GUILDMSG:
			{
				guildMsg(h, cid, (MSG_GUILD *) Packet);
			}
			break;

			case HEAD_INFO:
			{
				infoMsg(h, cid, (MSG_S_INFO *) Packet);
			}
			break;

			case HEAD_INFOSTATE:
			{
				infoStateMsg(h, cid, (MSG_INFO_STATE *) Packet);
			}
			break;

			case HEAD_DELCHAR:
			{
				delCharMsg(h, cid, (MSG_S_DELCHAR *) Packet);
			}
			break;

			case HEAD_BUYVIP:
			{
				buyVipMsg(h, cid, (MSG_BUY_VIP_REQUEST *) Packet);
			}
			break;

			case HEAD_BANONCHAR:
			{
				banOnCharMsg(h, cid, (MSG_BAN_CHAR *) Packet);
			}
			break;

			case HEAD_BANONACC:
			{
				banOnAccMsg(h, cid, (MSG_BAN_ACC *) Packet);
			}
			break;

			case HEAD_ADVMSG:
			{
				advMsgMsg(h, cid, (MSG_ADVMSG *) Packet);
			}
			break;

			case HEAD_DOQUERY:
			{
				doQueryMsg(h, cid, (MSG_DOQUERY *) Packet);
			}
			break;

			case HEAD_REPORT:
			{
				ReportMsg(h, cid, (MSG_REPORT *) Packet);
			}
			break;

			case HEAD_UNBAN:
			{
				unbanMsg(h, cid, (MSG_UNBAN *) Packet);
			}
			break;

			case HEAD_CHECKACCESS_JUMP:
			{
				doAccessCheck_Jump(h, cid, (MSG_ACCESS_JUMP *) Packet);
			}
			break;
			
			
			case HEAD_CHECKACCESS_COME:
			{
				doAccessCheck_Come(h, cid, (MSG_ACCESS_COME *) Packet);
			
			}
			break;

			case HEAD_CHECKACCESS_MOVE:
			{
				doAccessCheck_Move(h, cid, (MSG_ACCESS_MOVE *) Packet);
			}

			break;

			case HEAD_CHECKACCESS_GREENMSG:
			{
				doAccessCheck_GreenMSG(h, cid, (MSG_ACCESS_GREENMSG *) Packet);
			}
			break;

			case HEAD_SKINACCESS:
			{
				SkinCheckStatus (h, cid, (MSG_SKIN_CHECK *) Packet);
			}
			break;

			case HEAD_MSG_STATUS:
			{
				MsgChangeStatus(h, cid, (MSG_MSG_STATUS *) Packet);
			}
			break;

			case HEAD_LOG_HACK:
			{
				LogHackChangeStatus(h, cid, (MSG_LOG_HACK *) Packet);
			}
			break;
			
			case HEAD_CLIENT_STATUS: // leo: i dont like how this shit works so i disable it
			{
				//CharacterGotOnlineOrOffline(h, cid, (MSG_CLIENT_STATUS *) Packet);
			}
			break;

			case HEAD_EVENT_COMMAND:
			{
				EventCommandGMS(h, cid, (MSG_EVENT_COMMAND *) Packet);
			}
			break;
			
			case HEAD_CREW_MSG:
			{
				CrewMsg(h, cid, (MSG_CREW *) Packet);
			}
			break;

			/*case HEAD_MARRY_SYSTEM_INFO:
			{
				MarrigeInfo(h, cid, (MSG_MARRY_SYSTEM_INFO *)Packet);
			}
			break;*/

			case HEAD_MARRY_SYSTEM_UPDATE:
			{
				MarrigeUpdate(h, cid, (MSG_MARRY_SYSTEM_UPDATE *) Packet);
			}
			break;

			case HEAD_PHP_FRIENDMEMO_DEL:
			{
				PHPFriendMemoDelRequest(h, cid, (MSG_FREINDMEMO_DEL *) Packet);
			}
			break;

			case HEAD_PHP_FRIENDLIST_ADD:
			{
				PHPFriendListAdd(h, cid, (MSG_FREINDMEMO_ADD *) Packet);
			}
			break;

			case HEAD_PHP_FRIENDLIST_READ:
			{
				PHPFriendListRead(h, cid, (MSG_FREINDMEMO_READ *) Packet);
			}
			break;

			case HEAD_INVISIABLE_COMMAND:
			{
				InvisiableChange(h, cid, (MSG_INVISIBLE_COMMAND *) Packet);
			}
			break;

			case HEAD_INVISIABLE_CREW_COMMAND:
			{
				InvisiableCrewChange(h, cid, (MSG_INVISIBLE_CREW_COMMAND *) Packet);
			}
			break;

			case HEAD_GUILD_MEMBER_STATUS:
			{
				GuildMemberCheckStatus(h, cid, (MSG_GUILD_MEMBER_STATUS *) Packet);
			}
			break;

			case HEAD_GUILD_KICK_MEMBER:
			{
				GuildKickMemberCheck(h, cid, (MSG_GUILD_KICK_MEMBER *) Packet);
			}
			break;

			case HEAD_GUILD_SET_ASSIST:
			{
				GuildSetAssistCheck(h, cid, (MSG_GUILD_SET_ASSIST *) Packet);
			}
			break;

			case HEAD_GUILD_JOIN_REQUEST:
			{
				GuildJoinRequestAssist(h, cid, (MSG_GUILD_JOIN_REQUEST *) Packet);
			}
			break;

			case HEAD_KILL_EVENT:
			{
				EventKillCheck(h,cid,(MSG_KILLEVENT_CHECKPOINTS *)Packet);
			}
			break;

			case HEAD_SHOP_BUY_REQUEST:
			{
				ShopBuyRequest(h, cid, (MSG_SHOP_BUY_ITEM_REQUEST *)Packet);
			}
			break;

			case HEAD_OFFTRADE:
			{
				OffTradeRequest(h, cid, (MSG_S_OFFTRADE *)Packet);
			}
			break;

			case HEAD_REDDRAGON:
			{
				RedDragonRequest(h, cid, (MSG_S_REDDRAGON *)Packet);
			}
			break;

			case HEAD_FIXLEVELBUG:
			{
				FixLevelBugRequest(h, cid, (MSG_S_FIX_LEVEL_BUG *)Packet);
			}
			break;

			default:
			{
				g_Log.AddHeadHex(0, g_ModuleName, __FUNCTION__, "Unknown packet", Packet, PacketLen);
			}
			break;
		}
	}
	else if(Packet[0] == 2)
	{
		MSG_HEADER2 * lpHead = (MSG_HEADER2 *) Packet;
		// ----
		switch(lpHead->ProtocolId)
		{
			case HEAD_EXERCISESYSTEM:
			{
				switch((VDS_SUBPACKET_EXERCISESYSTEM_HEADERS)lpHead->SubProtocolId)
				{
					case VDS_SUBPACKET_EXERCISESYSTEM_HEADERS::EXERCISESYSTEM_SUBHEAD_GETANSWER:
					{
						if(TExerciseEvent_runState == TExerciseEvent_eRunState::STATE_WORKING)
						{
							MSG_EXERCISE_GETANSWER * lpMsg = (MSG_EXERCISE_GETANSWER *) Packet;
							// ----
							static char temp[11];	memset(temp, 0, sizeof(temp));
							static char temp1[11];	memset(temp1, 0, sizeof(temp1));
							// ----
							memcpy(temp,	lpMsg->szNick,		sizeof(lpMsg->szNick));
							memcpy(temp1,	lpMsg->szAccountID, sizeof(lpMsg->szAccountID));
							// ----
							TExerciseEvent::getAnswer(temp, temp1, lpMsg->Answer);
						}
					}
					break;
				}
			}
			break;

			case HEAD_RUNEVENT:
			{
				switch((VDS_SUBPACKET_RUNEVENT_HEADERS) lpHead->SubProtocolId)
				{
					case VDS_SUBPACKET_RUNEVENT_HEADERS::RUNEVENT_SUBHEAD_WINNERGET:
					{
						if(TRunEvent_RunState == RUNEVENT_STATE::RUNEVENT_RUNNING)
						{
							MSG_RUNEVENT_SENDWINNER * lpMsg = (MSG_RUNEVENT_SENDWINNER *) Packet;
							// ----
							static char temp[11];	memset(temp, 0, sizeof(temp));
							static char temp1[11];	memset(temp1, 0, sizeof(temp1));
							// ----
							memcpy(temp,	lpMsg->szNick,		sizeof(lpMsg->szNick));
							memcpy(temp1,	lpMsg->szAccountID, sizeof(lpMsg->szAccountID));
							// ----
							TRunEvent::getWinner(temp, temp1);
						}
					}
				}
			}
			break;

			case HEAD_WROTEEVENT:
			{
				switch((VDS_SUBPACKET_WROTEEVENT_HEADERS) lpHead->SubProtocolId)
				{
					case VDS_SUBPACKET_WROTEEVENT_HEADERS::WROTEEVENT_SUBHEAD_WINNERGET:
					{
						if(TFastWrote_State == FASTWROTE_STATE::FASTWROTE_RUNNING)
						{
							MSG_WROTEEVENT_SENDWINNER * lpMsg = (MSG_WROTEEVENT_SENDWINNER *) Packet;
							// ----
							static char temp[11];	memset(temp, 0, sizeof(temp));
							static char temp1[11];	memset(temp1, 0, sizeof(temp1));
							// ----
							memcpy(temp,	lpMsg->szNick,		sizeof(lpMsg->szNick));
							memcpy(temp1,	lpMsg->szAccountID, sizeof(lpMsg->szAccountID));
							// ----
							TFastWrote::getWinner(temp, temp1);
						}
					}
					break;
				}			
			}
			break;

			case HEAD_CONFUSEEVENT:
			{
				switch((VDS_SUBPACKET_CONFUSEEVENT_HEADERS) lpHead->SubProtocolId)
				{
					case VDS_SUBPACKET_CONFUSEEVENT_HEADERS::CONFUSEEVENT_SUBHEAD_WINNERGET:
					{
						if(TConfusedWrote_State == CONFUSED_STATE::CONFUSED_RUNNING)
						{
							MSG_CONFUSEEVENT_SENDWINNER * lpMsg = (MSG_CONFUSEEVENT_SENDWINNER *) Packet;
							// ----
							static char temp[11];	memset(temp, 0, sizeof(temp));
							static char temp1[11];	memset(temp1, 0, sizeof(temp1));
							// ----
							memcpy(temp,	lpMsg->szNick,		sizeof(lpMsg->szNick));
							memcpy(temp1,	lpMsg->szAccountID, sizeof(lpMsg->szAccountID));
							// ----
							TConfusedEvent::getWinner(temp, temp1);
						}
					}
					break;
				}			
			}
			break;
			
			case HEAD_LOTTERYEVENT:
			{
				switch((VDS_SUBPACKET_LOTTERYEVENT_HEADERS) lpHead->SubProtocolId)
				{
					case VDS_SUBPACKET_LOTTERYEVENT_HEADERS::LOTTERYEVENT_SUBHEAD_WINNERGET:
					{
						if(TLotteryEvent_STATE == LOTTERYEVENT_STATE::LOTTERYEVENT_RUNNING)
						{
							MSG_LOTTERYEVENT_SENDWINER * lpMsg = (MSG_LOTTERYEVENT_SENDWINER *) Packet;
							// ----
							static char temp[11];	memset(temp, 0, sizeof(temp));
							static char temp1[11];	memset(temp1, 0, sizeof(temp1));
							// ----
							memcpy(temp,	lpMsg->szNick,		sizeof(lpMsg->szNick));
							memcpy(temp1,	lpMsg->szAccountID, sizeof(lpMsg->szAccountID));
							// ----
							TLotteryEvent::getWinner(temp, temp1);

							char line [100];
							ObjectSendNoticeAll(line);
						}
					}
					break;

					case VDS_SUBPACKET_LOTTERYEVENT_HEADERS::LOTTERYEVENT_SUBHEAD_SENDERGET:
					{
						if(TLotteryEvent_STATE == LOTTERYEVENT_STATE::LOTTERYEVENT_RUNNING)
						{
							MSG_LOTTERYEVENT_GETSENDER * lpMsg = (MSG_LOTTERYEVENT_GETSENDER *) Packet;
							// ----
							static char temp[11];	memset(temp, 0, sizeof(temp));
							// ----
							memcpy(temp,	lpMsg->szNick,		sizeof(lpMsg->szNick));
							// ----
							TLotteryEvent::getSender(temp, lpMsg->Number);
						}
					}
					break;
				}	
			}
			break;

			case HEAD_GOLDEN_EVENT:
			{
				switch((VDS_SUBPACKET_GOLDEN_EVENT)lpHead->SubProtocolId)
				{
					case VDS_SUBPACKET_GOLDEN_EVENT::GOLDEN_EVENT_SUBHEAD_START:
					{
						TGoldenEvent::start();
					}
					break;

					case VDS_SUBPACKET_GOLDEN_EVENT::GOLDEN_EVENT_SUBHEAD_STOP:
					{
						TGoldenEvent::stop();
					}
					break;

					case VDS_SUBPACKET_GOLDEN_EVENT::GOLDEN_EVENT_SUBHEAD_GOLDEN_DIE:
					{
						//TGoldenEvent::goldenDie(h, cid, )
					}
					break;
				}
			}
			break;
		}
	}
	else if(Packet[0] == 4)
	{
		MSG_HEADER4 * lpHead = (MSG_HEADER4 *) Packet;
		// ----
		switch(lpHead->ProtocolId)
		{
			case HEAD_VOTESYSTEM:
			{
				voteSystemCore(h, cid, Packet);
			}
			break;

			case HEAD_ANTIHACK:
			{
				MSG_HEADER4 * lpHead = (MSG_HEADER4 *)Packet;
				// ----
				switch ((VDS_SUBPACKET_ANTIHACK_HEADERS)lpHead->SubProtocolId)
				{
				case VDS_SUBPACKET_ANTIHACK_HEADERS::ANTIHACK_SUBHEAD_PROCESS_NOTIFY:
				{
					AntiHackProcessNotify(h, cid, (MSG_ANTIHACK_PROCESS_NOTIFY *)Packet);
				}
				break;
				}
			
			}
			break;

			default:
			{
				g_Log.AddHeadHex(0, g_ModuleName, __FUNCTION__, "Unknown packet", Packet, PacketLen);
			}
			break;
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void startupMsg(TIOCPHandler * h, uint64_t cid, MSG_STARTUP * lpMsg)
{
	MSG_STARTUP pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GETSTARTUP);
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "GS Code : %u Reqeust for startup", lpMsg->btServerCode);
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Reset, CsSets FROM Noobs WHERE GsCode = %d", lpMsg->btServerCode);
	g_DB.Fetch();
	// ----

	pMsg.Resets = g_DB.GetInt("Reset");
	if (g_DB.GetInt("CsSets") == 1)
		pMsg.CsSets = true;
	else
		pMsg.CsSets = false;
	// ----
	if(TRunEvent_RunState == RUNEVENT_STATE::RUNEVENT_RUNNING)
	{
		pMsg.RunEventState = true;
		// ----
		MSG_RUNEVENT_START pMsg = {0};
		// ----
		HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_RUNEVENT, RUNEVENT_SUBHEAD_START);
		// ----
		pMsg.Map	= TRunEvent_CordsMap[TRunEvent_RoledCord].Map;
		pMsg.X		= TRunEvent_CordsMap[TRunEvent_RoledCord].X;
		pMsg.Y		= TRunEvent_CordsMap[TRunEvent_RoledCord].Y;
		// ----
		h->GetIocpServer().Send(cid, (LPBYTE) & pMsg, sizeof(pMsg));
	}
	else
	{
		pMsg.RunEventState = false;
	}
	// ----
	g_DB.Clear();
	// ----
	g_Obj[cid].m_GSCode = lpMsg->btServerCode;
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
	// ----
	// set GS name
	std::pair <int,int> arr (cid, lpMsg->btServerCode);
	g_MainConnectionsListNum.push_back(arr);
	// ----
	// set Msg Lock False
	MSG_MSG_STATUS_RE_SYS rpMsg = {0};
	// ----	
	HeadSet1(& rpMsg.Head, sizeof(rpMsg), HEAD_MSG_STATUS_SYS);
	
	// ----
	rpMsg.Status		= 0;
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & rpMsg, sizeof(rpMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void extraInfoMsg(TIOCPHandler * h, uint64_t cid, MSG_S_EXTRAINFO * lpMsg)
{
	int nDays				= -1;
	int nResets				= 0;
	int nVipLevel			= 0;
	// ----
	char szAccountID[11]	= {0};
	char szNick[11]			= {0};
	char szIpAddr[17]		= {0};
	char MarryName[11]		= {0};
	char Guild[11]			= {0};
	// ----
	char szTemp[256]		= {0};
	// ----
	memcpy(szAccountID,		lpMsg->szAccountID,		sizeof(lpMsg->szAccountID));
	memcpy(szNick,			lpMsg->szNick,			sizeof(lpMsg->szNick));
	memcpy(szIpAddr,		lpMsg->szIpAddr,		sizeof(lpMsg->szIpAddr));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Reset,Name,CtlCode FROM Character WHERE AccountID = '%s' AND Name = '%s'", szAccountID, szNick);
	g_DB.Fetch();
	g_DB.GetStr("Name", szTemp);
	int CltCode = g_DB.GetInt("CtlCode");
	// ----
	nResets = g_DB.GetInt("Reset");
	// ----
	g_DB.Clear();
	// ----
	// # Log
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "for (%s), (Nick-Packet)%s(Nick-SQL)%s", szAccountID, szNick, szTemp);
	// ----
	if(_strcmpi(szNick, szTemp) == 0)
	{
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT VipDays, VipLevel FROM MEMB_INFO WHERE memb___id = '%s'", szAccountID);
		// ----
		if(g_DB.Fetch() != SQL_NO_DATA)
		{
			nDays = g_DB.GetInt("VipDays");
			nVipLevel = g_DB.GetInt("VipLevel");
		}
		// ----
		g_DB.Clear();
	}
	// ----
	// # set allow info to 0 and crewInfo to 1
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE Character SET isInfoAllow = 0, isCrewInfoAllow = 1 WHERE Name = '%s'", szNick);
	g_DB.Fetch();
	g_DB.Clear();
	// ----
	// # Log
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "Info for (%s) - VipDays : %d, Resets : %d, VipLevel : %d", szAccountID, nDays, nResets, nVipLevel);
	// ----
	MSG_R_EXTRAINFO pMsg = {0};
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Select IsMarried, MarryName from Character where AccountId = '%s' and Name ='%s'", szAccountID, szNick);
	g_DB.Fetch();
	// ----
	pMsg.IsMarried = g_DB.GetInt("IsMarried");
	g_DB.GetStr("MarryName",MarryName);
	// ----
	g_DB.Clear();
	// ----
	memcpy(pMsg.MarryName, MarryName, sizeof(pMsg.MarryName));
	// ----
	// # Prepace packet
	// ----
	pMsg.nIndex		= lpMsg->nIndex;
	pMsg.nDays		= nDays;
	pMsg.nVipLevel	= nVipLevel;
	pMsg.nResets	= nResets;
	// ----
	bool canMove = false;
	bool canDisconnect = false;
	// ----
	if (CltCode == 8 || CltCode == 32)
	{
		lptagCFG_INSPECT_ACCESS	INSPECTAccess	= g_Config.getINSPECTAccessListByName(szNick);
		if(INSPECTAccess == NULL)
		{
			canMove = true;
			canDisconnect = true;	
		}
		else
		{
			if (INSPECTAccess->Move == false)
			{
				canMove = false;
			}
			if (INSPECTAccess->Disconnect == false)
			{
				canDisconnect = false;
			}
		}
	}
	// ----
	pMsg.CanUseDisconnect	= canDisconnect;
	pMsg.CanUseMove			= canMove;
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Select G_Name from GuildMember where Name = '%s'", szNick);
	g_DB.Fetch();
	g_DB.GetStr("G_Name",Guild);
	// ----
	g_DB.Clear();
	// ----
	memcpy(pMsg.szGuild, Guild, sizeof(pMsg.szGuild));
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_EXTRAINFO);
	// ----
	// # Send
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void goMsg(TIOCPHandler * h, uint64_t cid, MSG_S_GO * lpMsg)
{
	int		nPrice	= 0;
	int		nTemp	= 0;
	bool	bState	= false;
	// ----
	char	szAccountID[11]		= {0};
	char	szNickName[11]		= {0};
	char	szTargetName[11]	= {0};
	// ----
	memcpy(szAccountID,		lpMsg->szAccountID,		sizeof(lpMsg->szAccountID));
	memcpy(szNickName,		lpMsg->szNickName,		sizeof(lpMsg->szNickName));
	memcpy(szTargetName,	lpMsg->szTargetNick,		sizeof(lpMsg->szTargetNick));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Credits FROM MEMB_INFO WHERE memb___id = '%s'", szAccountID);
	g_DB.Fetch();
	// ----
	nTemp = g_DB.GetInt("Credits");
	// ----
	g_DB.Clear();
	// ----
	if(nTemp != -100)
	{
		if(nTemp >= lpMsg->nPrice)
		{
			char temp[100] = {0};
			sprintf(temp, "Go %s", szTargetName);
			// ----
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_INFO SET Credits = Credits - %d WHERE memb___id = '%s'", lpMsg->nPrice, szAccountID);
			g_DB.Fetch();
			g_DB.Clear();
			// ----
			ObjectLogCreditAdd(szNickName, szAccountID, (int) lpMsg->nPrice, temp,5);
			// ----
			nPrice = 1;
			bState = true;
		}
	}
	// ----
	MSG_R_GO pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GO);
	// ----
	pMsg.bState = bState;
	pMsg.nPrice = nPrice;
	// ----
	pMsg.nIndex			= lpMsg->nIndex;
	pMsg.nTargetIndex	= lpMsg->nTargetIndex;
	// ----
	// # Log
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "Info for (%s) - Credits : %d, State : %d", szAccountID, pMsg.nPrice, pMsg.bState);
	// ----
	// # Send
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void kandumMsg(TIOCPHandler * h, uint64_t cid, MSG_S_KANDUM * lpMsg)
{
	int nPrice			= 0;
	int nSQLPrice		= 0;
	int nKandumCount	= 0;
	int nState			= -1;
	// ----
	char szAccountId[11] = {0};
	char szNickName[11]	 = {0};
	// ----
	memcpy(szAccountId, lpMsg->szAccountID, sizeof(lpMsg->szAccountID));
	memcpy(szNickName,	lpMsg->szNickName,	sizeof(lpMsg->szNickName));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT KandumCount, Credits FROM MEMB_INFO WHERE memb___id = '%s'", szAccountId);
	g_DB.Fetch();
	// ----
	nSQLPrice		= g_DB.GetInt("Credits");
	nKandumCount	= g_DB.GetInt("KandumCount");
	// ----
	g_DB.Clear();
	// ----
	if((nSQLPrice != -100) && (nKandumCount != -100))
	{
		if(nSQLPrice >= lpMsg->nPrice)
		{
			if(nKandumCount > 0)
			{	
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_INFO SET Credits = Credits - %d, KandumCount = 0 WHERE memb___id = '%s'", lpMsg->nPrice, szAccountId);
				g_DB.Fetch();
				g_DB.Clear();
				// ----
				ObjectLogCreditAdd(szNickName, szAccountId, (int) lpMsg->nPrice, "Kandum",5);
				// ----
				nState = 1;
				nPrice = 1;
			}
			else
			{
				nState = 0; // TO MUCH CONDOM FOR TODAY
			}
		}
		else
		{
			nState = 2; // NO CREDITDS
		}
	}
	// ----
	MSG_R_KANDUM pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_KUADNM);
	// ----
	pMsg.nState = nState;
	pMsg.nPrice = nPrice;
	pMsg.nIndex = lpMsg->nIndex;
	// ----
	// # Log
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "Info for (%s) - Credits : %d, State : %d", szAccountId, pMsg.nPrice, pMsg.nState);
	// ----
	// # Send
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void noticeMsg(TIOCPHandler * h, uint64_t cid, MSG_S_POST * lpMsg)
{
	char szNick[11]			= {0};
	char szMesssage[101]	= {0};
	char szAccountId[11]	= {0};
	// ----
	int nTemp				= 0;
	// ----
	memcpy(szNick,		lpMsg->szNick,		sizeof(lpMsg->szNick));
	memcpy(szMesssage,	lpMsg->szMsg,		sizeof(lpMsg->szMsg));
	memcpy(szAccountId, lpMsg->szAcountID,	sizeof(lpMsg->szAcountID));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Credits FROM MEMB_INFO WHERE memb___id = '%s'", szAccountId);
	g_DB.Fetch();
	// ----
	nTemp = g_DB.GetInt("Credits");
	// ----
	g_DB.Clear();
	// ----
	if((nTemp > 0) && (nTemp != -100))
	{
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_INFO set Credits = Credits - %d WHERE memb___id = '%s'", lpMsg->nPrice, szAccountId);
		g_DB.Fetch();
		g_DB.Clear();
		// ----
		ObjectLogCreditAdd(szNick, szAccountId, (int) lpMsg->nPrice, "MSG",5);
		// -----
		MSG_R_POST pMsg = {0};
		// ----
		memcpy(pMsg.szMsg,	szMesssage,	sizeof(pMsg.szMsg));
		memcpy(pMsg.szNick, szNick,		sizeof(pMsg.szNick));
		// ----
		HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_NOTICEALL);
		// ----
		h->sendAll((UCHAR *) & pMsg, sizeof(pMsg));
	}
	else
	{
		objectMsgToNick(h, cid, szNick, "@[Msg] אין לך מספיק קרדיטים עלות הפקודה קרדיט אחד");
	}
}

//-----------------------------------------------------------------------------------------------------------------------

void noticeMsgGM(TIOCPHandler * h, uint64_t cid, MSG_S_POST * lpMsg)
{
	char szNick[11]			= {0};
	char szMesssage[101]	= {0};
	char szAccountId[11]	= {0};
	// ----
	int nTemp				= 0;
	// ----
	memcpy(szNick,		lpMsg->szNick,		sizeof(lpMsg->szNick));
	memcpy(szMesssage,	lpMsg->szMsg,		sizeof(lpMsg->szMsg));
	memcpy(szAccountId, lpMsg->szAcountID,	sizeof(lpMsg->szAcountID));
	// ----
	MSG_R_POST pMsg = {0};
	// ----
	memcpy(pMsg.szMsg,	szMesssage,	sizeof(pMsg.szMsg));
	memcpy(pMsg.szNick, szNick,		sizeof(pMsg.szNick));
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_NOTICEALLGM);
	// ----
	h->sendAll((UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void guildMsg(TIOCPHandler * h, uint64_t cid, MSG_GUILD * lpMsg)
{
	MSG_GUILD pMsg			= {0};
	// ----
	char szGuildName[11]	= {0};
	char szNick[11]			= {0};
	char szMsg[101]			= {0};
	// ----
	int G_Level=0, G_Level_Send=0;
	// ----
	memcpy(szGuildName, lpMsg->szGuildName,		sizeof(pMsg.szGuildName));
	memcpy(szMsg,		lpMsg->szMsg,			sizeof(pMsg.szMsg));
	memcpy(szNick,		lpMsg->szNick,			sizeof(pMsg.szNick));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT G_Status FROM GuildMember WHERE name = '%s'", szNick);
	g_DB.Fetch();
	// ----
	G_Level = g_DB.GetInt("G_Status");
	switch (G_Level)
	{
		case 128:
		{
			G_Level_Send = 1;
		}
		break;

		case 64:
		{
			G_Level_Send = 2;
		}
		break;

		case 32:
		{
			G_Level_Send = 3;
		}
		break;

		default:
		{
			G_Level_Send = 0;
		}
		break;

	}
	// ----
	g_DB.Clear();
	// ----
	memcpy(pMsg.szGuildName,	szGuildName,	sizeof(pMsg.szGuildName));
	memcpy(pMsg.szNick,			szNick,			sizeof(pMsg.szNick));
	memcpy(pMsg.szMsg,			szMsg,			sizeof(pMsg.szMsg));
	// ----
	pMsg.G_Status = G_Level_Send;
	// ----	
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GUILDMSG);
	// ----
	pMsg.nServerNumber = lpMsg->nServerNumber;
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "GNAME : %s, Name : %s, Msg : %s", pMsg.szGuildName, pMsg.szNick, pMsg.szMsg);
	// ----
	h->sendAll((UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void banMsg(TIOCPHandler * h, uint64_t cid, MSG_BAN * lpMsg)
{
	char szGameMsterNick[11]	= {0};
	char szPlayerNick[11]		= {0};
	char szTemp[11]				= {0};
	char szAccountID[11]		= {0};
	int BanState				= lpMsg->isBanAllUsers;
	// ----
	memcpy(szGameMsterNick, lpMsg->szGameMasterNick, sizeof(lpMsg->szGameMasterNick));
	memcpy(szPlayerNick,	lpMsg->szPlayerNick,	sizeof(lpMsg->szPlayerNick));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT AccountID, Name, bDays FROM Character WHERE Name = '%s'", szPlayerNick);
	g_DB.Fetch();
	// ----
	int bDaysFromDB = g_DB.GetInt("bDays");
	// ----
	g_DB.GetStr("AccountID", szAccountID);
	g_DB.GetStr("Name", szTemp);
	// ----
	if(_strcmpi(szTemp, szPlayerNick) != 0)
	{
		objectMsgToNick(h, cid, szGameMsterNick, "Ban failed : User not found");
		// ----
		return;
	}	
	// ----
	g_DB.Clear();
	// ----
	bool isAllowBan = true;
	// ----
	if(bDaysFromDB == -1)
	{
		isAllowBan = false;
		// ----
		for(GMS_ACCESS_LIST::iterator it = g_Config.GMSAccessList.begin() ; it != g_Config.GMSAccessList.end() ; ++it)
		{
			if(_strcmpi(it->Nick, szGameMsterNick) == 0)
			{
				if(it->isBanForeverEditAllow == true)
				{
					isAllowBan = true;
				}
				// ----
				break;
			}
		}
	}
	char Temp [1024] = {0};
	if(isAllowBan == true)
	{
		if(BanState == 0)
		{
			bool canGiveBan = true;
			// ----
			lptagCFG_INSPECT_ACCESS	INSPECTAccess	= g_Config.getINSPECTAccessListByName(szGameMsterNick);
			if(INSPECTAccess == NULL)
			{
				canGiveBan = true;
	
			}
			else if (INSPECTAccess->Ban == false)
				canGiveBan = false;
			
			if (canGiveBan==true)
			{
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE Character SET CtlCode = 1, bRes = %d, bBy = '%s', bDays = '%d' WHERE Name = '%s'", lpMsg->nReason, szGameMsterNick, lpMsg->nDays, szPlayerNick);
				g_DB.Fetch();
				g_DB.Clear();
				
				sprintf(Temp, "BannedBy %s %d %d", szGameMsterNick,  lpMsg->nDays, lpMsg->nReason);
				ObjectLogHistoryAdd(szPlayerNick, szAccountID, Temp, "NULL",6);
			}
			else
				ObjectAccessBan(h, cid, szGameMsterNick, "Ban");
		}
		else
		{
			bool canGiveBan = true;
			// ----
			lptagCFG_INSPECT_ACCESS	INSPECTAccess	= g_Config.getINSPECTAccessListByName(szGameMsterNick);
			if(INSPECTAccess == NULL)
			{
				canGiveBan = true;
	
			}
			else if (INSPECTAccess->Ban == false)
				canGiveBan = false;
			
			if (canGiveBan==true)
			{

			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE Character SET CtlCode = 1, bRes = %d, bBy = '%s', bDays = '%d' WHERE AccountID = '%s'", lpMsg->nReason, szGameMsterNick, lpMsg->nDays, szAccountID);
			g_DB.Fetch();
			g_DB.Clear();
			// ----
			sprintf(Temp, "BannedBy %s %d %d", szGameMsterNick, lpMsg->nDays, lpMsg->nReason);
			ObjectLogHistoryAdd("AllChar", szAccountID, Temp, "NULL",6);
			// ----
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT * FROM AccountCharacter WHERE Id='%s'", szAccountID);
			g_DB.Fetch();
			TCHAR CharName[5][11]={0};
			g_DB.GetStr("GameID1", CharName[0]);
			g_DB.GetStr("GameID2", CharName[1]);
			g_DB.GetStr("GameID3", CharName[2]);
			g_DB.GetStr("GameID4", CharName[3]);
			g_DB.GetStr("GameID5", CharName[4]);
			g_DB.Clear();

			// ----
			for(int i = 0 ; i < 5; ++i)
			{
				if(CharName[i][0] != 0)
				{
					if(lstrlen(CharName[i]) >= 1)
					{
						objectMsgToNick(h, cid, szGameMsterNick, CharName[i]);
					}
				}
			}
			// -----
			objectMsgToNick(h, cid, szGameMsterNick, "@[banusers] all players of the player banned");
			}
			else
				ObjectAccessBan(h, cid, szGameMsterNick, "Banusers");
		}
	}
	else
	{
		objectMsgToNick(h, cid, szGameMsterNick, "@Ban failed : User has ban forever!");
	}
}

//-----------------------------------------------------------------------------------------------------------------------

// roye add
void unbanMsg(TIOCPHandler * h, uint64_t cid, MSG_UNBAN * lpMsg)
{
	char szGameMsterNick[11]	= {0};
	char szPlayerNick[11]		= {0};

	char szTemp[11]				= {0};
	char szAccountID[11]		= {0};


	// ----
	memcpy(szGameMsterNick, lpMsg->szGameMasterNick, sizeof(lpMsg->szGameMasterNick));
	memcpy(szPlayerNick,	lpMsg->szPlayerNick,	sizeof(lpMsg->szPlayerNick));
	// ----

	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT AccountID, Name, CtlCode FROM Character WHERE Name = '%s'", szPlayerNick);
	g_DB.Fetch();
	// ----
	g_DB.GetStr("AccountID", szAccountID);
	g_DB.GetStr("Name", szTemp);
	int CltCode = g_DB.GetInt("CtlCode");
	// ----
	if(_strcmpi(szTemp, szPlayerNick) != 0)
	{
		objectMsgToNick(h, cid, szGameMsterNick, "UnBan failed : User not found");
		// ----
		return;
	}	
	// ----
	g_DB.Clear();

	if (CltCode == 1){
		bool isAllowUnBan = false;
		// ----
	
		for(GMS_ACCESS_LIST::iterator it = g_Config.GMSAccessList.begin() ; it != g_Config.GMSAccessList.end() ; ++it)
		{
			if(_strcmpi(it->Nick, szGameMsterNick) == 0)
			{
				if(it->isUnBan == true)
				{
					isAllowUnBan = true;
				}
				break;
			}

		}
		char Temp[1024] = {0};
		if(isAllowUnBan == true)
		{
			
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE Character SET CtlCode = 0, bRes = %d, bBy = '%s', bDays = '1' WHERE Name = '%s'", lpMsg->nReason, szGameMsterNick, szPlayerNick);
			g_DB.Fetch();
			g_DB.Clear();
			// ----
			sprintf(Temp, "UnBannedBy %s %d", szGameMsterNick, lpMsg->nReason);
			ObjectLogHistoryAdd(szPlayerNick, szAccountID, Temp, "NULL",6);
			// ----
			objectMsgToNick(h, cid, szGameMsterNick, "@[UnBan] The Ban Got Down");
			
		}
		else
		{
		
		ObjectAccessBan(h, cid, szGameMsterNick, "UnBan");
		//objectMsgToNick(szGameMsterNick, "@[UnBan] אין לך מספיק גישות להוריד באנים");
		}
	}
	else
	{
		objectMsgToNick(szGameMsterNick, "@[UnBan] לא ניתן להוריד באן לשחקן ללא באן");

	}
}
//-----------------------------------------------------------------------------------------------------------------------

void infoMsg(TIOCPHandler * h, uint64_t cid, MSG_S_INFO * lpMsg)
{
	MSG_R_INFO pMsg				= {0};
	// ----
	char szAccountID	[11]	= {0};
	char szServerName	[60]	= {0};
	char RequiredNick	[11]	= {0};
	char SeekingNick	[11]	= {0};
	char Temp			[300]	= {0};
	// ----
	memcpy(RequiredNick,	lpMsg->RequiredNick,	sizeof(lpMsg->RequiredNick));
	memcpy(SeekingNick,		lpMsg->SeekingName,		sizeof(lpMsg->SeekingName));
	// ----
	pMsg.SeekingIndex = lpMsg->SeekingIndex;
	// ----
	replace_char((char *) & RequiredNick, 0x27, ' ');
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT G_Name FROM GuildMember WHERE Name = '%s'", RequiredNick);
	// ----
	if(g_DB.Fetch() == SQL_NO_DATA)
	{
		char temp[] = "N/A";
		// ----
		memcpy(pMsg.szGuild, temp, sizeof(temp));
	}
	else
	{
		g_DB.GetStr("G_Name", pMsg.szGuild);
	}
	// ----
	g_DB.Clear();
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT isInfoAllow, Name FROM Character WHERE Name = '%s'", RequiredNick);
	// ----
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		int a = g_DB.GetInt("isInfoAllow");
		g_DB.Clear();
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT AccountID, CtlCode, Name FROM Character WHERE Name = '%s'", SeekingNick);
		g_DB.Fetch();
		int b =g_DB.GetInt("CtlCode");
		g_DB.Clear();
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Name, isInfoAllow, AccountID, cLevel, Class, Strength, Dexterity, Vitality, Energy, MapNumber, MapPosX, MapPosY, Leadership, CtlCode, Reset, IsMarried, MarryName, killEvent FROM Character WHERE Name = '%s'", RequiredNick);
		g_DB.Fetch();
		if(a > 0 && b != 32 && b != 8)
		{
			g_DB.Clear();
			// ----
			objectMsgToNick(h, cid, SeekingNick, "@[Info] Infooff השחקן חסם את האפשרות");
			// ----
			sprintf(Temp, "@[Info] ניסה לקבל מידע ללא הצלחה,%s", SeekingNick);
			objectMsgToNick(h, RequiredNick, Temp);
		}
		else
		{
			switch(g_DB.GetInt("CtlCode"))
			{
				case 8:
				case 32:
				{
					
					g_DB.Clear();
					// ----/
					sprintf(Temp, "@[Info] ניסה לקבל מידע ללא הצלחה,%s", SeekingNick);
					objectMsgToNick(h, RequiredNick, Temp);
					// ----
					objectMsgToNick(h, cid, SeekingNick, "@[Info] (GM) מצטערים לא ניתן לקבל מידע על מנהל משחק");
				}
				break;

				default:
				{
					g_DB.GetStr("AccountID", szAccountID);
					g_DB.GetStr("Name", pMsg.Name);
					g_DB.GetStr("MarryName", pMsg.MarryName);
					// ----
					pMsg.wLevel		= g_DB.GetInt("cLevel");
					pMsg.nResets	= g_DB.GetInt("Reset");
					pMsg.DBClass	= g_DB.GetInt("Class");
					pMsg.str		= g_DB.GetInt("Strength");
					pMsg.agi		= g_DB.GetInt("Dexterity");
					pMsg.vit		= g_DB.GetInt("Vitality");
					pMsg.ene		= g_DB.GetInt("Energy");
					pMsg.cmd		= g_DB.GetInt("Leadership");
					pMsg.Map		= g_DB.GetInt("MapNumber");
					pMsg.X			= g_DB.GetInt("MapPosX");
					pMsg.Y			= g_DB.GetInt("MapPosY");
					pMsg.isMarry	= (bool) g_DB.GetInt("IsMarried");
					pMsg.killEvent	= g_DB.GetInt("KillEvent");
					if (g_DB.GetInt("CtlCode") == 1)
						pMsg.isBanned	= true;
					else
						pMsg.isBanned	= false;
					// ----
					g_DB.Clear();
					// ----
					g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Credits, VipDays, VipLevel FROM MEMB_INFO WHERE memb___id = '%s'", szAccountID);
					g_DB.Fetch();
					// ----
					pMsg.nCredits	= g_DB.GetInt("Credits");
					pMsg.isVip		= (bool) g_DB.GetInt("VipDays");
					pMsg.VipLevel = g_DB.GetInt("VipLevel");
					// ----
					g_DB.Clear();
					// ----
					g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT ConnectStat, ServerName FROM MEMB_STAT WHERE memb___id = '%s' ", szAccountID);
					g_DB.Fetch();
					// ----
					g_DB.GetStr("ServerName", pMsg.szServerName);
					// ----
					int ConnectStat = g_DB.GetInt("ConnectStat");
					g_DB.Clear();
					// -----
					if(ConnectStat > 0)
					{
						g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT GameIDC FROM AccountCharacter WHERE Id = '%s'", szAccountID);
						g_DB.Fetch();
						// ----
						char Temp[12] = {0};
						// ----
						g_DB.GetStr("GameIDC", Temp);
						g_DB.Clear();
						// ----
						if(_strcmpi(RequiredNick, Temp) == 0)
						{
							pMsg.isOnline = true;
						}
						else
						{
							pMsg.isOnline = false;
						}
					}
					// ----
					g_Config.getServerNameByGSName(pMsg.szServerName, szServerName);
					// ----
					HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_INFO);
					// ----
					h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
					// ----
					g_DB.Clear();
					//--- roye
					g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT AccountID, CtlCode, Name FROM Character WHERE Name = '%s'", SeekingNick);
					if (g_DB.Fetch() != SQL_NO_DATA)
					if(g_DB.GetInt("CtlCode") != 32 && g_DB.GetInt("CtlCode") != 8){
						sprintf(Temp, "@[Info] ביצע בדיקת מידע על השם שלך ,%s",SeekingNick);
						objectMsgToNick(h, RequiredNick, Temp);
					}
				}
			}
		}
	}
	else
	{
		g_DB.Clear();
		// ----
		objectMsgToNick(h, cid, SeekingNick, "@[Info] שם השחקן לא קיים");
	}

}
//-----------------------------------------------------------------------------------------------------------------------

void infoStateMsg(TIOCPHandler * h, uint64_t cid, MSG_INFO_STATE * lpMsg)
{
	char szName[11] = {0};
	// ----
	memcpy(szName, lpMsg->szNick, sizeof(lpMsg->szNick));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE Character SET isInfoAllow = %d WHERE Name = '%s'", lpMsg->bState, szName);
	g_DB.Fetch();
	g_DB.Clear();
}


//-----------------------------------------------------------------------------------------------------------------------


void CrewMsg(TIOCPHandler * h, uint64_t cid, MSG_CREW * lpMsg)
{
	char szServerName	[60]	= {0};
	char SeekingNick	[11]	= {0};
	char Temp			[1024]	= {0};
	// ----	
	GMS_LIST GM = ObjectGetAllGmsStatus();
	// ----
	memcpy(SeekingNick, lpMsg->SeekingName, sizeof(lpMsg->SeekingName));
	// ----
	objectMsgToNick(h, cid, SeekingNick, "@ Crew List | רשימת צוות");
	objectMsgToNick(h, cid, SeekingNick, "@-GMS - מנהלי משחק--");
	// ----

	for (tagGMSStatus gm : GM)
	{

		if (gm.bStatus)
		{
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT isCrewInfoAllow from Character where AccountId = '%s' and Name = '%s'", gm.accName.c_str(), gm.GMName.c_str());
			if (g_DB.Fetch() != SQL_NO_DATA)
			{
				if (g_DB.GetInt("isCrewInfoAllow") == 1)
				{
					g_Config.getServerNameByGSCode(szServerName, gm.btServerCode);
					sprintf(Temp, "@[GMS][%d] : %s is online", (gm.btServerCode), gm.GMName.c_str());

					//g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::DeepSkyBlue, Temp);

					objectMsgToNick(h, cid, SeekingNick, Temp);
				}
			}
		}
	}
		
	
	// ----
	GM.clear();
	// ----
	objectMsgToNick(h, cid, SeekingNick, "@--Mefakhim - גילד מפקחים--");
	// ----
	GUILD_MEMBER_LIST GI = ObjectGetAllMembersGuild("Mefakhim");
	// ----
	for (GUILD_MEMBER_LIST::iterator it = GI.begin() ; it != GI.end() ; ++it)
	{
		if (it->bStatus == true)
		{
			sprintf(Temp, "@[%s][%d] : %s is online","Mefakhim", it->btServerCode, it->NameMember.c_str());
			objectMsgToNick(h, cid, SeekingNick, Temp);
		}
	}
	// ----
	GI.clear();
	// ----
	objectMsgToNick(h, cid, SeekingNick, "@--SiegeINS - גילד מפקחי סייג--");
	// ----
	GUILD_MEMBER_LIST SI = ObjectGetAllMembersGuild("SeigeINS");
	// ----
	for (GUILD_MEMBER_LIST::iterator it = SI.begin() ; it != SI.end() ; ++it)
	{
		if (it->bStatus == true)
		{
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT isCrewInfoAllow from Character where AccountId = '%s' and Name = '%s'", it->accName.c_str(), it->NameMember.c_str());
			if (g_DB.Fetch() != SQL_NO_DATA)
			{
				if(g_DB.GetInt("isCrewInfoAllow") == 1)
				{
					sprintf(Temp, "@[%s][%d] : %s is online","SiegeINS", it->btServerCode, it->NameMember.c_str());
					//g_Log.AddC(-1, "CrewMsg", __FUNCTION__, TColor::DeepSkyBlue, Temp);
					objectMsgToNick(h, cid, SeekingNick, Temp);
				}
			}
		}
	}
	SI.clear();
}

//-----------------------------------------------------------------------------------------------------------------------

void delCharMsg(TIOCPHandler * h, uint64_t cid, MSG_S_DELCHAR * lpMsg)
{
	char szName[11] = {0};
	// ----
	memcpy(szName, lpMsg->pMsgCharDel.Name, sizeof(lpMsg->pMsgCharDel.Name));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT CtlCode, Reset, Name FROM Character WHERE Name = '%s'", szName);
	// ----
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		MSG_R_DELCHAR pMsg = {0};
		// ----
		HeadSet1(& pMsg.Head,  sizeof(pMsg), HEAD_DELCHAR);
		// ----
		if(g_DB.GetInt("CtlCode") == 1)
		{
			pMsg.isBanned = true;
		}
		// ----
		pMsg.Resets			= g_DB.GetInt("Reset");
		pMsg.PlayerIndex	= lpMsg->PlayerIndex;
		// ----
		memcpy((void *) & pMsg.pMsgCharDel, & lpMsg->pMsgCharDel, sizeof(pMsg.pMsgCharDel));
		// ---
		h->GetIocpServer().Send(cid, (LPBYTE) & pMsg, sizeof(pMsg));
	}
	// ----
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

void buyVipMsg(TIOCPHandler * h, uint64_t cid, MSG_BUY_VIP_REQUEST * lpMsg)
{
	char szAccountID[11]	= {0};
	char szNick[11]			= {0};
	int	 VipLevel			= lpMsg->VipLevel;
	int	 VipDays			= lpMsg->VipDays;
	int	 VipPrice			= lpMsg->VipPrice;
	// ----
	memcpy(szAccountID,		lpMsg->szAccountID,		sizeof(lpMsg->szAccountID));
	memcpy(szNick,			lpMsg->szNick,			sizeof(lpMsg->szNick));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Credits, VipDays FROM MEMB_INFO WHERE memb___id = '%s'", szAccountID);
	// ----
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		int Credits		= g_DB.GetInt("Credits");
		int TrueVipDays = g_DB.GetInt("VipDays");
		// ----
		if (TrueVipDays == 0)
		{
			if (Credits >= VipPrice)
			{
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_INFO SET VipDays = VipDays + %d, Credits = Credits - %d, VipLevel = %d WHERE memb___id = '%s'",
					VipDays, VipPrice, VipLevel, szAccountID);
				g_DB.Fetch();
				g_DB.Clear();
				// ----
				ObjectLogCreditAdd(szNick, szAccountID, VipPrice, "BuyVipFromGame", 5);
				// ----
				objectMsgToNick(h, cid, szNick, "@[VIP]דרגת הויאיפי שלך עודכנה בהצלחה.");
			}
			else
			{
				objectMsgToNick(h, cid, szNick, "@[VIP] אין לך מספיק קרדיטים לרכישת ואיפי");
			}
		}
		else 
		{
			objectMsgToNick(h, cid, szNick, "@[VIP] יש לך כבר דרגת ויאיפי קיימת.");
			objectMsgToNick(h, cid, szNick, "@[VIP] תוכל לקנות רק לאחר שהדרגה הקיימת תסתיים");
		}
	}
	// ----
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

void banOnCharMsg(TIOCPHandler * h, uint64_t cid, MSG_BAN_CHAR * lpMsg)
{
	char szGameMaster[11]	= {0};
	char szNick[11]			= {0};
	char szAccountId[11]	= {0};
	char Temp[1024]			= {0};
	// -----
	memcpy(szNick,			lpMsg->szNick,			sizeof(lpMsg->szNick));
	memcpy(szGameMaster,	lpMsg->szGameMaster,		sizeof(lpMsg->szGameMaster));
	// ----
	lptagCFG_GMS_ACCESS	GMSAccess	= g_Config.getGMSAccessListByName(szGameMaster);
	// ----
	if(GMSAccess == NULL)
	{
		objectMsgToNick(h, cid, szGameMaster, "אין לך מספיק גישה לפקודה זו");
	}
	else if(GMSAccess->isAllowUseNewBan == false)
	{
		objectMsgToNick(h, cid, szGameMaster, "אין לך מספיק גישה לפקודה זו");
	}
	else
	{
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT AccountID FROM Character WHERE Name = '%s'", szNick);
		// ----
		if(g_DB.Fetch() == SQL_NO_DATA)
		{
			g_DB.Clear();
			// ----
			sprintf(Temp, "@[BanChar] לא נמצא במערכת השרת %s", szNick);
			// ----
			objectMsgToNick(h, cid, szGameMaster, Temp);
		}
		else
		{	
			g_DB.GetStr("AccountID", Temp);
			g_DB.Clear();
			// -----
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_INFO SET bloc_code = %d, banacc_by = '%s', banacc_res = %d, banacc_date = getdate() WHERE memb___id = '%s'", lpMsg->State, szGameMaster, lpMsg->ID, Temp);
			g_DB.Fetch();
			g_DB.Clear();
			// -----
			if (lpMsg->State) {
				sprintf(Temp, "BanAccLock %s %d", szGameMaster, lpMsg->ID);
				ObjectLogHistoryAdd("tmp", szAccountId, Temp, "NULL", 6);
			} else {
				sprintf(Temp, "BanAccDown %s %d", szGameMaster, lpMsg->ID);
				ObjectLogHistoryAdd("tmp", szAccountId, Temp, "NULL", 6);
			}
			// ----
			sprintf(Temp, "@[BanChar] %d SET to %s", lpMsg->State, szAccountId); 
			objectMsgToNick(h, cid, szGameMaster, Temp);
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void banOnAccMsg(TIOCPHandler * h, uint64_t cid, MSG_BAN_ACC * lpMsg)
{
	char szGameMaster[11]	= {0};
	char szAccountID[11]	= {0};
	// ----
	memcpy(szGameMaster,	lpMsg->szGameMaster,		sizeof(lpMsg->szGameMaster));
	memcpy(szAccountID,		lpMsg->szAccountID,		sizeof(lpMsg->szAccountID));
	// ----
	lptagCFG_GMS_ACCESS	GMSAccess	= g_Config.getGMSAccessListByName(szGameMaster);
	// ----
	if(GMSAccess == NULL)
	{
		objectMsgToNick(h, cid, szGameMaster, "אין לך מספיק גישה לפקודה זו");
	}
	else if(GMSAccess->isAllowUseNewBan == false)
	{
		objectMsgToNick(h, cid, szGameMaster, "אין לך מספיק גישה לפקודה זו");
	}
	else
	{
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT memb___id FROM MEMB_INFO WHERE memb___id = '%s'", szAccountID);
		// ----
		if(g_DB.Fetch() == SQL_NO_DATA)
		{
			g_DB.Clear();
			// ----
			objectMsgToNick(h, cid, szGameMaster, "@[BanAcc] שם המשתמש לא קיים");
		}
		else
		{
			g_DB.Clear();
			// ----
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_INFO SET bloc_code = %d, banacc_by = '%s', banacc_res = %d, banacc_date = getdate() WHERE memb___id = '%s'", lpMsg->State, szGameMaster, lpMsg->ID, szAccountID);
			g_DB.Fetch();
			g_DB.Clear();
			// ----
			char Temp[1024] = { 0 };
			// ----
			if (lpMsg->State) {
				sprintf(Temp, "BanAccLock %s %d", szGameMaster, lpMsg->ID);
				ObjectLogHistoryAdd("tmp", szAccountID, Temp, "NULL", 6);
			} else {
				sprintf(Temp, "BanAccDown %s %d", szGameMaster, lpMsg->ID);
				ObjectLogHistoryAdd("tmp", szAccountID, Temp, "NULL", 6);
			}
			// ----
			sprintf(Temp, "@[BanAcc] %s SET to %d", szAccountID, lpMsg->State);
			objectMsgToNick(h, cid, szGameMaster, Temp);
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void advMsgMsg(TIOCPHandler * h, uint64_t cid, MSG_ADVMSG * lpMsg)
{

	static std::list<tagNicksState> RequestedNicks;
	// ----
	char RequestedName[11] = {0};
	// ----
	memcpy(RequestedName, lpMsg->PakahName, sizeof(lpMsg->PakahName));
	// ----
	if(RequestedNicks.size() == 0)
	{
		tagNicksState NickState;
		// ----
		NickState.Name.assign(RequestedName);
		NickState.TickCount = GetTickCount();
		// ----
		RequestedNicks.push_back(NickState);		 
		// ----
		MSG_ADVMSG pMsg = {0};
		// ----
		HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_ADVMSG);
		// ----
		memcpy(pMsg.PakahName, RequestedName, sizeof(pMsg.PakahName));
		// ----
		h->GetIocpServer().Send(cid, (LPBYTE)& pMsg, sizeof(MSG_ADVMSG));
	}
	else
	{
		bool isExist = false;
		// ----
		for(std::list<tagNicksState>::iterator it = RequestedNicks.begin() ; it != RequestedNicks.end() ; ++it)
		{
			if(strcmp(it->Name.c_str(), RequestedName) == 0)
			{
				// # exist
				// ----
				if((GetTickCount() - it->TickCount) >= (60000 * 5) /* 5 minute */)
				{
					MSG_ADVMSG pMsg = {0};
					// ----
					HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_ADVMSG);
					// ----
					memcpy(pMsg.PakahName, RequestedName, sizeof(pMsg.PakahName));
					// ----
					h->GetIocpServer().Send(cid, (LPBYTE)& pMsg, sizeof(MSG_ADVMSG));
					// ----
					it->TickCount = GetTickCount();
				}
				else
				{
					objectMsgToNick(h, cid, RequestedName, "@[Adv] יש באפשרותך לפרסם זאת כל 5 דקות בלבד");
				}
				// ----
				isExist = true;
				// ----
				return;
			}
		}
		// ----
		if(isExist == false)
		{
			tagNicksState NickState;
			// ----
			NickState.Name.assign(RequestedName);
			NickState.TickCount = GetTickCount();
			// ----
			RequestedNicks.push_back(NickState);
			// ----
			MSG_ADVMSG pMsg = {0};
			// ----
			HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_ADVMSG);
			// ----
			memcpy(pMsg.PakahName, RequestedName, sizeof(pMsg.PakahName));
			// ----
			h->GetIocpServer().Send(cid, (LPBYTE)& pMsg, sizeof(MSG_ADVMSG));
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void doQueryMsg(TIOCPHandler * h, uint64_t cid, MSG_DOQUERY * lpMsg)
{
	char szQuery[200] = {0};
	// ----
	memcpy(szQuery, lpMsg->Query, lpMsg->QueryLen);
	// ----
	g_DB.Exec(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, szQuery);
	g_DB.Fetch();
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

void ReportMsg(TIOCPHandler * h, uint64_t cid, MSG_REPORT * lpMsg) // eliad
{
	char ReporterName[11]	= {0};
	char Name[11]			= {0};
	char Reason[101]		= {0};
	// ----
	memcpy(ReporterName, lpMsg->szReporterName, sizeof(lpMsg->szReporterName));
	memcpy(Name, lpMsg->szName, sizeof(lpMsg->szName));
	memcpy(Reason, lpMsg->szReason, sizeof(lpMsg->szReason));
	// ----
	replace_char((char *)& Name, 0x27, ' ');
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Name FROM Character WHERE Name = '%s'", Name);
	// ----
	if (g_DB.Fetch() == SQL_NO_DATA)
	{
		g_DB.Clear();
		// ----
		objectMsgToNick(h, cid, ReporterName, "~[Report] השחקן עליו דיווח לא קיים.");
		// ----
		// # Log
		// ----
		g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "~[Report] השחקן עליו דיווח לא קיים.");
	}
	else
	{
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "INSERT INTO Reports VALUES('%s', '%s', '%s', GETDATE())", ReporterName, Name, Reason);
		g_DB.Fetch();
		g_DB.Clear();
	}

}
//-----------------------------------------------------------------------------------------------------------------------

// roye access
void doAccessCheck_Jump	(TIOCPHandler * h, uint64_t cid, MSG_ACCESS_JUMP * lpMsg)
{
	bool AccState		= lpMsg->State;
	char Name [11] = {0};
	char Command [11] = {0};
	// ----
	memcpy(Name,	lpMsg->Name,		sizeof(lpMsg->Name));
	memcpy(Command,		lpMsg->Command,		sizeof(lpMsg->Command));
	// ----
	lptagCFG_INSPECT_ACCESS	INSPECTAccess	= g_Config.getINSPECTAccessListByName(Name);
	// ----
	if(INSPECTAccess == NULL)
	{
		AccState = true;
	}
	else if(INSPECTAccess->Jump == false)
	{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		// ----
		AccState = false;
	}
	else if(INSPECTAccess->Jump == true)
	{	
		AccState = true;
	}
	lpMsg->State = AccState;
	// ----
	MSG_ACCESS_JUMP pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CHECKACCESS_JUMP);
	memcpy(pMsg.Command, lpMsg->Command, sizeof(lpMsg->Command));
	memcpy(pMsg.Name, lpMsg->Name, sizeof(lpMsg->Name));
	memcpy(pMsg.TargetName, lpMsg->TargetName, sizeof(lpMsg->TargetName));
	// ----
	pMsg.State = AccState;
	pMsg.aIndex			= lpMsg->aIndex;
	pMsg.TeleportID=lpMsg->TeleportID;
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}

//-----------------------------------------------------------------------------------------------------------------------


void	doAccessCheck_Come	(TIOCPHandler * h, uint64_t cid, MSG_ACCESS_COME * lpMsg)
{
	bool AccState		= lpMsg->State;
	char Name [11] = {0};
	char Command [11] = {0};
	// ----
	memcpy(Name,	lpMsg->Name,		sizeof(lpMsg->Name));
	memcpy(Command,		lpMsg->Command,		sizeof(lpMsg->Command));
	// ----
	lptagCFG_INSPECT_ACCESS	INSPECTAccess	= g_Config.getINSPECTAccessListByName(Name);
	// ----
	if(INSPECTAccess == NULL)
	{
		AccState = true;
	}
	else if(INSPECTAccess->Come == false)
	{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		// ----
		AccState = false;
	}
	lpMsg->State = AccState;
	// ----
	MSG_ACCESS_COME pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CHECKACCESS_COME);
	memcpy(pMsg.Command, lpMsg->Command, sizeof(lpMsg->Command));
	memcpy(pMsg.Name, lpMsg->Name, sizeof(lpMsg->Name));
	memcpy(pMsg.TargetName, lpMsg->TargetName, sizeof(lpMsg->TargetName));
	// ----
	pMsg.State = AccState;
	pMsg.aIndex			= lpMsg->aIndex;
		
	// ----
	 h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}

//-----------------------------------------------------------------------------------------------------------------------

void	doAccessCheck_Move	(TIOCPHandler * h, uint64_t cid, MSG_ACCESS_MOVE * lpMsg)
{
	bool AccState		= lpMsg->State;
	char Command [11] = {0};
	char Name [11] = {0};
	// ----
	memcpy(Name,		lpMsg->Name,		sizeof(lpMsg->Name));
	memcpy(Command,		lpMsg->Command,		sizeof(lpMsg->Command));
	// ----
	lptagCFG_INSPECT_ACCESS	INSPECTAccess	= g_Config.getINSPECTAccessListByName(Name);
	// ----
	if(INSPECTAccess == NULL)
	{
		AccState = true;
	}
	else if (strcmp(Command, "Move") == 0) {
		if(INSPECTAccess->Move == false)
		{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		// ----	
		AccState = false;
		}
	}
	else if (INSPECTAccess->Disconnect == false)
	{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		// ----
		AccState = false;
	}

	lpMsg->State = AccState;
	// ----
	MSG_ACCESS_MOVE pMsg = {0};
	// ----	
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CHECKACCESS_MOVE);
	memcpy(pMsg.Command, lpMsg->Command, sizeof(lpMsg->Command));
	memcpy(pMsg.Name, lpMsg->Name, sizeof(lpMsg->Name));
	// ----
	pMsg.State			= AccState;
	pMsg.aIndex			= lpMsg->aIndex;
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}

//-----------------------------------------------------------------------------------------------------------------------

void doAccessCheck_GreenMSG	(TIOCPHandler * h, uint64_t cid, MSG_ACCESS_GREENMSG * lpMsg)
{
	bool AccState		= lpMsg->State;
	char Command [11] = {0};
	char Name [11] = {0};
	// ----
	memcpy(Name,		lpMsg->Name,		sizeof(lpMsg->Name));
	memcpy(Command,		lpMsg->Command,		sizeof(lpMsg->Command));
	// ----
	lptagCFG_GMS_ACCESS	GMSAccess	= g_Config.getGMSAccessListByName(Name);
	// ----
	if(GMSAccess == NULL)
	{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		AccState = false;
	}
	else if(GMSAccess->isGreenMSGAllow == false)
	{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		AccState = false;
	}

	else if(GMSAccess->isGreenMSGAllow == true)
	{
		AccState = true;
	}

	MSG_ACCESS_GREENMSG pMsg = {0};
	// ----	
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CHECKACCESS_GREENMSG);
	// ----
	memcpy(pMsg.Command, lpMsg->Command, sizeof(lpMsg->Command));
	memcpy(pMsg.Name, lpMsg->Name, sizeof(lpMsg->Name));
	// ----
	pMsg.State			= AccState;
	pMsg.aIndex			= lpMsg->aIndex;
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void EventCommandGMS (TIOCPHandler * h, uint64_t cid, MSG_EVENT_COMMAND * lpMsg)
{
	char szAccountID [11]	= {0};
	char szName [11]		= {0};
	char Temp [1024]		= {0};
	// ----
	int nEvents = 0;
	// ----
	memcpy(szAccountID,		lpMsg->AccountID,		sizeof(lpMsg->AccountID));
	memcpy(szName,			lpMsg->Name,				sizeof(lpMsg->Name));
	// ----
	MSG_EVENT_COMMAND pMsg = {0};
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT NumEvents FROM GM WHERE AccName = '%s' and GMName = '%s'", szAccountID, szName);
	// ----
	if(g_DB.Fetch() != SQL_NO_DATA) {
		nEvents = g_DB.GetInt("NumEvents");
	} else {
		pMsg.Status = 0;
		objectMsgToNick(h, cid, szName, "@You Don't have access to this command");
	}
	// ----
	g_DB.Clear();
	// ----
	if(nEvents > 0 || nEvents == -1)
	{
		TEventManager::e_EVENT_TYPES eEventType = (TEventManager::e_EVENT_TYPES) ObjectRandomize(1, TEventManager::uEVENTS_COUNT);

		if(TEventManager::startByGameMaster(eEventType, szName)) {
			if (nEvents != -1)
			{
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE GM SET NumEvents = %d Where AccName = '%s'", nEvents - 1, szAccountID);
				g_DB.Fetch();
				g_DB.Clear();
				// ----
				sprintf(Temp, "You have MORE %d Events to Run", nEvents - 1);
				// ----
				objectMsgToNick(h, cid, szName, Temp);
			}

			pMsg.Status = 1;
		}
		else
		{
			objectMsgToNick(h, cid, szName, "~There is already Event running");
		}
	}
	else
	{
		objectMsgToNick(h, cid, szName, "@You Don't have more Events to do");
		pMsg.Status = 2;
	}
	// ----	
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_EVENT_COMMAND);
	// ----
	memcpy(pMsg.Name, lpMsg->Name, sizeof(lpMsg->Name));
	memcpy(pMsg.AccountID, lpMsg->AccountID, sizeof(lpMsg->AccountID));
	// ----
	g_IOCP->sendAll((LPBYTE) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void MsgChangeStatus (TIOCPHandler * h, uint64_t cid, MSG_MSG_STATUS * lpMsg)
{
	bool AccState	= true;
	int Status		= lpMsg->Status;
	int Time		= lpMsg->Time;
	char Name [11]  = {0};
	// ----
	memcpy(Name,		lpMsg->Name,		sizeof(lpMsg->Name));
	// ----
	lptagCFG_GMS_ACCESS	GMSAccess	= g_Config.getGMSAccessListByName(Name);
	// ----
	
	if(GMSAccess == NULL)
	{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		AccState = false;
	}
	else if(GMSAccess->isMsgChangeAllow == false)
	{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		AccState = false;
	}

	else if(GMSAccess->isMsgChangeAllow == true)
	{
		AccState = true;
	}
	// ----
	MSG_MSG_STATUS_RE pMsg = {0};
	// ----
	if (AccState == false)
	{
		pMsg.Type			= 0;
	}
	else
	{
		if (Status == 1 && MSG_CONTINUE != true)
		{
			objectMsgToNick(h, cid, Name, "@הפעלת את נעילת המסג'ים");
			// ----
			g_MsgDisable.m_MsgTime = Time;
			MSG_CONTINUE = true;
			// ----
			memcpy(g_MsgDisable.m_MsgName, lpMsg->Name, sizeof(lpMsg->Name));
		}
		else if (Status == 0)
		{
			if(MSG_CONTINUE == true)
			{
				MSG_CONTINUE = false;
				g_MsgDisable.SendStopMsg();
			}
			objectMsgToNick(h, cid, Name, "@ביטלת את נעילת המסג'ים");
		}
		pMsg.Type			= 1;
	}
	// ----	
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_MSG_STATUS);
	// ----
	memcpy(pMsg.Name, lpMsg->Name, sizeof(lpMsg->Name));
	// ----
	pMsg.Status				= Status;
	// ----
	g_IOCP->sendAll((LPBYTE) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void LogHackChangeStatus (TIOCPHandler * h, uint64_t cid, MSG_LOG_HACK * lpMsg)
{
	bool ChangeStatus = false;
	char Name [11]  = {0};
	// ----
	memcpy(Name,		lpMsg->Name,		sizeof(lpMsg->Name));
	// ----
	lptagCFG_INSPECT_ACCESS	INSPECTAccess	= g_Config.getINSPECTAccessListByName(Name);
	// ----
	if(INSPECTAccess == NULL)
	{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		ChangeStatus = false;
	}
	else if(INSPECTAccess->isHackLogAllow == false)
	{
		objectMsgToNick(h, cid, Name, "אין לך מספיק גישה לפקודה זו");
		ChangeStatus = false;
	}

	else if(INSPECTAccess->isHackLogAllow == true)
	{
		ChangeStatus = true;
	}

	MSG_R_LOG_HACK pMsg = {0};

	if (ChangeStatus == false)
	{
		pMsg.status	= 0;
	}

	else
	{
		pMsg.status	= 1;
	}
	// ----	
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_LOG_HACK);
	// ----
	memcpy(pMsg.Name, lpMsg->Name, sizeof(lpMsg->Name));
	// ----
	pMsg.aIndex				=lpMsg->aIndex;
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------
void CharacterGotOnlineOrOffline (TIOCPHandler * h, uint64_t cid, MSG_CLIENT_STATUS * lpMsg)
{
	char szAccountID[11]	= {0};
	char szNick[11]			= {0};
	char szIpAddr[17]		= {0};
	// ----
	char szTemp[256]		= {0};
	char Temp[1024]			= {0};
	// ----
	char dateCheck [1024]	= {0};
	char typeCheck [30]		= {0};
	char nameCheck [11]		= {0};

	// ----
	memcpy(szAccountID,		lpMsg->szAccountID,		sizeof(lpMsg->szAccountID));
	memcpy(szNick,			lpMsg->szNick,			sizeof(lpMsg->szNick));
	memcpy(szIpAddr,		lpMsg->szIpAddr,			sizeof(lpMsg->szIpAddr));
	// ----
	//g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, "%d", lpMsg->Status);
	// ---
	/*if ((OFFLINE_ONLINE_STATUS)lpMsg->Status == OFFLINE_ONLINE_STATUS_OFFLINE)
	{
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_STAT SET ServerCode = '0' WHERE memb___id = '%s'",
		szAccountID);
		g_DB.Fetch();
		g_DB.Clear();
	}
	else if ((OFFLINE_ONLINE_STATUS)lpMsg->Status != OFFLINE_ONLINE_STATUS_UNKNOW)
	{
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_STAT SET ServerCode = '%d' WHERE memb___id = '%s'",
		lpMsg->btServerCode ,szAccountID);
		g_DB.Fetch();
		g_DB.Clear();
	}*/

	switch((OFFLINE_ONLINE_STATUS)lpMsg->Status)
	{
		case OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_OFFLINE:
		{
			if((_strcmpi(szNick, "") == 0))
			{
				memcpy(szNick,			"tmp",			sizeof("tmp"));
			}
			if (lpMsg->btServerCode > 10)
			{
				//g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, "disconnect");
				sprintf(Temp, "DisconnectFrom %d",  lpMsg->btServerCode);
				ObjectLogHistoryAdd(szNick, szAccountID, Temp, szIpAddr,3);	
			}
			else
			{
				//g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, "disconnect");
				sprintf(Temp, "DisconnectFrom %d",  lpMsg->btServerCode+1);
				ObjectLogHistoryAdd(szNick, szAccountID, Temp, szIpAddr,3);	
			}
		}
		break;
		
		case OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_ONLINE:
		{
			if (lpMsg->btServerCode > 10)
			{
				//g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, "connected");
				sprintf(Temp, "ConnectedTo %d", lpMsg->btServerCode);
				ObjectLogHistoryAdd("tmp", szAccountID, Temp, szIpAddr,2);
				// g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, Temp);
			}
			else
			{
				//g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, "connected");
				sprintf(Temp, "ConnectedTo %d", lpMsg->btServerCode+1);
				ObjectLogHistoryAdd("tmp", szAccountID, Temp, szIpAddr,2);
				// g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, Temp);
			}
		}
		break;

		case OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_ONLINE_PLAY:
		{
			if (lpMsg->btServerCode > 10)
			{
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Select TOP 1 name, date, type from Credit_Log where acc = '%s' order by date desc", szAccountID);
				g_DB.Fetch();
				// ----
				g_DB.GetStr("name", nameCheck);
				g_DB.GetStr("date", dateCheck);
				g_DB.GetStr("type", typeCheck);
				// ----
				g_DB.Clear();
				// ----
				sprintf(Temp, "ConnectedTo %d", lpMsg->btServerCode);
				if((_strcmpi(nameCheck, "tmp") == 0) && 	(_strcmpi(typeCheck, Temp) == 0))
				{
					ObjectLogHistoryUpdateLine(szNick, szAccountID, dateCheck, szIpAddr);
				}
				else
				{
					ObjectLogHistoryAdd(szNick, szAccountID, Temp, szIpAddr,2);
				}
				
			}
			else
			{
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Select TOP 1 name, date, type from Credit_Log where acc = '%s' order by date desc", szAccountID);
				g_DB.Fetch();
				// ----
				g_DB.GetStr("name", nameCheck);
				g_DB.GetStr("date", dateCheck);
				g_DB.GetStr("type", typeCheck);
				// ----
				g_DB.Clear();
				// ----
				sprintf(Temp, "ConnectedTo %d", lpMsg->btServerCode+1);
				if((_strcmpi(nameCheck, "tmp") == 0) && 	(_strcmpi(typeCheck, Temp) == 0))
				{
					ObjectLogHistoryUpdateLine(szNick, szAccountID, dateCheck, szIpAddr);
				}
				else
				{

					ObjectLogHistoryAdd(szNick, szAccountID, Temp, szIpAddr,2);
				}
			}
		}
		break;

		case OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_CHARSELECT:
		{
			/*g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, "char select");
			sprintf(Temp, "CharSelect %d", lpMsg->btServerCode+1);
			ObjectLogHistoryAdd(szNick, szAccountID, Temp, szIpAddr);*/
		}
		break;

		case OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_CS_ONLINE:
		{
			//g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, "connected cs");
			ObjectLogHistoryAdd(szNick, szAccountID, "ConnectedTo CS", szIpAddr,2);
		}
		break;

		case OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_DEL_CHAR:
		{
			//g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, "del char");
			ObjectLogHistoryAdd(szNick, szAccountID, "DelChar", szIpAddr,7);
		}
		break;

		case OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_CREATE_CHAR:
		{
			//g_Log.AddC(0, "ConnectionCharacters", __FUNCTION__, TColor::LightCyan, "cre char");
			ObjectLogHistoryAdd(szNick, szAccountID, "CreateChar", szIpAddr,7);
		}
		break;

		default:
		{
			g_Log.AddC(0, g_ModuleName, __FUNCTION__, TColor::Red, "Unknow error");
		}
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------------------
/*
void MarrigeInfo(TIOCPHandler * h, uint64_t cid, MSG_MARRY_SYSTEM_INFO * lpMsg)
{
	int			aIndex;
	int			Status;
	int			MarryType;
	int			IsMarried;
	char		MarryName[11];
	// ----
	MSG_MARRY_SYSTEM_INFO_R pMsg = {0};
	// ----
	memcpy(pMsg.szName,		lpMsg->szName,		sizeof(lpMsg->szName));
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_MARRY_SYSTEM_INFO_R);
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Select IsMarried, MarryName from Character where AccountId = '%s' and Name ='%s'", lpMsg->szAccountID, lpMsg->szName);
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		
		// ----
		pMsg.IsMarried = g_DB.GetInt("IsMarried");
		pMsg.MarryType = 0;
		g_DB.GetStr("MarryName",MarryName);
		// ----
		g_DB.Clear();
		// ----
		pMsg.aIndex				=lpMsg->aIndex;
		memcpy(pMsg.MarryName, MarryName, sizeof(pMsg.MarryName));
		// ----
		h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
	}
}*/

//-----------------------------------------------------------------------------------------------------------------------

void MarrigeUpdate (TIOCPHandler * h, uint64_t cid, MSG_MARRY_SYSTEM_UPDATE * lpMsg)
{
	if (lpMsg->MarrigeStatus)
	{
		int MarryTime1, MarryTime2;
		// ----
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Select MarryTimes from Character where Name ='%s'", lpMsg->MarryName1);
		g_DB.Fetch();
		// ----
		MarryTime1= g_DB.GetInt("MarryTimes");
		MarryTime1++;
		// ----
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Select MarryTimes from Character where Name ='%s'", lpMsg->MarryName2);
		g_DB.Fetch();
		// ----
		MarryTime2= g_DB.GetInt("MarryTimes");
		MarryTime2++;
		// ----
		g_DB.Clear();
		time_t rawtime;
		struct tm * timeinfo;
		char buffer [80];
		// ----
		time(& rawtime);
		// ----
		timeinfo = localtime (& rawtime);
		// ----
		strftime (buffer, 80, "%c", timeinfo);
		// ----
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Update Character SET IsMarried = 1, MarryName = '%s', MarryDate='%s', MarryTimes = %d where Name = '%s'",lpMsg->MarryName2, buffer, MarryTime1, lpMsg->MarryName1);
		g_DB.Fetch();
		g_DB.Clear();
		// ----
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Update Character SET IsMarried = 1, MarryName = '%s', MarryDate='%s', MarryTimes = %d where Name = '%s'",lpMsg->MarryName1, buffer, MarryTime2, lpMsg->MarryName2);
		g_DB.Fetch();
		g_DB.Clear();
	}
	else
	{
	
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Update Character Set IsMarried = 0, MarryName = 'NULL' where Name = '%s'", lpMsg->MarryName1);
		g_DB.Fetch();
		g_DB.Clear();
		// ----
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Update Character Set IsMarried = 0, MarryName = 'NULL' where Name = '%s'", lpMsg->MarryName2);
		g_DB.Fetch();
		g_DB.Clear();
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void SkinCheckStatus (TIOCPHandler * h, uint64_t cid, MSG_SKIN_CHECK * lpMsg)
{
	char szGMName [11]  = {0};
	char szName [11]  = {0};
	char szAccountID[11] = {0};
	int SkinChange = 0;
	// ----
	memcpy(szGMName,		lpMsg->szGMName,		sizeof(lpMsg->szGMName));
	memcpy(szName,			lpMsg->szName,			sizeof(lpMsg->szName));
	memcpy(szAccountID,		lpMsg->szAccountID,		sizeof(lpMsg->szAccountID));
	// ----
	MSG_SKIN_CHECK_R pMsg = {0};
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT SkinChange FROM GM WHERE AccName = '%s' and GMName = '%s'", szAccountID, szGMName);
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		SkinChange = g_DB.GetInt("SkinChange");
	}
	else
	{
		objectMsgToNick(h, cid, szName, "@You Don't have access to this command");
		pMsg.Status = 0;
	}
	// ----
	g_DB.Clear();

	if (SkinChange != 0)
	{
		pMsg.Status = SkinChange;
	}
	pMsg.MID = lpMsg->MID;
	char Temp [1024] = {0};
	// ----	
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_SKINACCESS);
	// ----
	memcpy(pMsg.szGMName,		lpMsg->szGMName, sizeof(lpMsg->szGMName));
	memcpy(pMsg.szName,			lpMsg->szName, sizeof(lpMsg->szName));
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------
// # Friend Memo Update
//-----------------------------------------------------------------------------------------------------------------------

void PHPFriendMemoDelRequest(TIOCPHandler * h, uint64_t cid, MSG_FREINDMEMO_DEL * lpMsg)
{
	char szName[11] = {0};
	// ----
	memcpy(szName, lpMsg->szName, sizeof(lpMsg->szName));
	// ----
	FriendMemoDelSend(szName, lpMsg->MemoIndex);
}
//-----------------------------------------------------------------------------------------------------------------------

void FriendMemoDelSend(char * Name, int MemoIndex)
{
	MSG_FREINDMEMO_DEL pMsg = {0};
	// ----
	memcpy(pMsg.szName,	Name,	sizeof(pMsg.szName));
	// ----
	pMsg.MemoIndex = MemoIndex;
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_FREINDMEMO_DEL);
	// ----
	g_IOCP->sendAll((UCHAR *) & pMsg, sizeof(pMsg));
}

//-----------------------------------------------------------------------------------------------------------------------

void PHPFriendListAdd(TIOCPHandler * h, uint64_t cid, MSG_FREINDMEMO_ADD * lpMsg)
{
	char RecvName[11]	= {0};
	char SendName[11]	= {0};
	char Subject[50]	= {0};
	// ----
	memcpy(RecvName, lpMsg->RecvName, sizeof(lpMsg->RecvName));
	memcpy(SendName, lpMsg->SendName, sizeof(lpMsg->SendName));
	memcpy(Subject, lpMsg->Subject, sizeof(lpMsg->Subject));
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::Pink, "recvName: `%s`, sendName: `%s`, subject: '%s`",
		RecvName, SendName, Subject);
	// ----
	FriendMemoListAdd(SendName, RecvName, lpMsg->MemoIndex, Subject);
}
//-----------------------------------------------------------------------------------------------------------------------

void FriendMemoListAdd(char * SendName, char * RecvName, USHORT MemoIndex, char * Subject)
{
	MSG_FREINDMEMO_ADD_GS pMsg = {0};
	// ----
	memcpy(pMsg.SendName,		SendName,	sizeof(pMsg.SendName));
	memcpy(pMsg.RecvName,		RecvName,	sizeof(pMsg.RecvName));
	memcpy(pMsg.Subject,		Subject,	sizeof(pMsg.Subject));
	// ----
	
	time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	// ----
	memcpy(pMsg.Date,		buf,	sizeof(pMsg.Date));
	pMsg.MemoIndex = MemoIndex;
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_FRIENDMEMO_ADD);
	// ----
	g_IOCP->sendAll((UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void PHPFriendListRead(TIOCPHandler * h, uint64_t cid, MSG_FREINDMEMO_READ * lpMsg)
{
	char RecvName[11]	= {0};
	char SendName[11]	= {0};
	char Subject[50]	= {0};
	// ----
	memcpy(RecvName, lpMsg->RecvName, sizeof(lpMsg->RecvName));
	memcpy(SendName, lpMsg->SendName, sizeof(lpMsg->SendName));
	memcpy(Subject, lpMsg->Subject, sizeof(lpMsg->Subject));	
	// ----
	FriendMemoRead(SendName, RecvName, lpMsg->MemoIndex, Subject);
}
//-----------------------------------------------------------------------------------------------------------------------
void FriendMemoRead(char * SendName, char * RecvName, USHORT MemoIndex, char * Subject)
{
	MSG_FREINDMEMO_READ pMsg = {0};
	// ----
	memcpy(pMsg.RecvName,		RecvName,	sizeof(pMsg.RecvName));
	memcpy(pMsg.SendName,		SendName,	sizeof(pMsg.SendName));
	memcpy(pMsg.Subject,		Subject,	sizeof(pMsg.Subject));
	// ----	
	pMsg.MemoIndex = MemoIndex;
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_FRIENDMEMO_READ);
	// ----
	g_IOCP->sendAll((UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void InvisiableChange (TIOCPHandler * h, uint64_t cid, MSG_INVISIBLE_COMMAND * lpMsg)
{
	// ----
	char Name [11]  = {0};
	char AccountId [11]  = {0};
	int CltCode = 0;
	// ----
	memcpy(Name,		lpMsg->szGMName,		sizeof(lpMsg->szGMName));
	memcpy(AccountId,		lpMsg->szAccountID,		sizeof(lpMsg->szAccountID));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "select CtlCode FROM Character WHERE AccountId = '%s' and Name = '%s'", AccountId, Name);
	if (g_DB.Fetch() != SQL_NO_DATA)
	{
		CltCode = g_DB.GetInt("CtlCode");
		g_DB.Clear();
		if (CltCode == 8 || CltCode == 32)
		{
			if(lpMsg->status == false)
			{
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Update Character Set CtlCode = 32 WHERE AccountId = '%s' and Name = '%s'", AccountId, Name);
			}
			else
			{
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Update Character Set CtlCode = 8 WHERE AccountId = '%s' and Name = '%s'", AccountId, Name);
			}
			g_DB.Fetch();
			g_DB.Clear();
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void InvisiableCrewChange (TIOCPHandler * h, uint64_t cid, MSG_INVISIBLE_CREW_COMMAND * lpMsg)
{	
	char Name [10]  = {0};
	char AccountId [10]  = {0};
	int CltCode = 0;
	// ----
	memcpy(Name,		lpMsg->szGMName,		sizeof(lpMsg->szGMName));
	memcpy(AccountId,		lpMsg->szAccountID,		sizeof(lpMsg->szAccountID));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "select CtlCode FROM Character WHERE AccountId = '%s' and Name = '%s'", AccountId, Name);
	if (g_DB.Fetch() != SQL_NO_DATA)
	{
		CltCode = g_DB.GetInt("CtlCode");
		g_DB.Clear();
		if (CltCode == 8 || CltCode ==32)
		{
			if(lpMsg->status == false)
			{
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Update Character Set isCrewInfoAllow = 0 WHERE AccountId = '%s' and Name = '%s'", AccountId, Name);
			}
			else
			{
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "Update Character Set isCrewInfoAllow = 1 WHERE AccountId = '%s' and Name = '%s'", AccountId, Name);
			}
			g_DB.Fetch();
			g_DB.Clear();
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void GuildMemberCheckStatus (TIOCPHandler * h, uint64_t cid, MSG_GUILD_MEMBER_STATUS * lpMsg)
{	
	char AssistName [10]  = {0};
	char MemberName [10]  = {0};
	char GuildName [10]  = {0};
	int GuildStatus = 0;
	// ----
	memcpy(AssistName,		lpMsg->AssistName,		sizeof(lpMsg->AssistName));
	memcpy(MemberName,	lpMsg->MemberName,		sizeof(lpMsg->MemberName));
	memcpy(GuildName,	lpMsg->GuildName,		sizeof(lpMsg->GuildName));
	// ----
	MSG_GUILD_MEMBER_STATUS_R pMsg = {0};
	// ----
	pMsg.Status = -1;
	// ----
	// # Checks if the Player is realy Assist Guild
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "select Name FROM GuildMember WHERE G_Name = '%s' and Name = '%s' and G_Status = %d", GuildName, AssistName, GUILD_ASSIST_STATUS);
	// ----
	if (g_DB.Fetch() != SQL_NO_DATA)
	{
		g_DB.Clear();
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT G_AssistAccess FROM Guild WHERE G_Name = '%s'", GuildName);
		g_DB.Fetch();
		// ----
		if (g_DB.GetInt("G_AssistAccess") == 0)
		{
			pMsg.Status = 8; // Can't change - doesn't have acess
		}
		else
		{
			// ----
			// # Checks that Guild Don't have more then 2 Battles
			// ----
			g_DB.Clear();
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "select count(*) FROM GuildMember WHERE G_Name = '%s' and G_Status = %d", GuildName, GUILD_BATTLE_STATUS); // Get Num Rows from SELECT
			g_DB.Fetch(); 
			// ----
			int NumRows = 0;
			// ----
			NumRows = g_DB.GetInt(0);
			// ----
			if (NumRows < 2 || lpMsg->Type == 0) // Checking Battle number < 2
			{
				g_DB.Clear();
				// ----
				// # Checks that the member is in the Guild and not Manager
				// ----
				g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "select Name, G_Status FROM GuildMember WHERE G_Name = '%s' and Name = '%s'", GuildName, MemberName);
				if (g_DB.Fetch() != SQL_NO_DATA)
				{
					GuildStatus = g_DB.GetInt("G_Status");
					// ----
					g_DB.GetStr("Name", MemberName);
					// ----
					if (GuildStatus == 128)
					{
						pMsg.Status = 7; // Trying to change to Manager
					}
					else
					{
						if(GuildStatus != lpMsg->Type)
						{
							// OK
							if (lpMsg->Type == 32 || lpMsg->Type == 0)
								pMsg.Status = 1;
							else
								pMsg.Status = 6;
						}
						else
						{
							pMsg.Status = 2; // Trying to change to the same status
						}
					}
				
				}
				else
				{
					pMsg.Status = 3; // Trying to change to player that he is not a member of the guild
				}
			}
			else
			{
				pMsg.Status = 4; // Has 2 Battles already
			}
		}
	}
	else
	{
		pMsg.Status = 5; // not an Assist
	}
	// ----
	g_DB.Clear();
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GUILD_MEMBER_STATUS);
	// ----
	memcpy(pMsg.AssistName,		AssistName,		sizeof(AssistName));
	memcpy(pMsg.MemberName,		MemberName,		sizeof(MemberName));
	memcpy(pMsg.GuildName,		GuildName,		sizeof(GuildName));
	// ----
	pMsg.Type = lpMsg->Type;
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void GuildKickMemberCheck (TIOCPHandler * h, uint64_t cid, MSG_GUILD_KICK_MEMBER * lpMsg)
{	
	char AssistName [10]  = {0};
	char MemberName [10]  = {0};
	char GuildName [10]  = {0};
	int GuildStatus = 0;
	// ----
	memcpy(AssistName,		lpMsg->AssistName,		sizeof(lpMsg->AssistName));
	memcpy(MemberName,	lpMsg->MemberName,		sizeof(lpMsg->MemberName));
	memcpy(GuildName,	lpMsg->GuildName,		sizeof(lpMsg->GuildName));
	// ----
	MSG_GUILD_KICK_MEMBER_R pMsg = {0};
	// ----
	pMsg.Status = -1;
	// ----
	// # Checks if the Player is realy Assist Guild
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "select Name FROM GuildMember WHERE G_Name = '%s' and Name = '%s' and G_Status = %d", GuildName, AssistName, GUILD_ASSIST_STATUS);
	// ----
	if (g_DB.Fetch() != SQL_NO_DATA)
	{
		g_DB.Clear();
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT G_AssistAccess FROM Guild WHERE G_Name = '%s'", GuildName);
		g_DB.Fetch();
		// ----
		if (g_DB.GetInt("G_AssistAccess") == 0)
		{
			pMsg.Status = 5; // Can't change - doesn't have acess
		}
		else
		{
			g_DB.Clear();
			// ----
			// # Checks that the member is in the Guild and not Manager
			// ----
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "select Name, G_Status FROM GuildMember WHERE G_Name = '%s' and Name = '%s'", GuildName, MemberName);
			if (g_DB.Fetch() != SQL_NO_DATA)
			{
				GuildStatus = g_DB.GetInt("G_Status");
				// ----
				g_DB.GetStr("Name", MemberName);
				// ----
				if(GuildStatus != GUILD_MANAGER_STATUS)
				{
					pMsg.Status = 1;
				}
				else
				{
					pMsg.Status = 2; // Trying to kick manager
				}
			}
			else
			{
				pMsg.Status = 3; // Trying to change to player that he is not a member of the guild
			}
		}
	}
	else
	{
		pMsg.Status = 4; // Not an Assist
	}
	// ----
	g_DB.Clear();
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GUILD_KICK_MEMBER);
	// ----
	memcpy(pMsg.AssistName,		AssistName,		sizeof(AssistName));
	memcpy(pMsg.MemberName,		MemberName,		sizeof(MemberName));
	memcpy(pMsg.GuildName,		GuildName,		sizeof(GuildName));
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void GuildSetAssistCheck (TIOCPHandler * h, uint64_t cid, MSG_GUILD_SET_ASSIST * lpMsg)
{	
	char ManagerName [10]  = {0};
	char GuildName [10]  = {0};
	char Temp[300] = {0};
	// ----
	memcpy(ManagerName,	lpMsg->ManagerName,		sizeof(lpMsg->ManagerName));
	memcpy(GuildName,	lpMsg->GuildName,		sizeof(lpMsg->GuildName));
	// ----
	// # Checks if the Player is realy Guild Manager
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Name FROM GuildMember WHERE G_Name = '%s' and Name = '%s' and G_Status = %d", GuildName, ManagerName, GUILD_MANAGER_STATUS);
	// ----
	if (g_DB.Fetch() != SQL_NO_DATA)
	{
		// ----
		// # Checks that the member is an Assist
		// ----
		if (lpMsg->Type == 0 || lpMsg->Type == 1)
		{
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE Guild SET G_AssistAccess = %d WHERE G_Name = '%s'", lpMsg->Type, GuildName);
			g_DB.Fetch();
			// ----
			objectMsgToNick(h,cid,ManagerName,"@Assist access changed");
		}
		else
		{
			objectMsgToNick(h,cid,ManagerName,"@Unknows Error #2");
		}
		
	}
	else
	{
		objectMsgToNick(h,cid,ManagerName,"@You are not a Guild Manager");
	}
	// ----
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

void GuildJoinRequestAssist (TIOCPHandler * h, uint64_t cid, MSG_GUILD_JOIN_REQUEST * lpMsg)
{	
	MSG_GUILD_JOIN_REQUEST_R pMsg = {0};
	// ----
	char AssistName [10]  = {0};
	char ReqName [10]  = {0};
	char Guild[100] = {0};
	// ----
	memcpy(AssistName,	lpMsg->AssistName,		sizeof(lpMsg->AssistName));
	memcpy(ReqName,	lpMsg->ReqName,		sizeof(lpMsg->ReqName));
	// ----
	// # Checks if the Player is realy Guild Manager
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT G_Name FROM GuildMember WHERE Name = '%s' and G_Status = %d", AssistName, GUILD_ASSIST_STATUS);
	// ----
	if (g_DB.Fetch() != SQL_NO_DATA)
	{
		g_DB.GetStr("G_Name", Guild);
		// ----
		g_DB.Clear();
		// ----
		// # Checks that the Assist has permissions
		// ----
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Name FROM Guild WHERE G_AssistAccess = 1 and G_Name = '%s'", Guild);
		g_DB.Fetch();
		// ----
		if (g_DB.GetInt("G_AssistAccess") == 0)
		{
			objectMsgToNick(h,cid,ReqName,"@Guild Assist doesn't have permission to add");
		}
		else
		{
			HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GUILD_JOIN_REQUEST);
			// ----
			memcpy(pMsg.AssistName,		AssistName,		sizeof(AssistName));
			memcpy(pMsg.ReqName,		ReqName,		sizeof(ReqName));
			// ----
			pMsg.Status = 1;
			// ----
			h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
		}
	}
	else
	{
		objectMsgToNick(h,cid,ReqName,"@Player is not Guild Assist");
	}
	// ----
	g_DB.Clear();	
}
//-----------------------------------------------------------------------------------------------------------------------

void EventKillCheck (TIOCPHandler * h, uint64_t cid, MSG_KILLEVENT_CHECKPOINTS * lpMsg)
{	
	char Nick [11]  = {0};
	char tNick [11]  = {0};
	char player1Nick[11] = {0};
	char Temp2[1024] = {0};
	// ----
	memcpy(Nick,	lpMsg->Nick,		sizeof(lpMsg->Nick));
	memcpy(tNick,	lpMsg->tNick,		sizeof(lpMsg->tNick));
	// ---
	int player1Kills = 0, player2Kills = 0;
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT killEvent FROM Character WHERE Name = '%s'", Nick); 
	// ----
	if (g_DB.Fetch() != SQL_NO_DATA)
	{
		player2Kills = g_DB.GetInt("killEvent");
		if (player2Kills > 0)
		{
			g_DB.Clear();
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT killEvent, killEventPl, KillEventDay FROM Character WHERE Name = '%s'", tNick);
			if (g_DB.Fetch() != SQL_NO_DATA)
			{
				player1Kills = g_DB.GetInt("killEvent");
				g_DB.GetStr("killEventPl", player1Nick);
				// ----
				if (_strcmpi(player1Nick, Nick) != 0)
				{
					g_DB.Clear();
					// ----
					player2Kills --;
					player1Kills ++;
					// ----
					g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE Character SET killEvent = %d, KillEventDay = KillEventDay-1 WHERE Name = '%s'", player2Kills, Nick);
					g_DB.Fetch();
					g_DB.Clear();
					// ----
					g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE Character SET killEvent = %d, killEventPl = '%s', KillEventDay = KillEventDay+1 WHERE Name = '%s'", player1Kills, Nick, tNick);
					g_DB.Fetch();
					objectMsgToNick(h,cid,tNick, "@[TopKill] נוספה לך נקודה");
					objectMsgToNick(h,cid,Nick, "@[TopKill] ירדה לך נקודה");
				}
			}
			else
			{
				objectMsgToNick(h,cid,lpMsg->Nick,"@Error Kill Event 2");
			}
		}
	}
	else
	{
		objectMsgToNick(h,cid,lpMsg->Nick,"@Error Kill Event 1");
	}
	// ----
	g_DB.Clear();	
}
//-----------------------------------------------------------------------------------------------------------------------

void ShopBuyRequest(TIOCPHandler * h, uint64_t cid, MSG_SHOP_BUY_ITEM_REQUEST * lpMsg)
{
	MSG_SHOP_BUY_ITEM_RESULT pMsg = { 0 };
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_SHOP_BUY_RESULT);
	// ----
	int iCoins;
	// ----
	pMsg.iShopId = lpMsg->iShopId;
	pMsg.bProductPos = lpMsg->bProductPos;
	// ----
	memcpy(pMsg.szAccountId, lpMsg->szAccountId, sizeof(lpMsg->szAccountId));
	memcpy(pMsg.szName, lpMsg->szName, sizeof(lpMsg->szName));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Coins FROM MEMB_INFO WHERE memb___id = '%s'", pMsg.szAccountId);
	// ----
	if (g_DB.Fetch() != SQL_NO_DATA)
	{
		iCoins = g_DB.GetInt("Coins");
	}
	// ----
	g_DB.Clear();
	// ----
	if (lpMsg->iPrice > iCoins) {
		pMsg.bResult = SHOP_BUY_RESULT::SHOP_BUY_RESULT_NOCOINS;
	} else {
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_INFO SET Coins = Coins - %d WHERE memb___id = '%s'", lpMsg->iPrice, pMsg.szAccountId);
		g_DB.Fetch();
		g_DB.Clear();
		// ----
		pMsg.bResult = SHOP_BUY_RESULT::SHOP_BUY_RESULT_SUCESSS;
		g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "Info for (%s) - Bought Item for %d , State : %d", pMsg.szAccountId, lpMsg->iPrice, pMsg.bResult);
	}
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *)& pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void OffTradeRequest(TIOCPHandler * h, uint64_t cid, MSG_S_OFFTRADE * lpMsg)
{
	int nPrice = 0;
	int nSQLPrice = 0;
	int nState = -1;
	// ----
	char szAccountId[11] = { 0 };
	char szNickName[11] = { 0 };
	// ----
	memcpy(szAccountId, lpMsg->szAccountID, sizeof(lpMsg->szAccountID));
	memcpy(szNickName, lpMsg->szNickName, sizeof(lpMsg->szNickName));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT Credits FROM MEMB_INFO WHERE memb___id = '%s'", szAccountId);
	g_DB.Fetch();
	// ----
	nSQLPrice = g_DB.GetInt("Credits");
	g_DB.Clear();

	if (nSQLPrice != -100)
	{
		if (nSQLPrice >= lpMsg->nPrice)
		{
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE MEMB_INFO SET Credits = Credits - %d WHERE memb___id = '%s'", lpMsg->nPrice, szAccountId);
			g_DB.Fetch();
			g_DB.Clear();
			// ----
			ObjectLogCreditAdd(szNickName, szAccountId, (int)lpMsg->nPrice, "OffTrade", 5);
			// ----
			nState = 1;
			nPrice = 1;
		}
		else
		{
			nState = 2; // NO CREDITDS
		}
	}

	// ----
	MSG_R_OFFTRADE pMsg = { 0 };
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_OFFTRADE);
	// ----
	pMsg.nState = nState;
	pMsg.nPrice = nPrice;
	pMsg.nIndex = lpMsg->nIndex;
	// ----
	// # Log
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "Info for (%s) - Credits : %d, State : %d", szAccountId, pMsg.nPrice, pMsg.nState);
	// ----
	// # Send
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *)& pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void RedDragonRequest(TIOCPHandler * h, uint64_t cid, MSG_S_REDDRAGON * lpMsg)
{
	int nDragonAccount = 0;
	int nState = -1;
	// ----
	char szAccountId[11] = { 0 };
	char szNickName[11] = { 0 };
	// ----
	memcpy(szAccountId, lpMsg->szAccountID, sizeof(lpMsg->szAccountID));
	memcpy(szNickName, lpMsg->szNickName, sizeof(lpMsg->szNickName));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT COUNT(*) as TEMP FROM GM_REDDRAGON_LOG WHERE memb___id = '%s' AND actiontime >= GETDATE()-1 ", szAccountId);
	g_DB.Fetch();
	// ----
	nDragonAccount = g_DB.GetInt("TEMP");
	g_DB.Clear();

	if (nDragonAccount != -100)
	{
		if (nDragonAccount < 1 || strcmp(szAccountId, "elad263") == 0 || strcmp(szAccountId, "MMOG2") == 0 || strcmp(szAccountId, "hagaibl123") == 0)
		{
			g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "INSERT INTO GM_REDDRAGON_LOG (memb___id, actiontime) VALUES('%s', GETDATE())", szAccountId);
			g_DB.Fetch();
			g_DB.Clear();
			// ----
			// ----
			nState = 1;
		}
		else
		{
			nState = 2; // NO MORE QOUTA
		}
	}

	// ----
	MSG_R_REDDRAGON pMsg = { 0 };
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_REDDRAGON);
	// ----
	pMsg.nState = nState;
	pMsg.nIndex = lpMsg->nIndex;
	// ----
	// # Log
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "Info for (%s) Tried to summon RedDragon, State : %d", szAccountId, pMsg.nState);
	// ----
	// # Send
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *)& pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void FixLevelBugRequest(TIOCPHandler * h, uint64_t cid, MSG_S_FIX_LEVEL_BUG * lpMsg)
{
	int nState = -1;
	int nLevel = -1;
	char szName[11] = { 0 };
	ULONGLONG nExp = 0;
	// ----
	nLevel = lpMsg->iLevel;
	memcpy(szName, lpMsg->szName, sizeof(lpMsg->szName));
	// ----
	g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "SELECT TOP 1 Experience from Character WHERE cLevel = %d", nLevel);
	g_DB.Fetch();
	// ----
	nExp = (ULONGLONG)g_DB.GetInt64("Experience");
	g_DB.Clear();

	if (nExp != -100)
	{
		g_DB.ExecFormat(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, "UPDATE Character SET Experience = '%d' WHERE Name = '%s'", nExp, szName);
		g_DB.Fetch();
		g_DB.Clear();
		// ----
		nState = 0;
	}
	else {
		nState = 2; // Something went wrong
	}

	// ----
	MSG_R_FIX_LEVEL_BUG pMsg = { 0 };
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_FIXLEVELBUG);
	// ----
	pMsg.nIndex = lpMsg->nIndex;
	pMsg.nState = nState;
	// ----
	// # LOG
	// ----
	g_Log.AddC(g_Obj[cid].m_GSCode, g_ModuleName, __FUNCTION__, TColor::White, "Fix Bug Levl for Character: %s, State : %d", szName, pMsg.nState);
	// ----
	// # Send
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *)& pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void SendMessageToAllServers(const char* szMessage)
{

	MSG_SENDNOTICEALLFROMDS pMsg = { 0 };
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_MESSAGE_ALL);
	// ----
	memcpy(pMsg.Notice, szMessage, strlen(szMessage));
	pMsg.NoticeLen = strlen(szMessage);

	g_IOCP.get()->sendAll((UCHAR *)& pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void AntiHackProcessNotify(TIOCPHandler * h, uint64_t cid, MSG_ANTIHACK_PROCESS_NOTIFY * lpMsg)
{
	char szAccountId[sizeof(MSG_ANTIHACK_PROCESS_NOTIFY::szAccountId) + 1] = { 0 };
	char szIpAddr[sizeof(MSG_ANTIHACK_PROCESS_NOTIFY::szIpAddr) + 1] = { 0 };
	char szProcess[sizeof(MSG_ANTIHACK_PROCESS_NOTIFY::szProcess) + 1] = { 0 };

	memcpy(szAccountId, lpMsg->szAccountId, sizeof(MSG_ANTIHACK_PROCESS_NOTIFY::szAccountId));
	memcpy(szIpAddr, lpMsg->szIpAddr, sizeof(MSG_ANTIHACK_PROCESS_NOTIFY::szIpAddr));
	memcpy(szProcess, lpMsg->szProcess, sizeof(MSG_ANTIHACK_PROCESS_NOTIFY::szProcess));


	static BYTE gsCode = g_Obj[cid].m_GSCode;

	g_Log.AddC(gsCode, g_ModuleName, __FUNCTION__, TColor::Chartreuse, "`%s` ip: `%s` account: `%s` checksum: `%I64u`",
		szProcess, szIpAddr, szAccountId, lpMsg->uChecksum);


	for (auto checksum : g_Config.GoodProcessesList) {
		if (lpMsg->uChecksum == checksum) {
			g_Log.AddC(gsCode, g_ModuleName, __FUNCTION__, TColor::Orange, "[%s][%s] - Skip Proccess whitelisted, process: [%s] | Hash: [%I64u]",
				szIpAddr, szAccountId, szProcess, lpMsg->uChecksum);

			return;
		}
	}


	g_DB.Clear();
	g_DB.ExecFormat(gsCode, g_ModuleName, __FUNCTION__, "SELECT checksum FROM AntiHackProcesses WHERE account = '%s' AND process = '%s' AND ip = '%s'", szAccountId, szProcess, szIpAddr);

	if (g_DB.Fetch() == SQL_NO_DATA) {
		g_DB.Clear();

		g_DB.ExecFormat(gsCode, g_ModuleName, __FUNCTION__, "INSERT INTO AntiHackProcesses (ip, account, process, checksum, date) VALUES \
				('%s', '%s', '%s', '%I64u', getdate());", szIpAddr, szAccountId, szProcess, lpMsg->uChecksum);
		g_DB.Fetch();
		g_DB.Clear();
	}
	else
	{
		ULONGLONG checksum = g_DB.GetInt64("checksum");
		g_DB.Clear();

		if (lpMsg->uChecksum != checksum) {
			g_DB.ExecFormat(gsCode, g_ModuleName, __FUNCTION__, "UPDATE AntiHackProcesses SET checksum = '%I64u', date = GETDATE() WHERE account = '%s' AND process = '%s' AND checksum = '%I64u'",
				lpMsg->uChecksum, szAccountId, szProcess, checksum);
			g_DB.Fetch();
			g_DB.Clear();
		}
	}

	for (auto checksum : g_Config.BadProcessesList) {
		if (lpMsg->uChecksum == checksum) {
			g_Log.AddC(gsCode, g_ModuleName, __FUNCTION__, TColor::Orange, "[%s][%s] - Disconnect has been sent, process: [%s] | Hash: [%I64u]",
				szIpAddr, szAccountId, szProcess, lpMsg->uChecksum);

			ObjectDcToAccount(h, cid, szAccountId);

			break;
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------