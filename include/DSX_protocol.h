//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once /* */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define KANDUM_PRICE					10
#define GO_PRICE						1
#define MSG_PRICE						1
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define BUY_VIP_PRICE					60
#define BUY_VIP_DAYS					30
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MIN_RESETS_CHARDEL				10
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define LOTTERY_EVENT_TRY_COUNT			1
#define LOTTERY_EVENT_ROLLED_RANGE		1, 50 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum VDS_PACKET_HEADERS
{
	NO_USE1,
	HEAD_PHP_FRIENDMEMO_DEL,
	HEAD_PHP_FRIENDLIST_ADD,
	HEAD_PHP_FRIENDLIST_READ,
	HEAD_GETSTARTUP,
	HEAD_EXTRAINFO,
	HEAD_GO,
	HEAD_KUADNM,
	HEAD_MSGTONICK,
	HEAD_DCTONICK,
	HEAD_DCTOACCOUNT,
	HEAD_NOTICEALL,
	HEAD_NOTICEALLGM,
	NO_USE2,
	NO_USE3,
	NO_USE4,
	HEAD_GUILDMSG,
	HEAD_BAN,
	HEAD_INFO,
	HEAD_INFOSTATE,
	HEAD_DELCHAR,
	HEAD_VOTESYSTEM,
	HEAD_EXERCISESYSTEM,
	HEAD_BUYVIP,
	HEAD_BANONCHAR,
	HEAD_BANONACC,
	HEAD_INVISIABLE_COMMAND,
	HEAD_INVISIABLE_CREW_COMMAND,
	HEAD_GUILD_MEMBER_STATUS,
	HEAD_GUILD_KICK_MEMBER,
	HEAD_GUILD_SET_ASSIST,
	HEAD_GUILD_JOIN_REQUEST,
	HEAD_ADVMSG,
	HEAD_RUNEVENT,
	HEAD_SENDNOTICEALLFROMDS,
	HEAD_WROTEEVENT,
	HEAD_DOQUERY,
	HEAD_LOTTERYEVENT,
	HEAD_MSG_STATUS,
	HEAD_MSG_STATUS_SYS,
	HEAD_CREW_MSG,
	HEAD_R_CREW_MSG,
	HEAD_LOG_HACK,
	HEAD_KILL_EVENT,
	HEAD_CONFUSEEVENT,
	HEAD_UNBAN,
	HEAD_CHECKACCESS_JUMP,
	HEAD_CHECKACCESS_COME,
	HEAD_CHECKACCESS_MOVE,
	HEAD_ACCESS_DENIED_BAN,
	HEAD_CHECKACCESS_GREENMSG,
	HEAD_SKINACCESS,
	HEAD_SUM_CLIENTS,
	HEAD_CLIENT_STATUS,
	HEAD_EVENT_COMMAND,
	HEAD_MARRY_SYSTEM_INFO,
	HEAD_MARRY_SYSTEM_INFO_R,
	HEAD_MARRY_SYSTEM_UPDATE,
	HEAD_FREINDMEMO_DEL,
	HEAD_FRIENDMEMO_ADD,
	HEAD_FRIENDMEMO_READ,
	HEAD_GOLDEN_EVENT,
	HEAD_SHOP_BUY_REQUEST,
	HEAD_SHOP_BUY_RESULT,
	HEAD_OFFTRADE,
	HEAD_MESSAGE_ALL,
	HEAD_REDDRAGON,
	HEAD_FIXLEVELBUG,
	HEAD_REPORT,
	HEAD_ANTIHACK,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum VDS_SUBPACKET_VOTESYSTEM_HEADERS
{
	VOTESYSTEM_SUBHEAD_START = 0x00,
	VOTESYSTEM_SUBHEAD_STOP,
	VOTESYSTEM_SUBHEAD_GETVOTE,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum VDS_SUBPACKET_ANTIHACK_HEADERS
{
	ANTIHACK_SUBHEAD_PROCESS_NOTIFY = 0x00,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum VDS_SUBPACKET_EXERCISESYSTEM_HEADERS
{
	EXERCISESYSTEM_SUBHEAD_START = 0x00,
	EXERCISESYSTEM_SUBHEAD_GETANSWER,
	EXERCISESYSTEM_SUBHEAD_GIVEPRIZE,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum VDS_SUBPACKET_RUNEVENT_HEADERS
{
	RUNEVENT_SUBHEAD_START = 0x00,
	RUNEVENT_SUBHEAD_STOP,
	RUNEVENT_SUBHEAD_WINNERGET,
	RUNEVENT_SUBHEAD_GIVEPRIZE,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum VDS_SUBPACKET_WROTEEVENT_HEADERS
{
	WROTEEVENT_SUBHEAD_START = 0x00,
	WROTEEVENT_SUBHEAD_STOP,
	WROTEEVENT_SUBHEAD_WINNERGET,
	WROTEEVENT_SUBHEAD_GIVEPRIZE,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum VDS_SUBPACKET_CONFUSEEVENT_HEADERS
{
	CONFUSEEVENT_SUBHEAD_START = 0x00,
	CONFUSEEVENT_SUBHEAD_STOP,
	CONFUSEEVENT_SUBHEAD_WINNERGET,
	CONFUSEEVENT_SUBHEAD_GIVEPRIZE,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum VDS_SUBPACKET_GOLDEN_EVENT
{
	GOLDEN_EVENT_SUBHEAD_START = 0x00,
	GOLDEN_EVENT_SUBHEAD_STOP,
	GOLDEN_EVENT_SUBHEAD_GOLDEN_DIE,
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum VDS_SUBPACKET_LOTTERYEVENT_HEADERS
{
	LOTTERYEVENT_SUBHEAD_START = 0x00,
	LOTTERYEVENT_SUBHEAD_STOP,
	LOTTERYEVENT_SUBHEAD_WINNERGET,
	LOTTERYEVENT_SUBHEAD_GIVEPRIZE,
	LOTTERYEVENT_SUBHEAD_SENDERGET,
	LOTTERYEVENT_SUBHEAD_START_GO,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum PRIZE_TYPES
{
	PRIZE_TYPE_NULL = 0x00,
	PRIZE_TYPE_CREDITS,
	PRIZE_TYPE_BLESS,
	PRIZE_TYPE_SOULS,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum OFFLINE_ONLINE_STATUS
{
	OFFLINE_ONLINE_STATUS_UNKNOW = 0x00,
	OFFLINE_ONLINE_STATUS_ONLINE,
	OFFLINE_ONLINE_STATUS_ONLINE_PLAY,
	OFFLINE_ONLINE_STATUS_OFFLINE,
	OFFLINE_ONLINE_STATUS_CHARSELECT,
	OFFLINE_ONLINE_STATUS_CS_ONLINE,
	OFFLINE_ONLINE_STATUS_DEL_CHAR,
	OFFLINE_ONLINE_STATUS_CREATE_CHAR,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum SHOP_BUY_RESULT
{
	SHOP_BUY_RESULT_UNKNOWN,
	SHOP_BUY_RESULT_SUCESSS,
	SHOP_BUY_RESULT_NOCOINS,
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define SET_NUMBERH(x)			( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x)			( (BYTE)((DWORD)(x) & 0xFF) )
#define SET_NUMBERHW(x)			( (WORD)((DWORD)(x)>>(DWORD)16) )
#define SET_NUMBERLW(x)			( (WORD)((DWORD)(x) & 0xFFFF) )
#define MAKE_NUMBERW(x,y)		( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  )
#define MAKE_NUMBERDW(x,y)		( (DWORD)(((WORD)((y)&0xFFFF)) | ((WORD)((x)&0xFFFF)<<16))  )
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PBMSG_HEAD
{
public:
	void set ( LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};
	// ----
	void setE ( LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = 0xC3;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};
	// ----
	BYTE c;
	BYTE size;
	BYTE headcode;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PWMSG_HEAD
{
public:
	void set( LPBYTE lpBuf, BYTE head, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};
	// ----
	void setE( LPBYTE lpBuf, BYTE head, int size)	
	{
		lpBuf[0] = 0xC4;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};
	// ----
	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PBMSG_HEAD2
{
public:
	void set(BYTE head, BYTE sub, BYTE size)
	{
		this->c			= 0xC1;
		this->size		= size;
		this->headcode	= head;
		this->subcode	= sub;
	};
	// ----
	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DEFAULT
{
	PBMSG_HEAD h;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DEFAULT2
{
	PBMSG_HEAD	h;
	BYTE		subcode;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DEFRESULT
{
	PBMSG_HEAD	h;
	BYTE		result;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_CHATDATA
{
	PBMSG_HEAD	h;
	char		chatid[10];
	char		chatmsg[60];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_CHARDELETE
{
	PBMSG_HEAD	h;
	BYTE		subcode;
	char		Name[10];
	char		LastJoominNumber[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_MAGICATTACK
{
	PBMSG_HEAD	h;
	BYTE		MagicLow;
	BYTE		MagicHigh;
	BYTE		TargetLow;
	BYTE		TargetHigh;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DURATION_MAGIC_RECV
{
	PBMSG_HEAD	h;
	BYTE		MagicNumber;
	BYTE		X;
	BYTE		Y;
	BYTE		Dir;
	BYTE		Dis;
	BYTE		TargetPos;
	BYTE		NumberH;
	BYTE		NumberL;
	BYTE		MagicKey;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct SDHP_GETWAREHOUSEDB_SAVE
{
	PWMSG_HEAD h;
	char AccountID[10];	// 4
	short aIndex;	// E
	int Money;	// 10
	BYTE dbItems[1920];	// 14
	BYTE DbVersion;	// 794
	short pw;	// 796
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma pack(push, 1)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct MSG_HEADER 
{
	BYTE	Type;
	BYTE	ProtocolId;
	BYTE	Len;
} 
* LPMSG_HEADER;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct MSG_HEADER2 
{
	BYTE	Type;
	BYTE	ProtocolId;
	BYTE	SubProtocolId;
	BYTE	Len;
} 
* LPMSG_HEADER2;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct MSG_HEADER3
{
	BYTE	Type;
	BYTE	ProtocolId;
	int		Len;
} 
* LPMSG_HEADER3;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct MSG_HEADER4
{
	BYTE	Type;
	BYTE	ProtocolId;
	BYTE	SubProtocolId;
	int		Len;
} 
* LPMSG_HEADER4;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_S_EXTRAINFO
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	char		szAccountID[10];
	char		szIpAddr[16];
	char		szNick[11];
};
// ----
struct MSG_R_EXTRAINFO
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	int			nDays;
	int			nVipLevel;
	int			nResets;
	int			IsMarried;
	bool		CanUseMove;
	bool		CanUseDisconnect;
	// ----
	char		szName[11];
	char		MarryName[11];
	char		szGuild[11];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_S_GO
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	char		szAccountID[10];
	char		szNickName[10];
	char		szTargetNick[10];
	int			nTargetIndex;
	int			nPrice;
};
// ----
struct MSG_R_GO 
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	int			nTargetIndex;
	int			nPrice;
	bool		bState;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_S_KANDUM
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	int			nPrice;
	char		szAccountID[10];
	char		szNickName[10];
};
// ----
struct MSG_R_KANDUM
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	int			nPrice;
	int			nState;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct MSG_S_OFFTRADE
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	int			nPrice;
	char		szAccountID[10];
	char		szNickName[10];
};

// ----
struct MSG_R_OFFTRADE
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	int			nPrice;
	int			nState;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct MSG_S_REDDRAGON
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	char		szAccountID[10];
	char		szNickName[10];
};

// ----
struct MSG_R_REDDRAGON
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	int			nState;
};

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct MSG_R_GLOAL_MSG 
{
	MSG_HEADER Head;
	// ----
	char	szMessage[100];
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_S_POST 
{
	MSG_HEADER	Head;
	// ----
	char        szNick[10];
	int			nPrice;
	char		szAcountID[10];
	char		szMsg[100];
};
// ----
struct MSG_R_POST
{
	MSG_HEADER	Head;
	// ----
	char        szNick[10];
	char		szMsg[100];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_S_INFO
{
	MSG_HEADER	Head;
	// ----
	int			SeekingIndex;
	char		SeekingName[10];
	char		RequiredNick[10];
};
// ----
struct MSG_R_INFO
{
	MSG_HEADER	Head;
	// ----
	int			SeekingIndex;
	int			VipLevel;
	// ----
	char		Name[10];
	char		szNick[10];
	char		szGuild[9];
	char		MarryName[11];
	// ----
	WORD		wLevel;
	USHORT		nResets;
	BYTE		DBClass;
	// ----
	USHORT		str;
	USHORT		agi;
	USHORT		vit;
	USHORT		ene;
	USHORT		cmd;
	// ----
	BYTE		Map;
	BYTE		X;
	BYTE		Y;
	// ----
	bool		isVip;
	bool		isOnline;
	bool		isMarry;
	bool		isBanned;
	int			nCredits;
	int			killEvent;
	// ----
	char		szServerName[40];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_S_DELCHAR
{
	MSG_HEADER		Head;
	// ----
	USHORT			PlayerIndex;
	// ----
	PMSG_CHARDELETE pMsgCharDel;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_R_DELCHAR
{
	MSG_HEADER		Head;
	// ----
	USHORT			PlayerIndex;
	USHORT			Resets;
	bool			isBanned;
	// ----
	PMSG_CHARDELETE pMsgCharDel;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_REPORT
{
	MSG_HEADER		Head;
	// ----
	char		szReporterName[10];
	char		szName[10];
	char		szReason[100];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_GUILD 
{
	MSG_HEADER	Head;
	// ----
	char        szNick[10];
	char        szGuildName[9];
	char        szMsg[100];
	int			nServerNumber;
	int			G_Status;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_BAN
{
	MSG_HEADER	Head;
	// ----
	char		szGameMasterNick[10];
	char		szPlayerNick[10];
	int			nDays;
	int			nReason;
	int			isBanAllUsers;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_MSGTONICK
{
	MSG_HEADER	Head;
	// ----
	char		szNick[10];
	char		szMessage[100];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_DCTONICK
{
	MSG_HEADER	Head;
	// ----
	char		szNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_DCTOACCOUNT
{
	MSG_HEADER	Head;
	// ----
	char		szAccountId[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 struct MSG_STARTUP
 {
	 MSG_HEADER	Head;
	 // ----
	 BYTE		btServerCode;
	 USHORT		Resets;
	 bool		RunEventState;
	 bool		CsSets;
 };
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_INFO_STATE
{
	MSG_HEADER Head;
	// -----
	char		szNick[10];
	bool		bState;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct VOTESYSTEM_ANSWERS
{
	char	Answer[100];
	BYTE	Len;
	BYTE	Id;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct VOTESYSTEM_ANSWERSD
{
	BYTE	Id;
	int		AnswerdFor;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_VOTESYSTEM_START
{
	MSG_HEADER4			Head;
	// ----
	char				szGameMaster[10];
	int					nSeconds;
	char				Question[100];
	BYTE				questionLen;
	BYTE				AnswersCount;
	VOTESYSTEM_ANSWERS	Answers[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_VOTESYSTEM_STOP
{
	MSG_HEADER4			Head;
	// ----
	BYTE				AnswersCount;
	VOTESYSTEM_ANSWERSD	Answered[10];
	// ----
	int					SumVoters;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_VOTESYETEM_GETVOTE
{
	MSG_HEADER4			Head;
	// -----
	char				PlayerName[10];
	char				AccountID[10];
	BYTE				VoteID;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_ANTIHACK_PROCESS_NOTIFY
{
	MSG_HEADER4			Head;
	// ----
	char				szAccountId[10];
	char				szIpAddr[16];
	char				szProcess[1024];
	ULONGLONG			uChecksum;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_EXERCISE_GETANSWER
{
	MSG_HEADER2		Head;
	// ----
	int				Answer;
	char			szNick[10];
	char			szAccountID[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_EXERCISE_START
{
	MSG_HEADER2		Head;
	// ----
	int				Num1;
	int				Num2;
	int				Num3;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_EXERCISE_GIVEPRIZE
{
	MSG_HEADER2		Head;
	// ----
	int				An;
	int				PrizeType;
	int				Prize;
	char			szNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_RUNEVENT_START
{
	MSG_HEADER2		Head;
	// ----
	BYTE			Map;
	BYTE			X;
	BYTE			Y;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_RUNEVENT_GIVEPRIZE
{
	MSG_HEADER2		Head;
	// ----
	int				PrizeType;
	int				Prize;
	char			szNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_RUNEVENT_SENDWINNER
{
	MSG_HEADER2		Head;
	// ----
	char			szAccountID[10];
	char			szNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_WROTEEVENT_SENDWINNER
{
	MSG_HEADER2		Head;
	// ----
	char			szAccountID[10];
	char			szNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_SEARCHBEVENT_START
{
	MSG_HEADER2		Head;
	// ----
	BYTE			Map;
	BYTE			X;
	BYTE			Y;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_SEARCHBEVENT_SENDWINNER
{
	MSG_HEADER2		Head;
	// ----
	char			szAccountID[10];
	char			szNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_WROTEEVENT_START
{
	MSG_HEADER2		Head;
	// ----
	char			Word1[50];
	char			Word2[50];
	char			Word3[50];
	char			Word4[50];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_WROTEEVENT_GIVEPRIZE
{
	MSG_HEADER2		Head;
	// ----
	int				PrizeType;
	int				Prize;
	char			szNick[10];
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_CONFUSEEVENT_SENDWINNER
{
	MSG_HEADER2		Head;
	// ----
	char			szAccountID[10];
	char			szNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_CONFUSEEVENT_START
{
	MSG_HEADER2		Head;
	// ----
	char			Word1[20];
	char			Word2[20];
	char			Word3[20];
	char			Word4[20];
	char			Word5[20];
	char			Word6[20];
	char			Word7[20];
	char			Word8[20];

};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_CONFUSEEVENT_GIVEPRIZE
{
	MSG_HEADER2		Head;
	// ----
	int				PrizeType;
	int				Prize;
	char			szNick[10];
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_LOTTERYEVENT_SENDWINER
{
	MSG_HEADER2		Head;
	// ----
	char			szAccountID[10];
	char			szNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_LOTTERYEVENT_START
{
	MSG_HEADER2		Head;
	// ----
	UINT			RolledNumber;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_LOTTERYEVENT_GIVEPRIZE
{
	MSG_HEADER2		Head;
	// ----
	int				PrizeType;
	int				Prize;
	char			szNick[10];
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_SEARCHBEVENT_GIVEPRIZE
{
	MSG_HEADER2		Head;
	// ----
	int				PrizeType;
	int				Prize;
	char			szNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_LOTTERYEVENT_GETSENDER
{
	MSG_HEADER2		Head;
	// ----
	char			szNick[10];
	UINT			Number;
	bool			bISOK;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_KILLEVENT_CHECKPOINTS
{
	MSG_HEADER		Head;
	// ----
	char			Nick[10];
	char			tNick[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_GOLDENEVENT_START
{
	MSG_HEADER		Head;
	// ----
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_GOLDENEVENT_SEND_WINNER
{
	MSG_HEADER		Head;
	// ----

};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_BUY_VIP_REQUEST
{
	MSG_HEADER		Head;
	// ----
	char			szAccountID[10];
	char			szNick[10];
	int				VipLevel;
	int				VipDays;
	int				VipPrice;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_BAN_CHAR
{
	MSG_HEADER		Head;
	// ----
	bool			State;
	char			szGameMaster[10];
	char			szNick[10];
	int				ID;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_BAN_ACC
{
	MSG_HEADER		Head;
	// ----
	bool			State;
	char			szGameMaster[10];
	char			szAccountID[10];
	int				ID;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_ADVMSG
{
	MSG_HEADER		Head;
	// ----
	char			PakahName[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_SENDNOTICEALLFROMDS
{
	MSG_HEADER		Head;
	// ----
	char			Notice[100];
	int				NoticeLen;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_CLIENT_STATUS
{
	MSG_HEADER	Head;
	// ----
	int			nIndex;
	BYTE		Status;
	BYTE		btServerCode;
	char		szAccountID[10];
	char		szNick[10];
	char		szIpAddr[16];

};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// roye add
// roye access
struct MSG_ACCESS_JUMP
{
	MSG_HEADER		Head;
	// ----
	bool			State;
	char			Command[10];
	char			Name[10];
	int				aIndex;
	char			TargetName[10];
	BYTE			TeleportID;

};

struct MSG_ACCESS_COME
{
	MSG_HEADER		Head;
	// ----
	bool			State;
	char			Command[10];
	char			Name[10];
	int				aIndex;
	char			TargetName[10];

};

struct MSG_ACCESS_MOVE
{
	MSG_HEADER		Head;
	// ----
	bool			State;
	char			Command[10];
	char			Name[10];
	int				aIndex;
};

struct MSG_ACCESS_GREENMSG
{
	MSG_HEADER		Head;
	// ----
	bool			State;
	char			Command[55];
	char			Name[10];
	int				aIndex;
};

struct MSG_ACCESS_BAN
{
	MSG_HEADER		Head;
	// ----
	char			Command[10];
	char			Name[10];
};

struct MSG_UNBAN
{
	MSG_HEADER		Head;
	// ----
	char szGameMasterNick[11];
	char szPlayerNick[11];
	int  nReason;
};

struct MSG_SKIN_CHECK
{
	MSG_HEADER		Head;
	// ----
	char szGMName[11];
	char szName[11];
	char szAccountID[11];
	int MID;
};

struct MSG_INVISIBLE_COMMAND
{
	MSG_HEADER		Head;
	// ----
	char szGMName[11];
	char szAccountID[11];
	bool status;
};

struct MSG_INVISIBLE_CREW_COMMAND
{
	MSG_HEADER		Head;
	// ----
	char szGMName[11];
	char szAccountID[11];
	bool status;
};

struct MSG_GUILD_MEMBER_STATUS
{
	MSG_HEADER		Head;
	// ----
	char AssistName[11];
	char MemberName[11];
	char GuildName[11];
	BYTE Type;
};

struct MSG_GUILD_MEMBER_STATUS_R
{
	MSG_HEADER		Head;
	// ----
	char AssistName[11];
	char MemberName[11];
	char GuildName[11];
	BYTE Type;
	int Status;
};

struct MSG_GUILD_KICK_MEMBER
{
	MSG_HEADER		Head;
	// ----
	char AssistName[11];
	char MemberName[11];
	char GuildName[11];
};

struct MSG_GUILD_KICK_MEMBER_R
{
	MSG_HEADER		Head;
	// ----
	char AssistName[11];
	char MemberName[11];
	char GuildName[11];
	int Status;
};

struct MSG_GUILD_SET_ASSIST
{
	MSG_HEADER		Head;
	// ----
	char ManagerName[11];
	char GuildName[11];
	BYTE Type;
};

struct MSG_GUILD_JOIN_REQUEST
{
	MSG_HEADER		Head;
	// ----
	char AssistName[11];
	char ReqName[11];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_GUILD_JOIN_REQUEST_R
{
	MSG_HEADER		Head;
	// ----
	char AssistName[11];
	char ReqName[11];
	BYTE Status;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_SKIN_CHECK_R
{
	MSG_HEADER		Head;
	// ----
	char szGMName[11];
	char szName[11];
	int Status;
	int MID;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_MSG_STATUS
{
	MSG_HEADER		Head;
	// ----
	int Status;
	int Time;
	char Name[11];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_MSG_STATUS_RE
{
	MSG_HEADER		Head;
	// ----
	char Name[11];
	int Status;
	int Type;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_MSG_STATUS_RE_SYS
{
	MSG_HEADER		Head;
	// ----
	int Status;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_SUM_CLIENTS
{
	MSG_HEADER		Head;
	// ----
	int Type;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_CREW
{
	MSG_HEADER		Head;
	// ----
	int			SeekingIndex;
	char		SeekingName[11];
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_LOG_HACK
{
	MSG_HEADER		Head;
	// ----
	int			aIndex;
	// ----
	char		Name[10];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_R_LOG_HACK
{
	MSG_HEADER		Head;
	// ----
	int			aIndex;
	// ----
	char		Name[10];
	// -----
	int			status;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_EVENT_COMMAND
{
	MSG_HEADER		Head;
	// ----
	int			aIndex;
	int			Status;
	// ----
	char		AccountID[11];
	char		Name[11];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_MARRY_SYSTEM_UPDATE
{
	MSG_HEADER		Head;
	// ----
	bool		MarrigeStatus;
	// ----
	char		MarryName1[11];
	char		MarryName2[11];

};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_DOQUERY
{
	MSG_HEADER		Head;
	// ----
	char			Query[130];
	int				QueryLen;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_SHOP_BUY_ITEM_REQUEST
{
	MSG_HEADER		Head;
	// ----
	char			szAccountId[11];
	char			szName[11];
	// ----
	int				iShopId;
	BYTE			bProductPos;
	int				iPrice;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_SHOP_BUY_ITEM_RESULT
{
	MSG_HEADER		Head;
	// ----
	char			szAccountId[11];
	char			szName[11];
	// ----
	int				iShopId;
	BYTE			bProductPos;
	BYTE			bResult;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// #Friend Memo Update
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_FREINDMEMO_DEL
{
	MSG_HEADER		Head;
	// ----
	char			szName[11];
	int				MemoIndex;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_FREINDMEMO_ADD
{
	MSG_HEADER		Head;
	// ----
	char			RecvName[11];
	char			SendName[11];
	char			Subject[50];
	int				MemoIndex; 
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MSG_FREINDMEMO_ADD_GS
{
	MSG_HEADER		Head;
	// ----
	char			RecvName[11];
	char			SendName[11];
	char			Subject[50];
	char			Date[30];
	int				MemoIndex; 
};

struct MSG_FREINDMEMO_READ
{
	MSG_HEADER		Head;
	// ----
	char			RecvName[11];
	char			SendName[11];
	char			Subject[50];
	int				MemoIndex; 
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct MSG_S_FIX_LEVEL_BUG
{
	MSG_HEADER		Head;
	// -----
	char			szName[11];
	int				nIndex;
	int				iLevel;
};

struct MSG_R_FIX_LEVEL_BUG
{
	MSG_HEADER		Head;
	// -----
	int				nIndex;
	int				nState;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma pack(pop)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void HeadSet1(LPMSG_HEADER pHead, BYTE Len, BYTE ProtocolId)
{
	pHead->Type			= 1;
	pHead->Len			= Len;
	pHead->ProtocolId	= ProtocolId;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void HeadSet2(LPMSG_HEADER2 pHead, BYTE Len, BYTE ProtocolId, BYTE subProtocolID)
{
	pHead->Type			= 2;
	pHead->Len			= Len;
	pHead->ProtocolId	= ProtocolId;
	pHead->SubProtocolId	= subProtocolID;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void HeadSet3(LPMSG_HEADER3 pHead, int Len, BYTE ProtocolId)
{
	pHead->Type			= 3;
	pHead->Len			= Len;
	pHead->ProtocolId	= ProtocolId;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void HeadSet4(LPMSG_HEADER4 pHead, int Len, BYTE ProtocolId, BYTE subProtocolID)
{
	pHead->Type			= 4;
	pHead->Len			= Len;
	pHead->ProtocolId	= ProtocolId;
	pHead->SubProtocolId= subProtocolID;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
