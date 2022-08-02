// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
//				coded by MaThreeX & PsychoGod		  //
// ================================================== //

#include "StdAfx.h"
#include "TMarrySystem.h"

#include "User.h"
#include "Chat.h"
#include "TConfig.h"
#include "TGameServer.h"
#include "TMessages.h"
#include "TBotSystem.h"
#include "TLogToFile.h"
#include "Item.h"
cMarry g_MarrySystem;

#define IAMarrySystem "..\\..\\DataServerX\\MarrySystem.ini"

char M_NAME1[11] = "";
char M_NAME2[11] = "";
bool MARRIAGE_STARTED = false;
//#TODO
// 1. ׁקטעûגאםטו ךמםפטדמג 100%
// 2. ־עקטסעךא ןונולוםםûץ מע לףסמנא 100%
// 3. ֿנמגונךא ןמכא 100%
// 4. ֿנמגונךא סגטהועוכוי ט חאבטנאםטו באבכא 100%
// 5. ׁקטעûגאםטו טח באחû ט חאםוסוםטו ג ןונולוםםף‏ 100%
// 6. Êמלאםהû הכÿ ֶוםאעûץ 100%
// 7. ֱמםףסû זוםאעûל 100%
// 8. ׁגאהüבא 100%


cMarry::cMarry()
{
}

cMarry::~cMarry()
{							   
}		

void cMarry::ResetConfigs()
{
	Config.MarrySystemEnabled = 0;
	Config.MarryHomoSexual = 0;
	Config.MarryCostZen = 0;
	Config.MarryCostCredits = 0;
	Config.MarryMinLvl = 0;
	Config.MarryTrace = 0;
	Config.MarryTraceLvl = 0;
	Config.MarryOnline = 0;
	Config.NumWitnesses = 0;

	Config.IsDivorce = 0;
	Config.DivorceNpcNum = 0;
	Config.DivorceCostZen = 0;
	Config.DivorceCostCredits = 0;
	Config.DivorceMinLvl = 0;

	Config.TakeItemsForMarry = 0;
//	Config.TakeItemsForDivorce = 0;

	for (int i=0; i < MAXMARRYITEM; i++)
	{ 
		Config.MarryItems[i].Num = 0;
		 
		Config.MarryItems[i].Group = 0;
			 
		Config.MarryItems[i].Type = 0;
			 
		Config.MarryItems[i].Lvl = 0;
			 
		Config.MarryItems[i].Luck = 0;
			 
		Config.MarryItems[i].Skill = 0;
			 
		Config.MarryItems[i].Opt = 0;
			 
		Config.MarryItems[i].Exc = 0;

		/*
		Config.DivorceItems[i].Num = 0;
		 
		Config.DivorceItems[i].Group = 0;
			 
		Config.DivorceItems[i].Type = 0;
			 
		Config.DivorceItems[i].Lvl = 0;
			 
		Config.DivorceItems[i].Luck = 0;
			 
		Config.DivorceItems[i].Skill = 0;
			 
		Config.DivorceItems[i].Opt = 0;
			 
		Config.DivorceItems[i].Exc = 0;
		*/
	}
}

