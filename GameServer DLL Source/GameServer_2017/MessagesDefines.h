//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # TCore.cpp
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # Guild Name wichh will be sent logs of warnings to gamemasters (in other words gamemasters guild name) 
// ----	
#define GAMEMASTERS_GUILD_NAME						"Crew"
// ----
// # SEND TO %GAMEMASTERS_GUILD_NAME
// ----
#define SEND_TO_GUILD_ANTIHACK_MSG					"[Anti-Hack][%s] Traing using Lahap Dupe mix"
// ----
// # Send to User Messages
// ----
#define SHTRODEL_ONLY_WHILE_YOU_IN_GUILD1			"[@] פקודת שליחת הודעה לגילד מתאפשרת"
#define SHTRODEL_ONLY_WHILE_YOU_IN_GUILD2			"[@] רק במידה ואתה נמצא בתוך גילד"
#define TRYING_USE_ESC_WHILE_TRADE_MSG				"@[Trade] אין אפשרות ללחוץ על כפתור זה בעת מסחר"
#define TRYING_USE_DUEL_WHILE_SIGE					"לא ניתן להשתמש בפקודה זאת בסייג"
#define DO_NOT_REPEAT_WORDS							"אין לחזור אל אותו משפט פעמים"
#define NOT_ALLOW_SPEICAL_CHARACTERS_INGUILD_MSG	"@[@] אין באפשרותך להכניס תווים מיוחדים להודעה"
#define FORMAT_MSG_FOR_HIDEN_GM_NOTICE				"[GM] %s"
#define FORMAT_MSG_FOR_GM_NOTICE					"[%s] %s"
#define INFO_IS_OFF_MSG								"[Info] (/Infooff) Off"
#define INFO_IS_ON_MSG								"[Info] (/ifoon) On"
// ----
// # Commands
// ----
#define BAN_COMMAND									"/ban"
#define GO_COMMAND									"/go"
// ----
// # Handle only commmands
// ----
#define DISCONNET_COMMAND_TO_HANDLE_ONLY			"/disconnect"
#define MOVE_COMMAND_TO_HANDLE_ONLY					"/move"
#define TRACK_COMMAND_TO_HANDLE_ONLY				"/track"
// ----
// # Logs
// ----
#define GMS_TRACK_LOG								"[%s][%s][TRACK] : %s"
#define GMS_LOG_MOVE								"[%s][%s][MOVE] : %s %s %s %s"
#define GMS_LOG_MOVEME								"[%s][%s][MOVEME] : %d %d %d"
#define GMS_LOG_NOTICE								"[%s][%s][NOTICE] : %s"
#define GMS_LOG_DISCONNECT							"[%s][%s][DISCONNECT] : %s"
#define GMS_LOG_INVISIBLE							"[%s][%s][INVISIBLE-%s] : %s"
#define GMS_LOG_WARP								"[%s][%s][WARP] Don't have Access]"
#define HACK_LOG_SPEICAL_CHARACTER_INGUILD_MSG		"[%s][%s][GUILD_NOTICE] TRY use special character ' in guild msg"
#define HACK_LOG_LAHAP_MIX_MSG						"[%s][%s][DUPE] TRY using lahap mix"
#define HACK_LOG_ESC_WHILE_TRADE_MSG				"[%s][%s][TRADE] Click *HEAD_CASTOUMBT* While using trade"
#define HACK_LOG_018								"[%s][%s][0X18] DC HACK"
#define HACK_LOG_UNALLOWEDCHARACTER					"[%s][%s] UNALLOWED CHARACTER"
#define WHISP_LOG_MESSAGE_FORMAT					"[%d][%s] -> [%s] : %s"
#define CHAT_LOG_MESSAGE_FORMAT						"[%d][%s][%s] : [ %s ]"
#define MAIL_LOG_MESSAGE_FORMAT						"[%d][%s] -> [%s]: Title: [%s] Message: [%s]"
#define TRADE_LOG_TRADE_MESSAGE_FORMAT				"[%d][%s][%s][%s] [%s(%d,%d)] Trade Accept By [%s][%s][%s] [%s(%d,%d)]"
#define TRADE_LOG_SHOP_MESSAGE_FORMAT				"[%d][%s][%s] [%s(%d,%d)] Item Sold To [%s][%s] [%s(%d,%d)]"
#define TRADE_LOG_SHOP_MESSAGE_OPEN_FORMAT			"[%d][%s][%s] [%s(%d,%d)] Opened a store"
#define TRADE_LOG_SHOP_MESSAGE_CLOSE_FORMAT			"[%d][%s][%s] [%s(%d,%d)] Closed the store"
#define TRADE_LOG_CONNECT							"[%d][%s][%s] : Connect to Coordinates: [%s(%d,%d)]"
// roye accsess
#define GMS_LOG_Access								"[%s][%s][Access] : User USED Command Without Access: [%s]"
#define CREATE_ITEM_LOG_FORMAT_DEL					"[%s][%s][%s][%d(%d,%d)] : User Delete [%s]"
#define CREATE_ITEM_LOG_FORMAT_CREATE				"[%s][%s][%s][%d(%d,%d)] : User Create [%s]"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------