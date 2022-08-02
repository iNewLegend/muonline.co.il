#include "stdafx.h"
#include "User.h"
#include "TSetup.h"
#include "ReadScript.h"
#include <iostream>
#include "EventItemManager.h"

CItemBag* g_RedDragonBag;

CItemBag::CItemBag()
{

}

CItemBag::~CItemBag()
{

}

void CItemBag::Init(char* name)
{
	this->m_bLoad = false;
	this->m_sEventName[0] = 0;
	this->m_iEventItemType = -1;
	this->m_iEventItemLevel = 0;
	this->m_iEventItemDropRate = 0;
	this->m_iItemDropRate = 0;
	this->m_iExItemDropRate = 0;
	this->m_iBagObjectCount = 0;

	this->LoadItem(name);
}

void CItemBag::LoadItem(char* script_file)
{
	int Token;

	this->m_bLoad = false;
	SMDFile = fopen(script_file, "r");

	if (SMDFile == NULL)
	{		
		g_Setup.MsgBox("Failed to load EventItemBag file %s", script_file);
		return;
	}

	int n = 0;

	while (true)
	{
		Token = GetToken();

		if (Token == 2)
		{
			break;
		}

		if (Token == 1)
		{
			int st = TokenNumber;

			if (st == 0)
			{
				while (true)
				{
					Token = GetToken();

					if (Token == 0)
					{
						if (strcmp("end", TokenString) == 0)
						{
							break;
						}
					}

					int map = TokenNumber;

					if (MAX_MAP_RANGE(map) == false)
					{
						g_Setup.MsgBox("ExEvent ItemBag LoadFail [%s]", script_file);
						return;
					}

					Token = GetToken();
					this->DropMapInfo[map].m_bIsDrop = TokenNumber;

					Token = GetToken();
					this->DropMapInfo[map].m_MinMonsterLevel = TokenNumber;

					Token = GetToken();
					this->DropMapInfo[map].m_MaxMonsterLevel = TokenNumber;
				}

			}
			else if (st == 1)
			{
				while (true)
				{
					Token = GetToken();

					if (Token == 0)
					{
						if (strcmp("end", TokenString) == 0)
						{
							break;
						}
					}

					strcpy(this->m_sEventName, TokenString);

					Token = GetToken();
					int type = TokenNumber;

					Token = GetToken();
					int index = TokenNumber;

					this->m_iEventItemType = ITEMGET(type, index);

					Token = GetToken();
					this->m_iEventItemLevel = TokenNumber;

					Token = GetToken();
					this->m_iEventItemDropRate = TokenNumber;

					Token = GetToken();
					this->m_iItemDropRate = TokenNumber;

					Token = GetToken();
					this->m_iExItemDropRate = TokenNumber;

					char szTemp[256];


				}
			}
			else if (st == 2)
			{
				while (true)
				{
					Token = GetToken();

					if (Token == 0)
					{
						if (strcmp("end", TokenString) == 0)
						{
							break;
						}
					}

					this->BagObject[n].m_type = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_index = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_minLevel = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_maxLevel = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_isskill = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_isluck = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_isoption = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_isexitem = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_isancitem = TokenNumber;

					n++;
					this->m_iBagObjectCount++;

					if (this->m_iBagObjectCount > 150 - 1)
					{
						break;
					}
				}
			}
		}
	}

	fclose(SMDFile);

	this->m_bLoad = true;
}


BYTE CItemBag::GetLevel(int n)
{
	if (n <0 || n > 150 - 1)
	{
		return 0;
	}

	if (this->BagObject[n].m_minLevel == this->BagObject[n].m_maxLevel)
	{
		return this->BagObject[n].m_minLevel;
	}

	int sub = (this->BagObject[n].m_maxLevel - this->BagObject[n].m_minLevel) + 1;
	int level = this->BagObject[n].m_minLevel + (rand() % sub);

	return level;
}

bool CItemBag::IsEnableEventItemDrop(int aIndex)
{
	OBJECTSTRUCT* gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	int iMapNumber = gObj->MapNumber;

	if (this->DropMapInfo[iMapNumber].m_bIsDrop == FALSE)
	{
		return false;
	}

	int iLevel = gObj->Level;

	if (iLevel < this->DropMapInfo[iMapNumber].m_MinMonsterLevel || iLevel > this->DropMapInfo[iMapNumber].m_MaxMonsterLevel)
	{
		return false;
	}

	return true;
}


bool CItemBag::DropEventItem(int aIndex)
{
	if (this->m_bLoad == false)
	{
		return false;
	}

	if (this->IsEnableEventItemDrop(aIndex) == false)
	{
		return false;
	}

	OBJECTSTRUCT* gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	if ((rand() % 1000) < this->m_iEventItemDropRate)
	{
		int ei;
		int eil;
		int x;
		int y;
		float dur = 0;
		dur = 255.0;

		x = gObj->X;
		y = gObj->Y;
		eil = this->m_iEventItemLevel;
		ei = this->m_iEventItemType;
#ifdef GS_99_60T
		int thdu = g_GS.gObjMonsterTopHitDamageUser((DWORD)gObj);

		g_GS.ItemSerialCreateSend(gObj->m_Index, gObj->MapNumber, x, y, ei, eil, dur, 0, 0, 0, thdu, 0, 0);
#endif
		return true;
	}

	return false;
}