void cMarry::Init()
{
	ResetConfigs();

	Config.MarrySystemEnabled		= g_Config.GetInt(0, 1,				1,		"MarrySystem",	"MarrySystemEnabled",			IAMarrySystem);
	if(!Config.MarrySystemEnabled)
		return;
	Config.MarryHomoSexual			= g_Config.GetInt(0, 1,				1,		"MarrySystem",	"MarryHomoSexual",				IAMarrySystem);
	Config.MarryCostZen				= g_Config.GetInt(0, 2000000000,	1000000,"MarrySystem",	"MarryCostZen",					IAMarrySystem);
	Config.MarryMinLvl				= g_Config.GetInt(0, 400,			0,		"MarrySystem",	"MarryMinLvl",					IAMarrySystem);
	Config.MarryTrace				= g_Config.GetInt(0, 1,				1,		"MarrySystem",	"MarryTrace",					IAMarrySystem);	   
	Config.MarryOnline				= g_Config.GetInt(0, 1,				1,		"MarrySystem",	"MarryOnline",					IAMarrySystem);
	Config.MarryTraceLvl			= g_Config.GetInt(1, 400,			200,	"MarrySystem",	"MarryTraceLvlReq",				IAMarrySystem); 
	Config.MarryCostCredits			= g_Config.GetInt(0, 400,			0,		"MarrySystem",	"MarryCostCredits",				IAMarrySystem);		
	Config.NumWitnesses				= g_Config.GetInt(0, 100,			2,		"MarrySystem",	"MarryNumWitnesses",			IAMarrySystem);
	
	Config.IsDivorce				= g_Config.GetInt(0, 2,				1,		"MarrySystem",	"DivorceEnabled",				IAMarrySystem);
	Config.DivorceCostZen			= g_Config.GetInt(0, 2000000000,	1000000,"MarrySystem",	"DivorceCostZen",				IAMarrySystem);
	Config.DivorceMinLvl			= g_Config.GetInt(0, 400,			0,		"MarrySystem",	"DivorceMinLvl",				IAMarrySystem);		
	Config.DivorceCostCredits		= g_Config.GetInt(0, 400,			0,		"MarrySystem",	"DivorceCostCredits",			IAMarrySystem);		
	Config.TakeItemsForMarry		= g_Config.GetInt(0, 20,			0,		"MarrySystem",	"TakeItemsForMarry",			IAMarrySystem);


	char Items[40];		
	if(Config.TakeItemsForMarry != 0)
	{
		for(int y = 0; y < Config.TakeItemsForMarry; y++)
		{							 				   											  
			wsprintf(Items, "Config.Item[%d].Num", y+1);
			Config.MarryItems[y].Num		= g_Config.GetInt(0, 20, 1, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Config.Item[%d].Index", y+1);
			Config.MarryItems[y].Group	= g_Config.GetInt(0, 15, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Config.Item[%d].Type", y+1);
			Config.MarryItems[y].Type	= g_Config.GetInt(0, 255, 0, "MarrySystem", Items, IAMarrySystem);  

			wsprintf(Items, "Config.Item[%d].Lvl", y+1);
			Config.MarryItems[y].Lvl		= g_Config.GetInt(0, 13, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Config.Item[%d].Luck", y+1);   
			Config.MarryItems[y].Luck	= g_Config.GetInt(0, 1, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Config.Item[%d].Skill", y+1);
			Config.MarryItems[y].Skill	= g_Config.GetInt(0, 1, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Config.Item[%d].Opt", y+1);
			Config.MarryItems[y].Opt		= g_Config.GetInt(0, 7, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Config.Item[%d].Exc", y+1);
			Config.MarryItems[y].Exc		= g_Config.GetInt(0, 63, 0, "MarrySystem", Items, IAMarrySystem);
		}
	}		   
	/*
	Config.TakeItemsForDivorce		= Configs.GetInt(0, 20,	2,	"MarrySystem",	"TakeItemsForDivorce",	IAMarrySystem);
	if(Config.TakeItemsForDivorce != 0)
	{
		for(int x = 0; x < Config.TakeItemsForDivorce; x++)
		{							 				   											  
			wsprintf(Items, "Divorce.Item[%d].Num", x+1);
			Config.DivorceItems[x].Num		= Configs.GetInt(0, 20, 1, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Divorce.Item[%d].Index", x+1);
			Config.DivorceItems[x].Group		= Configs.GetInt(0, 15, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Divorce.Item[%d].Type", x+1);
			Config.DivorceItems[x].Type		= Configs.GetInt(0, 255, 0, "MarrySystem", Items, IAMarrySystem);  

			wsprintf(Items, "Divorce.Item[%d].Lvl", x+1);
			Config.DivorceItems[x].Lvl		= Configs.GetInt(0, 13, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Divorce.Item[%d].Luck", x+1);   
			Config.DivorceItems[x].Luck		= Configs.GetInt(0, 1, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Divorce.Item[%d].Skill", x+1);
			Config.DivorceItems[x].Skill		= Configs.GetInt(0, 1, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Divorce.Item[%d].Opt", x+1);
			Config.DivorceItems[x].Opt		= Configs.GetInt(0, 7, 0, "MarrySystem", Items, IAMarrySystem);

			wsprintf(Items, "Divorce.Item[%d].Exc", x+1);
			Config.DivorceItems[x].Exc		= Configs.GetInt(0, 63, 0, "MarrySystem", Items, IAMarrySystem);
		}
	}*/
}

bool cMarry::CheckMarryCost(int aIndex, int tIndex)
{

	if(Config.MarryMinLvl > gObj[aIndex].Level)
	{			   
		//if(tObj == NULL)
			g_Msg.Msg(aIndex, "[Marriage] You don't have high lvl! Need %d more.", Config.MarryMinLvl - gObj[aIndex].Level);
			g_Msg.Msg(aIndex, "[Marriage] אתה לא ברמה המתאימה. חסר לך %d רמות", Config.MarryMinLvl - gObj[aIndex].Level);//PRIVAT
		/*else																			  
			Monster.NPCMessage(gObj->m_Index, tObj, "You don't have high lvl! Need %d more.", Config.MarryMinLvl - gObj->Level);
		*/
		return false;
	}
	if(Config.MarryMinLvl > gObj[tIndex].Level)
	{			   
		//if(tObj == NULL)
			g_Msg.Msg(tIndex, "[Marriage] You don't have high lvl! Need %d more.", Config.MarryMinLvl - gObj[tIndex].Level);
			g_Msg.Msg(tIndex, "[Marriage] אתה לא ברמה המתאימה. חסר לך %d רמות", Config.MarryMinLvl - gObj[tIndex].Level);//PRIVAT
			g_Msg.Msg(aIndex, "[Marriage] Your Partner Need %d Lvs more.", Config.MarryMinLvl - gObj[tIndex].Level);
			g_Msg.Msg(aIndex, "[Marriage] השותף לא ברמה המתאימה. חסר לשותף %d רמות", Config.MarryMinLvl - gObj[tIndex].Level);//PRIVAT
		/*else																			  
			Monster.NPCMessage(gObj->m_Index, tObj, "You don't have high lvl! Need %d more.", Config.MarryMinLvl - gObj->Level);
		*/
		return false;
	}
	if(Config.MarryCostZen > gObj[aIndex].Money)
	{			   
		//if(tObj == NULL)
			g_Msg.Msg(aIndex, "[Marriage] You don't have enough zen! Need %d more.", Config.MarryCostZen - gObj[aIndex].Money);	  //PRIVAT
			g_Msg.Msg(aIndex, "[Marriage] אין לך מספיק כסף. חסר עוד %d כסף", Config.MarryCostZen - gObj[aIndex].Money);	  //PRIVAT
		/*else																			  
			Monster.NPCMessage(gObj->m_Index, tObj, "You don't have enough zen! Need %d more.", Config.MarryCostZen - gObj->Money);		 
*/
		return false;
	}	
	if(Config.TakeItemsForMarry > 0)
	{
	 	if(CheckMarryItem(aIndex) == false)
		{
			//if(tObj == NULL)
				g_Msg.Msg(aIndex, "[Marriage] You don't have right items.");
				g_Msg.Msg(aIndex, "[Marriage] אין ברשותך את החפצים שהשרת דורש לחתונה");
			/*else
				Monster.NPCMessageLog(c_Blue ,t_COMMANDS, gObj, tObj, "You don't have right items. Check it one more time.");  
*/
			return false;
		} 
	}
	if(Config.NumWitnesses > 0)
	{
		int Num = 0;
	 	for(int i = OBJECT_START_INDEX; i <= OBJECT_MAX_INDEX; i++)
		{		
			if(i == aIndex || i == tIndex) continue;
			if(gObj[i].Connected < 3) continue;
			if(g_BotSystem.isThatBot(i)) continue;
			if(gObj[i].MapNumber != 2) continue;
			if(gObj[i].X < 204 || gObj[i].X > 214 || gObj[i].X == 209 || gObj[i].X == 210 || gObj[i].X == 205) continue;
			if(gObj[i].Y < 16 || gObj[i].Y > 23 || gObj[i].Y == 20 || gObj[i].Y == 22) continue;
			/*
		   
			if(gObj[i].Connected < 3 && !g_BotSystem.isThatBot(i)) continue; 	   
			if(gObj[aIndex].MapNumber != gObj[i].MapNumber) continue;	 		 
			*/
			Num++;
		}
		if((Num) < Config.NumWitnesses)
		{  
			g_Msg.Msg(aIndex, "[Marriage] You don't have at least %d witnesses.", Config.NumWitnesses);
			g_Msg.Msg(aIndex, "[Marriage] חסר לך %d אורחים לחתונה. סהכ דרושים %d", Config.NumWitnesses-Num,Config.NumWitnesses);
			g_Msg.Msg(aIndex, "[Marriage] (וודא שהם עומדים במקום הנכון (על הספסלים");
			if (RABBI_INDEX != -1)
				g_BotSystem.sendMessageFromBot(RABBI_INDEX, "You don't have at least %d witnesses.", Config.NumWitnesses);
			return false;
		}
	}
	if(Config.MarryCostZen > 0)
	{
		gObj[aIndex].Money -= Config.MarryCostZen;
		g_GS.GCMoneySend(aIndex, gObj[aIndex].Money);
	}						
	if(Config.MarryCostCredits > 0)
	{ 
		//PCPoint.UpdatePoints(gObj,Config.MarryCostPCPoint,MINUS,PCPOINT);
		g_Msg.Msg(aIndex, "[Marriage] You payed %d Credits", Config.MarryCostCredits); 
	}

	char Temp [1024] = {0};
	if(Config.TakeItemsForMarry > 0)
	{														  
	for ( BYTE i = 0 ; i < 76 ; i ++ )
		{
			if(Config.MarrySerial[i])
			{	
				int Type, Lv, Op1, Op2, Op3, NewOp, Index, Group;
				Index = gObj[aIndex].pInventory[i].m_Type;
				Lv = gObj[aIndex].pInventory[i].m_Level; 	  
				Op2 = gObj[aIndex].pInventory[i].m_Option2; 
				Op1 =gObj[aIndex].pInventory[i].m_Option1;
				Op3 =gObj[aIndex].pInventory[i].m_Option3;
				NewOp = gObj[aIndex].pInventory[i].m_NewOption;
				// ----
				g_GS.gObjInventoryDeleteItem (aIndex ,i );
				g_GS.GCInventoryItemDeleteSend (aIndex ,i  ,1);
				// ----
				Group = Index / 32;
				Type = Index - (Group*32);
				// ----
				sprintf(Temp, "In %d, Ty %d, Lv %d, Op1 %d, Op2 %d, Op3 %d New %d",Group, Type, Lv, Op1, Op2, Op3, NewOp);
				// ----
				g_CreateItemLog.Output(CREATE_ITEM_LOG_FORMAT_DEL,gObj[aIndex].AccountID, gObj[aIndex].Name,"Marry Del",gObj[aIndex].MapNumber,gObj[aIndex].X,gObj[aIndex].Y,Temp);
			}
		} 
	} 
	return true;
}

bool cMarry::CheckGender(int aIndex, int tIndex) //Returnes True if Gender check passed
{
	
	if((aIndex < OBJECT_START_INDEX) || (aIndex > OBJECT_MAX_INDEX))
		return false;
	if((tIndex < OBJECT_START_INDEX) || (tIndex > OBJECT_MAX_INDEX))
		return false;

	int aGender = MAN, tGender = MAN;
	switch(gObj[aIndex].DbClass)
	{			
	case 32:
	case 33:
		aGender = WOMAN;
	break;
	
	default:
		aGender = MAN;
	}

	switch(gObj[tIndex].DbClass)
	{			
	case 32:
	case 33: 
		tGender = WOMAN;						
		break;
	default:
		tGender = MAN;
	}

	if(tGender == aGender)
	{
		if(Config.MarryHomoSexual == 1)
		{
			if(tGender == MAN)
			{
			
				return true;
			}
			else
			{
				return true;
			}
		}
		else
		{
			g_Msg.Msg(aIndex, "[Marriage] We don't support untraditional weddings!!! Marriage canceled!!!");
			g_Msg.Msg(tIndex, "[Marriage] We don't support untraditional weddings!!! Marriage canceled!!!");
			g_Msg.Msg(aIndex, "[Marriage] אנחנו לא תומכים בחתונות של בני אותו המין. החתונה התבטלה!!!");
			g_Msg.Msg(tIndex, "[Marriage] אנחנו לא תומכים בחתונות של בני אותו המין. החתונה התבטלה!!!");
			if(RABBI_INDEX != -1)
				g_BotSystem.sendMessageFromBot(RABBI_INDEX, "We don't support untraditional weddings!!!");	  //AROUND*/
			return false;
		}
	} 
	return true;
}


bool cMarry::CheckMarryItem(int Index)
{	   
	int NumItem	= Config.TakeItemsForMarry;
	int NumSpesItem;

	int Num_Items = 0;
	int m_NumSpesItem[20];
	int x_NumItem = 0;

	for(int xo = 0; xo < 76; xo++)
		Config.MarrySerial[xo] = false;

	for(int x = 0; x < NumItem; x++)
	{		   			
		m_NumSpesItem[x] = 0;
		NumSpesItem = Config.MarryItems[x].Num;
	    x_NumItem += NumSpesItem;
			Config.MarryItems[x].Index = (Config.MarryItems[x].Group * 32 + Config.MarryItems[x].Type);   
			for(BYTE i = 12; i < 76 ; i ++ )
			{
				if(gObj[Index].pInventory[i].m_Type == Config.MarryItems[x].Index && 
					gObj[Index].pInventory[i].m_Level == Config.MarryItems[x].Lvl &&		  
					gObj[Index].pInventory[i].m_Option2 == Config.MarryItems[x].Luck &&
					gObj[Index].pInventory[i].m_Option1 == Config.MarryItems[x].Skill &&
					gObj[Index].pInventory[i].m_Option3 == Config.MarryItems[x].Opt &&
					gObj[Index].pInventory[i].m_NewOption == Config.MarryItems[x].Exc &&
					m_NumSpesItem[x] < NumSpesItem)
				{
					if(!Config.MarrySerial[i])
					{
						CheckMarryItemSerial(Index,i);
						m_NumSpesItem[x]++;
						Num_Items++;
					}
				}
			}							
	}
	if(Num_Items >= x_NumItem)
		return true;
	else
		return false;
}	  
	
void cMarry::CheckMarryItemSerial(int Index, BYTE Serial) 
{					
	unsigned long Ser = gObj[Index].pInventory[Serial].m_Number;
	for(BYTE i = 12; i < 76 ; i ++ )
		if(gObj[Index].pInventory[i].m_Number == Ser)
			Config.MarrySerial[i] = true;
}

bool cMarry::CheckLocation (int aIndex, int tIndex)
{
	bool bReturn = true;
	if((gObj[tIndex].X >= 204 && gObj[tIndex].X <= 214) && (gObj[tIndex].Y >= 13 && gObj[tIndex].Y <= 31))
	{
		g_Msg.Msg(tIndex, "@[Marriage] You Are In The Church. Get Out Before");
		g_Msg.Msg(tIndex, "@[Marriage] אתה כבר בתוך הכנסיה. צא החוצה");
		g_Msg.Msg(aIndex, "@[Marriage] Your Partner Is In The Church");
		g_Msg.Msg(aIndex, "@[Marriage] שותפך כבר בתוך הכנסיה.");
		bReturn = false;
	}

	if((gObj[aIndex].X >= 204 && gObj[aIndex].X <= 214) && (gObj[aIndex].Y >= 13 && gObj[aIndex].Y <= 31))
	{
		g_Msg.Msg(aIndex, "@[Marriage] You Are In The Church. Get Out Before");
		g_Msg.Msg(aIndex, "@[Marriage] אתה כבר בתוך הכנסיה. צא החוצה");
		g_Msg.Msg(tIndex, "@[Marriage] Your Partner Is In The Church");
		g_Msg.Msg(tIndex, "@[Marriage] שותפך כבר בתוך הכנסיה.");
		bReturn = false;
	}

	return bReturn;
}

unsigned long __stdcall TickMarriage(int Index)
{
	g_MarrySystem.NpcUse = -1;
	_NEW_OBJECT * nObject = & g_GS.nObject[NINDEX(Index)];
	// ----
	int i;
	bool answer = false;
	
	g_Msg.Msg(Index, "[Marriage] Write yes or no for answer. You have 30 Seconds.");	
	g_Msg.Msg(Index, "[Marriage] רשום כן או לא בשביל התשובה. יש לך 30 שניות");	
	for(i = 0; i < 150; i++)
	{
		if(g_MarrySystem.NpcUse == 0 || g_MarrySystem.NpcUse == 1) 
		{
			answer = true;
			break;
		}
		Sleep(100);			 								   
		
	}		
	
	if (!answer)
	{
	g_Msg.Msg(Index, "[Marriage] You have 15 sec more for answer...");
	for(i = 0; i < 50; i++)
	{
		if(g_MarrySystem.NpcUse == 0 || g_MarrySystem.NpcUse == 1) 
		{
			answer = true;
			break;
		}
		Sleep(100);			 							 
	}
	}

	if (!answer)
	{
	g_Msg.Msg(Index, "[Marriage] You have 10 sec more for answer...");
	for(i = 0; i < 50; i++)
	{
		Sleep(100);			 							 
		if(g_MarrySystem.NpcUse == 0 || g_MarrySystem.NpcUse == 1) 
		{
			answer = true;
			break;
		}
	}
	}

	if (!answer){
	g_Msg.Msg(Index, "[Marriage] You have 5 sec more for answer...");
	for(i = 0; i < 20; i++)
	{
		
		if(g_MarrySystem.NpcUse == 0 || g_MarrySystem.NpcUse == 1) 
		{
			answer = true;
			break;
		}
		Sleep(100);		
	}
	}

	if (!answer){
	g_Msg.Msg(Index, "[Marriage] You have 3 sec more for answer...");
	for(i = 0; i < 10; i++)
	{
				 							   
		if(g_MarrySystem.NpcUse == 0 || g_MarrySystem.NpcUse == 1) 
		{
			answer = true;
			break;
		}
		Sleep(100);	
	} 		
	}

	if (!answer)
	{
		g_Msg.Msg(Index, "[Marriage] You have 2 secs more for answer...");	
		for(i = 0; i < 10; i++)
		{
			if(g_MarrySystem.NpcUse == 0 || g_MarrySystem.NpcUse == 1) 
			{
				answer = true;
				break;
			}
			Sleep(100);		
		}
	}

	if (!answer)	
	{
	g_Msg.Msg(Index, "[Marriage] You have 1 sec more for answer...");
	for(i = 0; i < 10; i++)
	{
		if(g_MarrySystem.NpcUse == 0 || g_MarrySystem.NpcUse == 1) 
		{
			answer = true;
			break;
		}
		Sleep(100);		
	}
	}
					
	if (g_MarrySystem.NpcUse == 1)
		g_MarrySystem.EndMarriageTrue();
	else
		g_MarrySystem.EndMarriageFalse();
	return 1;
}		

void cMarry::EndMarriageFalse()
{	
	int aIndex = gObjGetIndexByName(g_MarrySystem.M_NAME1);
	int tIndex = gObjGetIndexByName(g_MarrySystem.M_NAME2);
	
	_NEW_OBJECT * nObject = & g_GS.nObject[NINDEX(aIndex)];
	_NEW_OBJECT * tnObject = & g_GS.nObject[NINDEX(tIndex)];

	if((aIndex >= OBJECT_START_INDEX) && (aIndex <= OBJECT_MAX_INDEX))
	{
		nObject->MarryType = 0;
		nObject->IsMarried = 0;
		g_Msg.Msg(aIndex, "Marriged cancled");
		g_Msg.Msg(aIndex, "הנישואים התבטלו");
		g_Msg.Msg(aIndex, "@הטבעת שלך נמצאת כעת על הרצפה מתחתיך");
		if(Config.TakeItemsForMarry != 0)
		{
			for(int y = 0; y < Config.TakeItemsForMarry; y++)
			{		
				int Type, Lv, Op1, Op2, Op3, NewOp, Group;
				char Temp [1024] = {0};
				// ----
				for (int i =0; i<Config.MarryItems[y].Num; i++)
				{
					Lv = Config.MarryItems[y].Lvl;	  
					Op2 = Config.MarryItems[y].Luck;;
					Op1 = Config.MarryItems[y].Skill;
					Op3 = Config.MarryItems[y].Opt;
					NewOp = Config.MarryItems[y].Exc;
					Group = Config.MarryItems[y].Group;
					Type = Config.MarryItems[y].Type;
					// ----
					sprintf(Temp, "In %d, Ty %d, Lv %d, Op1 %d, Op2 %d, Op3 %d New %d",Group, Type, Lv, Op1, Op2, Op3, NewOp);
					// ----
					g_GS.ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(Group, Type), Lv, 0xFF, Op1, Op2, Op3, aIndex, NewOp, 0);
					// ----
					g_CreateItemLog.Output(CREATE_ITEM_LOG_FORMAT_CREATE,gObj[aIndex].AccountID, gObj[aIndex].Name, "Marry Create", gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Temp);
				}
			}
		
		}

		if(Config.MarryCostZen > 0)
		{
			gObj[aIndex].Money += Config.MarryCostZen;
			g_GS.GCMoneySend(aIndex, gObj[aIndex].Money);
		}	
	}
	if((tIndex >= OBJECT_START_INDEX) && (tIndex <= OBJECT_MAX_INDEX))
	{
		tnObject->MarryType = 0;
		tnObject->IsMarried = 0;
		g_Msg.Msg(tIndex, "Marriged cancled");
		g_Msg.Msg(tIndex, "הנישואים התבטלו");
	}

	if (RABBI_INDEX != -1)
	{
		g_BotSystem.sendMessageFromBot(RABBI_INDEX, "%s didn't want to marry %s", g_MarrySystem.M_NAME2, g_MarrySystem.M_NAME1);
	}
	
	NpcUse = false;
	memcpy(g_MarrySystem.M_NAME1,			"",			sizeof(""));
	memcpy(g_MarrySystem.M_NAME2,			"",			sizeof(""));
	// ----
	g_MarrySystem.MARRIAGE_STARTED = false;
}

unsigned long __stdcall FireMarriage()
{
	int aIndex = gObjGetIndexByName(g_MarrySystem.M_NAME1);
	int tIndex = gObjGetIndexByName(g_MarrySystem.M_NAME2);

	if((aIndex < OBJECT_START_INDEX) || (aIndex > OBJECT_MAX_INDEX) || (tIndex < OBJECT_START_INDEX) || (tIndex > OBJECT_MAX_INDEX))
	{
		memcpy(M_NAME1,			"",			sizeof(""));
		memcpy(M_NAME2,			"",			sizeof(""));
		// ----
		MARRIAGE_STARTED = false;	
		if((aIndex < OBJECT_START_INDEX) || (aIndex > OBJECT_MAX_INDEX))
		{
			g_Msg.Msg(tIndex, "Your Marrige has cancled. Your Partner went offline");
			g_Msg.Msg(tIndex, "הנישואים בוטלו. השותף שלך התנתק/ה");
			g_MarrySystem.EndMarriageFalse();
		}
		if((tIndex < OBJECT_START_INDEX) || (tIndex > OBJECT_MAX_INDEX))
		{
			g_Msg.Msg(aIndex, "Your Marrige has cancled. Your Partner went offline");
			g_Msg.Msg(aIndex, "הנישואים בוטלו. השותף שלך התנתק/ה");
		}
		return 0;
	}
	_NEW_OBJECT * nObject = & g_GS.nObject[NINDEX(aIndex)];
	_NEW_OBJECT * tnObject = & g_GS.nObject[NINDEX(tIndex)];
	// ----
	PMSG_SERVERCMD ServerCmd;
	PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
	ServerCmd.CmdType = 0;
	for(int y = 0; y < 2; y++)
	{	
		ServerCmd.X = (BYTE)(gObj[aIndex].X);
		ServerCmd.Y = (BYTE)(gObj[aIndex].Y);	   
		g_GS.DataSend(aIndex, (LPBYTE)&ServerCmd, sizeof(ServerCmd));		
		g_GS.MsgSendV2((DWORD)& gObj[aIndex], (LPBYTE)&ServerCmd, sizeof(ServerCmd));
		// ----
		ServerCmd.X = (BYTE)gObj[tIndex].X;
		ServerCmd.Y = (BYTE)gObj[tIndex].Y;	   
		g_GS.DataSend(tIndex, (LPBYTE)&ServerCmd, sizeof(ServerCmd));		
		g_GS.MsgSendV2((DWORD)& gObj[tIndex], (LPBYTE)&ServerCmd, sizeof(ServerCmd));
	}
	// ----
	Sleep(3000);	  
	// ----
	FireworkOnTheScreen(aIndex);	 
	FireworkOnTheScreen(tIndex);
	Sleep(1000);
	// ----
	g_BotSystem.sendMessageFromBot(RABBI_INDEX, "Congratulations with the wedding %s and %s!", g_MarrySystem.M_NAME1, g_MarrySystem.M_NAME2);  
	// ----
	g_Msg.Msg(aIndex,"%s מזל טוב, התחתנת עם",g_MarrySystem.M_NAME2);
	g_Msg.Msg(tIndex,"%s מזל טוב, התחתנת עם",g_MarrySystem.M_NAME1);
	g_Msg.NoticeAll("Congratulations, %s and %s Got Married!",g_MarrySystem.M_NAME1,g_MarrySystem.M_NAME2);
	g_Msg.NoticeAll("התחתנו %s ו %s ,מזל טוב",g_MarrySystem.M_NAME1,g_MarrySystem.M_NAME2);
	// ----
	memcpy(nObject->MarryName,		gObj[tIndex].Name,		sizeof(gObj[tIndex].Name));
	memcpy(tnObject->MarryName,		gObj[aIndex].Name,		sizeof(gObj[aIndex].Name));
	// ----
	nObject->IsMarried = 1;
	tnObject->IsMarried = 1;	
	// ----
	GDMarryUpdate(gObj[aIndex].Name,  gObj[tIndex].Name, true);
	// ----
	g_MarrySystem.NpcUse = false;
	memcpy(g_MarrySystem.M_NAME1,			"",			sizeof(""));
	memcpy(g_MarrySystem.M_NAME2,			"",			sizeof(""));
	// ----
	g_MarrySystem.MARRIAGE_STARTED = false;		

	return 1;
}


void cMarry::EndMarriageTrue()
{	   					
	DWORD ThreadID;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FireMarriage, NULL, 0, &ThreadID);

	if (hThread == 0)
	{
		//Log.ConsoleOutPut(0, c_Red, t_NULL,"CreateThread() failed with error %d", GetLastError());
		return;
	}

	CloseHandle(hThread);
}

void cMarry::DivorceMarrige(int aIndex)
{
	_NEW_OBJECT * nObject = & g_GS.nObject[NINDEX(aIndex)];
	if(nObject->IsMarried == 0 )
	{														   
		g_Msg.Msg(aIndex, "[Divorce] You are not married!");
		g_Msg.Msg(aIndex, "[Divorce] אתה לא נשוי!");
		return;
	} 
	// ---- DSX UPDATE ----
	GDMarryUpdate(gObj[aIndex].Name, nObject->MarryName, 0);
	// ----
	int Index = gObjGetIndexByName(nObject->MarryName);
	// ----
	if((Index >= OBJECT_START_INDEX) && (Index <= OBJECT_MAX_INDEX))
	{														   
		g_Msg.Msg(aIndex, "[Divorce] Your ex. marriage is online.");
		g_Msg.Msg(aIndex, "[Divorce] השותף לשעבר מחובר");
		// ----
		_NEW_OBJECT * tnObject = & g_GS.nObject[NINDEX(Index)];
		// ----
		tnObject->IsMarried = 0;
		memcpy(tnObject->MarryName,		"",				sizeof(""));
		// ----
		g_Msg.Msg(Index, "[Divorce] You got divorced");
		g_Msg.Msg(Index, "[Divorce] התגרשת!");
	}
	else
		g_Msg.Msg(aIndex, "[Divorce] Your ex. marriage is offline.");

	// ----
	nObject->IsMarried = 0;	
	memcpy(nObject->MarryName,		"",				sizeof(""));
	// ----
	
	g_Msg.Msg(aIndex, "[Divorce] You Are Divorced Now!");
	g_Msg.Msg(aIndex, "[Divorce] אתה גרוש עכשיו!");

}

unsigned long __stdcall AskMarry(int* Index)
{	
	
	Sleep(5000); 
	if (RABBI_INDEX != -1)
	{
		g_BotSystem.sendMessageFromBot(RABBI_INDEX, "%s, Do you want to marry to %s?", gObj[Index[1]].Name, gObj[Index[0]].Name);
		g_Msg.Msg(Index[0], "~Rabi: %s, Do you want to marry to %s?", gObj[Index[1]].Name, gObj[Index[0]].Name);
		g_Msg.Msg(Index[0], "~Rabi: ?%s האם תרצה להתחתן עם ,%s", gObj[Index[0]].Name, gObj[Index[1]].Name);
		g_Msg.Msg(Index[1], "~Rabi: %s, Do you want to marry to %s?", gObj[Index[1]].Name, gObj[Index[0]].Name);
		g_Msg.Msg(Index[1], "~Rabi: ?%s האם תרצה להתחתן עם ,%s", gObj[Index[0]].Name, gObj[Index[1]].Name);
	}
	// ----
	DWORD ThreadID;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TickMarriage, (void*)Index[1], 0, &ThreadID);
	if (hThread == 0)
	{
		memcpy(g_MarrySystem.M_NAME1,			"",			sizeof(""));
		memcpy(g_MarrySystem.M_NAME2,			"",			sizeof(""));
		// ----
		g_MarrySystem.MARRIAGE_STARTED = false;
		//g_Msg.Msg(Index[0],"CreateThread() failed with error %d", GetLastError());
		return 1;
	}
	// ----
	CloseHandle(hThread); 
	return 1;
}

unsigned long __stdcall Move(int* Index)
{
	int aIndex, tIndex;
	aIndex = Index[0];
	tIndex = Index[1];
	
	// ----
	BYTE Map	= 2;
	BYTE X_Has	= 209;
	BYTE X_Wif	= 211;
	BYTE Y		= 14;
	// ----

	g_GS.gObjTeleport(aIndex, 0 , 1, 1);
	g_GS.gObjTeleport(tIndex, 0 , 1, 1);
	gObjCastRegen(aIndex, 0xFF);
	gObjCastRegen(tIndex, 0xFF);
	Sleep (1000);
	
	if (gObj[aIndex].DbClass == 32 || gObj[aIndex].DbClass == 33)
	{
		g_GS.gObjTeleport(aIndex, Map , X_Wif, Y);
		g_GS.gObjTeleport(tIndex, Map , X_Has, Y);
	}
	else
	{
		g_GS.gObjTeleport(aIndex, Map , X_Has, Y);
		g_GS.gObjTeleport(tIndex, Map , X_Wif, Y);
	}
	// ----
	gObjCastRegen(aIndex, 0xFF);
	gObjCastRegen(tIndex, 0xFF);
	// ----

	return 1;
}
void cMarry::StartMarriage(int aIndex, int tIndex)
{	 
	_NEW_OBJECT * nObject = & g_GS.nObject[FIXINDEX];
	_NEW_OBJECT * tObject = & g_GS.nObject[NINDEX(tIndex)];
	if (aIndex == tIndex)
		return;

	if ((aIndex < 0 || aIndex > OBJECT_MAX_INDEX-1))
		return;

	if ((tIndex < 0 || tIndex > OBJECT_MAX_INDEX-1)) 
		return; 
	// ----
	if(!gObjIsConnected(aIndex) && gObjIsConnected(tIndex))
		return;

	if(gObj[aIndex].m_PK_Level == 5 || gObj[aIndex].m_PK_Level == 6)
	{
		g_Msg.Msg(aIndex, "@[Marriage] You Are Murder");
		g_Msg.Msg(aIndex, "@[Marriage] אתה רוצח");
		g_Msg.Msg(tIndex, "@[Marriage] Your Partner Is Murder");
		g_Msg.Msg(tIndex, "@[Marriage] שותפך רוצח");
		return;
	}

	if(gObj[tIndex].m_PK_Level == 5 || gObj[tIndex].m_PK_Level == 6)
	{
		g_Msg.Msg(tIndex, "@[Marriage] You Are Murder");
		g_Msg.Msg(tIndex, "@[Marriage] אתה רוצח");
		g_Msg.Msg(aIndex, "@[Marriage] Your Partner Is Murder");
		g_Msg.Msg(aIndex, "@[Marriage] שותפך רוצח");
		return;
	}

	if (tObject->isMarryAllow == false)
	{
		g_Msg.Msg(aIndex, "@[Marriage] Your Partner Doesn't Avilable For Marry");
		g_Msg.Msg(aIndex, "@[Marriage] שותפך אינו/ה פנוי לנישואים (MarryOff) ");
		return;
	}

	DWORD dwCurTick = GetTickCount();
	if(nObject->dwPostTick != 0)
		if((dwCurTick - nObject->dwMarry) < MARRY_TIME)
		{
			g_Msg.Msg(aIndex, "@[TMarry] You Can Marry Every 3 Min");
			g_Msg.Msg(aIndex, "@[TMarry] אתה יכול להתחתן כל 3 דקות");
			return;
		}
	/*if (CheckLocation(aIndex, tIndex) == false)
		return;*/
	// ----
	if(nObject->IsMarried == 0 && tObject->IsMarried == 0 && MARRIAGE_STARTED == false)
	{	
		if(!CheckGender(aIndex,tIndex))
		{
			return;
		}
		if(!CheckMarryCost(aIndex, tIndex))
		{
			return;
		}
		
		DWORD ThreadID;
		g_MarrySystem.MARRIAGE_STARTED = true;
		int* pIndex = new int [2];
		pIndex[0] = aIndex;
		pIndex[1] = tIndex;
		// ----
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Move, (void*)(pIndex), 0, &ThreadID);
		if (hThread == 0)
		{
			return;
		}
		CloseHandle(hThread); 

		// ----
		memcpy(g_MarrySystem.M_NAME1,	 gObj[aIndex].Name, sizeof(gObj[aIndex].Name));
		memcpy(g_MarrySystem.M_NAME2,	 gObj[tIndex].Name, sizeof(gObj[tIndex].Name));
		// ----
		nObject->dwMarry = GetTickCount();
		// ----
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AskMarry, (void*)(pIndex), 0, &ThreadID);
		if (hThread == 0)
		{
			memcpy(g_MarrySystem.M_NAME1,			"",			sizeof(""));
			memcpy(g_MarrySystem.M_NAME2,			"",			sizeof(""));
			// ----
			g_MarrySystem.MARRIAGE_STARTED = false;
			//g_Msg.Msg(aIndex,"CreateThread() failed with error %d", GetLastError());
			return;
		}
		CloseHandle(hThread); 

	}		  
	else if(MARRIAGE_STARTED == true)
	{ 
		g_Msg.Msg(aIndex, "@[Marriage] There is already started Marriage");
		g_Msg.Msg(aIndex, "@[Marriage] Try again later please.");
		// ----
		g_Msg.Msg(aIndex, "@[Marriage] יש כבר חתמונה שמתקיימת");
		g_Msg.Msg(aIndex, "@[Marriage] נסה שוב מאוחר יותר");
		return;
	}
	else if(nObject->IsMarried == 1 || tObject->IsMarried == 1)
	{
		g_Msg.Msg(aIndex, "@[Marriage] You or Your Partner is Married already");
		g_Msg.Msg(aIndex, "@[Marriage] את/ה או שותפך כבר נשואים ");
		return;
	}
	else
	{
		g_Msg.Msg(aIndex, "@[Marriage] Unkown Error - please report (1)");
		g_Msg.Msg(aIndex, "@[Marriage] נסה להתנתק ולהתחבר שוב.");
		return;
	}
}	


void cMarry::TrackMarry(int aIndex, int tIndex)
{	 
	
	if (gObj[tIndex].MapNumber > 10 || gObj[tIndex].MapNumber == 9)
	{
		g_Msg.Msg(aIndex, "@[TMarry] Your marriage is inside event map, you cannot teleport");
		g_Msg.Msg(aIndex, "@[TMarry] אתה במפת איוונט, לא ניתן להשתגר");
		return;
	}
	if (gObj[aIndex].m_PK_Level == 5 || gObj[aIndex].m_PK_Level == 6)
	{
		g_Msg.Msg(aIndex, "@[TMarry] Your are murder");
		g_Msg.Msg(aIndex, "@[TMarry] אתה ברמת רוצח");
		return;
	}
	else if (gObj[tIndex].MapNumber != gObj[aIndex].MapNumber)
	{
		g_Msg.Msg(aIndex, "@[TMarry] Your marriage is not in your map, you need to be in the same map");
		g_Msg.Msg(aIndex, "@[TMarry] שותפך לא באותו מפה איתך");
		return;
	}
	if(Config.MarryTraceLvl > gObj[aIndex].Level)
	{
		g_Msg.Msg(aIndex, "@[TMarry] Your are not lv %d",Config.MarryTraceLvl);
		g_Msg.Msg(aIndex, "@[TMarry] %d אתה לא ברמה",Config.MarryTraceLvl);
		return;
	}
	/*_NEW_OBJECT * nObject = & g_GS.nObject[FIXINDEX];
	DWORD dwCurTick = GetTickCount();
	if(((dwCurTick - nObject->dwTrackMarry) > TRACK_MARRY) ||(nObject->dwPostTick == 0))
	{
		g_Msg.Msg(aIndex, "@[TMarry] Your Ccan Track Every 1 Min");
		g_Msg.Msg(aIndex, "@[TMarry] אתה יכול להשתגר כל דקה");
		//g_Msg.Msg(aIndex, "@[TMarry] שניות %d נשאר עוד",(TRACK_MARRY-(dwCurTick - nObject->dwTrackMarry))/1000);
		return;
	}*/
	g_Msg.Msg(aIndex, "@[TMarry] You successfully moved to %s!", gObj[tIndex].Name);
	g_Msg.Msg(tIndex, "@[TMarry] %s successfully moved to you!", gObj[aIndex].Name);
	// ----
	g_GS.gObjTeleport(aIndex, gObj[tIndex].MapNumber, (int)gObj[tIndex].X, (int)gObj[tIndex].Y);
	// ----
	gObjCastRegen(aIndex, 0xFF);
	gObjCastRegen(tIndex, 0xFF);
	// ----
	//nObject->dwPostTick = GetTickCount();
}