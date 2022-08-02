#include "Stdafx.h"
#include "MyMain.h"
#include "Console.h"
#include "TPacket.h"
//-----------------------------------------------------------------------------------------------------------
// made by Leo123 (czf.leo123@gmail.com) Leonid Vinikov
//-----------------------------------------------------------------------------------------------------------

// Main's adreess to varibales
//-----------------------------------------------------------------------------------------------------------
char * aData2Skill		= (char *)0x676428;
char * aIce_smd			= (char *)0x676438;
char * aLA_smd			= (char *)0x6763D8;
char * aWall_smd		= (char *)0x6763F8;
char * aWalls_smd		= (char *)0x676404;
char * a_smd_1			= (char *)0x676410;
char * aA_smd			= (char *)0x6763E8;
char * aT_smd_0			= (char *)0x6763A0;
char * aMagic_c_smd		= (char *)0x676394;
char * aTyphoon_smd		= (char *)0x676378;
char * aDargon_magic_	= (char *)0x676364;
char * aBones_warrior_	= (char *)0x676350;
char * aBone_a_smd		= (char *)0x676344;
char * aBone_c_sm		= (char *)0x676338;
char * aSP_smd			= (char *)0x67632C;
char * aBons_p01_smd	= (char *)0x67631C;
char * aSnow_p01_smd	= (char *)0x6762FC;
char * aSnow_p02_smd	= (char *)0x6762EC;
char * aSnow_p03_smd	= (char *)0x6762DC;
char * aUnicon_smd		= (char *)0x67629C;
char * aArrow_smd		= (char *)0x676290;
char * aN_smd_1			= (char *)0x676278;
char * aN_smd_0			= (char *)0x676284;
char * aQOU_smd			= (char *)0x676240;
char * aMston_b_smd		= (char *)0x676218;
char * aMston_a_smd		= (char *)0x676224;
char * aPXO_smd			= (char *)0x6761F8;
char * aDargon_magic_s	= (char *)0x676364;
char * aBone_c_smd		= (char *)0x676338;
char * aN_smd_2			= (char *)0x676250;
char * aBons_p02_smd	= (char *)0x67630C;
char * aACO_smd_0		= (char *)0x6761C0;
char * aTCV_smd			= (char *)0x676158;
char * aMagic2_smd		= (char *)0x6760EC;
char * aMagic3_smd		= (char *)0x6760E0;
char * aPiercing_smd	= (char *)0x6760D0;
char * aIce				= (char *)0x6760CC;
char * aFire			= (char *)0x6760B8;
char * aPoison			= (char *)0x6760B0;
char * aStone			= (char *)0x6760A8;
char * aCircle			= (char *)0x6760A0;
char * aMagic			= (char *)0x676098;
char * aStorm			= (char *)0x676090;
char * aLaser			= (char *)0x676088;
char * aSkeleton_0		= (char *)0x67607C;
char * aBone			= (char *)0x676070;
char * aSnow			= (char *)0x676068;
char * aRider			= (char *)0x676060;
char * aDarkhorse		= (char *)0x675F7C;
char * aDarkspirit		= (char *)0x675F70;
char * aHellgate		= (char *)0x675F4C;
char * aArrow			= (char *)0x675F44;
char * aArrowsteel		= (char *)0x675F38;
char * aArrowthunder	= (char *)0x675F28;
char * aArrowlaser		= (char *)0x675F1C;
char * aArrowv			= (char *)0x675F14;
char * aArrowsaw		= (char *)0x675F08;
char * aArrownature		= (char *)0x675EFC;
char * aProtect			= (char *)0x675EF4;
char * aRidingspear		= (char *)0x675EE8;
char * aBigstone		= (char *)0x675EDC;
char * aMagiccircle		= (char *)0x675ED0;
char * aArrowwing		= (char *)0x675EC4;
char * aArrowbomb		= (char *)0x675EB8;
char * aBall			= (char *)0x675EB0;
char * aBlast			= (char *)0x675EA8;
char * aArrowdouble		= (char *)0x675E94;
char * aInferno			= (char *)0x675EA0;
char * aKcross			= (char *)0x675E8C;
char * aCarow			= (char *)0x675E84;
char * aCombo			= (char *)0x675E7C;
char * aGate			= (char *)0x675E74;
char * aStonecoffin		= (char *)0x675E58;
char * aMonster_0		= (char *)0x673DBC;
char * aSkill			= (char *)0x673DC8;
char * aAirforce		= (char *)0x675E4C;
char * aM_waves			= (char *)0x675E44;
char * aM_piercing		= (char *)0x675E38;
char * aPierpart		= (char *)0x675E2C;
char * aDarklordskill	= (char *)0x675E1C;
char * aGroundstone		= (char *)0x675E10;
char * aGroundstone2	= (char *)0x675E00;
char * aSeamanfx		= (char *)0x675DF4;
char * aSkull			= (char *)0x675DEC;
char * aLacearrow		= (char *)0x675DE0;
char * aItem			= (char *)0x673DD0;
char * aEarthquake		= (char *)0x0675DD4;
char * aFlashing		= (char *)0x0675DC8;
char * aTail			= (char *)0x0675DC0;
char * aPiercing		= (char *)0x0675DB4;
char * aWaveforce		= (char *)0x0675DA8;
char * aBlizzard		= (char *)0x0675D9C;
char * aManyflag		= (char *)0x675D90;
char * aMusign			= (char *)0x675D88;
char * aGroundcrystal	= (char *)0x675D78;
char * aSkinshell		= (char *)0x675D6C;
char * aManarune		= (char *)0x675D60;
char * aJavelin			= (char *)0x675D58;
char * aArrowimpact		= (char *)0x675D4C;
char * aSwordforce		= (char *)0x675D40;
char * aFlybigstone1	= (char *)0x675D30;
char * aFlybigstone2	= (char *)0x675D20;
char * aFlysmallstone1	= (char *)0x675D10;
char * aFlysmallstone2	= (char *)0x675D00;
char * aWallstone1		= (char *)0x675CF4;
char * aWallstone2		= (char *)0x675CE8;
char * aGatepart1		= (char *)0x675CDC;
char * aGatepart2		= (char *)0x675CD0;
char * aGatepart3		= (char *)0x675CC4;
char * aAurora			= (char *)0x675CBC;
char * aTowergateplane	= (char *)0x675CAC;
char * aGolem_stone		= (char *)0x675CA0;
char * aBossrock		= (char *)0x675C94;
char * aBossrocklight	= (char *)0x675C84;
char * aProtectguild	= (char *)0x675C74;
char * aNpc				= (char *)0x673DB4;
char * aObject31		= (char *)0x675938;

