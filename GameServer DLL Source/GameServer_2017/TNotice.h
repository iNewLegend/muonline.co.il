//----------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------

__inline DWORD _ARGB(BYTE a, BYTE r, BYTE g, BYTE b)
{
    return a * 16777216 + b * 65536 + g * 256 + r;
};
//----------------------------------------------------------------------------------------------------------------

struct PMSG_NOTICE
{
    PBMSG_HEAD	h;
    BYTE		type;
    BYTE		btCount;
    WORD		wDelay;
    int			dwColor;
    BYTE		btSpeed;
    char		Notice[256];
};
//----------------------------------------------------------------------------------------------------------------

class CNotice
{
public:
	PMSG_NOTICE m_Notice;
	// ----
    static void MakeNoticeMsg			(void * lpNotice, BYTE btType, LPSTR szNoticeMsg);
    static void MakeNoticeMsgEx			(void * lpNotice, BYTE btType, LPSTR szNoticeMsg, ...);
    static void SetNoticeProperty		(void * lpNotice, BYTE btType, DWORD dwColor, BYTE btCount, WORD wDelay, BYTE btSpeed);
    static void SendNoticeToAllUser		(void * lpNotice);
    static void SendNoticeToUser		(int aIndex, void * lpNotice);
    static void AllSendServerMsg		(LPSTR chatmsg);
    static void GCServerMsgStringSend	(LPSTR szMsg, int aIndex, BYTE type);
	// ----
    CNotice(BYTE btType);
	// ----
    void __cdecl SendToUser				(int aIndex, LPSTR szMsg, ...);
    void __cdecl SendToAllUser			(LPSTR szMsg, ...);
};
//----------------------------------------------------------------------------------------------------------------