#include "StdAfx.h"
#include "TCore.h"
#include "Object.h"
#include "TSetup.h"
#include "TMessages.h"
#include "User.h"
#include "DSXProtocol.h"
#include "Chat.h"
#include "TDataServerSocket.h"
#include "TEncoding.h"
#include "TLogToFile.h"
#include "TChatVote.h"
#include "TBotSystem.h"
#include "TConfig.h"
#include "TNotice.h"
#include "TMarrySystem.h"
#include "Item.h"
#include "TShop.h"
#include "OffTrade.h"
#include "RedDragon.h"
#include "TPacket.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # Made By Leo123[BoR] -> GS 99.60T -> Only for MuOnline.co.il
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int g_GMLOGINID; // Bad 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool CCore::isFirstTimeConnect = false; 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::handlePackt(LPBYTE Packet, int Size)
{
	char btTemp[1024 * 3] = {0};
	// ----
	sprintf(btTemp, "Packet : ");
	// ----
	for(int i = 0 ; i != Size ; ++i)
	{
		if(i == 0)
		{
			sprintf(btTemp, "%X" , (BYTE)Packet[i]);
			// ----
			continue;
		}
		if((BYTE)Packet[i] > (BYTE)9)
		{
			sprintf(btTemp, "%s %X", btTemp, (BYTE)Packet[i]);
		}
		else
		{
			sprintf(btTemp, "%s 0%X", btTemp, (BYTE)Packet[i]);
		}
	}
	// ----
	g_HackLog.Output(btTemp);
	// ----
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::RecvDataParse(_PER_IO_CONTEXT * lpIOContext, int uIndex)
{
	#ifdef GS_99_60T
		if(g_BotSystem.isThatBot(uIndex) == true)
		{
			return;
		}
	#endif
	/*if(((BYTE)lpIOContext->Buffer[0] == 0x40) || ((BYTE)lpIOContext->Buffer[0] == 0x1D))
	{
		GCJoinResult(0x06, uIndex);
		// ----
		return;
	}
	
	handlePackt((LPBYTE)lpIOContext->Buffer, lpIOContext->nSentBytes);
	// ----
	BYTE xcode = (BYTE)lpIOContext->Buffer[0];
	// ----
	switch(xcode)
	{
		case 0xC1:
		case 0xC2:
		case 0xC3:
		case 0xC4:
		{
			//g_GS.CloseClient(uIndex);
			// ----
			g_HackLog.Output("%s using C1,C2,C3,C4", gObj[uIndex].Ip_addr);
			// ----
			handlePackt((LPBYTE)lpIOContext->Buffer, lpIOContext->nSentBytes);
		}
		break;
	}
	*/
	// ----
	#ifndef SEASAON3
		#if(PACKET_ENCYRPTION > 0)
			g_Encoder.DecodeBuffer((LPBYTE)lpIOContext->Buffer, lpIOContext->nSentBytes);
		#endif
	#endif
	// ----
	g_GS.RecvDataParse(lpIOContext, uIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::ProtocolCore(DWORD protoNum, LPBYTE aRecv, int aLen, int aIndex, DWORD Encrypt, DWORD Serial)
{
	bool bStop					= false;
	// ----
	static char szTemp[MAX_TEXT_LEN];
	static char szMsg[MAX_TEXT_LEN];
	// ----
	memset(szTemp, 0,	sizeof(szTemp));
	memset(szMsg, 0,	sizeof(szMsg));
	// ----
	_NEW_OBJECT * nObject		= & g_GS.nObject[FIXINDEX];
	// ----
	switch((BYTE)protoNum)
	{
		case 0xFE:
		{
			CPacket recvPacket(aRecv, aLen);

			std::string process = recvPacket.readString();
			ULONGLONG checksum = recvPacket.readLong();
			
			ObjectClientProcessNotify(aIndex, process, checksum);
			// ----
			bStop = true;
		}
		break;

		case HEAD_NEWAUTH: bStop = true; 

			break;
		// ----
		case HEAD_CHAT:
		{
			bStop = ChatCore(aIndex, (PMSG_CHATDATA *)aRecv);
		}
		break;

		case 0x01:
		{
			bStop = true;
			// ----
			g_HackLog.Output("%s try spoof talk", gObj[aIndex].Name);

		}
		break;

		case HEAD_WHISP:
		{
			PMSG_CHATDATA_WHISPER * whispMsg = (PMSG_CHATDATA_WHISPER *) aRecv;
			// ----
			g_ChatWhispLog.Output(WHISP_LOG_MESSAGE_FORMAT, g_Config.nServerCode, gObj[aIndex].Name, whispMsg->id, whispMsg->chatmsg);

			if (gObjIsGameMaster(aIndex) == true)
			{
				g_ChatWhispLog.Output(WHISP_LOG_MESSAGE_FORMAT, g_Config.nServerCode, gObj[aIndex].Name, whispMsg->id, whispMsg->chatmsg);
			}

			std::string s1 = whispMsg->id;

			if (s1.back() == 'M')
			{
					s1.pop_back();
					if (s1.back() == 'G')
						g_ChatWhispLogGM.Output(WHISP_LOG_MESSAGE_FORMAT, g_Config.nServerCode, gObj[aIndex].Name, whispMsg->id, whispMsg->chatmsg);
			}
		}
		break; 

		case HEAD_LAHAPMIX:
		{
			tagInterfaceState * state =  & gObj[aIndex].m_IfState;
			// ----
			if(state->type == 69)
			{
				g_Msg.SendAllGMS(SEND_TO_GUILD_ANTIHACK_MSG, gObj[aIndex].Name);
				// ----
				g_HackLog.Output(HACK_LOG_LAHAP_MIX_MSG, gObj[aIndex].AccountID, gObj[aIndex].Name);
				// ----
				g_GS.CloseClient(aIndex);
				// ----
				bStop = true;
			}
		}
		break;

		case 0xD0:
		{
			
		}
		break;
		
		case HEAD_MOVE:
		{
			
		}
		break;

		case 0x37:
		{
			tagInterfaceState * state =  & gObj[aIndex].m_IfState;
			// ----
			if(state->type == 68 || state->type == 69)
			{
				g_HackLog.Output("Hack 0x37 %s %s", gObj[aIndex].AccountID, gObj[aIndex].Name);
				// ----
				g_GS.gObjTradeCancel(aIndex);
				g_GS.gObjTradeCancel(gObj[aIndex].TargetNumber);
			}
		}
		break;


		case HEAD_CASTOUMBT: /* CASTOUM BUTTONS LIKE (ESC , I) CHECK FOR TRADE BUG */
		{
			#ifdef GS_99_60T

				tagInterfaceState * state =  & gObj[aIndex].m_IfState;
				// ----
				if(state->type == 65)
				{
					g_Msg.Msg(aIndex, TRYING_USE_ESC_WHILE_TRADE_MSG);
					// ----
					g_HackLog.Output(HACK_LOG_ESC_WHILE_TRADE_MSG, gObj[aIndex].AccountID, gObj[aIndex].Name);
					// ----
					g_GS.gObjTradeCancel(aIndex);
					g_GS.gObjTradeCancel(gObj[aIndex].TargetNumber);
				}
				// ----

			#endif

			bStop = true;
		}
		break;

		case 0x18: // NEW TEST
		{
			if(aLen > 5)
			{
				g_HackLog.Output(HACK_LOG_018, gObj[aIndex].AccountID, gObj[aIndex].Name);
				g_GS.CloseClient(aIndex);
				bStop = true;
			}


			if(aRecv[3] > 7)
			{
				g_HackLog.Output(HACK_LOG_018, gObj[aIndex].AccountID, gObj[aIndex].Name);
				g_GS.CloseClient(aIndex);
				bStop = true;
			}

		}
		break;

		case HEAD_DUELREQ: /* not able use Duel in GS_CS */
		{
			if(g_Config.isGSCastle == true)
			{
				g_Msg.Msg(aIndex, 1 , TRYING_USE_DUEL_WHILE_SIGE);
				// ----
				bStop = true;
			}
		}
		break;

		case HEAD_IMPORTANT:
		{
			PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *) aRecv;
			// ----
			switch(lpDef->subcode)
			{
				case HEAD_IMPORTANT_DELCHAR:
				{
					CGPCharDel((PMSG_CHARDELETE * ) aRecv, aIndex);
					// ----
					bStop = true;
				}
				break;
				
			}
		}break;
		

		// ----
		// # Attack case(s)
		// ----
		
		/*case 0xD9:*/ /*case 0x4A:*/ case 0x1E: case 0x19:
		{
			// ----
			_NEW_OBJECT * nObject		= & g_GS.nObject[FIXINDEX];
			// ----
			nObject->dwFrames++;
			nObject->dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
			nObject->dwElapsedTime = nObject->dwCurrentTime - nObject->dwLastUpdateTime;
			// ----
			if(nObject->dwElapsedTime >= 1000)
			{
				nObject->FPS = (UINT)(nObject->dwFrames * 1000.0 / nObject->dwElapsedTime);
				wsprintf(nObject->szFPS, ("APS = %u"), nObject->FPS);
				nObject->dwFrames = 0;
				nObject->dwLastUpdateTime = nObject->dwCurrentTime;
			}
			if(aRecv[2] == 0x19)
			{
				PMSG_MAGICATTACK * lpMsg = (PMSG_MAGICATTACK *) aRecv;
				// ----
				int Number = MAKE_NUMBERW(lpMsg->MagicLow, lpMsg->MagicHigh);
				// ----
				//g_Msg.Msg(aIndex, "Skill Number : %d", Number);
			}
			else if(aRecv[2] == 0x1E)
			{
				PMSG_DURATION_MAGIC_RECV * lpMsg = (PMSG_DURATION_MAGIC_RECV *) aRecv;
				// ----

				//g_Msg.PM(aIndex, "Num : %d, Target : %d", lpMsg->MagicNumber, lpMsg->TargetPos);

				switch(lpMsg->MagicNumber)
				{
					case 62:
					{
						if(nObject->dwDL_Horse_Tick == 0)
						{
							nObject->dwDL_Horse_Tick = GetTickCount();
							// ----
							// g_Msg.PM(aIndex, "first hit");
						}
						else
						{
							static DWORD dwCurTick; dwCurTick = GetTickCount();
							// ----
							if((dwCurTick - nObject->dwDL_Horse_Tick) < g_dwDLBestAttack)
							{
								g_dwDLBestAttack = (dwCurTick - nObject->dwDL_Horse_Tick);
								// -----
								g_HackLog.Output("[SpeedHack] :: [DL] Best : %d;PlayerName : %s;", g_dwDLBestAttack, gObj[aIndex].Name);
							}
							// ---
							if((dwCurTick - nObject->dwDL_Horse_Tick) < 9500)
							{
								g_HackLog.Output("[SpeedHack] :: [DL] HACK-DL-SKILL Cur : %d; PlayerName : %s;", (dwCurTick - nObject->dwDL_Horse_Tick), gObj[aIndex].Name);
							}
							else
							{
								g_HackLog.Output("[SpeedHack] :: [DL] Cur : %d; PlayerName : %s;", (dwCurTick - nObject->dwDL_Horse_Tick), gObj[aIndex].Name);
							}
							//	g_Msg.PM(aIndex, "Cur %d Best %d",  (dwCurTick - nObject->dwDL_Horse_Tick), g_dwDLBestAttack);
							// -----
							nObject->dwDL_Horse_Tick = GetTickCount();
						}
					}
					break;
				}
			}
			// ----
			if(nObject->FPS > 20)
			{
				g_HackLog.Output("[SpeedHack] :: [%s][%s][%s] [%d(%dx%d)]", gObj[aIndex].Name, nObject->szFPS, gObjGetClassName(aIndex), gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y);
				// ----
				for(int gmIndex = OBJECT_START_INDEX ; gmIndex != OBJECT_MAX_INDEX ; ++gmIndex)
				{
					if(gObjIsGameMaster(gmIndex) == true)
					{
						_NEW_OBJECT * nObject2		= & g_GS.nObject[NINDEX(gmIndex)];
						if(nObject2->isLogHackAllow == true)
						{
								g_Msg.Msg(gmIndex, "@[SpeedHack][%s][%d(%dx%d)]", gObj[aIndex].Name, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y);
						}
					}
				}
			}
		}
		break;
		
	}
	// ----
	if (gObj[aIndex].CloseType != -1)
	{
		if (gObj[aIndex].CloseCount != -1)
		{
			if (gObj[aIndex].CloseCount >= 2)
			{
				if (aRecv[2] == 0x1C)
				{
					closesocket(gObj[aIndex].m_socket);
					
				}
				
				//return;
			}
		}
		
	}
	
	if(bStop == false)
	{
		g_GS.ProtocolCore(protoNum, aRecv, aLen, aIndex, Encrypt, Serial);
	}
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
	OnConnect - Called When An User Get Connected

	@param aIndex int
	@return void
*/
void CCore::OnConnect(int aIndex)
{
	#ifdef GS_99_60T
	{
		// # Frist time connection to gameserver
		// ----
		if(CCore::isFirstTimeConnect == false)
		{
			// leo: bad should be loaded after option load/reload
			g_BotSystem.addBots();
			
			// ----
			g_GS.LogAdd("%s() first time user connected %s", __FUNCTION__, gObj[aIndex].Name);
			// ----
			CCore::isFirstTimeConnect = true;
		}		
	}
	#endif
	// ----
	// # Zero new object(addon to OBJECTSTRUCT)
	// ----
	ObjectSetZero(aIndex);
	// ----
	// # TODO : avoid all ifs and make something like that gEventManager.OnConnect(aIndex);
	// ----
	if(g_LOTTERYEVENT_STATE == true)
	{
		g_Msg.Msg(aIndex, "@איוונט נחש את המספר רץ כעת");
		g_Msg.Msg(aIndex, "@כדי לזכות באוונט אלייך לנחש את המספר המוגרל");
	}
	// ----
	if(g_RUNEVENT_STATE == true)
	{
		g_Msg.Msg(aIndex, "@איוונט רוץ ילד רוץ רץ כעת");
		g_Msg.Msg(aIndex, "@כדי לזכות באוונט אלייך להגיע לנקודת הציון הבאה");
		g_Msg.Msg(aIndex, "@%dx%d %s",g_RUNEVENT_CORD.X ,g_RUNEVENT_CORD.Y ,GetMapNameHeByID(g_RUNEVENT_CORD.Map));
	} 
	// ----
	if(g_FASTWROTE_STATE == true)
	{
		g_Msg.Msg(aIndex, "@איוונט זריזות רץ כעת");
		g_Msg.Msg(aIndex, "@כדי לזכות יש לרשום את המשפט הבא");
		g_Msg.Msg(aIndex, "@%s", g_WROTE_TEXT.c_str());
	}
	if(g_CONFUSEEVENT_STATE == true)
	{
		g_Msg.Msg(aIndex, "@איוונט מילים מבולבלות רץ כעת");
		g_Msg.Msg(aIndex, "@כדי לזכות יש לרשום את המשפט הבא בצורה נכונה");
		g_Msg.Msg(aIndex, "@%s", g_CONFUSE_WROTE_TEXT_WRONG.c_str());
	}
	// ----
	if (g_Config.KillEventStatus == true) // leo : Config should not have varibales (config varibales have to be changed only in 2 times (1 FIRST LOADING , 2 RELOADING)
	{
		g_Msg.Msg(aIndex, "@איוונט טופ קילר פעיל");
		// ----
		if (g_Config.KillEventDifClass == false)
			g_Msg.Msg(aIndex, "@ניתן להרוג רק את אותו סוג דמות");

		g_Msg.Msg(aIndex, "@%d :מינימום ריסט להשתתף", g_Config.KillEventMinRes);
		g_Msg.Msg(aIndex, "@%d :מקסימום הפרש בריסטים", g_Config.KillEventGapRes);
	}

	// ---- # Getting Marry Information from DSX

	if(g_Config.isGSCastle == false) 
	{
		if(g_DataServer.getStatus() == true)
		{
			GDCharacterGotOnlineOrOffline(aIndex, gObj[aIndex].AccountID, OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_ONLINE_PLAY);
			// ----
			GDExtraInfo(aIndex, gObj[aIndex].AccountID);
			// ----
			//GDGetMarryInfo (aIndex, gObj[aIndex].AccountID, gObj[aIndex].Name);
			LPCSTR Map = GetMapName(aIndex);
			// ----
			g_TradeLog.Output(TRADE_LOG_CONNECT,g_Config.nServerCode, gObj[aIndex].AccountID, gObj[aIndex].Name, Map, gObj[aIndex].X, gObj[aIndex].Y);
		}
		else
		{
			g_Msg.Notice(aIndex, "עקב בעיה טכנית אין באפשרותך להתחבר לשרת");
			g_Msg.Notice(aIndex, "נסה שוב בעוד מספר דקות");
			// ----
			g_GS.CloseClient(aIndex);
		}
	}
	else
	{
		GDCharacterGotOnlineOrOffline(aIndex, gObj[aIndex].AccountID, OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_CS_ONLINE);
	}
	// ----
	if(gObjIsGameMaster(aIndex) == true)
	{
		_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];

		nObject->canUseDisconnect	= true;
		nObject->canUseMove			= true;
		// ----
		// # FIX GameMaster Symbol (webzen fall)
		// ----
		if (gObjIsGameSI(aIndex) == false)
		{
			gObj[aIndex].m_ViewSkillState	|= 0x1000000;
		}
		// ----
		// # Printing a message login only for visible GMS.
		// ----
		if(gObj[aIndex].Authority == 2) {
			g_Msg.Msg(aIndex, "@You are INvisible");
		} else if(gObj[aIndex].Authority == 32) {
			g_Msg.Msg(aIndex, "@You are VISIBLE");
		}
		// ----
		#ifdef GS_99_60T
		{
			if (gObj[aIndex].Authority == 32 && strcmp(gObj[aIndex].Name, "YairNet") != 0)
			{
				if (gObjIsGameSI(aIndex) == false)
				{
					g_Msg.Msg(aIndex, "@Choose if you want to post that you login");
					g_Msg.Msg(aIndex, "@For YES: /y");
					g_Msg.Msg(aIndex, "@For NO: /n or anything else");

					g_GMLOGINID = aIndex;
				}
			}
		}
		#endif
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::OnDisconnect(int aIndex)
{
	#ifdef GS_99_60T
	{
		if (g_BotSystem.isThatBot(aIndex) == true)
		{
			return;
		}

		if(gObjIsGameMaster(aIndex) == true)
		{
			// # printing a message for logout only for visible GMS.
			// ----
			if((gObj[aIndex].Authority == 32))
			{
				if(gObjIsGameSI(aIndex) == false)
				{
					g_Msg.NoticeAll("%s Has Disconnected From The Server", gObj[aIndex].Name);
				}
			}
		}
	}
	#endif
	// ----
	if(gObj[aIndex].Type == OBJ_USER)
	{
		_NEW_OBJECT * nObject		= & g_GS.nObject[FIXINDEX];
		// ----
		nObject->Resets				= 0;
		nObject->isVip				= false;
		nObject->dwPostTick			= 0;
		// ----
		#ifdef GS_99_60T
		{
			// GS NORMAL
		}
		#else
		{
			char Temp[120] = {0}; 
			sprintf(Temp, "UPDATE Character SET MapNumber = 0, MapPosX = 239, MapPosY = 13 WHERE Name = '%s'", gObj[aIndex].Name);
			// ----
			boost::thread * thr = new boost::thread(boost::bind(& GDSendQuery, Temp));
		}
		#endif
	}
	// ----
	g_GS.gObjDel(aIndex);
	// ----
	memset(gObj[aIndex].Ip_addr, 0, 0x10);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::OnCloseClient(int aIndex)
{
	#ifdef GS_99_60T
	{
		if(g_BotSystem.isThatBot(aIndex) == true)
		{
			return;
		}
	}
	#endif
	// ----
	//g_GmsLog.Output("disconnect1 %s", gObj[aIndex].AccountID);
	if(g_BotSystem.isThatBot(aIndex) == false)
	{
		if(gObj[aIndex].Type == OBJ_USER)
		{
			//g_GmsLog.Output("disconnect %s", gObj[aIndex].AccountID);
			GDCharacterGotOnlineOrOffline(aIndex, gObj[aIndex].AccountID, OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_OFFLINE);
			if (g_OffTrade.EnableOff == true)
			{
				g_OffTrade.CloseClient(aIndex);
				return;
			}
		}
	}
	// ----
	g_GS.CloseClient(aIndex);
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::ResponErrorCloseClient(int aIndex)
{
	#ifdef GS_99_60T
	{
		if(g_BotSystem.isThatBot(aIndex) == true)
		{
			return;
		}
		if (g_OffTrade.EnableOff == true)
		{
			g_OffTrade.ResponErrorCloseClient(aIndex);
			return;
		}
		// ----
		g_GS.ResponErrorCloseClient(aIndex);
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOOL CCore::OngObjAdd(SOCKET aSocket, char * ip, int aIndex) 
{
	//GDChangeSumClients(1); // add user in the dsx
	BOOL ret = g_GS.gObjAdd(aSocket, ip, aIndex);
	// ----
	#define MAX_PER_IP 10
	// ----
	static USHORT	i;
	static BYTE		temp;
	// ----
	temp = 0;
	// ----
	for(i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
	{
		if(i == aIndex) continue;
		// ----
		if(strcmp(gObj[i].Ip_addr, ip) == 0)
		{
			++temp;
		}
		// ----
		if(temp >= MAX_PER_IP)
		{
			break;
		}
	}
	// ----
	if(temp >= MAX_PER_IP)
	{
		for(i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
		{
			if(strcmp(gObj[i].Ip_addr, ip) == 0)
			{											
				strcpy(gObj[i].Ip_addr, "0.0.0.0");
			}
		}
		// ----
		g_HackLog.Output("%s flood the server", ip);
	}
	// ----
	return ret;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::OnTeleport(int aIndex, int map, int x, int y)
{
	
	BYTE PetType		= gObj[aIndex].pInventory[8].m_Type;
	BYTE Ring1Type		= gObj[aIndex].pInventory[10].m_Type;
	BYTE Ring2Type		= gObj[aIndex].pInventory[11].m_Type;
	// ----
	if(gObj[aIndex].Energy >= 20000)
	{
		if((PetType == 0xA2) || (PetType == 0xA3) || (PetType == 0xA1))
		{
			g_Msg.Msg(aIndex, 1, "יש להוריד את החיה לפני השתגרות");	
			g_Msg.Msg(aIndex, 1, "you can't teleport while using dinorat or unricorn");
		}
		else if((Ring1Type == 0xB4) || (Ring2Type == 0xB4))
		{
			g_Msg.Msg(aIndex, 1, "לא ניתן לישתגר אם טבעת מסוג וויזרד");	
			g_Msg.Msg(aIndex, 1, "יש להוריד את הטבעת ולהישתגר מחדש");	
			g_Msg.Msg(aIndex, 1, "you can't teleport while using Wizard Ring");
		}
		else
		{
			g_GS.gObjTeleport(aIndex, map, x, y);
			// ----
			if(gObj[aIndex].Type == OBJ_USER)
			{
				REFRESH_INVENTORY;
			}
		}
	}
	else
	{
		g_GS.gObjTeleport(aIndex, map, x, y);
		// ----
		if(gObj[aIndex].Type == OBJ_USER)
		{
			REFRESH_INVENTORY;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOOL CCore::OnMoveGate(int aIndex, int gt)
{

	/*
	//g_Msg.Msg(aIndex, "%d",g_Config.nNoobServerCsResets);
	BYTE PetType		= gObj[aIndex].pInventory[8].m_Type;
	BYTE Ring1Type		= gObj[aIndex].pInventory[10].m_Type;
	BYTE Ring2Type		= gObj[aIndex].pInventory[11].m_Type;
	// ----
	_NEW_OBJECT * nObject		= & g_GS.nObject[FIXINDEX];
	//g_Msg.Msg(aIndex, "%d",gt);
	// ----
	if(gt == 102)
	{
		g_Msg.Msg(aIndex, "%d",g_Config.nNoobServerCsResets);
		if(g_Config.nNoobServerCsResets > 0 && gObjIsGameMaster(aIndex) == false)
		{
			g_Msg.Msg(aIndex, "IN 1");
			if(gObjCheckUserResets(aIndex,int(g_Config.nNoobServerCsResets)) == false)
			{
				g_Msg.Msg(aIndex, "IN 2");
				g_Msg.Msg(aIndex, "@[CS] אתה מנסה לעבור בכניסה ללורן מתחילים");
				g_Msg.Msg(aIndex, "@[CS] מעבר בשער מתאפשר רק לשחקנים");
				g_Msg.Msg(aIndex, "@[CS] %d שמספר הריסטים שלהם פחות מ", g_Config.nNoobServerCsResets);
				g_Msg.Msg(aIndex, "@[CS] שיגור רגיל ללורן ולי יתבצע דרך שרת 2");
				// ----
				return false;
			}
		}
		/*if(g_Config.bCsExSets == true && gObjIsGameMaster(aIndex) == false)
		{
			g_Msg.Msg(aIndex, "IN 2");
			OBJECTSTRUCT * lpObj = & gObj[aIndex];
			// ----
			for(int i = 0; i <= INVENTORY_SIZE; ++i)
			{
				// # Ex items +13 set dur to 255 (inventory)
				// ----
				if(lpObj->pInventory[i].m_Level >= 13)
				{
					if(lpObj->pInventory[i].m_NewOption == 0x3F)
					{
						g_Msg.Msg(aIndex, "@[CS] אתה מנסה לעבור בכניסה ללורן");
						g_Msg.Msg(aIndex, "@[CS] מעבר בשער מתאפשר רק לשחקנים");
						g_Msg.Msg(aIndex, "@[CS] ללא חפצים + הכל");
						g_Msg.Msg(aIndex, "@[CS] שיגור רגיל ללורן ולי יתבצע דרך שרת 2");

						return false;
					}
				}
			}/// נראה לי שסידרתי פשוט מקודם הורדתי כאן את הערות ואפשרתי את 2 הקודים cxsr
		}

		if(isMoveNGate(gt) == true)
		{
			gObjCastRegen(aIndex, gt);
		}
		return false;
	}
	// ----
	if(gObj[aIndex].Energy >= 20000)
	{
		if((PetType == 0xA2) || (PetType == 0xA3) || (PetType == 0xA1))
		{
			g_Msg.Msg(aIndex, 1, "יש להוריד את החיה לפני השתגרות");	
			g_Msg.Msg(aIndex, 1, "you can't teleport while using dinorat or unricorn");
			// ----
			if(isMoveNGate(gt) == true)
			{
				gObjCastRegen(aIndex, gt);
			}
			// ----
			return false;
		}
		else if((Ring1Type == 0xB4) || (Ring2Type == 0xB4))
		{
			g_Msg.Msg(aIndex, 1, "לא ניתן לישתגר אם טבעת מסוג וויזרד");	
			g_Msg.Msg(aIndex, 1, "יש להוריד את הטבעת ולהישתגר מחדש");	
			g_Msg.Msg(aIndex, 1, "you can't teleport while using Wizard Ring");
			// ----
			if(isMoveNGate(gt) == true)
			{
				gObjCastRegen(aIndex, gt);
			}
			// ----
			return false;
		}
		else
		{
			 return g_GS.gObjMoveGate(aIndex, gt);
		}
	}
	else
	{
		 return g_GS.gObjMoveGate(aIndex, gt);
	}
	// ---
	return false;*/

	BYTE PetType		= gObj[aIndex].pInventory[8].m_Type;
	BYTE Ring1Type		= gObj[aIndex].pInventory[10].m_Type;
	BYTE Ring2Type		= gObj[aIndex].pInventory[11].m_Type;
	// ----
	_NEW_OBJECT * nObject		= & g_GS.nObject[FIXINDEX];
	// ----
	if(gt == 102)
	{
		if(g_Config.nNoobServerCsResets > 0 && gObjIsGameMaster(aIndex) == false)
		{
			if(gObjCheckUserResets(aIndex,int(g_Config.nNoobServerCsResets)) == false)
			{
				g_Msg.Msg(aIndex, "@[CS] אתה מנסה לעבור בכניסה ללורן מתחילים");
				g_Msg.Msg(aIndex, "@[CS] מעבר בשער מתאפשר רק לשחקנים");
				g_Msg.Msg(aIndex, "@[CS] %d שמספר הריסטים שלהם פחות מ", g_Config.nNoobServerCsResets);
				g_Msg.Msg(aIndex, "@[CS] שיגור רגיל ללורן ולי יתבצע דרך שרת 2");
				// ----
				if(isMoveNGate(gt) == true)
				{
					gObjCastRegen(aIndex, gt);
				}
				// ----
				return false;
			}
		}
		if(g_Config.bCsExSets == true && gObjIsGameMaster(aIndex) == false)
		{
			OBJECTSTRUCT * lpObj = & gObj[aIndex];
			// ----
			for(int i = 0; i <= INVENTORY_SIZE; ++i)
			{
				// # Ex items +13 set dur to 255 (inventory)
				// ----
				if(lpObj->pInventory[i].m_Level >= 13)
				{
					if(lpObj->pInventory[i].m_NewOption == 0x3F)
					{
						g_Msg.Msg(aIndex, "@[CS] אתה מנסה לעבור בכניסה ללורן");
						g_Msg.Msg(aIndex, "@[CS] מעבר בשער מתאפשר רק לשחקנים");
						g_Msg.Msg(aIndex, "@[CS] ללא חפצים + הכל");
						g_Msg.Msg(aIndex, "@[CS] שיגור רגיל ללורן ולי יתבצע דרך שרת 2");

						if(isMoveNGate(gt) == true)
						{
							gObjCastRegen(aIndex, gt);
						}
						// ----
						return false;
					}
				}
			}
		}
	}
	// ----
	if(gObj[aIndex].Energy >= 20000)
	{
		if((PetType == 0xA2) || (PetType == 0xA3) || (PetType == 0xA1))
		{
			g_Msg.Msg(aIndex, 1, "יש להוריד את החיה לפני השתגרות");	
			g_Msg.Msg(aIndex, 1, "you can't teleport while using dinorat or unricorn");
			// ----
			if(isMoveNGate(gt) == true)
			{
				gObjCastRegen(aIndex, gt);
			}
			// ----
			return false;
		}
		else if((Ring1Type == 0xB4) || (Ring2Type == 0xB4))
		{
			g_Msg.Msg(aIndex, 1, "לא ניתן לישתגר אם טבעת מסוג וויזרד");	
			g_Msg.Msg(aIndex, 1, "יש להוריד את הטבעת ולהישתגר מחדש");	
			g_Msg.Msg(aIndex, 1, "you can't teleport while using Wizard Ring");
			// ----
			if(isMoveNGate(gt) == true)
			{
				gObjCastRegen(aIndex, gt);
			}
			// ----
			return false;
		}
		else
		{
			 return g_GS.gObjMoveGate(aIndex, gt);
		}
	}
	else
	{
		 return g_GS.gObjMoveGate(aIndex, gt);
	}
	// ---
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOOL CCore::OnPointAdd(BYTE type, OBJECTSTRUCT * lpObj)
{
	BOOL bReturn = TRUE;
	// ----
	switch(type)
	{
		case 0:
		{
			if(lpObj->Strength >= 32767)
			{
				bReturn = FALSE;
			}
		}
		break;

		case 1:
		{
			if(lpObj->Dexterity >= 32767)
			{
				bReturn = FALSE;
			}
		}
		break;

		case 2:
		{
			if(lpObj->Vitality >= 32767)
			{
				bReturn = FALSE;
			}
		}
		break;

		case 3:
		{
			if(lpObj->Energy >= 32767)
			{
				bReturn = FALSE;
			}
		}
		break;

		case 4:
		{
			if(lpObj->Leadership >= 32767)
			{
				bReturn = FALSE;
			}
		}
		break;
	}
	// ----
	if(bReturn == TRUE)
	{
		bReturn = g_GS.gObjLevelUpPointAdd(type, lpObj);
	}
	else
	{
		g_Msg.Msg(lpObj->m_Index, 1, "you can't add more then 32767 point(s)");
	}
	// ----
	return bReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::OnTraceCancel(int aIndex)
{
	g_GS.gObjTradeCancel(aIndex);
	// ----
	REFRESH_INVENTORY;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::GCTradeResponseSend(BYTE response, int aIndex, LPSTR id, WORD level, int GuildNumber)
{
	int tIndex = -1;
	char tAccountName[11] = {0};
	BYTE X, Y, MAP;
	// ----
	tIndex = gObj[aIndex].TargetNumber;
	if((tIndex < OBJECT_START_INDEX) || (tIndex > OBJECT_MAX_INDEX))
	{
		memcpy(tAccountName,	"",		sizeof(""));
		X = 0;
		Y = 0;
		MAP = 0;
	}
	else
	{
		memcpy(tAccountName,	gObj[tIndex].AccountID,		sizeof(gObj[tIndex].AccountID));
		X = gObj[tIndex].X;
		Y = gObj[tIndex].Y;
		MAP = gObj[tIndex].MapNumber;
	}
	if (response == 1)
	{
		g_TradeLog.Output(TRADE_LOG_TRADE_MESSAGE_FORMAT, g_Config.nServerCode, gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[aIndex].Ip_addr, GetMapNameByID(gObj[aIndex].MapNumber), gObj[aIndex].X, gObj[aIndex].Y, tAccountName, id, gObj[tIndex].Ip_addr, GetMapNameByID(MAP), X, Y);
	}

	g_GS.GCTradeResponseSend(response, aIndex, id, level, GuildNumber);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGTradeRequestSend(PMSG_TRADE_REQUEST * lpMsg, int aIndex)
{
	g_GS.CGTradeRequestSend((DWORD)lpMsg, aIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGPShopReqSetItemPrice(PMSG_REQ_PSHOP_SETITEMPRICE * lpMsg, int aIndex)
{
	#ifdef GS_99_60T
	{
		OBJECTSTRUCT * lpObj = & gObj[aIndex];
		// ----
		int iITEM_LOG_TYPE = lpObj->pInventory[lpMsg->btItemPos].m_Type;
		int iITEM_LOG_LEVEL =  lpObj->pInventory[lpMsg->btItemPos].m_Level;
		int iITEM_LOG_DUR =  lpObj->pInventory[lpMsg->btItemPos].m_Durability;
		int iITEM_LOG_SERIAL =  lpObj->pInventory[lpMsg->btItemPos].m_Number;
		// ----
		BYTE iITEM_LOG_OPTION_1 = lpObj->pInventory[lpMsg->btItemPos].m_Option1;
		BYTE iITEM_LOG_OPTION_2 = lpObj->pInventory[lpMsg->btItemPos].m_Option2;
		BYTE iITEM_LOG_OPTION_3 = lpObj->pInventory[lpMsg->btItemPos].m_Option3;
		BYTE iITEM_LOG_NEW_OPTION = lpObj->pInventory[lpMsg->btItemPos].m_NewOption;
		// ----
		if(iITEM_LOG_NEW_OPTION == 0x3F && iITEM_LOG_LEVEL >= 13)
		{
			_NEW_OBJECT * nObject		= & g_GS.nObject[FIXINDEX];
			// ----
			if (nObject->isAgreeShopping == true)
			{
				g_GS.CGPShopReqSetItemPrice((DWORD)lpMsg,aIndex);
			}
			else
			{
				g_Msg.Msg(aIndex, "@ישנה חסימה כנגד הכנסת חפצים +הכל לחנות");
				g_Msg.Msg(aIndex, "@צוות המשחק ממליץ לא להכניס חפצים לחנות!");
				g_Msg.Msg(aIndex, "@חפצים מהחנות עלולים להימחק עקב בעיות בשרת");
				g_Msg.Msg(aIndex, "@הכנסת החפצים היא באחריות השחקן בלבד!");
				g_Msg.Msg(aIndex, "@להורדת ההגנה יש לכתוב את הפקודה");
				g_Msg.Msg(aIndex, "@/sellItem on");
				g_GS.CGPShopAnsSetItemPrice(aIndex, 2, lpMsg->btItemPos);
			}

		}
		else
		{
			g_GS.CGPShopReqSetItemPrice((DWORD)lpMsg,aIndex);
		}
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGPShopReqBuyItem(PMSG_REQ_BUYITEM_FROM_PSHOP * lpMsg, int aSourceIndex)
{
	#ifdef GS_99_60T
	{
		int aIndex = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);
		// ----
		OBJECTSTRUCT * lpObj = & gObj[MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL)];
		// ----
		int iITEM_LOG_TYPE = lpObj->pInventory[lpMsg->btItemPos].m_Type;
		int iITEM_LOG_LEVEL =  lpObj->pInventory[lpMsg->btItemPos].m_Level;
		int iITEM_LOG_DUR =  lpObj->pInventory[lpMsg->btItemPos].m_Durability;
		int iITEM_LOG_SERIAL =  lpObj->pInventory[lpMsg->btItemPos].m_Number;
		// ----
		BYTE iITEM_LOG_OPTION_1 = lpObj->pInventory[lpMsg->btItemPos].m_Option1;
		BYTE iITEM_LOG_OPTION_2 = lpObj->pInventory[lpMsg->btItemPos].m_Option2;
		BYTE iITEM_LOG_OPTION_3 = lpObj->pInventory[lpMsg->btItemPos].m_Option3;
		BYTE iITEM_LOG_NEW_OPTION = lpObj->pInventory[lpMsg->btItemPos].m_NewOption;
		// ----
		if(iITEM_LOG_NEW_OPTION == 0x3F && iITEM_LOG_LEVEL >= 13)
		{
			_NEW_OBJECT * nObject		= & g_GS.nObject[FIXINDEX];
			// ----
			if (nObject->isAllowToSellPlusAll == true)
			{
				g_GS.CGPShopReqBuyItem((DWORD)lpMsg, aSourceIndex);
			}
			else
			{
				g_GS.CGPShopAnsBuyItem(aSourceIndex, aIndex, 0,6);
				g_Msg.Msg(aSourceIndex, 1, "לא ניתן לקנות חפצים +הכל");
			}

		}
		else
		{
			g_GS.CGPShopReqBuyItem((DWORD)lpMsg, aSourceIndex);
		}
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGPShopAnsSoldItem(int aSourceIndex, int aTargetIndex, int iItemPos)
{
	char tAccountName[11] = {0};
	char tName[11] = {0};
	BYTE tX, tY, tMAP;
	char sAccountName[11] = {0};
	char sName[11] = {0};
	BYTE sX, sY, sMAP;

	// ----
	if((aTargetIndex < OBJECT_START_INDEX) || (aTargetIndex > OBJECT_MAX_INDEX))
	{
		memcpy(tAccountName,	"",		sizeof(""));
		memcpy(tName,			"",		sizeof(""));
		tX = 0;
		tY = 0;
		tMAP = 0; 
	}
	else
	{
		memcpy(tAccountName,	gObj[aTargetIndex].AccountID,	sizeof(gObj[aTargetIndex].AccountID));
		memcpy(tName,			gObj[aTargetIndex].Name,		sizeof(gObj[aTargetIndex].Name));
		tX = gObj[aTargetIndex].X;
		tY = gObj[aTargetIndex].Y;
		tMAP = gObj[aTargetIndex].MapNumber; 
	}
	// ----
	if((aSourceIndex < OBJECT_START_INDEX) || (aSourceIndex > OBJECT_MAX_INDEX))
	{
		memcpy(sAccountName,	"",		sizeof(""));
		memcpy(sName,			"",		sizeof(""));
		sX = 0;
		sY = 0;
		sMAP = 0; 
	}
	else
	{
		memcpy(sAccountName,	gObj[aSourceIndex].AccountID,	sizeof(gObj[aSourceIndex].AccountID));
		memcpy(sName,			gObj[aSourceIndex].Name,		sizeof(gObj[aSourceIndex].Name));
		sX = gObj[aSourceIndex].X;
		sY = gObj[aSourceIndex].Y;
		sMAP = gObj[aSourceIndex].MapNumber; 
	}
	g_ShopLog.Output(TRADE_LOG_SHOP_MESSAGE_FORMAT, g_Config.nServerCode, sAccountName, sName, GetMapNameByID(sMAP), sX, sY, tAccountName, tName, GetMapNameByID(tMAP), tX, tY);
	// ----
	g_GS.CGPShopAnsSoldItem(aSourceIndex, aTargetIndex, iItemPos);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGPShopAnsOpen(int aIndex, BYTE btResult)
{
	char sAccountName[11] = {0};
	char sName[11] = {0};
	BYTE X, Y, MAP;
	// ----
	if((aIndex < OBJECT_START_INDEX) || (aIndex > OBJECT_MAX_INDEX))
	{
		memcpy(sAccountName,	"",		sizeof(""));
		memcpy(sName,			"",		sizeof(""));
		X = 0;
		Y = 0;
		MAP = 0; 
	}
	else
	{
		memcpy(sAccountName,	gObj[aIndex].AccountID,		sizeof(gObj[aIndex].AccountID));
		memcpy(sName,			gObj[aIndex].Name,			sizeof(gObj[aIndex].Name));
		X = gObj[aIndex].X;
		Y = gObj[aIndex].Y;
		MAP = gObj[aIndex].MapNumber; 
	}
	if (btResult == 1)
	{
		g_ShopLog.Output(TRADE_LOG_SHOP_MESSAGE_OPEN_FORMAT, g_Config.nServerCode, gObj[aIndex].AccountID, gObj[aIndex].Name, GetMapNameByID(MAP), X, Y);
	}

	g_GS.CGPShopAnsOpen(aIndex, btResult);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGPShopAnsClose(int aIndex, BYTE btResult)
{

	if (g_OffTrade.EnableOff == true)
	{
		g_OffTrade.CGPShopAnsClose(aIndex, btResult);
		return;
	}

	char sAccountName[11] = {0};
	char sName[11] = {0};
	BYTE X, Y, MAP;
	
	// ----
	if((aIndex < OBJECT_START_INDEX) || (aIndex > OBJECT_MAX_INDEX))
	{
		memcpy(sAccountName,	"",		sizeof(""));
		memcpy(sName,			"",		sizeof(""));
		X = 0;
		Y = 0;
		MAP = 0;
	}
	else
	{
		memcpy(sAccountName,	gObj[aIndex].AccountID,		sizeof(gObj[aIndex].AccountID));
		memcpy(sName,			gObj[aIndex].Name,			sizeof(gObj[aIndex].Name));
		X = gObj[aIndex].X;
		Y = gObj[aIndex].Y;
		MAP = gObj[aIndex].MapNumber; 
	}
	if (btResult == 1)
	{
		g_ShopLog.Output(TRADE_LOG_SHOP_MESSAGE_CLOSE_FORMAT, g_Config.nServerCode, gObj[aIndex].AccountID, gObj[aIndex].Name, GetMapNameByID(MAP), X, Y);
	}
	g_GS.CGPShopAnsClose(aIndex, btResult);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::PMoveProc(DWORD unk,  int aIndex)
{
	if (gObj[aIndex].CloseType != -1)
	{
		return;
	}
	#ifdef GS_99_60T
	{
		g_GS.PMoveProc(unk, aIndex);
		// ----
		// to add move log hack
		// -----
		if(g_RUNEVENT_STATE == true)
		{
			OBJECTSTRUCT * lpObj = & gObj[aIndex];
			// ----
			if(lpObj->Type == OBJ_USER)
			{
				if((lpObj->MapNumber == g_RUNEVENT_CORD.Map) &&
					(lpObj->TX == g_RUNEVENT_CORD.X) &&
					(lpObj->TY == g_RUNEVENT_CORD.Y))
				{
					GDRunEventWinnerSend(aIndex);
				}
			}
		}
	}
	#endif
	// ----
	//if(gObjIsGameMaster(aIndex) == true)ObjectCapturePlayerPoint(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].TX, gObj[aIndex].TY);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOOL CCore::gObjAttack(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj, DWORD lpMagic, BOOL magicsend, BYTE MSBFlag, int AttackDamage, BOOL bCombo)
{
	BOOL bReturn = TRUE;
	// ----
	if(gObjIsGameMaster(lpTargetObj->m_Index) != true && strstr(gObj[lpTargetObj->m_Index].GuildName, "Mefakhim") != NULL)
	{
		bReturn = false;
	}
	else if (gObjIsGameMaster(lpTargetObj->m_Index) == true)
	{
		_NEW_OBJECT * nObject		= & g_GS.nObject[NINDEX(lpTargetObj->m_Index)];

		if (nObject->isImmortal == true)
			bReturn = false;
		else
		{
			bReturn = g_GS.gObjAttack(lpObj, lpTargetObj, lpMagic	, magicsend, MSBFlag, AttackDamage, bCombo);

			#ifdef GS_99_60T
			if(lpObj->Type == OBJ_USER && lpObj->Class == 2)
			{
				_NEW_OBJECT * nObject		= & g_GS.nObject[NINDEX(lpObj->m_Index)];
				if(nObject->isVip)
				{
					if(lpObj->pInventory[1].m_Type == ITEMGET(4, 7))
					{
						lpObj->pInventory[1].m_Durability = 255.0f;
						g_GS.GCItemDurSend(lpObj->m_Index, 1, lpObj->pInventory[1].m_Durability, 0);
					}
					else if(lpObj->pInventory[0].m_Type == ITEMGET(4, 15))
					{
						lpObj->pInventory[0].m_Durability = 255.0f;
						g_GS.GCItemDurSend(lpObj->m_Index, 1, lpObj->pInventory[0].m_Durability, 0);
					}
				}
			}
			#endif
			return bReturn;
		}
	}
	else
	{
		bReturn = g_GS.gObjAttack(lpObj, lpTargetObj, lpMagic, magicsend, MSBFlag, AttackDamage, bCombo);

		#ifdef GS_99_60T
		if(lpObj->Type == OBJ_USER && lpObj->Class == 2)
		{
			_NEW_OBJECT * nObject		= & g_GS.nObject[NINDEX(lpObj->m_Index)];
			if(nObject->isVip)
			{
				if(lpObj->pInventory[1].m_Type == ITEMGET(4, 7))
				{
					lpObj->pInventory[1].m_Durability = 255.0f;
					g_GS.GCItemDurSend(lpObj->m_Index, 1, lpObj->pInventory[1].m_Durability, 0);
				}
				else if(lpObj->pInventory[0].m_Type == ITEMGET(4, 15))
				{
					lpObj->pInventory[0].m_Durability = 255.0f;
					g_GS.GCItemDurSend(lpObj->m_Index, 1, lpObj->pInventory[0].m_Durability, 0);
				}
			}
		}
		#endif
		return bReturn;
	}
	// ----
	return bReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::gObjUserDie(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj)
{
	if(lpObj->Type == OBJ_NPC && lpTargetObj->Type == OBJ_USER )
	{
		return;
	}
	// ----
	g_GS.gObjUserDie(lpObj, lpTargetObj);
	// ----
	int aIndex = lpObj->m_Index;
	// ----
	REFRESH_INVENTORY;
	// ----
	#ifndef GS_99_60T /* IF NOT GS NORMAL */
	// ----
	static SYSTEMTIME strSystime;
	// ----
	if((lpObj->Type == OBJ_USER) && (lpTargetObj->Type == OBJ_USER))
	{
		static char Temp[1024];
		static char Temp2[1024];
		ZeroMemory(Temp, 1024);
		ZeroMemory(Temp2, 1024);
		// ----
		sprintf(Temp2, "[%s][%s][%d][%d] KILLED [%s][%s][%d][%d]", lpTargetObj->Name, lpTargetObj->GuildName, lpTargetObj->X, lpTargetObj->Y,
			lpObj->Name, lpObj->GuildName, lpObj->X, lpObj->Y);
		// ----
		_beginthread(ObjectLogKill, 4, (LPVOID) Temp2);
		// ----
		GetLocalTime(& strSystime);
		// ----
		wsprintf(Temp, "[%d:%d:%d] %s Killed %s", strSystime.wHour, strSystime.wMinute, strSystime.wSecond,
				lpTargetObj->Name, lpObj->Name);
		// ----
		for(int i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
		{
			if(gObj[i].Type == OBJ_USER)
			{
				_NEW_OBJECT * nObject		= & g_GS.nObject[NINDEX(i)];
				// ----
				if(nObject->isLogKillerAllow == true)
				{
					g_Msg.Msg(i, Temp);
				}
			}
		}
	}
	// ----
	#else
	if ((lpObj->Type == OBJ_USER) && (lpTargetObj->Type == OBJ_USER) && g_Config.KillEventStatus && gObjCheckUserResetsGap (lpObj->m_Index, lpTargetObj->m_Index, g_Config.KillEventMinRes, g_Config.KillEventGapRes, g_Config.KillEventDifClass))
	{
		GDKillEventCheck(lpObj->Name, lpTargetObj->Name);
	}

	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::gObjPlayerKiller(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj)
{
	if(lpObj->Type == OBJ_NPC && lpTargetObj->Type == OBJ_USER )
	{
		return;
	}
	#ifdef GS_99_60T
		{
		// ----
		int aIndex = lpObj->m_Index;
		// ----
		if((lpObj->Type == OBJ_USER) && (lpTargetObj->Type == OBJ_USER))
		{
			if (!gObjIsGameMaster(aIndex))
				g_GS.gObjPlayerKiller((DWORD)lpObj, (DWORD)lpTargetObj);
		}
		}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
	gObjMonsterDieGiveItem - Called When monster die and it shhould be gived

	@param lpObj OBJECTSTRUCT * - The monster
	@param lpTargetObj OBJECTSTRUCT * - Player last hit 
	@return void
*/
void CCore::gObjMonsterDieGiveItem(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj)
{
	#ifdef GS_99_60T
	if (lpObj->Class == 42 && g_RedDragon.bIsActive == true)
	{
		g_RedDragon.redDragonMutex.lock();
		if (g_RedDragon.bIsActive == true)
		{						
			//int MaxHitUser = g_GS.gObjMonsterTopHitDamageUser((DWORD)lpObj);
			g_RedDragon.GiveRedDragonPrize(lpTargetObj);
			g_RedDragon.redDragonMutex.unlock();
			return;			
		}
		g_RedDragon.redDragonMutex.unlock();

	}

	if (g_Config.IsGoldenGiveCredit != false)
	{
		switch (lpObj->Class)
		{
		case 53: // golden titan
		case 78: // golden goblin
		case 79: // golden derkon
		case 80: // golden lizard
		case 82: // golden tanalos

			static char Query[MAX_TEXT_LEN] = { 0 };

			// # Here it gets who gived the most damage to the dead monster
			// ----
			int MaxHitUser = g_GS.gObjMonsterTopHitDamageUser((DWORD)lpObj);

			sprintf(Query, "UPDATE MEMB_INFO SET Credits = Credits + 1 WHERE memb___id = '%s'", lpTargetObj->AccountID);
			GDSendQuery(Query);

			g_Msg.NoticeAll("%s הרג את המפלצת המוזהבת!", lpTargetObj->Name);
			g_Msg.Notice(MaxHitUser, "[Golden] You win 1 Credit(s)");
		}
	}
	g_GS.gObjMonsterDieGiveItem((DWORD)lpObj, (DWORD)lpTargetObj);

	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGInventoryItemMove(PMSG_INVENTORYITEMMOVE * lpMsg, int aIndex)
{
	static bool Stop;
	// ----
	Stop = false;
	// ----
	if(g_Config.isGSUseItemLimit == true)
	{
		switch(lpMsg->target_item_num)
		{
			case 8:
			case 10:
			case 11:
			{
				switch(lpMsg->sItemInfo[0])
				{
					#ifndef GS_99_60T
					case 0xAA: // ring trans
					// ----
					#endif
					case 0xA0:
					case 0xA1:
					case 0xA2:
					case 0xA3:
					case 0xB4:
					{
						if(gObj[aIndex].Dexterity >= 10000)
						{
								static PMSG_INVENTORYITEMMOVE_RESULT pMsg;
								// ----
								pMsg.h.c			= 0xC3;
								pMsg.h.headcode		= 0x24;
								pMsg.h.size			= sizeof(pMsg);
								pMsg.result			= -1;
								pMsg.Pos			= lpMsg->source_item_num;
								// ----
								memcpy(pMsg.ItemInfo, lpMsg->sItemInfo, sizeof(pMsg.ItemInfo));
								// ----
								g_GS.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
								// ----
								g_Msg.Msg(aIndex, "@[Item] החפץ מיועד לשחקנים חלשים בלבד");
								// ----
								Stop = true;
						}
					}
					break;					
				}
			}
			break;
		}
	}
	if ((lpMsg->target_item_num >= 76 && lpMsg->target_item_num <=107) && lpMsg->tFlag == 4)
	{
		OBJECTSTRUCT * lpObj = & gObj[aIndex];
		// ----
		if (lpObj->pInventory[lpMsg->source_item_num].m_Level == 13 && lpObj->pInventory[lpMsg->source_item_num].m_NewOption == 0x3F)
		{
			_NEW_OBJECT * nObject		= & g_GS.nObject[FIXINDEX];
			// ----
			if (nObject->isAgreeShopping == false)
			{
				/*g_Msg.Msg(aIndex, "@ישנה חסימה כנגד הכנסת חפצים +הכל לחנות");
				g_Msg.Msg(aIndex, "@צוות המשחק ממליץ לא להכניס חפצים לחנות!");
				g_Msg.Msg(aIndex, "@חפצים מהחנות עלולים להימחק עקב בעיות בשרת");
				g_Msg.Msg(aIndex, "@הכנסת החפצים היא באחריות השחקן בלבד!");
				g_Msg.Msg(aIndex, "@להורדת ההגנה יש לכתוב את הפקודה");
				g_Msg.Msg(aIndex, "@/sellItem on");*/
				// ----
				static PMSG_INVENTORYITEMMOVE_RESULT pMsg;
				// ----
				pMsg.h.c			= 0xC3;
				pMsg.h.headcode		= 0x24;
				pMsg.h.size			= sizeof(pMsg);
				pMsg.result			= -1;
				pMsg.Pos			= lpMsg->source_item_num;
				// ----
				memcpy(pMsg.ItemInfo, lpMsg->sItemInfo, sizeof(pMsg.ItemInfo));
				// ----
				g_GS.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
				// ----
				Stop = true;
			}
		}
	}
	// ----
	if(Stop == false)
	{
		#ifdef GS_99_60T
		{
			_asm
			{
				MOV EDI, 0x42F680
				MOV ECX, aIndex
				PUSH ECX
				MOV EDX, lpMsg
				PUSH EDX
				CALL Edi
				ADD ESP,8H
			}
		}
		#else
		{
			_asm
			{
				MOV EDI, 0x432FF0
				MOV ECX, aIndex
				PUSH ECX
				MOV EDX, lpMsg
				PUSH EDX
				CALL Edi
				ADD ESP,8H
			}
		}
		#endif
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::GDGuildMemberDelResult(SDHP_GUILDMEMBERDEL_RESULT * lpMsg)
{
	#ifdef GS_99_60T
	{
		g_GS.GDGuildMemberDelResult((DWORD)lpMsg);
		// ----
		char Temp[11] = {0};
		// ----
		memcpy(Temp, lpMsg->MemberID , sizeof(lpMsg->MemberID));
		// ----
		int aIndex = gObjGetIndexByName(Temp);
		// ----
		if(aIndex != 0)
		{
			memset(gObj[aIndex].GuildName, 0 , MAX_ACCOUNT_LEN);
		}
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::GDGuildMemberAddResult(SDHP_GUILDMEMBERADD_RESULT * lpMsg)
{
	#ifdef GS_99_60T
	{
		g_GS.GDGuildMemberAddResult((DWORD)lpMsg);
		// ----
		char Temp[11] = {0};
		// ----
		memcpy(Temp, lpMsg->MemberID , sizeof(lpMsg->MemberID));
		// ----
		int aIndex = gObjGetIndexByName(Temp);
		// ----
		if(aIndex != 0)
		{
			g_GS.DGGuildMemberInfoRequest(aIndex);
		}
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGPCharDel(PMSG_CHARDELETE * lpMsg, int aIndex)
{
	MSG_S_DELCHAR pMsg = {0};
	// ----
	HeadSet1(& pMsg.Head, sizeof(pMsg), HEAD_DELCHAR);
	// ----
	pMsg.PlayerIndex = aIndex;
	// ----
	memcpy(& pMsg.pMsgCharDel, lpMsg, sizeof(pMsg.pMsgCharDel));
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOOL CCore::gObjSetCharacter(DWORD Msg, int aIndex)
{
	BOOL bReturn = g_GS.gObjSetCharacter(Msg, aIndex);
	// ----
	OBJECTSTRUCT * lpObj = & gObj[aIndex];
	// ----
	for(int i = 0; i <= INVENTORY_SIZE; ++i)
	{
		// # Ex items +13 set dur to 255 (inventory)
		// ----
		if(lpObj->pInventory[i].m_Level >= 13)
		{
			if(lpObj->pInventory[i].m_NewOption == 0x3F)
			{
				lpObj->pInventory[i].m_Durability = 255.0f;
			}
		}
	}
	// ----
	for(int i = 0; i <= WAREHOUSE_SIZE; ++i)
	{
		// # Ex items +13 set dur to 255 (warehose)
		// ----
		if(lpObj->pWarehouse[i].m_Level >= 13)
		{
			if(lpObj->pWarehouse[i].m_NewOption == 0x3F)
			{
				lpObj->pWarehouse[i].m_Durability = 255.0f;
			}
		}
	}
	// ----
	return bReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::DGGetWarehouseList(SDHP_GETWAREHOUSEDB_SAVE * lpMsg)
{
	g_GS.DGGetWarehouseList(DWORD(lpMsg));
	// ----
	OBJECTSTRUCT * lpObj = & gObj[lpMsg->aIndex];
	// ----
	for(int i = 0; i <= WAREHOUSE_SIZE; ++i)
	{
		// # Ex items +13 set dur to 255 (warehose)
		// ----
		if(lpObj->pWarehouse[i].m_Level >= 13)
		{
			if(lpObj->pWarehouse[i].m_NewOption == 0x3F)
			{
				lpObj->pWarehouse[i].m_Durability = 255.0f;
				
			}
		}
	}
	// ----
	g_GS.GCUserWarehouseSend(lpObj);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOOL CCore::DataSend(int aIndex, UCHAR * lpMsg, DWORD dwSize)
{
	#ifdef GS_99_60T
	{
		if(g_BotSystem.isThatBot(aIndex) == true)
		{
			return TRUE;
		}
	}
	#endif
	// ----
	BOOL bReturn = g_GS.DataSend(aIndex, lpMsg, dwSize);
	// ----
	//#define HANDLE_SEND_PACKETS
	#ifdef	HANDLE_SEND_PACKETS
	{
		char btTemp[1024 * 3] = {0};
		// ----
		sprintf(btTemp, "Packet : ");
		// ----
		for(int i = 0 ; i != dwSize ; ++i)
		{
			if(lpMsg[i] > 9)
			{
				sprintf(btTemp, "%s %X", btTemp, lpMsg[i]);
			}
			else
			{
				sprintf(btTemp, "%s 0%X", btTemp, lpMsg[i]);
			}
		}
		// ----
		g_HackLog.Output(btTemp);
	}
	#endif
	// ----
	return bReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::GCJoinResult(BYTE result, int aIndex)
{
	// # Function for gs normal )ONLY(
	// ----
	#ifdef GS_99_60T
	{
		g_GS.GCJoinResult(result,aIndex);
		// ----
		if(result == 0x01)
		{
			// # Send packet to the dataserverx 
			// # infrom about account connected succesfuly
			GDCharacterGotOnlineOrOffline(aIndex, gObj[aIndex].AccountID, OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_ONLINE);
		}
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::JGPGetCharList(UCHAR * lpRecv)
{
	g_GS.JGPGetCharList(lpRecv);
	// ----
	SDHP_CHARLISTCOUNT * lpCount	= (SDHP_CHARLISTCOUNT *)lpRecv;
	// ----
	// # Send packet to the dataserverx 
	// # infrom about select charachter login
	// ----
	GDCharacterGotOnlineOrOffline(lpCount->Number, gObj[lpCount->Number].AccountID, OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_CHARSELECT);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGPCharacterCreate(PMSG_CHARCREATE * lpMsg, int aIndex)
{
	char szNick[11] = {0};
	// ----
	memcpy(& szNick, lpMsg->Name, sizeof(lpMsg->Name));
	// ----
	//g_GmsLog.Output("check check %s", szNick);
	// ----
	if (!g_Config.UnAllowedNamesCheck (szNick))
	{
		g_GS.GCServerMsgStringSend((char *) "UnAllowed Nick", aIndex, 1);
		g_GS.JGCharacterCreateFailSend(aIndex,(DWORD)lpMsg);
	}
	else if(!ObjectCheckUnAllowedChars(szNick))
	{
		g_HackLog.Output(HACK_LOG_UNALLOWEDCHARACTER, gObj[aIndex].AccountID, szNick);
		g_GS.GCServerMsgStringSend((char *) "UnAllowed Chars", aIndex, 1);
		g_GS.JGCharacterCreateFailSend(aIndex,(DWORD)lpMsg);
	}
	else
	{
		g_GS.CGPCharacterCreate((DWORD)lpMsg, aIndex);
		// ----
		// CharacterGotOnlineOrOffline (aIndex, gObj[aIndex].AccountID, OFFLINE_ONLINE_STATUS::OFFLINE_ONLINE_STATUS_CREATE_CHAR);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::gObjCloseSetEx(int aIndex,int Flag) // Select Characters // FLAG 0 - CLOSE GAME FLAGE 1 SERVER SELECT FLAGE 2 CHAR SELECT
{
	g_GS.gObjCloseSet(aIndex,Flag);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::FriendMemoSend(PMSG_FRIEND_MEMO * lpMsg, int aIndex)
{
	char mail[1000];
	// ----
	memcpy(mail, lpMsg->Memo, lpMsg->MemoSize);
	// ----
	g_MailLog.Output(MAIL_LOG_MESSAGE_FORMAT, g_Config.nServerCode, gObj[aIndex].Name, lpMsg->Name, lpMsg->Subject, mail);
	g_GS.FriendMemoSend((DWORD)lpMsg, aIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGGuildRequestResultRecv(PMSG_GUILDQRESULT * lpMsg, int aIndex)
{
	#ifdef GS_99_60T
	{
		int number	= -1;
		number = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);
		// ----
		g_GS.CGGuildRequestResultRecv((DWORD)lpMsg, aIndex);
		// ----
		if(number >= OBJECT_START_INDEX && number <= OBJECT_MAX_INDEX)
		{
			if((gObj[number].m_IfState.use) && (gObj[number].m_IfState.type == 4))
			{
				gObj[number].m_IfState.use = 0;
			}
		}
		if(aIndex >= OBJECT_START_INDEX && aIndex <= OBJECT_MAX_INDEX)
		{
			if((gObj[aIndex].m_IfState.use) && (gObj[aIndex].m_IfState.type == 4))
			{
				gObj[aIndex].m_IfState.use = 0;
			}
		}	
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGLiveClient(PMSG_CLIENTTIME * lpClientTime, int aIndex)
{
	if (gObj[aIndex].m_AttackSpeedHackDetectedCount >= 2)
	{
		if ((lpClientTime->AttackSpeed-gObj[aIndex].m_AttackSpeed) > 5 || (lpClientTime->MagicSpeed - gObj[aIndex].m_MagicSpeed) > 5)
		{
			g_HackLog.Output("[SpeedHack] :: Item.BMD [%s][%s]; [%d]->[%d]; [%d]->[%d]; [%s] [%d(%dx%d)]", gObj[aIndex].AccountID, gObj[aIndex].Name,
				gObj[aIndex].m_AttackSpeed, lpClientTime->AttackSpeed, gObj[aIndex].m_MagicSpeed, lpClientTime->MagicSpeed,
				gObjGetClassName(aIndex), gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y);
		}
		if (gObj[aIndex].m_AttackSpeedHackDetectedCount >= 10)
		{
			if ((lpClientTime->AttackSpeed-gObj[aIndex].m_AttackSpeed) > 5 || (lpClientTime->MagicSpeed - gObj[aIndex].m_MagicSpeed) > 5)
			{
				g_HackLog.Output("[SpeedHack] :: Item.BMD [%s][%s] - Got Disconnect From Server By Server", gObj[aIndex].AccountID, gObj[aIndex].Name);
				g_GS.CloseClient(aIndex);
			}
		}
	}
	g_GS.CGLiveClient((DWORD)lpClientTime, aIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::gObjSavePetItemInfo(int aIndex, int inventype)
{
	#ifdef GS_99_60T
	{
		OBJECTSTRUCT *  lpObj = &gObj[aIndex];

		int founditemcount = 0;

		if (inventype == 0)
		{
			for (int n = 0; n < INVENTORY_SIZE; n++)
			{
				if (lpObj->pInventory[n].IsItem())
				{
					if (lpObj->pInventory[n].m_Type == ITEMGET(13, 4) || lpObj->pInventory[n].m_Type == ITEMGET(13, 5))
					{
						if (lpObj->pInventory[n].m_IsLoadPetItemInfo != FALSE)
						{
							founditemcount++;

							if (founditemcount >= 20) {
								//g_Msg.Notice(aIndex, "You cannot have more then %d pet in inventory", founditemcount);
								g_HackLog.Output("Hack gObjSavePetItemInfo %s %s :: in inventory", lpObj->AccountID, lpObj->Name);
								g_GS.CloseClient(aIndex);

								return;
							}
						}
					}
				}
			}

		}
		else if (inventype == 1)
		{
			for (int n = 0; n < WAREHOUSE_SIZE; n++)
			{
				if (lpObj->pWarehouse[n].IsItem())
				{
					if (lpObj->pWarehouse[n].m_Type == ITEMGET(13, 4) || lpObj->pWarehouse[n].m_Type == ITEMGET(13, 5))
					{
						if (lpObj->pWarehouse[n].m_IsLoadPetItemInfo != FALSE)
						{
							founditemcount++;

							if (founditemcount >= 20) {
								//g_Msg.Notice(aIndex, "You cannot have more then %d pet in warehouse", founditemcount);
								g_HackLog.Output("Hack gObjSavePetItemInfo %s %s :: in warehouse", lpObj->AccountID, lpObj->Name);
								g_GS.CloseClient(aIndex);

								return;
							}

						}
					}
				}
			}
		}

		g_GS.gObjSavePetItemInfo(aIndex, inventype);
	}
	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::GCReFillSend(int aIndex, int Life, BYTE Ipos)
{
	PMSG_REFILL pMsg;

	PHeadSetB((LPBYTE)&pMsg, GS_PACKET_HEADERS::HEAD_REFILL, sizeof(pMsg));

	pMsg.IPos = Ipos;
	pMsg.LifeH = SET_NUMBERH(Life);
	pMsg.LifeL = SET_NUMBERL(Life);
	pMsg.Flag = 0;

	pMsg.Life = Life;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::GCManaSend(int aIndex, int Mana, BYTE Ipos, BYTE flag, int BP)
{
	if(aIndex < 0 || aIndex > OBJECT_MAX_INDEX - 1 || gObj[aIndex].Type != OBJ_USER) {
		return;
	}

	if(Mana > 65535) {
		Mana = 65535;
	}

	PMSG_MANASEND pMsg;

	pMsg.h.set((LPBYTE)& pMsg, GS_PACKET_HEADERS::HEAD_MANASEND, sizeof(pMsg));

	pMsg.IPos = Ipos;
	pMsg.ManaH = SET_NUMBERH(Mana);
	pMsg.ManaL = SET_NUMBERL(Mana);
	pMsg.BPH = SET_NUMBERH(BP);
	pMsg.BPL = SET_NUMBERL(BP);

	pMsg.Mana = Mana;

	if(Ipos == 254) {
		pMsg.BP = gObj[aIndex].MaxBP;
	} else {
		pMsg.BP = gObj[aIndex].BP;
	}

	DataSend(aIndex, (LPBYTE)& pMsg, pMsg.h.size);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::GCDamageSend(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage)
{
	PMSG_ATTACKRESULT pResult;

	PHeadSetB((LPBYTE)&pResult, GS_PACKET_HEADERS::HEAD_ATTACK, sizeof(pResult));

	pResult.NumberH = SET_NUMBERH(TargetIndex);
	pResult.NumberL = SET_NUMBERL(TargetIndex);
	pResult.DamageH = SET_NUMBERH(AttackDamage);
	pResult.DamageL = SET_NUMBERL(AttackDamage);

	pResult.Damage = AttackDamage;
	pResult.DamageType = MSBDamage;

	if (MSBFlag != FALSE)
	{
		pResult.NumberH &= 0x7F;
		pResult.NumberH |= 0x80;
	}

	if(gObj[TargetIndex].Type == OBJ_USER) {
		DataSend(TargetIndex, (LPBYTE)&pResult, pResult.h.size);
	}

	if(gObj[aIndex].Type == OBJ_USER) {
		DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::GCKillPlayerExpSend(int aIndex, int TargetIndex, int exp, int AttackDamage, int MSBFlag)
{
	#ifdef GS_99_60T

	PMSG_ADDON_LASTDAMAGERESULT pMsg;

	pMsg.h.set((LPBYTE)& pMsg, 0xFB, sizeof(pMsg));

	pMsg.subcode = 0xD;

	pMsg.Damage = AttackDamage;

	DataSend(aIndex, (LPBYTE)& pMsg, pMsg.h.size);

	g_GS.GCKillPlayerExpSend(aIndex, TargetIndex, exp, AttackDamage, MSBFlag);

	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CCore::CGBuyRequestRecv(PMSG_BUYREQUEST * lpMsg, int aIndex)
{
	#ifdef GS_99_60T

	short delearTarget = gObj[aIndex].TargetShopNumber;

	if (delearTarget > COIN_SHOP_START && delearTarget < COIN_SHOP_START + CShop::bShopsCount + 1) {
		CShop::Shops[delearTarget - COIN_SHOP_START - 1].BuyRequest(aIndex, lpMsg->Pos);
	} else {
		g_GS.CGBuyRequestRecv((DWORD)lpMsg, aIndex);
	}

	#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool CCore::ShopDataLoad()
{
	#ifdef GS_99_60T

	bool bReturn = g_GS.ShopDataLoad();

	CShop::LoadShops();

	return bReturn;
	#else

	return true;

	#endif

	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void  CCore::CSPJoinIdPassRequest(PMSG_IDPASS *lpMsg, int aIndex)
{

	if (g_OffTrade.EnableOff == true)
	{
		g_OffTrade.OffTradeLogin(aIndex, lpMsg);		
	}
	g_GS.CSPJoinIdPassRequest((DWORD)lpMsg, aIndex);
	
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCore::gObjSecondProc()
{
#ifdef GS_99_60T
	for (int i = OBJECT_START_INDEX; i < OBJECT_MAX_INDEX; i++)
	{
		if (OfflineShop[i].IsOffTrade == 1)
		{
			(&gObj[i])->ConnectCheckTime = GetTickCount();
		}
	}

	g_GS.gObjSecondProc();
#endif
}