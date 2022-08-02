//-----------------------------------------------------------------------------------------------------------
#ifndef TDataBase_H
#define TDataBase_H
//-----------------------------------------------------------------------------------------------------------

#include <cstdio>
#include <sql.h>
#include <sqlext.h>
#include <string>
//-----------------------------------------------------------------------------------------------------------

#include "GLog.h"
//-----------------------------------------------------------------------------------------------------------

#define MAX_DB_TEXT_LEN	500
//-----------------------------------------------------------------------------------------------------------

enum STAFF
{
	MAXCOL			= 100,
	BLOBBATCH		= 10000,
	CQUERYNULL		= -100,
	CQUERYEOF		= -101,
	CQUERYNOCOL		= -102,
	CQUERYERROR		= -103
};
//-----------------------------------------------------------------------------------------------------------

class TDataBase
{
private:
	SQLLEN	 	m_AffectedRowCount;
	SQLRETURN	m_Return;
	// ----
	SQLHENV 	m_hEnv;
	SQLHDBC 	m_hDbc;
	SQLHSTMT	m_hStmt;	
	SQLSMALLINT m_nCol;
	// ----
	char		m_Col[MAXCOL][255];
	SQLCHAR		m_ColName[MAXCOL][50];
	SQLLEN		m_lCol[MAXCOL];
	// ----
	std::string	m_strHost;
	std::string	m_strUser;
	std::string	m_strPassword;
	std::string	m_strDataBase;
	std::string	m_strDnsName;
	// ----
	char		m_szTemp[MAX_DB_TEXT_LEN];
	SQLCHAR		m_szMsg[MAX_DB_TEXT_LEN];
	SQLCHAR		m_SqlState[MAX_DB_TEXT_LEN];
	// ----
	int			m_SQLErrorCount;
	SQLSMALLINT	m_MsgOutLen;
	SQLINTEGER	m_NativeError;
	// ----
	va_list		m_pArgs;
	// ----
public:
	TDataBase(void);
	~TDataBase(void);
	// ----
	//int			GetRowCount();
	bool		Connect(const char * szHost, const char * szDataBase, const char * szUser, const char * szPassword);
	bool		Connect(const char * szDnsName);
	bool		Reconnect();
	bool		Exec(BYTE btCode, const char * szModule, const char * szFunction, char * szQuery);
	bool		ExecFormat(BYTE btCode, const char * szModule, const char * szFunction, const char * szQuery, ...);
	int			FindCol(const char * szName);
	int			GetInt(int nCol);
	int			GetInt(const char *sCol);
	__int64		GetInt64(int nCol);
	__int64		GetInt64(const char *sCol);
	float		GetFloat(int nCol);
	float		GetFloat(const char *sCol);
	void		GetStr(int nCol, char *buf);
	void		GetStr(const char *sCol, char *buf);
	int			GetIntExec(char * szQuery);
	float		GetFloatExec(char * szQuery);
	bool		GetStrExec(char * szQuery, char * buf);
	int			GetAsBinary(LPSTR lpszStatement, LPBYTE OUT lpszReturnBuffer);
	void		SetAsBinary(LPTSTR lpszStatement, LPBYTE lpBinaryBuffer, SQLUINTEGER BinaryBufferSize);
	// ----
	SQLRETURN	inline Fetch(){ return SQLFetch(m_hStmt); };
	void		inline Clear(){ SQLCloseCursor(m_hStmt) ; SQLFreeStmt(m_hStmt, SQL_UNBIND); };
	// ----

	virtual	void OnError(const char * szMessage, ...)
	{
		va_start(m_pArgs, szMessage);
		vsprintf(m_szTemp, szMessage, m_pArgs);
		va_end(m_pArgs);
		// ----
		g_Log.AddC(-1, "TDataBase", __FUNCTION__, TColor::Red, (char*)szMessage);
	};

	virtual void OnMessage(const char * szMessage, ...)
	{
		va_start(m_pArgs, szMessage);
		vsprintf(m_szTemp, szMessage, m_pArgs);
		va_end(m_pArgs);
		// ----
		g_Log.AddC(-1, "TDataBase", __FUNCTION__, TColor::White, (char*)szMessage);
	};
	// ----
	void Diagnostic()
	{
		if(SQLGetDiagRec(SQL_HANDLE_STMT, m_hStmt, m_SQLErrorCount, m_SqlState, & m_NativeError, 
			m_szMsg, sizeof(m_szMsg), & m_MsgOutLen) != SQL_NO_DATA)
		{
			m_SQLErrorCount++;
			// ----
			memcpy(m_szTemp, m_szMsg , m_MsgOutLen);
			// ----
			OnError(m_szTemp);
		}
		else m_SQLErrorCount = 1;
		// ----
		if( strcmp((LPCTSTR)m_SqlState, "08S01") == 0 )
		{
			Reconnect();
		}
	};
	// ----
	void DiagnosticConn()
	{
		if(SQLGetDiagRec(SQL_HANDLE_DBC, m_hDbc, m_SQLErrorCount, m_SqlState, & m_NativeError, 
			m_szMsg, sizeof(m_szMsg), & m_MsgOutLen) != SQL_NO_DATA)
		{
			m_SQLErrorCount++;
			// ----
			memcpy(m_szTemp, m_szMsg , m_MsgOutLen);
			// ----
			OnError(m_szTemp);
		}
		else m_SQLErrorCount = 1;
		// ----
		if( strcmp((LPCTSTR)m_SqlState, "08S01") == 0 )
		{
			Reconnect();
		}
	};
};
//-----------------------------------------------------------------------------------------------------------
#endif /* TDataBase_H */
//-----------------------------------------------------------------------------------------------------------
