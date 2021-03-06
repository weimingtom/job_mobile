#ifndef _GAMECOMMON_H
#define	_GAMECOMMON_H

#ifdef WIN32
#if !defined(DEF_LINUX)
#include <windows.h>
#endif
#else
#define _UNIX
#endif

#include <algorithm>

//#include "../Protocol Buffers/Poker/Game_Poker.pb.h"
#include "../protobuf/gameLogic.pb.h"
#include "../Protocol Buffers/Poker/AdlGameCommon.h"
//#include "google/protobuf/repeated_field.h"
//#include <google/protobuf/stubs/common.h>

//#include "include/xtmpl.h"

using namespace std;
using namespace Game_Poker;
using namespace adl;

#if 0
/*
typedef vector<long>		VecUSN;
typedef vector<long>		VecCard;
typedef vector<long long>	VecMoney;
typedef vector<long>		VecState;
typedef vector<long>	    VecRankingFinishPoint;
typedef vector<long>	    VecUserBetCount;
*/
//#define MAX_GSTRINGBUF (1024)



#ifdef _UNIX
typedef long long LONGLONG;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;
typedef unsigned char* LPBYTE;
typedef DWORD* LPDWORD  ;
typedef char* LPCSTR ;
typedef char* LPSTR;
typedef wchar_t WCHAR;
typedef WCHAR* LPWSTR;
typedef const WCHAR* LPCWSTR;
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef unsigned long DWORD_PTR;
typedef size_t	strpos;
typedef const BYTE * LPCBYTE;
typedef void * LPVOID;
//typedef unsigned short WORD;
typedef WORD* BSTR;
typedef char CHAR;

#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))
#define FALSE	0
#define TRUE	1

#define lstrlenA	strlen
#define BOOL		int

#define _NO_XLIB 
#define _XADL

#define ERROR_INVALID_PARAMETER         87L    // dderror
#define ERROR_INSUFFICIENT_BUFFER       122L    // dderror
#define __stdcall
#endif

#ifndef ASSERT
#define EXCEPTION_ASSERT     0xE0000001
#define ASSERT(x) \
	if(!(x)) \
	::RaiseException( EXCEPTION_ASSERT, 0, 0, 0);
#endif

#define MAX_PLAYER_COUNT 5

const long g_lSSN=120;  //섯다
const int g_nVersion=1234;//1256;

const int MAX_CARD_ARRAY=8; // 전체 게임을 통틀어 최대 가지게 되는 카드 장 수
const int MAX_CARD_COUNT=5;
const int TOTAL_CARDS=4*13;
const int NUM_MADE=22;
const int MAX_CARDCHECK_COUNT=5;
const int MAX_CHANNEL=10;

enum {
	ITEM_PAYBOOK=1075,
	ITEM_MINICASHBOX=1049,
	ITEM_FIRSTGOLD=1904,
	ITEM_FIRSTCLUB=1901,
	ITEM_FIRSTDREAM=1905,
	ITEM_FIRSTLOVE=1906,	
	ITEM_FIRSTMINI=1903,
	ITEM_MINICASHBOX_PRACTICE=1080,  // 금고 체험권  
	ITEM_MINICASHBOX_DISCOUNT=1081,  // 금고 할인권
	ITEM_INFINITYSPEED=1030,
	ITEM_GAMEHELPER=1063,				// 게임 도우미(기본)
	ITEM_GAMEHELPER_PLUS=1064,		// 게임 도우미(플러스)
};

enum BETTING_RULE
{
	BETTING_FREE=0,
	BETTING_AUTO,
	BETTING_AUTO_ADD,
	BETTING_492,
};

enum ADD_RULE
{
	ADD_FREE=0,
	ADD_QUATER_1,
	ADD_QUATERHALF_11,
	ADD_QUATERHALF_12,
};

