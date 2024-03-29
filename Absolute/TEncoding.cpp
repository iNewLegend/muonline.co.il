#include "StdAfx.h"
#include "TEncoding.h"
//-----------------------------------------------------------------------------------------------------------
// # Made by leo123[BoR]
//-----------------------------------------------------------------------------------------------------------

CEncoding g_Encoder;
//-----------------------------------------------------------------------------------------------------------

CEncoding::CEncoding(void)
{

}
//-----------------------------------------------------------------------------------------------------------

CEncoding::~CEncoding(void)
{

}
//-----------------------------------------------------------------------------------------------------------

void CEncoding::CodeBuffer(LPBYTE Buffer, int Len)
{
	for(int i = 0 ; i != Len ; i++)
	{
		Buffer[i]		= EncBuff[Buffer[i]];
	}
}
//-----------------------------------------------------------------------------------------------------------

void CEncoding::DecodeBuffer(LPBYTE Buffer, int Len)
{
	for(int i = 0 ; i != Len ; i++)
	{
		Buffer[i]		= DecBuff[Buffer[i]];
	}
}
//-----------------------------------------------------------------------------------------------------------

BYTE EncBuff[256] =
{
	78,//0
	130,//1
	179,//2
	231,//3
	24,//4
	76,//5
	129,//6
	178,//7
	230,//8
	26,//9
	75,//10
	127,//11
	176,//12
	229,//13
	25,//14
	74,//15
	126,//16
	227,//17
	73,//18
	125,//19
	177,//20
	226,//21
	22,//22
	124,//23
	225,//24
	21,//25
	122,//26
	174,//27
	20,//28
	72,//29
	121,//30
	173,//31
	18,//32
	71,//33
	123,//34
	172,//35
	224,//36
	17,//37
	69,//38
	171,//39
	223,//40
	19,//41
	68,//42
	120,//43
	169,//44
	222,//45
	67,//46
	119,//47
	220,//48
	66,//49
	118,//50
	170,//51
	219,//52
	15,//53
	117,//54
	218,//55
	14,//56
	115,//57
	167,//58
	13,//59
	65,//60
	114,//61
	166,//62
	11,//63
	64,//64
	116,//65
	165,//66
	217,//67
	10,//68
	62,//69
	164,//70
	216,//71
	12,//72
	61,//73
	113,//74
	162,//75
	215,//76
	60,//77
	112,//78
	213,//79
	59,//80
	111,//81
	163,//82
	212,//83
	8,//84
	110,//85
	211,//86
	7,//87
	108,//88
	160,//89
	6,//90
	58,//91
	107,//92
	159,//93
	4,//94
	57,//95
	109,//96
	158,//97
	210,//98
	3,//99
	55,//100
	157,//101
	209,//102
	5,//103
	54,//104
	106,//105
	155,//106
	208,//107
	53,//108
	105,//109
	206,//110
	52,//111
	104,//112
	156,//113
	205,//114
	1,//115
	102,//116
	204,//117
	101,//118
	153,//119
	255,//120
	51,//121
	100,//122
	152,//123
	253,//124
	50,//125
	151,//126
	203,//127
	252,//128
	48,//129
	150,//130
	202,//131
	254,//132
	47,//133
	99,//134
	148,//135
	201,//136
	46,//137
	98,//138
	199,//139
	45,//140
	97,//141
	149,//142
	198,//143
	250,//144
	95,//145
	197,//146
	249,//147
	94,//148
	146,//149
	248,//150
	44,//151
	93,//152
	145,//153
	246,//154
	43,//155
	144,//156
	196,//157
	245,//158
	41,//159
	143,//160
	195,//161
	247,//162
	40,//163
	92,//164
	141,//165
	194,//166
	39,//167
	91,//168
	192,//169
	37,//170
	90,//171
	142,//172
	191,//173
	243,//174
	88,//175
	190,//176
	242,//177
	38,//178
	87,//179
	139,//180
	241,//181
	86,//182
	138,//183
	239,//184
	36,//185
	137,//186
	189,//187
	238,//188
	34,//189
	136,//190
	188,//191
	240,//192
	33,//193
	85,//194
	134,//195
	187,//196
	32,//197
	84,//198
	185,//199
	30,//200
	83,//201
	135,//202
	184,//203
	236,//204
	81,//205
	183,//206
	235,//207
	31,//208
	80,//209
	132,//210
	234,//211
	79,//212
	131,//213
	232,//214
	29,//215
	182,//216
	27,//217
	181,//218
	233,//219
	180,//220
	77,//221
	23,//222
	128,//223
	228,//224
	175,//225
	70,//226
	16,//227
	221,//228
	168,//229
	63,//230
	9,//231
	214,//232
	161,//233
	56,//234
	2,//235
	207,//236
	103,//237
	154,//238
	49,//239
	251,//240
	200,//241
	96,//242
	147,//243
	42,//244
	244,//245
	193,//246
	89,//247
	140,//248
	35,//249
	237,//250
	186,//251
	82,//252
	133,//253
	28,//254
	0,//255
};
//------------------------------------------------------------------------------------------------------------

