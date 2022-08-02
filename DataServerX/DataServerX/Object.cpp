//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Object.h"
#include "Protocol.h"
#include "GConfig.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "Object"
//-----------------------------------------------------------------------------------------------------------------------

TDataBase			g_DB;
OBJECTSTRUCT		g_Obj[OBJECT_MAX];
iocp::CIocpServer	* gDSIocp;

//-----------------------------------------------------------------------------------------------------------------------

bool		isDBConnected = false;
bool		MSG_CONTINUE  = false;
//-----------------------------------------------------------------------------------------------------------------------

int gObjSearchFree() 
{
	for(int i = 0; i < OBJECT_MAX; ++i)
	{
		if(g_Obj[i].m_aStatus == O_STATUS_EMPTY)
		{
			return i;
			// ----
			break;
		}
	}
	// ----
	return INVALID_OBJECT;
}
//-----------------------------------------------------------------------------------------------------------------------

void gObjAdd(int aIndex)
{
	PCLIENTOBJECTSTRUCT lpObj = & g_Obj[aIndex];
	// ----
	if(lpObj->m_aStatus == O_STATUS_EMPTY)
	{
		lpObj->m_aStatus = O_STATUS_CONNECTED;
		// ----
		lpObj->m_GSCode				= -1;
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void gObjDel(int aIndex) 
{
	PCLIENTOBJECTSTRUCT lpObj = & g_Obj[aIndex];
	// ----
	if(lpObj->m_aStatus != O_STATUS_EMPTY)
	{
		lpObj->m_aStatus = O_STATUS_EMPTY;
		lpObj->m_GSCode = -1;
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void objectInit()
{
	for(int i = 0 ; i != OBJECT_MAX ; ++i)
	{
		g_Obj[i].m_GSCode = -1;
	}

	if(g_DB.Connect("MuOnline") == true)
	{
		isDBConnected = true;
	}
	else
	{
		g_DB.DiagnosticConn();
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void objectWorker()
{
	if(isDBConnected == true)
	{
		g_DB.Diagnostic();
		g_DB.DiagnosticConn();
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void objectMsgToNick(TIOCPHandler * h,std::string szNick, std::string szMessage)
{
	MSG_MSGTONICK pMsg = {0};
	// ----
	memcpy(pMsg.szNick,		szNick.c_str(),			szNick.length());
	memcpy(pMsg.szMessage,	szMessage.c_str(),		szMessage.length());
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_MSGTONICK);
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::LightGray, "msg (%s) to nick(%s)", szMessage.c_str(), szNick.c_str());
	// ----
	h->sendAll((UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void objectMsgToNick(TIOCPHandler * h, uint64_t cid, char * szNick, const char * szMessage)
{
	MSG_MSGTONICK pMsg = { 0 };
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_MSGTONICK);
	// ----
	memcpy(pMsg.szNick, szNick, strlen(szNick));
	memcpy(pMsg.szMessage, szMessage, strlen(szMessage));
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *)& pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void objectMsgToNick(std::string szNick, std::string szMessage)
{
	MSG_MSGTONICK pMsg = {0};
	// ----
	memcpy(pMsg.szNick,		szNick.c_str(),			szNick.length());
	memcpy(pMsg.szMessage,	szMessage.c_str(),		szMessage.length());
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_MSGTONICK);
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::LightGray, "msg (%s) to nick(%s)", szMessage.c_str(), szNick.c_str());
	// ----
	g_IOCP->sendAll((UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectDcToNick(TIOCPHandler * h, char * szNick)
{	
	MSG_DCTONICK pMsg = {0};
	// ----
	memcpy(pMsg.szNick,		szNick,		strlen(szNick));
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_DCTONICK);
	// ----
	h->sendAll((UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectDcToNick(TIOCPHandler * h, uint64_t cid, char * szNick)
{
	MSG_DCTONICK pMsg = {0};
	// ----
	memcpy(pMsg.szNick,		szNick,		strlen(szNick));
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_DCTONICK);
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectDcToAccount(TIOCPHandler * h, std::string sAccount)
{
	MSG_DCTOACCOUNT pMsg = { 0 };
	// ----
	memcpy(pMsg.szAccountId, sAccount.c_str(), sAccount.length());
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_DCTOACCOUNT);
	// ----
	h->sendAll((UCHAR *)& pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectDcToAccount(TIOCPHandler * h, uint64_t cid, std::string sAccount)
{
	MSG_DCTOACCOUNT pMsg = { 0 };
	// ----
	memcpy(pMsg.szAccountId, sAccount.c_str(), sAccount.length());
	// ----
	HeadSet1(&pMsg.Head, sizeof(pMsg), HEAD_DCTOACCOUNT);
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *)& pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectAccessBan(TIOCPHandler * h, uint64_t cid, char * szNick, const char * command)
{
	MSG_ACCESS_BAN pMsg = {0};
	// ----
	memcpy(pMsg.Name,	szNick,		strlen(szNick));
	memcpy(pMsg.Command,		command,		strlen(command));
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_ACCESS_DENIED_BAN);
	// ----
	h->GetIocpServer().Send(cid, (UCHAR *) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectLogCreditAdd(std::string Name, std::string Account, int Credits, std::string type, int typeIndex)
{
	g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "SELECT Credits FROM MEMB_INFO WHERE memb___id = '%s'", Account.c_str());
	// ----
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		int CreditsTotal = g_DB.GetInt("Credits");
		g_DB.Clear();
		// ----
		g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "INSERT INTO Credit_LOG (acc,name,date,type,credit,credittotal, typeIndex) VALUES \
				('%s', '%s', getdate(), '%s', '%d', '%d', '%d');", Account.c_str(), Name.c_str(), type.c_str(), Credits, CreditsTotal, typeIndex);
		g_DB.Fetch();
	}
	// ----
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectLogHistoryAdd(std::string Name, std::string Account, std::string type, std::string ip, int typeIndex)
{
	g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "SELECT Credits FROM MEMB_INFO WHERE memb___id = '%s'", Account.c_str());
	// ----
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		g_DB.Clear();
		// ----
		g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "INSERT INTO Credit_LOG (acc, name, date, type, credit, credittotal, ip, typeIndex) VALUES \
				('%s', '%s', getdate(), '%s', '%d', '%d', '%s', '%d');", Account.c_str(), Name.c_str(), type.c_str(), 0, 0, ip.c_str(), typeIndex);
		g_DB.Fetch();
	}
	// ----
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectLogHistoryUpdateLine(std::string Name, std::string Account, std::string date, std::string ip)
{
	g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "SELECT Credits FROM MEMB_INFO WHERE memb___id = '%s'", Account.c_str());
	// ----
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		g_DB.Clear();
		// ----
		g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "UPDATE Credit_Log SET name = '%s', date = getdate(), ip = '%s' WHERE date = '%s' and acc = '%s'",
			Name.c_str(), ip.c_str(), date.c_str(), Account.c_str());
		
		g_DB.Fetch();
	}
	// ----
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectLogEventAdd(std::string Name, std::string Account, std::string whoRun, std::string typeEvent, std::string typePrize, int amount)
{
	g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "INSERT INTO Event_LOG (acc,name,eventCreator,date,typeEvent,typePrize,amountPrize) VALUES \
		('%s', '%s', '%s', getdate(), '%s', '%s', '%d');", Account.c_str(), Name.c_str(), whoRun.c_str(), typeEvent.c_str(), typePrize.c_str(), amount);
	g_DB.Fetch();
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectSendNoticeAll(std::string Notice)
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::LightGray, "%s", Notice.c_str());
	// ----
	MSG_SENDNOTICEALLFROMDS pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_SENDNOTICEALLFROMDS);
	// ----
	memcpy(pMsg.Notice, Notice.c_str(), Notice.length());
	// ----
	pMsg.NoticeLen = Notice.length();
	// ----
	if (pMsg.NoticeLen >= sizeof(pMsg.Notice)) {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Notice len max over: %d, limit: %d",
			pMsg.NoticeLen, sizeof(pMsg.Notice));

		pMsg.NoticeLen = sizeof(pMsg.Notice) - 1;
	}
	// ----
	g_IOCP->sendAll((LPBYTE) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

GMS_LIST ObjectGetAllGmsStatus()
{
	GMS_LIST GMS_Job;
	tagGMSStatus newGM;
	// ----
	int Counter = 0;
	bool Status = false;
	char Name [256] = {0};
	char GMN [256] = {0};
	char GSName [25] = {0};
	// ----
	g_DB.Exec(-1, g_ModuleName, __FUNCTION__, (char *)"SELECT AccName, GMName from GM");
	// ----
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		do
		{
			g_DB.GetStr("AccName", Name);
			g_DB.GetStr("GMName", GMN);
			// ----
			newGM.accName		= Name;
			newGM.GMName		= GMN;
			newGM.bStatus		= false;
			newGM.btServerCode	=  0;
			// ----
			GMS_Job.push_back(newGM);
			// ----
			++Counter;
		}
		while (Counter <50 && g_DB.Fetch() != SQL_NO_DATA);
	}
	// ----
	g_DB.Clear();
	// ----
	for (GMS_LIST::iterator it = GMS_Job.begin() ; it != GMS_Job.end() ; ++it)
	{
		g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "SELECT ServerName, ConnectStat from MEMB_STAT where memb___id = '%s'", it->accName.c_str());
		g_DB.Fetch();
		// ----
		Status = (bool)g_DB.GetInt("ConnectStat");
		// ----
		g_DB.GetStr("ServerName",GSName);
		// ----
		it->btServerCode = g_Config.getGSCodeGameByGSName(GSName);
		// ----
		g_DB.Clear();
		// ----
		if(Status)
		{
			g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "SELECT GameIDC FROM AccountCharacter WHERE Id = '%s'", it->accName.c_str());
			g_DB.Fetch();
			// ----
			char Temp[12] = {0};
			// ----
			g_DB.GetStr("GameIDC", Temp);
			g_DB.Clear();
			// ----
			if(_strcmpi(it->GMName.c_str(), Temp) == 0)
			{
					it->bStatus		 = true;
			}
			else
			{
					it->bStatus		 = false;
			}
		}
		else
		{
			it->bStatus		 = false;
		}
		// ----
		g_DB.Clear();
	}
	// ----
	return GMS_Job;
}
//-----------------------------------------------------------------------------------------------------------------------

GUILD_MEMBER_LIST ObjectGetAllMembersGuild(std::string GuildName)
{
	GUILD_MEMBER_LIST MEMBER_Job;
	tagMEMBERGuild newMember;
	// ----
	int Counter = 0;
	int CtlCode = 0;
	bool Status = false;
	char Name [11] = {0};
	char AccountName [11] = {0};
	char GSName [20] = {0};
	// ----
	g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "SELECT Name from GuildMember where G_Name = '%s'", GuildName.c_str());
	if(g_DB.Fetch() != SQL_NO_DATA)
	{
		do
		{
			g_DB.GetStr("Name", Name);
			// ----
			newMember.NameMember	= Name;
			newMember.bStatus		= false;
			newMember.btServerCode	=  0;
			// ----
			MEMBER_Job.push_back(newMember);
			// ----
			++Counter;
		}
		while (Counter <50 && g_DB.Fetch() != SQL_NO_DATA);
	}
	// ----
	g_DB.Clear();
	// ----
	for (GUILD_MEMBER_LIST::iterator it = MEMBER_Job.begin() ; it != MEMBER_Job.end() ; ++it)
	{
		g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "SELECT AccountID, CtlCode from Character where Name = '%s'", it->NameMember.c_str());
		g_DB.Fetch();
		// ----
		g_DB.GetStr("AccountID",AccountName);
		CtlCode = g_DB.GetInt("CtlCode");
		// ----
		it->accName = AccountName;
		// ----
		g_DB.Clear();
		// ----
		g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "SELECT ServerName, ConnectStat from MEMB_STAT where memb___id = '%s'", AccountName);
		g_DB.Fetch();
		// ----
		g_DB.GetStr("ServerName",GSName);
		// ----
		it->btServerCode = g_Config.getGSCodeGameByGSName(GSName);
		// ----
		Status = (bool)g_DB.GetInt("ConnectStat");
		// ----
		g_DB.Clear();
		// ----
		if(Status && CtlCode != 32)
		{
			g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "SELECT GameIDC FROM AccountCharacter WHERE Id = '%s'", AccountName);
			g_DB.Fetch();
			// ----
			char Temp[12] = {0};
			// ----
			g_DB.GetStr("GameIDC", Temp);
			g_DB.Clear();
			// ----
			if(_strcmpi(it->NameMember.c_str(), Temp) == 0)
				{
					it->bStatus		 = Status;
				}
			else
				{
					it->bStatus		 = false;
				}
		}
		else
		{
			it->bStatus	= false;
		}
		// ----
		g_DB.Clear();
	}
	// ----
	return MEMBER_Job;
}
//-----------------------------------------------------------------------------------------------------------------------

void MessagesWebState(bool status)
{
	if(status == true) {
		g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "Update DataServer Set messages_lock = 1");
	} else {
		g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "Update DataServer Set messages_lock = 0");
	}
	// ----
	g_DB.Fetch();
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

void ObjectIncraseCredits(std::string sAccountId, UINT uAmount) 
{
	g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "UPDATE MEMB_INFO Set Credits = Credits + %d WHERE memb___id = '%s'", uAmount, sAccountId.c_str());
	g_DB.Fetch();
	g_DB.Clear();
}
//-----------------------------------------------------------------------------------------------------------------------

UINT ObjectRandomize(UINT uMin, UINT uMax)
{
	UINT random = 0;
	static bool test;
	// ----
	LARGE_INTEGER cicles;
	QueryPerformanceCounter(&cicles);
	srand(cicles.QuadPart);
	// ----
	for (;;)
	{
		random = rand() % uMax;
		// ----
		if (random >= uMin)
		{
			break;
		}
	}
	return random;
}
//-----------------------------------------------------------------------------------------------------------------------