enum FIRST_RULE
{
	FIRST_FREE=0,
	FIRST_591,
	FIRST_491_1QUARTER,
	FIRST_491_1HALF,
	FIRST_491_2HALF,
	FIRST_592,
	FIRST_592_SPEED,	
};

enum SECOND_RULE
{
	SECOND_FREE=0,
	SECOND_NODIE,
};


enum{
	GAMETYPE_NORMAL=0,
	GAMETYPE_USERDEAL=1,
	GAMETYPE_POKERBET=2,
};

enum USER_STATE
{
	USERSTATE_NONE=-1,
	USERSTATE_READY=0,
	USERSTATE_WAITING,
	USERSTATE_49WAITING,
	USERSTATE_SELECTBEGIN,
	USERSTATE_SELECTEND,
	USERSTATE_PLAYING,
	USERSTATE_DIE,
	USERSTATE_SELECTCONTINUE,
};

enum GAMESTATE 
{
	GAMESTATE_INVALID=-1,
	GAMESTATE_READY=0,
	GAMESTATE_START,
	GAMESTATE_SELECT,
	GAMESTATE_PLAY,
	GAMESTATE_RESULT,
	GAMESTATE_SAVE,
	GAMESTATE_DEAD,
	GAMESTATE_MAX
};


enum SYSMSG_TYPE {
	SYSMSG_MONEYDEFICIT=10,
	SYSMSG_MONEYOVER,
	SYSMSG_PRIZEMONEY,
	SYSMSG_PURGE_RESERVED=100,
	SYSMSG_PURGE_CANCEL,
	SYSMSG_PURGE,
	SYSMSG_WINER=200,
	SYSMSG_DEALER,
	SYSMSG_MONEYLOSER,
	SYSMSG_MONEYADD,
	SYSMSG_GIVEMONEY,
	SYSMSG_GAMESTART,
	SYSMSG_CARDSELECT,
	SYSMSG_ENTRY,
	SYSMSG_OBSERVE,
	SYSMSG_EXIT,
	SYSMSG_BOSS,
	SYSMSG_NOSTART,
	SYSMSG_DBFAIL,
	SYSMSG_POWER,
	SYSMSG_MISSION,
	SYSMSG_GAMELIMIT,
	SYSMSG_MONEYWINADD,
	SYSMSG_TWOOWNER_NOMONEY,
	SYSMSG_LCS_KICKOUT_USER,
	SYSMSG_GAMEEND,
	SYSMSG_STRANGENESS,
	SYSMSG_AUTOBET,
	SYSMSG_TEST=1000,
};

enum BET_STATE
{
	BETSTATE_NONE=0,
	BETSTATE_CALL=1,
	BETSTATE_BBING,
	BETSTATE_CHECK,
	BETSTATE_DOUBLE,
	BETSTATE_QUARTER,
	BETSTATE_HALF,
	BETSTATE_FULL,
	BETSTATE_DIE,
	BETSTATE_LIVE,
	BETSTATE_ALLIN,
	BETSTATE_REST,
	BETSTATE_RECEIVE,
	BETSTATE_SAMEPOINT,
	BETSTATE_TENPOINT,
	BETSTATE_TWENTYPOINT,
	BETSTATE_FIFTYPOINT,
	BETSTATE_NINETYPOINT,
	BETSTATE_CUT,
	BETSTATE_PASS,
	BETSTATE_LIVE_CUT,
	BETSTATE_LIVE_PASS,
	BETSTATE_LINE,
	BETSTATE_DEAL,
};

enum {
	BET_TYPE_NONE=0,
	BET_TYPE_CALL=1,
	BET_TYPE_CHECK,
	BET_TYPE_CHECK_ONLY,
	BET_TYPE_BBING,
	BET_TYPE_BET,
	BET_TYPE_DIE,
	BET_TYPE_LIVE,
	BET_TYPE_REST_ONLY,
	BET_TYPE_REST,
	BET_TYPE_REST_HIGH,
	BET_TYPE_RECEIVE,
	BET_TYPE_SAMEPOINT,
	BET_TYPE_SAMEPOINT_HIGH,
	BET_TYPE_CHANGE,
	BET_TYPE_LIVE_CHANGE,
	BET_TYPE_LINE,
	BET_TYPE_LINE_TIME,
	BET_TYPE_LINEDEAL,
	BET_TYPE_LINEEND,
	BET_TYPE_AUTO,
};

