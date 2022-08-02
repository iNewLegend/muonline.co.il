#include "StdAfx.h"
#include "DSXProtocol.h"
#include "TDataServerSocket.h"
#include "Object.h"
#include "TSetup.h"
#include "TMessages.h"
#include "TLogToFile.h"
#include "Chat.h"
#include "TChatVote.h"
#include "TConfig.h"
#include "TBotSystem.h"
#include "Item.h"
#include "TShop.h"
#include "OffTrade.h"
#include "RedDragon.h"
#include "VIPSystem.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void vDSProtocolCore(unsigned char * pRecv, int aLen)
{
	if(pRecv[0] == 1)
	{
		MSG_HEADER * lpHead = (MSG_HEADER *) pRecv;
		// ----
		#pragma region basicPackets
		// ----
		switch(lpHead->ProtocolId)
		{
			case HEAD_GETSTARTUP:
			{
				MSG_STARTUP * pMsg = (MSG_STARTUP*) pRecv;
				// ----
				g_Config.nNoobServerCsResets = pMsg->Resets;
				g_Config.bCsExSets = pMsg->CsSets;
				g_RUNEVENT_STATE = pMsg->RunEventState;
			}
			break;

			case HEAD_EXTRAINFO:
			{
				MSG_R_EXTRAINFO * pMsg = (MSG_R_EXTRAINFO *) pRecv;
				// ----
				ObjectExtraInfoResult(pMsg->nIndex, pMsg);
			}
			break;

			case HEAD_GO:
			{
				MSG_R_GO * pMsg = (MSG_R_GO*) pRecv;
				// ----
				ObejctGoState(1, pMsg->nIndex, pMsg->nTargetIndex, pMsg->nPrice, pMsg->bState);
			}
			break;

			case HEAD_KUADNM:
			{
				MSG_R_KANDUM * pMsg = (MSG_R_KANDUM*) pRecv;
				// ----
				ObejctKandumState(1, pMsg->nIndex, pMsg->nPrice, pMsg->nState);
			}
			break;

			case HEAD_OFFTRADE:
			{
				MSG_R_OFFTRADE * pMsg = (MSG_R_OFFTRADE*)pRecv;
				// ----
				g_OffTrade.CreateOfflineTrade(1, pMsg->nIndex, pMsg->nPrice, pMsg->nState);
			}
			break;

			case HEAD_REDDRAGON:
			{
				MSG_R_REDDRAGON * pMsg = (MSG_R_REDDRAGON*)pRecv;
				// ----
				g_RedDragon.CreateRedDragon(1, pMsg->nIndex, pMsg->nState);
			}
			break;

			case HEAD_FIXLEVELBUG:
			{
				MSG_R_FIX_LEVEL_BUG * pMsg = (MSG_R_FIX_LEVEL_BUG*)pRecv;
				// ----
				if (pMsg->nState == 2)
				{
					g_Msg.PM(pMsg->nIndex, "[Fix Level Bug] Something went wrong");
					g_Msg.PM(pMsg->nIndex, "[Fix Level Bug] משהו השתבש");
					break;
				}
				g_Msg.PM(pMsg->nIndex, "[Fix Level Bug] Fixed, please re login");
				g_Msg.PM(pMsg->nIndex, "[Fix Level Bug] תוקן, אנא התחבר מחדש");
			}
			break;

			case HEAD_MESSAGE_ALL:
			{
				MSG_R_GLOAL_MSG * pMsg = (MSG_R_GLOAL_MSG*)pRecv;

				DGSendMessageAllRecive(pMsg);
			}
			break;

			case HEAD_NOTICEALL:
			{
				MSG_R_POST * pMsg = (MSG_R_POST*) pRecv;
				// ----
				char szNick[11] = {0};
				char szMsg[101]	= {0};
				// ----
				memcpy(szNick, pMsg->szNick, sizeof(pMsg->szNick));
				memcpy(szMsg, pMsg->szMsg, sizeof(pMsg->szMsg));
				// ----
				ObjectPostAll(szNick, szMsg);
			}
			break;

			case HEAD_NOTICEALLGM:
			{
				MSG_R_POST * pMsg = (MSG_R_POST*) pRecv;
				// ----
				char szNick[11] = {0};
				char szMsg[101]	= {0};
				// ----
				memcpy(szNick, pMsg->szNick, sizeof(pMsg->szNick));
				memcpy(szMsg, pMsg->szMsg, sizeof(pMsg->szMsg));
				// ----
				ObjectPostAllGM(szNick, szMsg);
			}
			break;

			case HEAD_GUILDMSG:
			{
				MSG_GUILD * pMsg = (MSG_GUILD*) pRecv;
				// ----
				ObjectGuildMsgAll(pMsg->nServerNumber, pMsg->szNick, pMsg->szMsg, pMsg->szGuildName, pMsg->G_Status);
			}
			break;

			case HEAD_MSGTONICK:
			{
				MSG_MSGTONICK * pMsg = (MSG_MSGTONICK *) pRecv;
				// ----
				char szPlayerNick[11] = {0};
				// ----
				memcpy(szPlayerNick, pMsg->szNick, sizeof(pMsg->szNick));
				// ----
				int aIndex = gObjGetIndexByName(szPlayerNick);
				// ----
				if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
				{
					g_Msg.Msg(aIndex, pMsg->szMessage);
				}
			}
			break;

			case HEAD_DCTONICK:
			{
				#ifdef GS_99_60T

				MSG_DCTONICK * pMsg = (MSG_DCTONICK *) pRecv;
				// ----
				char szPlayerNick[11] = {0};
				// ----
				memcpy(szPlayerNick, pMsg->szNick, sizeof(pMsg->szNick));
				// ----
				int aIndex = gObjGetIndexByName(szPlayerNick);
				// ----
				if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
				{
					g_GS.CloseClient(aIndex);
				}

				#endif
			}
			break;

			case HEAD_DCTOACCOUNT:
			{

				MSG_DCTOACCOUNT * pMsg = (MSG_DCTOACCOUNT *)pRecv;
				// ----
				char szAccountId[11] = { 0 };
				// ----
				memcpy(szAccountId, pMsg->szAccountId, sizeof(pMsg->szAccountId));
				// ----
				int aIndex = gObjGetIndexByAccountId(szAccountId);
				// ----
				if ((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
				{
					g_GS.CloseClient(aIndex);
				}


			}
			break;

			case HEAD_SKINACCESS:
			{
				MSG_SKIN_CHECK_R * lpMsg = (MSG_SKIN_CHECK_R *) pRecv;
				ObjectChangeSkin(lpMsg->szGMName, lpMsg->szName, lpMsg->Status, lpMsg->MID);
			}
			break;

			case HEAD_INFO:
			{
				DGInfoMsg((MSG_R_INFO *) pRecv);
			}
			break;

			case HEAD_DELCHAR:
			{
				MSG_R_DELCHAR * lpMsg = (MSG_R_DELCHAR *) pRecv;
				// ----
				if(lpMsg->isBanned == true)
				{
					g_Msg.Notice(lpMsg->PlayerIndex, "Can't remove banned Player");

				}
				else if(lpMsg->Resets >= MIN_RESETS_CHARDEL)
				{
					g_Msg.Notice(lpMsg->PlayerIndex, "Can't remove player above %d reset", MIN_RESETS_CHARDEL);
				}
				else
				{
					char szName[11] = {0};
					// ----
					memcpy(szName, lpMsg->pMsgCharDel.Name, sizeof(lpMsg->pMsgCharDel.Name));
					GDCharacterGotDelOrCreated (lpMsg->PlayerIndex, gObj[lpMsg->PlayerIndex].AccountID, szName, OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_DEL_CHAR);
					// ----
					g_GS.CGPCharDel(& lpMsg->pMsgCharDel, lpMsg->PlayerIndex);
					// ----
					return;
				}
				// ----
				PMSG_RESULT pResult;
				// ----
				pResult.h.c			= 0xC1;
				pResult.h.size		= sizeof(PMSG_RESULT);
				pResult.h.headcode	= 0xF3;
				pResult.subcode		= 0x02;
				pResult.result		= 0x00;
				// ----
				g_GS.DataSend(lpMsg->PlayerIndex, (UCHAR *)&pResult, pResult.h.size);
			}
			break;

			case HEAD_ADVMSG:
			{
				char Name[11]	= {0};
				// ----
				MSG_ADVMSG * lpMsg = (MSG_ADVMSG *) pRecv;
				// ----
				memcpy(Name, lpMsg->PakahName, sizeof(lpMsg->PakahName));
				// ----
				g_Msg.NoticeAll("[%s] מפקח בגילד הפקחים פנוי לפיקוחים", Name);
			}
			break;

			case HEAD_SENDNOTICEALLFROMDS:
			{
				//g_Setup.MsgBox("Got NOTICE ALL");
				char Notice[sizeof MSG_SENDNOTICEALLFROMDS().Notice + 1] = {0};
				// ----
				MSG_SENDNOTICEALLFROMDS * lpMsg = (MSG_SENDNOTICEALLFROMDS *) pRecv;
				// ----
				if (lpMsg->NoticeLen > sizeof(lpMsg->Notice)) {
					lpMsg->NoticeLen = sizeof(lpMsg->Notice);
				}
				// ----
				memcpy(Notice, lpMsg->Notice, lpMsg->NoticeLen);
				// ----
				g_Msg.NoticeAll(Notice);
			}
			break;

			// roye access
			case HEAD_CHECKACCESS_JUMP:
			{
				MSG_ACCESS_JUMP * lpMsg = (MSG_ACCESS_JUMP *) pRecv;
				// ----
				ObjectJumpTeleport(lpMsg->aIndex,lpMsg->TargetName,lpMsg->TeleportID,1,lpMsg->State);

			}
			break; 

			case HEAD_CHECKACCESS_COME:
			{
				MSG_ACCESS_COME * lpMsg = (MSG_ACCESS_COME *) pRecv;
				// ----
				ObjectComeTeleport(lpMsg->aIndex,lpMsg->TargetName,1,lpMsg->State);

			}
			break;

			case HEAD_CHECKACCESS_MOVE:
			{
				MSG_ACCESS_MOVE * lpMsg = (MSG_ACCESS_MOVE *) pRecv;
				char * Command = lpMsg->Command;
				// ----
				CheckMoveAndDisAcc(lpMsg->aIndex,Command,1,lpMsg->State);
			}

			break;

			case HEAD_ACCESS_DENIED_BAN:
			{
				MSG_ACCESS_BAN * lpMsg = (MSG_ACCESS_BAN *) pRecv;
				char * Command = lpMsg->Command;
				char * Name = lpMsg->Name;
				ObjectBanAccessDenied(Name,Command);
			}
			break;
			
			case HEAD_CHECKACCESS_GREENMSG:
			{	
				MSG_ACCESS_GREENMSG * lpMsg = (MSG_ACCESS_GREENMSG *) pRecv;
				char * Command = lpMsg->Command;
				CheckGreenMSG(lpMsg->aIndex, Command, 1, lpMsg->State);
			}
			break;

			case HEAD_MSG_STATUS:
			{
				MSG_MSG_STATUS_RE * lpMsg = (MSG_MSG_STATUS_RE *) pRecv;
				char * Name = lpMsg->Name;
				ObjectMSGChangeStatus (Name, lpMsg->Type, lpMsg->Status);
			}
			break;

			case HEAD_MSG_STATUS_SYS:
			{
				MSG_MSG_STATUS_RE_SYS * lpMsg = (MSG_MSG_STATUS_RE_SYS *) pRecv;
				ObjectMSGChangeStatusSys (lpMsg->Status);
			}
			break;

			case HEAD_LOG_HACK:
			{
				MSG_R_LOG_HACK * lpMsg = (MSG_R_LOG_HACK *) pRecv;
				ObjectLogHackChange (lpMsg->aIndex, lpMsg->status);
			}
			break;
			case HEAD_EVENT_COMMAND:
			{
				MSG_EVENT_COMMAND * lpMsg = (MSG_EVENT_COMMAND *) pRecv;

			}
			break;

			case HEAD_FREINDMEMO_DEL:
			{
				MSG_FREINDMEMO_DEL * lpMsg = (MSG_FREINDMEMO_DEL *) pRecv;
				// ----
				ObjectFriendMemoDelete(lpMsg->szName, lpMsg->MemoIndex);
			}
			break;

			case HEAD_FRIENDMEMO_ADD:
			{
				char RecvName[11]	= {0};
				char SendName[11]	= {0};
				char Subject[50]	= {0};
				char Date[30]		= {0};
				// ----
				MSG_FREINDMEMO_ADD_GS * lpMsg = (MSG_FREINDMEMO_ADD_GS *) pRecv;
				// ----
				memcpy(RecvName,	lpMsg->RecvName,	sizeof(lpMsg->RecvName));
				memcpy(SendName,	lpMsg->SendName,	sizeof(lpMsg->SendName));
				memcpy(Subject,		lpMsg->Subject,		sizeof(lpMsg->Subject));
				memcpy(Date,		lpMsg->Date,			sizeof(lpMsg->Date));
				// ----
				ObjectFriendMemoListSend(SendName, RecvName, lpMsg->MemoIndex, Subject, Date);
			}
			break;

			case HEAD_GUILD_MEMBER_STATUS:
			{
				char AssistName [11]  = {0};
				char MemberName [11]  = {0};
				char GuildName [11]  = {0};
				// ----
				MSG_GUILD_MEMBER_STATUS_R * lpMsg = (MSG_GUILD_MEMBER_STATUS_R *) pRecv;
				// ----
				memcpy(AssistName,	lpMsg->AssistName,	sizeof(lpMsg->AssistName));
				memcpy(MemberName,	lpMsg->MemberName,	sizeof(lpMsg->MemberName));
				memcpy(GuildName,	lpMsg->GuildName,	sizeof(lpMsg->GuildName));
				// ----
				ObjectGuildChangeMemberStatus(AssistName, MemberName, GuildName, lpMsg->Type, lpMsg->Status);
			}
			break;

			case HEAD_GUILD_KICK_MEMBER:
			{
				char AssistName [11]  = {0};
				char MemberName [11]  = {0};
				char GuildName [11]  = {0};
				// ----
				MSG_GUILD_KICK_MEMBER_R * lpMsg = (MSG_GUILD_KICK_MEMBER_R *) pRecv;
				// ----
				memcpy(AssistName,	lpMsg->AssistName,	sizeof(lpMsg->AssistName));
				memcpy(MemberName,	lpMsg->MemberName,	sizeof(lpMsg->MemberName));
				memcpy(GuildName,	lpMsg->GuildName,	sizeof(lpMsg->GuildName));
				// ----
				ObjectGuildKickMember(AssistName, MemberName, GuildName, lpMsg->Status);
			}
			break;

			case HEAD_GUILD_JOIN_REQUEST:
			{
				char AssistName [11]	= {0};
				char ReqName [11]		= {0};
				char GuildName [11]		= {0};
				// ----
				MSG_GUILD_JOIN_REQUEST_R * lpMsg = (MSG_GUILD_JOIN_REQUEST_R *) pRecv;
				// ----
				memcpy(AssistName,	lpMsg->AssistName,	sizeof(lpMsg->AssistName));
				memcpy(ReqName,	lpMsg->ReqName,	sizeof(lpMsg->ReqName));
				// ----
				int reqIndex = gObjGetIndexByName(ReqName);
				int assistIndex = gObjGetIndexByName(AssistName);
				// ----
				if(reqIndex < OBJECT_START_INDEX || reqIndex > OBJECT_MAX_INDEX)
				{
					return;
				}
				// ----
				if(assistIndex < OBJECT_START_INDEX || assistIndex > OBJECT_MAX_INDEX)
				{
					return;
				}
				// ----
				if (lpMsg->Status == 1)
				{
					CGGuildRequestRecv(reqIndex, assistIndex);
				}
				else
				{
					g_Msg.Msg(reqIndex,"@Error - Report Roye");
					g_Msg.Msg(assistIndex,"@Error - Report Roye");
				}
			}
			break;

			case HEAD_SHOP_BUY_RESULT:
			{
				DGShopBuyItemResult((MSG_SHOP_BUY_ITEM_RESULT *)pRecv);
			}
			break;

			default:
			{
				g_NewDataServerLog.Output("CASE : ERROR Len %u Case : %X GSCode %d", pRecv[0], pRecv[1], g_Config.nServerCode);
			}
			break;
			// ----
			#pragma endregion basicPackets
		// ----
		}
	}
	else if(pRecv[0] == 2)
	{
		MSG_HEADER2 * lpHead = (MSG_HEADER2 *) pRecv;
		// ----
		switch(lpHead->ProtocolId)
		{
			case HEAD_EXERCISESYSTEM:
			{
				vDSSubProtocolCoreEXERCISESYSTEM(pRecv, (VDS_SUBPACKET_EXERCISESYSTEM_HEADERS)lpHead->SubProtocolId);
			}
			break;

			case HEAD_RUNEVENT:
			{
				vDSSubProtocolCoreRUNEVENT(pRecv, (VDS_SUBPACKET_RUNEVENT_HEADERS) lpHead->SubProtocolId);
			}
			break;

			case HEAD_WROTEEVENT:
			{
				vDSSubProtocolCoreWROTEEVENT(pRecv, (VDS_SUBPACKET_WROTEEVENT_HEADERS) lpHead->SubProtocolId);
			}
			break;

			case HEAD_LOTTERYEVENT:
			{
				vDSSubProtocolCoreLOTTERYEVENT(pRecv, (VDS_SUBPACKET_LOTTERYEVENT_HEADERS) lpHead->SubProtocolId);
			}
			break;
			case HEAD_CONFUSEEVENT:
			{
				vDSSubProtocolCoreCONFUSEEEVENT(pRecv, (VDS_SUBPACKET_CONFUSEEVENT_HEADERS) lpHead->SubProtocolId);
			}
			break;
		}
	}
	else if(pRecv[0] == 4)
	{
		MSG_HEADER4 * lpHead = (MSG_HEADER4 *) pRecv;
		// ----
		switch(lpHead->ProtocolId)
		{
			case HEAD_VOTESYSTEM:
			{
				vDSSubProtocolCoreVOTESYSTEM(pRecv, (VDS_SUBPACKET_VOTESYSTEM_HEADERS) lpHead->SubProtocolId);
			}
			break;
		}
	}
	else 
	{
		g_NewDataServerLog.Output("[VdsProtocolCore] unknow xcode %X", pRecv[0]);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void vDSSubProtocolCoreEXERCISESYSTEM(unsigned char * pRecv, VDS_SUBPACKET_EXERCISESYSTEM_HEADERS Head)
{
	switch(Head)
	{
		case VDS_SUBPACKET_EXERCISESYSTEM_HEADERS::EXERCISESYSTEM_SUBHEAD_START:
		{
			g_EXERCISESYSTEM_STATE = true;
			// ----
			MSG_EXERCISE_START * lpMsg = (MSG_EXERCISE_START *) pRecv;
			// ----
			g_Msg.NoticeAll("[אוונט התרגיל מתחיל]");
			g_Msg.NoticeAll("%d + %d + %d = ? רשום את הפתרון בצאט", lpMsg->Num1, lpMsg->Num2, lpMsg->Num3);
			// ----
			g_EventLog.Output("[Event][Targil] [%d + %d + %d = %d] Started", lpMsg->Num1, lpMsg->Num2,
				lpMsg->Num3, (lpMsg->Num1 + lpMsg->Num2 + lpMsg->Num3));
		}
		break;

		case VDS_SUBPACKET_EXERCISESYSTEM_HEADERS::EXERCISESYSTEM_SUBHEAD_GIVEPRIZE:
		{
			g_EXERCISESYSTEM_STATE = false;
			// ----
			MSG_EXERCISE_GIVEPRIZE * lpMsg = (MSG_EXERCISE_GIVEPRIZE *) pRecv;
			// ----
			if(lpMsg->PrizeType == PRIZE_TYPE_NULL)
			{
				g_Msg.NoticeAll("[אוונט התרגיל נגמר]");
				g_Msg.NoticeAll("נגמר ללא פתרון כעבור 60 שניות");
				g_Msg.NoticeAll("תשובה: %d", lpMsg->An);
				// ----
				g_EventLog.Output("[Event][Targil] timeout after 60 seconds");
			}
			else
			{
				char temp1[11] = {0};
				// ----
				memcpy(temp1, lpMsg->szNick, sizeof(lpMsg->szNick));
				// ----
				int aIndex = gObjGetIndexByName(temp1);
				// ----
				g_Msg.NoticeAll("[אוונט התרגיל נגמר]");
				g_Msg.NoticeAll("תשובה: %d", lpMsg->An);
				g_Msg.NoticeAll("..:: %s ::..", temp1);
				// -----
				switch(lpMsg->PrizeType)
				{
					case PRIZE_TYPES::PRIZE_TYPE_SOULS:
					{
						switch(lpMsg->Prize)
						{
							case 0:
							{
								g_Msg.NoticeAll("זכה בתרגיל וקיבל חבילה של 10 סולים");
							}
							break;
							case 1:
							{
								g_Msg.NoticeAll("זכה בתרגיל וקיבל חבילה של 20 סולים");
							}
							break;
							case 2:
							{
								g_Msg.NoticeAll("זכה בתרגיל וקיבל חבילה של 30 סולים");
							}
							break;
						}
						// ----
						if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
						{
							g_Msg.Msg(aIndex, "@זכית באיבנט התרגיל הסולים על הרצפה");
							// ----
							g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 31), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
						}
					}
					break;

					case PRIZE_TYPES::PRIZE_TYPE_BLESS:
					{
						switch(lpMsg->Prize)
						{
							case 0:
							{
								g_Msg.NoticeAll("זכה בתרגיל וקיבל חבילה של 10 בלסים");
							}
							break;
							case 1:
							{
								g_Msg.NoticeAll("זכה בתרגיל וקיבל חבילה של 20 בלסים");
							}
							break;
							case 2:
							{
								g_Msg.NoticeAll("זכה בתרגיל וקיבל חבילה של 30 בלסים");
							}
							break;
						}
						// ----
						if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
						{
							g_Msg.Msg(aIndex, "@זכית באיבנט התרגיל הבלסים על הרצפה");
							// ----
							g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 30), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
						}
					}
					break;

					case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
					{
						g_Msg.NoticeAll("פתר את התרגיל ראשון וזוכה ב-%d קרדיטים ",
							lpMsg->Prize);
						if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
						{
							g_Msg.Msg(aIndex, "@איוונט תרגיל : זכית ב %d קרדיטים", lpMsg->Prize);
						}
					}
					break;
				}
				// ----
				g_EventLog.Output("[Event][Targil] %s win %d credits (stop)", temp1, lpMsg->Prize);
			}
		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void vDSSubProtocolCoreVOTESYSTEM(unsigned char * pRecv, VDS_SUBPACKET_VOTESYSTEM_HEADERS Head)
{
	switch(Head)
	{
		case VOTESYSTEM_SUBHEAD_START:
		{
			MSG_VOTESYSTEM_START * lpMsg = (MSG_VOTESYSTEM_START *) pRecv;
			// ----
			A_MAP Answers;
			// ----
			char szGameMaster[11]	= {0};
			char szQuestion[100]	= {0};
			// ----
			memcpy(szGameMaster,	lpMsg->szGameMaster,		sizeof(lpMsg->szGameMaster));
			memcpy(szQuestion,		lpMsg->Question,			lpMsg->questionLen);
			// ----
			for(int i = 0 ; i != lpMsg->AnswersCount ; ++i)
			{
				char Temp[100] = {0};
				// ----
				memcpy(Temp, lpMsg->Answers[i].Answer, lpMsg->Answers[i].Len);
				// ----
				Answers[lpMsg->Answers[i].Id] = Temp;
			}
			// ----
			CChatVote::onStart(szGameMaster, lpMsg->nSeconds, szQuestion, Answers);
		}
		break;

		case VOTESYSTEM_SUBHEAD_STOP:
		{
			MSG_VOTESYSTEM_STOP * lpMsg = (MSG_VOTESYSTEM_STOP *) pRecv;
			// ----
			AD_MAP AnswersResult;
			// ----
			for(int i = 0 ; i != lpMsg->AnswersCount ; ++i)
			{
				AnswersResult[lpMsg->Answered[i].Id] = lpMsg->Answered[i].AnswerdFor;
			}
			// ----
			int aIndex = gObjGetIndexByName((char *)VoteGameMaster.c_str());
			// ----
			if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
			{
				g_Msg.PM(aIndex, "[vote] total vote(rs) is %d", lpMsg->SumVoters);
			}
			// ----
			CChatVote::voteStop(AnswersResult);
		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void vDSSubProtocolCoreRUNEVENT(unsigned char * pRecv, VDS_SUBPACKET_RUNEVENT_HEADERS Head)
{
	switch(Head)
	{
		case VDS_SUBPACKET_RUNEVENT_HEADERS::RUNEVENT_SUBHEAD_START:
		{
			g_RUNEVENT_STATE = true;
			// ----
			MSG_RUNEVENT_START * lpMsg = (MSG_RUNEVENT_START *) pRecv;
			// ----
			g_Msg.NoticeAll("[אוונט רוץ ילד רוץ מתחיל]");
			g_Msg.NoticeAll("הראשון שיגיע למיקום יהיה הזוכה");
			g_Msg.NoticeAll("%dx%d %s",lpMsg->X ,lpMsg->Y ,GetMapNameHeByID(lpMsg->Map));
			// ----
			g_RUNEVENT_CORD.Map = lpMsg->Map;
			g_RUNEVENT_CORD.X	= lpMsg->X;
			g_RUNEVENT_CORD.Y	= lpMsg->Y;
			// ----
			g_EventLog.Output("[Event][RunEvent] [%d %d %d]", lpMsg->Map, lpMsg->X, lpMsg->Y);
		}
		break;

		case VDS_SUBPACKET_RUNEVENT_HEADERS::RUNEVENT_SUBHEAD_GIVEPRIZE:
		{
			g_RUNEVENT_STATE = false;
			// ----
			MSG_RUNEVENT_GIVEPRIZE * lpMsg = (MSG_RUNEVENT_GIVEPRIZE *) pRecv;
			// ----
			char temp1[11] = {0};
			// ----
			memcpy(temp1, lpMsg->szNick, sizeof(lpMsg->szNick));
			// ----
			int aIndex = gObjGetIndexByName(temp1);
			// ----
			g_Msg.NoticeAll("[אוונט רוץ ילד רוץ נגמר]");
			g_Msg.NoticeAll("..:: %s ::..", temp1);
			// -----
			switch(lpMsg->PrizeType)
			{
				case PRIZE_TYPES::PRIZE_TYPE_SOULS:
				{
					switch(lpMsg->Prize)
					{
						case 0:
						{
							g_Msg.NoticeAll("זכה ברוץ ילד רוץ וקיבל חבילה של 10 סולים");
						}
						break;
						case 1:
						{
							g_Msg.NoticeAll("זכה ברוץ ילד רוץ וקיבל חבילה של 20 סולים");
						}
						break;
						case 2:
						{
							g_Msg.NoticeAll("זכה ברוץ ילד רוץ וקיבל חבילה של 30 סולים");
						}
						break;
					}
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@זכית באיוונט רוץ ילד רוץ הסולים על הרצפה");
						// ----
						g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 31), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
					}
				}
				break;

				case PRIZE_TYPES::PRIZE_TYPE_BLESS:
				{
					switch(lpMsg->Prize)
					{
						case 0:
						{
							g_Msg.NoticeAll("זכה ברוץ ילד רוץ וקיבל חבילה של 10 בלסים");
						}
						break;
						case 1:
						{
							g_Msg.NoticeAll("זכה  ברוץ ילד רוץ וקיבל חבילה של 20 בלסים");
						}
						break;
						case 2:
						{
							g_Msg.NoticeAll("זכה  ברוץ ילד רוץ וקיבל חבילה של 30 בלסים");
						}
						break;
					}
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@זכית  באיוונט רוץ ילד רוץ הבלסים על הרצפה");
						// ----
						g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 30), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
					}
				}
				break;

				case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
				{
					g_Msg.NoticeAll("הגיע ליעד ראשון וזוכה ב-%d קרדיטים", lpMsg->Prize);
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@איוונט רוץ ילד רוץ : זכית ב %d קרדיטים", lpMsg->Prize);
					}
				}
				break;
			}
			// ----
			g_EventLog.Output("[Event][RunEvent] %s win %d credits (stop)", temp1, lpMsg->Prize);
			
		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void vDSSubProtocolCoreWROTEEVENT(unsigned char * pRecv, VDS_SUBPACKET_WROTEEVENT_HEADERS Head)
{
	switch(Head)
	{
		case VDS_SUBPACKET_WROTEEVENT_HEADERS::WROTEEVENT_SUBHEAD_START:
		{
			g_FASTWROTE_STATE = true;
			// ----
			MSG_WROTEEVENT_START * lpMsg = (MSG_WROTEEVENT_START *) pRecv;
			// ----
			char Temp[1024] = {0};
			char Temp1[1024] = {0};
			char Temp2[1024] = {0};
			char Temp3[1024] = {0};
			char Temp4[1024] = {0};
			// ----
			memcpy(Temp1, lpMsg->Word1, sizeof(lpMsg->Word1));
			memcpy(Temp2, lpMsg->Word2, sizeof(lpMsg->Word2));
			memcpy(Temp3, lpMsg->Word3, sizeof(lpMsg->Word3));
			memcpy(Temp4, lpMsg->Word4, sizeof(lpMsg->Word4));
			// ----
			sprintf(Temp, "%s %s %s %s", Temp1, Temp2, Temp3, Temp4);
			// ----
			g_WROTE_TEXT = Temp;
			// ----
			g_Msg.NoticeAll("[אוונט זריזות מתחיל]");
			g_Msg.NoticeAll("הראשון שירשום את המשפט הבא יהיה הזוכה");
			g_Msg.NoticeAll(Temp);
			// ----
			g_EventLog.Output("[Event][WroteEvent][%s]", Temp);
		}
		break;

		case VDS_SUBPACKET_RUNEVENT_HEADERS::RUNEVENT_SUBHEAD_GIVEPRIZE:
		{
			g_FASTWROTE_STATE = false;
			// ----
			MSG_WROTEEVENT_GIVEPRIZE * lpMsg = (MSG_WROTEEVENT_GIVEPRIZE *) pRecv;
			// ----
			char temp1[11] = {0};
			// ----
			memcpy(temp1, lpMsg->szNick, sizeof(lpMsg->szNick));
			// ----
			int aIndex = gObjGetIndexByName(temp1);
			// ----
			g_Msg.NoticeAll("[אוונט זריזות נגמר]");
			g_Msg.NoticeAll("..:: %s ::..", temp1);
			// -----
			switch(lpMsg->PrizeType)
			{
				case PRIZE_TYPES::PRIZE_TYPE_SOULS:
				{
					switch(lpMsg->Prize)
					{
						case 0:
						{
							g_Msg.NoticeAll("זכה באוונט זירזות וקיבל חבילה של 10 סולים");
						}
						break;
						case 1:
						{
							g_Msg.NoticeAll("זכה באוונט זירזות וקיבל חבילה של 20 סולים");
						}
						break;
						case 2:
						{
							g_Msg.NoticeAll("זכה באוונט זירזות וקיבל חבילה של 30 סולים");
						}
						break;
					}
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@זכית באיוונט זריזות הסולים על הרצפה");
						// ----
						g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 31), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
					}
				}
				break;

				case PRIZE_TYPES::PRIZE_TYPE_BLESS:
				{
					switch(lpMsg->Prize)
					{
						case 0:
						{
							g_Msg.NoticeAll("זכה באיוונט זריזות וקיבל חבילה של 10 בלסים");
						}
						break;
						case 1:
						{
							g_Msg.NoticeAll("זכה באיוונט זריזות וקיבל חבילה של 20 בלסים");
						}
						break;
						case 2:
						{
							g_Msg.NoticeAll("זכה באיוונט זריזות וקיבל חבילה של 30 בלסים");
						}
						break;
					}
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@זכית  באיוונט זריזות הבלסים על הרצפה");
						// ----
						g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 30), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
					}
				}
				break;

				case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
				{
					g_Msg.NoticeAll("המהיר ביותר רשם ראשון וזוכה ב-%d קרדיטים", lpMsg->Prize);
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@איוונט זריזות : זכית ב %d קרדיטים", lpMsg->Prize);
					}
				}
				break;
			}
			// ----
			g_EventLog.Output("[Event][WroteEvent] %s win %d credits (stop)", temp1, lpMsg->Prize);
			
		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void vDSSubProtocolCoreCONFUSEEEVENT(unsigned char * pRecv, VDS_SUBPACKET_CONFUSEEVENT_HEADERS Head)
{
	switch(Head)
	{
		case VDS_SUBPACKET_CONFUSEEVENT_HEADERS::CONFUSEEVENT_SUBHEAD_START:
		{
			g_CONFUSEEVENT_STATE = true;
			// ----
			MSG_CONFUSEEVENT_START * lpMsg = (MSG_CONFUSEEVENT_START *) pRecv;
			// ----
			char TempA[1024] = {0};
			char Temp[1024] = {0};
			char Temp1[1024] = {0};
			char Temp2[1024] = {0};
			char Temp3[1024] = {0};
			char Temp4[1024] = {0};
			char Temp5[1024] = {0};
			char Temp6[1024] = {0};
			char Temp7[1024] = {0};
			char Temp8[1024] = {0};
			// ----
			memcpy(Temp1, lpMsg->Word1, sizeof(lpMsg->Word1));
			memcpy(Temp2, lpMsg->Word2, sizeof(lpMsg->Word2));
			memcpy(Temp3, lpMsg->Word3, sizeof(lpMsg->Word3));
			memcpy(Temp4, lpMsg->Word4, sizeof(lpMsg->Word4));
			// ----
			sprintf(Temp, "%s %s %s %s", Temp1, Temp2, Temp3, Temp4);
			g_EventLog.Output("[Event][ConfuseEvent][%s]", Temp);
			// ----
			memcpy(Temp5, lpMsg->Word5, sizeof(lpMsg->Word5));
			memcpy(Temp6, lpMsg->Word6, sizeof(lpMsg->Word6));
			memcpy(Temp7, lpMsg->Word7, sizeof(lpMsg->Word7));
			memcpy(Temp8, lpMsg->Word8, sizeof(lpMsg->Word8));
			// ----
			sprintf(TempA, "%s %s %s %s", Temp5, Temp6, Temp7, Temp8);
			g_EventLog.Output("[Event][ConfuseEvent][%s]", TempA);
			// ----
			g_CONFUSE_WROTE_TEXT = TempA;
			// ----
			g_Msg.NoticeAll("[אוונט מילים מבולבלות מתחיל]");
			g_Msg.NoticeAll("הראשון שיכתוב את המשפט נכון יזכה");
			g_Msg.NoticeAll(Temp);
			g_CONFUSE_WROTE_TEXT_WRONG=Temp;
			// ----
			
		}
		break;

		case VDS_SUBPACKET_CONFUSEEVENT_HEADERS::CONFUSEEVENT_SUBHEAD_GIVEPRIZE:
		{
			g_CONFUSEEVENT_STATE = false;
			// ----
			MSG_CONFUSEEVENT_GIVEPRIZE * lpMsg = (MSG_CONFUSEEVENT_GIVEPRIZE *) pRecv;
			// ----
			char temp1[11] = {0};
			// ----
			memcpy(temp1, lpMsg->szNick, sizeof(lpMsg->szNick));
			// ----
			int aIndex = gObjGetIndexByName(temp1);
			// ----
			g_Msg.NoticeAll("[אוונט מילים מבולבלות נגמר]");
			g_Msg.NoticeAll("התשובה: %s", g_CONFUSE_WROTE_TEXT.c_str());
			g_Msg.NoticeAll("..:: %s ::..", temp1);
			// -----
			switch(lpMsg->PrizeType)
			{
				case PRIZE_TYPES::PRIZE_TYPE_SOULS:
				{
					switch(lpMsg->Prize)
					{
						case 0:
						{
							g_Msg.NoticeAll("זכה באוונט מילים מבולבלות וקיבל חבילה של 10 סולים");
						}
						break;
						case 1:
						{
							g_Msg.NoticeAll("זכה באוונט מילים מבולבלות וקיבל חבילה של 20 סולים");
						}
						break;
						case 2:
						{
							g_Msg.NoticeAll("זכה באוונט מילים מבולבלות וקיבל חבילה של 30 סולים");
						}
						break;
					}
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@זכית באיוונט מילים מבולבלות הסולים על הרצפה");
						// ----
						g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 31), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
					}
				}
				break;

				case PRIZE_TYPES::PRIZE_TYPE_BLESS:
				{
					switch(lpMsg->Prize)
					{
						case 0:
						{
							g_Msg.NoticeAll("זכה באיוונט מילים מבולבלות וקיבל חבילה של 10 בלסים");
						}
						break;
						case 1:
						{
							g_Msg.NoticeAll("זכה באיוונט מילים מבולבלות וקיבל חבילה של 20 בלסים");
						}
						break;
						case 2:
						{
							g_Msg.NoticeAll("זכה באיוונט מילים מבולבלות וקיבל חבילה של 30 בלסים");
						}
						break;
					}
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@זכית  באיוונט מילים מבולבלות הבלסים על הרצפה");
						// ----
						g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 30), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
					}
				}
				break;

				case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
				{
					g_Msg.NoticeAll("המהיר ביותר רשם ראשון וזוכה ב-%d קרדיטים", lpMsg->Prize);
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@איוונט מילים מבולבלות : זכית ב %d קרדיטים", lpMsg->Prize);
					}
				}
				break;
			}
			// ----
			g_EventLog.Output("[Event][ConfuseEvent] %s win %d credits (stop)", temp1, lpMsg->Prize);
			
		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void vDSSubProtocolCoreLOTTERYEVENT(unsigned char * pRecv, VDS_SUBPACKET_LOTTERYEVENT_HEADERS Head)
{
	switch(Head)
	{
		case VDS_SUBPACKET_LOTTERYEVENT_HEADERS::LOTTERYEVENT_SUBHEAD_START:
		{
			
			// ----
			MSG_LOTTERYEVENT_START * lpMsg = (MSG_LOTTERYEVENT_START *) pRecv;
			// ----
			g_LOTTREYEVENT_ROLEED = lpMsg->RolledNumber;
			// ----
			g_Msg.NoticeAll("[אוונט נחש את המספר מתחיל]");
			g_Msg.NoticeAll("הראשון שירשום את המספר שהשרת בחר יהיה הזוכה");
			g_Msg.NoticeAll("טווח המספרים לניחוש: %d-%d ", LOTTERY_EVENT_ROLLED_RANGE);
			// ----
			if(LOTTERY_EVENT_TRY_COUNT > 0)
			{
				g_Msg.NoticeAll("כמות הניחושים המותרת לכל משתמש %d", LOTTERY_EVENT_TRY_COUNT);
			}
			else if(LOTTERY_EVENT_TRY_COUNT == 0)
			{
				g_Msg.NoticeAll("אין הגבלה של כמות ניסונות");
			}
			// ----
			g_EventLog.Output("[Event][LotteryEvent][%d]", g_LOTTREYEVENT_ROLEED);
		}
		break;

		case VDS_SUBPACKET_LOTTERYEVENT_HEADERS::LOTTERYEVENT_SUBHEAD_START_GO:
		{
			g_LOTTERYEVENT_STATE = true;
		}
		break;

		case VDS_SUBPACKET_LOTTERYEVENT_HEADERS::LOTTERYEVENT_SUBHEAD_GIVEPRIZE:
		{
			g_LOTTERYEVENT_STATE = false;
			// ----
			MSG_LOTTERYEVENT_GIVEPRIZE * lpMsg = (MSG_LOTTERYEVENT_GIVEPRIZE *) pRecv;
			// ----
			char temp1[11] = {0};
			// ----
			memcpy(temp1, lpMsg->szNick, sizeof(lpMsg->szNick));
			// ----
			int aIndex = gObjGetIndexByName(temp1);
			// ----
			g_Msg.NoticeAll("[אוונט נחש את המספר נגמר]");
			g_Msg.NoticeAll("..:: %s ::..", temp1);
			g_Msg.NoticeAll("המספר הזוכה : %d", g_LOTTREYEVENT_ROLEED);
			// -----
			switch(lpMsg->PrizeType)
			{
				case PRIZE_TYPES::PRIZE_TYPE_SOULS:
				{
					switch(lpMsg->Prize)
					{
						case 0:
						{
							g_Msg.NoticeAll("זכה באוונט נחש את המספר וקיבל חבילה של 10 סולים");
						}
						break;
						case 1:
						{
							g_Msg.NoticeAll("זכה באוונט נחש את המספר וקיבל חבילה של 20 סולים");
						}
						break;
						case 2:
						{
							g_Msg.NoticeAll("זכה באוונט נחש את המספר וקיבל חבילה של 30 סולים");
						}
						break;
					}
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@זכית באיוונט נחש את המספר הסולים על הרצפה");
						// ----
						g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 31), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
					}
				}
				break;

				case PRIZE_TYPES::PRIZE_TYPE_BLESS:
				{
					switch(lpMsg->Prize)
					{
						case 0:
						{
							g_Msg.NoticeAll("זכה באיוונט נחש את המספר וקיבל חבילה של 10 בלסים");
						}
						break;
						case 1:
						{
							g_Msg.NoticeAll("זכה באיוונט נחש את המספר וקיבל חבילה של 20 בלסים");
						}
						break;
						case 2:
						{
							g_Msg.NoticeAll("זכה באיוונט נחש את המספר וקיבל חבילה של 30 בלסים");
						}
						break;
					}
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@זכית  באיוונט נחש את המספר הבלסים על הרצפה");
						// ----
						g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(12, 30), lpMsg->Prize, 0xFF, 0, 0, 0, aIndex, 0, 0);
					}
				}
				break;

				case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
				{
					g_Msg.NoticeAll("המהיר ביותר רשם ראשון וזוכה ב-%d קרדיטים", lpMsg->Prize);
					// ----
					if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
					{
						g_Msg.Msg(aIndex, "@איוונט נחש את המספר : זכית ב %d קרדיטים", lpMsg->Prize);
					}
				}
				break;
			}
			// ----
			g_EventLog.Output("[Event][LotteryEvent] %s win %d credits (stop)", temp1, lpMsg->Prize);
			
		}
		break;

		case VDS_SUBPACKET_LOTTERYEVENT_HEADERS::LOTTERYEVENT_SUBHEAD_SENDERGET:
		{
			static char temp[11];
			// ----
			if(g_LOTTERYEVENT_STATE == true)
			{
				MSG_LOTTERYEVENT_GETSENDER * lpMsg = (MSG_LOTTERYEVENT_GETSENDER *) pRecv;
				// ----
				memset(temp, 0, sizeof(temp));
				// ----
				memcpy(temp, lpMsg->szNick, sizeof(lpMsg->szNick));
				// ----
				int iIndex = gObjGetIndexByName(temp);
				// ----
				if(lpMsg->bISOK == true)
				{
					if(lpMsg->Number == g_LOTTREYEVENT_ROLEED)
					{
						if(iIndex != 0)
						{
							GDLotteryEventWinnerSend(iIndex);
						}
					}
					else if(lpMsg->Number > g_LOTTREYEVENT_ROLEED)
					{
						g_Msg.NoticeAll("בחר %d המספר של השרת נמוך יותר %s" ,lpMsg->Number, temp);
					}
					else if(lpMsg->Number < g_LOTTREYEVENT_ROLEED)
					{
						g_Msg.NoticeAll("בחר %d המספר של השרת גבוה יותר %s" ,lpMsg->Number, temp);
						
					}
				}
				else
				{
					if(iIndex != 0)
					{
						g_Msg.Msg(iIndex, "@עברת את הגבלת הניסיונות שבשרותך %d ", LOTTERY_EVENT_TRY_COUNT);
					}
				}
			}
		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDExtraInfo(int aIndex, char * sAccountID)
{
	MSG_S_EXTRAINFO pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_EXTRAINFO);
	// ----
	pMsg.nIndex		= aIndex;
	// ----
	memcpy(pMsg.szIpAddr,		gObj[aIndex].Ip_addr,	sizeof(gObj[aIndex].Ip_addr));
	memcpy(pMsg.szNick,			gObj[aIndex].Name,		sizeof(gObj[aIndex].Name));
	memcpy(pMsg.szAccountID,	sAccountID,				sizeof(pMsg.szAccountID));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSBanSet(char * GMName, char * PlayerName, int Days, int ibanReason, int isBanAllUsers)
{
	MSG_BAN pMsg	= {0};
	// ----
	HeadSet1(& pMsg.Head , sizeof(pMsg) , HEAD_BAN);
	// ----
	pMsg.nDays			=  Days;
	pMsg.nReason		= ibanReason;
	pMsg.isBanAllUsers	= isBanAllUsers;
	// ----
	memcpy(pMsg.szGameMasterNick ,		GMName,		sizeof(pMsg.szGameMasterNick));
	memcpy(pMsg.szPlayerNick,			PlayerName, sizeof(pMsg.szPlayerNick));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDGoRequest(int aIndex, int Target, int Credits, char * AccountID)
{
	MSG_S_GO pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GO);
	// ----
	pMsg.nIndex			= aIndex;
	pMsg.nTargetIndex	= Target;
	pMsg.nPrice			= Credits;
	// ----
	memcpy(pMsg.szTargetNick,	gObj[Target].Name,	sizeof(pMsg.szTargetNick));
	memcpy(pMsg.szNickName,		gObj[aIndex].Name,	sizeof(pMsg.szNickName));
	memcpy(pMsg.szAccountID,	AccountID,			sizeof(pMsg.szAccountID));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDKandumRequest(int aIndex, int Credits, char * AccountID)
{
	MSG_S_KANDUM pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_KUADNM);
	// ----
	pMsg.nIndex			= aIndex;
	pMsg.nPrice			= Credits;
	// ----
	memcpy(pMsg.szAccountID, AccountID, sizeof(pMsg.szAccountID));
	memcpy(pMsg.szNickName,		gObj[aIndex].Name,	sizeof(pMsg.szNickName));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDOffTradeRequest(int aIndex, int Credits, char * AccountID)
{
	MSG_S_OFFTRADE pMsg = { 0 };
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_OFFTRADE);
	// ----
	pMsg.nIndex = aIndex;
	pMsg.nPrice = Credits;
	// ----
	memcpy(pMsg.szAccountID, AccountID, sizeof(pMsg.szAccountID));
	memcpy(pMsg.szNickName, gObj[aIndex].Name, sizeof(pMsg.szNickName));
	// ----
	g_DataServer.DataSend((UCHAR *)& pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDRedDragonRequest(int aIndex, char * AccountID)
{
	MSG_S_REDDRAGON pMsg = { 0 };
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_REDDRAGON);
	// ----
	pMsg.nIndex = aIndex;
	// ----
	memcpy(pMsg.szAccountID, AccountID, sizeof(pMsg.szAccountID));
	memcpy(pMsg.szNickName, gObj[aIndex].Name, sizeof(pMsg.szNickName));
	// ----
	g_DataServer.DataSend((UCHAR *)& pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSendPost(char * Name, int Credits, char * Message, char * AccountID)
{
	MSG_S_POST pMsg		   = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg) , HEAD_NOTICEALL);
	// ----
	pMsg.nPrice		= Credits;
	// ----
	memcpy(pMsg.szNick,		Name,		sizeof(pMsg.szNick));
	memcpy(pMsg.szAcountID, AccountID,	sizeof(pMsg.szAcountID));
	memcpy(pMsg.szMsg,		Message,	sizeof(pMsg.szMsg));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSendPostGM(char * Name, char * Message, char * AccountID)
{
	MSG_S_POST pMsg		   = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg) , HEAD_NOTICEALLGM);
	// ----
	pMsg.nPrice		= 0;
	// ----
	memcpy(pMsg.szNick,		Name,		sizeof(pMsg.szNick));
	memcpy(pMsg.szAcountID, AccountID,	sizeof(pMsg.szAcountID));
	memcpy(pMsg.szMsg,		Message,	sizeof(pMsg.szMsg));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSendReportMsg(char * ReporterName, char * Name, char * Reason)
{
	MSG_REPORT pMsg		= {0};
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_REPORT);
	// ----
	memcpy(pMsg.szReporterName, ReporterName,	sizeof(pMsg.szReporterName));
	memcpy(pMsg.szName,			Name,			sizeof(pMsg.szName));
	memcpy(pMsg.szReason,		Reason,	sizeof(pMsg.szReason));
	// ----
	g_DataServer.DataSend((UCHAR *)& pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSendGuildMsg(std::string Name, std::string GuildName, std::string Message)
{
	MSG_GUILD pMsg		= {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GUILDMSG);
	// ----
	pMsg.nServerNumber	= g_Config.nServerCode + 1;
	// ----
	memcpy(pMsg.szNick,			Name.c_str() ,			Name.length());
	memcpy(pMsg.szGuildName,	GuildName.c_str(),		GuildName.length());
	memcpy(pMsg.szMsg,			Message.c_str(),		Message.length());
	// ----

	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSendStartupMSG(BYTE ServerCode)
{
	MSG_STARTUP pMsg	= {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GETSTARTUP);
	// ----
	pMsg.btServerCode = g_Config.nServerCode;
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSendInfoMsg(int aIndex, char * szNick)
{
	MSG_S_INFO pMsg		= {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_INFO);
	// ----
	pMsg.SeekingIndex = aIndex;
	// ----
	memcpy(pMsg.RequiredNick, szNick, sizeof(pMsg.RequiredNick));
	memcpy(pMsg.SeekingName, gObj[aIndex].Name, sizeof(pMsg.SeekingName));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void DGInfoMsg(MSG_R_INFO * lpMsg)
{
	char Name[11] = { 0 };
	char szGuild[10] = { 0 };
	char ServerName[50] = { 0 };
	// ----
	memcpy(ServerName, lpMsg->szServerName, sizeof(lpMsg->szServerName));
	memcpy(Name, lpMsg->Name, sizeof(lpMsg->Name));
	memcpy(szGuild, lpMsg->szGuild, sizeof(lpMsg->szGuild));
	// ----
	int targetIndex2 = gObjGetIndexByName(Name);
	// -----
	if (targetIndex2 == 0)
	{
		if (lpMsg->isBanned == true)
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Profile: Banned");
		}
		else
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Profile: Player");
		}
		// ----
		if (lpMsg->isOnline == true)
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] %s is %s on %s", Name, g_Chatfunc.GetMsgByStatus(lpMsg->isOnline), ServerName);
		}
		else
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] %s is %s", Name, g_Chatfunc.GetMsgByStatus(lpMsg->isOnline));
		}
		// -----
		g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Guild: %s, VIP Days: %d, VIP: %s Credits: %d", szGuild,
			lpMsg->isVip, g_VIPSystem.RequestVipLevelName(lpMsg->VipLevel, 2), lpMsg->nCredits);
		// -----
		if (lpMsg->isOnline == true)
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Level %d(%d), %s, %s (%dx%d)", lpMsg->wLevel, lpMsg->nResets,
				gObjGetClassNameByID(lpMsg->DBClass), GetMapNameByID(lpMsg->Map), lpMsg->X, lpMsg->Y);
		}
		else
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Level %d(%d), %s", lpMsg->wLevel, lpMsg->nResets, gObjGetClassNameByID(lpMsg->DBClass));
		}

		g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Str: %d, Agi: %d, Vit: %d, Ene: %d", lpMsg->str, lpMsg->agi, lpMsg->vit, lpMsg->ene);
		// ----
		if (lpMsg->DBClass == 64)
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Cmd: %d", lpMsg->cmd);
		}
	}
	else
	{
		int targetIndex = targetIndex2;
		// ----
		_NEW_OBJECT * ntObject = &g_GS.nObject[NINDEX(targetIndex)];
		// ----
		if (lpMsg->isBanned == true)
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Profile: Banned");
		}
		else
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Profile: Player");
		}
		// ----
		g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] %s is %s on %s",
			Name, g_Chatfunc.GetMsgByStatus(lpMsg->isOnline), lpMsg->szServerName);
		// ----
		g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Guild: %s, VIP: %s, Credits: %d",
			g_Chatfunc.GetGuildString(targetIndex), g_Chatfunc.GetVipString(targetIndex), lpMsg->nCredits);
		// ----
		g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Level %d(%d), %s, %s (%dx%d)",
			gObj[targetIndex].Level, lpMsg->nResets, gObjGetClassName(targetIndex), GetMapName(targetIndex), gObj[targetIndex].X, gObj[targetIndex].Y);
		// ----
		g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Str: %d, Agi: %d, Vit: %d, Ene: %d",
			gObj[targetIndex].Strength, gObj[targetIndex].Dexterity, gObj[targetIndex].Vitality, gObj[targetIndex].Energy);
		// ----
		if (gObj[targetIndex].Class == 4)
		{
			g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] Cmd: %d", gObj[targetIndex].Leadership);
		}
	}
	if (lpMsg->isMarry == true)
		g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] IsMarried: Yes, To: %s Kill Points: %d", lpMsg->MarryName, lpMsg->killEvent);
	else
		g_Msg.Msg(lpMsg->SeekingIndex, "@[Info] IsMarried: No; Kill Points: %d", lpMsg->killEvent);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSendInfoStateMsg	(char * szName, bool state)
{
	MSG_INFO_STATE pMsg	= {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_INFOSTATE);
	// ----
	pMsg.bState = state;
	// ----
	memcpy(pMsg.szNick, szName, sizeof(pMsg.szNick));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSendBuyVipMsg(std::string szAccountID, std::string szNick, int VipLevel, int VipDays, int VipPrice)
{
	MSG_BUY_VIP_REQUEST pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_BUYVIP);
	// ----
	memcpy(pMsg.szAccountID,	szAccountID.c_str(),	szAccountID.length());
	memcpy(pMsg.szNick,			szNick.c_str(),			szNick.length());
	pMsg.VipLevel = VipLevel;
	pMsg.VipDays = VipDays;
	pMsg.VipPrice = VipPrice;
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSetBanOnChar(std::string szGameMaster, std::string szNick, bool status, int ID)
{
	MSG_BAN_CHAR pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_BANONCHAR);
	// ----
	pMsg.State = status;
	pMsg.ID = ID;
	// ----
	memcpy(pMsg.szNick,			szNick.c_str(),			szNick.length());
	memcpy(pMsg.szGameMaster,	szGameMaster.c_str(),	szGameMaster.length());
	// -----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSetBanOnAcc(std::string szGameMaster, std::string szAccountID, bool status, int ID)
{
	MSG_BAN_ACC pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_BANONACC);
	// ----
	pMsg.State = status;
	pMsg.ID	   = ID;
	// ----
	memcpy(pMsg.szAccountID,	szAccountID.c_str(),	szAccountID.length());
	memcpy(pMsg.szGameMaster,	szGameMaster.c_str(),	szGameMaster.length());
	// -----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDAdvMsgMsg(std::string PakahName)
{
	MSG_ADVMSG pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_ADVMSG);
	// ----
	memcpy(pMsg.PakahName, PakahName.c_str(), PakahName.length());
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDRunEventWinnerSend(int aIndex)
{
	MSG_RUNEVENT_SENDWINNER pMsg = {0};
	// ----
	HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_RUNEVENT, VDS_SUBPACKET_RUNEVENT_HEADERS::RUNEVENT_SUBHEAD_WINNERGET);
	// ----
	memcpy(pMsg.szAccountID,	gObj[aIndex].AccountID,		sizeof(pMsg.szAccountID));
	memcpy(pMsg.szNick,			gObj[aIndex].Name,			sizeof(pMsg.szNick));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDWroteEventWinnerSend(int aIndex)
{
	MSG_WROTEEVENT_SENDWINNER pMsg = {0};
	// ----
	HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_WROTEEVENT, VDS_SUBPACKET_WROTEEVENT_HEADERS::WROTEEVENT_SUBHEAD_WINNERGET);
	// ----
	memcpy(pMsg.szAccountID,	gObj[aIndex].AccountID,		sizeof(pMsg.szAccountID));
	memcpy(pMsg.szNick,			gObj[aIndex].Name,			sizeof(pMsg.szNick));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDConfuseEventWinnerSend(int aIndex)
{
	MSG_CONFUSEEVENT_SENDWINNER pMsg = {0};
	// ----
	HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_CONFUSEEVENT, VDS_SUBPACKET_CONFUSEEVENT_HEADERS::CONFUSEEVENT_SUBHEAD_WINNERGET);
	// ----
	memcpy(pMsg.szAccountID,	gObj[aIndex].AccountID,		sizeof(pMsg.szAccountID));
	memcpy(pMsg.szNick,			gObj[aIndex].Name,			sizeof(pMsg.szNick));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSendQuery(std::string Query)
{
	Sleep(100);
	// ----
	MSG_DOQUERY pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_DOQUERY);
	// ----
	memcpy(pMsg.Query, Query.c_str(), Query.length());
	// ----
	pMsg.QueryLen = Query.length();
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDLotteryEventWinnerSend(int aIndex)
{
	MSG_LOTTERYEVENT_SENDWINER pMsg = {0};
	// ----
	HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_LOTTERYEVENT, VDS_SUBPACKET_RUNEVENT_HEADERS::RUNEVENT_SUBHEAD_WINNERGET);
	// ----
	memcpy(pMsg.szAccountID,	gObj[aIndex].AccountID,		sizeof(pMsg.szAccountID));
	memcpy(pMsg.szNick,			gObj[aIndex].Name,			sizeof(pMsg.szNick));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDLotteryEventSenderSend(int aIndex, UINT Number)
{
	MSG_LOTTERYEVENT_GETSENDER pMsg = {0};
	// ----
	HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_LOTTERYEVENT, VDS_SUBPACKET_LOTTERYEVENT_HEADERS::LOTTERYEVENT_SUBHEAD_SENDERGET);
	// ----
	memcpy(pMsg.szNick,			gObj[aIndex].Name,			sizeof(pMsg.szNick));
	// ----
	pMsg.Number	= Number;
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSUnBanSet(char * GMName, char * PlayerName, int ibanReason)
{
	MSG_UNBAN pMsg	= {0};
	// ---- 
	HeadSet1(& pMsg.Head , sizeof(pMsg) , HEAD_UNBAN);
	// ----
	pMsg.nReason		= ibanReason;
	// ----
	memcpy(pMsg.szGameMasterNick,		GMName,		sizeof(pMsg.szGameMasterNick));
	memcpy(pMsg.szPlayerNick,			PlayerName, sizeof(pMsg.szPlayerNick));		
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDCheckAccess_Jump(int aIndex, char * TargetName, BYTE TeleportID, char * command)
{
	MSG_ACCESS_JUMP pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CHECKACCESS_JUMP);
	// ----
	pMsg.State			= true;
	pMsg.aIndex			= aIndex;
	pMsg.TeleportID		= TeleportID;
	// ----
	memcpy(pMsg.Name, gObj[aIndex].Name, sizeof(pMsg.Name));
	memcpy(pMsg.Command, command, sizeof(pMsg.Command));
	memcpy(pMsg.TargetName, TargetName, sizeof(pMsg.TargetName));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDCheckAccess_Come(int aIndex, char * TargetName, char * command)
{
	MSG_ACCESS_COME pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CHECKACCESS_COME);
	// ----
	pMsg.State			= true;
	pMsg.aIndex			= aIndex;
	// ----
	memcpy(pMsg.Name, gObj[aIndex].Name, sizeof(pMsg.Command));
	memcpy(pMsg.Command, command, sizeof(pMsg.Command));
	memcpy(pMsg.TargetName, TargetName, sizeof(pMsg.TargetName));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDCheckAccess_Move(int aIndex,char * Name , char * command)
{
	MSG_ACCESS_MOVE pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CHECKACCESS_MOVE);
	// ----
	pMsg.Name;
	pMsg.State			= true;
	pMsg.aIndex			= aIndex;
	// ----
	memcpy(pMsg.Name, Name, sizeof(pMsg.Name));
	memcpy(pMsg.Command, command, sizeof(pMsg.Command));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDCheckAccess_GreenMSG(int aIndex, char * Name , char * command)
{
	MSG_ACCESS_GREENMSG pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CHECKACCESS_GREENMSG);
	// ----
	pMsg.Name;
	pMsg.State			= false;
	pMsg.aIndex			= aIndex;
	// ----
	memcpy(pMsg.Name, Name, sizeof(pMsg.Name));
	memcpy(pMsg.Command, command, sizeof(pMsg.Command));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDMsgStatus(char * Name, int time, int status)
{

	MSG_MSG_STATUS pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_MSG_STATUS);
	// ----
	pMsg.Name;
	pMsg.Status			= status;
	pMsg.Time			= time;
	// ----
	memcpy(pMsg.Name, Name, sizeof(pMsg.Name));
	
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDLogHack(int aIndex, char * Name)
{
	MSG_LOG_HACK pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_LOG_HACK);
	// ----
	pMsg.Name;
	pMsg.aIndex			= aIndex;
	// ----
	memcpy(pMsg.Name, Name, sizeof(pMsg.Name));
	
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDCharacterGotOnlineOrOffline(int aIndex, char * sAccountID, OFFLINE_ONLINE_STATUS Status_Co)
{
	MSG_CLIENT_STATUS pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CLIENT_STATUS);
	// ----
	pMsg.nIndex		= aIndex;
	pMsg.Status		= Status_Co;
	pMsg.btServerCode = g_Config.nServerCode;
	// ----
	memcpy(pMsg.szNick,			gObj[aIndex].Name,		sizeof(gObj[aIndex].Name));
	//g_GmsLog.Output("del check %s", gObj[aIndex].Name);
	memcpy(pMsg.szAccountID,	sAccountID,				sizeof(pMsg.szAccountID));
	memcpy(pMsg.szIpAddr,		gObj[aIndex].Ip_addr,	sizeof(gObj[aIndex].Ip_addr));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDCharacterGotDelOrCreated(int aIndex, char * sAccountID, char * sName, OFFLINE_ONLINE_STATUS Status_Co)
{
	MSG_CLIENT_STATUS pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CLIENT_STATUS);
	// ----
	pMsg.nIndex		= aIndex;
	pMsg.Status		= Status_Co;
	pMsg.btServerCode = g_Config.nServerCode;
	// ----
	memcpy(pMsg.szNick,			sName,					sizeof(pMsg.szNick));
	memcpy(pMsg.szAccountID,	sAccountID,				sizeof(pMsg.szAccountID));
	memcpy(pMsg.szIpAddr,		gObj[aIndex].Ip_addr,	sizeof(gObj[aIndex].Ip_addr));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDEventCommandGMS (int aIndex)
{
	MSG_EVENT_COMMAND pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_EVENT_COMMAND);
	// ----
	pMsg.aIndex			= aIndex;
	pMsg.Status			= 0;
	// ----
	memcpy(pMsg.AccountID,		gObj[aIndex].AccountID,		sizeof(gObj[aIndex].AccountID));
	memcpy(pMsg.Name,			gObj[aIndex].Name,			sizeof(gObj[aIndex].Name));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDCrewMsgReq(int aIndex)
{
	MSG_CREW pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_CREW_MSG);
	// ----
	pMsg.SeekingIndex = aIndex;
	// ----
	memcpy(pMsg.SeekingName, gObj[aIndex].Name, sizeof(pMsg.SeekingName));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDMarryUpdate(char * MarryName1, char * MarryName2, bool MarrigeStatus)
{
	MSG_MARRY_SYSTEM_UPDATE pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_MARRY_SYSTEM_UPDATE);
	// ----
	pMsg.MarrigeStatus		= MarrigeStatus;
	// ----
	memcpy(pMsg.MarryName1,		MarryName1,				sizeof(pMsg.MarryName1));
	memcpy(pMsg.MarryName2,		MarryName2,				sizeof(pMsg.MarryName2));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSkinCheck(char * GMName, char * AccountID, char * szName, int MID)
{
	int aIndex = gObjGetIndexByName(GMName);
	MSG_SKIN_CHECK pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_SKINACCESS);
	// ----
	pMsg.MID		= MID;
	// ----
	memcpy(pMsg.szGMName,		GMName,				sizeof(pMsg.szGMName));
	memcpy(pMsg.szName,			szName,				sizeof(pMsg.szName));
	memcpy(pMsg.szAccountID,	AccountID,			sizeof(pMsg.szAccountID));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDInvisibleChange(char * GMName, char * AccountID, bool status)
{
	MSG_INVISIBLE_COMMAND pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_INVISIABLE_COMMAND);
	// ----
	pMsg.status		= status;
	// ----
	memcpy(pMsg.szGMName,		GMName,				sizeof(pMsg.szGMName));
	memcpy(pMsg.szAccountID,	AccountID,			sizeof(pMsg.szAccountID));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDInvisibleCrewChange(char * GMName, char * AccountID, bool status)
{
	MSG_INVISIBLE_CREW_COMMAND pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_INVISIABLE_CREW_COMMAND);
	// ----
	pMsg.status		= status;
	// ----
	memcpy(pMsg.szGMName,		GMName,				sizeof(pMsg.szGMName));
	memcpy(pMsg.szAccountID,	AccountID,			sizeof(pMsg.szAccountID));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDAssistCheckRequest(char * AssistName, char * MemberName, char * GuildName, int Type)
{
	MSG_GUILD_MEMBER_STATUS pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GUILD_MEMBER_STATUS);
	// ----
	pMsg.Type		= Type;
	// ----
	memcpy(pMsg.AssistName,		AssistName,			sizeof(pMsg.AssistName));
	memcpy(pMsg.MemberName,		MemberName,			sizeof(pMsg.MemberName));
	memcpy(pMsg.GuildName,		GuildName,			sizeof(pMsg.GuildName));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDKickCheckRequest(char * AssistName, char * MemberName, char * GuildName)
{
	MSG_GUILD_KICK_MEMBER pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GUILD_KICK_MEMBER);
	// ----
	memcpy(pMsg.AssistName,		AssistName,			sizeof(pMsg.AssistName));
	memcpy(pMsg.MemberName,		MemberName,			sizeof(pMsg.MemberName));
	memcpy(pMsg.GuildName,		GuildName,			sizeof(pMsg.GuildName));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDSetAssistCheckRequest(char * ManagerName, char * GuildName, BYTE Type)
{
	MSG_GUILD_SET_ASSIST pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GUILD_SET_ASSIST);
	// ----
	memcpy(pMsg.ManagerName,		ManagerName,	sizeof(pMsg.ManagerName));
	memcpy(pMsg.GuildName,		GuildName,			sizeof(pMsg.GuildName));
	// ----
	pMsg.Type = Type;
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDGuildJoinRequestByAssist(char * AssistName, char * ReqName)
{
	MSG_GUILD_JOIN_REQUEST pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_GUILD_JOIN_REQUEST);
	// ----
	memcpy(pMsg.AssistName,		AssistName,		sizeof(pMsg.AssistName));
	memcpy(pMsg.ReqName,		ReqName,		sizeof(pMsg.ReqName));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDKillEventCheck(char * Name, char * tName)
{
	MSG_KILLEVENT_CHECKPOINTS pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_KILL_EVENT);
	// ----
	memcpy(pMsg.Nick,		Name,		sizeof(pMsg.Nick));
	memcpy(pMsg.tNick,		tName,		sizeof(pMsg.tNick));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDShopBuyItemRequest(std::string sAccountId, std::string sName, int iShopId, BYTE bProductPos, int iPrice)
{
	#ifdef GS_99_60T

	MSG_SHOP_BUY_ITEM_REQUEST pMsg = { 0 };
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_SHOP_BUY_REQUEST);
	// ----
	memcpy(pMsg.szAccountId, sAccountId.c_str(), sAccountId.length());
	memcpy(pMsg.szName, sName.c_str(), sName.length());
	// ----
	pMsg.iShopId = iShopId;
	pMsg.bProductPos = bProductPos;
	pMsg.iPrice = iPrice;
	// ----
	g_DataServer.DataSend((UCHAR *)& pMsg, sizeof(pMsg));

#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDFixLevelBugRequest(int aIndex, char * szName)
{
	MSG_S_FIX_LEVEL_BUG pMsg = { 0 };
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_FIXLEVELBUG);
	// ----
	pMsg.nIndex = aIndex;
	pMsg.iLevel = gObj[aIndex].Level;
	// ----
	memcpy(pMsg.szName, gObj[aIndex].Name, sizeof(pMsg.szName));
	// ----
	g_DataServer.DataSend((UCHAR *)& pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GDAntiHackProcessNotify(std::string sAccountId, std::string sIpAddress, std::string sProcess, ULONGLONG uChecksum)
{
	MSG_ANTIHACK_PROCESS_NOTIFY pMsg = { 0 };
	// ----
	HeadSet4(&pMsg.Head, sizeof(pMsg), HEAD_ANTIHACK, VDS_SUBPACKET_ANTIHACK_HEADERS::ANTIHACK_SUBHEAD_PROCESS_NOTIFY);
	// ----
	memcpy(pMsg.szAccountId, sAccountId.c_str(), sAccountId.length());
	memcpy(pMsg.szIpAddr, sIpAddress.c_str(), sIpAddress.length());
	memcpy(pMsg.szProcess, sProcess.c_str(), sProcess.length());
	// ----
	pMsg.uChecksum = uChecksum;
	// ----
	g_DataServer.DataSend((UCHAR *)& pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void DGShopBuyItemResult(MSG_SHOP_BUY_ITEM_RESULT * pMsg)
{
#ifdef GS_99_60T

	char szAccountId[11] = { 0 };
	char szName[11] = { 0 };
	// ----
	memcpy(szAccountId, pMsg->szAccountId, sizeof(pMsg->szAccountId));
	memcpy(szName, pMsg->szName, sizeof(pMsg->szName));
	// ----
	if (gObjIsAccontConnect(szAccountId)) {
		int aIndex = gObjGetIndexByName(szName);
		// ----
		if (aIndex > 0) {
			if (pMsg->iShopId <= CShop::bShopsCount) {
				CShop::Shops[pMsg->iShopId].BuyResult(aIndex, pMsg->bProductPos, (SHOP_BUY_RESULT)pMsg->bResult);
			}
		}
	}

#endif
}
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void DGSendMessageAllRecive(MSG_R_GLOAL_MSG* pMsg)
{
	char szMsg[101] = { 0 };
	memcpy(szMsg, pMsg->szMessage, sizeof(pMsg->szMessage));
	g_Msg.NoticeAll(szMsg);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------