char * aEffect			= (char *)0x675C6C;
char * aSkillFlower1_t	= (char *)0x675C58;
char * aSkillFlower2_t	= (char *)0x675C44;
char * aSkillFlower3_t	= (char *)0x675C30;
char * aDataSkill		= (char *)0x6760C0;
char * aSkillDkthreebo  = (char *)0x675F58;
char * aDataObject12	= (char *)0x675E64;

void * unk_6763C8		= (void *)0x6763C8;
void * unk_6763BC		= (void *)0x6763BC;
void * unk_6763AC		= (void *)0x6763AC;
void * unk_67626C		= (void *)0x67626C;
void * unk_676260		= (void *)0x676260;
void * unk_676230		= (void *)0x676230;
void * unk_6761E0		= (void *)0x6761E0;
void * unk_6761A8		= (void *)0x6761A8;
void * unk_676198		= (void *)0x676198;
void * unk_676178		= (void *)0x676178;
void * unk_676168		= (void *)0x676168;
void * unk_67614C		= (void *)0x67614C;
void * unk_676140		= (void *)0x676140;
void * unk_676134		= (void *)0x676134;
void * unk_676128		= (void *)0x676128;
void * unk_67611C		= (void *)0x67611C;
void * unk_676104		= (void *)0x676104;
void * unk_6760F8		= (void *)0x6760F8;
void * unk_676110		= (void *)0x676110;
void * unk_675F88		= (void *)0x675F88;

BYTE byte_6719C8		= (BYTE)0x6719C8;
DWORD off_676078		= (DWORD)0x676078;
//-----------------------------------------------------------------------------------------------------------

_ProtocolCore	_core_recv;
std::string		playerName;
BYTE			AcessState = 0xFF;
//-----------------------------------------------------------------------------------------------------------

bool MyMain::is_firstPacketRecvied = false;
//-----------------------------------------------------------------------------------------------------------

