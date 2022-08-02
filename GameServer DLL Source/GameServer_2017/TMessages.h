//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef MESSAGES_H
#define MESSAGES_H
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CMessages
{
public:
	CMessages(void);
	~CMessages(void);
	// ---
	void DataSendAll(unsigned char* Packet, int Len);
	// change
	void CMessages::DataSendAll(char* Message, unsigned char* Packet, int Len);
	void DataSendMap(int Map, unsigned char* Packet, int Len);
	void DataSendNear(int aIndex, unsigned char* Packet, int Len);
	// ----
	void Notice(int aIndex, const char* Format, ...);
	void NoticeMap(int Map, const char *Format, ...);
	void NoticeAll(const char *Format, ...);
	// ----
	void PM(int aIndex, const char *Format, ...);
	void PMAll(const char *Format, ...);
	void PMMap(int Map, const char *Format, ...);
	// ----
	void Msg(int aIndex, const char *Format, ...);
	void Msg(int aIndex, BYTE Type, const char *Format, ...);
	void MsgAll(const char *Format, ...);
	void MsgMap(int Map, const char *Format, ...);
	// ----
	void AllianceMsg(int aIndex, int SenderIndex, const char *Format, ...);
	//void AllianceMsgAll(const char *Format, ...);
	// ----
	void SendGuild(const char * szGuildName, const char * Format, ...);
	void SendAllGMS(const char * Format, ...);
	// ----
	void GreenNoticeAll(const char *Format, ...);
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

extern CMessages g_Msg;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif /* MESSAGES_H */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------