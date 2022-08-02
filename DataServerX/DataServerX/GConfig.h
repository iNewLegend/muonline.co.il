//----------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------

#include <wchar.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>
//----------------------------------------------------------------------------------------------------------------

#define MAX_SERVER_NAME			20
#define MAX_FILE_SIZE			2000000		/* 2M (2 MB )*/
#define MAX_CLASS_TEMP			100
#define MAX_PATH_LEN			256
//----------------------------------------------------------------------------------------------------------------

#define GMS_ACCESS_PATCH			"./GMS_Access.cfg"
#define GAMESERVER_LIST_PATCH		"./GAMESERVER_LIST.cfg"
#define INSPECT_ACCESS_LIST_PATCH	"./INSPEC_ACCESS.cfg"
#define BAD_PROCESSES_LIST_PATCH	"./BAD_PROCESSES.cfg"
#define GOOD_PROCESSES_LIST_PATCH	"./GOOD_PROCESSES.cfg"
//----------------------------------------------------------------------------------------------------------------

#define GUILD_MANAGER_STATUS	128
#define GUILD_ASSIST_STATUS		64
#define GUILD_BATTLE_STATUS		32
//----------------------------------------------------------------------------------------------------------------

typedef struct /* GMS_ACCCESS */
{
	char			Nick[11];
	bool			isBanForeverEditAllow;
	bool			isAllowUseNewBan;
	bool			isUnBan;
	bool			isGreenMSGAllow;
	bool			isMsgChangeAllow;
}
tagCFG_GMS_ACCESS, * lptagCFG_GMS_ACCESS;
//----------------------------------------------------------------------------------------------------------------

typedef struct /* GAMESERVER_LIST */
{
	USHORT			uPort;
	BYTE			bGSCode;
	char			szGSTitleName[50];
	char			szGSNiceName[50];
	BYTE			bGSCodeGame;
	// ----
	void			Clear()
	{
		uPort		= 0;
		bGSCode		= 0;
		bGSCodeGame = 0;
		// ----
		memset(szGSTitleName, 0, sizeof(szGSNiceName));
		memset(szGSNiceName, 0, sizeof(szGSNiceName));
	}
}
tagCFG_GAMESERVER_LIST, * lptagCFG_GAMESERVER_LIST;
//----------------------------------------------------------------------------------------------------------------

// roye access

typedef struct /* Inspect_Access */
{
	char			Nick[11];
	bool			Move;
	bool			Disconnect;
	bool			Jump;
	bool			Come;
	bool			Ban;
	bool			Baunsers;
	bool			Vote;
	bool			isHackLogAllow;
}
tagCFG_INSPECT_ACCESS, * lptagCFG_INSPECT_ACCESS;

//----------------------------------------------------------------------------------------------------------------

#define GMS_ACCESS_LIST	std::list<tagCFG_GMS_ACCESS>
#define GSS_SERVER_LIST	std::vector<tagCFG_GAMESERVER_LIST>

// roye access
#define INSPECT_ACCESS_LIST	std::list<tagCFG_INSPECT_ACCESS>
//----------------------------------------------------------------------------------------------------------------

void replace_char(char * src, char find, char replace);
//----------------------------------------------------------------------------------------------------------------

class TConfig
{
private:
    char		temp[MAX_CLASS_TEMP];
    // ----
    LPSTR		szPatchFile;
    FILE 	*	handleFile;
    LPBYTE		dataFile;
    ULONG		fileReached;
    UINT		dataCount;
	ULONG		dataSize;
	// ----
    bool		fileRead				(LPSTR szPatch);
	bool		fileIsEnd				();
    void		fileGetString			(LPSTR lpDest, int nDestLen);
    void		fileGetString			(LPSTR lpDest);
    int			fileGetInt				();
    bool		fileGetBool				();
    void		fileClose				();
public:
	GMS_ACCESS_LIST	GMSAccessList;
	GSS_SERVER_LIST	GSSServerList;
	INSPECT_ACCESS_LIST Inspect_AccessList;
	// ----
	std::list<ULONGLONG>	BadProcessesList;
	std::list<ULONGLONG>	GoodProcessesList;
	// ----
							TConfig					(void);
    virtual ~				TConfig					(void);
    // ----
    void					Init					();
	bool					readGmsAccessList		(std::string patch);
	bool					readGameServerList		(std::string patch);
	bool					readBadProcesses		(std::string patch);
	bool					readGoodProcesses		(std::string patch);
	// -----
	lptagCFG_GMS_ACCESS		getGMSAccessListByName	(std::string Name);
	void					getServerNameByGSName	(LPSTR lpDest, LPSTR Name);
	void					getServerNameByGSCode	(LPSTR lpDest, BYTE Code);
	BYTE					getGSCodeGameByGSName	(LPSTR Name);

	// roye access
	bool readInspectAccessList(std::string patch);
	lptagCFG_INSPECT_ACCESS getINSPECTAccessListByName(std::string Name);

	// roye end
	
};
//----------------------------------------------------------------------------------------------------------------
extern TConfig			g_Config;
//----------------------------------------------------------------------------------------------------------------