//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

#include "TDataBase.h"
#include "GIOCPHandler.h"
//-----------------------------------------------------------------------------------------------------------------------

#define OBJECT_MAX		100
#define INVALID_OBJECT	-1
#define MAXIDLETIMEMS	15000
//-----------------------------------------------------------------------------------------------------------------------

enum OBJECT_STATUS 
{
	O_STATUS_EMPTY,
	O_STATUS_CONNECTED,
};
//-----------------------------------------------------------------------------------------------------------------------

typedef struct OBJECTSTRUCT 
{
	int				m_GSCode;
	// ----
	OBJECT_STATUS	m_aStatus;
} 
* PCLIENTOBJECTSTRUCT;
//-----------------------------------------------------------------------------------------------------------------------

struct tagNicksState
{
	std::string		Name;
	int				TickCount;
};
//-----------------------------------------------------------------------------------------------------------------------

typedef struct /* tagGMSStatus */
{
	std::string		accName;
	std::string		GMName;
	bool			bStatus;
	BYTE			btServerCode;
} tagGMSStatus, * lptagGMSStatus;
//-----------------------------------------------------------------------------------------------------------------------

typedef struct /* tagMEMBERGuild */
{
	std::string		accName;
	std::string		NameMember;
	bool			bStatus;
	BYTE			btServerCode;
} tagMEMBERGuild, * lptagMEMBERGuild;
//-----------------------------------------------------------------------------------------------------------------------

#define GMS_LIST			std::list <tagGMSStatus>
#define GUILD_MEMBER_LIST	std::list <tagMEMBERGuild>
//-----------------------------------------------------------------------------------------------------------------------

int			gObjSearchFree	();
void		gObjAdd			(int aIndex);
void		gObjDel			(int aIndex);
void		objectInit		();
void		objectWorker	();
void		objectMsgToNick		(TIOCPHandler * h, std::string szNick, std::string szMessage);
void		objectMsgToNick		(TIOCPHandler * h, uint64_t cid, char * szNick, const char * szMessage);
void		objectMsgToNick		(std::string szNick, std::string szMessage);
void		ObjectDcToNick		(TIOCPHandler * h, char * szNick);
void		ObjectDcToNick		(TIOCPHandler * h, uint64_t cid, char * szNick);
void		ObjectDcToAccount	(TIOCPHandler * h, std::string sAccount);
void		ObjectDcToAccount	(TIOCPHandler * h, uint64_t cid, std::string sAccount);
void		ObjectAccessBan		(TIOCPHandler * h, uint64_t cid, char * szNick, const char * Command);
void		ObjectLogCreditAdd			(std::string Name, std::string Account, int Credits, std::string type, int typeIndex);
void		ObjectLogHistoryAdd			(std::string Name, std::string Account, std::string type, std::string ip, int typeIndex);
void		ObjectLogHistoryUpdateLine	(std::string Name, std::string Account, std::string date, std::string ip);
void		ObjectLogEventAdd			(std::string Name, std::string Account, std::string whoRun, std::string typeEvent, std::string typePrize, int amount);
void		ObjectSendNoticeAll			(std::string Notice);
void		ObjectIncraseCredits		(std::string sAccountId, UINT uAmount); 

GMS_LIST			ObjectGetAllGmsStatus	();
GUILD_MEMBER_LIST	ObjectGetAllMembersGuild(std::string GuildName);

// this funciton should be rename as ObjectWebMsgState
void		MessagesWebState	(bool status);

UINT		ObjectRandomize	(UINT min, UINT max);
//-----------------------------------------------------------------------------------------------------------------------

extern	OBJECTSTRUCT		g_Obj[OBJECT_MAX];
extern	TDataBase			g_DB;
extern	iocp::CIocpServer	* gDSIocp;
extern  bool				MSG_CONTINUE;
//-----------------------------------------------------------------------------------------------------------------------