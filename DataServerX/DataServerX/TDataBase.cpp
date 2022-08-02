//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "TDataBase.h"
#include "Object.h"
//-----------------------------------------------------------------------------------------------------------

#define g_ModuleName "TDataBase"
//-----------------------------------------------------------------------------------------------------------

TDataBase::TDataBase(void)
{
	m_SQLErrorCount		= 1;
	m_AffectedRowCount 	= -1;
	m_Return			= SQL_SUCCESS;
	// ----
	memset(m_szTemp, 0, sizeof(m_szTemp));
	memset(m_szMsg,0 , sizeof(m_szMsg));
	memset(m_SqlState, 0, sizeof(m_SqlState));
	// ----
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, & m_hEnv);
	SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
}
//-----------------------------------------------------------------------------------------------------------

TDataBase::~TDataBase(void)
{
	if (m_hStmt)SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	if (m_hDbc) SQLDisconnect(m_hDbc);
	if (m_hDbc) SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	if (m_hEnv) SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}
//-----------------------------------------------------------------------------------------------------------

bool TDataBase::Connect(const char * szHost, const char * szDataBase, const char * szUser, const char * szPassword)
{
	bool bReturn						= false;
	int	iRecored						= 1;
    SQLSMALLINT cbOutCon				= 0;
	// ----
	SQLCHAR InCon[255]					= {0};
	SQLCHAR OutCon[255]					= {0};
	SQLWCHAR szSQLState[MAX_DB_TEXT_LEN]	= {0};
	SQLWCHAR szSQLMsg[MAX_DB_TEXT_LEN]		= {0};
	// ----
	SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, & m_hDbc);
	// ----
	wsprintf((char *)InCon, "DRIVER=SQL Server;Server=%s;DATABASE=%s;UID=%s;PWD=%s;", szHost,
		szDataBase, szUser, szPassword);
	// ----
	OnMessage((char *)InCon);
	// ----
	m_Return = SQLDriverConnect(m_hDbc, NULL, InCon, sizeof(InCon), OutCon,
		sizeof(OutCon), & cbOutCon, SQL_DRIVER_NOPROMPT);
	// ----
	if((m_Return == SQL_SUCCESS) || (m_Return == SQL_SUCCESS_WITH_INFO))
	{
		m_Return = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, & m_hStmt);
		// ----
		if((m_Return == SQL_SUCCESS) || (m_Return == SQL_SUCCESS_WITH_INFO))
		{
			m_strHost = szHost;
			m_strDataBase = szDataBase;
			m_strUser = szUser;
			m_strPassword = szPassword;
			// ----
			bReturn  = true;
		}
		else
		{
			m_hStmt = 0;
		}
	}
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------

bool TDataBase::Connect(const char * szDnsName)
{
	bool bReturn						= false;
	int	iRecored						= 1;
    SQLSMALLINT cbOutCon				= 0;
	// ----
	SQLCHAR InCon[255]					= {0};
	SQLCHAR OutCon[255]					= {0};
	SQLWCHAR szSQLState[MAX_DB_TEXT_LEN]	= {0};
	SQLWCHAR szSQLMsg[MAX_DB_TEXT_LEN]		= {0};
	// ----
	SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, & m_hDbc);
	// ----
	wsprintf((char *)InCon, "DATABASE=%s;DRIVER=SQL Server;Server=(local);", szDnsName);
	// ----
	OnMessage((char *)InCon);
	// ----
	m_Return = SQLDriverConnect(m_hDbc, NULL, InCon, sizeof(InCon), OutCon,
		sizeof(OutCon), & cbOutCon, SQL_DRIVER_NOPROMPT);
	// ----
	if((m_Return == SQL_SUCCESS) || (m_Return == SQL_SUCCESS_WITH_INFO))
	{
		m_Return = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, & m_hStmt);
		// ----
		if((m_Return == SQL_SUCCESS) || (m_Return == SQL_SUCCESS_WITH_INFO))
		{
			m_strDnsName = szDnsName;
			// ----
			bReturn  = true;
		}
		else
		{
			m_hStmt = 0;
		}
	}
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------

bool TDataBase::Reconnect()
{
	if(m_strDnsName.length() == 0)
	{
		return Connect(m_strHost.c_str(), m_strDataBase.c_str(), m_strUser.c_str(), m_strPassword.c_str());
	}
	else
	{
		return Connect(m_strDnsName.c_str());
	}
}
//-----------------------------------------------------------------------------------------------------------