enum{
	BET_TURN_NONE=0,
	BET_TURN_LIVE_1=1,
	BET_TURN_LIVE_2=2,
	BET_TURN_REST_1=3,
	BET_TURN_REST_2=4,
	BET_TURN_REST_3=5,
	BET_TURN_REMATCH_REST_1=11,
	BET_TURN_REMATCH_REST_2=12,
	BET_TURN_REMATCH_REST_3=13,
	BET_TURN_LINE=21,
	BET_TURN_BET_1_1=101,
	BET_TURN_BET_2_1=102,
	BET_TURN_BET_2_2=103,
	BET_TURN_BET_2_3=104,
};


enum {
	EXIT_INVALID=0,
	EXIT_OBSERVE,
	EXIT_EXIT
};

enum MSG_ERRORCODE
{
	ERR_SUCCESS=0,
	ERR_NOACCESS,		// user has no access code to create room...
	ERR_INVALIDTARGET,
	ERR_INVALIDPWD,
	ERR_NOSEAT,
	ERR_ALREADY,
	ERR_INVALIDSVCID,
	ERR_SYSTEM,
	ERR_MISMATCHVERSION,
	ERR_FAULTSTATE,
	ERR_NOTNOWTURN,
	ERR_DONOTPLAYER,
	ERR_VERIFYPLAYER,
	ERR_FIRSTUSER,
	ERR_REALNAME,

	// 점검 공지 강화(병도 2010-07-07 )
	ERR_CHECKNOTICE_0,	// 정기점검
	ERR_CHECKNOTICE_1,	// 임시점검
};

enum ENTRY_ERRORCODE
{
	ENTRY_NOMONEY=0,
	ENTRY_NOMONEY_OBSERVE,
	ENTRY_SPACE,
	ENTRY_IP,
	ENTRY_VERSION,
	ENTRY_BLACKLIST,
	ENTRY_GAMELIMIT,
	ENTRY_POWERCHANNEL,
	ENTRY_LOCALJACKPOT_NOMONEY, //로컬 잭팟 : 돈이 부족할때 패킷
	ENTRY_NEEDTICKET, //철이가 대기표시스템: 티켓필요하다 알림
	ENTRY_GRADE,			// 등급이 맞지 않을때. GON
	ENTRY_OVERMONEY,
	ENTRY_TWOOWNER_NOMONEY,
};


enum RankPrecedence {
	RANK_NONE=-1,
	RANK_NOMADE=0,
	RANK_MADE=1,
	RANK_NINE_FOUR=2,
	RANK_FOOL_NINE_FOUR=3,
	RANK_THREE_SEVEN=4,
	RANK_FOUR_SEVEN=5,
	RANK_ZERO=6,
	RANK_ONE=7,
	RANK_TWO=8,
	RANK_THREE=9,
	RANK_FOUR=10,
	RANK_FIVE=11,
	RANK_SIX=12,
	RANK_SEVEN=13,
	RANK_EIGHT=14,
	RANK_NINE=15,
	RANK_FOUR_SIX=16,
	RANK_TEN_FOUR=17,
	RANK_TEN_ONE=18,
	RANK_ONE_NINE=19,
	RANK_ONE_FOUR=20,
	RANK_ONE_TWO=21,
	RANK_1DDANG=22,
	RANK_2DDANG=23,
	RANK_3DDANG=24,
	RANK_4DDANG=25,
	RANK_5DDANG=26,
	RANK_6DDANG=27,
	RANK_7DDANG=28,
	RANK_8DDANG=29,
	RANK_9DDANG=30,
	RANK_10DDANG=31,
	RANK_13DDANG=32,
	RANK_18DDANG=33,
	RANK_38DDANG=34,
	RANK_MAX,
	RANK_73DDANGCATCH,
	RANK_ASSA_JANGDDANG,
	
