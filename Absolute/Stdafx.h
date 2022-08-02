#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TEXT_LEN						1024
#define MakePtr( cast, ptr, addValue )		( cast )( ( DWORD )( ptr ) + ( DWORD )( addValue ) ) 
//-----------------------------------------------------------------------------------------------

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "detours.lib")
//-----------------------------------------------------------------------------------------------

# if defined(_MSC_VER)
#ifndef _CRT_SECURE_NO_DEPRECATE
# define _CRT_SECURE_NO_DEPRECATE (1)
#endif
#pragma warning(disable : 4996)
# endif
//-----------------------------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <crtdbg.h>
#include <cstdlib>
#include <process.h>
#include <WinSock2.h>
#include <string.h>
#include <wchar.h>
#include <mbstring.h>
#include "detours.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
//-----------------------------------------------------------------------------------------------
// # [Notice] : this is not the place for this (ALL BELLOW)

extern char		StreamBuffUrl[100];
extern DWORD	StreamUrl;
//-----------------------------------------------------------------------------------------------

int char2int(char input);
void hex2bin(const char* src, char* target);
std::string urlencode(const std::string &c);
std::string char2hex(char dec);