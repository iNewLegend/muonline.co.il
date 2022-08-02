//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef OBJECT_H
#define OBJECT_H
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct _POSITION
{
	BYTE x;
	BYTE y;
	BYTE Map;
	BYTE RoledID;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct _LOACTION
{
	BYTE Map;
	BYTE X;
	BYTE Y;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void		ObjectSetZero			(int aIndex);
void		ObjectVIPCheck			(LPVOID lParam);
void		ObjectBanAdd			(int gmIndex, char * szNick , int Days , int ReasonID);
void		ObjectBanUsersAdd		(int gmIndex, char * szNick , int Days , int ReasonID);
void		ObjectExtraInfoResult	(int aIndex, MSG_R_EXTRAINFO * lpMsg);
void		ObejctGoState			(int Type, int aIndex, int Target, int Credits, bool State);
void		ObjectDOGo				(int aIndex, int tIndex);
void		ObjectUnBanAdd			(int aIndex, char * name, int bRes);
void		ObjectComeTeleport		(int srcIndex, char * TargetName, int type, bool access);
void		ObjectDOCome			(int aIndex, int tIndex);
void		ObjectMoveMeTeleport	(int aIndex, int map, int x, int y);
void		ObjectBanAccessDenied	(char * Nick, char* Command);

void		ObjectMSGChangeStatus		(char * Name, int type, int status);
void		ObjectMSGChangeStatusSys		(int status);

void		ObjectEventCommandAccess (char * Nick, int status);
void		ObejctKandumState		(int Type, int aIndex, int Credits, int Code);
void		ObjectDoKandum			(int aIndex);
void		ObjectKandumThread		(LPVOID lParam);
_POSITION	ObjectRolePosition		();
void		ObjectPostAll			(char * Name, char * Message);
void		ObjectPostAllGM			(char * Name, char * Message);
void		ObjectGuildMsgAll		(int uServerNumber, char * Name, char * Message, char * GuildName, int G_Status);
void		ObjectLogKill			(LPVOID lpAram);
bool		ObjectTeleportByMapName	(int aIndex, char * MapName);
void		ObjectOuputActiveGMS	(int targetIndex);
void		ObjectOuputActiveG_Membe(int targetIndex, char * GuildName);
void		ObjectJumpTeleport		(int srcIndex, char * TargetName, BYTE TeleportID, int check, bool access);
void		ObjectOutputUptime		(int aIndex);
double		ObjectGetResetsByPoints	(int aIndex);
void		ObjectCapturePlayerPoint(int aIndex, BYTE Map, BYTE X, BYTE Y);
int			ObjectSpawnMonster		(int ModID, BYTE Map, BYTE X, BYTE Y);
short		ObjectAddSearch			(SOCKET aSocket, char * ip);
void		ObjectLogHackChange		(int aIndex, int status);
void		ObjectMoveInLorenvaly	(int aIndex);
UINT		ObjectGetRandomize		(UINT start, UINT max);
void		ObjectUpdateFirstMarrigeInfo	(int aIndex, char * Name, char * MarryName, int IsMarried, int MarryType);
void		ObjectChangeSkin		(char * GMName, char * szName, int Status, int MID);
void		ObjectFriendMemoDelete	(char * Name, int MemoIndex);
void		ObjectFriendMemoListSend(char * SendName, char * RecvName, int MemoIndex, char * Subject, char * Date);
bool		ObjectCheckUnAllowedChars(std::string szNick);
void		ObjectGuildChangeMemberStatus	(char * AssistName, char * MemberName, char * GuildName, BYTE Type, int Status);
void		ObjectGuildKickMember	(char * AssistName, char * MemberName, char * GuildName, int Status);
void		ObjectClientProcessNotify	(int aIndex, std::string sProcessName, ULONGLONG uChecksum);
// leo: bad funciton names or not the place for them
void		CGGuildRequestRecv(int aIndex, int assistIndex);
void		GCResultSend(int aIndex, BYTE headcode, BYTE result);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

extern bool g_EXERCISESYSTEM_STATE;
extern bool g_RUNEVENT_STATE;
extern bool g_FASTWROTE_STATE;
extern bool g_LOTTERYEVENT_STATE;
extern bool g_CONFUSEEVENT_STATE;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

extern UINT			g_LOTTREYEVENT_ROLEED;
extern _LOACTION	g_RUNEVENT_CORD;
extern std::string	g_WROTE_TEXT;
extern std::string	g_CONFUSE_WROTE_TEXT;
extern std::string	g_CONFUSE_WROTE_TEXT_WRONG;
extern bool MSG_STATUS; // bad name
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif /* OBJECT_H */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------