void MyMain::HookAll()
{
	// get addr of addons.dll ProtocolCore;
	_core_recv = (_ProtocolCore)GetProcAddress(LoadLibrary("Addons.dll"), "NSProtocolCore");
	// ----
	// # Hook ProtocolCore
	// ----
	BYTE PROTOCOL_CORE_HOOK[] = { 0xFF ,0x15 ,0x144 ,0x113 ,0x140 ,0x100 ,0x190 ,0x190 };
	DWORD * PROTOCOL_CORE_HOOK_PLACE = (DWORD*)0x4CDA7D;

	memcpy(PROTOCOL_CORE_HOOK_PLACE, PROTOCOL_CORE_HOOK, sizeof(PROTOCOL_CORE_HOOK));

	SetOffset(0x00401344, (DWORD)& ProtocolCore);

	// leo123
	return; // 

	// ----
	// # Load Skills
	// ----
	BYTE LOAD_SKILLS_HOOK[] = {/*JMP DWORD PTR DS:[4CB136]*/0xFF ,0x25 ,0x36 ,0xB1 ,0x4C ,0x00, /* NOP */ 0x90 };
	DWORD *	LOAD_SKILLS_HOOK_PLACE = (DWORD*)0x5E84E0;

	memcpy(LOAD_SKILLS_HOOK_PLACE, LOAD_SKILLS_HOOK, sizeof(LOAD_SKILLS_HOOK));

	SetOffset(0x4CB136, (DWORD)& LoadSkills);
	// ----
	// # ViewSkillState
	// ----
	// set address of ViewSkillState(...) somewhere
	SetOffset(0x412282, (DWORD)& ViewSkillState);
	HookViewSkillState(true);
}
//-----------------------------------------------------------------------------------------------------------

void MyMain::HookViewSkillState(bool action) // rewrite later
{
	// offset to place the hook
	DWORD *	ADDR_sub_412290		= (DWORD*)0x412290;

	if(action)
	{
		// construct hook
		BYTE JMP2Hook_sub_412290 [] = {/*JMP DWORD PTR DS:[0x412282]*/0xFF ,0x25 ,0x82 ,0x22 ,0x41 ,0x00, /* NOP */ 0x90};
		// make cal to somewhere to call sub_412290
		memcpy(ADDR_sub_412290, JMP2Hook_sub_412290, sizeof(JMP2Hook_sub_412290)); 
		return;
	}
	// destruct hook, (back orginal)
	BYTE JMP2UNHook_sub_412290 [] = {0x55, 0x8B, 0xEC, 0x64, 0xA1, 0x00, 0x00};
	// make cal to somewhere to call sub_412290
	memcpy(ADDR_sub_412290, JMP2UNHook_sub_412290, sizeof(JMP2UNHook_sub_412290)); 
}
//-----------------------------------------------------------------------------------------------------------

int MyMain::ProtocolCore(BYTE xcode, LPBYTE aRecv, unsigned int len, int a5)
{
	MyMain::is_firstPacketRecvied = true;

	#if(ABSOLUTE_CONSOLE == ON)

	Console.Write("ProtocolCore() xcode : %2x, len : %d, index : %d", xcode, len, a5);

	if (aRecv[0] == 0xC1)
	{
		char packetString[2048] = { 0 };

		sprintf(packetString, "%02X", aRecv[0]);

		for (DWORD i = 1; i < len; ++i)
		{
			sprintf(packetString, "%s %02X", packetString, aRecv[i]);
		}

		Console.Write(packetString);
	}
	
	#endif

	if (xcode == 0xF3)
	{
		if (aRecv[3] == 0x70)
		{
			aRecv[3] = 0x3;
		}
	}


	if(xcode == 0xF1)
	{
		if(aRecv[3] == 255)
		{
			CPacket extraInfo(aRecv, len);

			extraInfo.readByte();
			extraInfo.readByte();

			playerName = extraInfo.readString();		
			AcessState = extraInfo.readByte();

			if(AcessState == 0xFF)
			{
				playerName = "";
			}

			return true;
		}
	}

	// addons.dll : ProtocolCore
	_core_recv(xcode, aRecv, len, a5);

	/*	
	_asm 
	{
		//MOV EDI,6ACA18B0 // addons.dll::PrtocolCore
		MOV EDI,0x4CDB60
		PUSH a5
		PUSH len
		PUSH aRecv
		PUSH xcode
		call edi
		add esp,0x10
	}
	*/
}
//-----------------------------------------------------------------------------------------------------------