	RANK_TOP=0,
	RANK_ONEPAIR,
	RANK_TWOPAIR,
	RANK_THREEOFAKIND,
	RANK_STRAIGHT,
	RANK_BACKSTRAIGHT,
	RANK_MOUNTAIN,
	RANK_FLUSH,
	RANK_FULLHOUSE,
	RANK_FOUROFAKIND,
	RANK_STRAIGHTFLUSH,
	RANK_ROYALSTRAIGHTFLUSH,	
};


enum Timer {
	TIMER_START=1,
	TIMER_STARTPREV,
	TIMER_DEALOPEN,
	TIMER_BETTING,
	TIMER_BETTINGTURN,
	TIMER_BETTINGWANT,
	TIMER_DEAL,
	TIMER_SPEEDGAME,
	TIMER_GAMEEND,
	TIMER_NEWGAME,
	TIMER_CONTINUE,
	TIMER_REMATCH,
	TIMER_AUTOBET,
	TIMER_PURGE,
	TIMER_CARDDEAL,
	TIMER_FINISHUSER,
	TIMER_ECHO_DEALS,
	TIMER_ECHO_BET,
	TIMER_ECHO_DEAL,
	TIMER_ECHO_FINISH,
};


string vformat(LPCSTR fmt, va_list vl) 
{
	CHAR buf[MAX_GSTRINGBUF + 1];

	int nBuf=_vsnprintf_s(buf, MAX_GSTRINGBUF, fmt, vl);

	if(nBuf<0)
		buf[MAX_GSTRINGBUF]=0;
	return string(buf);
}
	
wstring vformat(LPCWSTR fmt, va_list vl) 
{
	WCHAR buf[MAX_GSTRINGBUF + 1];
	int nBuf=_vsnwprintf_s(buf, MAX_GSTRINGBUF, fmt, vl);
	if(nBuf<0)
		buf[MAX_GSTRINGBUF]=0;
	return wstring(buf);
}
	
string format(LPCSTR fmt, ...) 
{
	va_list vl;
	va_start(vl, fmt);
	string ret=vformat(fmt, vl);
	va_end(vl);
	return ret;
}
	
wstring format(LPCWSTR fmt, ...) 
{
	va_list vl;
	va_start(vl, fmt);
	wstring ret=vformat(fmt, vl);
	va_end(vl);
	return ret;
}




