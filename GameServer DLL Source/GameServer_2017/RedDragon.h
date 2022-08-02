#pragma once
class CRedDragon
{
private:
	int iMobId = 42;
	int	iRedDragonAttackRate;
	int	iRedDragonMinDmg;
	int	iRedDragonMaxDmg;
	int	iRedDragonHP;
	int	iRedDragonPrizeCredits;
	int	iRedDragonAttackSpeed;
	int	iRedDragonAttackRange;
	int	iRedDragonDefense;
	int	iRedDragonLevel;
	int summoner;
	int map;
	int x;
	int y;
	static void SpwanLogic(void * lpParam);
public:
	CRedDragon();
	~CRedDragon();
	
	bool bIsActive;
	void Init();
	void SpwanRedDragon(int summoner, int map, int x, int y);	
	void GiveRedDragonPrize(OBJECTSTRUCT * winnerIndex);
	static void CreateRedDragon(int Type, int aIndex, int Code);
	boost::mutex redDragonMutex;
};

extern CRedDragon g_RedDragon;

