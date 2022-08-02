//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "GConfig.h"
#include "GLog.h"
//----------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TConfig"
//----------------------------------------------------------------------------------------------------------------

char		findGershaim[] = {'"', 0x00};
//----------------------------------------------------------------------------------------------------------------

TConfig			g_Config;
//----------------------------------------------------------------------------------------------------------------

void replace_char(char * src, char find, char replace)
{
	while(*src)
	{
		if(*src == find)
		{
			*src = replace;
		}
		// ----
		src++;
	}
}
//----------------------------------------------------------------------------------------------------------------

TConfig::TConfig(void)
{
    Init();
}
// ----------------------------------------------------------------------------------------------------------------

TConfig::~TConfig(void)
{
    // ----
}
//----------------------------------------------------------------------------------------------------------------

bool TConfig::fileRead(LPSTR szPatch)
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
                g_Log.MsgBox("[TConfig][fileRead] :: error : fread %d", __LINE__);
            }
            // ----
            fclose(handleFile);
            // ----
            bReturn = true;
        }
    }
	else
	{
		g_Log.AddMSB(-1, g_ModuleName, __FUNCTION__, "file %s reading error %d", szPatch, GetLastError());
	}
    // ----
    return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

bool TConfig::fileIsEnd()
{
	char Temp[1024] = {0};
	// ----
	dataCount = 0;
	// ----
	bool bNeedThis = true;
	// ----
	int fileRechTemp = fileReached;
	// ----
	try
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
	catch(...)
	{
		return true;
	}
	// ----
	return false;
}
//----------------------------------------------------------------------------------------------------------------

void TConfig::fileGetString(LPSTR lpDest, int nDestLen)
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

void TConfig::fileGetString(LPSTR lpDest)
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

int TConfig::fileGetInt()
{
	ZeroMemory(temp, MAX_CLASS_TEMP);
	// ----
    fileGetString(temp, MAX_CLASS_TEMP);
    // ----
    return atoi(temp);
}
//----------------------------------------------------------------------------------------------------------------

bool TConfig::fileGetBool()
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
        g_Log.MsgBox("[TConfig][fileGetBool] :: in file : %s found unexpected word : %s", szPatchFile, temp);
        // ----
        ExitProcess(0);
    }
    // ----
    return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

void TConfig::fileClose()
{
    free(dataFile);
}
//----------------------------------------------------------------------------------------------------------------

void TConfig::Init()
{

}
//----------------------------------------------------------------------------------------------------------------

bool TConfig::readGmsAccessList(std::string patch)
{
	bool bReturn = false;
	// ----
	GMSAccessList.clear();
	// ----
	if(fileRead((LPSTR)patch.c_str()) == true)
	{
		do
		{
			tagCFG_GMS_ACCESS Conf;
			// ----
			memset(& Conf, 0x00 , sizeof(Conf));
			// ----
			// # Name
			// ----
			fileGetString(Conf.Nick, sizeof(Conf.Nick));
			// ----
			// # New 2 options of ban
			// ----
			Conf.isBanForeverEditAllow	= fileGetBool();
			Conf.isAllowUseNewBan		= fileGetBool();
			Conf.isUnBan				= fileGetBool();
			Conf.isGreenMSGAllow		= fileGetBool();
			Conf.isMsgChangeAllow		= fileGetBool();
			// ----
			GMSAccessList.push_back(Conf);
		}
		while(fileIsEnd() == false);
		// ----
		fileClose();
		// -----
		g_Log.Add(-1, g_ModuleName, __FUNCTION__, "Loaded FROM GMSAccessList Count : %u", GMSAccessList.size());
		// ----
		bReturn = true;
	}
	// ----
	return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

bool TConfig::readGameServerList(std::string patch)
{
	bool bReturn = false;
	// ----
	GSSServerList.clear();
	// ----
	if(fileRead((LPSTR)patch.c_str()) == true)
	{
		do
		{
			tagCFG_GAMESERVER_LIST Conf;
			// ----
			Conf.Clear();
			// ----
			// # Port
			// ----
			Conf.uPort		= fileGetInt();
			// ----
			// # Gs Code
			// ----
			Conf.bGSCode	= fileGetInt();
			// ----
			// # TitleName & Nice Name
			// ----
			fileGetString(Conf.szGSTitleName, sizeof(Conf.szGSTitleName));
			fileGetString(Conf.szGSNiceName, sizeof(Conf.szGSTitleName));
			// ----
			// # Gs Code Game
			// ----
			Conf.bGSCodeGame	= fileGetInt();
			// ----
			GSSServerList.push_back(Conf);
		}
		while(fileIsEnd() == false);
		// ----
		fileClose();
		// -----
		g_Log.Add(-1, g_ModuleName, __FUNCTION__, "Print %s Count : %u", patch.c_str(), GSSServerList.size());
		// ----
		for(BYTE i = 0 ; i != GSSServerList.size(); ++i)
		{
			g_Log.AddC(GSSServerList.at(i).bGSCode, g_ModuleName, __FUNCTION__, TColor::DarkOrange, 
				"%d][%s][%s][OK", GSSServerList[i].uPort, GSSServerList[i].szGSTitleName, GSSServerList[i].szGSNiceName);
		}
		// ----
		bReturn = true;
	}
	// ----
	return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

bool TConfig::readBadProcesses(std::string patch)
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
			// ----
			fileGetString(szTemp, sizeof(szTemp));
			// ----
			BadProcessesList.push_back(_atoi64((const char *)szTemp));
		} while (fileIsEnd() == false);
		// ----
		fileClose();
		// ----
		g_Log.Add(-1, g_ModuleName, __FUNCTION__, "Print %s Count : %u", patch.c_str(), BadProcessesList.size());
		// -----
		bReturn = true;
	}
	// ----
	return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

