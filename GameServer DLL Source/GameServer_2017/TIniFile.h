#ifndef TINIFILE_H
#define TINIFILE_H
//---------------------------------------------------------------------------
 
//---------------------------------------------------------------------------
// # Created by:    S@nek[BoR];
// # Last Update:   20.07.2010 11-53;
// # Status:        Completed;
// # Description:   Class for read *.ini files for VC++;
//---------------------------------------------------------------------------

#include <stdio.h>
//---------------------------------------------------------------------------
 
class TIniFile
{
private:
    char m_szFilePath[256];
    // ----
    char m_szSection[100];
    // ----
    char m_szTemp[50];
    char m_szValue[50];
public:
    TIniFile() {};
    TIniFile(const char * szFilePath) { SetFilePath((char *)szFilePath); };
    TIniFile(const char * szFilePath, const char * szSection) { SetFilePath((char *)szFilePath); SetSection((char *)szSection); };
    ~TIniFile() {};
    // ----
    void SetFilePath(char * szFilePath)
    {
        memset(m_szFilePath, 0, sizeof(m_szFilePath));
        memcpy(m_szFilePath, szFilePath, strlen(szFilePath));
    };
    // ----
    void SetSection(char * szSection)
    {
        memset(m_szSection, 0, sizeof(m_szSection));
        memcpy(m_szSection, szSection, strlen(szSection));
    };
    // ----
    // # BOOL;
    // ----
    bool ReadBool(char * szKey)
    {
        return (GetPrivateProfileInt(m_szSection, szKey, 0, m_szFilePath) == 0) ? false : true;
    };
    // ----
    bool ReadBool(char * szSection, char * szKey)
    {
        return (GetPrivateProfileInt(szSection, szKey, 0, m_szFilePath) == 0) ? false : true;
    };
    // ----
    bool ReadBool(const char * szKey, bool bDefaultValue)
    {
        return (GetPrivateProfileInt(m_szSection, szKey, (bDefaultValue == false) ? 0 : 1, m_szFilePath) == 0) ? false : true;
    };
    // ----
    bool ReadBool(const char * szSection, char * szKey, bool bDefaultValue)
    {
        return (GetPrivateProfileInt(szSection, szKey, (bDefaultValue == false) ? 0 : 1, m_szFilePath) == 0) ? false : true;
    };
    // ----
    // # INT;
    // ----
    int ReadInt(const  char * szKey)
    {
        return GetPrivateProfileInt(m_szSection, szKey, 0, m_szFilePath);
    };
    // ----
    int ReadInt(const  char * szSection, char * szKey)
    {
        return GetPrivateProfileInt(szSection, szKey, 0, m_szFilePath);
    };
    // ----
    int ReadInt(const char * szKey, int iDefaultValue)
    {
        return GetPrivateProfileInt(m_szSection, szKey, iDefaultValue, m_szFilePath);
    };
    // ----
    int ReadInt(char * szSection, char * szKey, int iDefaultValue)
    {
        return GetPrivateProfileInt(szSection, szKey, iDefaultValue, m_szFilePath);
    };
    // ----
    // # FLOAT;
    // ----
    float ReadFloat(const  char * szKey)
    {
        GetPrivateProfileString(m_szSection, szKey, "0", m_szTemp, 5, m_szFilePath);
        // ----
        return atof(m_szTemp);
    };
    // ----
    float ReadFloat(const char * szSection, char * szKey)
    {
        GetPrivateProfileString(szSection, szKey, "0", m_szTemp, 5, m_szFilePath);
        // ----
        return atof(m_szTemp);
    };
    // ----
    float ReadFloatconst (const  char * szKey, float fDefaultValue)
    {
        sprintf(m_szValue, "%f\0", fDefaultValue);
        // ----
        GetPrivateProfileString(m_szSection, szKey, m_szValue, m_szTemp, 5, m_szFilePath);
        // ----
        return atof(m_szTemp);
    };
    // ----
    float ReadFloat(const char * szSection, char * szKey, float fDefaultValue)
    {
        sprintf(m_szValue, "%f\0", fDefaultValue);
        // ----
        GetPrivateProfileString(szSection, szKey, m_szValue, m_szTemp, 5, m_szFilePath);
        // ----
        return atof(m_szTemp);
    };
    // ----
    // # String;
    // ----
    void ReadString(const  char * szKey, char * szBufOut)
    {
        GetPrivateProfileString(m_szSection, szKey, "---", szBufOut, 200, m_szFilePath);
    };
    // ----
    void ReadString(const  char * szSection, char * szKey, char * szBufOut)
    {
        GetPrivateProfileString(szSection, szKey, "---", szBufOut, 200, m_szFilePath);
    };
    // ----
    void ReadString(const  char * szKey, char * szBufOut, int iMaxLen)
    {
        GetPrivateProfileString(m_szSection, szKey, "---", szBufOut, iMaxLen, m_szFilePath);
    };
    // ----
    void ReadString(const  char * szSection, char * szKey, char * szBufOut, int iMaxLen)
    {
        GetPrivateProfileString(szSection, szKey, "---", szBufOut, iMaxLen, m_szFilePath);
    };
    // ----
    void ReadString2(const char * szKey, char * szBufOut, char * szDefaultValue)
    {
        GetPrivateProfileString(m_szSection, szKey, szDefaultValue, szBufOut, 200, m_szFilePath);
    };
    // ----
    void ReadString2(const char * szSection, char * szKey, char * szBufOut, char * szDefaultValue)
    {
        GetPrivateProfileString(szSection, szKey, szDefaultValue, szBufOut, 200, m_szFilePath);
    };
    // ----
    void ReadString2(const  char * szKey, char * szBufOut, int iMaxLen, char * szDefaultValue)
    {
        GetPrivateProfileString(m_szSection, szKey, szDefaultValue, szBufOut, iMaxLen, m_szFilePath);
    };
    // ----
    void ReadString2(const  char * szSection, char * szKey, char * szBufOut, int iMaxLen, char * szDefaultValue)
    {
        GetPrivateProfileString(szSection, szKey, szDefaultValue, szBufOut, iMaxLen, m_szFilePath);
    };
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
 