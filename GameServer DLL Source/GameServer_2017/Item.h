#ifndef ITEM_H
#define ITEM_H

#ifdef GS_99_60T
#define ITEM_ATTRIBUTE_BASE		0x9439368
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAX_TYPE_PLAYER				5
#define MAX_ITEM_LEVEL				15
#define MAX_TYPE_ITEMS				16
#define MAX_SUBTYPE_ITEMS			32
#define MAX_ITEM_INFO				7
#define MAX_ITEM_SPECIAL_ATTRIBUTE	7
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAX_ITEMS	(MAX_TYPE_ITEMS * MAX_SUBTYPE_ITEMS)
#define ITEMGET(x,y) ((x)*MAX_SUBTYPE_ITEMS + (y))
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
	char Name[32]; // 0
	BYTE HaveItemInfo; // 20
	BYTE TwoHand;	// 21
	BYTE Level; // 22
	BYTE Width;	// 23
	BYTE Height;	// 24
	char Serial; // 25
	BYTE OptionFlag; // 26
	BYTE MondownFlag; // 27
	BYTE AttackSpeed; // 28
	BYTE WalkSpeed; // 29
	BYTE DamageMin; // 2A
	BYTE DamageMax; // 2B
	BYTE SuccessfulBlocking; // 2C
	BYTE Defense; // 2D
	BYTE MagicDefense; // 2E
	BYTE Speed;	// 2F
	BYTE Durability; // 30
	BYTE MagicDurability; // 31
	BYTE AttackDur;	// 32
	BYTE DefenceDur; // 33
	WORD RequireStrength; // 34
	WORD RequireDexterity; // 36
	WORD RequireEnergy; // 38
	WORD RequireLevel; // 3A
	WORD Value; // 3C
	BYTE RequireClass[MAX_TYPE_PLAYER]; // 3E
	BYTE Resistance[MAX_ITEM_SPECIAL_ATTRIBUTE]; // unk43 - Ice poisonous lightning non ground wind water
	WORD RequireVitality;	// 4A
	int BuyMoney; // 4C
	int MagicPW; // 50
	float RepaireMoneyRate;	// 54
	float AllRepaireMoneyRate; // 58
	bool QuestItem;	// 5C
	BYTE SetAttr; // 5D
	BYTE ResistanceType;	// 5E
	int ItemSlot; // 60
	int SkillType; // 64
	int RequireLeadership;	// 68

}  ITEM_ATTRIBUTE;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct CITEM_STRUCT
{
	ULONG m_Number; // +0x0(0x4)
	CHAR m_serial; // +0x4(0x1)
	SHORT m_Type; // +0x6(0x2)
	SHORT m_Level; // +0x8(0x2)
	UCHAR m_Part; // +0xa(0x1)
	UCHAR m_Class; // +0xb(0x1)
	UCHAR m_TwoHand; // +0xc(0x1)
	UCHAR m_AttackSpeed; // +0xd(0x1)
	UCHAR m_WalkSpeed; // +0xe(0x1)
	USHORT m_DamageMin; // +0x10(0x2)
	USHORT m_DamageMax; // +0x12(0x2)
	UCHAR m_SuccessfulBlocking; // +0x14(0x1)
	USHORT m_Defense; // +0x16(0x2)
	USHORT m_MagicDefense; // +0x18(0x2)
	UCHAR m_Speed; // +0x1a(0x1)
	USHORT m_DamageMinOrigin; // +0x1c(0x2)
	USHORT m_DefenseOrigin; // +0x1e(0x2)
	USHORT m_Magic; // +0x20(0x2)
	float m_Durability; // +0x24(0x4)
	USHORT m_DurabilitySmall; // +0x28(0x2)
	float m_BaseDurability; // +0x2c(0x4)
	UCHAR m_SpecialNum; // +0x30(0x1)
	UCHAR m_Special[0x8]; // +0x31(0x8)
	UCHAR m_SpecialValue[0x8]; // +0x39(0x8)
	USHORT m_RequireStrength; // +0x42(0x2)
	USHORT m_RequireDexterity; // +0x44(0x2)
	USHORT m_RequireEnergy; // +0x46(0x2)
	USHORT m_RequireLevel; // +0x48(0x2)
	USHORT m_RequireLeaderShip; // +0x4a(0x2)
	USHORT m_Leadership; // +0x4c(0x2)
	UCHAR m_RequireClass[0x5]; // +0x4e(0x5)
	UCHAR m_Resistance[0x7]; // +0x53(0x7)
	int m_Value; // +0x5c(0x4)
	ULONG m_SellMoney; // +0x60(0x4)
	ULONG m_BuyMoney; // +0x64(0x4)
	int m_iPShopValue; // +0x68(0x4)
	UCHAR m_bItemExist; // +0x6c(0x1)
	int m_OldSellMoney; // +0x70(0x4)
	int m_OldBuyMoney; // +0x74(0x4)
	UCHAR m_Option1; // +0x78(0x1)
	UCHAR m_Option2; // +0x79(0x1)
	UCHAR m_Option3; // +0x7a(0x1)
	UCHAR m_NewOption; // +0x7b(0x1)
	float m_DurabilityState[0x4]; // +0x7c(0x10)
	float m_CurrentDurabilityState; // +0x8c(0x4)
	UCHAR m_SkillChange; // +0x90(0x1)
	UCHAR m_QuestItem; // +0x91(0x1)
	UCHAR m_SetOption; // +0x92(0x1)
	UCHAR m_SetAddStat; // +0x93(0x1)
	UCHAR m_IsValidItem; // +0x94(0x1)
	UCHAR m_SkillResistance[0x7]; // +0x95(0x7)
	int m_IsLoadPetItemInfo; // +0x9c(0x4)
	int m_PetItem_Level; // +0xa0(0x4)
	int m_PetItem_Exp; // +0xa4(0x4)
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CItem // Never Edit ! 
{
public:
	CItem();
	void Clear();
	bool IsItem();
	int IsSetItem();
	void Convert(int type, char Option1, char Option2, char Option3, char Attribute2, char SetOption, char DbVersion);
	int GetLevel();
	DWORD GetNumber();
	void Value();
	void OldValue();
	void GetSize(int& w, int& h);
	int ItemDamageMin();
	int ItemDefense();
	int IsClass(char aClass, int ChangeUP);
	LPSTR GetName();
	void PlusSpecialSetRing(unsigned char* Value);
	void PlusSpecial(int* Value, int Special);
	void PlusSpecialPercent(int* Value, int Special, WORD Percent);
	void PlusSpecialPercentEx(int* Value, int SourceValue, int Special);
	void SetItemPlusSpecialStat(short* Value, int Special);
	int GetAddStatType();
	int GetWeaponType();
	void SetPetItemInfo(int petlevel, int petexp);
	int AddPetItemExp(int petexp);
	int DecPetItemExp(int percent);
	int PetItemLevelDown(int exp);
	void PetValue();
	int IsExtItem();
	int IsExtLifeAdd();
	int IsExtManaAdd();
	int IsExtDamageMinus();
	int IsExtDamageReflect();
	int IsExtDefenseSuccessfull();
	int IsExtMonsterMoney();
	int IsExtExcellentDamage();
	int IsExtAttackRate();
	int IsExtAttackRate2();
	int IsExtAttackSpeed();
	int IsExtMonsterDieLife();
	int IsExtMonsterDieMana();
	int IsWingOpGetOnePercentDamage();
	int IsWingOpGetLifeToMonster();
	int IsWingOpGetManaToMoster();
	int IsDinorantReduceAttackDamaege();
	int SimpleDurabilityDown(int iDur);
	int DurabilityDown(int dur, int aIndex);
	int DurabilityDown2(int dur, int aIndex);
	int NormalWeaponDurabilityDown(int defence, int aIndex);
	int BowWeaponDurabilityDown(int defence, int aIndex);
	int StaffWeaponDurabilityDown(int defence, int aIndex);
	int ArmorDurabilityDown(int damagemin, int aIndex);
	int CheckDurabilityState();

	DWORD m_Number; // 0
	char m_serial;	// 4
	short m_Type; // 6
	short m_Level; // 8
	BYTE m_Part;	// A
	BYTE m_Class;	// B
	BYTE m_TwoHand;	// C
	BYTE m_AttackSpeed;	// D
	BYTE m_WalkSpeed;	// E
	WORD m_DamageMin;	// 10
	WORD m_DamageMax;	// 12
	BYTE m_SuccessfulBlocking;	// 14
	WORD m_Defense;	// 16
	WORD m_MagicDefense;	// 18
	BYTE m_Speed;	// 1A
	WORD m_DamageMinOrigin;	// 1C
	WORD m_DefenseOrigin;	// 1E
	WORD m_Magic;	// 20
	float m_Durability; // 24
	WORD m_DurabilitySmall; // 28
	float m_BaseDurability;	// 2C
	BYTE m_SpecialNum;	// 30
	BYTE m_Special[8];	// 31
	BYTE m_SpecialValue[8];	// 39
	WORD m_RequireStrength;	// 42
	WORD m_RequireDexterity;	// 44
	WORD m_RequireEnergy;	// 46
	WORD m_RequireLevel;	// 48
	WORD m_RequireVitality;	// 4A
	WORD m_RequireLeaderShip;	// 4C
	WORD m_Leadership;	// 4E
	BYTE m_RequireClass[MAX_TYPE_PLAYER];	// 50
	BYTE m_Resistance[MAX_ITEM_SPECIAL_ATTRIBUTE];	// 55
	int m_Value;	// 5C
	DWORD m_SellMoney;	// 60
	DWORD m_BuyMoney;	// 64
	int m_iPShopValue;	// 68
	bool m_bItemExist;	// 6C
	int m_OldSellMoney;	// 70
	int m_OldBuyMoney;	// 74
	BYTE m_Option1;	// 78  Skill
	BYTE m_Option2;	// 79  Luck
	BYTE m_Option3;	// 7A  Option
	BYTE m_NewOption;	// 7B ExcellentOption
	float m_DurabilityState[4];	// 7C
	float m_CurrentDurabilityState;	// 8C
	bool m_SkillChange;	// 90
	bool m_QuestItem;	// 91
	BYTE m_SetOption;	// 92
	BYTE m_SetAddStat;	// 93
	bool m_IsValidItem;	// 94
	BYTE m_SkillResistance[MAX_ITEM_SPECIAL_ATTRIBUTE];	// 95
	BOOL m_IsLoadPetItemInfo;	// 9C
	int  m_PetItem_Level;	// A0
	int  m_PetItem_Exp; // A4
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ItemGetSize		(int index, int & width, int & height);
void ItemByteConvert	(unsigned char* buf, CItem item); 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif /* ITEM_H */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------