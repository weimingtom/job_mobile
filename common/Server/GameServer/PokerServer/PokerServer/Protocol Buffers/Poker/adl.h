#ifndef __adl_H__
#define __adl_H__
#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#define _NO_XLIB
#define _XADL
//#define _Poker
//#define _UNIX
//#define _AirPlay

using namespace std;

#ifndef _Poker
#include "xadldefine.h"

#include "takeout/adl/xADLBER.h"
#include "takeout/adl/xUtil.h"
#else

#ifndef _AirPlay

//#include "../../../Platform/client/SNSD/Classes/takeout/adl/xADLBER.h"
//#include "../../../Platform/client/SNSD/Classes/takeout/adl/xUtil.h"

#else


#include "list"
#include "vector"
#include "string"
#include "algorithm"
using namespace std;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;
typedef unsigned char* LPBYTE;
typedef DWORD* LPDWORD  ;
typedef char* LPCSTR ;
typedef char* LPSTR;
typedef wchar_t WCHAR;
typedef char CHAR;
typedef WCHAR* LPWSTR;
typedef const WCHAR* LPCWSTR;
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef unsigned long DWORD_PTR;
typedef size_t	strpos;
typedef const BYTE * LPCBYTE;
typedef void * LPVOID;
typedef long long LONGLONG;
typedef unsigned short WORD;
typedef WORD* BSTR;
typedef int BOOL;
#define ASSERT(a) 
// Do not use ForEachElmt to vector, deque, string. See Effective STL Item 9
#define ForEachFromTo(_IT, i, from, to) \
	for(_IT i = (from); ((i) != (to)); ++i)
#define ForEach(T, l, i) \
	ForEachFromTo(T::iterator, i, (l).begin(), (l).end())
#define ForCEach(T, l, i) \
	ForEachFromTo(T::const_iterator, i, (l).begin(), (l).end())
#define ForNext(i) (++(i))
#define ForEraseNext(l,i) ((i) = (l).erase(i))

#define ForEachElmtFromTo(_IT, i, j, from, to) \
	for(_IT i, j = (from); ((((i) = (j)) == (to)) ? 0 : (++(j), 1)); )

#define ForEachElmt(T, l, i, j) \
	ForEachElmtFromTo(T::iterator, i, j, (l).begin(), (l).end())

#define ForEachCElmt(_T, l, i, j) \
	ForEachElmtFromTo(_T::const_iterator, i, j, (l).begin(), (l).end())

#define ForEachElmtRvs(_T, l, i, j) \
	ForEachElmtFromTo(_T::reverse_iterator, i, j, (l).rbegin(), (l).rend())

#define ForEachCElmtRvs(_T, l, i, j) \
	ForEachCElmtFromTo(_T::const_reverse_iterator, i, j, (l).rbegin(), (l).rend())

#include "xADLBER.h"
#include "xUtil.h"
#endif

#endif


#include "AdlGameCommon.h"
//#include "AdlGameCommon_b.h"
#include "AdlGameUser_Poker.h"
//#include "AdlGameUser_Poker_b.h"
#include "AdlGameRoom.h"
//#include "AdlGameRoom_b.h"
#include "AdlGame_Poker.h"
//#include "AdlGame_Poker_b.h"
#ifndef _Poker
#include "adlutil.h"
#endif

/*
#ifndef _Poker
#include "AdlSGSCli.h"
#include "AdlSGSCli_b.h"
#include "AdlSGSCommon.h"
#include "AdlSGSCommon_b.h"
#endif
*/

const long g_lSSN=120;  //섯다
const int g_nVersion=1234;//1256;

const int MAX_CARD_ARRAY=8; // 전체 게임을 통틀어 최대 가지게 되는 카드 장 수
const int MAX_CARD_COUNT=5;
const int TOTAL_CARDS=4*13;
const int NUM_MADE=22;
const int MAX_CARDCHECK_COUNT=5;
const int MAX_CHANNEL=10;
//const int Seat[5][5]={{0, 1, 2, 3, 4}, {1, 2, 3, 4, 0}, {2, 3, 4, 0, 1}, {3, 4, 0, 1, 2}, {4, 0, 1, 2, 3}};
// CHANNEL_1에 해당하는 값이 항상 모든 배열의 끝에 있어야 한다.

//철이가 강퇴 카운트
//const int MAX_ALLIN=3;//수호천사
//const int PURGE_INCRAESE[LIMIT_PURGECNT]={1, 2, 5, 10, 20}; 
//철이가 강퇴 카운트

//수호천사
const int cnt_MAX_ALLIN=4;	// 4회로 변경 : 섯다 수호군

enum _NEWSUDDA_GAMERULE{
	GAMERULE_SUDDA_2=0,
	GAMERULE_SUDDA_3=1,
	GAMERULE_DORIG_9=2,
};

enum StraightPrecedence {
	STRAIGHT_NONE=-1,
	STRAIGHT_TOP,
	STRAIGHT_BACK,
	STRAIGHT_MOUNTAIN
};

///////////////////////////////////////////////////////////////////////////////////
// 폴리스 방제 신고 변경
enum TERMINATE_ROOM
{
	TERMINATE_ROOM_GRACEFUL=1,                // 진행중인 방이 끝난 뒤 방 삭제
	TERMINATE_ROOM_IMMEDIATE=2,               // 즉시 방 삭제(현재 쓰지 않을 것이나 추후 필요할 경우를 위해)
	KICKOUT_USER_CHEAT=1,
};


#endif