class Item : public _Item
{
public:
	long GetFucnsrl(){ return m_lFucnsrl; }
	LONGLONG GetStartTime(){ return m_llStartTime; }
	LONGLONG GetEndTime(){ return m_llEndTime; }
	LONGLONG GetCount(){ return m_llCount; }
	long	 GetCount_long(){ return (long)m_llCount; }

	
	void SetFucnsrl(long lsrl){ m_lFucnsrl=lsrl; }
	void SetStartTime(LONGLONG llTemp){ m_llStartTime=llTemp; }
	void SetEndTime(LONGLONG llTemp){ m_llEndTime=llTemp; }
	void SetCount(long lCnt){ m_llCount=lCnt; }

#ifndef _UNIX
	void SetItem(string & sitem)
	{
		string sTemp= sitem.substr(0, sitem.find(","));
		m_lFucnsrl=atol(sTemp.c_str());
		sitem.erase(0, sitem.find(",")+1);

		string sTemp1=sitem.substr(0, sitem.find(","));
#ifdef _IPHONE
		m_llStartTime=atoll(sTemp1.c_str());
#else
		m_llStartTime=_atoi64(sTemp1.c_str());
#endif
		sitem.erase(0, sitem.find(",")+1);

		string sTemp2=sitem.substr(0, sitem.find(","));
#ifdef _IPHONE
		m_llEndTime=atoll(sTemp2.c_str());
#else
		m_llEndTime=_atoi64(sTemp2.c_str());
#endif
		sitem.erase(0, sitem.find(",")+1);

		string sTemp3=sitem.substr(0, sitem.find(","));
#ifdef _IPHONE
		m_llCount=atoll(sTemp3.c_str());
#else
		m_llCount=_atoi64(sTemp3.c_str());
#endif
		sitem.erase(0, sitem.find(",")+1);
	}
	void SetVIP(string & sitem, string & sday)
	{
		m_lFucnsrl=atol(sitem.c_str());
#ifdef _IPHONE
		m_llStartTime=atoll(sday.c_str());
		m_llEndTime=atoll(sday.c_str());
#else
		m_llStartTime=_atoi64(sday.c_str());
		m_llEndTime=_atoi64(sday.c_str());
#endif
		
		m_llCount=0;
	}
#endif
	void Clear()
	{
		m_lFucnsrl=0;
		m_llStartTime=0;
		m_llEndTime=0;
		m_llCount=0;
	}

	LONG	m_lFucnsrl;
	LONGLONG	m_llStartTime;
	LONGLONG	m_llEndTime;
	LONGLONG	m_llCount;
};


class ItemList : public _ItemList
{

public:
	void Clear(){ m_lstItem.clear(); }
	
#ifndef _UNIX
	void SetItem(string & sReservedString4)
	{		
		int nCursor;
		while( (nCursor=sReservedString4.find("|"))!=-1)
		{
			sReservedString4.erase(0, nCursor+1);
			string sTemp= sReservedString4.substr(0, sReservedString4.find(","));
			
			int temp=sReservedString4.find("|");
			if(temp==-1) break;
			string sTemp2=sReservedString4.substr(0, temp);
			
			Item tmpItem;
			tmpItem.SetItem(sTemp2);			
			
			AddItem(tmpItem);						
		}
	}
	void SetVIP(string sVipString)
	{
		if(0==sVipString.size()) return;
		string::size_type pos;
		pos=sVipString.find_first_of('|');
		if(NULL==pos) return;
		string strIndex=sVipString.substr(0, pos);
		sVipString.erase(sVipString.begin(), sVipString.begin() + pos + 1);
		int nAll=atoi(sVipString.c_str());
		int nYear=nAll/100;
		int nMonth=nAll%100+1;
		if(12<nMonth){
			nYear+=1;
			nMonth=1;
		}
#ifdef _IPHONE
		string strDay=format("%04d%02d%s", nYear, nMonth, "03000000");
#else
		string strDay=::format("%04d%02d%s", nYear, nMonth, "03000000");
#endif
		Item tmpItem;
		tmpItem.SetVIP(strIndex, strDay);
		AddItem(tmpItem);			
	}
	long RemoveItem(long lFucnsrl)
	{
		ForEachElmt(list<Item>, m_lstItem, i, j)
		{
			if(i->GetFucnsrl()==lFucnsrl){
				m_lstItem.erase(i);
				return true;	
			}
		}
		return false;		
	}

	long AddItem(const Item & item)
	{
		RemoveItem(item.m_lFucnsrl);
		m_lstItem.push_back(item);
		return true;
	}

	long IsItem(long lFucnsrl)
	{
		ForEachElmt(list<Item>, m_lstItem, i, j)
		{
			if(i->GetFucnsrl()==lFucnsrl){
				SYSTEMTIME st; 
#ifdef _IPHONE
				LONGLONG lCurrentTime=(st.wYear*10000000000ll) + (st.wMonth*100000000) + (st.wDay*1000000) + (st.wHour*10000) + (st.wMinute*100) + st.wSecond;
#else
				GetLocalTime(&st);
				LONGLONG lCurrentTime=(st.wYear*10000000000ll) + (st.wMonth*100000000) + (st.wDay*1000000) + (st.wHour*10000) + (st.wMinute*100) + st.wSecond;
#endif				return i->GetEndTime() >= lCurrentTime;
			}
			
		}			
		return false;
	}
	