bool TDataBase::Exec(BYTE btCode, const char * szModule, const char * szFunction, char * szQuery)
{
	bool bReturn = false;
	// ----
	Clear();	// #ShadowKing : clean the cursor before use it
	// ----
	m_Return = SQLExecDirect(m_hStmt, (SQLCHAR *)szQuery, SQL_NTS);
	// ----
	g_Log.AddC(btCode, szModule, szFunction, TColor::DeepSkyBlue, szQuery);
	// ----
	if((m_Return == SQL_SUCCESS) || (m_Return == SQL_SUCCESS_WITH_INFO) || (m_Return == SQL_NO_DATA))
	{
		SQLRowCount(m_hStmt, & m_AffectedRowCount);
		SQLNumResultCols(m_hStmt, & m_nCol);
		// ----
		if (m_nCol > MAXCOL)
		{
			OnError("You have exceeded the maximum number of columns");
		}
		else if(m_nCol == 0)
		{
			Clear();
			// ----
			bReturn = true;
		}
		else
		{
			for (int i = 0 ; i < m_nCol ; ++i)
			{
				SQLBindCol(m_hStmt, i+1, SQL_C_CHAR, m_Col[i], 255, & m_lCol[i]);
				SQLDescribeCol(m_hStmt, i+1, m_ColName[i], 30, NULL, NULL, NULL, NULL, NULL);
			}
			// ----
			bReturn = true;
		}
	}
	else
	{
		Diagnostic();
	}
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------

bool TDataBase::ExecFormat(BYTE btCode, const char * szModule, const char * szFunction, const char * szQuery, ...)
{
	va_start(m_pArgs, szQuery);
	vsprintf(m_szTemp, szQuery, m_pArgs);
	va_end(m_pArgs);
	// ----
	return Exec(btCode, szModule, szFunction, m_szTemp);
}
//-----------------------------------------------------------------------------------------------------------

int TDataBase::FindCol(const char * szName)
{
	int iReturn = -1;
	// ----
	for (int i = 0 ; i < m_nCol ; ++i)
	{
		if (_stricmp(szName, (LPCTSTR)m_ColName[i]) == 0)
		{
			iReturn = i;
			// ----
			break;
		}
	}
	// ----
	return iReturn;
}
//-----------------------------------------------------------------------------------------------------------

int TDataBase::GetInt(int nCol)
{
	int iReturn = CQUERYNOCOL;
	// ----
	if (nCol <= m_nCol)
	{
		if (m_lCol[nCol] != SQL_NULL_DATA)
		{
			iReturn = atoi(m_Col[nCol]);
		}
		else
		{
			iReturn = CQUERYNULL;
		}
	}
	// ----
	return iReturn;
}
//-----------------------------------------------------------------------------------------------------------

int TDataBase::GetInt(const char *sCol)
{
	int iReturn = CQUERYNOCOL;
	int n		= -1;
	// ----
	n = FindCol(sCol);
	// ----
	if (n != -1)
	{
		iReturn = GetInt(n);
	}
	// ----
	return iReturn;
}
//-----------------------------------------------------------------------------------------------------------

__int64 TDataBase::GetInt64(int nCol)
{
	__int64 iReturn = CQUERYNOCOL;
	// ----
	if (nCol <= m_nCol)
	{
		if (m_lCol[nCol] != SQL_NULL_DATA)
		{
			iReturn = _atoi64(m_Col[nCol]);
		}
		else
		{
			iReturn = CQUERYNULL;
		}
	}
	// ----
	return iReturn;
}
//-----------------------------------------------------------------------------------------------------------

__int64 TDataBase::GetInt64(const char *sCol)
{
	__int64 iReturn = CQUERYNOCOL;
	int n		= -1;
	// ----
	n = FindCol(sCol);
	// ----
	if (n != -1)
	{
		iReturn = GetInt64(n);
	}
	// ----
	return iReturn;
}
//-----------------------------------------------------------------------------------------------------------

float TDataBase::GetFloat(int nCol)
{
	float fReturn = CQUERYNOCOL;
	// ----
	if (nCol <= m_nCol)
	{ 
		if (m_lCol[nCol] != SQL_NULL_DATA)
		{
			fReturn = (float)atof(m_Col[nCol]);
		}
		else
		{
			fReturn = CQUERYNULL;
		}
	}
	// ----
	return fReturn;
}
//-----------------------------------------------------------------------------------------------------------

float TDataBase::GetFloat(const char *sCol)
{
	float fReturn	= CQUERYNOCOL;
	int n			= -1;
	// ----
	n = FindCol(sCol);
	// ----
	if (n != -1)
	{
		fReturn = GetFloat(n);
	}
	// ----
	return fReturn;
}
//-----------------------------------------------------------------------------------------------------------

void TDataBase::GetStr(int nCol, char *buf)
{
	if (nCol > m_nCol)
	{
		buf[0] = '\0';
		return;
	}
	// ----
	if (m_lCol[nCol] == SQL_NULL_DATA) 
	{
		buf[0] = '\0';
	} 
	else 
	{
		lstrcpy(buf, m_Col[nCol]);
	}
}
//-----------------------------------------------------------------------------------------------------------

void TDataBase::GetStr(const char *sCol, char *buf)
{
	int n = -1;
	// ----
	n = FindCol(sCol);
	// ----
	if (n == -1)
	{
		buf[0] = '\0';
	} 
	else 
	{
		GetStr(n, buf);
	}
}
//-----------------------------------------------------------------------------------------------------------

int	TDataBase::GetIntExec(char * szQuery)
{
	int iReturn = CQUERYERROR;
	// ----
	if (Exec(-1, g_ModuleName, __FUNCTION__, szQuery))
	{
		if (Fetch() != SQL_NO_DATA)
		{	
			iReturn = GetInt(1);
			// ----
			Clear();
		}
		else
		{
			Clear();
			// ----
			iReturn = CQUERYEOF;
		}
	}
	// ----
	return iReturn;
}
//-----------------------------------------------------------------------------------------------------------

float TDataBase::GetFloatExec(char * szQuery)
{
	float fReturn = CQUERYERROR;
	// ----
	if (Exec(-1, g_ModuleName, __FUNCTION__, szQuery))
	{
		if (Fetch() != SQL_NO_DATA)
		{	
			fReturn = GetFloat(1);
			// ----
			Clear();
		}
		else
		{
			Clear();
			// ----
			fReturn = CQUERYEOF;
		}
	}
	// ----
	return fReturn;
}
//-----------------------------------------------------------------------------------------------------------

bool TDataBase::GetStrExec(char * szQuery, char * buf)
{
	bool bReturn = false;
	// ----
	if (Exec(-1, g_ModuleName, __FUNCTION__, szQuery))
	{
		if (Fetch() != SQL_NO_DATA)
		{
			GetStr(1,buf);
			// ----
			Clear();
			// ----
			bReturn = true;
		}
		else
		{
			Clear();
			// ----
			buf[0] = '\0';
		}
	}
	else
	{
		buf[0] = '\0';
	}
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------

int TDataBase::GetAsBinary(LPTSTR lpszStatement, LPBYTE OUT lpszReturnBuffer)
{/* add Clear(); before query */
	SQLCHAR * pSQLBuf;
	SQLINTEGER BufLen;
	SQLCHAR SQLBinary[10000];
	SQLINTEGER lOfs = 0;
	SQLLEN SQLLen;
	SQLRETURN SQLResult;

	Clear(); // #ShadowKing

	//SQLAllocHandle(SQL_HANDLE_STMT, m_hConnection, &m_hStmt);

	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::DeepSkyBlue, lpszStatement);

	SQLResult = SQLExecDirect(m_hStmt, (SQLTCHAR *)lpszStatement, SQL_NTS);


	if ( SQLResult != SQL_SUCCESS )
	{
		Diagnostic();
		return -1;
	}

	while ( true )
	{
		SQLResult = SQLFetch(m_hStmt);

		if ( SQLResult == SQL_NO_DATA )
			break;

		pSQLBuf = lpszReturnBuffer;

		while ( true )
		{

			SQLResult = SQLGetData(m_hStmt,
				1, SQL_C_BINARY , SQLBinary, sizeof(SQLBinary), &SQLLen);

			if ( SQLResult == SQL_NO_DATA )
				break;

			if ( SQLLen == -1 )
			{
				Clear();
				return 0;
			}

			if ( SQLResult == SQL_SUCCESS )
			{
				BufLen = SQLLen;
			}
			else
			{
				BufLen = sizeof(SQLBinary);
			}

			lOfs += BufLen;
			memcpy(pSQLBuf, SQLBinary, BufLen);
			pSQLBuf = &pSQLBuf[lOfs];
		}
	}

	//SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	return BufLen;
}
//-----------------------------------------------------------------------------------------------------------

void TDataBase::SetAsBinary(LPTSTR lpszStatement, LPBYTE lpBinaryBuffer, SQLUINTEGER BinaryBufferSize)
{ /* add Clear(); before query */

	Clear(); // #ShadowKing

	SQLLEN cbValueSize = -0x64 - BinaryBufferSize;
	SQLPOINTER pToken;
	BYTE cBUFFER[10000];
	SQLRETURN Result;

	SQLBindParameter(m_hStmt, 1, SQL_PARAM_INPUT,
		SQL_C_BINARY , SQL_LONGVARBINARY, BinaryBufferSize, 0, (SQLPOINTER)1, 0, &cbValueSize);

	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::DeepSkyBlue, lpszStatement);

	SQLExecDirect(m_hStmt, (SQLTCHAR *)lpszStatement, SQL_NTS);
	Result = SQLParamData(m_hStmt, &pToken);

	int lOfs=0;

	while ( Result == SQL_NEED_DATA )
	{
		memcpy(cBUFFER, lpBinaryBuffer, sizeof(cBUFFER));
		Result = SQLPutData(m_hStmt, cBUFFER, BinaryBufferSize);
		Result = SQLParamData(m_hStmt, &pToken);
		lOfs += sizeof(cBUFFER);
	}

	SQLParamData(m_hStmt, &pToken);
	Clear();
}
//-----------------------------------------------------------------------------------------------------------
