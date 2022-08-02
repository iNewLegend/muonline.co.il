//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef CHAT_H
#define CHAT_H
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define CHAT_FLOOD		30000
#define HELP_FLOOD		300000
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CChatFunctions
{
public:
	const char *	GetMsgByStatus	(bool status);
	char	GetParam		(char id, char* txt, char* buff);
	void	GetLongParam	(char* text, char* buff);
	LPCSTR	GetGuildString	(int aIndex);
	LPCSTR	GetVipString	(int aIndex);
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ChatGMBanAdd			(int aIndex, char * Message);
void ChatGMBanUsersAdd		(int aIndex, char * Message);
void ChatInfoCMD			(int aIndex, char * Message);
void ChatGOCmd				(int aIndex, char * Message);
void ChatKandumCMD			(int aIndex);
void ChatPostCMD			(int aIndex, char * Message);
void ChatMsgCMD				(int aIndex, char * Message);
void ChatMsgCMDGM			(int aIndex, char * Message);
void ChatUnBanCmd			(int aIndex, char * Message);
void CheckMoveAndDisAcc		(int aIndex, char * Message, int type, bool access);
void ChatComeCmd			(int aIndex, char * Message);
void ChatMoveMeCmd			(int aIndex, char * Message);
void CheckGreenMSG			(int aIndex, char * Message, int type, bool access);
void ChatMSGChange			(int aIndex, char * Message);
void ChatMarryStartCommand	(int aIndex, char * Message);
void ChatTrackMarry			(int aIndex, char * Message);
void ChatHelpCMD			(int aIndex);
void ChatOffTradeCMD		(int aIndex);
void ChatRedDragonCMD		(int aIndex);
void ChatFixLevelBugCMD		(int aIndex);
bool ChatCore				(int aIndex, PMSG_CHATDATA * lpMsg);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

extern CChatFunctions g_Chatfunc;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif /* CHAT_H */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------