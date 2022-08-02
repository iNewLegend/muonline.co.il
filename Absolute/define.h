//-----------------------------------------------------------------------------------------------------------
#ifndef DEFINE_H
#define DEFINE_H
//-----------------------------------------------------------------------------------------------------------

enum Lang
{
	EN = 0,
	HE = 1,
};
//-----------------------------------------------------------------------------------------------------------

typedef struct
{
	Lang eLang;
	bool isLoadCamera;
} tag_LAUNCHER_REQUEST, *lptag_LAUNCHER_REQUEST;
//-----------------------------------------------------------------------------------------------------------

#define OFF 0
#define ON 1
//-----------------------------------------------------------------------------------------------------------

//#define ABSOLUTE_MAIN_VERSION		":;<=>" //
#define ABSOLUTE_MAIN_VERSION		":;<==" // 
#define ABSOLUTE_MAIN_SERIAL_WORD	'X'
#define ABSOLUTE_WAIT_RADIO			2000
//-----------------------------------------------------------------------------------------------------------

#define ABSOLUTE_PACKET_ENCRYPTION	ON
#define ABSOLUTE_CONSOLE			OFF
#define ABSOLUTE_CHECKFILES			ON
#define ABSOLUTE_RADIO				ON
//-----------------------------------------------------------------------------------------------------------

#define ABSOLUTE_ANTIHACK_SCAN_TITLE ON
#define ABSOLUTE_ANTIHACK_SCAN_PROC	 ON
//-----------------------------------------------------------------------------------------------------------

extern SOCKET					g_LAST_USED_SOCKET;
extern DWORD					g_LAST_USED_PORT;
extern lptag_LAUNCHER_REQUEST	g_launcherRequest;
//-----------------------------------------------------------------------------------------------------------
#endif /* DEFINE_H */
//-----------------------------------------------------------------------------------------------------------