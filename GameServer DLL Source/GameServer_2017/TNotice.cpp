#include "stdafx.h"
#include "TNotice.h"
#include "User.h"
#include "TGameServer.h"

//----------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TNotice"
//----------------------------------------------------------------------------------------------------------------

void CNotice::MakeNoticeMsg(void * lpNotice, BYTE btType, char * szNoticeMsg)
{
    PMSG_NOTICE * pNotice		= (PMSG_NOTICE *)lpNotice;
	pNotice->type				= btType;
    // ----
    wsprintf(pNotice->Notice, szNoticeMsg);
	// ----
    PHeadSetB((LPBYTE)pNotice, 0x0D, (((strlen(pNotice->Notice)) + sizeof(PMSG_NOTICE)) - sizeof(pNotice->Notice) + 1));
}
//----------------------------------------------------------------------------------------------------------------

void CNotice::MakeNoticeMsgEx(void * lpNotice, BYTE btType, char * szNoticeMsg, ...)
{
    PMSG_NOTICE * pNotice	 = (PMSG_NOTICE *)lpNotice;
	pNotice->type			 = btType;
	 // ----
    va_list pArguments;
    va_start(pArguments, szNoticeMsg);
	 // ----
    vsprintf((char *)pNotice->Notice, (char *)szNoticeMsg, pArguments);
	 // ----
    va_end(pArguments);
	 // ----
    PHeadSetB((LPBYTE)pNotice, 0x0D, (((strlen(pNotice->Notice)) + sizeof(PMSG_NOTICE)) - sizeof(pNotice->Notice) + 1));
}
//----------------------------------------------------------------------------------------------------------------

void CNotice::SetNoticeProperty(void * lpNotice, BYTE btType, DWORD dwColor, BYTE btCount, WORD wDelay, BYTE btSpeed)
{
    PMSG_NOTICE * pNotice	= (PMSG_NOTICE *) lpNotice;
	// ----
    pNotice->type			= btType;
    pNotice->dwColor			= dwColor;
    pNotice->btCount			= btCount;
    pNotice->wDelay			= wDelay;
    pNotice->btSpeed			= btSpeed;
}
//----------------------------------------------------------------------------------------------------------------

void CNotice::SendNoticeToAllUser(void * lpNotice)
{
    PMSG_NOTICE * pNotice = (PMSG_NOTICE *)lpNotice;
	 // ----
	OBJECTSTRUCT * lpUser;
	 // ----
    for(int n = OBJECT_START_INDEX ; n < OBJECT_MAX_INDEX ; ++n)
    {
		lpUser = & gObj[n];
		// ----
        if(lpUser->Connected == PLAYER_PLAYING)
        {
            if(lpUser->Type  == OBJ_USER)
            {
                g_GS.DataSend(n, (UCHAR *)pNotice  , pNotice->h.size);
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------

void CNotice::SendNoticeToUser(int aIndex, void * lpNotice)
{
    PMSG_NOTICE * pNotice = (PMSG_NOTICE *)lpNotice;
	// ----
    g_GS.DataSend(aIndex, (UCHAR *)pNotice, pNotice->h.size);
}
//----------------------------------------------------------------------------------------------------------------

void CNotice::AllSendServerMsg(LPSTR chatmsg)
{
    PMSG_NOTICE pNotice;
	// ----
    MakeNoticeMsg((CNotice *) & pNotice, 0,  chatmsg);
	// ----
	OBJECTSTRUCT * lpUser;
	// ----
    for(int n = OBJECT_START_INDEX ; n < OBJECT_MAX_INDEX ; ++n)
    {
		lpUser = & gObj[n];
		// ----
        if(lpUser->Connected == PLAYER_PLAYING)
        {
            if(lpUser->Type  == OBJ_USER)
            {
                g_GS.DataSend(n, (UCHAR *)&pNotice , pNotice.h.size);
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------

void CNotice::GCServerMsgStringSend(LPSTR szMsg, int aIndex, BYTE type)
{
    PMSG_NOTICE pNotice;
	// ----
    MakeNoticeMsg(& pNotice, type, szMsg);
	// ----
    g_GS.DataSend(aIndex, (UCHAR *)&pNotice, pNotice.h.size);
}
//----------------------------------------------------------------------------------------------------------------

CNotice::CNotice(BYTE btType)
{
    this->m_Notice.btCount		= 1;
    this->m_Notice.btSpeed		= 20;
    this->m_Notice.dwColor		= _ARGB(255, 255, 200, 80);
    this->m_Notice.wDelay		= 0;
    this->m_Notice.type			= btType;
}
//----------------------------------------------------------------------------------------------------------------

void CNotice::SendToAllUser(LPSTR szMsg, ...)
{
    va_list pArguments;
    va_start(pArguments, szMsg);
	// ----
    vsprintf(this->m_Notice.Notice, (char *)szMsg, pArguments);
	// ----
    va_end(pArguments);
	// ----
    PHeadSetB((LPBYTE)&this->m_Notice, 0x0D, (((strlen(this->m_Notice.Notice)) + sizeof(PMSG_NOTICE)) - sizeof(this->m_Notice.Notice) + 1));
	// ----
	OBJECTSTRUCT * lpUser;
	// ----
    for(int n = OBJECT_START_INDEX ; n < OBJECT_MAX_INDEX ; ++n)
    {
		lpUser = & gObj[n];
		// ----
        if(lpUser->Connected == PLAYER_PLAYING)
        {
            if(lpUser->Type  == OBJ_USER)
            {
                g_GS.DataSend(n, (LPBYTE)&this->m_Notice , this->m_Notice.h.size);
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------

void CNotice::SendToUser(int aIndex, LPSTR szMsg, ...)
{
    va_list pArguments;
    va_start(pArguments, szMsg);
	// ----
    vsprintf(this->m_Notice.Notice, (char *)szMsg, pArguments);
	// ----
    va_end(pArguments);
	// ----
    PHeadSetB((LPBYTE)&this->m_Notice, 0x0D, (((strlen(this->m_Notice.Notice)) + sizeof(PMSG_NOTICE)) - sizeof(this->m_Notice.Notice) + 1));
	// ----
    g_GS.DataSend(aIndex, (LPBYTE)&this->m_Notice , this->m_Notice.h.size);
}
//----------------------------------------------------------------------------------------------------------------