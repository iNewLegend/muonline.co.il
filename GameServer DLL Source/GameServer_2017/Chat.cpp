//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "StdAfx.h"
#include "Chat.h"
#include "TMessages.h"
#include "User.h"
#include "TLogToFile.h"
#include "Object.h"
#include "DSXProtocol.h"
#include "TSetup.h"
#include "TConfig.h"
#include "TMarrySystem.h"
#include "TBotSystem.h"
#include "TChatVote.h"
#include "TCore.h"
#include "TDataServerSocket.h"
#include "TShop.h"
#include "OffTrade.h"
#include "RedDragon.h"
#include "VIPSystem.h"
#include "Helper.h";
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CChatFunctions	g_Chatfunc;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const char * CChatFunctions::GetMsgByStatus(bool status)
{
	if (status) {
		return "Online";

	}

	return "Offline";
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

char CChatFunctions::GetParam(char id, char* txt, char* buff)
{
	static char	msg[255];
	// ----
	memset(msg, 0, sizeof(msg));
	// ----
	char	cnt			= 0;
	char*	pch			= NULL;	
	// ----
	strcpy( msg , txt );
	// ----
	pch					= strtok(msg ," ");
	// ----
	while(pch != NULL)
	{
		if(cnt == id)
		{
			strcpy(buff , pch);
			// ----
			return id;
		}
		// ----
		pch				= strtok(NULL , " ");
		// ----
		cnt++;
	}
	// ----
	return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CChatFunctions::GetLongParam(char* text, char* buff)
{
	static char	msg[255];
	// ----
	memset(msg, 0, sizeof(msg));
	// ----
	LPCSTR Content	= {0};
	int sLen		= 0;
	// ----
	strcpy(msg, text);
	// ----
	sLen = strlen(msg);
	// ----
	for(int i = 0 ; i < sLen ; ++i)
	{
		if((char)msg[i] == 0x20)
		{
			msg[i] = 0x00;
			// ----
			Content = msg + i + 1;
			// ----
			break;
		}
	}
	// ----
	strcpy(buff, Content);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LPCSTR CChatFunctions::GetGuildString(int aIndex)
{
	LPCSTR lpReturn = "N/A";
	// ----
	if(strlen(gObj[aIndex].GuildName) > 0)
	{
		lpReturn = gObj[aIndex].GuildName;
	}
	// ----
	return lpReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LPCSTR CChatFunctions::GetVipString(int aIndex)
{
	LPCSTR lpReturn			= "Off";
	// ----
	_NEW_OBJECT * nObject	= & g_GS.nObject[FIXINDEX];
	// ----
	if(nObject->isVip == true)
	{
		lpReturn = "On";
	}
	// ----
	return lpReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatGMBanAdd(int aIndex, char * Message)
{
	char	Name[256]	= {0};
	int		Days		= 0;
	int		BanRes		= 0;
	// ----
	if(gObjIsGameMaster(aIndex) == true)
	{
		if(strcmpi("/Ban", Message) == 0)
		{
			g_Msg.Msg(aIndex, "@[Ban] Useage: /Ban <Nick> <Days> <ID>");
			// ----
			return;
		}
		sscanf(& Message[4], "%s %d %d", Name, & Days, & BanRes);
		// ----
		if(strlen(Name) > 10)
		{
			g_Msg.Msg(aIndex, "@[Ban] השם של החשקן לא יכול להיות יותר מי 10 תווים");
			// ----
			return;
		}
		// ----
		if(Days == 0)
		{
			g_Msg.Msg(aIndex, "@[Ban] באפשרותך לתת באן למינימום יום אחד");
			g_Msg.Msg(aIndex, "@[Ban] Useage: /Ban <Nick> <Days> <ID>");
			// ----
			return;
		}
		// ----
		if(BanRes <= 0)
		{
			g_Msg.Msg(aIndex, "@[Ban] שחכת לציין מספר אשכול בפורום ציין 1 במידה ותרצה לעדכן בהמשך");
			g_Msg.Msg(aIndex," @[Ban] Useage: /Ban <Nick> <Days> <ID>");
			// ----
			return;
		}
		// ----
		g_GmsLog.Output("[TCHAT][ChatGMBanAdd] :: User [%s] Banned By [%s] for [%d] days ResID [%d]", Name, gObj[aIndex].Name,
			Days, BanRes);
		// ----
		Name[11] = 0;
		// ----
		ObjectBanAdd(aIndex, Name, Days, BanRes);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatGMBanUsersAdd(int aIndex, char * Message)
{
	char	Name[256]	= {0};
	int		Days		= 0;
	int		BanRes		= 0;
	// ----
	if(gObjIsGameMaster(aIndex) == true)
	{
		if(strcmpi("/banusers", Message) == 0)
		{
			g_Msg.Msg(aIndex, "@[banusers] Useage: /banusers <Nick> <Days> <ID>");
			// ----
			return;
		}
		sscanf(& Message[9], "%s %d %d", Name, & Days, & BanRes);
		// ----
		if(strlen(Name) > 10)
		{
			g_Msg.Msg(aIndex, "@[banusers] השם של החשקן לא יכול להיות יותר מי 10 תווים");
			// ----
			return;
		}
		// ----
		if(Days == 0)
		{
			g_Msg.Msg(aIndex, "@[banusers] באפשרותך לתת באן למינימום יום אחד");
			g_Msg.Msg(aIndex, "@[banusers] Useage: /banusers <Nick> <Days> <ID>");
			// ----
			return;
		}
		// ----
		if(BanRes <= 0)
		{
			g_Msg.Msg(aIndex, "@[banusers] שחכת לציין מספר אשכול בפורום ציין 1 במידה ותרצה לעדכן בהמשך");
			g_Msg.Msg(aIndex," @[banusers] Useage: /banusers <Nick> <Days> <ID>");
			// ----
			return;
		}
		// ----
		g_GmsLog.Output("[TCHAT][ChatGMBanUsersAdd] :: User [%s] Banned By [%s] for [%d] days ResID [%d]", Name, gObj[aIndex].Name,
			Days, BanRes);
		// ----
		Name[11] = 0;
		// ----
		ObjectBanUsersAdd(aIndex, Name, Days, BanRes);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatInfoCMD(int aIndex, char * Message)
{
	char	TargetName[200]	= {0};
	int		TargetIndex		= -1;
	// ----
	if(strcmpi("/Info", Message) == 0)
	{
		g_Msg.Msg(aIndex, "[Info] Useage: /Info <Name>");
		// ----
		return;
	}
	// ----
	g_Chatfunc.GetParam(1, Message, TargetName);
	// ----
	GDSendInfoMsg(aIndex, TargetName);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatGOCmd(int aIndex, char * Message)
{
	char	TargetName[200]	= {0};
	int		TargetIndex		= -1;
	// ----
	if(strcmpi(Message, "/Go") == 0)
	{
		g_Msg.Msg(aIndex, "[Go] Useage: /Go <Name>");
		g_Msg.Msg(aIndex, "[Go] Price %d Credit.", GO_PRICE);
		// ----
		return;
	}
	// ----
	g_Chatfunc.GetParam(1, Message, TargetName);
	// ----
	TargetIndex				= gObjGetIndexByName(TargetName);
	// ----
	if((TargetIndex >= OBJECT_START_INDEX) && (TargetIndex <= OBJECT_MAX_INDEX))
	{
		_NEW_OBJECT * ntObject	= & g_GS.nObject[NINDEX(TargetIndex)];
		// ----
		if(ntObject->isGoAllow == false)
		{
			g_Msg.Msg(aIndex, "@[Go] Gooff השחקן חסם את האפשרות ");
			g_Msg.Msg(TargetIndex, "@[Go] ניסה להתשגר לכיוון שלך ללא הצלחה,%s", gObj[aIndex].Name);
		}
		else if(gObjIsGameMaster(TargetIndex) == true)
		{
			g_Msg.Msg(aIndex, "@[Go] (GM) מצטערים ,לא ניתן להתשגר למנהל משחק");
			g_Msg.Msg(TargetIndex, "@[Go] ניסה להתשגר לכיוון שלך,%s", gObj[aIndex].Name);
		}
		else if(gObjGetMapLevel(gObj[TargetIndex].MapNumber, gObj[TargetIndex].Class) == -1)
		{
			g_Msg.Msg(aIndex, "@[GO] Access denied map");
			g_Msg.Msg(aIndex, "@[GO] לא נית לגשת למפה");
		}
		// ----
		else if((gObj[aIndex].Level) < (gObjGetMapLevel(gObj[TargetIndex].MapNumber, gObj[TargetIndex].Class)))
		{
			g_Msg.Msg(aIndex, "@[GO] אתה רמה נמוכה מדי בשביל לגשת למפה");
		}
		else
		{
			ObejctGoState(0, aIndex, TargetIndex, GO_PRICE , false);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatKandumCMD(int aIndex)
{
	/*BYTE*/ auto PetType		= gObj[aIndex].pInventory[8].m_Type;
	/*BYTE*/ auto Ring1Type		= gObj[aIndex].pInventory[10].m_Type;
	/*BYTE*/ auto Ring2Type		= gObj[aIndex].pInventory[11].m_Type;
	// ----
	if((PetType == 0xA2) || (PetType == 0xA3))
	{
		g_Msg.Msg(aIndex, 1, "יש להוריד את הסוס לפני השימוש בפקודה");	
		g_Msg.Msg(aIndex, 1, "you can't kundun while using dinorat or unricorn");
	}
	else if((Ring1Type == 0xB4) || (Ring2Type == 0xB4))
	{
		g_Msg.Msg(aIndex, 1, "לא ניתן להשתמש בפוקדה אם טבעת מסוג וויזרד");	
		g_Msg.Msg(aIndex, 1, "יש להוריד את הטבעת ולנסות שוב");	
		g_Msg.Msg(aIndex, 1, "you can't kundun  while using Wizard Ring");
	}
	else
	{
		ObejctKandumState(0, aIndex, g_Config.nKandunPrice, 0);
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatOffTradeCMD(int aIndex)
{
	g_OffTrade.RequestOfflineTrade(aIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatRedDragonCMD(int aIndex)
{
	GDRedDragonRequest(aIndex, gObj[aIndex].AccountID);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatPostCMD(int aIndex, char * Message)
{
	_NEW_OBJECT * nObject = & g_GS.nObject[FIXINDEX];
	// ----
	if ((g_VIPSystem.RequestVIPBonus(aIndex, 0) == true) && (nObject->isVip == true) || (g_Config.isGSCastle == true) || (strstr(gObj[aIndex].GuildName, "Mefakhim") != NULL))
	{
		DWORD dwCurTick = GetTickCount();
		// ----
		if(((dwCurTick - nObject->dwPostTick) > CHAT_FLOOD) || 
			(nObject->dwPostTick == 0)						|| 
			(g_Config.isGSCastle == true)					||
			(gObjIsGameMaster(aIndex) == true)				)
		{
			if(strcmpi(Message, "/Post") == 0)
			{
				g_Msg.Msg(aIndex, "Useage : /Post <Text>");
			}
			else
			{
				char * Content = (char*) Message;
				// ----
				g_Chatfunc.GetLongParam(Message, Content);
				// ----
				for(USHORT i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
				{
					if(gObj[i].Type == OBJ_USER)
					{
						if(gObj[i].Connected == PLAYER_PLAYING)
						{
							g_Msg.AllianceMsg(i, aIndex, " [Post] %s", Content);
						}
					}
				}
				// ---
				nObject->dwPostTick = GetTickCount();
			}
		}
		else
		{
			g_Msg.Msg(aIndex, "@[Post].הגנת הצפה - ניתן לשלח הודעה כל חצי דקה");
			g_Msg.Msg(aIndex, 1, "[Post] יש לך לחכות עוד %d שניות", (CHAT_FLOOD/1000) - ((dwCurTick - nObject->dwPostTick)/1000));
		}
	}
	else
	{
		g_Msg.Msg(aIndex, "@[Post] הפקודה מתאפשרת רק למשתמשי ויאיפי");
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatMsgCMD(int aIndex, char * Message)
{
	if (MSG_STATUS == true)
	{
		if(strcmpi(Message, "/Msg") == 0)
		{
			g_Msg.Msg(aIndex, "[Msg] Useage: /Msg <Text>");
			g_Msg.Msg(aIndex, "[Msg] Price %d Credit.", MSG_PRICE);
			// ----
			return;
		}
		// ----
		char * Content = (char*) Message;
		// ----
		g_Chatfunc.GetLongParam(Message, Content);
		// ----
		GDSendPost(gObj[aIndex].Name, MSG_PRICE, Message, gObj[aIndex].AccountID);
	}
	else
		g_Msg.Msg(aIndex, "@[MSG] הודעות המסג' סגורים עקב שידור / איוונט");
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatMsgCMDGM(int aIndex, char * Message)
{
	char * Content = (char*) Message;
	char	MessageSend[500]	= {0};
	// ----
	GDSendPostGM(gObj[aIndex].Name, & Message[2], gObj[aIndex].AccountID);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatComeCmd(int aIndex, char * Message)
{
	char	TargetName[200]	= {0};
	int		TargetIndex		= -1;
	// ----
	if(gObjIsGameMaster(aIndex) == true)
	{
		if(strcmpi(Message, "/come") == 0)
		{
			g_Msg.Msg(aIndex, "[Come] Syntax: /come <Name>");
			// ----
			return;
		}
		// ----
		g_Chatfunc.GetParam(1, Message, TargetName);
		// ----
	
		TargetIndex				= gObjGetIndexByName(TargetName);
		// ----
		if((TargetIndex >= OBJECT_START_INDEX) && (TargetIndex <= OBJECT_MAX_INDEX))
		{
			_NEW_OBJECT * ntObject	= & g_GS.nObject[NINDEX(TargetIndex)];
			// ----
			
			ObjectComeTeleport(aIndex, TargetName,0,true);
		}

		else
			g_Msg.Msg(aIndex, "@[Come] The User Is Not Connected / Exist");
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatUnBanCmd(int aIndex, char * Message)
{
	char	Name[256]	= {0};
	char	Reason[256]	= {0};
	int		BanRes		= 0;
	// ----
	if(gObjIsGameMaster(aIndex) == true)
	{
		if(strcmpi("unban", Message) == 0)
		{
			g_Msg.Msg(aIndex, "@[Ban] Useage: /Ban <Nick> <Days> <ID>");
			// ----
			return;
		}

		g_Chatfunc.GetParam(1, Message, Name);
		g_Chatfunc.GetParam(2, Message, Reason);
		BanRes = atoi(Reason);
		// ----
		if(strlen(Name) > 10)
		{
			g_Msg.Msg(aIndex, "@[Ban] השם של החשקן לא יכול להיות יותר מי 10 תווים");
			// ----
			return;
		}
		// ----
		
		if(BanRes <= 0)
		{
			g_Msg.Msg(aIndex, "@[UnBan] שחכת לציין מספר אשכול בפורום ציין 1 במידה ותרצה לעדכן בהמשך");
			g_Msg.Msg(aIndex," @[UnBan] Useage: /UnBan <Nick> <ID>");
			// ----
			return;
		}
		// ----
		int targetIndex = -1;
		targetIndex = gObjGetIndexByName(Name);

		
		g_GmsLog.Output("[TCHAT][ChatGMUnBan] :: User [%s] UnBanned By [%s] ResID [%d]", Name, gObj[aIndex].Name, BanRes);
		// ----
		Name[11] = 0;
		// ----
		
		ObjectUnBanAdd(aIndex, Name, BanRes);
		
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatMoveMeCmd (int aIndex, char * Message)
{
	int Y = 120;
	int X = 120;
	int Map = 0;
	// ----
	if(gObjIsGameMaster(aIndex) == true)
	{
		if(strcmpi(Message, "/moveme") == 0)
		{
			g_Msg.Msg(aIndex, "[MoveMe] Syntax: /moveme <Map> <X> <Y>");
			// ----
			return;
		}
		// ----
		sscanf(& Message[7], "%d %d %d", & Map, & X, & Y);
		// ----
		if (X > 255 || Y > 255)
		{
			g_Msg.Msg(aIndex, "[MoveMe] Syntax: X / Y > 255");
			// ----
			return;
		}
		if (X < 0 || Y < 0)
		{
			g_Msg.Msg(aIndex, "[MoveMe] Syntax: X / Y < 0");
			// ----
			return;
		}
		ObjectMoveMeTeleport(aIndex, Map, X, Y);

	}

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CheckMoveAndDisAcc(int aIndex, char * Message, int type, bool access)
{
	_NEW_OBJECT * nObject	= & g_GS.nObject[FIXINDEX];
	// ----
	bool temp = true;
	// ----
	if(gObjIsGameMaster(aIndex) == true)
	{

		switch (type)
		{
		case 0:
			{
				GDCheckAccess_Move(aIndex, gObj[aIndex].Name ,Message);
			}
			break;
		case 1:
			{
				if (access == false)
				{
					g_Msg.Msg(aIndex, "@[%s] You Don't Have Access for this Command.",Message);
					g_Msg.Msg(aIndex, "@[%s] You Have Been Reported.",Message);
					// ----
					g_GmsLog.Output(GMS_LOG_Access, gObj[aIndex].AccountID, gObj[aIndex].Name, Message);
				}
				if(strcmpi(Message, "Disconnec") == 0)
					nObject->canUseDisconnect	= access;
				if(strcmpi(Message, "Move") == 0)
					nObject->canUseMove			= access;
			}
			break;
		}
	}

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CheckGreenMSG(int aIndex, char * Message, int type, bool access)
{
	if(gObjIsGameMaster(aIndex) == true)
	{
		switch(type)
		{
			case 0:
			{
				char Mes[55] = {0};

				g_Chatfunc.GetLongParam(Message, Mes);

				GDCheckAccess_GreenMSG(aIndex, gObj[aIndex].Name , Mes);
			}
			break;

			case 1:
			{
				if(! access) {
					g_Msg.Msg(aIndex, "@[%s] You Don't Have Access for this Command.", "GreenMSG");
					g_Msg.Msg(aIndex, "@[%s] You Have Been Reported.", "GreenMSG");
					// ----
					g_GmsLog.Output(GMS_LOG_Access, gObj[aIndex].AccountID, gObj[aIndex].Name, "GreenMSG");
				}
				else {
					g_Msg.GreenNoticeAll(Message);
				}

			}	
			break;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatMSGChange(int aIndex, char * Message)
{
	char param1[100] = { 0 };
	char param2[100] = { 0 };

	g_Chatfunc.GetParam(1, Message, param1);
	g_Chatfunc.GetParam(2, Message, param2);

	int Status = atoi(param1);
	int time = atoi(param2);

	if(strcmpi("/msgst", Message) == 0)
	{
		g_Msg.Msg(aIndex, "@[MsgSt] Useage: /msgst <Status> <Time(in min)>");
		// ----
		return;
	}
	if(Status != 0 && Status !=1) // leo : why not if(Status > 1) ?
	{
		g_Msg.Msg(aIndex, "@[MsgSt] Status Must Be Only 0(Un) / 1 (Locked)");
		// ----
		return;
	}
	if(Status == 1 && time <= 0 || Status == 1 && time > 90)
	{
		g_Msg.Msg(aIndex, "@[MsgSt] Time Must Be Between 0 - 90 Min");
		// ----
		return;
	}
	if (Status == 0)
	{
		g_GmsLog.Output("[TCHAT][MsgOn] :: [%s] Put On Msg", gObj[aIndex].Name);
		GDMsgStatus (gObj[aIndex].Name, 0, Status);
	}
	else if (MSG_STATUS == false)
	{
		g_Msg.Msg(aIndex, "@[MsgSt] To Update The Time You Need first");
		g_Msg.Msg(aIndex, "@[MsgSt] To Get Down the MsgSt");
	}
	else
	{
		g_GmsLog.Output("[TCHAT][MsgOff] :: User [%s] Put Down Msg For [%d] Mins", gObj[aIndex].Name, time);
		GDMsgStatus (gObj[aIndex].Name, time, Status);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatTrackMarry(int aIndex, char * Message)
{
	int		tIndex		= -1;
	// ----
	_NEW_OBJECT * nObject = & g_GS.nObject[NINDEX(aIndex)];
	
	if (nObject->IsMarried != 1)
	{
		g_Msg.Msg(aIndex, "@[Marry] Your Are Not Married");
		return;
	}	
	// ----
	tIndex				= gObjGetIndexByName(nObject->MarryName);
	// ----
	if((tIndex >= OBJECT_START_INDEX) && (tIndex <= OBJECT_MAX_INDEX))
	{
		g_MarrySystem.TrackMarry(aIndex,tIndex);
	}
	else
	{
		g_Msg.Msg(aIndex, "@[Marry] Your partner is offline");
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatReportCommand(int aIndex, char * Message)
{
	_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];
	// ----
	char		Name[256]			= { 0 };
	char		Reason[100]			= { 0 };
	// ----
	DWORD dwCurTick = GetTickCount();

	if (strcmpi(Message, "/report") == 0)
	{
		g_Msg.Msg(aIndex, "~[Report] Useage: /report [Name] [Type]");
		g_Msg.Msg(aIndex, "~[Report] יש לציין סוג דיווח ושם השחקן עליו אתם מדווחים");
		g_Msg.Msg(aIndex, "~[Report] 1 - דיווח על תוכנות לא חוקיות");
		g_Msg.Msg(aIndex, "~[Report] 2 - קריאה לאיש צוות מחובר");
		// -----
		return;
	}
	// ----

	if ((dwCurTick - nObject->dwReportTick) > HELP_FLOOD || (nObject->dwReportTick == 0))
	{
		if (strlen(Name) > 10)
		{
			g_Msg.Msg(aIndex, "~[Report] שם השחקן הכנסת לא חוקי.");
			return;
		}
		// ----
		g_Chatfunc.GetParam(1, Message, Name);
		g_Chatfunc.GetParam(2, Message, Reason); 

		UINT ReasonCode = atoi(Reason);
		// ----
		std::string sReporter = gObj[aIndex].Name;
		std::string sName = Name;

		switch (ReasonCode)
		{
		case 1:
			GDSendReportMsg(gObj[aIndex].Name, Name, Reason);
			GDSendGuildMsg("[System]", "Crew","משתמש בהאקים " +sName + " דיווח שהשחקן " + sReporter);
			GDSendGuildMsg("[System]", "SiegeINS", "משתמש בהאקים " + sName + " דיווח שהשחקן " + sReporter);
			break;
		case 2:
			GDSendReportMsg(gObj[aIndex].Name, Name, Reason);
			GDSendGuildMsg("[System]", "Crew", " זקוק לעזרה מחבר צוות " + sReporter);
			GDSendGuildMsg("[System]", "Mefakhim", " זקוק לעזרה מחבר צוות " + sReporter);
			break;
		default:
			g_Msg.Msg(aIndex, "~[Report] סוג הדיווח אינו חוקי, יש להצמד להוראות הפקודה");
			return;
		}

		// ----
		g_Msg.Msg(aIndex, "~[Report] תודה על הדיווח");
		g_Msg.Msg(aIndex, "~[Report] הדיווח הועבר בהצלחה לגורמים המתאימים");
		// ----
		nObject->dwReportTick = GetTickCount();

	}
	else
	{
		g_Msg.PM(aIndex, "~[Report] ניתן לדווח פעם ב%d דקות", HELP_FLOOD / 60000);
		g_Msg.Msg(aIndex, "~[Report] יש לך לחכות עוד %d שניות", (HELP_FLOOD / 1000) - ((dwCurTick - nObject->dwReportTick) / 1000));
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatMarryStartCommand(int aIndex, char * Message)
{
	char	TargetName[256]	= {0};
	int		tIndex		= -1;
	// ----
	if(strcmpi(Message, "/marry") == 0)
	{
		g_Msg.Msg(aIndex, "@[Marry] Useage: /marry <Name>");
		//g_Msg.Msg(aIndex, "[marry] Price %d Credit.", GO_PRICE);
		// ----
		return;
	}
	// ----
	g_Chatfunc.GetParam(1, Message, TargetName);
	// ----
	if (strlen(TargetName) >10 )
	{
		return;
	}
	tIndex				= gObjGetIndexByName(TargetName);
	// ----
	if((tIndex >= OBJECT_START_INDEX) && (tIndex <= OBJECT_MAX_INDEX))
	{
		g_MarrySystem.StartMarriage(aIndex,tIndex);
	}
	else
	{
		g_Msg.Msg(aIndex, "@[Marry] Your partner is offline or wrong name");
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatHelpCMD(int aIndex)
{
	_NEW_OBJECT * nObject = & g_GS.nObject[FIXINDEX];
	// ----
	if(g_Config.isGSCastle == false)
	{
		DWORD dwCurTick = GetTickCount();
		// ----
		if((dwCurTick - nObject->dwHelpTick) > HELP_FLOOD || (nObject->dwHelpTick == 0))
		{
			g_Msg.PM(aIndex, "[Help]----פקודות בתשלום / לויאיפי----");
			g_Msg.PM(aIndex, "[Help]/vip - קניית ויאיפי בתשלום");
			g_Msg.PM(aIndex, "[Help]/post - פוסט למשתמשי ויאיפי");
			g_Msg.PM(aIndex, "[Help]/msg - פירסום בזהוב בתשלום");
			g_Msg.PM(aIndex, "[Help]/kundun - זימון קאנדן בתשלום");
			g_Msg.PM(aIndex, "[Help]/go - שיגור לשחקן בתשלום");
			g_Msg.PM(aIndex, "[Help]/go on/off - הפעלה וכיבוי אפשרות שיגור אליך");
			g_Msg.PM(aIndex, "[Help]/OffTrade - פתחו חנות להשאירו את השחקן עומד");
			g_Msg.PM(aIndex, "=======================");
			g_Msg.PM(aIndex, "[Help]----פקודות לקבלת מידע----");
			g_Msg.PM(aIndex, "[Help]/crew - קבלת שמות השחקנים של הצוות שמחוברים");
			g_Msg.PM(aIndex, "[Help]/log on/off - הפעלה וכיבוי של הלוג בסייג");
			g_Msg.PM(aIndex, "[Help]/radio off/on - הפעלה וכיבוי רדיו אמיו ישראל");
			g_Msg.PM(aIndex, "[Help]/info - קבלת מידע על שחקן");
			g_Msg.PM(aIndex, "[Help]/infoon /infooff - הפעלה וכיבוי של אפשרות קבלת המידע עליך");
			g_Msg.PM(aIndex, "[Help]/time - קבלת זמן שרת");
			g_Msg.PM(aIndex, "=======================");
			g_Msg.PM(aIndex, "[Help]----פקודות של מערכת החתונה----");
			g_Msg.PM(aIndex, "[Help]/marry - הצעה לחתונה - בתשלום");
			g_Msg.PM(aIndex, "[Help]/marry on/off - הפעלה/כיבוי האפשרות קבלת חתונה");
			g_Msg.PM(aIndex, "[Help]$ - שליחת הודעה לבן זוג");
			g_Msg.PM(aIndex, "[Help]/marrychat on/off - הפעלה/כיבוי האפשרות לקבלת הודעות מהבן זוג");
			g_Msg.PM(aIndex, "[Help]/tmarry - שיגור לבן זוג");
			g_Msg.PM(aIndex, "[Help]/divorce - להתגרש מבן הזוג");
			g_Msg.PM(aIndex, "=======================");
			g_Msg.PM(aIndex, "[Help]-----פקודות של מערכת הגילדות----");
			g_Msg.PM(aIndex, "[Help]/joinguild assistName - בקשה להיכנס לגילד");
			g_Msg.PM(aIndex, "[Help]/setassist on/off - הפעלה וכיבוי גישה של האסיס");
			g_Msg.PM(aIndex, "[Help]/setmember - הפיכה של באטל לחבר על ידי האסיס");
			g_Msg.PM(aIndex, "[Help]/setbattle - הפיכה של חבר לבאטל על ידי האסיס");
			g_Msg.PM(aIndex, "[Help]/kickmemb - הוצאת חבר גילד על ידי האסיס");
			g_Msg.PM(aIndex, "=======================");
			g_Msg.PM(aIndex, "[Help]-----פקודות נוספות----");
			g_Msg.PM(aIndex, "[Help]/shopguard on/off - הפעלה וכיבוי הכנסת חפצים+הכל לחנות");
			g_Msg.PM(aIndex, "[Help]/request on/off - הפעלה וכיבוי קבלת הצעות");
			g_Msg.PM(aIndex, "[Help]/whisper on/off - הפעלה וכיבוי קבלת לחישות");
			g_Msg.PM(aIndex, "muonline.co.il");
			// ----
			nObject->dwHelpTick = GetTickCount();
		}
		else
		{
			g_Msg.PM(aIndex, "[Help] דקות %d ניתן להשתמש בפקודה פעם ב", HELP_FLOOD/60000);
			g_Msg.Msg(aIndex, 1, "[Help] יש לך לחכות עוד %d שניות", (HELP_FLOOD/1000) - ((dwCurTick - nObject->dwHelpTick)/1000));
		
		}
	}
	else
	{
		g_Msg.PM(aIndex, "לא ניתן להשתמש בפקודה בסייג");
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
ChatCore - Called When user writes a input

@param aIndex int
@param lpMsg PMSG_CHATDATA
@return bool - ? continue to ProtocolCore
*/
bool ChatCore(int aIndex, PMSG_CHATDATA * lpMsg)
{
	bool bReturn = false;
	// ----
	static char Command[100];
	static char myTemp[100];
	// ----
	memset(Command, 0, sizeof(Command));
	memset(myTemp, 0, sizeof(myTemp));
	// ----
	_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];
	// ----
	g_Chatfunc.GetParam(0, lpMsg->chatmsg, Command);
	// ----
	// # Chat log
	// ----
	g_ChatLog.Output(CHAT_LOG_MESSAGE_FORMAT, g_Config.nServerCode, gObj[aIndex].AccountID, gObj[aIndex].Name, lpMsg->chatmsg);
	// ----
	// # Changes
	// ----
	if (g_FASTWROTE_STATE == true)
	{
		if (strcmpi(lpMsg->chatmsg, g_WROTE_TEXT.c_str()) == 0)
		{
			GDWroteEventWinnerSend(aIndex);
		}
	}
	if (g_CONFUSEEVENT_STATE == true)
	{
		if (strcmpi(lpMsg->chatmsg, g_CONFUSE_WROTE_TEXT.c_str()) == 0)
		{
			GDConfuseEventWinnerSend(aIndex);
		}
	}
	if (g_LOTTERYEVENT_STATE == true)
	{
		static char exertemp[5];
		// ----
		memset(exertemp, 0, sizeof(exertemp));
		// ----
		memcpy(exertemp, lpMsg->chatmsg, sizeof(exertemp));
		// ----
		for (int i = 0; i != strlen(exertemp); ++i)
		{
			char c = exertemp[i];

			if ((c >= '0' && c <= '9'))
			{
			}
			else
			{
				goto CONTINUE;
			}
		}
		// ----
		int num = atoi(exertemp);
		// ----
		GDLotteryEventSenderSend(aIndex, num);
	}
	// ----
	// # Review later
	// ----
	if (g_GMLOGINID == aIndex)
	{
		char answer[2];
		memcpy(answer, lpMsg->chatmsg, sizeof(answer));
		if ((gObj[aIndex].Authority == 32))
		{
			if (answer[0] == '/' && answer[1] == 'y' || answer[0] == '/' && answer[1] == 'Y')
			{
				g_Msg.NoticeAll(" %s Has Connected To The Server", gObj[aIndex].Name);
				g_Msg.Msg(aIndex, "@You Chose to Write about your LOGIN");
				bReturn = true;

			}
			else if (answer[0] == '/' && answer[1] == 'n' || answer[0] == '/' && answer[1] == 'N')
			{
				g_Msg.Msg(aIndex, "@You Chose NOT to Write about your LOGIN");
				bReturn = true;
			}
			else
			{
				g_Msg.Msg(aIndex, "@You Chose NOT to Write about your LOGIN");
			}

		}
		g_GMLOGINID = 0;

	}

	if (g_EXERCISESYSTEM_STATE == true)
	{
		static char exertemp[5];
		// ----
		memset(exertemp, 0, sizeof(exertemp));
		// ----
		memcpy(exertemp, lpMsg->chatmsg, sizeof(exertemp));
		// ----
		for (int i = 0; i != strlen(exertemp); ++i)
		{
			char c = exertemp[i];

			if ((c >= '0' && c <= '9'))
			{
			}
			else
			{
				goto CONTINUE;
			}
		}
		// ----
		int num = atoi(exertemp);
		// ----
		MSG_EXERCISE_GETANSWER pMsg = { 0 };
		// ----
		HeadSet2(&pMsg.Head, sizeof(pMsg), HEAD_EXERCISESYSTEM, EXERCISESYSTEM_SUBHEAD_GETANSWER);
		// ----
		pMsg.Answer = num;
		// ----
		memcpy(pMsg.szNick, gObj[aIndex].Name, sizeof(pMsg.szNick));
		memcpy(pMsg.szAccountID, gObj[aIndex].AccountID, sizeof(pMsg.szAccountID));
		// ----
		g_DataServer.DataSend((UCHAR *)& pMsg, sizeof(pMsg));
	}
	else if (VoteIsRunning == true)
	{
		if (isdigit(lpMsg->chatmsg[0]) > 0)
		{
			if (atoi(lpMsg->chatmsg) <= 9)
			{
				CChatVote::sendVote(gObj[aIndex].Name, gObj[aIndex].AccountID, atoi(lpMsg->chatmsg));
				// ----
				return false;
			}
		}
	}
	// ----
CONTINUE:
	// ----
	if (lpMsg->chatmsg[0] != '/')
	{
		if (g_LOTTERYEVENT_STATE == false)
		{
			if (strcmpi(nObject->LastChat, lpMsg->chatmsg) == 0)
			{
				g_Msg.Msg(aIndex, 1, DO_NOT_REPEAT_WORDS);
				// ----
				return true;
			}
			else
			{
				memcpy(nObject->LastChat, lpMsg->chatmsg, sizeof(lpMsg->chatmsg));
			}
		}
		// need to 
	}
	// ----
	if (lpMsg->chatmsg[0] == '@')
	{
		if (lpMsg->chatmsg[1] == '>')			/* @> */
		{
			if (strstr(lpMsg->chatmsg, "'") != NULL)
			{
				g_Msg.Msg(aIndex, NOT_ALLOW_SPEICAL_CHARACTERS_INGUILD_MSG);
				// ----
				g_HackLog.Output(HACK_LOG_SPEICAL_CHARACTER_INGUILD_MSG, gObj[aIndex].AccountID, gObj[aIndex].Name);
				// ----
				bReturn = true;
			}
		}
		else if (lpMsg->chatmsg[1] == '@')		/* @@ */
		{
			if (strlen(gObj[aIndex].GuildName) > 0)
			{
				GDSendGuildMsg(gObj[aIndex].Name, gObj[aIndex].GuildName, &lpMsg->chatmsg[1]);
				// ----
				bReturn = true;
			}
			else
			{
				g_Msg.Msg(aIndex, SHTRODEL_ONLY_WHILE_YOU_IN_GUILD1);
				g_Msg.Msg(aIndex, SHTRODEL_ONLY_WHILE_YOU_IN_GUILD2);
			}
		}
		else									/* @ */
		{
			if (strlen(gObj[aIndex].GuildName) > 0)
			{
				GDSendGuildMsg(gObj[aIndex].Name, gObj[aIndex].GuildName, &lpMsg->chatmsg[1]);
				// ----
				bReturn = true;
			}
			else
			{
				g_Msg.Msg(aIndex, SHTRODEL_ONLY_WHILE_YOU_IN_GUILD1);
				g_Msg.Msg(aIndex, SHTRODEL_ONLY_WHILE_YOU_IN_GUILD2);
			}
		}
	}

	if (lpMsg->chatmsg[0] == '$')
	{
		switch (nObject->IsMarried)
		{
		case -1:
		{
			g_Msg.Msg(aIndex, "@[$ Marry] Error 2 (Try to reconnect)");
			g_Msg.Msg(aIndex, "@[$ Marry] שגיאה מספר 2 - נסה להתחבר מחדש");
		}
		break;
		case 0:
		{
			g_Msg.Msg(aIndex, "@[$ Marry] You Are Not Married");
			g_Msg.Msg(aIndex, "@[$ Marry] אתה לא נשוי");
		}
		break;
		case 1:
		{

			int tIndex = gObjGetIndexByName(nObject->MarryName);
			if ((tIndex >= OBJECT_START_INDEX) && (tIndex <= OBJECT_MAX_INDEX))
			{
				_NEW_OBJECT * tObject = &g_GS.nObject[NINDEX(tIndex)];
				if (tObject->isMarryChat == true)
				{
					g_Msg.PM(tIndex, "[$]%s:%s", gObj[aIndex].Name, &lpMsg->chatmsg[1]);
					g_Msg.PM(aIndex, "[$]%s:%s", gObj[aIndex].Name, &lpMsg->chatmsg[1]);
				}
				else
				{
					g_Msg.Msg(aIndex, "@[$ Marry] Your Partner Closed Marry Chat");
					g_Msg.Msg(aIndex, "@[$ Marry] השותף שלך סגר את אפשרות זו");
				}
			}
			else
			{
				g_Msg.Msg(aIndex, "@[$ Marry] Your Partner is not connect");
				g_Msg.Msg(aIndex, "@[$ Marry] השותף שלך לא מחובר");
			}

		}
		break;
		}
		bReturn = true;
	}
	// ----
	// # Mefakhih CMDS
	// ----
	if (strstr(gObj[aIndex].GuildName, "Mefakhim") != NULL)
	{
		if (strcmpi(Command, "/adv") == 0)
		{
			GDAdvMsgMsg(gObj[aIndex].Name);
		}
	}
	// ----
	// # GMS LOG
	// ----
	if (gObjIsGameMaster(aIndex) == true)
	{
		g_GmsLog.Output(CHAT_LOG_MESSAGE_FORMAT, g_Config.nServerCode, gObj[aIndex].AccountID, gObj[aIndex].Name, lpMsg->chatmsg);
		// ----
		if (lpMsg->chatmsg[0] == '!')
		{
			if (lpMsg->chatmsg[1] == '!')
			{
				ChatMsgCMDGM(aIndex, lpMsg->chatmsg);
			}
			else
			{
				g_GmsLog.Output(GMS_LOG_NOTICE, gObj[aIndex].AccountID, gObj[aIndex].Name, lpMsg->chatmsg);
				// ---
				if (gObj[aIndex].AuthorityCode == 63)
				{
					g_Msg.NoticeAll(FORMAT_MSG_FOR_GM_NOTICE, gObj[aIndex].Name, &lpMsg->chatmsg[1]);
				}
				else
				{
					// leo : what the hell is going here ? 
					std::string s1 = gObj[aIndex].Name;

					if (s1.back() == 'I') {
						s1.pop_back();
						if (s1.back() == 'S')
							g_Msg.NoticeAll(FORMAT_MSG_FOR_GM_NOTICE, gObj[aIndex].Name, &lpMsg->chatmsg[1]);
						else
							g_Msg.NoticeAll(FORMAT_MSG_FOR_HIDEN_GM_NOTICE, &lpMsg->chatmsg[1]);
					} else if (s1.back() == 'M') {
						s1.pop_back();
						if (s1.back() == 'G')
							g_Msg.NoticeAll(FORMAT_MSG_FOR_GM_NOTICE, gObj[aIndex].Name, &lpMsg->chatmsg[1]);
						else
							g_Msg.NoticeAll(FORMAT_MSG_FOR_HIDEN_GM_NOTICE, &lpMsg->chatmsg[1]);
					} else {
						g_Msg.NoticeAll(FORMAT_MSG_FOR_HIDEN_GM_NOTICE, &lpMsg->chatmsg[1]);
					}
				}
				// ----
			}
			return true;
		}
		// ----
		if (strcmpi(Command, "/vote") == 0)
		{
			if (gObj[aIndex].Authority == 32) {
				if (strcmpi(lpMsg->chatmsg, "/vote") == 0)
				{
					g_Msg.Msg(aIndex, "Set answer	: /vote <number> <answer>");
					g_Msg.Msg(aIndex, "Set question	: /vote set <question>");
					g_Msg.Msg(aIndex, "Start vote	: /vote start <seconds>");
					// ----
					return true;
				}
				// ----
				CChatVote::Core(aIndex, lpMsg->chatmsg);
				// ----
				return true;
			}
			else
			{
				g_Msg.Msg(aIndex, "@[Vote] You Don't Have Access for this Command.");
				g_Msg.Msg(aIndex, "@[Vote] You Have Been Reported.");

				g_GmsLog.Output(GMS_LOG_Access, gObj[aIndex].AccountID, gObj[aIndex].Name, "Vote");
			}
			return true;
		}
		else if (strcmpi(Command, "/dumpset") == 0)
		{
			char btTemp[1024 * 3] = { 0 };
			// ----
			sprintf(btTemp, "DUMPSET : ");
			// ----
			for (int i = 0; i != sizeof(gObj[aIndex].CharSet); ++i)
			{
				if (gObj[aIndex].CharSet[i] > 9)
				{
					sprintf(btTemp, "%s %X", btTemp, gObj[aIndex].CharSet[i]);
				}
				else
				{
					sprintf(btTemp, "%s 0%X", btTemp, gObj[aIndex].CharSet[i]);
				}
			}
			// ----
			g_HackLog.Output(btTemp);
			// ----
			g_Msg.Msg(aIndex, "dump saved in hacklog thanks");
		}
		else if (strcmpi(Command, "/warp") == 0)
		{
			g_GmsLog.Output(GMS_LOG_WARP, gObj[aIndex].AccountID, gObj[aIndex].Name);
			// ----
			return true;
		}
		else if (strcmpi(Command, "/printbots") == 0)
		{
			g_BotSystem.printDemo(aIndex);
		}
		else if (strcmpi(Command, "/addbots") == 0)
		{
			g_BotSystem.addBots();
		}
		else if (strcmpi(Command, "/delbots") == 0)
		{
			g_BotSystem.delBots();
		}
		else if (strcmpi(Command, "/reloadbots") == 0)
		{
			g_BotSystem.delBots();
			g_BotSystem.loadBots();
			g_BotSystem.addBots();
		}
		else if (strcmpi(Command, "/reddragon") == 0)
		{
			ChatRedDragonCMD(aIndex);
		}
		else if (strcmpi(Command, "/advmsg") == 0)
		{
			if (strcmpi(lpMsg->chatmsg, "/advmsg") == 0)
			{
				g_Msg.Msg(aIndex, "Syntax : /advmsg <Msg>");
				// ----
				return true;
			}
			if (strcmpi(gObj[aIndex].Name, "Eliad") == 0)
			{
				char tmp[100] = { 0 };

				g_Chatfunc.GetLongParam(lpMsg->chatmsg, tmp);
				struct PMSG_CHATDATA_NUMBER
				{
					PBMSG_HEAD h;
					BYTE NumberH;	// 3
					BYTE NumberL;	// 4
					char chatmsg[60];	// 5
				};

				PMSG_CHATDATA_NUMBER pMsg = { 0 };

				pMsg.h.set((LPBYTE)& pMsg, 0x01, sizeof(pMsg));

				strcpy(pMsg.chatmsg, tmp);

				for (int i = 0; i != OBJECT_SIZE; ++i)
				{
					if ((gObj[i].Type == OBJ_MONSTER) || (gObj[i].Type == OBJ_NPC))
					{
						pMsg.NumberH = SET_NUMBERH(i);
						pMsg.NumberL = SET_NUMBERL(i);

						g_GS.MsgSendV2((DWORD)& gObj[i], (LPBYTE)& pMsg, sizeof(pMsg));
						g_GS.DataSend(i, (UCHAR *)& pMsg, sizeof(pMsg));

					}
				}
			}
			else
			{
				g_Msg.Msg(aIndex, "@Only for Eliad MMOG cuz drink vodka :D");
			}

		}
		else if (strcmpi(Command, "/skin") == 0)
		{
#ifdef GS_99_60T
			{
				if (strcmpi(lpMsg->chatmsg, "/skin") == 0)
				{
					g_Msg.Msg(aIndex, "Syntax : /skin <number>");
					return true;
				}
				else
				{
					char ID_char[200] = { 0 };
					// ----
					g_Chatfunc.GetParam(1, lpMsg->chatmsg, ID_char);
					// ----
					int ID = atoi(ID_char);
					if (strlen(ID_char) == 0)
					{
						g_Msg.Msg(aIndex, "Syntax : /skin <number>");
						return true;
					}
					if (ID < -1 || ID == 68 || ID == 239 || ID > 310)
					{
						g_Msg.Msg(aIndex, "@[Skin]ID of Monster is wrong. (-1~310)");
						return true;
					}
					// ----
					// g_GmsLog.Output("[%s][%s][Skin]: Tried to change himself to [%d]", gObj[aIndex].AccountID, gObj[aIndex].Name, ID);
					// ----
					//GDSkinCheck(gObj[aIndex].Name, gObj[aIndex].AccountID, "", ID);
					GDSkinCheck(gObj[aIndex].Name, gObj[aIndex].AccountID, gObj[aIndex].Name, ID);
				}
			}
#endif
		}

		else if (strcmpi(Command, "/skino") == 0)
		{
#ifdef GS_99_60T
			{
				if (strcmpi(lpMsg->chatmsg, "/skino") == 0)
				{
					g_Msg.Msg(aIndex, "Syntax : /skino <name> <number>");
					return true;
				}
				else
				{
					char Name[100] = { 0 };
					char ID_char[100] = { 0 };
					// ----
					g_Chatfunc.GetParam(1, lpMsg->chatmsg, Name);
					g_Chatfunc.GetParam(2, lpMsg->chatmsg, ID_char);
					// ----
					int ID = atoi(ID_char);
					if (strlen(Name)>10)
					{
						g_Msg.Msg(aIndex, "@Name of player is wrong");
						return true;
					}
					if (strlen(ID_char) == 0)
					{
						g_Msg.Msg(aIndex, "Syntax : /skino <name> <number>");
						return true;
					}
					if (ID < -1 || ID == 68 || ID == 239 || ID > 310)
					{
						g_Msg.Msg(aIndex, "@[Skin] ID of Monster is wrong");
						return true;
					}
					// ----
					g_GmsLog.Output("[%s][%s][Skino] : Tried to change [%s] to [%d]", gObj[aIndex].AccountID, gObj[aIndex].Name, Name, ID);
					// ----
					GDSkinCheck(gObj[aIndex].Name, gObj[aIndex].AccountID, Name, ID);
				}
			}
#endif
		}
		else if (strcmpi(lpMsg->chatmsg, "/invi on") == 0)
		{
			std::string s1(gObj[aIndex].Name);
			if (s1.back() == 'I')
			{
				s1.pop_back();
				if (s1.back() == 'S')
				{
					g_GmsLog.Output(GMS_LOG_INVISIBLE, gObj[aIndex].AccountID, gObj[aIndex].Name, "SI", "ON");
					g_Msg.Msg(aIndex, "@[Invisible] Invisible on");
					GDInvisibleChange(gObj[aIndex].Name, gObj[aIndex].AccountID, true);
					CCore::gObjCloseSetEx(aIndex, 1);
				}
			}
			else if (s1.back() == 'M')
			{
				s1.pop_back();
				if (s1.back() == 'G')
				{
					g_GmsLog.Output(GMS_LOG_INVISIBLE, gObj[aIndex].AccountID, gObj[aIndex].Name, "GM", "ON");
					g_Msg.Msg(aIndex, "@[Invisible] Invisible on");
					GDInvisibleChange(gObj[aIndex].Name, gObj[aIndex].AccountID, true);
					CCore::gObjCloseSetEx(aIndex, 1);
				}
			}
		}
		else if (strcmpi(lpMsg->chatmsg, "/visi on") == 0)
		{
			std::string s1(gObj[aIndex].Name);
			if (s1.back() == 'I')
			{
				s1.pop_back();
				if (s1.back() == 'S')
				{
					g_GmsLog.Output(GMS_LOG_INVISIBLE, gObj[aIndex].AccountID, gObj[aIndex].Name, "SI", "OFF");
					g_Msg.Msg(aIndex, "@[Invisible] Invisible off");
					GDInvisibleChange(gObj[aIndex].Name, gObj[aIndex].AccountID, false);
					CCore::gObjCloseSetEx(aIndex, 1);
				}
			}
			else if (s1.back() == 'M')
			{
				s1.pop_back();
				if (s1.back() == 'G')
				{
					g_GmsLog.Output(GMS_LOG_INVISIBLE, gObj[aIndex].AccountID, gObj[aIndex].Name, "GM", "OFF");
					g_Msg.Msg(aIndex, "@[Invisible] Invisible off");
					GDInvisibleChange(gObj[aIndex].Name, gObj[aIndex].AccountID, false);
					CCore::gObjCloseSetEx(aIndex, 1);
				}
			}
		}
		else if (strcmpi(lpMsg->chatmsg, "/crewInfo on") == 0)
		{
			g_Msg.Msg(aIndex, "@[CrewInfo] Crew Info on");
			GDInvisibleCrewChange(gObj[aIndex].Name, gObj[aIndex].AccountID, true);
		}
		else if (strcmpi(lpMsg->chatmsg, "/crewInfo off") == 0)
		{
			g_Msg.Msg(aIndex, "@[CrewInfo] Crew Info off");
			GDInvisibleCrewChange(gObj[aIndex].Name, gObj[aIndex].AccountID, false);
		}
		else if (strcmpi(lpMsg->chatmsg, "/shopgm off") == 0)
		{
			g_Msg.Msg(aIndex, 1, "[ShopGM] You Can't sell now + all in Shop");
			nObject->isAllowToSellPlusAll = false;
		}
		else if (strcmpi(lpMsg->chatmsg, "/shopgm on") == 0)
		{
			g_Msg.Msg(aIndex, 1, "[ShopGM] You Can sell now + all in Shop");
			nObject->isAllowToSellPlusAll = true;
		}
		else if (strcmpi(Command, "/banchar") == 0)
		{
			if (strcmpi(lpMsg->chatmsg, "/banchar") == 0)
			{
				g_Msg.Msg(aIndex, "Syntax : /banchar <nick> <0/1>");
			}
			else
			{
				char Status[100] = { 0 };
				char Name[100] = { 0 };
				char ID_char[10] = { 0 };
				int ID = 0;
				// ----
				g_Chatfunc.GetParam(1, lpMsg->chatmsg, Name);
				g_Chatfunc.GetParam(2, lpMsg->chatmsg, Status);
				g_Chatfunc.GetParam(3, lpMsg->chatmsg, ID_char);
				// ----
				ID = atoi(ID_char);
				// ----
				if (strlen(Name) > 10)
				{
					g_Msg.Msg(aIndex, "Maxmium size Name OR AccountID is 10");
				}
				else if ((strlen(Status) > 0) && strlen(Name) > 0 && strlen(ID_char)> 0)
				{
					if (atoi(Status) == 1 || atoi(Status) == 0)
					{
						GDSetBanOnChar(gObj[aIndex].Name, Name, (bool)(atoi(Status)), ID);
					}
					else
					{
						g_Msg.Msg(aIndex, "Syntax : /banchar <nick> <0/1> <id>");
					}
				}
				else
				{
					g_Msg.Msg(aIndex, "Syntax : /banchar <nick> <0/1> <id>");
				}
			}
		}
		else if (strcmpi(Command, "/banacc") == 0)
		{
			if (strcmpi(lpMsg->chatmsg, "/banacc") == 0)
			{
				g_Msg.Msg(aIndex, "Syntax : /banacc <acc> <0/1> <id>");
			}
			else
			{
				char Status[100] = { 0 };
				char AccountID[100] = { 0 };
				char ID_char[10] = { 0 };
				int ID = 0;
				// ----
				g_Chatfunc.GetParam(1, lpMsg->chatmsg, AccountID);
				g_Chatfunc.GetParam(2, lpMsg->chatmsg, Status);
				g_Chatfunc.GetParam(3, lpMsg->chatmsg, ID_char);
				// ----
				ID = atoi(ID_char);
				// ----
				if (strlen(AccountID) > 10) {
					g_Msg.Msg(aIndex, "Maxmium size Name OR AccountID is 10");
				} 
				else if ((strlen(Status) > 0) && strlen(AccountID) > 0 && strlen(ID_char)> 0)  
				{
					if (atoi(Status) == 1 || atoi(Status) == 0) {
						GDSetBanOnAcc(gObj[aIndex].Name, AccountID, (bool)(atoi(Status)), ID);
					}
					else {
						g_Msg.Msg(aIndex, "Syntax : /banacc <acc> <0/1> <id>");
					}
				} else {
					g_Msg.Msg(aIndex, "Syntax : /banacc <acc> <0/1> <id>");
				}
			}
		}
		else if (strcmpi(Command, "/jump") == 0)
		{
			if (strcmpi(lpMsg->chatmsg, "/jump") == 0)
			{
				g_Msg.Msg(aIndex, "Syntax : /jump <Nick> <1/2/3>");
				// ----
				return true;
			}
			else
			{
				char ID[100] = { 0 };
				char Name[100] = { 0 };
				// ----
				g_Chatfunc.GetParam(2, lpMsg->chatmsg, ID);
				g_Chatfunc.GetParam(1, lpMsg->chatmsg, Name);
				// ----
				if (strlen(Name) > 10)
				{
					g_Msg.Msg(aIndex, "Maxmium size Name OR AccountID is 10");
				}
				else if ((strlen(ID) > 0) && strlen(Name) > 0)
				{
					ObjectJumpTeleport(aIndex, Name, atoi(ID), 0, true);
				}
				else
				{
					g_Msg.Msg(aIndex, "Syntax : /jump <Nick> <1/2/3>");
				}
			}
			// ----
			return true;
		}
		else if (strcmpi(lpMsg->chatmsg, "/LogHack On") == 0)
		{
			GDLogHack(aIndex, gObj[aIndex].Name);
			bReturn = true;
		}
		else if (strcmpi(lpMsg->chatmsg, "/LogHack Off") == 0)
		{
			nObject->isLogHackAllow = false;
			// ----
			g_Msg.Msg(aIndex, 1, "[LogHack] is off");
			// ----
			bReturn = true;
		}
		else if (strcmpi(lpMsg->chatmsg, "/kill On") == 0)
		{
			if (gObj[aIndex].Authority == 32)
			{
				nObject->isImmortal = false;
				// ----
				g_Msg.Msg(aIndex, 1, "[Immortal] is off");
				// ----
			}
			bReturn = true;
		}
		else if (strcmpi(lpMsg->chatmsg, "/kill Off") == 0)
		{
			if (gObj[aIndex].Authority == 32)
			{
				nObject->isImmortal = true;
				// ----
				g_Msg.Msg(aIndex, 1, "[Immortal] is on");
				// ----
			}
			bReturn = true;
		}
		// ----
		// Roye add - Event Command
		// ----
		else if (strcmpi(lpMsg->chatmsg, "/event") == 0)
		{
			GDEventCommandGMS(aIndex);
			bReturn = true;
		}
		// ----
		if (strcmpi(Command, DISCONNET_COMMAND_TO_HANDLE_ONLY) == 0)
		{
			if (nObject->canUseDisconnect == true)
			{
				// roye access
				//CheckMoveAndDisAcc(aIndex, "Disconnec", 0, true);
				// roye end
				g_Chatfunc.GetParam(1, lpMsg->chatmsg, myTemp);
				if (gObjIsGameMaster(aIndex) == true)
				{
					int tIndex = gObjGetIndexByName(myTemp);
					if (gObjIsConnected(tIndex) == true)
					{
						closesocket(gObj[tIndex].m_socket);
					}
				}
				// ----
				g_GmsLog.Output(GMS_LOG_DISCONNECT, gObj[aIndex].AccountID, gObj[aIndex].Name, myTemp);
			}
			else
			{
				CheckMoveAndDisAcc(aIndex, (char *)"Disconnec", 0, true);
				// ----
				bReturn = true;
			}
		}
		// ----
		if (strcmpi(Command, MOVE_COMMAND_TO_HANDLE_ONLY) == 0)
		{
			char AccountID[11] = { 0 };
			char Map[4] = { 0 };
			char X[4] = { 0 };
			char Y[4] = { 0 };
			// ----
			g_Chatfunc.GetParam(1, lpMsg->chatmsg, AccountID);
			g_Chatfunc.GetParam(2, lpMsg->chatmsg, Map);
			g_Chatfunc.GetParam(3, lpMsg->chatmsg, X);
			g_Chatfunc.GetParam(4, lpMsg->chatmsg, Y);
			// ----
			if ((strlen(AccountID) > 2) && (strlen(Map) > 0))
			{
				if (nObject->canUseMove == true)
				{
					// roye access
					CheckMoveAndDisAcc(aIndex, (char *)"Move", 0, true);
					//roye end
					g_GmsLog.Output(GMS_LOG_MOVE, gObj[aIndex].AccountID, gObj[aIndex].Name, AccountID, Map, X, Y);
				}
				else
				{
					CheckMoveAndDisAcc(aIndex, (char *)"Move", 0, true);
					// ----
					bReturn = true;
				}
			}
			else
			{
				bReturn = ObjectTeleportByMapName(aIndex, AccountID);
			}
		}
		// ----
		if (strcmpi(Command, TRACK_COMMAND_TO_HANDLE_ONLY) == 0)
		{
			g_Chatfunc.GetParam(1, lpMsg->chatmsg, myTemp);
			// ----
			g_GmsLog.Output(GMS_TRACK_LOG, gObj[aIndex].AccountID, gObj[aIndex].Name, myTemp);
		}
	}
	// Not GMS
	else
	{
		// ----
		// # Loren vally bug fix
		// ----
#ifdef GS_99_60T
		{
			if (strcmpi(lpMsg->chatmsg, "/move lorenvalley") == 0)
			{
				//g_Msg.Notice(aIndex, "m_PK_Level %d",  gObj[aIndex].m_PK_Level);

				if (gObj[aIndex].Level > 200)
				{
					if (gObj[aIndex].m_PK_Level != 6)
					{
						if (gObj[aIndex].Money >= 20000)
						{
							gObj[aIndex].Money = gObj[aIndex].Money - 20000;

							//g_Msg.Notice(aIndex, "1 Money %d",  gObj[aIndex].Money);

							g_GS.GCMoneySend(aIndex, gObj[aIndex].Money);

							//g_Msg.Notice(aIndex, "12 Money %d",  gObj[aIndex].Money);

							g_GS.gObjTeleport(aIndex, 0, 223, 13);
							// ----
							return true;
						}
						else
						{
							//g_Msg.Msg(aIndex, "@Leak of money");
						}
					}
					else
					{
						//g_Msg.Msg(aIndex, "@Pk Level");
					}
				}
				else
				{
					//g_Msg.Msg(aIndex, "@Leak of level - need LV 200");
				}
			}
		}
#else
		{
			if (strcmpi(lpMsg->chatmsg, "/move lorenvalley") == 0)
			{
				//g_Msg.Notice(aIndex, "m_PK_Level %d",  gObj[aIndex].m_PK_Level);

				if (gObj[aIndex].Level > 200)
				{
					if (gObj[aIndex].m_PK_Level != 6)
					{
						if (gObj[aIndex].Money >= 20000)
						{
							gObj[aIndex].Money = gObj[aIndex].Money - 20000;

							//g_Msg.Notice(aIndex, "1 Money %d",  gObj[aIndex].Money);

							g_GS.GCMoneySend(aIndex, gObj[aIndex].Money); //--> falls
																		  // ----
							ObjectMoveInLorenvaly(aIndex);
							//g_Msg.Notice(aIndex, "12 Money %d",  gObj[aIndex].Money);

							//g_GS.gObjTeleport(aIndex, 0 , 223, 13);
							// ----
							return true;
						}
						else
						{
							//g_Msg.Msg(aIndex, "@Leak of money");
						}
					}
					else
					{
						//g_Msg.Msg(aIndex, "@Pk Level");
					}
				}
				else
				{
					//g_Msg.Msg(aIndex, "@Leak of level - need LV 200");
				}
			}
		}
#endif
	}
	// ----
	if (g_Config.isGSCastle == false)
	{
		if (strcmpi(Command, BAN_COMMAND) == 0)
		{
			ChatGMBanAdd(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/joinguild") == 0)
		{
			if (strcmpi(lpMsg->chatmsg, "/joinguild") == 0)
			{
				g_Msg.Msg(aIndex, "Syntax : /joinguild <nameAssist>");
				return true;
			}
			else
			{
				char Name[100] = { 0 };
				// ----
				g_Chatfunc.GetParam(1, lpMsg->chatmsg, Name);
				// ----
				if (strlen(Name)>10)
				{
					g_Msg.Msg(aIndex, "@Name of player is wrong");
					return true;
				}
				int assistIndex = gObjGetIndexByName(Name);
				// ----
				if (assistIndex < OBJECT_START_INDEX || assistIndex > OBJECT_MAX_INDEX)
				{
					g_Msg.Msg(aIndex, "@Name of Assist is wrong");
					return true;
				}
				if (strcmpi(gObj[assistIndex].GuildName, "") == 0)
				{
					g_Msg.Msg(aIndex, "@The name is not in guild");
					return true;
				}
				if (strcmpi(gObj[aIndex].GuildName, "") != 0)
				{
					g_Msg.Msg(aIndex, "@You are already in guild!");
					return true;
				}
				if (gObj[assistIndex].GuildStatus != 64)
				{
					g_Msg.Msg(aIndex, "@The name is not Guild Assist");
					return true;
				}
				if (gObj[assistIndex].MapNumber != gObj[aIndex].MapNumber)
				{
					g_Msg.Msg(aIndex, "@You are to far from the Assist");
					return true;
				}
				if (gObj[assistIndex].X - gObj[aIndex].X > 2 || gObj[assistIndex].X - gObj[aIndex].X < -2)
				{
					g_Msg.Msg(aIndex, "@You are to far from the Assist");
					return true;
				}
				if (gObj[assistIndex].Y - gObj[aIndex].Y > 2 || gObj[assistIndex].Y - gObj[aIndex].Y < -2)
				{
					g_Msg.Msg(aIndex, "@You are to far from the Assist");
					return true;
				}
				GDGuildJoinRequestByAssist(gObj[assistIndex].Name, gObj[aIndex].Name);
			}
		}
		else if (strcmpi(Command, "/setmember") == 0)
		{
			if (strcmpi(lpMsg->chatmsg, "/setmember") == 0)
			{
				g_Msg.Msg(aIndex, "Syntax : /setmember <name>");
				return true;
			}
			else
			{
				char Name[100] = { 0 };
				// ----
				g_Chatfunc.GetParam(1, lpMsg->chatmsg, Name);
				// ----
				if (strlen(Name)>10)
				{
					g_Msg.Msg(aIndex, "@Name of player is wrong");
					return true;
				}
				if (strcmpi(gObj[aIndex].GuildName, "") == 0)
				{
					g_Msg.Msg(aIndex, "@You are not in Guild");
					return true;
				}
				if (gObj[aIndex].GuildStatus != 64)
				{
					g_Msg.Msg(aIndex, "@You are not Guild Assist");
					return true;
				}
				GDAssistCheckRequest(gObj[aIndex].Name, Name, gObj[aIndex].GuildName, 0);
			}
		}
		else if (strcmpi(Command, "/setbattle") == 0)
		{
			if (strcmpi(lpMsg->chatmsg, "/setbattle") == 0)
			{
				g_Msg.Msg(aIndex, "Syntax : /setbattle <name>");
				return true;
			}
			else
			{
				char Name[100] = { 0 };
				// ----
				g_Chatfunc.GetParam(1, lpMsg->chatmsg, Name);
				// ----
				if (strlen(Name)>10)
				{
					g_Msg.Msg(aIndex, "@Name of player is wrong");
					return true;
				}
				if (strcmpi(gObj[aIndex].GuildName, "") == 0)
				{
					g_Msg.Msg(aIndex, "@You are not in Guild");
					return true;
				}
				if (gObj[aIndex].GuildStatus != 64)
				{
					g_Msg.Msg(aIndex, "@You are not Guild Assist");
					return true;
				}
				GDAssistCheckRequest(gObj[aIndex].Name, Name, gObj[aIndex].GuildName, 32);
			}
		}
		else if (strcmpi(Command, "/kickmemb") == 0)
		{
			if (strcmpi(lpMsg->chatmsg, "/kickmemb") == 0)
			{
				g_Msg.Msg(aIndex, "Syntax : /kickmemb <name>");
				return true;
			}
			else
			{
				char Name[100] = { 0 };
				// ----
				g_Chatfunc.GetParam(1, lpMsg->chatmsg, Name);
				// ----
				if (strlen(Name)>10)
				{
					g_Msg.Msg(aIndex, "@Name of player is wrong");
					return true;
				}
				if (strcmpi(gObj[aIndex].GuildName, "") == 0)
				{
					g_Msg.Msg(aIndex, "@You are not in Guild");
					return true;
				}
				if (gObj[aIndex].GuildStatus != 64)
				{
					g_Msg.Msg(aIndex, "@You are not Guild Assist");
					return true;
				}
				GDKickCheckRequest(gObj[aIndex].Name, Name, gObj[aIndex].GuildName);
			}
		}
		else if (strcmpi(lpMsg->chatmsg, "/setassist off") == 0)
		{
			if (strcmpi(gObj[aIndex].GuildName, "") == 0)
			{
				g_Msg.Msg(aIndex, "@You are not in Guild");
				return true;
			}
			if (gObj[aIndex].GuildStatus != 128)
			{
				g_Msg.Msg(aIndex, "@You are not Guild Manager");
				return true;
			}
			GDSetAssistCheckRequest(gObj[aIndex].Name, gObj[aIndex].GuildName, 0);
		}
		else if (strcmpi(lpMsg->chatmsg, "/setassist on") == 0)
		{
			if (strcmpi(gObj[aIndex].GuildName, "") == 0)
			{
				g_Msg.Msg(aIndex, "@You are not in Guild");
				return true;
			}
			if (gObj[aIndex].GuildStatus != 128)
			{
				g_Msg.Msg(aIndex, "@You are not Guild Manager");
				return true;
			}
			GDSetAssistCheckRequest(gObj[aIndex].Name, gObj[aIndex].GuildName, 1);
		}
		else if (strcmpi(Command, "/banusers") == 0)
		{
			ChatGMBanUsersAdd(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, GO_COMMAND) == 0)
		{
			ChatGOCmd(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/Gooff") == 0)
		{
			_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];
			// ----
			nObject->isGoAllow = false;
			// ----
			g_Msg.Msg(aIndex, 1, "[Go] (/Gooff) Off");
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/fixlevelbug") == 0) {
			ChatFixLevelBugCMD(aIndex);
		}
		else if (strcmpi(Command, "/marry") == 0)
		{
			ChatMarryStartCommand(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/marryon") == 0)
		{
			_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];
			// ----
			nObject->isMarryAllow = true;
			// ----
			g_Msg.Msg(aIndex, 1, "[Marry] (/MarryOn) On");
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/marryoff") == 0)
		{
			_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];
			// ----
			nObject->isMarryAllow = false;
			// ----
			g_Msg.Msg(aIndex, 1, "[Marry] (/MarryOff) Off");
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/marryoff") == 0)
		{
			nObject->isMarryAllow = false;
			// ----
			g_Msg.Msg(aIndex, 1, "[Marry] (/MarryOff) Off");
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/marrychat on") == 0)
		{
			nObject->isMarryChat = true;
			// ----
			g_Msg.Msg(aIndex, 1, "[MarryChat] (/MarryChatOn) On");
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/marrychat off") == 0)
		{
			nObject->isMarryChat = false;
			// ----
			g_Msg.Msg(aIndex, 1, "[MarryChat] (/MarryChatOff) Off");
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/tmarry") == 0)
		{
			ChatTrackMarry(aIndex, lpMsg->chatmsg);
			bReturn = true;
		}
		else if (strcmpi(Command, "/divorce") == 0)
		{
			g_MarrySystem.DivorceMarrige(aIndex);
			bReturn = true;
		}
		else if (strcmpi(Command, "no") == 0 && g_MarrySystem.MARRIAGE_STARTED && strcmpi(g_MarrySystem.M_NAME2, gObj[aIndex].Name) == 0)
		{
			g_MarrySystem.NpcUse = 0;
			//bReturn = true;
		}
		else if (strcmpi(Command, "לא") == 0 && g_MarrySystem.MARRIAGE_STARTED && strcmpi(g_MarrySystem.M_NAME2, gObj[aIndex].Name) == 0)
		{
			g_MarrySystem.NpcUse = 0;
			//bReturn = true;
		}
		else if (strcmpi(Command, "כן") == 0 && g_MarrySystem.MARRIAGE_STARTED == true && strcmpi(g_MarrySystem.M_NAME2, gObj[aIndex].Name) == 0)
		{
			g_MarrySystem.NpcUse = 1;
			//bReturn = true;
		}
		else if (strcmpi(Command, "yes") == 0 && g_MarrySystem.MARRIAGE_STARTED == true && strcmpi(g_MarrySystem.M_NAME2, gObj[aIndex].Name) == 0)
		{
			g_MarrySystem.NpcUse = 1;
			//bReturn = true;
		}
		else if (strcmpi(Command, "/kundun") == 0)
		{
			ChatKandumCMD(aIndex);
			// ----
			bReturn = true;
		}
		// Off Trade
		else if (strcmpi(Command, "/OffTrade") == 0)
		{
			ChatOffTradeCMD(aIndex);
			// ----
			bReturn = true;
		}
		// Report Player
		else if (strcmpi(Command, "/report") == 0)
		{
			ChatReportCommand(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		//roye add
		else if (strcmpi(Command, "/come") == 0)
		{
			ChatComeCmd(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		//roye end
		else if (strcmpi(Command, "/Post") == 0)
		{
			ChatPostCMD(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/vip") == 0)
		{
			if (strcmpi(lpMsg->chatmsg, "/vip") == 0)
			{
				g_Msg.Msg(aIndex, "@[VIP]Syntax: /vip <Number>");
				g_Msg.Msg(aIndex, "@[Bronze: 1 Price: %d][Silver: 2 Price: %d]", g_Config.bVIPPrice, g_Config.sVIPPrice);
				g_Msg.Msg(aIndex, "@[Gold: 3 Price: %d][Platinum: 4 Price: %d]", g_Config.gVIPPrice, g_Config.pVIPPrice);
				g_Msg.Msg(aIndex, "@[VIP]Example: /vip 1");
				return true;
			}
			char szCode[100] = { 0 };
			UINT VipCodeLvl = 0;
			// ----
			g_Chatfunc.GetParam(1, lpMsg->chatmsg, szCode);
			// ----
			VipCodeLvl = atoi(szCode);
			// ----
			switch (VipCodeLvl)
			{
			case 1:
				g_VIPSystem.VIPBuyRequest(aIndex, 1);
				return true;
			case 2:
				g_VIPSystem.VIPBuyRequest(aIndex, 2);
				return true;
			case 3:
				g_VIPSystem.VIPBuyRequest(aIndex, 3);
				return true;
			case 4:
				g_VIPSystem.VIPBuyRequest(aIndex, 4);
				return true;
			default:
				g_Msg.Msg(aIndex, "לא הייתה אפשרות לאתר את רמת הויאיפי הרצויה");
				return true;
			}
		}
		else if (strcmpi(Command, "/Msg") == 0)
		{
			ChatMsgCMD(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		// ----
		else if ((g_Config.isKeepCommand == true) && (strcmpi(Command, "/keep") == 0))
		{
			if (lpMsg->chatmsg[5] == 0x30)
			{
				bReturn = true;
			}
		}
		else if (strcmpi(lpMsg->chatmsg, "/shopguard on") == 0)
		{
			nObject->isAgreeShopping = false;
			g_Msg.Msg(aIndex, 1, "כעת לא תוכל לשים חפצים +הכל בחנות");
			g_Msg.Msg(aIndex, 1, "צוות המשחק ממליץ לא לשים חפצים בחנות");
			g_Msg.Msg(aIndex, 1, "שעלולים להימחק עקב בעיות");
		}
		else if (strcmpi(lpMsg->chatmsg, "/shopguard off") == 0)
		{
			nObject->isAgreeShopping = true;
			g_Msg.Msg(aIndex, 1, "כעת תוכל לשים חפצים +הכל בחנות");
			g_Msg.Msg(aIndex, 1, "צוות המשחק ממליץ לא לשים חפצים בחנות");
			g_Msg.Msg(aIndex, 1, "שעלולים להימחק עקב בעיות");
		}
		else if (strcmpi(Command, "/guildwar") == 0)
		{
			bReturn = true;
			// ----
			g_Msg.Msg(aIndex, 1, "לא ניתן להשתמש בפקודה הזאת");
		}
	}
	// for CS ONLY
	// ----
	else
	{
		if (strcmpi(lpMsg->chatmsg, "/Log On") == 0)
		{
			nObject->isLogKillerAllow = true;
			// ----
			g_Msg.Msg(aIndex, 1, "[Log] is on");
			// ----
			bReturn = true;
		}
		else if (strcmpi(lpMsg->chatmsg, "/Log Off") == 0)
		{
			nObject->isLogKillerAllow = false;
			// ----
			g_Msg.Msg(aIndex, 1, "[Log] is off");
			// ----
			bReturn = true;
		}

		else if (strcmpi(Command, "/Msg") == 0)
		{
			ChatMsgCMD(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/Post") == 0)
		{
			ChatPostCMD(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/Duel") == 0)
		{
			bReturn = true;
			// ----
			g_Msg.Msg(aIndex, 1, "לא ניתן להשתמש בפקודה זאת בסייג");
		}
		else if (strcmpi(Command, "/War") == 0)
		{
			bReturn = true;
			// ----
			g_Msg.Msg(aIndex, 1, "לא ניתן להשתמש בפקודה זאת בסייג");
		}
		else if (strcmpi(Command, "/guildwar") == 0)
		{
			bReturn = true;
			// ----
			g_Msg.Msg(aIndex, 1, "לא ניתן להשתמש בפקודה זאת בסייג");
		}
		else if (strcmpi(Command, "/Ban") == 0)
		{
			ChatGMBanAdd(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
		else if (strcmpi(Command, "/banusers") == 0)
		{
			ChatGMBanUsersAdd(aIndex, lpMsg->chatmsg);
			// ----
			bReturn = true;
		}
	}
	// for whole gameserver's
	// ----
	if (strcmpi(lpMsg->chatmsg, "/uptime") == 0)
	{
		ObjectOutputUptime(aIndex);
		// ----
		bReturn = true;
	}
	else if (strcmpi(lpMsg->chatmsg, "/crew") == 0)
	{
		GDCrewMsgReq(aIndex);
		// ----
		bReturn = true;
	}
	else if (strcmpi(lpMsg->chatmsg, "/re off") == 0)
	{
		gObj[aIndex].m_Option = 0;
		// ----
		g_Msg.Msg(aIndex, 1, "You are now rejecting all requests from other players.");
		// ----
		bReturn = true;
	}
	else if (strcmpi(lpMsg->chatmsg, "/re on") == 0)
	{
		gObj[aIndex].m_Option |= 1;
		// ----
		g_Msg.Msg(aIndex, 1, "You are now accepting all requests from other players.");
		// ----
		bReturn = true;
	}
	else if (strcmpi(Command, "/help") == 0)
	{
		ChatHelpCMD(aIndex);
		// ----
		bReturn = true;
	}
	else if (strcmpi(Command, "/time") == 0)
	{
		static SYSTEMTIME strSystime;
		// ----
		if (strSystime.wSecond < 10)
			g_Msg.Msg(aIndex, "Mu Israel Time[%d:%d:0%d]", strSystime.wHour, strSystime.wMinute, strSystime.wSecond);
		else
			g_Msg.Msg(aIndex, "Mu Israel Time[%d:%d:%d]", strSystime.wHour, strSystime.wMinute, strSystime.wSecond);
	}
	else if (strcmpi(lpMsg->chatmsg, "/radio on") == 0)
	{
		g_Msg.Msg(aIndex, 1, "[Radio] is on");
		// ----
		g_Msg.SendAllGMS("[%s] radio is on", gObj[aIndex].Name);
		// ----
		bReturn = true;
	}
	else if (strcmpi(lpMsg->chatmsg, "/radio off") == 0)
	{
		g_Msg.Msg(aIndex, 1, "[Radio] is off");
		// ----
		g_Msg.SendAllGMS("[%s] radio is off", gObj[aIndex].Name);
		// ----
		bReturn = true;
	}
	else if (strcmpi(Command, "/infooff") == 0)
	{
		_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];
		// ----
		nObject->isInfoAllow = false;
		// ----
		g_Msg.Msg(aIndex, 1, INFO_IS_OFF_MSG);
		// ----
		GDSendInfoStateMsg(gObj[aIndex].Name, true);
		// ----
		bReturn = true;
	}
	else if (strcmpi(Command, "/infoon") == 0)
	{
		_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];
		// ----
		nObject->isInfoAllow = true;
		// ----
		g_Msg.Msg(aIndex, 1, INFO_IS_ON_MSG);
		// ----
		GDSendInfoStateMsg(gObj[aIndex].Name, false);
		// ----
		bReturn = true;
	} 
	#ifdef GS_99_60T
	else if (strcmpi(Command, "/buy") == 0)
	{
		if (nObject->nBuyItemCode == 0) {
			g_Msg.Msg(aIndex, "@[Buy] הקוד שבחרת שגוי");
			return true;
		}

		if (strcmpi(lpMsg->chatmsg, "/buy") == 0)  {
			g_Msg.Msg(aIndex, "@[Buy]Syntax : /buy <code>");
			g_Msg.Msg(aIndex, "@[Buy] יש להקיש קוד מוצר על ידי לחיצה על חפץ");
			return true;
		}

		char szCode[100] = { 0 };
		UINT nCode = 0;
		// ----
		g_Chatfunc.GetParam(1, lpMsg->chatmsg, szCode);
		// ----
		nCode = atoi(szCode);
		// ----
		if (nCode != nObject->nBuyItemCode) {
			g_Msg.Msg(aIndex, "@[Buy] הקוד שבחרת שגוי");
			g_Msg.Msg(aIndex, "@[Buy] יש ללחוץ על אחד החפצים כדי לקבל קוד קניה");
			g_Msg.Msg(aIndex, "@[Buy]/buy 13478278 :לדוגמא");
			return true;
		}
		// ----

		GDShopBuyItemRequest(gObj[aIndex].AccountID, gObj[aIndex].Name, nObject->buyShop->ShopId
			, nObject->bBuyProductPos, nObject->buyShop->Prices[nObject->bBuyProductPos]);

		nObject->bBuyProductPos = 0;
		nObject->nBuyItemCode = 0;
	
		bReturn = true;
	}
	#endif
	else if (strcmpi(Command, "/shop") == 0)
	{
		#ifdef GS_99_60T
		{
			if (strcmpi(lpMsg->chatmsg, "/shop") == 0)
			{
				g_Msg.Msg(aIndex, "@[Shop]Syntax : /shop <id> (range: 1 ~ %d)", CShop::bShopsCount);
				g_Msg.Msg(aIndex, "@[Shop]יש להקיש מספר חנות לאחר הפקודה");
				g_Msg.Msg(aIndex, "@[Shop]/shop 1 :לדוגמא");
				return true;
			}
			else
			{
				char szShopId[100] = { 0 };
				int iShopId = 0;
				// ----
				g_Chatfunc.GetParam(1, lpMsg->chatmsg, szShopId);
				// ----
				iShopId = atoi(szShopId);
				// ----
				if (iShopId > 0 && iShopId <= CShop::bShopsCount) {
					g_Msg.Msg(aIndex, "@[Shop]ברוך הבא לחנות מספר %d", iShopId);
					CShop::Shops[iShopId - 1].ShopRequest(aIndex);
				}
				else {
					g_Msg.Msg(aIndex, "@[Shop]Syntax : /shop <id> (range: 1 ~ %d)", CShop::bShopsCount);
					g_Msg.Msg(aIndex, "@[Shop]יש להקיש מספר חנות לאחר הפקודה");
					g_Msg.Msg(aIndex, "@[Shop]/shop 1 :לדוגמא");
					bReturn = true;
				}
			}
		}
		#else
		{
			g_Msg.Msg(aIndex, "/shop command is only in normal maps");
		}
		#endif
	}
	else if (strcmpi(Command, "/info") == 0)
	{
		ChatInfoCMD(aIndex, lpMsg->chatmsg);
		// ----
		bReturn = true;
	}
	else if (strcmpi(Command, "/moveme") == 0)
	{
		ChatMoveMeCmd(aIndex, lpMsg->chatmsg);
		// ----
		bReturn = true;
	}
	// roye add
	else if (strcmpi(Command, "/unban") == 0)
	{
		ChatUnBanCmd(aIndex, lpMsg->chatmsg);
		// ----
		bReturn = true;
	}
	else if (strcmpi(Command, "/gmsg") == 0)
	{
		CheckGreenMSG(aIndex, lpMsg->chatmsg, 0, false);
		bReturn = true;
	}

	else if (strcmpi(Command, "/msgst") == 0)
	{
		ChatMSGChange(aIndex, lpMsg->chatmsg);
		bReturn = true;
	}
	// ----
	return bReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ChatFixLevelBugCMD(int aIndex)
{
	LPOBJ lpObj = (LPOBJ)OBJECT_POINTER(aIndex);

	if (lpObj->Level == 400)
	{
		g_Msg.PM(aIndex, "[Level Bug] You are level 400 - Reset");
		g_Msg.PM(aIndex, "[Level Bug] אתה רמה 400, תעשה ריסט");
		return;
	}
	if (lpObj->Level < 360)
	{
		g_Msg.PM(aIndex, "[Level Bug] Only available from level 360");
		g_Msg.PM(aIndex, "[Level Bug] התיקון אפשרי רק מרמה 360");	
		return;
	}

}