int MyMain::ViewSkillState(unknown_struct_5540D0 * a1)
{	
  char ctlcode; // al@3
  int result; // eax@9
  int v3; // eax@12
  int v4; // eax@14
  int v5; // eax@16
  int v6; // eax@18
  int v7; // eax@20
  int v8; // eax@22
  char szName[11] = {0};

  memcpy(szName, & a1->playerName, 10);


  if (playerName.length())
  {
	  if (strcmp((const char *)playerName.c_str(), szName) == 0)
	  {
		  if (AcessState == 0x00)
		  {
			  a1->byte358 = 5; // GM
		  }
		  else if (AcessState == 0x01)
		  {
			  a1->byte358 = 3; // VIP
		  }
		  else if (AcessState == 0x02)
		  {
			  a1->byte358 = 2; // GI
		  }
	  }
  }

  if((0x1020000 & a1->viewSkillState) == 0x1020000) // VIP
  {
    if ( a1->dword35C && a1->byte358 != 3 )
      sub_412530((int)a1);
	  a1->byte358 = 3;
  }
  else if((0x1040000 & a1->viewSkillState) == 0x1040000) // GI
  {
    if (a1->dword35C && a1->byte358 != 2 )
      sub_412530((int)a1);

	  a1->byte358 = 2;
  }
  if(((0x01000000 & a1->viewSkillState) == 0x01000000) || (ctlcode = a1->ctlcode, ctlcode == 32) || (ctlcode == 8 ))
  {
    if( a1->dword35C && a1->byte358 != 5)
      sub_412530((int)a1);

    a1->byte358 = 5;
  }

  result = a1->dword35C;
  if ( !result )
  {
    result = a1->byte358;
    if ( (BYTE)result )
    {
      result = (unsigned __int8)result;
      switch ( result )
      {
/*		case 2: // GI
		//MessageBoxA(0, "case 2", "Eliad -> TEST", MB_ICONERROR);
          v3 = sub_649E83(472);
          if ( !v3 )
            goto LABEL_24;
		   //Console.Write("[GI] %s %d %x",szName, ctlcode, a1->dword78);
		  result = sub_412560(v3, 294, 20, 1, 1116471296, -1063256064, 0, 0, 0, 1110704128);
          goto LABEL_25;

        case 3: // vip
		//MessageBoxA(0, "case 3", "Eliad -> TEST", MB_ICONERROR);
          v3 = sub_649E83(472);
          if ( !v3 )
            goto LABEL_24;
		  result = sub_412560(v3, 316, 20, 1, 1116471296, -1063256064, 0, 0, 0, 1110704128);
          goto LABEL_25;

        case 4: // flags
		//MessageBoxA(0, "case 4", "Eliad -> TEST", MB_ICONERROR);
          v3 = sub_649E83(472);
          if ( !v3 )
            goto LABEL_24;
          result = sub_412560(v3, 294, 2, 0, 0, 0, 0, 0, 0, 0);
          goto LABEL_25;

        case 5: // GM
		//MessageBoxA(0, "case 5", "Eliad -> TEST", MB_ICONERROR);
          v4 = sub_649E83(472);
          if ( !v4 )
            goto LABEL_24;

		  //Console.Write("[GM] %s %d %x",szName, ctlcode, a1->dword78);
          result = sub_412560(v4, 295, 20, 1, 1116471296, -1063256064, 0, 0, 0, 1110704128);
          goto LABEL_25;

        /*case 6:
		//MessageBoxA(0, "case 6", "Eliad -> TEST", MB_ICONERROR);
          v5 = sub_649E83(472);
          if ( !v5 )
            goto LABEL_24;
          result = sub_4129A0(v5, 1591, 0, 20, 1123024896, 0, 0);
          goto LABEL_25;
        
		case 7:
		//MessageBoxA(0, "case 7", "Eliad -> TEST", MB_ICONERROR);
          v6 = sub_649E83(472);
          if ( !v6 )
            goto LABEL_24;
          result = sub_4129A0(v6, 1591, 2, 20, 1123024896, 0, 0);
          goto LABEL_25;
        
		case 8:
		//MessageBoxA(0, "case 8", "Eliad -> TEST", MB_ICONERROR);
          v7 = sub_649E83(472);
          if ( !v7 )
            goto LABEL_24;
          result = sub_4129A0(v7, 1591, 1, 20, 1123024896, 0, 0);
          goto LABEL_25;
		  
        case 9:
		//MessageBoxA(0, "case 9", "Eliad -> TEST", MB_ICONERROR);
          v8 = sub_649E83(472);
          if ( v8 )
            result = sub_4129A0(v8, 1591, 3, 20, 1123024896, 0, 0);
          else
LABEL_24:
            result = 0;
LABEL_25:
          a1->dword35C = result;
          break;*/
        default:
			{
          return result;
			}
      }
    }
  } 

  return result;
}
//-----------------------------------------------------------------------------------------------------------