	LONGLONG GetCount(long lFucnsrl)
	{
#ifdef _IPHONE
		list<Item>::iterator i;
		list<Item>::iterator j;
#endif	
		ForEachElmt(list<Item>, m_lstItem, i, j)
		{
			if(i->GetFucnsrl()==lFucnsrl) 
				return i->GetCount();	
		}
		return 0;		
	}

	long GetCount_long(long lFucnsrl)
	{
#ifdef _IPHONE
		list<Item>::iterator i;
		list<Item>::iterator j;
#endif	
		ForEachElmt(list<Item>, m_lstItem, i, j)
		{
			if(i->GetFucnsrl()==lFucnsrl)
				return i->GetCount_long();
		}
		return 0;			
	}
	
	LONGLONG GetEndTime(long lFucnsrl)
	{
#ifdef _IPHONE
		list<Item>::iterator i;
		list<Item>::iterator j;
#endif	
		ForEachElmt(list<Item>, m_lstItem, i, j)
		{
			if(i->GetFucnsrl()==lFucnsrl)
				return i->GetEndTime();
		}
		return 0;				
	}
	
	void SetEndTime(long lFucnsrl, LONGLONG llToTime)
	{
//#ifdef _IPHONE
		list<Item>::iterator i;
		list<Item>::iterator j;
//#endif	
		ForEachElmt(list<Item>, m_lstItem, i, j)
		{
			if(i->GetFucnsrl()==lFucnsrl) break;
		}
		if(i==m_lstItem.end()) return;	
		
		i->SetEndTime(llToTime);
	}
#endif
	std::list<Item>	m_lstItem;
};


class BettingMsg : public _BettingMsg
{

public:
	void Clear()
	{
		m_lUSN=-1;
		m_nIndex=-1;
		m_BetType=-1;
		m_bBettingMoney=false;
		m_bMoneyLack=false;
		m_bCallMoneyZero=false;
		m_llCallMoney=0;
		m_llRaiseMoney=0;
	}
	LONG	m_lUSN;
	int	m_nIndex;
	LONG	m_BetType;
	LONG	m_bBettingMoney;
	LONG	m_bMoneyLack;
	LONG	m_bCallMoneyZero;
	LONGLONG	m_llCallMoney;
	LONGLONG	m_llRaiseMoney;
};

typedef vector<BettingMsg> BettingMsgArray;

#define BettingMsgTable_Ctor

class BettingMsgTable : public vector<BettingMsg>, public _BettingMsgTable
{

public:
	BettingMsgTable(){ clear(); }
	void Init(int nSize=MAX_PLAYER_COUNT)
	{
		if(0 >= nSize) return;
		clear();
		for(int i=0; i<nSize; ++i)
		{
			BettingMsg msg;
			msg.Clear();
			push_back(msg);
		}
	}

	void Clear()
	{
		for(int i=0; i<(int)size(); ++i)
			at(i).Clear();
	}

	BettingMsg & GetBettingMsg(int idx){return at(idx);}
	const BettingMsg & GetBettingMsg(int idx) const {return at(idx);}
};

class Cards : public PKCards
{
public:
	enum{
		CARDTYPE_NORMAL=0,
		CARDTYPE_HIDDEN=1,
		CARDTYPE_SAME=2,
	};

