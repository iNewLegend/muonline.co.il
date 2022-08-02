#pragma once
#include "stdafx.h"
typedef unsigned char       BYTE;
typedef char*       LPSTR;

class CEventBag
{
public:

	CEventBag()
	{
		this->m_type = 0;
		this->m_index = 0;
		this->m_minLevel = 0;
		this->m_maxLevel = 0;
		this->m_isskill = 0;
		this->m_isluck = 0;
		this->m_isoption = 0;
		this->m_isexitem = 0;
		this->m_isancitem = 0;
	}

	BYTE m_type;
	BYTE m_index;
	BYTE m_minLevel;
	BYTE m_maxLevel;
	BYTE m_isskill;
	BYTE m_isluck;
	BYTE m_isoption;
	BYTE m_isexitem;
	BYTE m_isancitem;
};

class CEventBagDropMapInfo
{
public:

	CEventBagDropMapInfo()
	{
		this->Init();
	};

	void Init()
	{
		this->m_bIsDrop = false;
		this->m_MinMonsterLevel = 0;
		this->m_MaxMonsterLevel = 0;
	};

	BYTE m_bIsDrop;
	BYTE m_MinMonsterLevel;
	BYTE m_MaxMonsterLevel;
};


class CItemBag
{
public:

	CItemBag();
	virtual ~CItemBag();

	void Init(LPSTR name);
	void LoadItem(LPSTR script_file);
	bool DropEventItem(int aIndex);
	int DropItem(int aIndex);
	BYTE GetMinLevel(int n);
	BYTE GetMaxLevel(int n);
	int PickItem(CItem& objItem, int& nItemIndex);

private:

	int GetBagCount(){ return this->m_iBagObjectCount; }
	bool IsEnableEventItemDrop(int aIndex);
	BYTE GetLevel(int n);

private:

	bool m_bLoad;
	char m_sEventName[255];
	int m_iEventItemType;
	int m_iEventItemLevel;
	int m_iEventItemDropRate;
	int m_iItemDropRate;
	int m_iExItemDropRate;
	int m_iBagObjectCount;
	CEventBagDropMapInfo DropMapInfo[50];
	CEventBag BagObject[150];
};


extern CItemBag* g_RedDragonBag;

BYTE NewOptionRand(int level);
void LoadItemBag();
