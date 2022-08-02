#include "stdafx.h"
#include "User.h"
#include "TMessages.h"
#include "TConfig.h"
#include "VIPSystem.h"
#include "DSXProtocol.h"

VIPSystem g_VIPSystem;

VIPSystem::VIPSystem()
{
}

VIPSystem::~VIPSystem()
{
}

void VIPSystem::Init()
{
#ifdef GS_99_60T
	// Load fuking configs
	g_VIPSystem.IsVIPSystemOn = g_Config.IsVIPSystemOn;
	g_VIPSystem.bGSVIPCode = g_Config.VipServerLevel;
	// VIP Bronze
	g_VIPSystem.bPostCommand		= g_Config.bPostCommand;
	g_VIPSystem.bOffTradeCommand	= g_Config.bOffTradeCommand;
	g_VIPSystem.bVIPSing			= g_Config.bVIPSing;
	g_VIPSystem.bVIPDays			= g_Config.bVIPDays;
	g_VIPSystem.bVIPPrice			= g_Config.bVIPPrice;
	// VIP Silver
	g_VIPSystem.sPostCommand		= g_Config.sPostCommand;
	g_VIPSystem.sOffTradeCommand	= g_Config.sOffTradeCommand;
	g_VIPSystem.sVIPSing			= g_Config.sVIPSing;
	g_VIPSystem.sVIPDays			= g_Config.sVIPDays;
	g_VIPSystem.sVIPPrice			= g_Config.sVIPPrice;
	// VIP Gold
	g_VIPSystem.gPostCommand		= g_Config.gPostCommand;
	g_VIPSystem.gOffTradeCommand	= g_Config.gOffTradeCommand;
	g_VIPSystem.gVIPSing			= g_Config.gVIPSing;
	g_VIPSystem.gVIPDays			= g_Config.gVIPDays;
	g_VIPSystem.gVIPPrice			= g_Config.gVIPPrice;
	// Platinum VIP
	g_VIPSystem.pPostCommand		= g_Config.pPostCommand;
	g_VIPSystem.pOffTradeCommand	= g_Config.pOffTradeCommand;
	g_VIPSystem.pVIPSing			= g_Config.pVIPSing;
	g_VIPSystem.pVIPDays			= g_Config.pVIPDays;
	g_VIPSystem.pVIPPrice			= g_Config.pVIPPrice;
#endif
}
// -------
// RequestCode - [0:PostCommand][1:OffTradeCommand][2:VIPSing]
// -------
bool VIPSystem::RequestVIPBonus(int aIndex, int RequestCode)
{
	_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];

	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	if (g_VIPSystem.IsVIPSystemOn == true)
	{
		if (RequestCode == 0)
		{
			switch (nObject->VipLevel)
			{
			case 1:
				return g_VIPSystem.bPostCommand;
			case 2:
				return g_VIPSystem.sPostCommand;
			case 3:
				return g_VIPSystem.gPostCommand;
			case 4:
				return g_VIPSystem.pPostCommand;
			default:
				return false;
			}
		}
		else if (RequestCode == 1)
		{
			switch (nObject->VipLevel)
			{
			case 1:
				return g_VIPSystem.bOffTradeCommand;
			case 2:
				return g_VIPSystem.sOffTradeCommand;
			case 3:
				return g_VIPSystem.gOffTradeCommand;
			case 4:
				return g_VIPSystem.pOffTradeCommand;
			default:
				return false;
			}
		}
		else if (RequestCode == 2)
		{
			switch (nObject->VipLevel)
			{
			case 1:
				return g_VIPSystem.bVIPSing;
			case 2:
				return g_VIPSystem.sVIPSing;
			case 3:
				return g_VIPSystem.gVIPSing;
			case 4:
				return g_VIPSystem.pVIPSing;
			default:
				return false;
			}
		}
		else
		{
			g_Msg.Msg(aIndex, "@[VIP] אין לך רמת ויאיפי כדי לבצע את הפעולה");
			return false;
		}
	}

	return false;
}

LPCSTR VIPSystem::RequestVipLevelName(int VipLevel, int Lang)
{
	// Lang 1 = HEB
	// Lang 2 = ENG

	if (Lang == 1)
	{
		switch (VipLevel)
		{
		case 1:
			return "ברונז";
		case 2:
			return "סילבר";
		case 3:
			return "גולד";
		case 4:
			return "פלטינום";
		default:
			return "אין";
		}
	}
	else
	{
		switch (VipLevel)
		{
		case 1:
			return "Bronze";
		case 2:
			return "Silver";
		case 3:
			return "Gold";
		case 4:
			return "Platinum";
		default:
			return "None";
		}
	}
}

void VIPSystem::VIPBuyRequest(int aIndex, int VipLevel)
{
	//OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	switch (VipLevel)
	{
	case 1:
		GDSendBuyVipMsg(gObj[aIndex].AccountID, gObj[aIndex].Name, VipLevel, g_VIPSystem.bVIPDays, g_VIPSystem.bVIPPrice);
		g_Msg.Msg(aIndex, "@[VIP] ביצעת פקודה לקניית ויאיפי מסוג %s למשך %d ימים", RequestVipLevelName(VipLevel, 1), g_VIPSystem.bVIPDays);
		break;
	case 2:
		GDSendBuyVipMsg(gObj[aIndex].AccountID, gObj[aIndex].Name, VipLevel, g_VIPSystem.sVIPDays, g_VIPSystem.sVIPPrice);
		g_Msg.Msg(aIndex, "@[VIP] ביצעת פקודה לקניית ויאיפי מסוג %s למשך %d ימים", RequestVipLevelName(VipLevel, 1), g_VIPSystem.sVIPDays);
		break;
	case 3:
		GDSendBuyVipMsg(gObj[aIndex].AccountID, gObj[aIndex].Name, VipLevel, g_VIPSystem.gVIPDays, g_VIPSystem.gVIPPrice);
		g_Msg.Msg(aIndex, "@[VIP] ביצעת פקודה לקניית ויאיפי מסוג %s למשך %d ימים", RequestVipLevelName(VipLevel, 1), g_VIPSystem.gVIPDays);
		break;
	case 4:
		GDSendBuyVipMsg(gObj[aIndex].AccountID, gObj[aIndex].Name, VipLevel, g_VIPSystem.pVIPDays, g_VIPSystem.pVIPPrice);
		g_Msg.Msg(aIndex, "@[VIP] ביצעת פקודה לקניית ויאיפי מסוג %s למשך %d ימים", RequestVipLevelName(VipLevel, 1), g_VIPSystem.pVIPDays);
		break;
	default:
		break;
	}
}