	void Clear()
	{
		m_vtCards.clear();
		m_lResultIdx=0;
		m_vUserUSN.clear();
	}
	void AddUSN(long lUSN)
	{
		VecUSN::iterator Find;
		Find=find(m_vUserUSN.begin(), m_vUserUSN.end(), lUSN);
		if(m_vUserUSN.end()==Find){
			m_vUserUSN.push_back(lUSN);
		}	
	}
	void DelUSN(long lUSN)
	{
		VecUSN::iterator new_end;
		new_end=remove(m_vUserUSN.begin(), m_vUserUSN.end(), lUSN);
		m_vUserUSN.erase(new_end, m_vUserUSN.end());
	}
	void DelUSN()
	{
		m_vUserUSN.clear();
	}
	string CardStr(){
		int nTotal=m_vtCards.size();
		string sCard;
		for(int i=0; i<nTotal; i++){
			sCard=sCard+format("%2d", m_vtCards[i]);
		}
		return sCard;
	}
	VecCard	m_vtCards;
	LONG	m_lResultIdx;
	VecUSN	m_vUserUSN;
};

typedef vector<Cards> CardArray;

#define CardTable_Ctor

class CardTable : public vector<Cards>, public _CardTable
{

public:
	CardTable(){ clear(); }
	void Init(int nSize=MAX_PLAYER_COUNT)
	{
		if(0 >= nSize) return;
		clear();
		for(int i=0; i<nSize; ++i)
		{
			Cards cards;
			cards.Clear();
			push_back(cards);
		}
	}

	void Clear()
	{
		for(int i=0; i<(int)size(); ++i)
			at(i).Clear();
	}

	Cards & GetCards(int idx){return at(idx);}
	const Cards & GetCards(int idx) const {return at(idx);}
};

class Money : public _Money
{
public:
	void Clear()
	{
		m_llCMoney=0;
		m_llCallMoney=0;
		m_llSideMoney=0;
		m_llCallHabMoney=0;
		m_llJackpotMoney=0;
		m_llTakeMoney=0;
		m_lBetState=0;
		m_lBetReceive=0;
		m_lBetCount=0;
		m_lResultIdx=0;
		m_sMoneyMsg="";
	}

	void BetClear()
	{
		m_llCallMoney=0;
		m_lBetState=0;
		m_lBetReceive=0;
		m_lBetCount=0;
		m_lResultIdx=0;
		m_sMoneyMsg="";
	}
	LONGLONG	m_llCMoney;
	LONGLONG	m_llCallMoney;
	LONGLONG	m_llSideMoney;
	LONGLONG	m_llCallHabMoney;
	LONGLONG	m_llTakeMoney;
	LONGLONG	m_llJackpotMoney;
	LONG	m_lBetState;
	LONG	m_lBetReceive;
	LONG	m_lBetCount;
	LONG	m_lResultIdx;
	std::string	m_sMoneyMsg;
};

#define MoneyTable_Ctor

class MoneyTable : public vector<Money> , public _MoneyTable
{

public:
	MoneyTable(){ clear(); }
	void Init(int nSize=MAX_PLAYER_COUNT)
	{
		if(0 >= nSize) return;
		clear();
		for(int i=0; i<nSize; ++i)
		{
			Money money;
			money.Clear();
			push_back(money);
		}
	}
	virtual void Clear()
	{
		for(int i=0; i<(int)size(); ++i)
			at(i).Clear();
	}
	void Add()
	{
		Money money;
		money.Clear();
		push_back(money);
	}
	void AddRemove(int nSize)
	{
		if((int)size()==nSize) return;
		if((int)size()>nSize)
		{
			erase(begin()+nSize, end());
		}
		else
		{
			for(int i=(int)size(); i<nSize; i++)
			{
				Money money;
				money.Clear();
				push_back(money);
			}
		}	
	}
	void Remove(int idx)
	{
		if((0>idx)||((int)size()<=idx)) return;
		erase(begin()+idx);
	}

	Money& GetMoney(int idx){return at(idx);}
	const Money& GetMoney(int idx) const {return at(idx);}
};