bool TConfig::readGoodProcesses(std::string patch)
{
	bool bReturn = false;
	// ----
	GoodProcessesList.clear();
	// ----
	if (fileRead((LPSTR)patch.c_str()) == true)
	{
		do
		{
			char szTemp[200] = { 0 };
			// ----
			fileGetString(szTemp, sizeof(szTemp));
			// ----
			GoodProcessesList.push_back(_atoi64((const char *)szTemp));
		} while (fileIsEnd() == false);
		// ----
		fileClose();
		// ----
		g_Log.Add(-1, g_ModuleName, __FUNCTION__, "Print %s Count : %u", patch.c_str(), GoodProcessesList.size());
		// -----
		bReturn = true;
	}
	// ----
	return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

lptagCFG_GMS_ACCESS TConfig::getGMSAccessListByName(std::string Name)
{
	lptagCFG_GMS_ACCESS lpReturn = NULL;
	// ----
	for(GMS_ACCESS_LIST::iterator it = GMSAccessList.begin() ; it != GMSAccessList.end() ; ++it)
	{
		if(_strcmpi(Name.c_str(), it->Nick) == 0)
		{
			lpReturn = & (*it);
			// ----
			break;
		}
	}
	// ----
	return lpReturn;
}
//----------------------------------------------------------------------------------------------------------------

void TConfig::getServerNameByGSName(LPSTR lpDest, LPSTR Name)
{
	for(int i = 0 ; i != GSSServerList.size() ; ++i)
	{
		if(_strcmpi(Name, GSSServerList.at(i).szGSTitleName) == 0)
		{
			memcpy(lpDest, GSSServerList.at(i).szGSNiceName, 40);
			// ----
			break;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------

void TConfig::getServerNameByGSCode(LPSTR lpDest, BYTE Code)
{
	for(int i = 0 ; i != GSSServerList.size() ; ++i)
	{
		if(GSSServerList.at(i).bGSCode == Code)
		{
			memcpy(lpDest, GSSServerList.at(i).szGSNiceName, 40);
			// ----
			break;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------

BYTE TConfig::getGSCodeGameByGSName(LPSTR Name)
{
	BYTE cReturn = 0;
	for(int i = 0 ; i != GSSServerList.size() ; ++i)
	{
		if(_strcmpi(Name, GSSServerList.at(i).szGSTitleName) == 0)
		{
			cReturn = GSSServerList.at(i).bGSCodeGame;
			// ----
			break;
		}
	}
	return cReturn;
}
//----------------------------------------------------------------------------------------------------------------

bool TConfig::readInspectAccessList(std::string patch)
{
	bool bReturn = false;
	// ----
	Inspect_AccessList.clear();
	// ----
	if(fileRead((LPSTR)patch.c_str()) == true)
	{
		do
		{
			tagCFG_INSPECT_ACCESS Conf;
			// ----
			memset(& Conf, 0x00 , sizeof(Conf));
			// ----
			// # Name
			// ----
			fileGetString(Conf.Nick, sizeof(Conf.Nick));
			// ----
			// # Commands
			// ----
			Conf.Move			= fileGetBool();
			Conf.Disconnect		= fileGetBool();
			Conf.Jump			= fileGetBool();
			Conf.Come			= fileGetBool();
			Conf.Ban			= fileGetBool();
			Conf.Baunsers		= fileGetBool();
			Conf.Vote			= fileGetBool();
			Conf.isHackLogAllow = fileGetBool();
			// ----
			Inspect_AccessList.push_back(Conf);
		}
		while(fileIsEnd() == false);
		// ----
		fileClose();
		// -----
		g_Log.Add(-1, g_ModuleName, __FUNCTION__, "Loaded FROM InpectAccessList Count : %u", Inspect_AccessList.size());
		// ----
		bReturn = true;
	}
	// ----
	return bReturn;
}
//----------------------------------------------------------------------------------------------------------------

lptagCFG_INSPECT_ACCESS TConfig::getINSPECTAccessListByName(std::string Name)
{
	lptagCFG_INSPECT_ACCESS lpReturn = NULL;
	// ----
	for(INSPECT_ACCESS_LIST::iterator it = Inspect_AccessList.begin() ; it != Inspect_AccessList.end() ; ++it)
	{
		if(_strcmpi(Name.c_str(), it->Nick) == 0)
		{
			lpReturn = & (*it);
			// ----
			break;
		}
	}
	// ----
	return lpReturn;
}
//----------------------------------------------------------------------------------------------------------------