// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
//				coded by MaThreeX					  //
// ================================================== //

#ifndef MARRYSYSTEM_H
#define MARRYSYSTEM_H

//#define IAMarrySystem = "..\\..\\DataServerX\\MarrySystem.ini"
#define MAXMARRYITEM 20
enum eGender {MAN, WOMAN};
#define MARRY_TIME		180000
class cMarry
{
public:	
	cMarry();
	~cMarry();  
	
	
	void Init(); 
	void StartMarriage			(int aIndex, int tIndex);
	void EndMarriageFalse		();
	void EndMarriageTrue		();
	void DivorceMarrige			(int aIndex);
	void TrackMarry				(int aIndex, int tIndex);

	char M_NAME1[11];
	char M_NAME2[11];
	bool MARRIAGE_STARTED;
	int NpcUse;

	/*For marry*/ 
	struct SItems
	{
		unsigned long Serial;
		int Group;
		short Index; // GROP *512 + TYPE
		int Type;	
		int Lvl;
		int Skill;
		int Luck;
		int Opt;
		int Exc;
		int Num;
	};

	struct sMarry
	{
		int MarrySystemEnabled;
		int MarryHomoSexual;
		int MarryCostZen;
		int MarryCostCredits;
		int MarryMinLvl;
		int MarryTrace;
		int MarryTraceLvl;
		int IsMarry;
		int MarryOnline;
		int NumWitnesses;

		int IsDivorce;
		int DivorceNpcNum;
		int DivorceCostZen;
		int DivorceCostCredits;
		int DivorceMinLvl;

		int TakeItemsForMarry;
		int TakeItemsForDivorce;
								
		SItems MarryItems[MAXMARRYITEM];	
		SItems DivorceItems[MAXMARRYITEM];	
						  
		bool MarrySerial[76];
		bool DivorceSerial[76];

	}Config; 
private:
	bool CheckLocation (int aIndex, int tIndex);
	bool CheckGender(int aIndex, int tIndex); 
	bool CheckMarryItem(int Index);
	void CheckMarryItemSerial(int Index, BYTE Serial);
	bool CheckMarryCost(int aIndex, int tIndex);
	void ResetConfigs();


};
extern cMarry g_MarrySystem;

#endif