class WinLoseInfo : public _WinLoseInfo
{
public:
	void Clear()
	{
		m_llCMoney=0;
		m_lWin=0;
		m_lLose=0;
		m_lReserved=0;
	}
	LONGLONG	m_llCMoney;
	LONG	m_lWin;
	LONG	m_lLose;
	LONG	m_lReserved;
};

#define CWinLose_Ctor


class CWinLose : public _CWinLose
{
public:
	CWinLose(){ Clear(); }
	void	Clear(){ m_lWin=0; m_lLose=0; m_lContinue=0; }
	void AddWin(long bContinue=false)
	{
		m_lWin++;
		m_lContinue=((true==bContinue)?(m_lContinue+1):(0));
	}
	void AddLose(long bContinue=false)
	{
		m_lLose++;
		m_lContinue=((true==bContinue)?(m_lContinue+1):(0));
	}
	void SetWin(long lWin){ m_lWin=lWin; }
	void SetLose(long lLose){ m_lLose=lLose; }
	long GetWinLose(void){ return m_lWin+m_lLose; }
	LONG	m_lWin;
	LONG	m_lLose;
	LONG	m_lContinue;
};

typedef vector<CWinLose>			vecWinLoseCnt;

#endif


_Cards* CreatePoker(void)
{
	_Cards* card = new _Cards;

	//USN임의 생성
	card->Clear();
	card->clear_m_vuserusn();
	card->mutable_m_vuserusn()->set_usn(12345);

	//card->m_vUserUSN = new VecUSN();
	//card->

	for(int i = 0 ; i < 110 ; i++)
		card->add_m_vtcards(i);

	for(int i = 0 ; i < 100 ; i++)
		card->add_m_lresultidx(i);

	return card;
}

//Protocol Buffers 형식의 데이터를 STL로 전환 또는 그 반대
////////////////////////////////////////
////////////////////////////////////////
class PB_STL_Convertor
{
public:
	static void STL2PB(_Cards *cards, VecCard *vt)
	{
		int i = 0;
		for(VecCard::iterator it = vt->begin() ; it != vt->end() ; ++it)
		{
			cards->set_m_vtcards(++i, *it);
		}

		//std::cout << cards->DebugString() << std::endl;
		cards->PrintDebugString();
	}

	static void PB2STL(_Cards *cards, VecCard *vt)
	{
		for(int *pt = cards->mutable_m_vtcards()->begin() ; pt != cards->mutable_m_vtcards()->end() ; ++pt)
		{
			vt->push_back(*pt);
		}

		cards->PrintDebugString();
	}
};


class PokerCard : public _Cards, public PB_STL_Convertor
{
public:

	PokerCard()
	{
		
	}

	void Clear()
	{
		m_vtCards.clear();
		m_lResultIdx=0;
		m_vUserUSN.clear();
	}
	void AddUSN(long lUSN)
	{
		VecUSN::iterator Find;
		Find=find(m_vUserUSN.begin(), m_vUserUSN.end(), lUSN);
		if(m_vUserUSN.end()==Find){
			m_vUserUSN.push_back(lUSN);
		}	
	}
	void DelUSN(long lUSN)
	{
		VecUSN::iterator new_end;
		new_end=remove(m_vUserUSN.begin(), m_vUserUSN.end(), lUSN);
		m_vUserUSN.erase(new_end, m_vUserUSN.end());
	}
	void DelUSN()
	{
		m_vUserUSN.clear();
	}
	string CardStr(){
		int nTotal=m_vtCards.size();
		string sCard;
		for(int i=0; i<nTotal; i++){
			//sCard=sCard+format("%2d", m_vtCards[i]);
		}
		return sCard;
	}

	
	void PB2STL_Cards(void)
	{

	}

	void PB2STL_USN(void)
	{
	}
	

	VecCard	m_vtCards;
	LONG	m_lResultIdx;
	VecUSN	m_vUserUSN;
};

#endif//_GAMECOMMON_H