void MyMain::LoadSkills()
{
  int v0; // esi@4
  int v1; // esi@6
  int v2; // esi@8
  int v3; // esi@10
  int v4; // esi@14
  signed int v5; // esi@16
  int v6; // esi@20

  if(! byte_6719C8 )
  {
    sub_5E0EE0(193, aData2Skill, aIce_smd);
    sub_5E0EE0(194, aData2Skill, a_smd_1);
    sub_5E0EE0(195, aData2Skill, aWall_smd);
    sub_5E0EE0(200, aData2Skill, aA_smd);
    sub_5E0EE0(201, aData2Skill, aLA_smd);
    sub_5E0EE0(202, aData2Skill, (const char *)&unk_6763C8);
    sub_5E0EE0(203, aData2Skill, (const char *)&unk_6763BC);
    sub_5E0EE0(204, aData2Skill, (const char *)&unk_6763AC);
    sub_5E0EE0(205, aData2Skill, aT_smd_0);
    sub_5E0EE0(206, aData2Skill, aMagic_c_smd);
    sub_5E0EE0(207, aData2Skill, aTyphoon_smd);
    sub_5E0EE0(208, aData2Skill, aDargon_magic_s);
    sub_5E0EE0(209, aData2Skill, aBones_warrior_);
    sub_5E0EE0(210, aData2Skill, aBone_a_smd);
    sub_5E0EE0(211, aData2Skill, aBone_c_smd);
    sub_5E0EE0(212, aData2Skill, aSP_smd);
    sub_5E0EE0(213, aData2Skill, aBons_p01_smd);
    sub_5E0EE0(214, aData2Skill, aBons_p02_smd);
    sub_5E0EE0(215, aData2Skill, aSnow_p01_smd);
    sub_5E0EE0(216, aData2Skill, aSnow_p02_smd);
    sub_5E0EE0(217, aData2Skill, aSnow_p03_smd);
    sub_5E0EE0(198, aData2Skill, aUnicon_smd);
    sub_5E0EE0(219, aData2Skill, aArrow_smd);
    sub_5E0EE0(220, aData2Skill, aN_smd_0);
    sub_5E0EE0(221, aData2Skill, aN_smd_1);
    sub_5E0EE0(222, aData2Skill, (const char *)&unk_67626C);
    sub_5E0EE0(223, aData2Skill, (const char *)&unk_676260);
    sub_5E0EE0(224, aData2Skill, aSP_smd);
    sub_5E0EE0(225, aData2Skill, aN_smd_2);
    sub_5E0EE0(262, aData2Skill, aQOU_smd);
    sub_5E0EE0(228, aData2Skill, (const char *)&unk_676230);
    sub_5E0EE0(229, aData2Skill, aMston_a_smd);
    sub_5E0EE0(230, aData2Skill, aMston_b_smd);
    sub_5E0EE0(236, aData2Skill, aPXO_smd);
    sub_5E0EE0(226, aData2Skill, (const char *)&unk_6761E0);
    sub_5E0EE0(227, aData2Skill, aACO_smd_0);
    sub_5E0EE0(239, aData2Skill, (const char *)&unk_6761A8);
    sub_5E0EE0(243, aData2Skill, (const char *)&unk_676198);
    sub_5E0EE0(244, aData2Skill, (const char *)&unk_676178);
    sub_5E0EE0(245, aData2Skill, (const char *)&unk_676168);
    sub_5E0EE0(268, aData2Skill, aTCV_smd);
    sub_5E0EE0(248, aData2Skill, (const char *)&unk_67614C);
    sub_5E0EE0(249, aData2Skill, (const char *)&unk_676140);
    sub_5E0EE0(250, aData2Skill, (const char *)&unk_676134);
    sub_5E0EE0(251, aData2Skill, (const char *)&unk_676128);
    sub_5E0EE0(252, aData2Skill, (const char *)&unk_67611C);
    sub_5E0EE0(253, aData2Skill, (const char *)&unk_676110);
    sub_5E0EE0(254, aData2Skill, (const char *)&unk_676104);
    sub_5E0EE0(255, aData2Skill, (const char *)&unk_6760F8);
    sub_5E0EE0(256, aData2Skill, aMagic2_smd);
    sub_5E0EE0(257, aData2Skill, aMagic3_smd);
    if ( !byte_6719C8 )
      sub_5E0EE0(258, aData2Skill, aPiercing_smd);
  }
  byte_6719C8 = 1;
  sub_5E10E0(193, (int)aDataSkill, aIce, 1);
  sub_5E10E0(202, (int)aDataSkill, aIce, 2);
  sub_5E10E0(194, (int)aDataSkill, aFire, 1);
  sub_5E10E0(195, (int)aDataSkill, aPoison, 1);
  v0 = 200;
  do
  {
    sub_5E10E0(v0, (int)aDataSkill, aStone, v0 - 199);
    ++v0;
  }
  while ( v0 - 200 < 2 );
  sub_5E10E0(203, (int)aDataSkill, aCircle, 1);
  sub_5E10E0(204, (int)aDataSkill, aCircle, 2);
  sub_5E10E0(205, (int)aDataSkill, aMagic, 1);
  sub_5E10E0(206, (int)aDataSkill, aMagic, 2);
  sub_5E10E0(207, (int)aDataSkill, aStorm, 1);
  sub_5E10E0(208, (int)aDataSkill, aLaser, 1);
  v1 = 209;
  do
  {
    sub_5E10E0(v1, (int)aDataSkill, aSkeleton_0, v1 - 208);
    ++v1;
  }
  while ( v1 - 209 < 3 );
  sub_5E10E0(212, (int)aDataSkill, (const char *)&off_676078, 1);
  v2 = 213;
  do
  {
    sub_5E10E0(v2, (int)aDataSkill, aBone, v2 - 212);
    ++v2;
  }
  while ( v2 - 213 < 2 );
  v3 = 215;
  do
  {
    sub_5E10E0(v3, (int)aDataSkill, aSnow, v3 - 214);
    ++v3;
  }
  while ( v3 - 215 < 3 );
  sub_5E10E0(198, (int)aDataSkill, aRider, 1);
  if ( !byte_6719C8 )
    sub_5E0EE0(269, aData2Skill, (const char *)&unk_675F88);

  sub_5E10E0(269, (int)aDataSkill, aRider, 2);
  sub_5E10E0(191, (int)aDataSkill, aDarkhorse, -1);
  sub_5E10E0(192, (int)aDataSkill, aDarkspirit, -1);
  sub_60F900((int)aSkillDkthreebo, 1718, 9729, 10497, 0, 1);
  sub_5E10E0(197, (int)aDataSkill, aHellgate, -1);
  sub_5E10E0(219, (int)aDataSkill, aArrow, 1);

  _asm 
  {
	  MOV EDX,DWORD PTR DS:[0x56FA650]
	  MOV EAX,DWORD PTR DS:[EDX+0x9D2C]
	  MOV BYTE PTR DS:[EAX+0xA],0
	  MOV ECX,DWORD PTR DS:[0x56FA650]
	  MOV EDX,DWORD PTR DS:[ECX+0x9D2C]
	  MOV DWORD PTR DS:[EDX+4],0x3E19999A
  }
 
  sub_5E10E0(220, (int)aDataSkill, aArrowsteel, 1);
  sub_5E10E0(221, (int)aDataSkill, aArrowthunder, 1);
  sub_5E10E0(222, (int)aDataSkill, aArrowlaser, 1);
  sub_5E10E0(223, (int)aDataSkill, aArrowv, 1);
  sub_5E10E0(224, (int)aDataSkill, aArrowsaw, 1);
  sub_5E10E0(225, (int)aDataSkill, aArrownature, 1);
  sub_5E0CA0(262, aSkill, 10497, 9728, 1);
  sub_5E10E0(262, (int)aDataSkill, aProtect, 2);
  sub_5E0CA0(268, aSkill, 10497, 9728, 1);
  sub_5E10E0(268, (int)aDataSkill, aRidingspear, 1);
  sub_5E10E0(228, (int)aDataSkill, aProtect, 1);
  v4 = 229;

  do
  {
    sub_5E10E0(v4, (int)aDataSkill, aBigstone, v4 - 228);
    ++v4;
  }
  while ( v4 - 229 < 2 );

  sub_5E10E0(236, (int)aDataSkill, aMagiccircle, 1);
  sub_5E10E0(227, (int)aDataSkill, aArrowwing, 1);
  sub_5E10E0(226, (int)aDataSkill, aArrowbomb, 1);
  sub_5E10E0(239, (int)aDataSkill, aBall, 1);

  _asm //*dword_56FA650->pbyteDCEC = 0;
  {
	  MOV EDX,DWORD PTR DS:[0x56FA650]
	  MOV EAX,DWORD PTR DS:[EDX+0xBEA4]
	  MOV DWORD PTR DS:[EAX+4],0x3F000000
  }

  sub_5E10E0(243, (int)aDataSkill, aBlast, 1);
  sub_5E10E0(244, (int)aDataSkill, aInferno, 1);
  sub_5E10E0(245, (int)aDataSkill, aArrowdouble, 1);
  sub_5E10E0(267, (int)aDataSkill, aKcross, -1);
  sub_5E10E0(270, (int)aDataSkill, aCarow, -1);
  sub_5E10E0(271, (int)aDataSkill, aCombo, -1);
  sub_5E10E0(265, (int)aDataObject12, aGate, 1);
  sub_5E10E0(266, (int)aDataObject12, aGate, 2);
  sub_5E10E0(263, (int)aDataObject12, aStonecoffin, 1);
  sub_5E10E0(264, (int)aDataObject12, aStonecoffin, 2);
  sub_5E0BE0(105);
  v5 = 0;

  do
  {
    sub_5E0CA0(266, aMonster_0, 10497, 9728, 1);
    sub_5E0CA0(v5++ + 263, aMonster_0, 10497, 9728, 1);
  }
  while ( v5 < 2 );

  sub_5E10E0(272, (int)aDataSkill, aAirforce, -1);
  sub_5E10E0(273, (int)aDataSkill, aM_waves, -1);
  sub_5E10E0(274, (int)aDataSkill, aM_piercing, -1);
  sub_5E10E0(275, (int)aDataSkill, aPierpart, -1);
  sub_5E10E0(276, (int)aDataSkill, aDarklordskill, -1);
  sub_5E10E0(277, (int)aDataSkill, aGroundstone, -1);

  _asm //*dword_56FA650->pbyteDCEC = 0;
  {
	  MOV EDX,DWORD PTR DS:[0x56FA650]
	  MOV EAX,DWORD PTR DS:[EDX+0xDCEC]
	  MOV BYTE PTR DS:[EAX],0
  }

  sub_5E10E0(278, (int)aDataSkill, aGroundstone2, -1);

  _asm //*dword_56FA650->pbyteDDB8 = 0;
  {
	  MOV ECX,DWORD PTR DS:[0x056FA650]
	  MOV EDX,DWORD PTR DS:[ECX+0xDDB8]
	  MOV BYTE PTR DS:[EDX],0
  }

  sub_5E10E0(279, (int)aDataSkill, aSeamanfx, -1);
  sub_5E10E0(280, (int)aDataSkill, aSkull, -1);
  sub_5E10E0(281, (int)aDataSkill, aLacearrow, -1);
  sub_5E0BE0(312);
  sub_5E0CA0(281, aItem, 10496, 9728, 1);

  if(! byte_6719C8 )
  {
    sub_5E0EE0(248, aData2Skill, (const char *)&unk_67614C);
    sub_5E0EE0(249, aData2Skill, (const char *)&unk_676140);
    sub_5E0EE0(250, aData2Skill, (const char *)&unk_676134);
    sub_5E0EE0(252, aData2Skill, (const char *)&unk_67611C);
    sub_5E0EE0(254, aData2Skill, (const char *)&unk_676104);
    sub_5E0EE0(255, aData2Skill, (const char *)&unk_6760F8);
    sub_5E0EE0(256, aData2Skill, aMagic2_smd);
    sub_5E0EE0(257, aData2Skill, aMagic3_smd);
  }
  sub_5E10E0(248, (int)aDataSkill, aEarthquake, 1);
  sub_5E10E0(249, (int)aDataSkill, aEarthquake, 2);
  sub_5E10E0(250, (int)aDataSkill, aEarthquake, 3);
  sub_5E10E0(252, (int)aDataSkill, aEarthquake, 5);
  sub_5E10E0(254, (int)aDataSkill, aEarthquake, 7);
  sub_5E10E0(255, (int)aDataSkill, aEarthquake, 8);
  sub_5E10E0(256, (int)aDataSkill, aFlashing, -1);
  sub_5E10E0(257, (int)aDataSkill, aTail, -1);
  sub_5E10E0(251, (int)aDataSkill, aEarthquake, 4);
  sub_5E10E0(253, (int)aDataSkill, aEarthquake, 6);
  sub_5E10E0(258, (int)aDataSkill, aPiercing, -1);
  sub_5E10E0(260, (int)aDataSkill, aWaveforce, -1);
  sub_5E10E0(261, (int)aDataSkill, aBlizzard, -1);
  sub_5E10E0(294, (int)aDataSkill, "GI", -1);


  sub_5E10E0(295, (int)aDataSkill, aMusign, -1);

  sub_5E10E0(307, (int)aDataSkill, aGroundcrystal, -1);
  sub_5E10E0(308, (int)aDataSkill, aSkinshell, -1);
  sub_5E10E0(309, (int)aDataSkill, aManarune, -1);
  sub_5E10E0(310, (int)aDataSkill, aJavelin, -1);
  sub_5E10E0(311, (int)aDataSkill, aArrowimpact, -1);
  sub_5E10E0(312, (int)aDataSkill, aSwordforce, -1);

  sub_5E10E0(296, (int)aDataSkill, aFlybigstone1, -1);
  sub_5E10E0(297, (int)aDataSkill, aFlybigstone2, -1);
  sub_5E10E0(298, (int)aDataSkill, aFlysmallstone1, -1);
  sub_5E10E0(299, (int)aDataSkill, aFlysmallstone2, -1);
  sub_5E10E0(300, (int)aDataSkill, aWallstone1, -1);
  sub_5E10E0(301, (int)aDataSkill, aWallstone2, -1);
  sub_5E10E0(302, (int)aDataSkill, aGatepart1, -1);
  sub_5E10E0(303, (int)aDataSkill, aGatepart2, -1);
  sub_5E10E0(304, (int)aDataSkill, aGatepart3, -1);
  sub_5E10E0(305, (int)aDataSkill, aAurora, -1);
  sub_5E10E0(306, (int)aDataSkill, aTowergateplane, -1);
  sub_5E10E0(313, (int)aDataSkill, aGolem_stone, -1);
  sub_5E10E0(314, (int)aDataSkill, aBossrock, -1);
  sub_5E10E0(315, (int)aDataSkill, aBossrocklight, -1);

  sub_5E10E0(316, (int)aDataSkill, "vip", -1);

  sub_5E10E0(317, (int)aDataSkill, aProtectguild, -1);
  sub_5E0BE0(952);
  sub_5E0CA0(191, aSkill, 10497, 9728, 1);
  sub_5E0CA0(192, aSkill, 10497, 9728, 1);
  sub_5E0CA0(197, aSkill, 10497, 9728, 1);
  sub_5E0CA0(269, aSkill, 10497, 9728, 1);
  sub_5E0CA0(248, aSkill, 10497, 9728, 1);
  sub_5E0CA0(249, aSkill, 10497, 9728, 1);
  sub_5E0CA0(250, aSkill, 10497, 9728, 1);
  sub_5E0CA0(252, aSkill, 10497, 9728, 1);
  sub_5E0CA0(254, aSkill, 10497, 9728, 1);
  sub_5E0CA0(255, aSkill, 10497, 9728, 1);
  sub_5E0CA0(256, aSkill, 10497, 9728, 1);
  sub_5E0CA0(257, aSkill, 10497, 9728, 1);
  sub_5E0CA0(260, aSkill, 10497, 9728, 1);
  sub_5E0CA0(261, aSkill, 10497, 9728, 1);
  sub_5E0CA0(270, aSkill, 10497, 9728, 1);
  sub_5E0CA0(271, aSkill, 10497, 9728, 1);
  sub_5E0CA0(272, aSkill, 10496, 9728, 1);
  sub_5E0CA0(273, aSkill, 10497, 9728, 1);
  sub_5E0CA0(274, aSkill, 10497, 9728, 1);
  sub_5E0CA0(275, aSkill, 10497, 9728, 1);
  sub_5E0CA0(277, aSkill, 10497, 9728, 1);
  sub_5E0CA0(278, aSkill, 10497, 9728, 1);
  sub_5E0CA0(279, aSkill, 10496, 9728, 1);
  sub_5E0CA0(280, aSkill, 10496, 9728, 1);
  // flags replaced
  sub_5E0CA0(294, aSkill, 10497, 9728, 1);
  sub_5E0CA0(295, aSkill, 10497, 9728, 1);

  sub_5E0CA0(296, aNpc, 10497, 9728, 1);
  sub_5E0CA0(297, aSkill, 10497, 9728, 1);
  sub_5E0CA0(298, aSkill, 10497, 9728, 1);
  sub_5E0CA0(299, aSkill, 10497, 9728, 1);
  sub_5E0CA0(300, aObject31, 10497, 9728, 1);
  sub_5E0CA0(301, aObject31, 10497, 9728, 1);
  sub_5E0CA0(302, aMonster_0, 10497, 9728, 1);
  sub_5E0CA0(303, aMonster_0, 10497, 9728, 1);
  sub_5E0CA0(304, aMonster_0, 10497, 9728, 1);
  sub_5E0CA0(305, aMonster_0, 10497, 9728, 1);
  sub_5E0CA0(306, aSkill, 10497, 9728, 1);
  sub_5E0CA0(313, aMonster_0, 10497, 9728, 1);
  sub_5E0CA0(314, aSkill, 10497, 9728, 1);
  sub_5E0CA0(315, aSkill, 10497, 9728, 1);
  // GI
  sub_5E0CA0(316, aSkill, 10497, 9728, 1);

  sub_5E0CA0(308, aEffect, 10497, 9728, 1);
  sub_5E0CA0(317, aItem, 10497, 9728, 1);

  v6 = 190;

  do
  {
    if ( v6 == 258 )
      sub_5E0CA0(258, aSkill, 10497, 9728, 1);
    else
      sub_5E0CA0(v6, aSkill, 10497, 9728, 1);
    ++v6;
  }
  while ( v6 < 318 );

  sub_60FD90((int)aSkillFlower1_t, 1544, 9728, 10496, 0, 1);
  sub_60FD90((int)aSkillFlower2_t, 1545, 9728, 10496, 0, 1);
  sub_60FD90((int)aSkillFlower3_t, 1546, 9728, 10496, 0, 1);
}
//-----------------------------------------------------------------------------------------------------------