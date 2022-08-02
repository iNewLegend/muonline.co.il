#include "StdAfx.h"
#include "Object.h"
#include "TGameServer.h"
#include "TMessages.h"
#include "DSXProtocol.h"
#include "TSetup.h"
#include "TDataServerSocket.h"
#include "TCore.h"
#include "TLogToFile.h"
#include "User.h"
#include "TConfig.h"
#include "TPacket.h"
#include "VIPSystem.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # Made By Leo123[BoR] -> GS 99.60T -> Only for MuOnline.co.il
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool g_EXERCISESYSTEM_STATE			= false;
bool g_RUNEVENT_STATE				= false;
bool g_FASTWROTE_STATE				= false;
bool g_LOTTERYEVENT_STATE			= false;
bool g_CONFUSEEVENT_STATE			= false;
bool MSG_STATUS						= true; // leo: bad name can do logical conflicts
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UINT		g_LOTTREYEVENT_ROLEED   = 0;
_LOACTION	g_RUNEVENT_CORD			= {0};
std::string g_WROTE_TEXT;
std::string g_CONFUSE_WROTE_TEXT;
std::string g_CONFUSE_WROTE_TEXT_WRONG;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectSetZero(int aIndex)
{
	_NEW_OBJECT * nObject = & g_GS.nObject[FIXINDEX];
	// ----
	nObject->canUseMove = false;
	nObject->canUseDisconnect = false;
	nObject->isGoAllow = true;
	nObject->isInfoAllow = true;
	nObject->isLogKillerAllow = true;
	nObject->isMarryChat = true;
	nObject->isImmortal = true;
	nObject->isLogHackAllow = false;
	nObject->isAllowToSellPlusAll = false;
	nObject->isAgreeShopping = false;
	nObject->dwPostTick = GetTickCount();
	nObject->dwHelpTick = GetTickCount() - 240000;
	nObject->dwMarry = 0;
	nObject->Resets = 0;
	nObject->VipLevel = 0;
	// ----
	nObject->dwDL_Horse_Tick = 0;
	// ----
	nObject->dwFrames = 0;
	nObject->dwCurrentTime = 0;
	nObject->dwLastUpdateTime = 0;
	nObject->dwElapsedTime = 0;
	nObject->szFPS[0] = '\0';
	nObject->FPS = 0;
	// ----
	// # Marry System Defalt Values
	// ----
	nObject->MarryType = -1;
	nObject->IsMarried = -1;
	nObject->isMarryAllow = false;
	memset(nObject->MarryName, 0x0, sizeof(nObject->MarryName));
	// ----
	// # Coin Shop
	// ----
	#ifdef GS_99_60T
	nObject->nBuyItemCode = 0;
	nObject->bBuyProductPos = 0x00;
	#endif

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectVIPCheck(LPVOID lParam)
{
	if(g_Config.isServerVip == true)
	{
		for(USHORT i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
		{
			if(gObj[i].Type == OBJ_USER)
			{
				if(gObj[i].Connected >= PLAYER_CONNECTED)
				{
					GDExtraInfo(i, gObj[i].AccountID);
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectBanAdd(int gmIndex, char * szNick , int Days , int ReasonID)
{
	if(gmIndex == 0) {
		return;
	}
	// ----
	if(Days < -1) {
		return;
	}
	// ----
	int targetIndex = gObjGetIndexByName(szNick);
	// ----
	if(gObjIsGameMaster(targetIndex) == true)
	{
		g_Msg.Msg(gmIndex, "[Ban] הפקודה לא מתאפשרת על מנהל משחק");
		g_Msg.SendAllGMS("%s Want ban other GM :%s", gObj[gmIndex].Name , szNick);
		// ----
		return;
	}
	// ----
	g_Msg.Notice(targetIndex, "%s קבלת באן על ידי", gObj[gmIndex].Name);
	// ----
	if(Days == -1)
	{
		g_Msg.Notice(targetIndex, "המנהל בחר לתת לך באן לתמיד - עוד מידע בפורום");
	}
	else
	{
		g_Msg.Notice(targetIndex, "You're banned, remove more %d days.", Days);
	}
	// ----
	Sleep(100);
	// ----
	g_GS.CloseClient(targetIndex);
	// ----
	g_Msg.SendAllGMS("[Ban] Player %s Get Banned to %d Days by %s", szNick, Days, gObj[gmIndex].Name);
	// ----
	GDSBanSet(gObj[gmIndex].Name, szNick, Days, ReasonID, 0);
	// ----
	if(gObjIsConnected(targetIndex) != true)
	{
		g_Msg.Msg(gmIndex, "[Ban] השחקן לא נמצא מחובר");
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectBanUsersAdd(int gmIndex, char * szNick , int Days , int ReasonID)
{
	int targetIndex = -1;
	// ----
	if(gmIndex == 0)
	{
		return;
	}
	// ----
	if(Days < -1)
	{
		return;
	}
	// ----
	targetIndex = gObjGetIndexByName(szNick);
	// ----
	if(gObjIsGameMaster(targetIndex) == true)
	{
		g_Msg.Msg(gmIndex, "[banusers] הפקודה לא מתאפשרת על מנהל משחק");
		g_Msg.SendAllGMS("%s Want ban other GM :%s", gObj[gmIndex].Name , szNick);
		// ----
		return;
	}
	// ----
	g_Msg.Notice(targetIndex, "%s קבלת באן על ידי", gObj[gmIndex].Name);
	// ----
	if(Days == -1)
	{
		g_Msg.Notice(targetIndex, "המנהל בחר לתת לך באן לתמיד - עוד מידע בפורום");
	}
	else
	{
		g_Msg.Notice(targetIndex, "You're banned, remove more %d days.", Days);
	}
	// ----
	Sleep(100);
	// ----
	g_GS.CloseClient(targetIndex);
	// ----
	g_Msg.SendAllGMS("[Banusers] Player %s Get Banned to %d Days by %s", szNick, Days, gObj[gmIndex].Name);
	// ----
	GDSBanSet(gObj[gmIndex].Name, szNick, Days, ReasonID, 1);
	// ----
	if(gObjIsConnected(targetIndex) != true)
	{
		g_Msg.Msg(gmIndex, "[banusers] השחקן לא נמצא מחובר");
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectVIPDisconnectThread(LPVOID lpParam)
{
	Sleep(100);
	g_Msg.Msg((int) lpParam, 0, "לשרת זה ניתן להתחבר במידה ויש לך גישת ויאיפי");
	Sleep(100);
	g_Msg.Msg((int) lpParam, 0, "להסבר על רכישת מנוי ויאיפי יש לפנות לפורום");
	Sleep(100);
	g_Msg.Msg((int) lpParam, 0, "www.forum.muonline.co.il");
	Sleep(100);
	g_Msg.Msg((int) lpParam, 0, "אתה מנותק מהשרת");
	Sleep(100);
	g_Msg.Msg((int) lpParam, 0, "No VIP access to the server");
	// ----
	Sleep(1200);
	// ----
	g_GS.CloseClient((int) lpParam);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectExtraInfoResult(int aIndex, MSG_R_EXTRAINFO * lpMsg)
{

	if(gObjIsGameMaster(aIndex) == true)
	{
		lpMsg->nDays = 5000;
	}
	// ----
	if(g_Config.isServerVip == true)
	{
		if(lpMsg->nDays == -1) /* SQL Conn fail */
		{
			g_Msg.Notice(aIndex, "עקב בעיה טכנית אין אפשרות להתחבר לשרת");
			g_Msg.Notice(aIndex, "נסה שוב בעוד מספר דקות");
			// -----
			g_GS.CloseClient(aIndex);
			// ----
			return;
		}
		// ----
		if(lpMsg->nDays <= 0) /* user has no vip */
		{
			if (gObjCheckUserResets(aIndex, 1, lpMsg->nResets) == true)
			{
				g_Msg.PM(aIndex, "[VIP] מנוי ויאפי חינם עד 1 ריסט");
				g_Msg.PM(aIndex, "[VIP] FREE Access to Vip Servers until 1 Reset");
			}
			else
			{
				_beginthread(ObjectVIPDisconnectThread, 4, (LPVOID) aIndex);
				// ----
				return;
			}
		}

		if (lpMsg->nVipLevel < g_Config.VipServerLevel && lpMsg->nDays != 0)
		{
			if (gObjCheckUserResets(aIndex, 1, lpMsg->nResets) == false)
			{
				_beginthread(ObjectVIPDisconnectThread, 4, (LPVOID)aIndex);
				// ----
				return;
			}
		}

	}
	// ----
	if(lpMsg->nDays > 0)
	{ 
		g_Msg.PM(aIndex, "[VIP] נותרו עוד %d ימים לדרגת הויאיפי מסוג %s שלך.", lpMsg->nDays, g_VIPSystem.RequestVipLevelName(lpMsg->nVipLevel, 1));
		g_Msg.PM(aIndex, "[VIP] You have more %d day(s) for VIP %s Level", lpMsg->nDays, g_VIPSystem.RequestVipLevelName(lpMsg->nVipLevel, 2));
	}
	else if (gObjCheckUserResets(aIndex, 1, lpMsg->nResets) == true && g_Config.isServerVip == false)
	{
		g_Msg.PM(aIndex, "[VIP] מנוי מסוג %s בחינם עד ריסט הראשון שלך.", g_VIPSystem.RequestVipLevelName(lpMsg->nVipLevel, 1));
		g_Msg.PM(aIndex, "[VIP] FREE Access to Vip Type %s Until 1 Reset", g_VIPSystem.RequestVipLevelName(lpMsg->nVipLevel, 2));
	}
	// ----
#ifdef GS_99_60T
	/*if(aIndex >= OBJECT_START_INDEX && aIndex <= OBJECT_MAX_INDEX)
	{
		if(gObj[aIndex].Connected >= PLAYER_PLAYING)
		{
			if(strcmp("Mefakhim", lpMsg->szGuild) == 0)
			{
				CPacket extraInfo;
				// ----
				extraInfo.writeByte(0xF1);
				extraInfo.writeByte(255);
				extraInfo.writeString(gObj[aIndex].Name);
				// ----
				//  GI Ballon
				gObj[aIndex].m_ViewSkillState	|= 0x1040000;
				extraInfo.writeByte(0x02);
				// ----
				TAG_HEADER head(0xC1, extraInfo.getLength());
				// ----
				extraInfo.writeHeader(& head);
				// ----
				std::string test = extraInfo.getBuffer();
				g_GS.DataSend(aIndex, (UCHAR *) test.c_str(), test.length());
			}
			else if((! gObjIsGameMaster(aIndex)) && (lpMsg->nDays > 0)) // if not gm but an vip on i will give u vip not gi
			{
				gObj[aIndex].m_ViewSkillState	|= 0x1020000; // VIP
				// ----
				CPacket extraInfo;
				// ----
				extraInfo.writeByte(0xF1);
				extraInfo.writeByte(255);
				extraInfo.writeString(gObj[aIndex].Name);
				extraInfo.writeByte(0x01);
				// ----
				TAG_HEADER head(0xC1, extraInfo.getLength());
				// ----
				extraInfo.writeHeader(& head);
				// ----
				std::string stringPacket = extraInfo.getBuffer();
				// ----
				g_GS.DataSend(aIndex, (UCHAR *) stringPacket.c_str(), stringPacket.length());
			}
		}
	}*/
#endif

	_NEW_OBJECT * nObject = & g_GS.nObject[FIXINDEX];
	// ----

	if(nObject != NULL)
	{
		try
		{
			nObject->VipLevel = lpMsg->nVipLevel;
			nObject->Resets = lpMsg->nResets;
			// ----
			if(lpMsg->nDays > 0)
			{
				nObject->isVip = true;
			}
			else
			{
				nObject->isVip = false;
			}
		}
		catch(...)
		{
		}
	}
	// ----
	if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
	{	
		_NEW_OBJECT * nObject = & g_GS.nObject[NINDEX(aIndex)];
		// ----
		nObject->IsMarried = lpMsg->IsMarried;
		nObject->MarryType = 0;
		memcpy(nObject->MarryName,		lpMsg->MarryName,		sizeof(nObject->MarryName));
		// ----
		if(nObject->IsMarried == 1)
		{
			g_Msg.Msg(aIndex,"@[Marry] You are Married to %s", nObject->MarryName);
			int tIndex = gObjGetIndexByName(nObject->MarryName);
			if((tIndex >= OBJECT_START_INDEX) && (tIndex <= OBJECT_MAX_INDEX))
			{
				g_Msg.Msg(aIndex, "@[Marry] Your Partner is Online");
				g_Msg.Msg(tIndex, "@[Marry] Your Partner Has Loged In");
			}
			else
			{
				g_Msg.Msg(aIndex, "@[Marry] Your Partner is Offline");
			}

		}
		else if (nObject->IsMarried == 0)
			g_Msg.Msg(aIndex,"@[Marry] You are not Married");
		else
			g_Msg.Msg(aIndex,"@[Marry] Unknown Error (2) Report Admin");
		// ----
		// # Access System
		// ----
		nObject->canUseDisconnect	= lpMsg->CanUseDisconnect;
		nObject->canUseMove			= lpMsg->CanUseMove;

		/*if (gObjIsGameMaster(aIndex) != true)
		{
			#ifdef GS_99_60T
			g_Msg.PMAll("%s, Entered Game!", gObj[aIndex].Name);
			#endif
		}*/
	}

	/*#ifdef GS_99_60T
	if(gObjIsGameMaster(aIndex)) 
	{
		CPacket extraInfo;
		// ----
		extraInfo.writeByte(0xF1);
		extraInfo.writeByte(255);
		extraInfo.writeString(gObj[aIndex].Name);
		// ----
		extraInfo.writeByte(0x00); // gm
		// ----
		TAG_HEADER head(0xC1, extraInfo.getLength());
		// ----
		extraInfo.writeHeader(& head);
		// ----
		std::string test = extraInfo.getBuffer();
		g_GS.DataSend(aIndex, (UCHAR *) test.c_str(), test.length());
	}
	#endif*/
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObejctGoState(int Type, int aIndex, int Target, int Credits, bool State)
{
	if(g_DataServer.getStatus() == false)
	{
		g_Msg.Msg(aIndex, "@[GO] DataServer error , please try again later");
	}
	else
	{
		switch(Type)
		{
			case 0: /* Send ASK FOR RESULT */
			{
				GDGoRequest(aIndex, Target, Credits, gObj[aIndex].AccountID);
			}
			break;

			case 1: /* RECV RESULT */
			{
				if(State == true)
				{
					if(Credits > 0)
					{
						ObjectDOGo(aIndex, Target);
					}
				}
				else
				{
					if(Credits == 0)
					{
						g_Msg.Msg(aIndex, "@[GO]  מצטערים ,אין לך מספיק קרדיטים");
					}
					else
					{
						g_Msg.Msg(aIndex, "@[GO]  עקב בעיה טכנית אין באפשרותינו לספק שרות זה כעת");
					}
				}
			}
			break;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectDOGo(int aIndex, int tIndex)
{
	BYTE Map	= gObj[tIndex].MapNumber;
	BYTE X		= gObj[tIndex].X;
	BYTE Y		= gObj[tIndex].Y;
	// ----
	g_Msg.Msg(tIndex, "@[GO] משתגר לכיוון שלך, %s ", gObj[aIndex].Name);
	g_Msg.Msg(aIndex, "@[GO] אתה משתגר כעת");
	// ----
	g_GS.gObjTeleport(aIndex, Map , X, Y);
	// ----
	gObjCastRegen(aIndex, 0xFF);
	gObjCastRegen(tIndex, 0xFF);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectUnBanAdd(int aIndex, char * name, int bRes)
{
	int targetIndex = -1;
	// ----
	if(aIndex == 0)
	{
		return;
	}
	// ----

	targetIndex = gObjGetIndexByName(name);
	// ----
	if(gObjIsGameMaster(targetIndex) == true)
	{
		g_Msg.Msg(aIndex, "[UnBan] הפקודה לא מתאפשרת על מנהל משחק");
		g_Msg.SendAllGMS("%s Want Unban other GM :%s", gObj[aIndex].Name , name);
		// ----
		return;
	}
	// ----
	
	
	// ----

	GDSUnBanSet(gObj[aIndex].Name, name, bRes);
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectComeTeleport(int srcIndex, char * TargetName, int type, bool access)
{	
	
	switch (type)
	{
	case 0:
		{
			GDCheckAccess_Come(srcIndex, TargetName, (char *)"Come");

		}
		break;
	case 1:
		{
			if (access){
				char szName[11] = {0};
				// ----
				memcpy(szName, TargetName, 10);
				// ----
				int targetIndex = gObjGetIndexByName(szName);
				// ----
				if(targetIndex != -1)
				{
				ObjectDOCome(srcIndex, targetIndex);

				g_Msg.Msg(srcIndex, "@[COME] שיגרת את %s", TargetName);
				g_Msg.Msg(targetIndex, "@%s, מנהל משחק שיגר אותך", gObj[srcIndex].Name);
				// ----
				g_GmsLog.Output("[%s][%s][COME] : %s got to [%d] [%d] [%d]", gObj[srcIndex].AccountID, gObj[srcIndex].Name, gObj[targetIndex].Name,gObj[srcIndex].MapNumber,gObj[srcIndex].X,gObj[srcIndex].Y);
				// ----
		
				}
			}
			else
			{
				g_Msg.Msg(srcIndex, "@[Come] You Don't Have Access for this Command.");
				g_Msg.Msg(srcIndex, "@[Come] You Have Been Reported.");

				g_GmsLog.Output(GMS_LOG_Access, gObj[srcIndex].AccountID, gObj[srcIndex].Name, "Come");
			}

		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectDOCome(int aIndex, int tIndex)
{
	BYTE Map	= gObj[aIndex].MapNumber;
	BYTE X		= gObj[aIndex].X;
	BYTE Y		= gObj[aIndex].Y;
	// ----

	// ----

	g_GS.gObjTeleport(tIndex, Map , X, Y);
	// ----
	gObjCastRegen(aIndex, 0xFF);
	gObjCastRegen(tIndex, 0xFF);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectMSGChangeStatus (char * Name, int type, int status)
{
	int aIndex = gObjGetIndexByName(Name);
	switch (type)
	{
		case 0:
		{
			g_Msg.Msg(aIndex, "@[%s] You Don't Have Access for this Command.", "ChangeMsg");
			g_Msg.Msg(aIndex, "@[%s] You Have Been Reported.", "ChangeMsg");

			g_GmsLog.Output(GMS_LOG_Access, gObj[aIndex].AccountID, gObj[aIndex].Name, "ChangeMsg");

		}
		break;
	
		case 1:
		{
			if (status == 1)
			{
				MSG_STATUS = false;
				
			}
			else if (status == 0)
			{
				MSG_STATUS = true;
			}
		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectMSGChangeStatusSys (int status)
{
	if (status == 1)
		{
			MSG_STATUS = false;
		}
		else if (status == 0)
		{
			MSG_STATUS = true;
		}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectMoveMeTeleport (int aIndex, int map, int x, int y)
{
	if (map>=0 && map<=10 && map!=5 || map==30)
	{
		g_GmsLog.Output(GMS_LOG_MOVEME, gObj[aIndex].AccountID, gObj[aIndex].Name, map, x, y);
		g_GS.gObjTeleport(aIndex, map , x, y);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectBanAccessDenied (char * Nick, char* Command)
{
	int aIndex = gObjGetIndexByName(Nick);
	g_GmsLog.Output(GMS_LOG_Access, gObj[aIndex].AccountID, gObj[aIndex].Name, Command);
	g_Msg.SendAllGMS("[%s] The Player %s Don't HAVE the",Command, gObj[aIndex].Name);
	g_Msg.SendAllGMS("Permision to Give Un/Bans",Command, gObj[aIndex].Name);
	g_Msg.Msg(aIndex, "@[%s] You Don't HAVE the Permision to Give Bans/UnBans", Command);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectEventCommandAccess (char * Nick, int status)
{
	int aIndex = gObjGetIndexByName(Nick);
	if (status == 1)
	{
		g_GmsLog.Output(GMS_LOG_Access, gObj[aIndex].AccountID, gObj[aIndex].Name, "Event");
		g_Msg.SendAllGMS("[%s] The Player %s Don't HAVE the","Event", gObj[aIndex].Name);
		g_Msg.SendAllGMS("Permision to play Events");
		g_Msg.Msg(aIndex, "@[%s] You Don't HAVE the Permision to play Events", "Event");
	}
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObejctKandumState(int Type, int aIndex, int Credits, int Code)
{
	if(g_DataServer.getStatus() == false)
	{
		g_Msg.Msg(aIndex, "@[Kundun] DataServer error , please try again later");
	}
	else
	{
		switch(Type)
		{
			case 0: /* Send Kandum Request */
			{
				GDKandumRequest(aIndex, Credits, gObj[aIndex].AccountID);
			}
			break;

			case 1: /* Kandum Request Result */
			{
				switch(Code)
				{
					case -1:
					{
						g_Msg.Msg(aIndex, "@[Kundun] DataServer error please try later");
					}
					break;

					case 0:
					{
						g_Msg.Msg(aIndex, "@[Kundun]  או שאין לך מספיק קרדיטים או שהשתמשת בפקודה כבר היום");
						g_Msg.Msg(aIndex, "@[Kundun]  you're already used Kandum command today or no credits");
					}
					break;

					case 1:
					{
						if(Credits > 0)
						{
							ObjectDoKandum(aIndex);
						}
					}
					break;

					case 2:
					{
						g_Msg.Msg(aIndex, "@[Kundun]  מצטערים ,אין לך מספיק קרדיטים");
						g_Msg.Msg(aIndex, "@[Kundun]  you dont have credits to invite Kandum");
					}
					break;
				}
			}
			break;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectDoKandum(int aIndex)
{
	_POSITION Pos	= ObjectRolePosition();
	// ----
	BYTE Map			= Pos.Map;
	BYTE X				= Pos.x;
	BYTE Y				= Pos.y;
	// ----
	g_Msg.PM(aIndex, "[Kundun](%d) תשמיד את המפלצתתתתת ^_^", Pos.RoledID);
	// ----
	g_GS.gObjTeleport(aIndex, Map, X , Y);
	// ----
	_beginthread(ObjectKandumThread, 4 , (LPVOID) aIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectKandumThread(LPVOID lParam)
{
	g_Msg.PM((int)lParam, "[Kundun] הקונדום יצא בעוד 3");
	Sleep(1000);
	g_Msg.PM((int)lParam, "[Kundun] הקונדום יצא בעוד 2");
	Sleep(1000);
	g_Msg.PM((int)lParam, "[Kundun] הקונדום יצא בעוד 1");
	Sleep(1000);
	g_Msg.PM((int)lParam, "[Kundun] מוכנים?! קדימה לתקוף");
	// ----
	short MobIndex					= g_GS.gObjAddMonster(gObj[(int)lParam].MapNumber);
	// ----
	if(MobIndex >= 0)
	{
		gObj[MobIndex].Y			= gObj[(int)lParam].Y;
		gObj[MobIndex].X			= gObj[(int)lParam].X;
		gObj[MobIndex].MapNumber	= gObj[(int)lParam].MapNumber;
		// ----
		if(g_GS.gObjSetMonster(MobIndex, 275) == true)
		{
			g_Msg.PM((int)lParam, "[Kundun] חשוב לדעת: יש להרוג את המפלצת תוך 2 דקות");
			// ----
			Sleep(120000);
			// ----
			g_GS.gObjDel(MobIndex);
			// ----
			g_Msg.PM((int)lParam, "[Kundun] הזמן נגמר אם לא הצלחת להרוג נסה שוב מחר");
		}
		else
		{
			g_Msg.PM((int)lParam, "[Kundun] שגיאה נה לפנות לאדמין אם תמונת מסך שגיאה מספר 123121");
		}
	}
	else
	{
		g_Msg.PM((int)lParam, "[Kundun] שגיאה נה לפנות לאדמין אם תמונת מסך שגיאה מספר 2111");
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

_POSITION ObjectRolePosition()
{
	_POSITION	Pos		= {0};
	UINT		uRoll	= ObjectGetRandomize(0, 14);
	// ----
	while((uRoll > 15) || (uRoll < 0))
	{
		uRoll = ObjectGetRandomize(0, 14);
	}
	// ----
	switch(uRoll)
	{
		case 0:
		{
			Pos.x	= 86;
			Pos.y	= 88;
			Pos.Map	= 0;
		}
		break;

		case 2:
		{
			Pos.x	= 98;
			Pos.y	= 104;
			Pos.Map	= 0;
		}
		break;

		case 3:
		{
			Pos.x	= 85;
			Pos.y	= 89;
			Pos.Map	= 0;
		}
		break;

		case 4:
		{
			Pos.x	= 93;
			Pos.y	= 20;
			Pos.Map	= 0;
		}
		break;

		case 5:
		{
			Pos.x	= 20;
			Pos.y	= 81;
			Pos.Map	= 0;
		}
		break;

		case 6:
		{
			Pos.x	= 196;
			Pos.y	= 82;
			Pos.Map	= 0;
		}
		break;

		case 7:
		{
			Pos.x	= 18;
			Pos.y	= 86;
			Pos.Map	= 0;
		}
		break;
	
		case 8:
		{
			Pos.x	= 82;
			Pos.y	= 91;
			Pos.Map	= 0;
		}
		break;
		
		case 9:
		{
			Pos.x	= 86;
			Pos.y	= 88;
			Pos.Map	= 0;
		}
		break;
		
		case 10:
		{
			Pos.x	= 98;
			Pos.y	= 104;
			Pos.Map	= 0;
		}
		break;
		
		case 11:
		{
			Pos.x	= 85;
			Pos.y	= 89;
			Pos.Map	= 0;
		}
		break;
		
		case 12:
		{
			Pos.x	= 93;
			Pos.y	= 20;
			Pos.Map	= 0;
		}
		break;
			
		case 13:
		{
			Pos.x	= 20;
			Pos.y	= 81;
			Pos.Map	= 0;
		}
		break;
			
		case 14:
		{
			Pos.x	= 196;
			Pos.y	= 82;
			Pos.Map	= 0;
		}
		break;

		default:
		{
			Pos.x	= 220;
			Pos.y	= 60;
			Pos.Map	= 0;
		}
		break;
	}
	// ----
	Pos.RoledID = uRoll;
	// ----
	return Pos;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectPostAll(char * Name, char * Message)
{
	static char Temp[11];
	// ----
	memset(Temp, 0 , sizeof(Temp));
	memcpy(Temp, Name, 10);
	// ----
	g_Msg.NoticeAll("[MSG,%s] %s", Temp, Message);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectPostAllGM(char * Name, char * Message)
{
	static char Temp[11];
	// ----
	memset(Temp, 0 , sizeof(Temp));
	memcpy(Temp, Name, 10);
	// ----
	g_Msg.NoticeAll("[%s, All] %s", Temp, Message);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectGuildMsgAll(int uServerNumber, char * Name, char * Message, char * GuildName, int G_Status)
{
	char Temp[11] = {0};
	char GuildNamer[10] = {0};
	// ----
	memcpy(GuildNamer, GuildName, 9);
	// ----
	if(strlen(GuildNamer) <= 0)
	{
		return;
	}
	// ----
	for(USHORT i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
	{
		if(gObj[i].Type == OBJ_USER)
		{
			if(gObj[i].Connected == PLAYER_PLAYING)
			{
				if(Message[0] == '@')
				{
					_GUILD_INFO_STRUCT * lpGuild = (_GUILD_INFO_STRUCT*) g_GS.SearchGuild(GuildNamer);
					// ----
					if(lpGuild != NULL && gObj[i].lpGuild != NULL)
					{
						if(strlen(gObj[i].GuildName) > 0)
						{
							if((gObj[i].lpGuild->iGuildUnion > 0) && gObj[i].lpGuild->iGuildUnion == lpGuild->iGuildUnion)
							{
								memcpy(Temp, Name , 10);
								// ----
								switch (G_Status)
								{
									case 0:
									{
										g_Msg.PM(i, "[%d][%s]%s: %s", uServerNumber, "Member",Temp , & Message[1]);
									}
									break;

									case 1:
									{
										g_Msg.PM(i, "[%d][%s]%s: %s", uServerNumber, "Master",Temp , & Message[1]);
									}
									break;

									case 2:
									{
										g_Msg.PM(i, "[%d][%s]%s: %s", uServerNumber, "Assist",Temp , & Message[1]);
									}
									break;

									case 3:
									{
										g_Msg.PM(i, "[%d][%s]%s: %s", uServerNumber, "Battle",Temp , & Message[1]);
									}
									break;
								}
							}
						}
					}
				}
				// ----
				else if(gObj[i].GuildName[0] == GuildNamer[0])
				{
					if(gObj[i].GuildName[1] == GuildNamer[1])
					{
						if(_strcmpi(gObj[i].GuildName, GuildNamer) == 0)
						{
							memcpy(Temp, Name , 10);
							// ----
							switch (G_Status)
							{
									case 0:
									{
										g_Msg.Msg(i, "@[%d][%s]%s: %s", uServerNumber, "Member",Temp , Message);
									}
									break;

									case 1:
									{
										g_Msg.Msg(i, "@[%d][%s]%s: %s", uServerNumber, "Master",Temp , Message);
									}
									break;

									case 2:
									{
										g_Msg.Msg(i, "@[%d][%s]%s: %s", uServerNumber, "Assist",Temp , Message);
									}
									break;

									case 3:
									{
										g_Msg.Msg(i, "@[%d][%s]%s: %s", uServerNumber, "Battle",Temp , Message);
									}
									break;
								}
							//g_Msg.Msg(i, "@[%d]%s: %s", uServerNumber, Temp , Message);
						}
					}
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectLogKill(LPVOID lpParam)
{
	#ifndef GS_99_60T /* IF NOT GS NORMAL */

	char * Log = (char *)lpParam;
	// ----
	g_KillerLog.Output(Log);

	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ObjectTeleportByMapName(int aIndex, char * MapName)
{
	bool bReturn = false;
	// ----
	if(_strcmpi("Arena", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 6, 65, 139);
		// ----
		bReturn = true;
	}
	// ----
	if(_strcmpi("Lorencia", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 0, 148, 126);
		// ----
		bReturn = true;
	}
	// ----
	if(_strcmpi("Noria", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 3, 171, 111);
		// ----
		bReturn = true;
	}
	// ----
	if(_strcmpi("Devias", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 2, 216, 38);
		// ----
		bReturn = true;
	}
	if(_strcmpi("Devias2", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 2, 23, 27);
		// ----
		bReturn = true;
	}
	if(_strcmpi("Devias3", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 2, 226, 231);
		// ----
		bReturn = true;
	}
	if(_strcmpi("Devias4", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 2, 71, 181);
		// ----
		bReturn = true;
	}
	// ----
	if(_strcmpi("Dungeon", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 1, 107, 247);
		// ----
		bReturn = true;
	}
	if(_strcmpi("Dungeon2", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 1, 232, 126);
		// ----
		bReturn = true;
	}
	if(_strcmpi("Dungeon3", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 1, 3, 84);
		// ----
		bReturn = true;
	}
	// ----
	if(_strcmpi("Atlans", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 7, 17, 22);
		// ----
		bReturn = true;
	}
	if(_strcmpi("Atlans2", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 7, 225, 53);
		// ----
		bReturn = true;
	}	
	if(_strcmpi("Atlans3", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 7, 65, 163);
		// ----
		bReturn = true;
	}
	// ----
	if(_strcmpi("LostTower", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 4, 210, 70);
		// ----
		bReturn = true;
	}
	if(_strcmpi("LostTower2", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 4, 243, 237);
		// ----
		bReturn = true;
	}
	if(_strcmpi("LostTower3", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 4, 86, 167);
		// ----
		bReturn = true;
	}
	if(_strcmpi("LostTower4", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 4, 87, 87);
		// ----
		bReturn = true;
	}
	if(_strcmpi("LostTower5", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 4, 130, 53);
		// ----
		bReturn = true;
	}
	if(_strcmpi("LostTower6", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 4, 53, 53);
		// ----
		bReturn = true;
	}
	if(_strcmpi("LostTower7", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 4, 8, 86);
		// ----
		bReturn = true;
	}
	// ----
	if(_strcmpi("Tarkan", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 8, 196, 62);
		// ----
		bReturn = true;
	}
	if(_strcmpi("Tarkan2", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 8, 96, 145);
		// ----
		bReturn = true;
	}
	// ----
	if(_strcmpi("Icarus", MapName) == 0)
	{
		g_GS.gObjTeleport(aIndex, 10, 14, 13);
		// ----
		bReturn = true;
	}
	// ----
	if(_strcmpi("lorenvalley", MapName) == 0)
	{
		#ifndef GS_99_60T 
			g_GS.gObjTeleport(aIndex, 30, 93, 61);
		#else
			g_GS.gObjTeleport(aIndex, 0, 223, 13);
		#endif
		// ----
		bReturn = true;
	}
	// ----
	return bReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectOuputActiveGMS(int targetIndex)
{
	for(int i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
	{
		if(gObjIsConnected(i) == true)
		{
			if(gObjIsGameMaster(i) == true)
			{
				if(gObj[i].Authority == 32)
				{
					g_Msg.Msg(targetIndex, "@[GMS] : %s is online", gObj[i].Name);
				}
			}
		}
	}
	/*
	g_Msg.Msg(targetIndex, "Got Activ TVD");
	GDCrewMsgReq(targetIndex, "Crew");
	g_Msg.Msg(targetIndex, "Got Activ TVD");*/
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectOuputActiveG_Membe(int targetIndex, char * GuildName)
{
	for(int i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
	{
		if(gObjIsConnected(i) == true)
		{
			if(_strcmpi(gObj[i].GuildName, GuildName) == 0)
			{
				g_Msg.Msg(targetIndex, "@[%s] : %s is online", GuildName, gObj[i].Name);
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectJumpTeleport(int srcIndex, char * TargetName, BYTE TeleportID, int check, bool access)
{
	switch (check){

		case 0:
		{
			GDCheckAccess_Jump(srcIndex, TargetName, TeleportID, (char *)"Jump");

		}
		break;

		case 1:
			{
			if (access==true){
			char szName[11] = {0};
			// ----
			memcpy(szName, TargetName, 10);
			// ----
			int targetIndex = gObjGetIndexByName(szName);
			// ----
			if(targetIndex == 0)
			{
				g_Msg.Msg(srcIndex, "@[Jump] Player : %s is not connected", szName);
			}
			else
			{
				g_Msg.Msg(targetIndex, "@%s, מנהל משחק שיגר אותך", gObj[srcIndex].Name);
			// ----
				g_GmsLog.Output("[%s][%s][JUMP] : %s", gObj[srcIndex].AccountID, gObj[srcIndex].Name, gObj[targetIndex].Name);
			// ----
			switch(TeleportID)
			{
				default:
				case 1:
				{
					g_GS.gObjTeleport(srcIndex, 6, 119 , 116);
					g_GS.gObjTeleport(targetIndex, 6, 119 , 116);
				 
				}
				break;

				case 2:
				{
					g_GS.gObjTeleport(srcIndex, 3, 20, 25);
					g_GS.gObjTeleport(targetIndex, 3, 20, 25);
				}
				break;
	
				case 3:
				{
					g_GS.gObjTeleport(srcIndex, 0, 100 , 100);
					g_GS.gObjTeleport(targetIndex, 0, 100 , 100);
			 
				}
				break;

				case 4:
				{
				g_GS.gObjTeleport(srcIndex, 0, 130 , 130);
				g_GS.gObjTeleport(targetIndex, 0, 130 , 130);
			 
				}
				break;

				case 5:
				{
					g_GS.gObjTeleport(srcIndex, 10, 150 , 150);
					g_GS.gObjTeleport(targetIndex, 10, 150 , 150);
			 
				}
				break;
	
				}
			}
		}
			else{
				g_Msg.Msg(srcIndex, "@[Jump] You Don't Have Access for this Command.");
				g_Msg.Msg(srcIndex, "@[Jump] You Have Been Reported.");

				g_GmsLog.Output(GMS_LOG_Access, gObj[srcIndex].AccountID, gObj[srcIndex].Name, "Jump");
			
			}
	  }
	break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectOutputUptime(int aIndex)
{
	g_Msg.Msg(aIndex, "Days(%u)Hours(%u)Minutes(%u)Seconds(%u)", g_Timer.getDays(), g_Timer.getHours() , g_Timer.getMinutes(), g_Timer.getSeconds());
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

double ObjectGetResetsByPoints(int aIndex)
{
	double total_points = (gObj[aIndex].Strength + gObj[aIndex].Dexterity + gObj[aIndex].Vitality + gObj[aIndex].Energy + gObj[aIndex].Leadership + gObj[aIndex].LevelUpPoint);
	// ----
	switch (gObj[aIndex].Class)
	{
		/* DW , DK , ELF */
		case 0:
		case 1:	
		case 2:
		{
			total_points = (total_points / 2175);
		}
		break;

		/* MG , DL */
		case 3:	
		case 4:	
		{
			total_points = (total_points / 2793);
		}
		break;
	}
	// ----
	return total_points;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectCapturePlayerPoint(int aIndex, BYTE Map, BYTE X, BYTE Y)
{
	static std::list<_LOACTION> Loactions;
	static char Temp[1024];
	static char Temp2[1024];
	// ----
	int yairINdex = gObjGetIndexByName((char *)"YairNet");
	// ----
	if(Loactions.size() == 200)
	{
		FILE * Handle = fopen("./locations.txt", "a+");
		// ----
		fseek(Handle, 0, SEEK_END);
		// ----
		for(std::list<_LOACTION>::iterator it = Loactions.begin() ; it != Loactions.end() ; ++it)
		{
			sprintf(Temp, "%d %d %d\n", it->Map, it->X, it->Y);
			fwrite(Temp, 1, strlen(Temp), Handle);
		}

		
		fclose(Handle);

		

		if(yairINdex != 0)
		{
			g_Msg.PM(aIndex, "Item saved");
		}

		Loactions.clear();


	}
	else if(Loactions.empty() == true)
	{
		_LOACTION loca;
		// ----
		loca.Map	= Map;
		loca.X		= X;
		loca.Y		= Y;
		// ----
		Loactions.push_back(loca);
	}
	else
	{
		sprintf(Temp, "%X%X%X", Map, X, Y);
		// ----
		bool isExist = false;
		// ----
		for(std::list<_LOACTION>::iterator it = Loactions.begin() ; it != Loactions.end() ; ++it)
		{
			sprintf(Temp2, "%X%X%X", it->Map, it->X, it->Y);
			// ----
			if(strcmp(Temp2, Temp) == 0)
			{
				isExist = true;
				// ----
				break;
			}
		}
		// ----
		if(isExist == false)
		{
			_LOACTION loca;
			// ----
			loca.Map	= Map;
			loca.X		= X;
			loca.Y		= Y;
			// ----
			Loactions.push_back(loca);
			// ----
			if(Loactions.size() % 2 == 0)
			{
				g_Msg.Msg(yairINdex, "%d %d %d , %d", Map, X, Y , Loactions.size());
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int	ObjectSpawnMonster(int MobID, BYTE Map, BYTE X, BYTE Y)
{
	int iReturn = -1;
	// ----
	short MobIndex					= g_GS.gObjAddMonster(Map);
	// ----
	if(MobIndex >= 0)
	{
		gObj[MobIndex].Y			= Y;
		gObj[MobIndex].X			= X;
		gObj[MobIndex].MapNumber	= Map;
		// ----
		if(g_GS.gObjSetMonster(MobIndex, MobID) == true)
		{
			iReturn = MobIndex;
		}
	}
	// ----
	return iReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

short ObjectAddSearch(SOCKET aSocket, char * ip)
{
	for(int i = OBJECT_START_INDEX; i < OBJECT_MAX_INDEX; ++i)
    {
        if(gObj[i].Connected == PLAYER_EMPTY)
        {
            return i;
        }
    }
    // ----
    return -1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectLogHackChange(int aIndex, int status)
{

	switch (status)
	{
	case 0:
	{

	}
	break;
	case 1:
	{
		_NEW_OBJECT * nObject = &g_GS.nObject[NINDEX(aIndex)];
		nObject->isLogHackAllow = true;
		g_Msg.Msg(aIndex, 1, "[LogHack] is on");
	}
	break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectMoveInLorenvaly (int aIndex)
{
	UINT random = ObjectGetRandomize(0,20);
	// ----
	switch (random)
	{

	case 0:
		{
			g_GS.gObjTeleport(aIndex, 30, 40, 43);
		}
		break;

	case 1:
		{
			g_GS.gObjTeleport(aIndex, 30, 60, 47);
		}
		break;

	case 2:
		{
			g_GS.gObjTeleport(aIndex, 30, 75, 44);
		}
		break;
	
	case 3:
		{
			g_GS.gObjTeleport(aIndex, 30, 87, 52);
		}
		break;
	
	case 4:
		{
			g_GS.gObjTeleport(aIndex, 30, 105, 50);
		}
		break;
	
	case 5:
		{
			g_GS.gObjTeleport(aIndex, 30, 104, 32);
		}
		break;
	
	case 6:
		{
			g_GS.gObjTeleport(aIndex, 30, 90, 35);
		}
		break;
	
	case 7:
		{
			g_GS.gObjTeleport(aIndex, 30, 90, 46);
		}
		break;
	
	case 8:
		{
			g_GS.gObjTeleport(aIndex, 30, 93, 20);
		}
		break;
	
	case 9:
		{
			g_GS.gObjTeleport(aIndex, 30, 72, 16);
		}
		break;
	
	case 10:
		{
			g_GS.gObjTeleport(aIndex, 30, 54, 25);
		}
		break;

	case 11:
		{
			g_GS.gObjTeleport(aIndex, 30, 83, 31);
		}
		break;

	case 12:
		{
			g_GS.gObjTeleport(aIndex, 30, 106, 31);
		}
		break;
	
	case 13:
		{
			g_GS.gObjTeleport(aIndex, 30, 120, 45);
		}
		break;
	
	case 14:
		{
			g_GS.gObjTeleport(aIndex, 30, 112, 59);
		}
		break;

	case 15:
		{
			g_GS.gObjTeleport(aIndex, 30, 96, 52);
		}
		break;

	case 16:
		{
			g_GS.gObjTeleport(aIndex, 30, 135, 25);
		}
		break;

	case 17:
		{
			g_GS.gObjTeleport(aIndex, 30, 141, 43);
		}
		break;

	case 18:
		{
			g_GS.gObjTeleport(aIndex, 30, 78, 36);
		}
		break;

	case 19:
		{
			g_GS.gObjTeleport(aIndex, 30, 61, 37);
		}
		break;

	default:
		{
			g_GS.gObjTeleport(aIndex, 30, 40, 50);
		}
		break;

	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UINT ObjectGetRandomize(UINT start, UINT max)
{
	UINT random = 0;
	static bool test;
	// ----
	LARGE_INTEGER cicles;
	QueryPerformanceCounter(&cicles);
	srand (cicles.QuadPart);
	// ----
	for(;;)
	{
		random = rand() % max;
		// ----
		if(random >= start)
		{
			break;
		}
	}
	return random;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectUpdateFirstMarrigeInfo(int aIndex, char * Name, char * MarryName, int IsMarried, int MarryType)
{
	int Index = gObjGetIndexByName(Name);
	
	if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX) && Index == aIndex)
	{
		_NEW_OBJECT * nObject = & g_GS.nObject[NINDEX(Index)];
		// ----
		nObject->IsMarried = IsMarried;
		nObject->MarryType = MarryType;
		memcpy(nObject->MarryName,		MarryName,		sizeof(nObject->MarryName));
		// ----
		if(nObject->IsMarried == 1)
		{
			g_Msg.Msg(Index,"@[Marry] You are Married to %s", nObject->MarryName);
			int tIndex = gObjGetIndexByName(nObject->MarryName);
			if((tIndex >= OBJECT_START_INDEX) && (tIndex <= OBJECT_MAX_INDEX))
			{
				g_Msg.Msg(Index, "@[Marry] Your Partner is Online");
				g_Msg.Msg(tIndex, "@[Marry] Your Partner Has Loged In");
			}
			else
			{
				g_Msg.Msg(Index, "@[Marry] Your Partner is Offline");
			}

		}
		else if (nObject->IsMarried == 0)
			g_Msg.Msg(Index,"@[Marry] You are not Married");
		else
			g_Msg.Msg(Index,"@[Marry] Unknown Error (2) Report Admin");

	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectChangeSkin(char * GMName, char * szName, int Status, int MID)
{
	int GmIndex = gObjGetIndexByName(GMName);
	if (Status != 0)
	{
		
		int tIndex = gObjGetIndexByName(szName);
	
		if(_strcmpi(szName, "") != 0 && (tIndex >= OBJECT_START_INDEX) && (tIndex <= OBJECT_MAX_INDEX))
		{
			if (Status == 2)
			{
				gObj[tIndex].m_Change = MID;
				g_GS.gObjViewportListProtocolCreate(&gObj[tIndex]);
				g_Msg.Msg(GmIndex,"@[Skin] You Changed to Number %d", MID);
				g_Msg.Msg(tIndex,"@[Skin] %s Changed You to Number %d", GMName, MID);
			}
			else
			{
				g_Msg.Msg(GmIndex,"@[Skin] You Dont Have Access");
				g_Msg.Msg(GmIndex,"@[Skin] You Have Been Reported");
				g_GmsLog.Output(GMS_LOG_Access, gObj[GmIndex].AccountID, gObj[GmIndex].Name, "Skino");
			}

		}
		else if (_strcmpi(szName, "") == 0)
		{
			gObj[GmIndex].m_Change = MID;
			g_GS.gObjViewportListProtocolCreate(&gObj[GmIndex]);
			g_Msg.Msg(GmIndex,"@[Skin] You Changed to Number %d", MID);
		}
		else
		{
			g_Msg.Msg(GmIndex,"@[Skin] Player Not Connected");
		}
	}
	else
	{
		g_Msg.Msg(GmIndex,"@[Skin] You Dont Have Access");
		g_Msg.Msg(GmIndex,"@[Skin] You Have Been Reported");
		g_GmsLog.Output(GMS_LOG_Access, gObj[GmIndex].AccountID, gObj[GmIndex].Name, "Skin");
	}
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # FriendMemo System
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectFriendMemoDelete(char * Name, int MemoIndex)
{
	int aIndex = gObjGetIndexByName(Name);
	// ----
	if (aIndex >= OBJECT_START_INDEX && aIndex <= OBJECT_MAX_INDEX)
	{
		PMSG_FRIEND_MEMO_DEL_REQ pMsg = {0};
		pMsg.h; 
		pMsg.MemoIndex = MemoIndex;
		// ----
		g_GS.FriendMemoDelReq((DWORD)&pMsg, aIndex);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectFriendMemoListSend(char * SendName, char * RecvName, int MemoIndex, char * Subject, char * Date)
{
	int tIndex = gObjGetIndexByName(RecvName);
	// ----
	char szSendName[11] = {0};
	char szRecvName[11] = {0};
	char szSubject[32] = {0};
	// ----
	memcpy(szSendName, SendName, sizeof(szSendName));
	memcpy(szRecvName, RecvName, sizeof(szRecvName));
	memcpy(szSubject, Subject, sizeof(szSubject));
	// ----
	if (tIndex >= 0 && tIndex <= OBJECT_MAX_INDEX)
	{
		FHP_FRIEND_MEMO_LIST pMsg = {0};
		// ----
		pMsg.Number		= gObjGetIndexByName(RecvName);
		pMsg.MemoIndex	= MemoIndex;
		pMsg.read		= 0;
		// ----
		memcpy(pMsg.SendName, szSendName,	sizeof(pMsg.SendName));
		memcpy(pMsg.RecvName, szRecvName,	sizeof(pMsg.RecvName));
		memcpy(pMsg.Date,	Date,			sizeof(Date));
		memcpy(pMsg.Subject, szSubject,		sizeof(szSubject));
		// ----
		g_GS.FriendMemoList((DWORD)&pMsg);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ObjectCheckUnAllowedChars(std::string szNick)
{
	if (szNick.length() < 4 || szNick.length() > 10)
	{
		return false;
	}
	for (int i = 0; i<szNick.length(); i++)
	{
		if(szNick.at(i) >= 'a' && szNick.at(i) <= 'z')
		{
			// OK
		}
		else if(szNick.at(i) >= 'A' && szNick.at(i) <= 'Z')
		{
			// OK
		}
		else if(szNick.at(i) >= '0' && szNick.at(i) <= '9')
		{
			// OK
		}
		else if(szNick.at(i) == '!' || szNick.at(i) == '@' || szNick.at(i) == '#' || szNick.at(i) == '$' || szNick.at(i) == '*' || szNick.at(i) == '(' || szNick.at(i) == ')' || szNick.at(i) == '_' || szNick.at(i) == '-' || szNick.at(i) == '='  || szNick.at(i) == '[' || szNick.at(i) == ']' || szNick.at(i) == '~' || szNick.at(i) == '<' || szNick.at(i) == '>' || szNick.at(i) == '+')
		{
			// OK
		}
		else
		{
			// BAD
			return false;
		}
	}
	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectGuildChangeMemberStatus (char * AssistName, char * MemberName, char * GuildName, BYTE Type, int Status)
{
	int aIndex = gObjGetIndexByName(AssistName);
	// ----
	if(aIndex < OBJECT_START_INDEX || aIndex > OBJECT_MAX_INDEX)
	{
		return;
	}
	switch (Status)
	{
		case -1:
		{
			g_Msg.Msg(aIndex, 1, "Unknown Error #1 - Report to Srv.Develpoer");
		}
		break;
		case 1:
		{
			if (Type == 0)
			{
				g_GS.GDGuildReqAssignStatus(aIndex, 3, MemberName, 0);
			}
			else if (Type == 32)
			{
				g_GS.GDGuildReqAssignStatus(aIndex, 1, MemberName, 32);
			}
			else
			{
				g_Msg.Msg(aIndex, 1, "Unknown Error #2 - Report to Srv.Develpoer");
			}
		}
		break;
		case 2:
		{
			g_Msg.Msg(aIndex, "@Can't change to the same status");
		}
		break;
		case 3:
		{
			g_Msg.Msg(aIndex, "@Trying to change to not a Guild Member");
		}
		break;
		case 4:
		{
			g_Msg.Msg(aIndex, "@You have already 2 Battles");
		}
		break;
		case 5:
		{
			g_Msg.Msg(aIndex, "@You aren't Guild Assist");
		}
		break;
		case 6:
		{
			g_Msg.Msg(aIndex, 1, "Unknown Error #6 - Report to Srv.Develpoer");
		}
		break;
		case 7:
		{
			g_Msg.Msg(aIndex, "@Trying to change the Manager Guild");
		}
		break;
		case 8:
		{
			g_Msg.Msg(aIndex, "@You don't have access");
		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectGuildKickMember (char * AssistName, char * MemberName, char * GuildName, int Status)
{
	int aIndex = gObjGetIndexByName(AssistName);
	// ----
	if(aIndex < OBJECT_START_INDEX || aIndex > OBJECT_MAX_INDEX)
	{
		return;
	}
	switch (Status)
	{
		case -1:
		{
			g_Msg.Msg(aIndex, 1, "Unknown Error #1 - Report to Srv.Develpoer");
		}
		break;
		case 1:
		{
			g_GS.GDGuildMemberDel(aIndex, GuildName, MemberName);
		}
		break;
		case 2:
		{
			g_Msg.Msg(aIndex, "@Trying to kick Manager");
		}
		break;
		case 3:
		{
			g_Msg.Msg(aIndex, "@Trying to kick not a Guild Member");
		}
		break;
		case 4:
		{
			g_Msg.Msg(aIndex, "@You aren't Guild Assist");
		}
		break;
		case 5:
		{
			g_Msg.Msg(aIndex, "@You don't have access");
		}
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ObjectClientProcessNotify(int aIndex, std::string sProcessName, ULONGLONG uChecksum)
{
	if (strlen(gObj[aIndex].AccountID) > 1) {
		std::string Account(gObj[aIndex].AccountID);
		std::string Ip(gObj[aIndex].Ip_addr);

		GDAntiHackProcessNotify(Account, Ip, sProcessName, uChecksum);

		
		/*for (auto checksum : g_Config.BadProcessesList) {

			if (uChecksum == checksum) {
				g_ProcessesLog.Output("[%s][%s][%s] - Has been disconnected by the server, Process: [%s] | Hash: [%I64u]",
					Account.c_str(), gObj[aIndex].Name, Ip.c_str(), sProcessName.c_str(), uChecksum);

				g_GS.CloseClient(aIndex);

				break;
			}
		}*/
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GCResultSend(int aIndex, BYTE headcode, BYTE result)
{
	PMSG_DEFRESULT pResult;

	PHeadSetB((LPBYTE)&pResult, headcode, sizeof(pResult));
	pResult.result = result;
	
	g_GS.DataSend(aIndex, (UCHAR*)&pResult, pResult.h.size);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CGGuildRequestRecv(int aIndex, int assistIndex)
{
	int number = assistIndex;
	// ----
	if(number < OBJECT_START_INDEX || number > OBJECT_MAX_INDEX)
	{
		return;
	}
	if(aIndex < OBJECT_START_INDEX || aIndex > OBJECT_MAX_INDEX)
	{
		return;
	}
	// ----
	if(gObjIsConnected(number) == false)
	{
		GCResultSend(aIndex, 0x51, 0x03);
		// ----
		return;
	}
	// ----
	if(gObj[aIndex].m_IfState.use > 0)
	{
		GCResultSend(aIndex, 0x51, 0x06);
		// ----
		return;
	}
	// ----
	if(gObj[number].m_IfState.use > 0)
	{
		GCResultSend(aIndex, 0x51, 0x06);
		return;
	}
	// ----
	if(gObj[aIndex].Level < 6)
	{
		GCResultSend(aIndex, 0x51, 0x07);
		return;
	}
	// ----
	if(gObj[aIndex].GuildNumber > 0)
	{
		GCResultSend(aIndex, 0x51, 0x05);
		return;
	}
	// ----
	if((gObj[number].m_Option & 1) != 1)
	{
		GCResultSend(aIndex, 0x51, 0x00);
		return;
	}
	// ----
	if(gObj[number].GuildNumber > 0)
	{
		/*if(strcmp(gObj[number].lpGuild->Names[0], gObj[number].Name))
		{
			GCResultSend(aIndex, 0x51, 0x04);
			// ----
			return;
		}*/
		// ----
		if(gObj[number].lpGuild->WarState)
		{
			GCResultSend(aIndex, 0x51, 0x06);
			// ----
			return;
		}
		// ----
		int MaxGuildMember;
		// ----
		if(gObj[number].Class == 4) // LORD
		{
			MaxGuildMember = gObj[number].Level / 10 + gObj[number].Leadership / 10;
		}
		else
		{
			MaxGuildMember = gObj[number].Level / 10;
		}
		// ----
		if(MaxGuildMember > MAX_USER_GUILD)
		{
			MaxGuildMember = MAX_USER_GUILD;
		}
		// ----
		if(gObj[number].lpGuild->TotalCount >= MaxGuildMember)
		{
			GCResultSend(aIndex, 0x51, 0x02);
			// ----
			return;
		}
	}
	else
	{
		GCResultSend(aIndex, 0x51, 0x04);
		// ----
		return;
	}
	// ----
	gObj[aIndex].m_IfState.use		= 1;
	gObj[aIndex].m_IfState.type		= 4;
	gObj[aIndex].m_IfState.state	= 0;
	// ----
	gObj[number].m_IfState.use		= 1;
	gObj[number].m_IfState.type		= 4;
	gObj[number].m_IfState.state	= 0;
	// ----
	gObj[aIndex].TargetNumber		= number;
	gObj[number].TargetNumber		= aIndex;
	// ----
	gObj[aIndex].m_InterfaceTime	= GetTickCount();
	gObj[number].m_InterfaceTime	= GetTickCount();
	// ----
	PMSG_GUILDQUESTSEND pMsg;
	// ----
	PHeadSetB((LPBYTE)&pMsg, 0x50, sizeof(pMsg));
	// ----
	pMsg.NumberH					= SET_NUMBERH(aIndex);
	pMsg.NumberL					= SET_NUMBERL(aIndex);
	// ----
	g_GS.DataSend(number, (LPBYTE)&pMsg, pMsg.h.size);
	// ----

	g_Msg.Msg(aIndex, "out1");
	g_Msg.Msg(assistIndex, "out2");
}