#ifndef LOGPROC_H
#define LOGPROC_H
// ---------------------------------------------------------------------------

#define LOG_TEXT_LINE	120
#define LOG_TEXT_LENGTH	300
// ---------------------------------------------------------------------------

#include "TColor.h"
#include <time.h>
#include <stdlib.h>
#include <string>
#include <boost/thread/mutex.hpp>
// ---------------------------------------------------------------------------

typedef struct
{
    int Day;
    int Month;
    int Year;
} CTLDATE;
// ---------------------------------------------------------------------------

typedef struct
{
    char		Text[LOG_TEXT_LENGTH];
    USHORT		Lenght;
    TColor::T	Color;
} CTLVISIBLESTRUCT;
// ---------------------------------------------------------------------------

typedef struct
{
    HBRUSH					StandByBG;
    COLORREF				StandByText;
} STUATS_COLORS_INFO;
// ---------------------------------------------------------------------------

class TLog
{
    private:
        CTLVISIBLESTRUCT		m_LogStr[LOG_TEXT_LINE];
        // ----
        HFONT					m_HFont;
        STUATS_COLORS_INFO		m_StatusColors;
        // ----
        char					m_szLogBufTemp[1024];
        char					m_szLogBufTempTime[1024];
        // ----
        char					m_szBufferKeep[65536];
        DWORD					m_dwLogKeepSize;
        DWORD					m_dwMaxLogKeepBufferSize;
        // ----
        char					m_szFunctionName[255];
        // ----
        int						m_iCurrentLine; // Current Line of Log;
        FILE 		*			m_fLog; // File Variable for Log;
        // ----
		char					m_szLogsPath[1024];
        char					m_szLogFileName[255];
        char					m_szLogFileName_Orig[255];
        // ----
        int						m_iLogBufTempSize;
        va_list					m_lpArguments;
        // ----
        DWORD					m_dwMaxLogBufferSize;
        DWORD					m_dwMaxLogFileSize;
        // ----
		boost::mutex			m_LogCriticalSection;
        // ----
        CTLDATE					m_StartDate;
        CTLDATE					m_CurDate;
        // ----
        bool					m_bWriteLog;
        // ----
        void LogDataSet_Start();
        void LogDataSet_Check();
        // ----
        void LogTextAdd(TColor::T tColor, char * szMsg, int iLen);
        // ----
        void GCS_Create()
        {
            //InitializeCriticalSection(& m_LogCriticalSection);
        }
        void GCS_Lock()
        {
			m_LogCriticalSection.lock();
        }
        void GCS_UnLock()
        {
			m_LogCriticalSection.unlock();
        }
        void GCS_Delete()
        {
            //DeleteCriticalSection(& m_LogCriticalSection);
        }

    public:
        TLog();
        virtual ~TLog();
        // ----
        void LogInit(bool bLogPrint, const char * szLogPath);
        // ----
        void LogTextClear();
        bool LogDateChange();
        // ----
        void Add(BYTE btStatus, const char * szModuleName, const char * szFunctionName,
                const char * szLog, ...);
        void AddC(BYTE btStatus,  const char * szModuleName, const char * szFunctionName,
                  TColor::T tColor, const char * szLog, ...);
        void AddF(BYTE btStatus, char * szModuleName, char * szFunctionName,
                  char * szLog, ...);
        void AddHeadHex(BYTE btStatus, const char * szModuleName, const char * szFunctionName,
                        const char * szText, LPBYTE lpBuf, int iSize);
        void LogTextPaint(HWND hWnd);
        // ----
        void MsgBox(const char * szlog, ...);
        void AddMSB(BYTE btStatus, const char * szModuleName, const char * szFunctionName,
                    const char * szLog, ...);
        // ----
        void LogAddOfCloseProgram();
        // ----
        void SetMaxLogKeepBufferSize(DWORD dwMaxSize)
        {
            GCS_Lock();
            // ----
            m_dwMaxLogKeepBufferSize	= dwMaxSize;
            // ----
            GCS_UnLock();
        };
        // ----
        void SetMaxLogFileSize(USHORT usMaxMBSize)
        {
            GCS_Lock();
            // ----
            m_dwMaxLogFileSize		= (DWORD)usMaxMBSize * (DWORD)(1024 * 1024); // 'n' MBytes;
            // ----
            GCS_UnLock();
        };
        // ----
        void SaveDataInFile();
        // ----
        void SaveDataInFileExternal();
};
// ---------------------------------------------------------------------------

int TMsgBox(UINT uType, char * szCaption, char * szlog, ...);
// ---------------------------------------------------------------------------

extern TLog			g_Log;
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------


