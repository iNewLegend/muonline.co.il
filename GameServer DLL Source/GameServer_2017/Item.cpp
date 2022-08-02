#include "stdafx.h"
#include "Item.h"
#include "TSetup.h"

#ifdef GS_99_60T
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ITEM_ATTRIBUTE * ItemAttribute = (ITEM_ATTRIBUTE *)ITEM_ATTRIBUTE_BASE;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ItemGetSize(int index, int & width, int & height)
{
	width = ItemAttribute[index].Width;
	height = ItemAttribute[index].Height;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ItemByteConvert(unsigned char* buf, CItem item)
{
	// leo: i dont know why but when i use this function it works (gs one make problems)

	int n = 0;

	memset(buf, 0, 7);
	buf[n] = item.m_Type & 0xFF;
	n++;
	buf[n] = 0;
	buf[n] |= item.m_Level * 8;
	buf[n] |= item.m_Option1 * 128;
	buf[n] |= item.m_Option2 * 4;
	buf[n] |= item.m_Option3 & 3;
	n++;
	buf[n] = item.m_Durability;
	n++;
	buf[n] = 0;
	buf[n] |= ((item.m_Type & 0x100) >> 1);

	if (item.m_Option3 > 3)
	{
		buf[n] |= 0x40; // item +16 option
	}

	buf[n] |= item.m_NewOption;
	n++;
	buf[n] = item.m_SetOption;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CItem::CItem()
{
	this->Clear();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CItem::Clear()	// Fine
{
	this->m_Type = -1;
	this->m_Level = 0;
	this->m_Part = 0;
	this->m_Class = 0;
	this->m_TwoHand = 0;
	this->m_AttackSpeed = 0;
	this->m_DamageMin = 0;
	this->m_DamageMax = 0;
	this->m_SuccessfulBlocking = 0;
	this->m_Defense = 0;
	this->m_MagicDefense = 0;
	this->m_Durability = 0;
	this->m_SpecialNum = 0;
	this->m_Value = 0;
	this->m_Option1 = 0;
	this->m_Option2 = 0;
	this->m_Option3 = 0;
	this->m_NewOption = 0;
	this->m_Number = 0;
	this->m_DurabilitySmall = 0;
	this->m_iPShopValue = -1;
	this->m_bItemExist = true;
	this->m_CurrentDurabilityState = -1;
	this->m_SetOption = 0;
	this->m_QuestItem = false;

	memset(this->m_Special, 0, sizeof(this->m_Special));
	memset(this->m_SpecialValue, 0, sizeof(this->m_SpecialValue));
	memset(this->m_Resistance, 0, sizeof(this->m_Resistance));

	this->m_IsLoadPetItemInfo = 0;
	this->m_PetItem_Level = 1;
	this->m_PetItem_Exp = 0;
	this->m_Leadership = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool CItem::IsItem() // Good
{
	if (this->m_Type < 0) {
		return false;
	}

	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CItem::Convert(int type, char Option1, char Option2, char Option3, char Attribute2, char SetOption, char DbVersion)
{
	 // decompile from gs seems working

	__int64 v8; // rax@98
	__int64 v9; // rax@109
	__int64 v10; // rax@120
	__int64 v11; // rax@129
	__int64 v12; // rax@150
	__int64 v13; // rax@153
	__int64 v14; // rax@156
	int i; // [sp+60h] [bp-20h]@48
	int iChaosItem; // [sp+64h] [bp-1Ch]@30
	int SOptionStatValue; // [sp+68h] [bp-18h]@13
	int SOption; // [sp+6Ch] [bp-14h]@13
	ITEM_ATTRIBUTE *p; // [sp+70h] [bp-10h]@5
	int ItemLevel; // [sp+74h] [bp-Ch]@51
	int _type; // [sp+78h] [bp-8h]@1
	CItem *thisa; // [sp+7Ch] [bp-4h]@1
	char SetOptiona; // [sp+9Ch] [bp+1Ch]@13

	thisa = this;
	_type = type;
	if (!DbVersion)
		_type = type % 16 + 32 * (type / 16);
	if (_type > 511)
		g_Setup.MsgBox("error-L1 : ItemIndex error %d", _type);
	p = &ItemAttribute[_type];
	thisa->m_serial = p->Serial;
	thisa->m_Type = type;
	if (!DbVersion)
		thisa->m_Type = _type;
	thisa->m_NewOption = Attribute2;
	if (!p->OptionFlag)
		thisa->m_NewOption = 0;
	if (_type >= 387 && _type <= 390 || _type == 446)
		Attribute2 = 0;

	SetOptiona = SetOption & 0xF;
	SOption = SetOptiona & 3;
	SOptionStatValue = 0;
	if (SOption != 1 && SOption != 2)
		SOption = 0;
	if ((((signed int)(unsigned __int8)SetOptiona >> 2) & 3) != 1
		&& (((signed int)(unsigned __int8)SetOptiona >> 2) & 3) != 2)
		SOption = 0;
	
	if (/*CSetItemOption::IsSetItem(&gSetItemOption, _type) && */ SetOption && (unsigned __int8)SetOptiona != 255 && SOption)
	{
		thisa->m_SetOption = SetOptiona;
		if (thisa->m_SetOption)
		{
			thisa->m_NewOption = 0;
			Attribute2 = 0;
			SOptionStatValue = ((signed int)(unsigned __int8)SetOptiona >> 2) & 3;
		}
	}
	else
	{
		//thisa->m_SetOption = 0;
	}


	memset(thisa->m_SkillResistance, 0, 7u);
	if (_type == 19 || _type == 146 || _type == 170)
		Attribute2 = 0;
	iChaosItem = 0;
	switch (thisa->m_Type)
	{
	case 0x46:
		iChaosItem = 15;
		break;
	case 0xA7:
		iChaosItem = 25;
		break;
	case 0x86:
		iChaosItem = 30;
		break;
	}
	if (g_GS.ItemGetDurability(thisa->m_Type, 0, 0, 0))
		thisa->m_BaseDurability = (float)g_GS.ItemGetDurability(
			thisa->m_Type,
			thisa->m_Level,
			Attribute2 & 0x7F,
			thisa->m_SetOption);
	else
		thisa->m_BaseDurability = 0;

	thisa->m_DurabilityState[0] = thisa->m_BaseDurability * 0.5;
	thisa->m_DurabilityState[1] = thisa->m_BaseDurability * 0.30000001;
	thisa->m_DurabilityState[2] = thisa->m_BaseDurability * 0.2;
	thisa->m_Value = p->Value;
	thisa->m_AttackSpeed = p->AttackSpeed;
	thisa->m_TwoHand = p->TwoHand;
	thisa->m_DamageMin = p->DamageMin;
	thisa->m_DamageMax = p->DamageMax;
	thisa->m_SuccessfulBlocking = p->SuccessfulBlocking;
	thisa->m_Defense = p->Defense;
	thisa->m_MagicDefense = p->MagicDefense;
	thisa->m_WalkSpeed = p->WalkSpeed;
	thisa->m_Magic = LOWORD(p->MagicPW);
	thisa->m_serial = p->Serial;
	thisa->m_QuestItem = p->QuestItem;
	if (thisa->m_Durability == 0.0)
	{
		thisa->m_CurrentDurabilityState = 1;
	}
	else if (thisa->m_Durability >= (double)thisa->m_DurabilityState[2])
	{
		if (thisa->m_Durability >= (double)thisa->m_DurabilityState[1])
		{
			if (thisa->m_Durability >= (double)thisa->m_DurabilityState[0])
				thisa->m_CurrentDurabilityState = 0.5;
			else
				thisa->m_CurrentDurabilityState = 0.3;
		}
		else
		{
			thisa->m_CurrentDurabilityState = 0.2;
		}
	}
	else
	{
		thisa->m_CurrentDurabilityState = 0.0;
	}
	memcpy(thisa->m_RequireClass, p->RequireClass, 5u);
	for (i = 0; i < 7; ++i)
		thisa->m_Resistance[i] = thisa->m_Level * p->Resistance[i];
	ItemLevel = p->Level;
	if ((Attribute2 & 0x3F) <= 0)
	{
		if (thisa->m_SetOption)
			ItemLevel = p->Level + 25;
	}
	else
	{
		ItemLevel = p->Level + 25;
	}
	if (p->RequireStrength)
		thisa->m_RequireStrength = 3 * (3 * thisa->m_Level + ItemLevel) * p->RequireStrength / 100 + 20;
	else
		thisa->m_RequireStrength = 0;
	if (p->RequireDexterity)
		thisa->m_RequireDexterity = 3 * (3 * thisa->m_Level + ItemLevel) * p->RequireDexterity / 100 + 20;
	else
		thisa->m_RequireDexterity = 0;
	if (p->RequireEnergy)
		thisa->m_RequireEnergy = 3 * (ItemLevel + 4 * thisa->m_Level) * p->RequireEnergy / 100 + 20;
	else
		thisa->m_RequireEnergy = 0;
	if (thisa->m_SetOption)
		ItemLevel = p->Level + 30;
	if (p->RequireLevel)
	{
		if (_type == 420)
		{
			thisa->m_RequireLevel = 2 * LOWORD(thisa->m_PetItem_Level) + 218;
		}
		else if (_type < 387 || _type > 390)
		{
			if (_type < 391 || _type > 408)
				thisa->m_RequireLevel = p->RequireLevel + 4 * thisa->m_Level;
			else
				thisa->m_RequireLevel = p->RequireLevel;
		}
		else
		{
			thisa->m_RequireLevel = 5 * thisa->m_Level + p->RequireLevel;
		}
	}
	else
	{
		thisa->m_RequireLevel = 0;
	}
	if (_type == 421)
		thisa->m_RequireLeaderShip = 15 * LOWORD(thisa->m_PetItem_Level) + 185;
	else
		thisa->m_RequireLeaderShip = 0;
	if (thisa->m_Type == 426)
	{
		if (ItemLevel > 2)
			thisa->m_RequireLevel = 50;
		else
			thisa->m_RequireLevel = 20;
	}
	if ((Attribute2 & 0x3F) > 0 && (signed int)thisa->m_RequireLevel > 0)
		thisa->m_RequireLevel += 20;
	thisa->m_Leadership = 0;
	if ((signed int)thisa->m_DamageMax > 0)
	{
		if (thisa->m_SetOption && ItemLevel)
		{
			thisa->m_DamageMax += (unsigned int)(25 * thisa->m_DamageMin / p->Level) + 5;
			thisa->m_DamageMax += ItemLevel / 40 + 5;
		}
		else if ((Attribute2 & 0x3F) > 0)
		{
			if (iChaosItem)
			{
				thisa->m_DamageMax += iChaosItem;
			}
			else if (p->Level)
			{
				thisa->m_DamageMax += (unsigned int)(25 * thisa->m_DamageMin / p->Level) + 5;
			}
		}
		thisa->m_DamageMax += 3 * thisa->m_Level;
		if (thisa->m_Level >= 10)
		{
			v8 = (thisa->m_Level - 8) * (thisa->m_Level - 9);
			thisa->m_DamageMax += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}
	if ((signed int)thisa->m_DamageMin > 0)
	{
		if (thisa->m_SetOption && ItemLevel)
		{
			thisa->m_DamageMin += (unsigned int)(25 * thisa->m_DamageMin / p->Level) + 5;
			thisa->m_DamageMin += ItemLevel / 40 + 5;
		}
		else if ((Attribute2 & 0x3F) > 0)
		{
			if (iChaosItem)
			{
				thisa->m_DamageMin += iChaosItem;
			}
			else if (p->Level)
			{
				thisa->m_DamageMin += (unsigned int)(25 * thisa->m_DamageMin / p->Level) + 5;
			}
		}
		thisa->m_DamageMin += 3 * thisa->m_Level;
		if (thisa->m_Level >= 10)
		{
			v9 = (thisa->m_Level - 8) * (thisa->m_Level - 9);
			this->m_DamageMin += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}
	if ((signed int)thisa->m_Magic > 0)
	{
		if (thisa->m_SetOption && ItemLevel)
		{
			thisa->m_Magic += (unsigned int)(25 * thisa->m_Magic / p->Level) + 5;
			thisa->m_Magic += ItemLevel / 60 + 2;
		}
		else if ((Attribute2 & 0x3F) > 0)
		{
			if (iChaosItem)
			{
				thisa->m_Magic += iChaosItem;
			}
			else if (p->Level)
			{
				thisa->m_Magic += (unsigned int)(25 * thisa->m_Magic / p->Level) + 5;
			}
		}
		thisa->m_Magic += 3 * thisa->m_Level;
		if (thisa->m_Level >= 10)
		{
			this->m_Magic += (this->m_Magic * 25) / p->Level + 5;
			this->m_Magic += ItemLevel / 60 + 2;
		}
	}
	if (p->SuccessfulBlocking > 0)
	{
		if (thisa->m_SetOption && ItemLevel)
		{
			thisa->m_SuccessfulBlocking += (unsigned int)(25 * thisa->m_SuccessfulBlocking / p->Level) + 5;
			thisa->m_SuccessfulBlocking += ItemLevel / 40 + 5;
		}
		else if ((Attribute2 & 0x3F) > 0 && p->Level)
		{
			thisa->m_SuccessfulBlocking += (unsigned int)(25 * thisa->m_SuccessfulBlocking / p->Level) + 5;
		}
		thisa->m_SuccessfulBlocking += 3 * thisa->m_Level;
		if (thisa->m_Level >= 10)
		{
			v11 = (thisa->m_Level - 8) * (thisa->m_Level - 9);
			thisa->m_SuccessfulBlocking += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}
	if (p->Defense > 0)
	{
		if (thisa->m_Type < 192 || thisa->m_Type >= 224)
		{
			if (thisa->m_SetOption && ItemLevel)
			{
				thisa->m_Defense += 12 * thisa->m_Defense / p->Level + p->Level / 5 + 4;
				thisa->m_Defense += 3 * thisa->m_Defense / ItemLevel + ItemLevel / 30 + 2;
			}
			else if ((Attribute2 & 0x3F) > 0 && p->Level)
			{
				thisa->m_Defense += 12 * thisa->m_Defense / p->Level + p->Level / 5 + 4;
			}
			if ((_type < 387 || _type > 390) && _type != 446 && _type != 420)
				thisa->m_Defense += 3 * thisa->m_Level;
			else
				thisa->m_Defense += 2 * thisa->m_Level;
			if (thisa->m_Level >= 10)
			{
				v12 = (thisa->m_Level - 8) * (thisa->m_Level - 9);
				this->m_Defense += (this->m_Level - 9) * (this->m_Level - 8) / 2;
			}
		}
		else
		{
			thisa->m_Defense += thisa->m_Level;
			if (thisa->m_SetOption && ItemLevel)
				thisa->m_Defense += (unsigned int)(20 * thisa->m_Defense / ItemLevel) + 2;
		}
	}
	if (_type == 446)
	{
		thisa->m_Defense = 2 * thisa->m_Level + 15;
		if (thisa->m_Level >= 10)
		{
			v13 = (thisa->m_Level - 8) * (thisa->m_Level - 9);
			thisa->m_Defense += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}
	if (p->MagicDefense > 0)
	{
		thisa->m_MagicDefense += 3 * thisa->m_Level;
		if (thisa->m_Level >= 10)
		{
			v14 = (thisa->m_Level - 8) * (thisa->m_Level - 9);
			thisa->m_MagicDefense += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}
	thisa->m_Level &= 0xFu;
	memset(thisa->m_Special, 0, 8u);
	memset(thisa->m_SpecialValue, 0, 8u);
	thisa->m_SpecialNum = 0;
	thisa->m_Option1 = 0;
	thisa->m_Option2 = 0;
	thisa->m_Option3 = 0;
	thisa->m_SkillChange = 0;
	if (Option1 && p->SkillType)
	{
		if (p->SkillType == 66)
		{
			thisa->m_SkillChange = 1;
			thisa->m_Special[thisa->m_SpecialNum] = 0;
			thisa->m_Option1 = 1;
		}
		else
		{
			thisa->m_Special[thisa->m_SpecialNum] = LOBYTE(p->SkillType);
			thisa->m_Option1 = 1;
		}
	}
	if (thisa->m_Type == 419)
	{
		thisa->m_Option1 = 1;
		thisa->m_Special[thisa->m_SpecialNum] = 49;
	}
	if (thisa->m_Type == 420)
	{
		thisa->m_Option1 = 1;
		thisa->m_Special[thisa->m_SpecialNum] = 62;
	}
	++thisa->m_SpecialNum;
	if (Option2)
	{
		if (_type >= 0 && _type < 384)
		{
			thisa->m_Special[thisa->m_SpecialNum] = 84;
			thisa->m_Option2 = 1;
		}
		if (_type >= 384 && _type <= 390)
		{
			thisa->m_Special[thisa->m_SpecialNum] = 84;
			thisa->m_Option2 = 1;
		}
		if (_type == 446)
		{
			thisa->m_Special[thisa->m_SpecialNum] = 84;
			thisa->m_Option2 = 1;
		}
	}
	++thisa->m_SpecialNum;
	if (Option3)
	{
		if (_type >= 0 && _type < 160)
		{
			thisa->m_Special[thisa->m_SpecialNum] = 80;
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		if (_type >= 160 && _type < 192)
		{
			thisa->m_Special[thisa->m_SpecialNum] = 81;
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		if (_type >= 192 && _type < 224)
		{
			thisa->m_Special[thisa->m_SpecialNum] = 82;
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		if (_type >= 224 && _type < 384)
		{
			thisa->m_Special[thisa->m_SpecialNum] = 83;
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		if (_type >= 424 && _type < 430 || _type >= 436 && _type <= 444)
		{
			if (_type == 440)
			{
				thisa->m_Special[thisa->m_SpecialNum] = -84;
				thisa->m_Option3 = Option3;
			}
			else if (_type == 444)
			{
				thisa->m_Special[thisa->m_SpecialNum] = -83;
				thisa->m_Option3 = Option3;
			}
			else
			{
				thisa->m_Special[thisa->m_SpecialNum] = 85;
				thisa->m_Option3 = Option3;
			}
		}
		if (_type == 446)
		{
			thisa->m_Special[thisa->m_SpecialNum] = 80;
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		switch (_type)
		{
		case 384:
			thisa->m_Special[thisa->m_SpecialNum] = 85;
			thisa->m_Option3 = Option3;
			break;
		case 385:
			thisa->m_Special[thisa->m_SpecialNum] = 81;
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
			break;
		case 386:
			thisa->m_Special[thisa->m_SpecialNum] = 80;
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
			break;
		case 387:
			thisa->m_Special[thisa->m_SpecialNum] = 80;
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
			if (thisa->m_NewOption & 0x20)
				thisa->m_Special[thisa->m_SpecialNum] = 85;
			else
				thisa->m_Special[thisa->m_SpecialNum] = 80;
			break;
		case 388:
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
			if (thisa->m_NewOption & 0x20)
				thisa->m_Special[thisa->m_SpecialNum] = 81;
			else
				thisa->m_Special[thisa->m_SpecialNum] = 85;
			break;
		case 389:
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
			if (thisa->m_NewOption & 0x20)
				thisa->m_Special[thisa->m_SpecialNum] = 80;
			else
				thisa->m_Special[thisa->m_SpecialNum] = 85;
			break;
		case 390:
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
			if (thisa->m_NewOption & 0x20)
				thisa->m_Special[thisa->m_SpecialNum] = 80;
			else
				thisa->m_Special[thisa->m_SpecialNum] = 81;
			break;
		case 419:
			thisa->m_Option3 = Option3;
			if (thisa->m_Option3 & 2)
				thisa->m_Special[thisa->m_SpecialNum++] = 103;
			if (thisa->m_Option3 & 4)
			{
				thisa->m_Special[thisa->m_SpecialNum++] = 97;
				thisa->m_AttackSpeed += 5;
			}
			if (thisa->m_Option3 & 1)
				thisa->m_Special[thisa->m_SpecialNum] = 104;
			break;
		}
		if (_type == 446)
		{
			thisa->m_Option3 = Option3;
			thisa->m_RequireStrength += 4 * (unsigned __int8)Option3;
			thisa->m_Special[thisa->m_SpecialNum] = 80;
		}
	}
	++thisa->m_SpecialNum;
	if (_type >= 192 && _type < 384 || _type >= 424 && _type <= 425 || _type >= 437 && _type <= 440)
	{
		if ((thisa->m_NewOption >> 5) & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 86;
		if ((thisa->m_NewOption >> 4) & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 87;
		if ((thisa->m_NewOption >> 3) & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 88;
		if ((thisa->m_NewOption >> 2) & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 89;
		if ((thisa->m_NewOption >> 1) & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 90;
		if (thisa->m_NewOption & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 91;
	}
	if (_type >= 0 && _type < 192 || _type >= 428 && _type <= 429 || _type >= 441 && _type <= 444)
	{
		if ((thisa->m_NewOption >> 5) & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 92;
		if ((_type < 160 || _type >= 192) && _type != 428 && _type != 441 && _type != 443)
		{
			if ((thisa->m_NewOption >> 4) & 1)
				thisa->m_Special[thisa->m_SpecialNum++] = 93;
			if ((thisa->m_NewOption >> 3) & 1)
				thisa->m_Special[thisa->m_SpecialNum++] = 94;
		}
		else
		{
			if ((thisa->m_NewOption >> 4) & 1)
				thisa->m_Special[thisa->m_SpecialNum++] = 95;
			if ((thisa->m_NewOption >> 3) & 1)
				thisa->m_Special[thisa->m_SpecialNum++] = 96;
		}
		if ((thisa->m_NewOption >> 2) & 1)
		{
			thisa->m_Special[thisa->m_SpecialNum++] = 97;
			thisa->m_AttackSpeed += 7;
		}
		if ((thisa->m_NewOption >> 1) & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 98;
		if (thisa->m_NewOption & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 99;
	}
	if (_type >= 387 && _type <= 390 || _type == 446)
	{
		if (thisa->m_NewOption & 1)
			thisa->m_Special[thisa->m_SpecialNum++] = 100;
		if (thisa->m_NewOption & 2)
			thisa->m_Special[thisa->m_SpecialNum++] = 101;
		if (thisa->m_NewOption & 4)
			thisa->m_Special[thisa->m_SpecialNum++] = 102;
		if (thisa->m_NewOption & 8)
			thisa->m_Special[thisa->m_SpecialNum++] = 105;
	}
	if (SOptionStatValue && p->SetAttr)
	{
		thisa->m_Special[thisa->m_SpecialNum] = p->SetAttr - 61;
		thisa->m_SetAddStat = 5 * SOptionStatValue;
		++thisa->m_SpecialNum;
	}
	thisa->m_Part = LOBYTE(p->ItemSlot);
	thisa->Value();
	if (thisa->m_Type != 135 && thisa->m_Type != 143)
	{
		thisa->m_DamageMinOrigin = thisa->m_DamageMin;
		thisa->m_DefenseOrigin = thisa->m_Defense;
		thisa->m_DamageMin -= (signed __int64)((double)thisa->m_DamageMin * thisa->m_CurrentDurabilityState);
		thisa->m_DamageMax -= (signed __int64)((double)thisa->m_DamageMax * thisa->m_CurrentDurabilityState);
		thisa->m_Defense -= (signed __int64)((double)thisa->m_Defense * thisa->m_CurrentDurabilityState);
		thisa->m_SuccessfulBlocking -= (signed __int64)((double)thisa->m_SuccessfulBlocking * thisa->m_CurrentDurabilityState);
		if (thisa->m_Durability < 1.0)
			thisa->m_AttackSpeed = 0;
	}
	if (thisa->m_Durability == 0.0)
		memset(thisa->m_Resistance, 0, 7u);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CItem::Value()
{
	// from gs 1.00.18 seems working

	if (this->m_Type == -1)
	{
		return;
	}

	ITEM_ATTRIBUTE * p = &ItemAttribute[this->m_Type];

	if (p->BuyMoney != 0)
	{
		this->m_SellMoney = p->BuyMoney;
		this->m_BuyMoney = p->BuyMoney;
		this->m_SellMoney /= 3;

		if (this->m_SellMoney >= 1000)
		{
			this->m_SellMoney = this->m_SellMoney / 100 * 100;
		}
		else if (this->m_SellMoney >= 100)
		{
			this->m_SellMoney = this->m_SellMoney / 10 * 10;
		}

		if (this->m_BuyMoney >= 1000)
		{
			this->m_BuyMoney = this->m_BuyMoney / 100 * 100;
		}
		else if (this->m_BuyMoney >= 100)
		{
			this->m_BuyMoney = this->m_BuyMoney / 10 * 10;
		}

		return;
	}

	int Level = sqrt((double)this->m_Level);
	__int64 Gold = 0;
	int Type = (this->m_Type) / MAX_SUBTYPE_ITEMS;
	int Level2 = p->Level + this->m_Level * 3;
	int excellent = 0;

	for (int i = 0; i<this->m_SpecialNum; i++)
	{
		switch (this->m_Special[i])
		{
		case 0x56:	// 86.
		case 0x57:
		case 0x58:
		case 0x59:
		case 0x5A:
		case 0x5B:
		case 0x5C:
		case 0x5D:
		case 0x5E:
		case 0x5F:
		case 0x60:
		case 0x61:
		case 0x62:
		case 0x63:	// 99.
			excellent = 1;
		}
	}

	if (excellent != 0)
	{
		Level2 += 25;
	}

	if (this->m_Type == ITEMGET(4, 15)) // Arrow
	{
		int lc10 = 70;

		if (this->m_Level == 1)
		{
			lc10 = 1200;
		}
		else if (this->m_Level == 2)
		{
			lc10 = 2000;
		}

		if (this->m_Durability > 0.0f)
		{
			Gold = lc10 * this->m_Durability / p->Durability;
		}
	}
	else if (this->m_Type == ITEMGET(4, 7)) // Arrow of Crossbow
	{
		int lc11;

		if (this->m_Durability > 0.0f)
		{
			lc11 = 100;

			if (this->m_Level == 1)
			{
				lc11 = 1400;
			}
			else if (this->m_Level == 2)
			{
				lc11 = 2200;
			}

			Gold = lc11 * this->m_Durability / p->Durability;
		}
	}
	else if (this->m_Type == ITEMGET(14, 13)) // Bless
	{
		Gold = 9000000;
	}
	else if (this->m_Type == ITEMGET(14, 14)) // soul
	{
		Gold = 6000000;
	}
	else if (this->m_Type == ITEMGET(12, 15)) // chaos
	{
		Gold = 810000;
	}
	else if (this->m_Type == ITEMGET(14, 16)) // Life
	{
		Gold = 45000000;
	}
	else if (this->m_Type == ITEMGET(14, 22)) // Creation
	{
		Gold = 36000000;
	}
	else if (this->m_Type == ITEMGET(12, 30)) //Pack Of Bless
	{
		Gold = (this->m_Level + 1) * 9000000 * 10;
	}
	else if (this->m_Type == ITEMGET(12, 31)) //Pack Of Soul
	{
		Gold = (this->m_Level + 1) * 6000000 * 10;
	}
	else if (this->m_Type == ITEMGET(13, 15)) //Fruits
	{
		Gold = 33000000;
	}
	else if (this->m_Type == ITEMGET(13, 14)) //Loch Feather
	{
		if (this->m_Level == 1)
		{
			Gold = 7500000;	// Crest ofMonarch
		}
		else
		{
			Gold = 180000;	// Blue Feather
		}
	}
	else if (this->m_Type == ITEMGET(14, 31)) // Jewel of Guardian
	{
		Gold = 60000000;
	}
	else if (this->m_Type == ITEMGET(14, 7)) // Siege Potion
	{
		if (this->m_Level == 0)
		{
			Gold = (int)(this->m_Durability) * 900000;
		}
		else if (this->m_Level == 1)
		{
			Gold = (int)(this->m_Durability) * 450000;
		}
	}
	else if (this->m_Type == ITEMGET(13, 11)) // Order(Guardian/Life Stone)
	{
		if (this->m_Level == 1)
		{
			Gold = 2400000;
		}
	}
	else if (this->m_Type == ITEMGET(13, 7)) // Contract(Summon)
	{
		if (this->m_Level == 0)
		{
			Gold = 1500000;
		}
		else if (this->m_Level == 1)
		{
			Gold = 1200000;
		}
	}
	else if (this->m_Type == ITEMGET(13, 32))
	{
		Gold = (int)this->m_Durability * 150;
	}
	else if (this->m_Type == ITEMGET(13, 33))
	{
		Gold = (int)this->m_Durability * 300;
	}
	else if (this->m_Type == ITEMGET(13, 34))
	{
		Gold = (int)this->m_Durability * 3000;
	}
	else if (this->m_Type == ITEMGET(13, 35))
	{
		Gold = 30000;
	}
	else if (this->m_Type == ITEMGET(13, 36))
	{
		Gold = 90000;
	}
	else if (this->m_Type == ITEMGET(13, 37))
	{
		Gold = 150000;
	}
	else if (this->m_Type == ITEMGET(14, 35))
	{
		Gold = (int)this->m_Durability * 2000;
	}
	else if (this->m_Type == ITEMGET(14, 36))
	{
		Gold = (int)this->m_Durability * 4000;
	}
	else if (this->m_Type == ITEMGET(14, 37))
	{
		Gold = (int)this->m_Durability * 6000;
	}
	else if (this->m_Type == ITEMGET(14, 38))
	{
		Gold = (int)this->m_Durability * 2500;
	}
	else if (this->m_Type == ITEMGET(14, 39))
	{
		Gold = (int)this->m_Durability * 5000;
	}
	else if (this->m_Type == ITEMGET(14, 40))
	{
		Gold = (int)this->m_Durability * 7500;
	}
	else if (this->m_Type == ITEMGET(13, 3)) // Dinorant
	{
		Gold = 960000;

		for (int k = 0; k<3; k++)
		{
			if ((this->m_Option3 & (1 << k)) != 0)
			{
				Gold += 300000;
			}
		}
	}
	else if (this->m_Type == ITEMGET(14, 17)) // Devil Eye
	{
		switch (this->m_Level)
		{
		case 1:
			Gold = 15000;
			break;
		case 2:
			Gold = 21000;
			break;
		case 3:
			Gold = 30000;
			break;
		case 4:
			Gold = 45000;
			break;
		case 5:
			Gold = 60000;
			break;
		case 6:
			Gold = 75000;
			break;
		default:
			Gold = 30000;
			break;
		}
	}
	else if (this->m_Type == ITEMGET(14, 18)) // Devil Key
	{
		switch (this->m_Level)
		{
		case 1:
			Gold = 15000;
			break;
		case 2:
			Gold = 21000;
			break;
		case 3:
			Gold = 30000;
			break;
		case 4:
			Gold = 45000;
			break;
		case 5:
			Gold = 60000;
			break;
		case 6:
			Gold = 75000;
			break;
		default:
			Gold = 30000;
			break;
		}
	}
	else if (this->m_Type == ITEMGET(14, 19)) // Devil's Invitation
	{
		switch (this->m_Level)
		{
		case 1:
			Gold = 60000;
			break;
		case 2:
			Gold = 84000;
			break;
		case 3:
			Gold = 120000;
			break;
		case 4:
			Gold = 180000;
			break;
		case 5:
			Gold = 240000;
			break;
		case 6:
			Gold = 300000;
			break;
		default:
			Gold = 120000;
			break;
		}
	}
	else if (this->m_Type == ITEMGET(14, 20)) // Remedy Of Love
	{
		Gold = 900;
	}
	else if (this->m_Type == ITEMGET(14, 21)) // Rena
	{
		switch (this->m_Level)
		{
		case 0:	// Rena
			Gold = 9000;
			this->m_Durability = this->m_BaseDurability;
		case 1:	// Stone
			Gold = 9000;
			this->m_Durability = this->m_BaseDurability;
			break;
		case 3:	// Mark of Lord
			Gold = (int)(this->m_Durability) * 3900;
			break;
		default:
			Gold = 9000;
			this->m_Durability = this->m_BaseDurability;
		}
	}
	else if (this->m_Type == ITEMGET(14, 9) && this->m_Level == 1) // Ale
	{
		Gold = 1000;
	}
	else if (this->m_Type == ITEMGET(13, 18)) // Invisibility Cloak
	{
		switch (this->m_Level)
		{
		case 1:
			Gold = 150000;
			break;
		case 2:
			Gold = 660000;
			break;
		case 3:
			Gold = 720000;
			break;
		case 4:
			Gold = 780000;
			break;
		case 5:
			Gold = 840000;
			break;
		case 6:
			Gold = 900000;
			break;
		case 7:
			Gold = 960000;
			break;
		default:
			Gold = 600000;
			break;
		}
	}
	else if (this->m_Type == ITEMGET(13, 16) || this->m_Type == ITEMGET(13, 17)) // Blood and Paper of BloodCastle
	{
		switch (this->m_Level)
		{
		case 1:
			Gold = 15000;
			break;
		case 2:
			Gold = 21000;
			break;
		case 3:
			Gold = 30000;
			break;
		case 4:
			Gold = 39000;
			break;
		case 5:
			Gold = 48000;
			break;
		case 6:
			Gold = 60000;
			break;
		case 7:
			Gold = 75000;
			break;
		default:
			Gold = 15000;
			break;
		}
	}
	else if (this->m_Type == ITEMGET(13, 29)) // Armor of Guardman
	{
		Gold = 5000;
	}
	else if (this->m_Type == ITEMGET(13, 20)) // Wizards Ring
	{
		switch (this->m_Level)
		{
		case 0:
			Gold = 30000;
			break;

		default:
			Gold = 0;
		}
	}
	else if (this->m_Type == ITEMGET(13, 31)) // Spirit
	{
		switch (this->m_Level)
		{
		case 0:
			Gold = 30000000;
			break;

		case 1:
			Gold = 15000000;
		}
	}
	else if (this->m_Type == ITEMGET(14, 28)) // Lost Map
	{
		Gold = 600000;
	}
	else if (this->m_Type == ITEMGET(14, 29)) // Symbol of Kundun
	{
		Gold = ((10000.0f) * this->m_Durability) * 3.0f;
	}
	else if (this->m_Type == ITEMGET(14, 45) ||
		this->m_Type == ITEMGET(14, 46) ||
		this->m_Type == ITEMGET(14, 47) ||
		this->m_Type == ITEMGET(14, 48) ||
		this->m_Type == ITEMGET(14, 49) ||
		this->m_Type == ITEMGET(14, 50))
	{
		Gold = ((50.0f) * this->m_Durability) * 3.0f;
	}
	else if (this->m_Type == ITEMGET(12, 26))
	{
		switch (this->m_Level)
		{
		case 0:
			Gold = 60000;
			break;
		}
	}
	else if (p->Value > 0)
	{
		Gold += (p->Value * p->Value * 10) / 12;

		if (this->m_Type >= ITEMGET(14, 0) && this->m_Type <= ITEMGET(14, 8))	// Potions + Antidote
		{
			if (this->m_Level > 0)
			{
				Gold *= (__int64)(pow(2.0f, Level));
			}

			Gold = Gold / 10 * 10;
			Gold *= (__int64)this->m_Durability;
			this->m_BuyMoney = Gold;
			this->m_SellMoney = Gold / 3;
			this->m_SellMoney = this->m_SellMoney / 10 * 10;
			return;
		}
	}
	else if ((Type == 12 && this->m_Type > ITEMGET(12, 6)) || Type == 13 || Type == 15)
	{
		Gold = Level2*Level2*Level2 + 100;

		for (int u = 0; u<this->m_SpecialNum; u++)
		{
			switch (this->m_Special[u])
			{
			case 0x55:
				Gold += Gold*this->m_Option3;
			}
		}
	}
	else
	{
		switch (this->m_Level)
		{
		case  5:	Level2 += 4;	break;
		case  6:	Level2 += 10;	break;
		case  7:	Level2 += 25;	break;
		case  8:	Level2 += 45;	break;
		case  9:	Level2 += 65;	break;
		case 10:	Level2 += 95;	break;
		case 11:	Level2 += 135;	break;
		case 12:	Level2 += 185;	break;
		case 13:	Level2 += 245;	break;
		}

		if (Type == 12 && this->m_Type <= ITEMGET(12, 6))	// Wings
		{
			Gold = (Level2 + 40)*Level2*Level2 * 11 + 40000000;
		}
		else
		{
			Gold = (Level2 + 40)*Level2*Level2 / 8 + 100;
		}

		if (Type >= 0 && Type <= 6)
		{
			if (p->TwoHand == 0)
			{
				Gold = Gold * 80 / 100;
			}
		}

		for (int g = 0; g<this->m_SpecialNum; g++)
		{
			switch (this->m_Special[g])
			{
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 56:
				Gold += (__int64)(Gold * 1.5);
				break;

			case 80:
			case 81:
			case 83:
			case 85:

				switch (this->m_Option3)
				{
				case 1:
					Gold += (__int64)(Gold * 6.0 / 10.0);
					break;

				case 2:
					Gold += (__int64)(Gold * 14.0 / 10.0);
					break;

				case 3:
					Gold += (__int64)(Gold * 28.0 / 10.0);
					break;

				case 4:
					Gold += (__int64)(Gold * 56.0 / 10.0);
					break;
				}
				break;

			case 82:

				switch (this->m_Option3)
				{
				case 1:
					Gold += (__int64)(Gold * 6.0 / 10.0);
					break;

				case 2:
					Gold += (__int64)(Gold * 14.0 / 10.0);
					break;

				case 3:
					Gold += (__int64)(Gold * 28.0 / 10.0);
					break;

				case 4:
					Gold += (__int64)(Gold * 56.0 / 10.0);
					break;
				}
				break;

			case 84:
				Gold += (__int64)(Gold * 25.0 / 100.0);
				break;

			case 86:
			case 87:
			case 88:
			case 89:
			case 90:
			case 91:
			case 92:
			case 93:
			case 94:
			case 95:
			case 96:
			case 97:
			case 98:
			case 99:
				Gold += Gold;
				break;

			case 100:
			case 101:
			case 102:
			case 103:
			case 104:
				Gold += (__int64)(Gold * 25.0 / 100.0);
				break;

			}
		}
	}

	if (Gold > 3000000000)
	{
		Gold = 3000000000;
	}

	this->m_BuyMoney = (DWORD)Gold;
	this->m_SellMoney = (DWORD)Gold;

	this->m_SellMoney = this->m_SellMoney / 3;

	if ((this->m_Type < ITEMGET(14, 0) || this->m_Type >  ITEMGET(14, 8)) &&
		this->m_Type != ITEMGET(13, 20) &&
		this->m_Type != ITEMGET(14, 28) &&
		this->m_Type != ITEMGET(14, 29) &&
		this->m_Type != ITEMGET(14, 21) &&
		this->m_Type != ITEMGET(13, 15) &&
		this->m_Type != ITEMGET(13, 16) &&
		this->m_Type != ITEMGET(13, 17) &&
		this->m_Type != ITEMGET(13, 18) &&
		this->m_Type != ITEMGET(13, 11) &&
		this->m_Type != ITEMGET(13, 7) &&
		this->m_Type != ITEMGET(13, 32) &&
		this->m_Type != ITEMGET(13, 33) &&
		this->m_Type != ITEMGET(13, 34) &&
		this->m_Type != ITEMGET(13, 35) &&
		this->m_Type != ITEMGET(13, 36) &&
		this->m_Type != ITEMGET(13, 37) &&
		this->m_Type != ITEMGET(14, 45) &&
		this->m_Type != ITEMGET(14, 46) &&
		this->m_Type != ITEMGET(14, 47) &&
		this->m_Type != ITEMGET(14, 48) &&
		this->m_Type != ITEMGET(14, 49) &&
		this->m_Type != ITEMGET(14, 50))
	{
		float lc15 = 1.0f - (this->m_Durability / this->m_BaseDurability);
		int lc16 = this->m_SellMoney*0.6*lc15;
		this->m_SellMoney -= lc16;
	}

	if (this->m_SellMoney >= 1000)
	{
		this->m_SellMoney = this->m_SellMoney / 100 * 100;
	}
	else if (this->m_SellMoney >= 100)
	{
		this->m_SellMoney = this->m_SellMoney / 10 * 10;
	}

	if (this->m_BuyMoney >= 1000)
	{
		this->m_BuyMoney = this->m_BuyMoney / 100 * 100;
	}
	else if (this->m_BuyMoney >= 100)
	{
		this->m_BuyMoney = this->m_BuyMoney / 10 * 10;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CItem::GetSize(int & w, int & h)
{
	w = ItemAttribute[this->m_Type].Width;
	h = ItemAttribute[this->m_Type].Height;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LPSTR CItem::GetName()
{
	return ItemAttribute[this->m_Type].Name;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
