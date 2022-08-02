#include "stdafx.h"
#include "TMessages.h"
#include "User.h"
#include "TCore.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # Made By Leo123[BoR] -> GS 99.60T -> Only for MuOnline.co.il

CMessages g_Msg;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CMessages::CMessages(void)
{
	// ----
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CMessages::~CMessages(void)
{
	// ----
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::DataSendAll(unsigned char* Packet, int Len)
{
	for(USHORT i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
	{
		if(gObjIsConnected(i))
		{
			g_GS.DataSend(i, Packet, Len);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::DataSendMap(int Map, unsigned char* Packet, int Len)
{
	for(USHORT i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
	{
		if(gObjIsConnected(i))
		{
			if(gObj[i].MapNumber == Map)
			{
				g_GS.DataSend(i, Packet, Len);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::DataSendNear(int aIndex, unsigned char* Packet, int Len)
{
	BYTE MyMap			= gObj[aIndex].MapNumber;
	BYTE MyX			= gObj[aIndex].X;
	BYTE MyY			= gObj[aIndex].Y;
	// ----
	for(USHORT i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
	{
		if(gObjIsConnected(i))
		{
			BYTE Map			= gObj[aIndex].MapNumber;
			BYTE X				= gObj[aIndex].X;
			BYTE Y				= gObj[aIndex].Y;
			// ----
			if(MyMap == Map)
			{
				if(X < (MyX + 6) && X > (MyX - 6))
				{
					if(Y < (MyY + 6) && Y > (MyY - 6))
					{
						g_GS.DataSend(i, Packet, Len);
					}
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::Notice(int aIndex, const char* Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet		= 0xC1;
	*(Packet + 2) = 0x0D;
	*(Packet + 3) = 0x00;
	// ----
	memcpy((Packet+13), Message, strlen(Message));
	// ----
	int Len = (strlen(Message) + 13);
	*(Packet+1) = Len;
	// ----
	g_GS.DataSend(aIndex, Packet, Len);
	// ----
	free(Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::NoticeMap(int Map, const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet		= 0xC1;
	*(Packet+2) = 0x0D;
	*(Packet+3) = 0x00;
	// ----
	memcpy((Packet+13), Message, strlen(Message));
	// ----
	int Len		= (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	// ----
	DataSendMap(Map, Packet, Len);
	// ----
	free(Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::NoticeAll(const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet		= 0xC1;
	*(Packet+2) = 0x0D;
	*(Packet+3) = 0x00;
	// ----
	memcpy((Packet+13), Message, strlen(Message));
	// ----
	int Len		= (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	// ----
	DataSendAll(Packet, Len);
	// ----
	free(Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::PM(int aIndex, const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet		= 0xC1;
	*(Packet+2) = 0x02;
	// ----
	memcpy((Packet+13), Message, strlen(Message));
	// ----
	int Len		= (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	// ----
	g_GS.DataSend(aIndex, Packet, Len);
	// ----
	free(Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::PMAll(const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet		= 0xC1;
	*(Packet+2) = 0x02;
	// ----
	memcpy((Packet+13), Message, strlen(Message));
	// ----
	int Len		= (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	// ----
	DataSendAll(Packet, Len);
	// ----
	free(Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::PMMap(int Map, const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet		= 0xC1;
	*(Packet+2) = 0x02;
	// ----
	memcpy((Packet+13), Message, strlen(Message));
	// ----
	int Len		= (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	// ----
	DataSendMap(Map, Packet, Len);
	// ----
	free(Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::Msg(int aIndex, const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet		= 0xC1;
	*(Packet+2) = 0x00;
	// ----
	memcpy((Packet+13), Message, strlen(Message));
	// ----
	int Len		= (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	// ----
	g_GS.DataSend(aIndex, Packet, Len);
	// ----
	free(Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::Msg(int aIndex, BYTE Type, const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	g_GS.GCServerMsgStringSend(Message, aIndex, Type);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::MsgAll(const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet		= 0xC1;
	*(Packet+2) = 0x00;
	// ----
	memcpy((Packet+13), Message, strlen(Message));
	// ----
	int Len		= (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	// ----
	DataSendAll(Packet, Len);
	// ----
	free(Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::MsgMap(int Map, const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet		= 0xC1;
	*(Packet+2) = 0x00;
	// ----
	memcpy((Packet+13), Message, strlen(Message));
	// ----
	int Len		= (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	// ----
	DataSendMap(Map, Packet, Len);
	// ----
	free(Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::AllianceMsg(int aIndex, int SenderIndex, const char *Format, ...)
{
	char Message1[1024];
	char Message[1024];
	// ----
	memset(Message, 0 , sizeof(Message));
	memset(Message1, 0 , sizeof(Message1));
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message1, Format, pArguments);
	va_end(pArguments);
	// ----
	sprintf(Message, "@@%s", Message1);
	// ----
	PMSG_CHATDATA pMsg = {0};
	// ----
	pMsg.h.c			= 0xC1;
	pMsg.h.headcode		= 0x00;
	// ----
	memcpy(pMsg.chatid,		gObj[SenderIndex].Name,	MAX_ACCOUNT_LEN);
	memcpy(pMsg.chatmsg,	Message,				sizeof(pMsg.chatmsg));
	// ----
	pMsg.h.size = sizeof(pMsg);
	// ----
	g_GS.DataSend(aIndex, (UCHAR *) & pMsg , pMsg.h.size);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*void Messages::AllianceMsgAll(const char *Format, ...)
{
	char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet		= (BYTE*) malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet			= 0xC1;
	*(Packet + 2)	= 0x00;
	*(Packet + 13)	= 0x40;
	*(Packet + 14)	= 0x40;
	// ----
	memcpy(& Packet[16] , Message, strlen(Message));
	// ----
	int Len		= (strlen(Message) + 16);
	// ----
	*(Packet+1) = Len;
	// ----
	DataSendAll(Packet, Len);
	// ----
	free(Packet);
}*/
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::SendGuild(const char * szGuildName, const char * Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	OBJECTSTRUCT * lpObj;
	// ----
	for(USHORT i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
	{
		lpObj = & gObj[i];
		// ----
		if(lpObj->Type == OBJ_USER)
		{
			if(lpObj->Connected == PLAYER_PLAYING)
			{
				if(lpObj->GuildName[0] == szGuildName[0])
				{
					if(lpObj->GuildName[1] == szGuildName[1])
					{
						if(_strcmpi(lpObj->GuildName, szGuildName) == 0)
						{
							Msg(i, "@[GM.System] %s", Message);
						}
					}
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMessages::SendAllGMS(const char * Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	for(USHORT i = OBJECT_START_INDEX ; i != OBJECT_MAX_INDEX ; ++i)
	{
		if(gObj[i].Type == OBJ_USER)
		{
			if(gObjIsGameMaster(i) == true)
			{
				if(gObj[i].Connected == PLAYER_PLAYING)
				{
					Msg(i, "@[GM.System] %s", Message);
				}
			}
			
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



void CMessages::GreenNoticeAll(const char *Format, ...)
{
	 char Message[1024];
	 va_list pArguments;
	 va_start(pArguments, Format);
	 vsprintf(Message, Format, pArguments);
	 va_end(pArguments);
	 // ----
	 BYTE *Packet;
	 // ----
	 Packet = (BYTE*) malloc(200);
	 memset(Packet, 0x00, 200);
	 // ----
	 *Packet = 0xC1;
	 *(Packet+2) = 0x0D;
	 *(Packet+3) = 0x02;
	 // ----
	 memcpy((Packet+13), Message, strlen(Message));
	 int Len = (strlen(Message) + 0x13);
	 // ----
	 *(Packet+1) = Len;
	 // ----
	 DataSendAll(Packet, Len);
	 // ----
	 free (Packet);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

