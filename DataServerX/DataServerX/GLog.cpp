// ---------------------------------------------------------------------------
// # Optimized by:	S@nek[BoR];
// # Last Update:	19.07.2010 03-22;
// # Status:		Completed;
// ---------------------------------------------------------------------------

#include "stdafx.h"
#include "GLog.h"
// ---------------------------------------------------------------------------

TLog	g_Log;
// ---------------------------------------------------------------------------

bool IsFile(char * filename)
{
	bool result		= false;
	// ----
	FILE * fp	= fopen(filename, "rb");
	// ----
	if ( fp != NULL )
	{
		fclose(fp);
		// ----
		result		= true;
	}
	// ----
	return result;
}
// ---------------------------------------------------------------------------

DWORD CalcFileSize(char * szFilePath)
{
	// Function calculation size of the file in byte;
	DWORD dwLength	= 0;
	HANDLE hFile	= NULL;
	// ----
	hFile = CreateFile(szFilePath, 0, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	// ----
	if ( hFile != INVALID_HANDLE_VALUE )
	{
		dwLength	= GetFileSize(hFile, 0);
		// ----
		CloseHandle(hFile);
	}
	// ----
	return dwLength;
}
// ---------------------------------------------------------------------------

TLog::TLog()
{
    GCS_Create();
}
// ---------------------------------------------------------------------------

TLog::~TLog()
{
    if(m_bWriteLog == true)
    {
        SaveDataInFile();
    }
    // ----
    GCS_Delete();
}
// ---------------------------------------------------------------------------

void TLog::LogInit(bool bLogPrint, const char * szLogsPath)
{
	memset(m_szLogsPath, 0x00, sizeof(m_szLogsPath));
	memcpy(m_szLogsPath, szLogsPath, strlen(szLogsPath));
	// ----
    SetMaxLogKeepBufferSize(65536 / 2);
    SetMaxLogFileSize(256);
    // ----
    m_iCurrentLine				= 0;
    // ----
    m_dwLogKeepSize				= 0;
    // ----
    m_dwMaxLogBufferSize		= 1024;
    // ----
    m_HFont		= CreateFont(15, 6,
                             0, 0, FW_DONTCARE, 0, 0, 0,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                             CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
                             DEFAULT_PITCH | FF_DONTCARE, "Tahoma");
    // ----
    m_StatusColors.StandByBG	= CreateSolidBrush(RGB(0x00, 0x00, 0x00)); // Black;
    m_StatusColors.StandByText	= RGB(0xFF, 0xFF, 0xFF); // White;
    // ----
    m_bWriteLog			= bLogPrint;
    // ----
    int iStrSize		= sizeof(m_LogStr[0]);
    // ----
    for(int i = 0; i < LOG_TEXT_LINE; ++i)
    {
        memset(& m_LogStr[i], 0, iStrSize);
    }
    // ----
    if(m_bWriteLog == true)
    {
        LogDataSet_Start();
    }
}
// ---------------------------------------------------------------------------

void TLog::LogDataSet_Start()
{
    char szTemp[255];
    memset(szTemp, 0, sizeof(szTemp));
    // ----
    tm * today;
    time_t ltime;
    // ----
    time(& ltime);
    today				= localtime(& ltime);
    // ----
    today->tm_year		= today->tm_year + 1900;
    // ----
    m_CurDate.Day		= today->tm_mday;
    m_CurDate.Month		= today->tm_mon + 1;
    m_CurDate.Year		= today->tm_year;
    // ----
    m_StartDate.Day		= m_CurDate.Day;
    m_StartDate.Month	= m_CurDate.Month;
    m_StartDate.Year	= m_CurDate.Year;
    // ----
    /*
    wsprintf(szTemp, "Log\\%02d%02d%02d_%s.html",
    	LogMYear, LogMonth, LogMDay, & szServerName);
    */
    // ----
    wsprintf(szTemp, "%s\\%02d.%02d.%04d.html",
             m_szLogsPath, m_StartDate.Day, m_StartDate.Month, m_StartDate.Year);
    // ----
    CreateDirectory(m_szLogsPath, NULL);
    // ----
    if(IsFile(szTemp) == true)
    {
        for(int i = 2; ; ++i)
        {
            memset(szTemp, 0, sizeof(szTemp));
            // ----
            wsprintf(szTemp, "%s\\%02d.%02d.%04d_start-%d.html",
                     m_szLogsPath, m_StartDate.Day, m_StartDate.Month, m_StartDate.Year, i);
            // ----
            if(IsFile(szTemp) == false)
            {
                break;
            }
        }
    }
    // ----
    memset(m_szLogFileName_Orig, 0, sizeof(m_szLogFileName_Orig));
    memcpy(m_szLogFileName_Orig, szTemp, strlen(szTemp) - 4);
    // ----
    strcpy(m_szLogFileName, szTemp);
}
// ---------------------------------------------------------------------------

void TLog::LogDataSet_Check()
{
    tm * today;
    time_t ltime;
    // ----
    time(& ltime);
    today			= localtime(& ltime);
    // ----
    today->tm_year	= today->tm_year + 1900;
    // ----
    int iYear		= today->tm_year;
    int iMonth		= today->tm_mon + 1;
    int iDay		= today->tm_mday;
    // ----
    char szTemp[255];
    memset(szTemp, 0, sizeof(szTemp));
    // ----
    if((iDay == m_CurDate.Day) &&
            (iMonth == m_CurDate.Month) &&
            (iYear == m_CurDate.Year))
    {
        DWORD dwFileSize	= CalcFileSize(m_szLogFileName);
        // ----
        if(dwFileSize < m_dwMaxLogFileSize)
        {
            return;
        }
        // ----
        CreateDirectory("D:\\LOGS\\DataServerX", NULL);
        // ----
        for(int i = 1; ; ++i)
        {
            memset(szTemp, 0, sizeof(szTemp));
            // ----
            wsprintf(szTemp, "%s_part-i.html",
                     m_szLogFileName_Orig, i);
            // ----
            if(IsFile(szTemp) == false)
            {
                break;
            }
        }
    }
    else
    {
        m_CurDate.Day		= iDay;
        m_CurDate.Month		= iMonth;
        m_CurDate.Year		= iYear;
        // ----
        CreateDirectory("D:\\LOGS\\DataServerX", NULL);
        // ----
        wsprintf(szTemp, "D:\\LOGS\\DataServerX\\%02d.%02d.%04d_-_%02d.%02d.%04d.html",
                 m_StartDate.Day, m_StartDate.Month, m_StartDate.Year,
                 m_CurDate.Day, m_CurDate.Month, m_CurDate.Year);
    }
    // ----
    memset(m_szLogFileName_Orig, 0, sizeof(m_szLogFileName_Orig));
    memcpy(m_szLogFileName_Orig, szTemp, strlen(szTemp) - 4);
    // ----
    strcpy(m_szLogFileName, szTemp);
}
// ---------------------------------------------------------------------------

void TLog::LogTextClear()
{
    GCS_Lock();
    // ----
    int iStrSize	= sizeof(m_LogStr[0]);
    // ----
    for(int i = 0; i < LOG_TEXT_LINE; ++i)
    {
        memset(& m_LogStr[i], 0, iStrSize);
    }
    // ----
    GCS_UnLock();
}
// ---------------------------------------------------------------------------

bool TLog::LogDateChange()
{
    bool result			= false;
    // ----
    tm * today;
    time_t ltime;
    // ----
    time(& ltime);
    // ----
    today			= localtime(& ltime);
    today->tm_year	= today->tm_year + 1900;
    today->tm_mon	= today->tm_mon + 1;
    // ----
    if(today->tm_mday <= m_CurDate.Day)
    {
        if(today->tm_mon <= m_CurDate.Month)
        {
            if(today->tm_year <= m_CurDate.Year)
            {
                return result;
            }
        }
    }
    // ----
    GCS_Lock();
    // ----
    LogDataSet_Check();
    // ----
    GCS_UnLock();
    // ----
    result			= true;
    // ----
    return result;
}
// ---------------------------------------------------------------------------

void TLog::LogTextAdd(TColor::T tColor, char * szMsg, int iLen)
{
    if(iLen >= LOG_TEXT_LENGTH)
    {
        iLen			= LOG_TEXT_LENGTH - 1;
    }
    // ----
    m_iCurrentLine++;
    // ----
    if(m_iCurrentLine >= LOG_TEXT_LINE)
    {
        m_iCurrentLine		= 0;
    }
    // ----
    memcpy(m_LogStr[m_iCurrentLine].Text, szMsg, iLen);
    // ----
    m_LogStr[m_iCurrentLine].Text[iLen]	= '\0';
    m_LogStr[m_iCurrentLine].Lenght		= iLen;
    m_LogStr[m_iCurrentLine].Color		= tColor; // Phew;
}
// ---------------------------------------------------------------------------

void TLog::MsgBox(const char * szlog, ...)
{
    char szBuffer[512];
    memset(szBuffer, 0, sizeof(szBuffer));
    // ----
    va_list pArguments;
    // ----
    va_start(pArguments, szlog);
    vsprintf(szBuffer, szlog, pArguments);
    va_end(pArguments);
    // ----
    MessageBox(NULL, szBuffer, "error", MB_OK | MB_APPLMODAL);
}
// ---------------------------------------------------------------------------

int TMsgBox(UINT uType, char * szCaption, char * szlog, ...)
{
    char szBuffer[512];
    memset(szBuffer, 0, sizeof(szBuffer));
    // ----
    va_list pArguments;
    // ----
    va_start(pArguments, szlog);
    vsprintf(szBuffer, szlog, pArguments);
    va_end(pArguments);
    // ----
    return MessageBox(NULL, szBuffer, szCaption, uType);
}
// ---------------------------------------------------------------------------

void TLog::AddMSB(BYTE btStatus, const char * szModuleName, const char * szFunctionName,
                  const char * szLog, ...)
{
    GCS_Lock();
    // ----
    memset(m_szLogBufTemp, 0, m_dwMaxLogBufferSize);
    // ----
    va_start(m_lpArguments, szLog);
    m_iLogBufTempSize	= vsprintf(m_szLogBufTemp, szLog, m_lpArguments);
    va_end(m_lpArguments);
    // ----
    tm * today;
    time_t ltime;
    // ----
    time(& ltime);
    today			= localtime(& ltime);
    // ----
    m_iLogBufTempSize	= sprintf(m_szLogBufTempTime, "[%.8s][%d][%s][%s][%s]\0",
                                  asctime(today) + 11, btStatus, szModuleName, szFunctionName, m_szLogBufTemp);
    // ----
	LogTextAdd(TColor::Firebrick, m_szLogBufTempTime, m_iLogBufTempSize);
    // ----
	memset(m_szLogBufTemp, 0 , sizeof(m_szLogBufTemp));
	// ----
	m_iLogBufTempSize += sprintf(m_szLogBufTemp, "<font color='#%02X%02X%02X'> %s </font><br>", GetRValue(TColor::Firebrick), GetGValue(TColor::Firebrick), GetBValue(TColor::Firebrick), m_szLogBufTempTime);
	// ----
    if(m_bWriteLog == true)
    {
        if((m_dwLogKeepSize + m_iLogBufTempSize) >= m_dwMaxLogKeepBufferSize)
        {
            SaveDataInFile();
        }
        // ----
        LogDataSet_Check();
        // ----
        m_dwLogKeepSize		+= sprintf(& m_szBufferKeep[m_dwLogKeepSize],
                                       "%s\n", m_szLogBufTemp);
    }
    // ----
    MessageBox(NULL, m_szLogBufTempTime, "[WARNING]", MB_OK);
    // ----
    GCS_UnLock();
}
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// # Write Log Function;
// ---------------------------------------------------------------------------

void TLog::Add(BYTE btStatus, const char * szModuleName, const char * szFunctionName,
              const char * szLog, ...)
{
    GCS_Lock();
    // ----
    memset(m_szLogBufTemp, 0, m_dwMaxLogBufferSize);
    // ----
    va_start(m_lpArguments, szLog);
    m_iLogBufTempSize	= vsprintf(m_szLogBufTemp, szLog, m_lpArguments);
    va_end(m_lpArguments);
    // ----
    tm * today;
    time_t ltime;
    // ----
    time(& ltime);
    today			= localtime(& ltime);
    // ----
    // # Check FunctionName for ::
    BYTE i			= 0;
    BYTE btLen		= (BYTE)strlen(szFunctionName);
    // ----
    for(i = btLen - 1; i > 1; i--)
    {
        if((szFunctionName[i] == ':') && (szFunctionName[i - 1] == ':'))
        {
            break;
        }
    }
    // ----
    if(i == 1)
    {
        m_iLogBufTempSize	= sprintf(m_szLogBufTempTime, "[%.8s][%d][%s][%s][%s]\0",
                                      asctime(today) + 11, btStatus, szModuleName, szFunctionName, m_szLogBufTemp);
    }
    else
    {
        memset(m_szFunctionName, 0, sizeof(m_szFunctionName));
        // ----
        memcpy(m_szFunctionName, & szFunctionName[i + 1], btLen - i - 1);
        // ----
        m_iLogBufTempSize	= sprintf(m_szLogBufTempTime, "[%.8s][%d][%s][%s][%s]",
                                      asctime(today) + 11, btStatus, szModuleName, m_szFunctionName, m_szLogBufTemp);
    }
    // ----
    LogTextAdd(TColor::White, m_szLogBufTempTime, m_iLogBufTempSize);
    // ----
	memset(m_szLogBufTemp, 0 , sizeof(m_szLogBufTemp));
	// ----
	m_iLogBufTempSize += sprintf(m_szLogBufTemp, "<font color='#%02X%02X%02X'> %s </font><br>", GetRValue(TColor::White), GetGValue(TColor::White), GetBValue(TColor::White), m_szLogBufTempTime);
	// ----
    if(m_bWriteLog == true)
    {
        if((m_dwLogKeepSize + m_iLogBufTempSize) >= m_dwMaxLogKeepBufferSize)
        {
            SaveDataInFile();
        }
        // ----
        LogDataSet_Check();
        // ----
        m_dwLogKeepSize		+= sprintf(& m_szBufferKeep[m_dwLogKeepSize],
                                       "%s\n", m_szLogBufTemp);
    }
    // ----
    GCS_UnLock();
}
// ---------------------------------------------------------------------------

void TLog::AddC(BYTE btStatus, const char * szModuleName, const char * szFunctionName,
                TColor::T tColor, const char * szLog, ...)
{
    GCS_Lock();
    // ----
    memset(m_szLogBufTemp, 0, m_dwMaxLogBufferSize);
    // ----
    va_start(m_lpArguments, szLog);
    m_iLogBufTempSize	= vsprintf(m_szLogBufTemp, szLog, m_lpArguments);
    va_end(m_lpArguments);
    // ----
    tm * today;
    time_t ltime;
    // ----
    time(& ltime);
    today			= localtime(& ltime);
    // ----
    // # Check FunctionName for ::
    BYTE i			= 0;
    BYTE btLen		= (BYTE)strlen(szFunctionName);
    // ----
    for(i = btLen - 1; i > 1; i--)
    {
        if((szFunctionName[i] == ':') && (szFunctionName[i - 1] == ':'))
        {
            break;
        }
    }
    // ----
    if(i == 1)
    {
        m_iLogBufTempSize	= sprintf(m_szLogBufTempTime, "[%.8s][%d][%s][%s][%s]",
                                      asctime(today) + 11, btStatus, szModuleName, szFunctionName, m_szLogBufTemp);
    }
    else
    {
        memset(m_szFunctionName, 0, sizeof(m_szFunctionName));
        // ----
        memcpy(m_szFunctionName, & szFunctionName[i + 1], btLen - i - 1);
        // ----
        m_iLogBufTempSize	= sprintf(m_szLogBufTempTime, "[%.8s][%d][%s][%s][%s]",
                                      asctime(today) + 11, btStatus, szModuleName, m_szFunctionName, m_szLogBufTemp);
    }
    // ----
    LogTextAdd(tColor, m_szLogBufTempTime, m_iLogBufTempSize);
    // ----
	memset(m_szLogBufTemp, 0 , sizeof(m_szLogBufTemp));
	// ----
	m_iLogBufTempSize += sprintf(m_szLogBufTemp, "<font color='#%02X%02X%02X'> %s </font><br>", GetRValue(tColor), GetGValue(tColor), GetBValue(tColor), m_szLogBufTempTime);
	// ----
    if(m_bWriteLog == true)
    {
        if((m_dwLogKeepSize + m_iLogBufTempSize) >= m_dwMaxLogKeepBufferSize)
        {
            SaveDataInFile();
        }
        // ----
        LogDataSet_Check();
        // ----
		try
		{
			m_dwLogKeepSize		+= sprintf(& m_szBufferKeep[m_dwLogKeepSize],
                                       "%s\n", m_szLogBufTemp);
		}
		catch(...)
		{
		}
    }
    // ----
    GCS_UnLock();
}
// ---------------------------------------------------------------------------

void TLog::AddF(BYTE btStatus, char * szModuleName, char * szFunctionName,
                char * szLog, ...)
{
    if(m_bWriteLog == false)
    {
        return;
    }
    // ----
    GCS_Lock();
    // ----
    memset(m_szLogBufTemp, 0, m_dwMaxLogBufferSize);
    // ----
    va_start(m_lpArguments, szLog);
    m_iLogBufTempSize	= vsprintf(m_szLogBufTemp, szLog, m_lpArguments);
    va_end(m_lpArguments);
    // ----
    tm * today;
    time_t ltime;
    // ----
    time(& ltime);
    today			= localtime(& ltime);
    // ----
    // # Check FunctionName for ::
    BYTE i			= 0;
    BYTE btLen		= (BYTE)strlen(szFunctionName);
    // ----
    for(i = btLen - 1; i > 1; i--)
    {
        if((szFunctionName[i] == ':') && (szFunctionName[i - 1] == ':'))
        {
            break;
        }
    }
    // ----
    if(i == 1)
    {
        m_iLogBufTempSize	= sprintf(m_szLogBufTempTime, "[%.8s][%d][%s][%s][%s]\0",
                                      asctime(today) + 11, btStatus, szModuleName, szFunctionName, m_szLogBufTemp);
    }
    else
    {
        memset(m_szFunctionName, 0, sizeof(m_szFunctionName));
        // ----
        memcpy(m_szFunctionName, & szFunctionName[i + 1], btLen - i - 1);
        // ----
        m_iLogBufTempSize	= sprintf(m_szLogBufTempTime, "[%.8s][%d][%s][%s][%s]\0",
                                      asctime(today) + 11, btStatus, szModuleName, m_szFunctionName, m_szLogBufTemp);
    }
    // ----
    if((m_dwLogKeepSize + m_iLogBufTempSize) >= m_dwMaxLogKeepBufferSize)
    {
        SaveDataInFile();
    }
    // ----
    LogDataSet_Check();
    // ----
    m_dwLogKeepSize		+= sprintf(& m_szBufferKeep[m_dwLogKeepSize],
                                   "%s\n", m_szLogBufTempTime);
    // ----
    GCS_UnLock();
}
// ---------------------------------------------------------------------------

void TLog::AddHeadHex(BYTE btStatus, const char * szModuleName, const char * szFunctionName,
                      const char * szText, LPBYTE lpBuf, int iSize)
{
    if(m_bWriteLog == false)
    {
        return;
    }
    // ----
    tm * today;
    time_t ltime;
    // ----
    time(& ltime);
    today		= localtime(&ltime);
    // ----
    GCS_Lock();
    // ----
    LogDataSet_Check();
    // ----
    m_iLogBufTempSize	= sprintf(m_szLogBufTempTime, "[%.8s][%s][%d] Buffer: (",
                                  asctime(today) + 11, szText, iSize);
    // ----
    for(int n = 0; n < iSize; n++)
    {
        m_iLogBufTempSize	+= sprintf(& m_szLogBufTempTime[m_iLogBufTempSize],
                                       "%02X ", lpBuf[n]);
    }
    // ----
    m_iLogBufTempSize	+= sprintf(& m_szLogBufTempTime[m_iLogBufTempSize], ")");
    // ----
	memset(m_szLogBufTemp, 0 , sizeof(m_szLogBufTemp));
	// ----
	m_iLogBufTempSize += sprintf(m_szLogBufTemp, "<font color='#%02X%02X%02X'> %s </font><br>", GetRValue(TColor::White), GetGValue(TColor::White), GetBValue(TColor::White), m_szLogBufTempTime);
	// ----
    if(m_bWriteLog == true)
    {
        if((m_dwLogKeepSize + m_iLogBufTempSize) >= m_dwMaxLogKeepBufferSize)
        {
            SaveDataInFile();
        }
        // ----
        LogDataSet_Check();
        // ----
        m_dwLogKeepSize		+= sprintf(& m_szBufferKeep[m_dwLogKeepSize],
                                       "%s\n", m_szLogBufTemp);
    }
    // ----
    GCS_UnLock();
}
// ---------------------------------------------------------------------------

void TLog::LogTextPaint(HWND hWnd)
{
    HDC hDC				= GetDC(hWnd);
    // ----
    RECT m_Rect;
    // ----
    GetClientRect(hWnd, & m_Rect);
    // ----
    m_Rect.top		= 15;
    // ----
    FillRect(hDC, & m_Rect, m_StatusColors.StandByBG);
    // ----
    int iCorX		= 5;
    int iCorY		= m_Rect.top + 5;
    // ----
    int iLinesPerSize	= (m_Rect.bottom - 5 - iCorY) / 15;
    // ----
    int n			= m_iCurrentLine;
    // ----
    int iStrLen		= 0;
    // ----
    iCorY			+= (iLinesPerSize * 15);
    // ----
    while(iLinesPerSize-- > 0)
    {
        iStrLen		= m_LogStr[n].Lenght;
        // ----
        if(iStrLen < 1)
        {
            break;
        }
        // ----
        SetBkMode(hDC, TRANSPARENT);
        // ----
        SelectObject(hDC, m_HFont);
        // ----
        SetTextColor(hDC, m_LogStr[n].Color);
        // ----
        iCorY		-= 15;
        // ----
        TextOut(hDC, iCorX, iCorY, m_LogStr[n].Text, iStrLen);
        // ----
        n--;
        // ----
        if(n < 0)
        {
            n		= LOG_TEXT_LINE - 1;
        }
    }
    // ----
    ReleaseDC(hWnd, hDC);
}
// ---------------------------------------------------------------------------

void TLog::LogAddOfCloseProgram()
{
    GCS_Lock();
    // ----
    memset(m_szLogBufTempTime, 0, m_dwMaxLogBufferSize);
    // ----
    tm * today;
    time_t ltime;
    // ----
    time(& ltime);
    today			= localtime(& ltime);
    // ----
    m_iLogBufTempSize	= sprintf(m_szLogBufTempTime, "[%.8s][%s]<br>",
                                  asctime(today) + 11,
                                  "################################################################################");
    m_iLogBufTempSize	+= sprintf(& m_szLogBufTempTime[m_iLogBufTempSize], "[%.8s][%s]<br>",
                                   asctime(today) + 11,
                                   "################################################################################");
    m_iLogBufTempSize	+= sprintf(& m_szLogBufTempTime[m_iLogBufTempSize], "[%.8s][%s]<br>",
                                   asctime(today) + 11,
                                   "############################ End Of Work - WM_CLOSE ############################");
    m_iLogBufTempSize	+= sprintf(& m_szLogBufTempTime[m_iLogBufTempSize], "[%.8s][%s]<br>",
                                   asctime(today) + 11,
                                   "################################################################################");
    m_iLogBufTempSize	+= sprintf(& m_szLogBufTempTime[m_iLogBufTempSize], "[%.8s][%s]<br>",
                                   asctime(today) + 11,
                                   "################################################################################");
    // ----
	m_iLogBufTempSize	+= sprintf(& m_szLogBufTempTime[m_iLogBufTempSize], "</body></html>");
	// ----
    if(m_bWriteLog == true)
    {
        if((m_dwLogKeepSize + m_iLogBufTempSize) >= m_dwMaxLogKeepBufferSize)
        {
            SaveDataInFile();
        }
        // ----
        LogDataSet_Check();
        // ----
        m_dwLogKeepSize		+= sprintf(& m_szBufferKeep[m_dwLogKeepSize],
                                       "%s\n", m_szLogBufTempTime);
        // ----
        SaveDataInFile();
    }
    // ----
    GCS_UnLock();
}
// ---------------------------------------------------------------------------




void TLog::SaveDataInFile()
{
    if(m_dwLogKeepSize < 1)
    {
        return;
    }
	if((m_fLog = fopen(m_szLogFileName, "a+")) != NULL)
    {
		if(ftell(m_fLog) == 0)
		{
			fprintf(m_fLog, "\
				<html>\n\
				<body>\n\
				<head>\n\
				<title>%s</title>\n\
				<style>\n\
				body {\n\
				font-size : 15px;\n\
				color:white;\n\
				background-color:black;\n\
				font-family:lucida console;\n\
				}\n\
				</style>\n\
				</head>"
				, m_szLogFileName);
		}
		// ----
        fprintf(m_fLog, m_szBufferKeep);
        // ----
        fclose(m_fLog);
        // ----
        m_dwLogKeepSize				= 0;
        // ----
        memset(m_szBufferKeep, 0, sizeof(m_szBufferKeep));
    }
}
// ---------------------------------------------------------------------------

void TLog::SaveDataInFileExternal()
{
    GCS_Lock();
    // ----
    if(m_dwLogKeepSize > 0)
    {
        if((m_fLog = fopen(m_szLogFileName, "a+")) != NULL)
        {
			if(ftell(m_fLog) == 0)
			{
				fprintf(m_fLog, "<html><body bgcolor='black'>");
			}
            fprintf(m_fLog, m_szBufferKeep);
            // ----
            fclose(m_fLog);
            // ----
            m_dwLogKeepSize				= 0;
            // ----
            memset(m_szBufferKeep, 0, sizeof(m_szBufferKeep));
        }
    }
    // ----
    GCS_UnLock();
}
// ---------------------------------------------------------------------------



