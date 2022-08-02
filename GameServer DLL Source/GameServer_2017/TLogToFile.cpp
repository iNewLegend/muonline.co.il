#include "stdafx.h"
#include "TLogToFile.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CLogToFile	g_GmsLog			("GmsLog",				"d:\\logs\\GmsLog",						true);
CLogToFile	g_MailLog			("MailLog",				"d:\\logs\\MailLog",					true);
CLogToFile  g_ChatLog			("ChatLog",				"d:\\logs\\ChatLog",					true);
CLogToFile	g_ChatWhispLog		("WhispLog",			"d:\\logs\\PMLog",						true);
CLogToFile	g_ChatWhispLogGM	("WhispLogGM",			"d:\\logs\\PMLogGM",					true);
CLogToFile	g_NewDataServerLog	("NewDataServerLog",	"d:\\logs\\NewDataServerLog",			true);
CLogToFile	g_EventLog			("EventLog",			"d:\\logs\\EventLog",					true);
CLogToFile	g_CreateItemLog		("CreateItemLog",		"d:\\logs\\CreateItemLog",				true);
CLogToFile	g_TradeLog			("TradeLog",			"d:\\logs\\TradeLog",					true);
CLogToFile	g_ShopLog			("ShopLog",				"d:\\logs\\TradeAndShopLog",			true);
CLogToFile	g_ResetLog			("ResetLog",			"d:\\logs\\ResetLog",					true);
CLogToFile	g_CoinShopLog		("CoinShopLog",			"d:\\logs\\CoinShopLog",				true);
CLogToFile	g_ProcessesLog		("ProcessesLog",		"d:\\logs\\ProcessesLog",				true);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef GS_99_60T 
CLogToFile	g_KillerLog		("KillerLog",	"d:\\logs\\KillerLog",		true);
CLogToFile	g_HackLog		("HackLog",		"d:\\logs\\HackLogSige",	true);
#else
CLogToFile	g_HackLog		("HackLog",		"d:\\logs\\HackLog",		true);
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CLogToFile::CLogToFile(const char * LogFileName, const char * LogDirectoryName, BOOL bWithDate)
{
	m_nGSCode = 99;
	// ----
	if(strcmp(LogFileName, "") == 0)
	{
		strcpy(m_szLogFileName, "LOGDATA");
	}
	else
	{
		strcpy(m_szLogFileName, LogFileName);
	}
	// ----
	if(!strcmp(LogDirectoryName, ""))
	{
		strcpy(m_szLogDirectoryName, "LOG");
	}
	else
	{
		strcpy(m_szLogDirectoryName, LogDirectoryName);
	}
	// ----
	m_bWithDate  = bWithDate;	
	// ----
	CreateDirectory(LogDirectoryName, NULL);
	// ----
	InitializeCriticalSection(&m_critLogToFile);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CLogToFile::~CLogToFile()
{
	DeleteCriticalSection(&m_critLogToFile);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CLogToFile::setCode(UINT Code)
{
	m_nGSCode = Code;
	// ----
	Output("//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
	Output("//# Log START (GS_START) ------------------------------------------------------------------------------------------------");
	Output("//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CLogToFile::Output(const char * fmt, ...)
{
	static va_list argptr;
	// ----
	static int		iChrWritten;
	static char	szLogFileName[260];
	// ----
	memset(szLogFileName, 0, sizeof(szLogFileName));
	// ----
	static SYSTEMTIME strSystime;
	// ----
	EnterCriticalSection(&m_critLogToFile);
	// ----
	va_start(argptr, fmt);
	iChrWritten = vsprintf(m_cBUFFER, fmt, argptr);
	va_end(argptr);
	// ----
	GetLocalTime(&strSystime);
	// ----
	wsprintf(szLogFileName, "%s\\%04d-%02d-%02d_%s.txt", & m_szLogDirectoryName[0],
		strSystime.wYear, strSystime.wMonth, strSystime.wDay, & m_szLogFileName [0]);
	// ----
	if((m_fLogFile = fopen(szLogFileName, "a+"))==0)	//flipe +'0
	{
		LeaveCriticalSection(&m_critLogToFile);	
	}
	else
	{
		if(m_bWithDate ==0)
		{
			fprintf(m_fLogFile, "%s\n", m_cBUFFER);
		}
		else
		{
			if(strSystime.wSecond < 10)
			{
				fprintf(m_fLogFile, "[GS%d][%d:%d:0%d] : %s\n", m_nGSCode ,strSystime.wHour, strSystime.wMinute, strSystime.wSecond, m_cBUFFER);
			}
			else
			{
				fprintf(m_fLogFile, "[GS%d][%d:%d:%d] : %s\n", m_nGSCode ,strSystime.wHour, strSystime.wMinute, strSystime.wSecond, m_cBUFFER);
			}
		}
		// ----
		fclose(m_fLogFile);
		// ----
		LeaveCriticalSection(&m_critLogToFile);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------