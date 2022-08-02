//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef LOGTOFILE_H
#define LOGTOFILE_H
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define c_s CRITICAL_SECTION
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CLogToFile
{
public:
	CLogToFile(const char* LogFileName, const char * LogDirectoryName, BOOL bWithDate);
	~CLogToFile();
	// ----
	void __cdecl	Output(const char * fmt, ...);
	// ----
	void			setCode(UINT Code);
private:
	FILE*	m_fLogFile;					
	// ----
	char	m_szLogFileName		[260];
	char	m_szLogDirectoryName[260];
	char	m_cBUFFER			[65536];
	// ----
	BOOL	m_bWithDate;
	// ----
	c_s		m_critLogToFile; 
	// ----
	UINT	m_nGSCode;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

extern CLogToFile	g_GmsLog;
extern CLogToFile	g_MailLog;
extern CLogToFile	g_HackLog;
extern CLogToFile	g_ChatLog;
extern CLogToFile	g_ChatWhispLog;
extern CLogToFile	g_ChatWhispLogGM;
extern CLogToFile	g_NewDataServerLog;
extern CLogToFile	g_EventLog;
extern CLogToFile	g_CreateItemLog;
extern CLogToFile	g_TradeLog;
extern CLogToFile	g_ShopLog;
extern CLogToFile	g_ResetLog;
extern CLogToFile	g_CoinShopLog;
extern CLogToFile	g_ProcessesLog;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef GS_99_60T 
extern CLogToFile	g_KillerLog; 
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif /* LOGTOFILE_H */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------