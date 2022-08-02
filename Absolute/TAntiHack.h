//-----------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------

#include "tlhelp32.h"
#include <list>
//-----------------------------------------------------------------------------------------------------------

#define MAX_DUMP_SIZE 64
//-----------------------------------------------------------------------------------------------------------

typedef struct
{
	char *		szOffset;
	char *		szMemoryDump;
} tagProcessMemoryFile, *lpTagProcessMemoryFile;
//-----------------------------------------------------------------------------------------------------------

typedef struct
{
	DWORD		dwOffset;
	BYTE		aMemoryDump[MAX_DUMP_SIZE];
	UINT		uIDumpLen;
	WORD		wID;
} tagProcessMemory, *lpTagProcessMemory;
//-----------------------------------------------------------------------------------------------------------

struct tagProcess
{
	unsigned __int64 uChecksum;
	std::string	name;

	inline bool operator<(const tagProcess& lhs)
	{
		return ((lhs.uChecksum < this->uChecksum));
	}

	bool operator==(const struct tagProcess& a) const
	{
		return (a.name == this->name && a.uChecksum == this->uChecksum);
	}
};
//-----------------------------------------------------------------------------------------------------------

#define PROCESS_MEMORY_LIST std::list	<tagProcessMemory>
#define PROCESSES_LIST		std::list	<tagProcess>
//-----------------------------------------------------------------------------------------------------------

#define SVOID static void CALLBACK
#define SBOOL static BOOL CALLBACK
//-----------------------------------------------------------------------------------------------------------

class TAntiHack
{
private:
	static tagProcessMemoryFile m_processMemoryFile[];
	// --
	PROCESS_MEMORY_LIST m_processMemoryList;
public:
	TAntiHack();
	~TAntiHack();
	// --
	PROCESSES_LIST GetProcesses();
	// --
	SBOOL	ScanWindowsProc(HWND hwnd, LPARAM lParam);
	void	ScanWindows();
	void	ScanProcess();
	void	Run();
};
//-----------------------------------------------------------------------------------------------------------
extern TAntiHack g_AntiHack;
//-----------------------------------------------------------------------------------------------------------