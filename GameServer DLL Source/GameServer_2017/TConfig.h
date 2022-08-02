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

#define CREATE_CHARACTER_UNALLOW_NAMES		"./CREATE_CHARACTER_UNALLOW_NAMES.cfg"
#define BAD_PROCESS							"../../data/badProcesses.txt"
//----------------------------------------------------------------------------------------------------------------

#define UNALLOWED_NAMES_LIST	std::list<tagCFG_UNALLOWED_NAMES>
#define BAD_PROCESSES_LIST		std::list<ULONGLONG>
//----------------------------------------------------------------------------------------------------------------

typedef struct /* GMS_ACCCESS */
{
	char			Nick[11];
}
tagCFG_UNALLOWED_NAMES, * lptagCFG_UNALLOWED_NAMES;
//----------------------------------------------------------------------------------------------------------------

class CConfig
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
public:
    bool		fileRead				(LPSTR szPatch);
	bool		fileIsEnd				();
    void		fileGetString			(LPSTR lpDest, int nDestLen);
    void		fileGetString			(LPSTR lpDest);
    int			fileGetInt				();
    bool		fileGetBool				();
    void		fileClose				();
	long		GetInt(long Min, long Max, long Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName);

	// ----
	bool	isServerVip;
	bool	isKeepCommand;
	bool	isGSCastle;
	bool	bCsExSets;
	bool	isGSUseItemLimit;
	bool	KillEventDifClass;
	bool	KillEventStatus;
	bool	IsOffTradeOn;
	bool	IsOffTradeRestricedMap;
	bool	IsGoldenGiveCredit;
	// ---- VIP System -----
	bool	IsVIPSystemOn;
	// Bronze VIP
	bool	bPostCommand;
	bool	bOffTradeCommand;
	bool	bVIPSing;
	int		bVIPDays;
	int		bVIPPrice;
	// Silver VIP
	bool	sPostCommand;
	bool	sOffTradeCommand;
	bool	sVIPSing;
	int		sVIPDays;
	int		sVIPPrice;
	// Gold VIP
	bool	gPostCommand;
	bool	gOffTradeCommand;
	bool	gVIPSing;
	int		gVIPDays;
	int		gVIPPrice;
	// Platinum VIP
	bool	pPostCommand;
	bool	pOffTradeCommand;
	bool	pVIPSing;
	int		pVIPDays;
	int		pVIPPrice;
	// ----
	int		VipServerLevel;
	// ----
	UINT	nServerCode;
	UINT	nPort;
	UINT	nNoobServerCsResets;	
	int		nOffTradeMapNumber1;
	int		nOffTradeMapNumber2;
	int		nOffTradeMapNumber3;
	int		nOffTradeMapNumber1Cost;
	int		nOffTradeMapNumber2Cost;
	int		nOffTradeMapNumber3Cost;
	int		nOffTradeOnlyVIP;
	int		nKandunPrice;
	int		iRedDragonAttackRate;
	int		iRedDragonMinDmg;
	int		iRedDragonMaxDmg;
	int		iRedDragonHP;
	int		iRedDragonPrizeCredits;
	int		iRedDragonAttackSpeed;
	int		iRedDragonAttackRange;
	int		iRedDragonDefense;
	int		iRedDragonLevel;
	// ----
	int KillEventMinRes;
	int KillEventGapRes;
	// ----
	UNALLOWED_NAMES_LIST CreateCharacterUnallowedList;
	BAD_PROCESSES_LIST	BadProcessesList;
	// ----
							CConfig					(void);
    virtual ~				CConfig					(void);
    // ----
    void					readFiles				();
	void					readConfig				();
	bool					readUnallowedCharNames	(std::string patch);
	bool					readBadProcesses		(std::string patch);
	bool					UnAllowedNamesCheck		(char * name);
	
};
//----------------------------------------------------------------------------------------------------------------
extern CConfig			g_Config;
//----------------------------------------------------------------------------------------------------------------