BYTE DecBuff[256] =
{
	255,//0
	115,//1
	235,//2
	99,//3
	94,//4
	103,//5
	90,//6
	87,//7
	84,//8
	231,//9
	68,//10
	63,//11
	72,//12
	59,//13
	56,//14
	53,//15
	227,//16
	37,//17
	32,//18
	41,//19
	28,//20
	25,//21
	22,//22
	222,//23
	4,//24
	14,//25
	9,//26
	217,//27
	254,//28
	215,//29
	200,//30
	208,//31
	197,//32
	193,//33
	189,//34
	249,//35
	185,//36
	170,//37
	178,//38
	167,//39
	163,//40
	159,//41
	244,//42
	155,//43
	151,//44
	140,//45
	137,//46
	133,//47
	129,//48
	239,//49
	125,//50
	121,//51
	111,//52
	108,//53
	104,//54
	100,//55
	234,//56
	95,//57
	91,//58
	80,//59
	77,//60
	73,//61
	69,//62
	230,//63
	64,//64
	60,//65
	49,//66
	46,//67
	42,//68
	38,//69
	226,//70
	33,//71
	29,//72
	18,//73
	15,//74
	10,//75
	5,//76
	221,//77
	0,//78
	212,//79
	209,//80
	205,//81
	252,//82
	201,//83
	198,//84
	194,//85
	182,//86
	179,//87
	175,//88
	247,//89
	171,//90
	168,//91
	164,//92
	152,//93
	148,//94
	145,//95
	242,//96
	141,//97
	138,//98
	134,//99
	122,//100
	118,//101
	116,//102
	237,//103
	112,//104
	109,//105
	105,//106
	92,//107
	88,//108
	96,//109
	85,//110
	81,//111
	78,//112
	74,//113
	61,//114
	57,//115
	65,//116
	54,//117
	50,//118
	47,//119
	43,//120
	30,//121
	26,//122
	34,//123
	23,//124
	19,//125
	16,//126
	11,//127
	223,//128
	6,//129
	1,//130
	213,//131
	210,//132
	253,//133
	195,//134
	202,//135
	190,//136
	186,//137
	183,//138
	180,//139
	248,//140
	165,//141
	172,//142
	160,//143
	156,//144
	153,//145
	149,//146
	243,//147
	135,//148
	142,//149
	130,//150
	126,//151
	123,//152
	119,//153
	238,//154
	106,//155
	113,//156
	101,//157
	97,//158
	93,//159
	89,//160
	233,//161
	75,//162
	82,//163
	70,//164
	66,//165
	62,//166
	58,//167
	229,//168
	44,//169
	51,//170
	39,//171
	35,//172
	31,//173
	27,//174
	225,//175
	12,//176
	20,//177
	7,//178
	2,//179
	220,//180
	218,//181
	216,//182
	206,//183
	203,//184
	199,//185
	251,//186
	196,//187
	191,//188
	187,//189
	176,//190
	173,//191
	169,//192
	246,//193
	166,//194
	161,//195
	157,//196
	146,//197
	143,//198
	139,//199
	241,//200
	136,//201
	131,//202
	127,//203
	117,//204
	114,//205
	110,//206
	236,//207
	107,//208
	102,//209
	98,//210
	86,//211
	83,//212
	79,//213
	232,//214
	76,//215
	71,//216
	67,//217
	55,//218
	52,//219
	48,//220
	228,//221
	45,//222
	40,//223
	36,//224
	24,//225
	21,//226
	17,//227
	224,//228
	13,//229
	8,//230
	3,//231
	214,//232
	219,//233
	211,//234
	207,//235
	204,//236
	250,//237
	188,//238
	184,//239
	192,//240
	181,//241
	177,//242
	174,//243
	245,//244
	158,//245
	154,//246
	162,//247
	150,//248
	147,//249
	144,//250
	240,//251
	128,//252
	124,//253
	132,//254
	120,//255
};
//------------------------------------------------------------------------------------------------------------