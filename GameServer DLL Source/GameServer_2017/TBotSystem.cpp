#include "StdAfx.h"
#include "TBotSystem.h"
#include "TSetup.h"
#include "Object.h"
#include "TGameServer.h"
#include "User.h"
#include "TMessages.h"
#include "TConfig.h"
#include "TLogToFile.h"
#include "Helper.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* FILE 
	BotName		BotMap	BotX	BotY	"BotDir"	BotClass		BotCharset															BotAds

	"Leo123"	"0"		"120"	"130"	"3"			"0"				"30 14 14 55 55 5F 1F FF FF FB FE 00 00 0D 00"						"HelloAll"
*/
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CBotSystem g_BotSystem;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int RABBI_INDEX = -1; // not place for that. should be part of CBotSystem
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CBotSystem::CBotSystem(void)
{
	_beginthread(talkWorker, 4, this);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CBotSystem::~CBotSystem(void)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool CBotSystem::loadBots()
{
	bool bReturn = false;
	// ----
	m_Bots.clear();
	// ----
	char localTemp[200] = {0};
	// ----
	if(g_Config.fileRead((char *)BOTS_FILE) == true)
	{
		do
		{	
			tagBot Bot; Bot.Clear();
			// ----
			memset(localTemp, 0, sizeof(localTemp));
			// ----
			// # BotName
			// ----
			g_Config.fileGetString(localTemp);
			Bot.Name = localTemp;
			// ----
			// # BotMap, BotX, BotY, BotTX, BotTY, BotDir, BotClass
			// ----
			Bot.BotMap		= g_Config.fileGetInt();
			Bot.BotX		= g_Config.fileGetInt();
			Bot.BotY		= g_Config.fileGetInt();
			Bot.BotTX		= g_Config.fileGetInt();
			Bot.BotTY		= g_Config.fileGetInt();
			Bot.BotDir		= g_Config.fileGetInt();
			Bot.BotClass	= g_Config.fileGetInt();
			// ----
			// # BotCharset
			// ----
			memset(localTemp, 0, sizeof(localTemp));
			g_Config.fileGetString(localTemp, 50);
			// ----
			helper_removespace(localTemp);
			helper_hex2bin(localTemp, Bot.CharSet, sizeof(Bot.CharSet));
			//				   30 4C C5 22 22 2F 1F FF FF F9 FF A5 00"
			/*sscanf(localTemp, "%X %X %X %X %X %X %X %X %X %X %X %X %X",
				 Bot.CharSet[0],  Bot.CharSet[1],  Bot.CharSet[2],  Bot.CharSet[3],  Bot.CharSet[4], Bot.CharSet[5], Bot.CharSet[6], Bot.CharSet[7], Bot.CharSet[8],
				Bot.CharSet[9], Bot.CharSet[10], Bot.CharSet[11], Bot.CharSet[12]);*/
			// ----
			// Bot Ads
			// ----
			memset(localTemp, 0, sizeof(localTemp));
			g_Config.fileGetString(localTemp);
			Bot.BotAds = localTemp;
			// ----
			memset(localTemp, 0, sizeof(localTemp));
			g_Config.fileGetString(localTemp);
			Bot.BotAds2 = localTemp;
			// ----
			memset(localTemp, 0, sizeof(localTemp));
			g_Config.fileGetString(localTemp);
			Bot.BotAds3 = localTemp;
			// ----
			memset(localTemp, 0, sizeof(localTemp));
			g_Config.fileGetString(localTemp);
			Bot.BotAds4 = localTemp;
			// -----
			Bot.BotIsRabbi	= g_Config.fileGetInt();
			m_Bots.push_back(Bot);
 		} while (g_Config.fileIsEnd() == false);
		// ----
		g_Config.fileClose();
		// ----
		bReturn = true;
	} 
	// ----
	return bReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CBotSystem::printDemo(int aIndex)
{
	for(BOTS_LIST::iterator it = m_Bots.begin() ; it != m_Bots.end() ; ++it)
	{
		g_Msg.Msg(aIndex, "%s %s", it->Name.c_str(), it->BotAds.c_str());
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool CBotSystem::isThatBot(int aIndex)
{
	bool bReturn = false;
	// ----
	for(BOTS_LIST::iterator it = m_Bots.begin() ; it != m_Bots.end() ; ++it)
	{
		if(it->aIndex == aIndex)
		{
			bReturn = true;
			// ----
			break;
		}
	}
	// ----
	return bReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CBotSystem::addBots()
{
	for(BOTS_LIST::iterator it = m_Bots.begin() ; it != m_Bots.end() ; ++it)
	{
		if (it->isEventBot != 1)
		{
			it->aIndex = ObjectSpawnMonster(17, it->BotMap, it->BotX, it->BotY);
			// ----
			gObj[it->aIndex].Type		= OBJ_USER;
			gObj[it->aIndex].DbClass	= 1;
			gObj[it->aIndex].Class		= it->BotClass;
			gObj[it->aIndex].m_Change	= -1;
			gObj[it->aIndex].Dir		= it->BotDir;
			// ----
			gObj[it->aIndex].Level		= 400;
			gObj[it->aIndex].StartX		= it->BotX;
			gObj[it->aIndex].StartY		= it->BotY;
			// ----
			gObj[it->aIndex].MTX		= it->BotX;
			gObj[it->aIndex].MTY		= it->BotY;
			// ----
			gObj[it->aIndex].TX			= it->BotTX;
			gObj[it->aIndex].TY			= it->BotTY;
			// ----
			gObj[it->aIndex].m_OldX		= it->BotX;
			gObj[it->aIndex].m_OldY		= it->BotY;
			// ----
			gObj[it->aIndex].m_PosNum	= -1;
			gObj[it->aIndex].PathCount	= 0;
			gObj[it->aIndex].PathStartEnd = 0;
			gObj[it->aIndex].Teleport = 0;
			gObj[it->aIndex].m_Option = 0;
			// ----
			memcpy(gObj[it->aIndex].CharSet, it->CharSet, sizeof(it->CharSet));
			// ----
			g_GS.gObjViewportListProtocolCreate(& gObj[it->aIndex]);
			// ----
			memset(gObj[it->aIndex].Name, 0, sizeof(gObj[it->aIndex].Name));
			memcpy(gObj[it->aIndex].Name, it->Name.c_str(), it->Name.length());
			// ----
			gObj[it->aIndex].Live = FALSE;

			if(it->BotIsRabbi == 1)
			{
				RABBI_INDEX = it->aIndex;
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CBotSystem::delBots()
{
	int indexTemp = -1;
	// ----
	for(BOTS_LIST::iterator it = m_Bots.begin() ; it != m_Bots.end() ; ++it)
	{
		indexTemp = it->aIndex;
		// ----
		it->aIndex = -1;
		// ----
		g_GS.gObjDel(indexTemp);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CBotSystem::talkWorker(LPVOID param)
{
	boost::mutex Guard;
	// ----
	CBotSystem * botSystem = (CBotSystem *) param;
	// ----
	struct PMSG_CHATDATA_NUMBER
	{
		PBMSG_HEAD h;
		BYTE NumberH;	// 3
		BYTE NumberL;	// 4
		char chatmsg[60];	// 5
	};
	// ----
	while(true)
	{
		boost::posix_time::seconds seconds(7);
		boost::posix_time::seconds seconds3(3);
		boost::this_thread::sleep(seconds);
		// ----
		if(botSystem->m_Bots.size() > 0)
		{
			for(BOTS_LIST::iterator it = botSystem->m_Bots.begin() ; it != botSystem->m_Bots.end() ; ++it)
			{
				gObj[it->aIndex].ConnectCheckTime = GetTickCount();
				// ----
				PMSG_CHATDATA_NUMBER pMsg = {0};
				// ----
				pMsg.h.set((LPBYTE) & pMsg, 0x01, sizeof(pMsg));
				// ----
				pMsg.NumberH = SET_NUMBERH(it->aIndex);
				pMsg.NumberL = SET_NUMBERL(it->aIndex);
				// ----
				if(_strcmpi(it->BotAds.c_str(), "0") != 0)
				{
					memset(pMsg.chatmsg, 0 , sizeof(pMsg.chatmsg));
					memcpy(pMsg.chatmsg, it->BotAds.c_str(), it->BotAds.length());
					g_GS.MsgSendV2((DWORD) & gObj[it->aIndex], (LPBYTE) & pMsg, sizeof(pMsg));
					boost::this_thread::sleep(seconds3);
				}
				else continue;
				// ----
				if(_strcmpi(it->BotAds2.c_str(), "0") != 0)
				{
					memset(pMsg.chatmsg, 0 , sizeof(pMsg.chatmsg));
					memcpy(pMsg.chatmsg, it->BotAds2.c_str(), it->BotAds2.length());
					g_GS.MsgSendV2((DWORD) & gObj[it->aIndex], (LPBYTE) & pMsg, sizeof(pMsg));
					boost::this_thread::sleep(seconds3);
				}
				else continue;
				// ----
				if(_strcmpi(it->BotAds3.c_str(), "0") != 0)
				{
					memset(pMsg.chatmsg, 0 , sizeof(pMsg.chatmsg));
					memcpy(pMsg.chatmsg, it->BotAds3.c_str(), it->BotAds3.length());
					g_GS.MsgSendV2((DWORD) & gObj[it->aIndex], (LPBYTE) & pMsg, sizeof(pMsg));
					boost::this_thread::sleep(seconds3);
				}
				else continue;
				// ----
				if(_strcmpi(it->BotAds4.c_str(), "0") != 0)
				{
					memset(pMsg.chatmsg, 0 , sizeof(pMsg.chatmsg));
					memcpy(pMsg.chatmsg, it->BotAds4.c_str(), it->BotAds4.length());
					g_GS.MsgSendV2((DWORD) & gObj[it->aIndex], (LPBYTE) & pMsg, sizeof(pMsg));
					boost::this_thread::sleep(seconds3);
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void CBotSystem::sendMessageFromBot(int Index, const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	boost::mutex Guard;
	// ----
	struct PMSG_CHATDATA_NUMBER
	{
		PBMSG_HEAD h;
		BYTE NumberH;	// 3
		BYTE NumberL;	// 4
		char chatmsg[60];	// 5
	};
	// ----
	for(BOTS_LIST::iterator it = m_Bots.begin() ; it != m_Bots.end() ; ++it)
	{
		if (it->aIndex == Index && Index != -1)
		{
			// ----
			PMSG_CHATDATA_NUMBER pMsg = {0};
			// ----
			pMsg.h.set((LPBYTE) & pMsg, 0x01, sizeof(pMsg));
			// ----
			pMsg.NumberH = SET_NUMBERH(it->aIndex);
			pMsg.NumberL = SET_NUMBERL(it->aIndex);
				// ----
			if(_strcmpi(Message, "") != 0)
			{
				memset(pMsg.chatmsg, 0 , sizeof(pMsg.chatmsg));
				memcpy(pMsg.chatmsg, Message, strlen(Message));
				g_GS.MsgSendV2((DWORD) & gObj[it->aIndex], (LPBYTE) & pMsg, sizeof(pMsg));			
			}
		}		
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