BOOL CItemBag::DropItem(int aIndex)
{
	if (this->m_bLoad == FALSE)
		return false;

	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum;
	int ExOption = 0;

	OBJECTSTRUCT* gObj = (OBJECTSTRUCT*)(aIndex * OBJECT_SIZE + OBJECT_BASE);

	if (this->GetBagCount() > 0)
	{
		srand(time(0));
		DropItemNum = rand() % this->GetBagCount();

		dur = 0;
		x = gObj->X;
		y = gObj->Y;
		level = this->BagObject[DropItemNum].m_maxLevel;
		type = ITEMGET(this->BagObject[DropItemNum].m_type, this->BagObject[DropItemNum].m_index);

		if (type == -1)
			return false;

		if (this->BagObject[DropItemNum].m_isskill != 0)
			Option1 = 1;

		if (this->BagObject[DropItemNum].m_isluck != 0)
		{
			Option2 = 1;
		}

		if (this->BagObject[DropItemNum].m_isoption != 0)
		{
			Option3 = this->BagObject[DropItemNum].m_isoption;
		}

		if (this->BagObject[DropItemNum].m_isexitem)
		{
			ExOption = this->BagObject[DropItemNum].m_isexitem;

		}

		if (type == ITEMGET(12, 15) ||
			type == ITEMGET(14, 13) ||
			type == ITEMGET(14, 14))
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}

		g_GS.ItemSerialCreateSend(gObj->m_Index, gObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, gObj->m_Index, ExOption, 0);

		PMSG_SERVERCMD ServerCmd;

		PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
		ServerCmd.CmdType = 0;
		ServerCmd.X = gObj->X;
		ServerCmd.Y = gObj->Y;

		g_GS.MsgSendV2((DWORD)gObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
	}

	return true;
}


BYTE CItemBag::GetMinLevel(int n)
{
	if (n<0 || n > 150 - 1)
		return 0;

	return this->BagObject[n].m_minLevel;
}

BYTE CItemBag::GetMaxLevel(int n)
{
	if (n<0 || n > 150 - 1)
		return 0;

	return this->BagObject[n].m_maxLevel;
}


BOOL CItemBag::PickItem(CItem & objItem, int & nItemIndex)
{
	if (this->m_bLoad == FALSE)
		return false;

	int DropItemNum;

	if (this->GetBagCount() > 0)
	{
		DropItemNum = rand() % this->GetBagCount();
		nItemIndex = DropItemNum;
		objItem.m_Type = ITEMGET(this->BagObject[DropItemNum].m_type, this->BagObject[DropItemNum].m_index);
		objItem.m_Level = this->GetLevel(DropItemNum);

		if (objItem.m_Type == -1)
			return false;

		if (this->BagObject[DropItemNum].m_isskill != 0)
			objItem.m_Option1 = 1;

		if (this->BagObject[DropItemNum].m_isluck != 0)
			objItem.m_Option2 = 1;

		if (this->BagObject[DropItemNum].m_isoption != 0)
			objItem.m_Option3 = 1;

		if (this->BagObject[DropItemNum].m_isexitem != 0)
		{
			objItem.m_NewOption = 1;
			objItem.m_Option1 = 0;
			objItem.m_Option2 = 0;
		}

		if (objItem.m_Type == ITEMGET(12, 15) ||
			objItem.m_Type == ITEMGET(14, 13) ||
			objItem.m_Type == ITEMGET(14, 14))
		{
			objItem.m_Option1 = 0;
			objItem.m_Option2 = 0;
			objItem.m_Option3 = 0;
			objItem.m_Level = 0;
		}

		if (objItem.m_Type == ITEMGET(13, 0) ||
			objItem.m_Type == ITEMGET(13, 1) ||
			objItem.m_Type == ITEMGET(13, 2) ||
			objItem.m_Type == ITEMGET(13, 8) ||
			objItem.m_Type == ITEMGET(13, 9) ||
			objItem.m_Type == ITEMGET(13, 12) ||
			objItem.m_Type == ITEMGET(13, 13))
		{
			objItem.m_Level = 0;
		}

		objItem.m_Durability = 0;

		return true;
	}

	return false;
}

BYTE NewOptionRand(int level)
{
	BYTE NOption = 0;

	NOption = 1 << (rand() % 6);

	if ((NOption & 2) != 0)
	{
		if ((rand() % 2) != 0)
		{
			NOption = 1 << (rand() % 6);
		}
	}

	if ((rand() % 4) == 0)
	{
		NOption |= 1 << (rand() % 6);
	}

	return NOption;
}

void LoadItemBag()
{
	g_RedDragonBag = new CItemBag;
	if (g_RedDragonBag == NULL)
	{
		g_Setup.MsgBox("CItemBag %s", "Memory allocation error");
		return;
	}
	g_RedDragonBag->Init((char *)"..\\Data\\RedDragonBag.txt");
}

