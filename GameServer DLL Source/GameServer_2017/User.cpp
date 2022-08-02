#include "stdafx.h"
#include "User.h"
#include "TLogToFile.h"
#include "TBotSystem.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # Made By Leo123[BoR] -> GS 99.60T -> Only for MuOnline.co.il

OBJECTSTRUCT *	gObj = (OBJECTSTRUCT*)OBJECT_BASE;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DWORD g_dwDLBestAttack = GetTickCount();
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int gObjGetIndexByName(char * Name)
{
    for(USHORT n = OBJECT_START_INDEX; n < OBJECT_MAX_INDEX; n++)
    {
        if(gObj[n].Connected >= PLAYER_PLAYING)
        {
            if(_strcmpi(gObj[n].Name , Name) == 0)
            {
                return n;
            }
        }
    }
	// ----
    return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int gObjGetIndexByAccountId(char * szAcccountId)
{
	for (USHORT n = OBJECT_START_INDEX; n < OBJECT_MAX_INDEX; n++)
	{
		if (gObj[n].Connected >= PLAYER_LOGGED)
		{
			if (_strcmpi(gObj[n].AccountID, szAcccountId) == 0)
			{
				return n;
			}
		}
	}
	// ----
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool gObjIsGameMaster(int aIndex)
{
	if(gObjIsConnected(aIndex) == true)
	{
		if((gObj[aIndex].Authority == 32) || gObj[aIndex].Authority == 2)
		{
			return true;
		}
	}
	// ----
	return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool gObjIsGameSI(int aIndex)
{
	if(gObjIsConnected(aIndex) == true)
	{
		if((gObj[aIndex].Authority == 32) || gObj[aIndex].Authority == 2)
		{
			std::string s1 = gObj[aIndex].Name;
			if (s1.back() == 'I')
			{
				s1.pop_back();
				if (s1.back() == 'S')
				{
					return true;
				}
			}
		}
	}
	// ----
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int gObjGetMapLevel(int Map,int Class)
{
	int iReturn					=  -1;
	// ----
	if(Class == 3 || Class == 4)
	{
		switch (Map)
		{
			case 0:		iReturn =  33;	break;
			case 1:		iReturn =  33;	break;
			case 2:		iReturn =  33;	break;
			case 3:		iReturn =  33;	break;
			case 4:		iReturn =  60;	break;
			case 6:		iReturn =  186;	break;
			case 7:		iReturn =  46;	break;
			case 8:		iReturn =  93;	break;
			case 10:	iReturn =  120; break;
		}
	}
	else
	{
		switch (Map)
		{
			case 0:		iReturn =  50;	break;
			case 1:		iReturn =  50;	break;
			case 2:		iReturn =  50;	break;
			case 3:		iReturn =  50;	break;
			case 4:		iReturn =  90;	break;
			case 6:		iReturn =  280; break;
			case 7:		iReturn =  70;	break;
			case 8:		iReturn =  140;	break;
			case 10:	iReturn =  180;	break;
		}
	}
	// ----
	return iReturn;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LPCSTR gObjGetClassName(int aIndex)
{
	LPCSTR lpReturn = "Unknown";
	// ----
	switch (gObj[aIndex].DbClass)
	{
		case 0:		lpReturn = "Dark Wizard";		break;
		case 1:		lpReturn = "Soul Master";		break;
		case 16:	lpReturn = "Dark Knight";		break;
		case 17:	lpReturn = "Blade Knight";		break;
		case 32:	lpReturn = "Fairy Elf";			break;
		case 33:	lpReturn = "Muse Elf";			break;
		case 48:	lpReturn = "Magic Gladiator";	break;
		case 64:	lpReturn = "Dark Lord";			break;
	}
	// ----
	return lpReturn;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LPCSTR	gObjGetClassNameByID(int ID)
{
	LPCSTR lpReturn = "Unknown";
	// ----
	switch (ID)
	{
		case 0:		lpReturn = "Dark Wizard";		break;
		case 1:		lpReturn = "Soul Master";		break;
		case 16:	lpReturn = "Dark Knight";		break;
		case 17:	lpReturn = "Blade Knight";		break;
		case 32:	lpReturn = "Fairy Elf";			break;
		case 33:	lpReturn = "Muse Elf";			break;
		case 48:	lpReturn = "Magic Gladiator";	break;
		case 64:	lpReturn = "Dark Lord";			break;
	}
	// ----
	return lpReturn;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LPCSTR GetMapName(int aIndex)
{
	LPCSTR	lpReturn	= "Unknown";
	int		MapID		= gObj[aIndex].MapNumber;
	// ----
	switch (MapID)
	{
		case 0:		lpReturn = "Lorencia";			break;
		case 1:		lpReturn = "Dungeon";			break;
		case 2:		lpReturn = "Davais";			break;
		case 3:		lpReturn = "Noria";				break;
		case 4:		lpReturn = "Lost Tower";		break;
		case 5:		lpReturn = "Unknown";			break;
		case 6:		lpReturn = "Arena";				break;
		case 7:		lpReturn = "Atlans";			break;
		case 8:		lpReturn = "Tarkan";			break;
		case 9:		lpReturn = "Devil Square";		break;
		case 10:	lpReturn = "Icarus";			break;
		// ----
		case 11:	lpReturn = "Blood Castle 1";	break;
		case 12:	lpReturn = "Blood Castle 2";	break;
		case 13:	lpReturn = "Blood Castle 3";	break;
		case 14:	lpReturn = "Blood Castle 4";	break;
		case 15:	lpReturn = "Blood Castle 5";	break;
		case 16:	lpReturn = "Blood Castle 6";	break;
		case 17:	lpReturn = "Blood Castle 7";	break;
		// ----
		case 18:	lpReturn = "Chaos Castle 1";	break;
		case 19:	lpReturn = "Chaos Castle 2";	break;
		case 20:	lpReturn = "Chaos Castle 3";	break;
		case 21:	lpReturn = "Chaos Castle 4";    break;
		case 22:	lpReturn = "Chaos Castle 5";	break;
		case 23:	lpReturn = "Chaos Castle 6";	break;
		// ----
		case 24:	lpReturn = "Kalima 1";			break;
		case 25:	lpReturn = "Kalima 2";			break;
		case 26:	lpReturn = "Kalima 3";			break;
		case 27:	lpReturn = "Kalima 4";			break;
		case 28:	lpReturn = "Kalima 5";			break;
		case 29:	lpReturn = "Kalima 6";			break;
		// ----
		case 30:	lpReturn = "Valley of Loren";	break;
		case 31:	lpReturn = "Land Of Trials";	break;
	}
	//	----
	return lpReturn;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LPCSTR	GetMapNameHeByID(int ID)
{
	LPCSTR	lpReturn	= "Unknown";
	// ----
	switch (ID)
	{
		case 0:		lpReturn = "לורנסיה";			break;
		case 1:		lpReturn = "דאנגן";			break;
		case 2:		lpReturn = "דויאס";			break;
		case 3:		lpReturn = "נוריה";				break;
		case 4:		lpReturn = "לוסט טאור";		break;
		case 5:		lpReturn = "Unknown";			break;
		case 6:		lpReturn = "ארנה";				break;
		case 7:		lpReturn = "אטלנס";			break;
		case 8:		lpReturn = "טרקן";			break;
		case 9:		lpReturn = "Devil Square";		break;
		case 10:	lpReturn = "איכרוס";			break;
		// ----
		case 11:	lpReturn = "Blood Castle 1";	break;
		case 12:	lpReturn = "Blood Castle 2";	break;
		case 13:	lpReturn = "Blood Castle 3";	break;
		case 14:	lpReturn = "Blood Castle 4";	break;
		case 15:	lpReturn = "Blood Castle 5";	break;
		case 16:	lpReturn = "Blood Castle 6";	break;
		case 17:	lpReturn = "Blood Castle 7";	break;
		// ----
		case 18:	lpReturn = "Chaos Castle 1";	break;
		case 19:	lpReturn = "Chaos Castle 2";	break;
		case 20:	lpReturn = "Chaos Castle 3";	break;
		case 21:	lpReturn = "Chaos Castle 4";    break;
		case 22:	lpReturn = "Chaos Castle 5";	break;
		case 23:	lpReturn = "Chaos Castle 6";	break;
		// ----
		case 24:	lpReturn = "Kalima 1";			break;
		case 25:	lpReturn = "Kalima 2";			break;
		case 26:	lpReturn = "Kalima 3";			break;
		case 27:	lpReturn = "Kalima 4";			break;
		case 28:	lpReturn = "Kalima 5";			break;
		case 29:	lpReturn = "Kalima 6";			break;
		// ----
		case 30:	lpReturn = "Valley of Loren";	break;
		case 31:	lpReturn = "Land Of Trials";	break;
	}
	// ----
	return lpReturn;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LPCSTR	GetMapNameByID(int ID)
{
	LPCSTR	lpReturn	= "Unknown";
	// ----
	switch (ID)
	{
		case 0:		lpReturn = "Lorencia";			break;
		case 1:		lpReturn = "Dungeon";			break;
		case 2:		lpReturn = "Davais";			break;
		case 3:		lpReturn = "Noria";				break;
		case 4:		lpReturn = "Lost Tower";		break;
		case 5:		lpReturn = "Unknown";			break;
		case 6:		lpReturn = "Arena";				break;
		case 7:		lpReturn = "Atlans";			break;
		case 8:		lpReturn = "Tarkan";			break;
		case 9:		lpReturn = "Devil Square";		break;
		case 10:	lpReturn = "Icarus";			break;
		// ----
		case 11:	lpReturn = "Blood Castle 1";	break;
		case 12:	lpReturn = "Blood Castle 2";	break;
		case 13:	lpReturn = "Blood Castle 3";	break;
		case 14:	lpReturn = "Blood Castle 4";	break;
		case 15:	lpReturn = "Blood Castle 5";	break;
		case 16:	lpReturn = "Blood Castle 6";	break;
		case 17:	lpReturn = "Blood Castle 7";	break;
		// ----
		case 18:	lpReturn = "Chaos Castle 1";	break;
		case 19:	lpReturn = "Chaos Castle 2";	break;
		case 20:	lpReturn = "Chaos Castle 3";	break;
		case 21:	lpReturn = "Chaos Castle 4";    break;
		case 22:	lpReturn = "Chaos Castle 5";	break;
		case 23:	lpReturn = "Chaos Castle 6";	break;
		// ----
		case 24:	lpReturn = "Kalima 1";			break;
		case 25:	lpReturn = "Kalima 2";			break;
		case 26:	lpReturn = "Kalima 3";			break;
		case 27:	lpReturn = "Kalima 4";			break;
		case 28:	lpReturn = "Kalima 5";			break;
		case 29:	lpReturn = "Kalima 6";			break;
		// ----
		case 30:	lpReturn = "Valley of Loren";	break;
		case 31:	lpReturn = "Land Of Trials";	break;
	}
	// ----
	return lpReturn;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BYTE LevelSmallConvert(int level)
{
	if(level >= 13)
	{
		return 6;
	}
	// ----
	if(level >= 11 && level <=12)
	{
		return 5;
	}
	// ----
	if(level >= 9 && level <= 10)
	{
		return 4;
	}
	// ----
	if(level >= 7 && level <= 8)
	{
		return 3;
	}
	// ----
	if(level >= 5 && level <= 6)
	{
		return 2;
	}
	// ----
	if(level >= 3 && level <= 4)
	{
		return 1;
	}
	// ----
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool gObjIsAccontConnect(int aIndex, char * szAccountID)
{
	bool bReturn = false;
	// ----
	if((aIndex > 0) && (aIndex < OBJECT_MAX_INDEX -1))
	{
		if(gObj[aIndex].Connected >= PLAYER_LOGGED)
		{
			if(strlen(gObj[aIndex].AccountID) > 0)
			{
				if(_strcmpi(gObj[aIndex].AccountID, szAccountID) == 0)
				{
					bReturn = true;
				}
			}
		}
	}
	// ----
	return bReturn;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool gObjIsAccontConnect(char * szAccountID)
{
	bool bReturn = false;
	// ----
	for(int n = OBJECT_START_INDEX; n < OBJECT_MAX_INDEX; n++)
	{
		if(_strcmpi(gObj[n].AccountID, szAccountID) == 0)
		{
			if(gObjIsAccontConnect(n, szAccountID) == true) 
			{
				bReturn = true;
			}
			// ----
			break;
		}
	}
	// ----
	return bReturn;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void gObjCastRegen(int aIndex, int gt)
{
	OBJECTSTRUCT * lpObj		= & gObj[aIndex];
	// ----
	int x						= lpObj->X;
	int y						= lpObj->Y;
	int Map						= lpObj->MapNumber;
	// ----
	lpObj->RegenMapNumber	= Map;
	lpObj->RegenMapX		= x;
	lpObj->RegenMapY		= y;
	// ----
	g_GS.gObjClearViewportofMine(lpObj);
	// ----
	g_GS.GCTeleportSend(lpObj, gt, lpObj->MapNumber, lpObj->X, lpObj->Y, lpObj->Dir);
	// ----
	if(lpObj->m_Change >= 0)
	{
		g_GS.gObjViewportListProtocolCreate(lpObj);
	}
	// ----
	lpObj->RegenOk		= 1;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool isMoveNGate(int gt)
{
	bool bReturn = true;
	// ----
	switch(gt)
	{
		case 50:
		case 17:
		case 27:
		case 22:
		case 72:
		case 73:
		case 74:
		case 2:
		case 6:
		case 10:
		case 49:
		case 75:
		case 76:
		case 42:
		case 31:
		case 33:
		case 35:
		case 37:
		case 39:
		case 41:
		case 57:
		case 77:
		case 63:
		case 104:
		{
			bReturn = false;
		}
		break;

		default:
		{
			bReturn = true;
		}
		break;
	}
	// ----
	return bReturn;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void PHeadSetB(LPBYTE lpBuf, BYTE head, int size)
{
	lpBuf[0]	= 0xC1;
	lpBuf[1]	= size;
	lpBuf[2]	= head;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
{
	lpBuf[0]	= 0xC1;
	lpBuf[1]	= size;
	lpBuf[2]	= head;
	lpBuf[3]	= sub;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GCJoinResult(BYTE result, int aIndex)
{
	PMSG_RESULT  pResult;

	PHeadSubSetB((LPBYTE)&pResult, 0xF1, 0x01, sizeof(pResult));
	pResult.result = result;
	g_GS.DataSend(aIndex, (UCHAR*)&pResult, pResult.h.size);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOOL gObjIsConnected(int Index)
{
	OBJECTSTRUCT * lpObj		= & gObj[Index];

	if (g_BotSystem.isThatBot(Index)) {
		return false;
	}

	if (lpObj->Type != OBJ_USER) {
		return false;
	}

	if (lpObj->Connected < PLAYER_PLAYING ) {
		return false;
	}

	if (lpObj->CloseCount > 0 ) {
		return false;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void FireworkOnTheScreen(int aIndex)
{					   
	PMSG_SERVERCMD ServerCmd;
	PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
	ServerCmd.CmdType = 0;
	for(int x = 0; x < 10; x+=2)
	{
		for(int y = 0; y < 10; y+=2)
		{
			ServerCmd.X = gObj[aIndex].X + x - 5;
			ServerCmd.Y = gObj[aIndex].Y + y - 5;
			g_GS.MsgSendV2((DWORD)& gObj[aIndex], (LPBYTE)&ServerCmd, sizeof(ServerCmd));	   
			g_GS.DataSend(aIndex, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool gObjCheckUserResets (int aIndex, int Reset)
{
	int SumPoints = 0, SumPointsCheck = 0;
	_NEW_OBJECT * nObject = & g_GS.nObject[FIXINDEX];
	if (nObject->Resets <= Reset && nObject->Resets >= 0)
	{
		switch (gObj[aIndex].Class)
		{
			case 3:
			case 4:
				{
					SumPoints = (gObj[aIndex].Strength + gObj[aIndex].Dexterity + gObj[aIndex].Vitality + gObj[aIndex].Energy + gObj[aIndex].Leadership + gObj[aIndex].LevelUpPoint);
					SumPointsCheck = 110 + (Reset+1)*2793+250;
					g_ResetLog.Output("Dsx-SQL Reset: %d; Game Reset: %d", nObject->Resets, SumPoints/2793);
					if (SumPoints <= SumPointsCheck)
					{
						return true; 
					}
				}
			break;
			case 0:
			case 1:
			case 2:
				{
					SumPoints = (gObj[aIndex].Strength + gObj[aIndex].Dexterity + gObj[aIndex].Vitality + gObj[aIndex].Energy + gObj[aIndex].Leadership + gObj[aIndex].LevelUpPoint);
					SumPointsCheck = 80 + ((Reset+1) * 2195);
					g_ResetLog.Output("Dsx-SQL Reset: %d; Game Reset: %d", nObject->Resets, SumPoints/2195);
					if (SumPoints <= SumPointsCheck)
					{
						return true; 
					}
				}
			break;
		}	
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool gObjCheckUserResets (int aIndex, int Reset, int RResets)
{
	int SumPoints = 0, SumPointsCheck = 0;
	if (RResets < Reset && RResets >= 0)
	{
		switch (gObj[aIndex].Class)
		{
			case 3:
			case 4:
				{
					SumPoints = (gObj[aIndex].Strength + gObj[aIndex].Dexterity + gObj[aIndex].Vitality + gObj[aIndex].Energy + gObj[aIndex].Leadership + gObj[aIndex].LevelUpPoint);
					SumPointsCheck = Reset*2793;
					g_ResetLog.Output("Dsx-SQL Reset: %d; Game Reset: %d", RResets, SumPoints/2793);
					if (SumPoints <= SumPointsCheck)
					{
						return true; 
					}
				}
			break;
			case 0:
			case 1:
			case 2:
				{
					SumPoints = (gObj[aIndex].Strength + gObj[aIndex].Dexterity + gObj[aIndex].Vitality + gObj[aIndex].Energy + gObj[aIndex].Leadership + gObj[aIndex].LevelUpPoint);
					SumPointsCheck = 80 + (Reset * 2195);
					g_ResetLog.Output("Dsx-SQL Reset: %d; Game Reset: %d", RResets, SumPoints/2195);
					if (SumPoints <= SumPointsCheck)
					{
						return true; 
					}
				}
			break;
		}	
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool gObjCheckUserResetsGap (int aIndex, int tIndex, int ResetGap, int minResets, bool difClass)
{
	if (difClass == false && gObj[aIndex].Class != gObj[tIndex].Class)
		return false;
	// ----
	_NEW_OBJECT * nObject = & g_GS.nObject[FIXINDEX];
	_NEW_OBJECT * tObject = & g_GS.nObject[NINDEX(tIndex)];
	// ----
	int aResets = 0;
	int bResets = 0;
	// ----
	double SumPoints = 0, SumPointsT = 0;
	// ----
	SumPoints = (gObj[aIndex].Strength + gObj[aIndex].Dexterity + gObj[aIndex].Vitality + gObj[aIndex].Energy + gObj[aIndex].Leadership + gObj[aIndex].LevelUpPoint);
	SumPointsT = (gObj[tIndex].Strength + gObj[tIndex].Dexterity + gObj[tIndex].Vitality + gObj[tIndex].Energy + gObj[tIndex].Leadership + gObj[tIndex].LevelUpPoint);	
	// ----
	if (SumPoints > 131000 && SumPointsT > 131000) // full players
		return true;
	// ----
	if (abs(nObject->Resets-tObject->Resets) <= ResetGap)
	{
		switch (gObj[aIndex].Class)
		{
			case 3:
			case 4:
				{
					aResets = (SumPoints + 110) / 2793;
				}
				break;
			case 0:
			case 1:
			case 2:
				{
					aResets = (SumPoints + 80) / 2195;
				}
				break;
		}
		// ----
		switch (gObj[tIndex].Class)
		{
			case 3:
			case 4:
				{
					SumPoints = (gObj[tIndex].Strength + gObj[tIndex].Dexterity + gObj[tIndex].Vitality + gObj[tIndex].Energy + gObj[tIndex].Leadership + gObj[tIndex].LevelUpPoint);
					bResets = (SumPoints + 110) / 2793;
				}
				break;
			case 0:
			case 1:
			case 2:
				{
					SumPoints = (gObj[tIndex].Strength + gObj[tIndex].Dexterity + gObj[tIndex].Vitality + gObj[tIndex].Energy + gObj[tIndex].Leadership + gObj[tIndex].LevelUpPoint);
					bResets = (SumPoints + 80) / 2195;
				}
				break;
		}
		// ----
		if ((abs(aResets-bResets) <= ResetGap) && (aResets > minResets) && (bResets > minResets))
		{
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool PacketCheckTime(OBJECTSTRUCT * lpObj)
{
	if ((GetTickCount() - lpObj->m_PacketCheckTime) < 300) {
		return false;
	}

	lpObj->m_PacketCheckTime = GetTickCount();

	return true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool gObjFixInventoryPointer(int aIndex)
{
	#ifdef GS_99_60T

	if (gObjIsConnected(aIndex) == 0) {
		g_GS.LogAdd("[Fix Inv.Ptr] [%s][%s] - disconnected", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return false;
	}

	if (gObj[aIndex].pInventory == gObj[aIndex].Inventory1) {
		return true;
	}

	if (gObj[aIndex].pInventory == gObj[aIndex].Inventory2) {
		if (gObj[aIndex].pTransaction == 1) {
			g_GS.LogAdd("[Fix Inv.Ptr] [%s][%s] - Transaction == 1, Do not change Pointer", gObj[aIndex].AccountID, gObj[aIndex].Name);
			return false;
		} else {
			g_GS. LogAdd("[Fix Inv.Ptr] [%s][%s] - Inventory Pointer was 2", gObj[aIndex].AccountID, gObj[aIndex].Name);

			for (int n = 0; n < INVENTORY_SIZE; n++) {
				gObj[aIndex].Inventory2[n].Clear();
			}
		}
	} else {
		g_GS.LogAdd("[Fix Inv.Ptr] [%s][%s] - Inventory Pointer was Wrong", gObj[aIndex].AccountID, gObj[aIndex].Name);
	}

	gObjSetInventory1Pointer(&gObj[aIndex]);

	#endif

	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void gObjSetInventory1Pointer(OBJECTSTRUCT * lpObj)
{
	#ifdef GS_99_60T

	lpObj->pInventory = lpObj->Inventory1;
	lpObj->pInventoryMap = lpObj->InventoryMap1;
	lpObj->pInventoryCount = &lpObj->InventoryCount1;

	#endif
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool gObjIsFreeSlotForItem(int aIndex, CItem item)
{
	#ifdef GS_99_60T

	int w, h, iwidth, iheight;
	BYTE blank = 0;

	item.GetSize(iwidth, iheight);

	for (h = 0; h < 8; h++) {
		for (h = 0; h < 8; h++) {
			for (w = 0; w < 8; w++) {
				if (*(BYTE*)(gObj[aIndex].pInventoryMap + h * 8 + w) == 255)
				{
					blank = g_GS.gObjOnlyInventoryRectCheck(aIndex, w, h, iwidth, iheight);

					if (blank == 254)
					{
						goto GOTO_EndFunc;
					}

					if (blank != 255)
					{
						return true;
					}
				}
			}
		}
	}
GOTO_EndFunc:

	#endif

	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BYTE gObjShopBuyInventoryInsertItem(int aIndex, CItem item)
{
	#ifdef GS_99_60T

	int w, h, iwidth, iheight;
	BYTE blank = 0;

	item.GetSize(iwidth, iheight);

	for (h = 0; h < 8; h++)
	{
		for (w = 0; w < 8; w++)
		{
			if (*(BYTE*)(gObj[aIndex].pInventoryMap + h * 8 + w) == 255)
			{
				blank = g_GS.gObjOnlyInventoryRectCheck(aIndex, w, h, iwidth, iheight);

				if (blank == 254)
				{
					goto GOTO_EndFunc;
				}

				if (blank != 255)
				{
					gObj[aIndex].pInventory[blank] = item;

					if (item.m_serial == 0)
					{
						gObj[aIndex].pInventory[blank].m_Number = 0;
					}
					else
					{
						gObj[aIndex].pInventory[blank].m_Number = g_GS.gGetItemNumber();
						g_GS.gPlusItemNumber();
					}

					g_GS.gObjInventoryItemSet(aIndex, blank, gObj[aIndex].pInventory[blank].m_Type);
					return blank;
				}
			}
		}
	}
GOTO_EndFunc:

	#endif

	return -1;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------