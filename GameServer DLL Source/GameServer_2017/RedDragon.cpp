#include "stdafx.h"
#include "RedDragon.h"
#include "User.h"
#include "TMessages.h"
#include "TConfig.h"
#include "EventItemManager.h"
CRedDragon g_RedDragon;

CRedDragon::CRedDragon()
{
}


CRedDragon::~CRedDragon()
{
}

void CRedDragon::Init()
{
	// Load shit from config
	g_RedDragon.iRedDragonAttackRate = g_Config.iRedDragonAttackRate;
	g_RedDragon.iRedDragonMinDmg = g_Config.iRedDragonMinDmg;
	g_RedDragon.iRedDragonMaxDmg = g_Config.iRedDragonMaxDmg;
	g_RedDragon.iRedDragonHP = g_Config.iRedDragonHP;
	g_RedDragon.iRedDragonPrizeCredits = g_Config.iRedDragonPrizeCredits;
	g_RedDragon.iRedDragonAttackSpeed = g_Config.iRedDragonAttackSpeed;
	g_RedDragon.iRedDragonAttackRange = g_Config.iRedDragonAttackRange;
	g_RedDragon.iRedDragonDefense = g_Config.iRedDragonDefense;
	g_RedDragon.iRedDragonLevel = g_Config.iRedDragonLevel;
	g_RedDragon.bIsActive = false;
}

void CRedDragon::CreateRedDragon(int Type, int aIndex, int Code)
{
	OBJECTSTRUCT * lpObj = &gObj[aIndex];

	if (Code == 2)
	{
		g_Msg.Msg(aIndex, "[RedDragon] You already used your daily qouta");
		return;
	}

	g_RedDragon.SpwanRedDragon(aIndex, lpObj->MapNumber, lpObj->X, lpObj->Y);
}

void CRedDragon::SpwanRedDragon(int summoner, int map, int x, int y)
{
	g_RedDragon.redDragonMutex.lock();
	if (g_RedDragon.bIsActive == true)
	{
		g_Msg.PM(summoner, "זימון הדרקון האדום נכשל - הוא כבר קיים");
		g_RedDragon.redDragonMutex.unlock();
		return;
	}
	g_RedDragon.bIsActive = true;
	g_RedDragon.redDragonMutex.unlock();
	g_Msg.NoticeAll("הדרקון האדום יופיע בעוד 10 שניות");
	g_RedDragon.map = map;
	g_RedDragon.x = x;
	g_RedDragon.y = y;
	g_RedDragon.summoner = summoner;
	_beginthread(CRedDragon::SpwanLogic,0,NULL);
	g_Msg.PM(summoner, "%d,[%d,%d] הדרקון האדום זומן רנדומלית למיקום:", map, x, y);
}

void CRedDragon::SpwanLogic(void * lpParam)
{
	int map = g_RedDragon.map;
	int x = g_RedDragon.x;
	int y = g_RedDragon.y;
	int summoner = g_RedDragon.summoner;

	Sleep(10000);
	short mobId = g_GS.gObjAddMonster(map);

	OBJECTSTRUCT *gMob = (OBJECTSTRUCT*)OBJECT_POINTER(mobId);

	if (mobId == 0)
	{
		g_Msg.PM(summoner, "זימון הדרקון האדום נכשל");
	}

	gMob->MapNumber = map;
	gMob->X = x;
	gMob->Y = y;


	if (g_GS.gObjSetMonster(mobId, g_RedDragon.iMobId) == false)
	{
		g_Msg.PM(summoner, "זימון הדרקון האדום נכשל");
		g_GS.gObjDel(mobId);
	}

	gMob->m_AttackDamageMax = g_RedDragon.iRedDragonMaxDmg;
	gMob->m_AttackDamageMin = g_RedDragon.iRedDragonMinDmg;
	gMob->m_AttackRating = g_RedDragon.iRedDragonAttackRate;
	gMob->m_AttackRange = g_RedDragon.iRedDragonAttackRange;
	gMob->Life = g_RedDragon.iRedDragonHP;
	gMob->MaxLife = g_RedDragon.iRedDragonHP;
	gMob->m_Defense = g_RedDragon.iRedDragonDefense;
	gObj->Level = g_RedDragon.iRedDragonLevel;
	gObj->m_AttackSpeed = g_RedDragon.iRedDragonAttackSpeed;
#ifdef GS_99_60T
	g_GS.gObjSetPosition(mobId, x, y);
#endif
	g_Msg.NoticeAll("חסלו את הדרקון האדום במפה %s", GetMapNameHeByID(map));
	g_Msg.NoticeAll("במיקום: %d, %d", y, x);

}

void CRedDragon::GiveRedDragonPrize(OBJECTSTRUCT * winnerIndex)
{	
	
	// Give Credits
	char Query[MAX_TEXT_LEN] = { 0 };
	sprintf(Query, "UPDATE MEMB_INFO SET Credits = Credits + 20 WHERE memb___id = '%s'", winnerIndex->AccountID);
	GDSendQuery(Query);
	
	// Drop Item
	g_RedDragonBag->DropItem(winnerIndex->m_Index);

	// Send Message to all
	g_Msg.NoticeAll("%s הרג את הדרקון האדום!", winnerIndex->Name);
	g_Msg.PM(winnerIndex->m_Index, "~[Red Dragon] You win %d Credit(s)", g_RedDragon.iRedDragonPrizeCredits);
	g_Msg.PM(winnerIndex->m_Index, "~[Red Dragon] זכית ב %d קרדיטים", g_RedDragon.iRedDragonPrizeCredits);

	g_RedDragon.bIsActive = false;
}
