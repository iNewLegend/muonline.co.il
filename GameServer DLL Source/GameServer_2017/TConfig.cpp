#include "stdafx.h"
#include "TConfig.h"
#include "TLogToFile.h"
#include "TIniFile.h"
#include "TSetup.h"
#include "TBotSystem.h"
#include "TMarrySystem.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # Made By Leo123[BoR] & Roye Trick -> GS 99.60T -> Only for MuOnline.co.il

#define g_ModuleName "CConfig"
//----------------------------------------------------------------------------------------------------------------

char		findGershaim[] = {'"', 0x00};
//----------------------------------------------------------------------------------------------------------------

CConfig			g_Config;
//----------------------------------------------------------------------------------------------------------------

CConfig::CConfig(void)
{

}
// ----------------------------------------------------------------------------------------------------------------

CConfig::~CConfig(void)
{
    // ----
}
//----------------------------------------------------------------------------------------------------------------

bool CConfig::fileRead(LPSTR szPatch)
{
    bool bReturn = false;
    // ----
    szPatchFile	= szPatch;
    // ----
    fileReached	 = 0;
    // ----
    if((handleFile = fopen(szPatch, "r")) > 0)
    {
		fseek(handleFile, 0 , SEEK_END);
		// ----
		dataSize = ftell(handleFile);
		// ----
		fseek(handleFile, 0 , SEEK_SET);
		// ----
        if((dataFile = (LPBYTE) malloc(MAX_FILE_SIZE)) != NULL)
        {
            if(fread(dataFile, 1, MAX_FILE_SIZE, handleFile) <= 0)
            {
				g_Setup.MsgBox("[CConfig][fileRead] :: error : fread %d", __LINE__);
            }
            // ----
            fclose(handleFile);
            // ----
            bReturn = true;
        }
    }
	else
	{
		g_Setup.MsgBox("file %s reading error %d", szPatch, GetLastError());
	}
    // ----
    return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

bool CConfig::fileIsEnd()
{
	char Temp[1024] = {0};
	// ----
	dataCount = 0;
	// ----
	bool bNeedThis = true;
	// ----
	int fileRechTemp = fileReached;
	// ----
	//try
	{
		while(true)
		{
			if(dataFile[fileRechTemp] == 0x00)
			{
				return true;
			}
			if((dataFile[fileRechTemp] == '"') || (bNeedThis == false))
			{
				bNeedThis = false;
				// ----
				if(dataFile[fileRechTemp + 1] == '"')
				{
					fileRechTemp++;
					fileRechTemp++;
					// ---
					break;
				}
				// ----
				Temp[dataCount] = dataFile[fileRechTemp + 1];
				// ----
				fileRechTemp++;
			}
			else
			{
				fileRechTemp++;
			}
		}
	}
	//catch(...)
	{
	//	return true;
	}
	/// ----
	return false;

}
//----------------------------------------------------------------------------------------------------------------

void CConfig::fileGetString(LPSTR lpDest, int nDestLen)
{
    dataCount = 0;
    // ----
    bool bNeedThis = true;
    // ----
    memset(lpDest, 0, nDestLen);
    // ----
    while(true)
    {
        if((dataFile[fileReached] == '"') || (bNeedThis == false))
        {
            bNeedThis = false;
            // ----
            if(dataFile[fileReached + 1] == '"')
            {
                fileReached++;
                fileReached++;
                // ---
                break;
            }
            // ----
            lpDest[dataCount] = dataFile[fileReached + 1];
            // ----
            dataCount++;
            fileReached++;
        }
        else
        {
            fileReached++;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------

void CConfig::fileGetString(LPSTR lpDest)
{
    dataCount = 0;
    // ----
    bool bNeedThis = true;
    // ----
    while(true)
    {
        if((dataFile[fileReached] == '"') || (bNeedThis == false))
        {
            bNeedThis = false;
            // ----
            if(dataFile[fileReached + 1] == '"')
            {
                fileReached++;
                fileReached++;
                // ---
                break;
            }
            // ----
            lpDest[dataCount] = dataFile[fileReached + 1];
            // ----
            dataCount++;
            fileReached++;
        }
        else
        {
            fileReached++;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------

int CConfig::fileGetInt()
{
	ZeroMemory(temp, MAX_CLASS_TEMP);
	// ----
    fileGetString(temp, MAX_CLASS_TEMP);
    // ----
    return atoi(temp);
}
//----------------------------------------------------------------------------------------------------------------

long CConfig::GetInt(long Min, long Max, long Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName)
{
	long lResult;

	WIN32_FIND_DATAA wfd;
	if (FindFirstFileA(FolderName, &wfd) == INVALID_HANDLE_VALUE)
	{	
		g_Setup.MsgBox("Error configs in %s!", FolderName);
		g_Setup.MsgBox("Can't find file!");
		g_Setup.MsgBox("Taked default value for %s(%ld)", ConfigName, Default);
		lResult = Default;
	}
	else
		lResult = GetPrivateProfileInt(BlockName, ConfigName, -100500, FolderName);

	if(lResult == -100500)
	{	   
		g_Setup.MsgBox("Error configs in %s!", FolderName);
		g_Setup.MsgBox("Can't find file!");
		g_Setup.MsgBox("Taked default value for %s(%ld)", ConfigName, Default);
		lResult = Default;
	}

	if(lResult < Min || lResult > Max)
	{
		g_Setup.MsgBox("Error configs in %s!", FolderName);
		g_Setup.MsgBox("Can't find file!");
		g_Setup.MsgBox("Taked default value for %s(%ld)", ConfigName, Default);
		lResult = Default;
	} 
	return lResult;
}
//----------------------------------------------------------------------------------------------------------------

bool CConfig::fileGetBool()
{
    bool bReturn = false;
    // ----
    fileGetString(temp, MAX_CLASS_TEMP);
    // ----
    if(_strcmpi(temp, "true") == 0)
    {
        bReturn = true;
    }
    else if(_strcmpi(temp, "false") == 0)
    {
        bReturn = false;
    }
    else
    {
		g_Setup.MsgBox("[CConfig][fileGetBool] :: in file : %s found unexpected word : %s", szPatchFile, temp);
        // ----
        ExitProcess(0);
    }
    // ----
    return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

void CConfig::fileClose()
{
    free(dataFile);
}
//----------------------------------------------------------------------------------------------------------------

 void CConfig::readFiles()
{
	readConfig();
	readUnallowedCharNames(CREATE_CHARACTER_UNALLOW_NAMES);
	readBadProcesses(BAD_PROCESS);
	// ----
	#ifdef GS_99_60T
	{
		if (!g_BotSystem.loadBots())
		{
			g_Setup.MsgBox("g_BotSystem.loadBots() :: failed");
		}

		g_MarrySystem.Init();
	}
	#endif
}
//----------------------------------------------------------------------------------------------------------------

void CConfig::readConfig()
{
	TIniFile IniConf("./Config.cfg", "Config");
	// ----
	isServerVip		= IniConf.ReadBool	("IsVIP",		true);
	VipServerLevel = IniConf.ReadInt	("VipServerLevel", 0);
	//nNoobServerCsResets	= IniConf.ReadInt	("CSResetNoobs",true);
	isKeepCommand	= IniConf.ReadBool	("IsKeep0Only", true);
	isGSUseItemLimit= IniConf.ReadBool	("IsItemLimit", true);
	nPort			= IniConf.ReadInt	("Port",		6000);
	KillEventDifClass = IniConf.ReadBool("KEDifClass",	false);
	KillEventMinRes = IniConf.ReadInt	("KEMinR",		0);
	KillEventGapRes = IniConf.ReadInt	("KEGapR",		0);
	KillEventStatus = IniConf.ReadBool	("KEStat",		false);
	// ----
	// # VIP System
	// ----
	IsVIPSystemOn = GetPrivateProfileInt("VIPSystem", "VIPSystemOn", true, "./FlameVIPSystem.ini");
	// VIP Bronze
	bPostCommand		= GetPrivateProfileInt("Bronze", "PostCommand", true, "./FlameVIPSystem.ini");
	bOffTradeCommand	= GetPrivateProfileInt("Bronze", "OffTradeCommand", true, "./FlameVIPSystem.ini");
	bVIPSing			= GetPrivateProfileInt("Bronze", "VIPSing", true, "./FlameVIPSystem.ini");
	bVIPDays			= GetPrivateProfileInt("Bronze", "VIPDays", 31, "./FlameVIPSystem.ini");
	bVIPPrice			= GetPrivateProfileInt("Bronze", "VIPPrice", 30, "./FlameVIPSystem.ini");
	// VIP Silver
	sPostCommand		= GetPrivateProfileInt("Silver", "PostCommand", true, "./FlameVIPSystem.ini");
	sOffTradeCommand	= GetPrivateProfileInt("Silver", "OffTradeCommand", true, "./FlameVIPSystem.ini");
	sVIPSing			= GetPrivateProfileInt("Silver", "VIPSing", true, "./FlameVIPSystem.ini");
	sVIPDays			= GetPrivateProfileInt("Silver", "VIPDays", 31, "./FlameVIPSystem.ini");
	sVIPPrice			= GetPrivateProfileInt("Silver", "VIPPrice", 30, "./FlameVIPSystem.ini");
	// VIP Gold
	gPostCommand		= GetPrivateProfileInt("Gold", "PostCommand", true, "./FlameVIPSystem.ini");
	gOffTradeCommand	= GetPrivateProfileInt("Gold", "OffTradeCommand", true, "./FlameVIPSystem.ini");
	gVIPSing			= GetPrivateProfileInt("Gold", "VIPSing", true, "./FlameVIPSystem.ini");
	gVIPDays			= GetPrivateProfileInt("Gold", "VIPDays", 31, "./FlameVIPSystem.ini");
	gVIPPrice			= GetPrivateProfileInt("Gold", "VIPPrice", 30, "./FlameVIPSystem.ini");
	// VIP Platinum
	pPostCommand		= GetPrivateProfileInt("Platinum", "PostCommand", true, "./FlameVIPSystem.ini");
	pOffTradeCommand	= GetPrivateProfileInt("Platinum", "OffTradeCommand", true, "./FlameVIPSystem.ini");
	pVIPSing			= GetPrivateProfileInt("Platinum", "VIPSing", true, "./FlameVIPSystem.ini");
	pVIPDays			= GetPrivateProfileInt("Platinum", "VIPDays", 31, "./FlameVIPSystem.ini");
	pVIPPrice			= GetPrivateProfileInt("Platinum", "VIPPrice", 30, "./FlameVIPSystem.ini");
	// ----
	// # OffTrade
	// ----
	IsOffTradeOn = GetPrivateProfileInt("config", "OffTradeOn", true, "./Config.cfg");
	IsOffTradeRestricedMap = GetPrivateProfileInt("config", "OffTradeRestrictedMaps", true, "./Config.cfg"); 
	nOffTradeMapNumber1 = GetPrivateProfileInt("config", "OffTradeMapNumber1", 0, "./Config.cfg"); 
	nOffTradeMapNumber1Cost = GetPrivateProfileInt("config", "OffTradeMapNumber1Cost", 2, "./Config.cfg");
	nOffTradeMapNumber2 = GetPrivateProfileInt("config", "OffTradeMapNumber2", 2, "./Config.cfg");
	nOffTradeMapNumber2Cost = GetPrivateProfileInt("config", "OffTradeMapNumber2Cost", 0, "./Config.cfg"); 
	nOffTradeMapNumber3 = GetPrivateProfileInt("config", "OffTradeMapNumber3", 2, "./Config.cfg"); 
	nOffTradeMapNumber3Cost = GetPrivateProfileInt("config", "OffTradeMapNumber3Cost", 0, "./Config.cfg"); 
	nOffTradeOnlyVIP = GetPrivateProfileInt("config", "OffTradeOnlyVIP", 0, "./Config.cfg");
	// ----
	nKandunPrice = GetPrivateProfileInt("config", "KandunPrice", 10, "./Config.cfg");
	// ----
	IsGoldenGiveCredit = GetPrivateProfileInt("config", "GoldenGiveCredit", false, "./Config.cfg");
	// ----
	iRedDragonAttackRate = GetPrivateProfileInt("RedDragonSettings", "AttackRate", 1800000, "./FlameRedDragon.ini");
	iRedDragonAttackSpeed = GetPrivateProfileInt("RedDragonSettings", "AttackSpeed", 20000, "./FlameRedDragon.ini");
	iRedDragonAttackRange = GetPrivateProfileInt("RedDragonSettings", "AttackRange", 2000, "./FlameRedDragon.ini");
	iRedDragonDefense = GetPrivateProfileInt("RedDragonSettings", "AttackRange", 2000000, "./FlameRedDragon.ini");
	iRedDragonMaxDmg = GetPrivateProfileInt("RedDragonSettings", "MaxDmg", 1100000, "./FlameRedDragon.ini");
	iRedDragonMinDmg = GetPrivateProfileInt("RedDragonSettings", "MinDmg", 600000, "./FlameRedDragon.ini");
	iRedDragonHP = GetPrivateProfileInt("RedDragonSettings", "HP", 500000000, "./FlameRedDragon.ini");
	iRedDragonLevel = GetPrivateProfileInt("RedDragonSettings", "Level", 200, "./FlameRedDragon.ini");
	iRedDragonPrizeCredits = GetPrivateProfileInt("RedDragonSettings", "PrizeCredits", 6, "./FlameRedDragon.ini");
	// ----
	nServerCode		= GetPrivateProfileInt("GameServerInfo","ServerCode", 0,"Data\\ServerInfo.dat");
	// ----
	sprintf(temp, "GameServer%d", nServerCode);
	// ----
	g_HackLog.setCode(nServerCode);
	g_MailLog.setCode(nServerCode);
	g_GmsLog.setCode(nServerCode);
	g_ChatLog.setCode(nServerCode);
	g_ChatWhispLog.setCode(nServerCode);
	g_ChatWhispLogGM.setCode(nServerCode);
	g_EventLog.setCode(nServerCode);
	g_CreateItemLog.setCode(nServerCode);
	g_TradeLog.setCode(nServerCode);
	g_ShopLog.setCode(nServerCode);
	g_ResetLog.setCode(nServerCode);
	g_CoinShopLog.setCode(nServerCode);
	g_ProcessesLog.setCode(nServerCode);
	// ----
	#ifndef GS_99_60T
		g_KillerLog.setCode(nServerCode);
	#endif
}
//----------------------------------------------------------------------------------------------------------------

bool CConfig::readUnallowedCharNames(std::string patch)
{
	bool bReturn = false;
	// ----
	CreateCharacterUnallowedList.clear();
	// ----
	if(fileRead((LPSTR)patch.c_str()) == true)
	{
		do
		{
			tagCFG_UNALLOWED_NAMES Conf;
			// ----
			memset(& Conf, 0x00 , sizeof(Conf));
			// ----
			// # Name
			// ----
			fileGetString(Conf.Nick, sizeof(Conf.Nick));
			// ----
			CreateCharacterUnallowedList.push_back(Conf);
		}
		while(fileIsEnd() == false);
		// ----
		fileClose();
		// -----
		bReturn = true;
	}
	// ----
	return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

bool CConfig::readBadProcesses(std::string patch)
{
	bool bReturn = false;
	// ----
	BadProcessesList.clear();
	// ----
	if (fileRead((LPSTR)patch.c_str()) == true)
	{
		do
		{
			char szTemp[200] = { 0 };

			fileGetString(szTemp, sizeof(szTemp));
			// ----
			BadProcessesList.push_back(_atoi64((const char *)szTemp));
		} while (fileIsEnd() == false);
		// ----
		fileClose();
		// -----
		bReturn = true;
	}
	// ----
	return bReturn;
}
//----------------------------------------------------------------------------------------------------------------
// leo: not the place for this funciton

bool CConfig::UnAllowedNamesCheck(char * name)
{
	bool bReturn = true;
	// ----
	std::string name_str, check;
	name_str = name;
	for(UNALLOWED_NAMES_LIST::iterator it = CreateCharacterUnallowedList.begin() ; it != CreateCharacterUnallowedList.end() ; ++it)
	{
		// ----
		check = it->Nick;
		if (name_str.find(check) != std::string::npos)
		{
			g_HackLog.Output("[CConfig][TryUnAllowedNick] :: Tried %s with %s", name_str.c_str(), check.c_str());
			bReturn = false;
			break;
		}
		// ----
	}
	return bReturn;
}
//----------------------------------------------------------------------------------------------------------------