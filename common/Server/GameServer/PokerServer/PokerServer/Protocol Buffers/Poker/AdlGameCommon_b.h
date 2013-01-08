//
// AdlGameCommon_b.h: generated by XADL compiler 1.1 , 2011.8.24 16:38:0
//

#ifndef GAMECOMMON_H
#define GAMECOMMON_H

namespace adl { // start of namesapce
template<>
class BER<WAITINGUSERDATA >
{
public:
	static DWORD Size(const WAITINGUSERDATA& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<LONG >::Size(_obj.m_lUSN);
		dwSize += BER<LONG >::Size(_obj.m_lTicketNum);
		dwSize += BER<LONG >::Size(_obj.m_lBackColor);
		dwSize += BER<LONG >::Size(_obj.m_bCallWeb);
		return dwSize;
	}

	static bool Load(WAITINGUSERDATA* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONG >::Load(&(_obj->m_lUSN), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lTicketNum), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lBackColor), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_bCallWeb), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const WAITINGUSERDATA& _obj )
	{
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lUSN ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lTicketNum ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lBackColor ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_bCallWeb ))
			return false;
		return true;
	}
	static bool Copy(WAITINGUSERDATA* _obj, const WAITINGUSERDATA& src)
	{
		if(!BER<LONG >::Copy(&(_obj->m_lUSN), src.m_lUSN))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lTicketNum), src.m_lTicketNum))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lBackColor), src.m_lBackColor))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_bCallWeb), src.m_bCallWeb))
			return false;
		return true;
	}

};

template<>
class BER<OneCard >
{
public:
	static DWORD Size(const OneCard& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<int >::Size(_obj.m_nIndex);
		dwSize += BER<LONG >::Size(_obj.m_lCardIndex);
		return dwSize;
	}

	static bool Load(OneCard* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<int >::Load(&(_obj->m_nIndex), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lCardIndex), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const OneCard& _obj )
	{
		if(!BER<int >::Store(ppBuf, pdwSize, _obj.m_nIndex ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lCardIndex ))
			return false;
		return true;
	}
	static bool Copy(OneCard* _obj, const OneCard& src)
	{
		if(!BER<int >::Copy(&(_obj->m_nIndex), src.m_nIndex))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lCardIndex), src.m_lCardIndex))
			return false;
		return true;
	}

};

template<>
class BER<Cards >
{
public:
	static DWORD Size(const Cards& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<VecCard >::Size(_obj.m_vtCards);
		dwSize += BER<LONG >::Size(_obj.m_lResultIdx);
		dwSize += BER<VecUSN >::Size(_obj.m_vUserUSN);
		return dwSize;
	}

	static bool Load(Cards* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<VecCard >::Load(&(_obj->m_vtCards), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lResultIdx), ppBuf, pdwSize))
			return false;
		if(!BER<VecUSN >::Load(&(_obj->m_vUserUSN), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const Cards& _obj )
	{
		if(!BER<VecCard >::Store(ppBuf, pdwSize, _obj.m_vtCards ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lResultIdx ))
			return false;
		if(!BER<VecUSN >::Store(ppBuf, pdwSize, _obj.m_vUserUSN ))
			return false;
		return true;
	}
	static bool Copy(Cards* _obj, const Cards& src)
	{
		if(!BER<VecCard >::Copy(&(_obj->m_vtCards), src.m_vtCards))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lResultIdx), src.m_lResultIdx))
			return false;
		if(!BER<VecUSN >::Copy(&(_obj->m_vUserUSN), src.m_vUserUSN))
			return false;
		return true;
	}

};

template<>
class BER<Money >
{
public:
	static DWORD Size(const Money& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<LONGLONG >::Size(_obj.m_llCMoney);
		dwSize += BER<LONGLONG >::Size(_obj.m_llCallMoney);
		dwSize += BER<LONGLONG >::Size(_obj.m_llSideMoney);
		dwSize += BER<LONGLONG >::Size(_obj.m_llCallHabMoney);
		dwSize += BER<LONGLONG >::Size(_obj.m_llTakeMoney);
		dwSize += BER<LONGLONG >::Size(_obj.m_llJackpotMoney);
		dwSize += BER<LONG >::Size(_obj.m_lBetState);
		dwSize += BER<LONG >::Size(_obj.m_lBetReceive);
		dwSize += BER<LONG >::Size(_obj.m_lBetCount);
		dwSize += BER<LONG >::Size(_obj.m_lResultIdx);
		dwSize += BER<std::string >::Size(_obj.m_sMoneyMsg);
		return dwSize;
	}

	static bool Load(Money* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONGLONG >::Load(&(_obj->m_llCMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llCallMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llSideMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llCallHabMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llTakeMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llJackpotMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lBetState), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lBetReceive), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lBetCount), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lResultIdx), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sMoneyMsg), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const Money& _obj )
	{
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llCMoney ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llCallMoney ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llSideMoney ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llCallHabMoney ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llTakeMoney ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llJackpotMoney ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lBetState ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lBetReceive ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lBetCount ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lResultIdx ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sMoneyMsg ))
			return false;
		return true;
	}
	static bool Copy(Money* _obj, const Money& src)
	{
		if(!BER<LONGLONG >::Copy(&(_obj->m_llCMoney), src.m_llCMoney))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llCallMoney), src.m_llCallMoney))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llSideMoney), src.m_llSideMoney))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llCallHabMoney), src.m_llCallHabMoney))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llTakeMoney), src.m_llTakeMoney))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llJackpotMoney), src.m_llJackpotMoney))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lBetState), src.m_lBetState))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lBetReceive), src.m_lBetReceive))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lBetCount), src.m_lBetCount))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lResultIdx), src.m_lResultIdx))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sMoneyMsg), src.m_sMoneyMsg))
			return false;
		return true;
	}

};

template<>
class BER<UserMoney >
{
public:
	static DWORD Size(const UserMoney& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<LONG >::Size(_obj.m_lUSN);
		dwSize += BER<LONG >::Size(_obj.m_lState);
		dwSize += BER<LONGLONG >::Size(_obj.m_llMoney);
		dwSize += BER<LONGLONG >::Size(_obj.m_llCallHabMoney);
		dwSize += BER<LONGLONG >::Size(_obj.m_llTakeMoney);
		dwSize += BER<LONGLONG >::Size(_obj.m_llDealMoney);
		dwSize += BER<std::string >::Size(_obj.m_sNickName);
		dwSize += BER<std::string >::Size(_obj.m_sDealerTax);
		return dwSize;
	}

	static bool Load(UserMoney* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONG >::Load(&(_obj->m_lUSN), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lState), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llCallHabMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llTakeMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llDealMoney), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sNickName), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sDealerTax), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const UserMoney& _obj )
	{
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lUSN ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lState ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llMoney ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llCallHabMoney ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llTakeMoney ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llDealMoney ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sNickName ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sDealerTax ))
			return false;
		return true;
	}
	static bool Copy(UserMoney* _obj, const UserMoney& src)
	{
		if(!BER<LONG >::Copy(&(_obj->m_lUSN), src.m_lUSN))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lState), src.m_lState))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llMoney), src.m_llMoney))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llCallHabMoney), src.m_llCallHabMoney))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llTakeMoney), src.m_llTakeMoney))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llDealMoney), src.m_llDealMoney))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sNickName), src.m_sNickName))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sDealerTax), src.m_sDealerTax))
			return false;
		return true;
	}

};

template<>
class BER<BettingMsg >
{
public:
	static DWORD Size(const BettingMsg& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<LONG >::Size(_obj.m_lUSN);
		dwSize += BER<int >::Size(_obj.m_nIndex);
		dwSize += BER<LONG >::Size(_obj.m_BetType);
		dwSize += BER<LONG >::Size(_obj.m_bBettingMoney);
		dwSize += BER<LONG >::Size(_obj.m_bMoneyLack);
		dwSize += BER<LONG >::Size(_obj.m_bCallMoneyZero);
		dwSize += BER<LONGLONG >::Size(_obj.m_llCallMoney);
		dwSize += BER<LONGLONG >::Size(_obj.m_llRaiseMoney);
		return dwSize;
	}

	static bool Load(BettingMsg* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONG >::Load(&(_obj->m_lUSN), ppBuf, pdwSize))
			return false;
		if(!BER<int >::Load(&(_obj->m_nIndex), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_BetType), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_bBettingMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_bMoneyLack), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_bCallMoneyZero), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llCallMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llRaiseMoney), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const BettingMsg& _obj )
	{
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lUSN ))
			return false;
		if(!BER<int >::Store(ppBuf, pdwSize, _obj.m_nIndex ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_BetType ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_bBettingMoney ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_bMoneyLack ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_bCallMoneyZero ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llCallMoney ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llRaiseMoney ))
			return false;
		return true;
	}
	static bool Copy(BettingMsg* _obj, const BettingMsg& src)
	{
		if(!BER<LONG >::Copy(&(_obj->m_lUSN), src.m_lUSN))
			return false;
		if(!BER<int >::Copy(&(_obj->m_nIndex), src.m_nIndex))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_BetType), src.m_BetType))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_bBettingMoney), src.m_bBettingMoney))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_bMoneyLack), src.m_bMoneyLack))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_bCallMoneyZero), src.m_bCallMoneyZero))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llCallMoney), src.m_llCallMoney))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llRaiseMoney), src.m_llRaiseMoney))
			return false;
		return true;
	}

};

template<>
class BER<Item >
{
public:
	static DWORD Size(const Item& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<LONG >::Size(_obj.m_lFucnsrl);
		dwSize += BER<LONGLONG >::Size(_obj.m_llStartTime);
		dwSize += BER<LONGLONG >::Size(_obj.m_llEndTime);
		dwSize += BER<LONGLONG >::Size(_obj.m_llCount);
		return dwSize;
	}

	static bool Load(Item* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONG >::Load(&(_obj->m_lFucnsrl), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llStartTime), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llEndTime), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llCount), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const Item& _obj )
	{
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lFucnsrl ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llStartTime ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llEndTime ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llCount ))
			return false;
		return true;
	}
	static bool Copy(Item* _obj, const Item& src)
	{
		if(!BER<LONG >::Copy(&(_obj->m_lFucnsrl), src.m_lFucnsrl))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llStartTime), src.m_llStartTime))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llEndTime), src.m_llEndTime))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llCount), src.m_llCount))
			return false;
		return true;
	}

};

template<>
class BER<ItemList >
{
public:
	static DWORD Size(const ItemList& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<std::list<Item> >::Size(_obj.m_lstItem);
		return dwSize;
	}

	static bool Load(ItemList* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<std::list<Item> >::Load(&(_obj->m_lstItem), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const ItemList& _obj )
	{
		if(!BER<std::list<Item> >::Store(ppBuf, pdwSize, _obj.m_lstItem ))
			return false;
		return true;
	}
	static bool Copy(ItemList* _obj, const ItemList& src)
	{
		if(!BER<std::list<Item> >::Copy(&(_obj->m_lstItem), src.m_lstItem))
			return false;
		return true;
	}

};

template<>
class BER<WinLoseInfo >
{
public:
	static DWORD Size(const WinLoseInfo& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<LONGLONG >::Size(_obj.m_llCMoney);
		dwSize += BER<LONG >::Size(_obj.m_lWin);
		dwSize += BER<LONG >::Size(_obj.m_lLose);
		dwSize += BER<LONG >::Size(_obj.m_lReserved);
		return dwSize;
	}

	static bool Load(WinLoseInfo* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONGLONG >::Load(&(_obj->m_llCMoney), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lWin), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lLose), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lReserved), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const WinLoseInfo& _obj )
	{
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llCMoney ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lWin ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lLose ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lReserved ))
			return false;
		return true;
	}
	static bool Copy(WinLoseInfo* _obj, const WinLoseInfo& src)
	{
		if(!BER<LONGLONG >::Copy(&(_obj->m_llCMoney), src.m_llCMoney))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lWin), src.m_lWin))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lLose), src.m_lLose))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lReserved), src.m_lReserved))
			return false;
		return true;
	}

};

template<>
class BER<CWinLose >
{
public:
	static DWORD Size(const CWinLose& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<LONG >::Size(_obj.m_lWin);
		dwSize += BER<LONG >::Size(_obj.m_lLose);
		dwSize += BER<LONG >::Size(_obj.m_lContinue);
		return dwSize;
	}

	static bool Load(CWinLose* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONG >::Load(&(_obj->m_lWin), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lLose), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lContinue), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const CWinLose& _obj )
	{
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lWin ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lLose ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lContinue ))
			return false;
		return true;
	}
	static bool Copy(CWinLose* _obj, const CWinLose& src)
	{
		if(!BER<LONG >::Copy(&(_obj->m_lWin), src.m_lWin))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lLose), src.m_lLose))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lContinue), src.m_lContinue))
			return false;
		return true;
	}

};

template<>
class BER<CRefill >
{
public:
	static DWORD Size(const CRefill& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<LONGLONG >::Size(_obj.m_llTime);
		dwSize += BER<int >::Size(_obj.m_nCnt);
		dwSize += BER<LONG >::Size(_obj.m_lPLevel);
		return dwSize;
	}

	static bool Load(CRefill* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONGLONG >::Load(&(_obj->m_llTime), ppBuf, pdwSize))
			return false;
		if(!BER<int >::Load(&(_obj->m_nCnt), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lPLevel), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const CRefill& _obj )
	{
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llTime ))
			return false;
		if(!BER<int >::Store(ppBuf, pdwSize, _obj.m_nCnt ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lPLevel ))
			return false;
		return true;
	}
	static bool Copy(CRefill* _obj, const CRefill& src)
	{
		if(!BER<LONGLONG >::Copy(&(_obj->m_llTime), src.m_llTime))
			return false;
		if(!BER<int >::Copy(&(_obj->m_nCnt), src.m_nCnt))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lPLevel), src.m_lPLevel))
			return false;
		return true;
	}

};

template<>
class BER<CGamePlayTime >
{
public:
	static DWORD Size(const CGamePlayTime& _obj)
	{
		DWORD dwSize = 0;
		dwSize += BER<LONGLONG >::Size(_obj.m_llPlayTime);
		dwSize += BER<LONGLONG >::Size(_obj.m_llJoinTime);
		dwSize += BER<LONGLONG >::Size(_obj.m_llTotalPlayTime);
		dwSize += BER<LONGLONG >::Size(_obj.m_llFirstPlayDate);
		dwSize += BER<LONGLONG >::Size(_obj.m_llLastLogonData);
		dwSize += BER<LONG >::Size(_obj.m_lTotalCnt);
		dwSize += BER<LONG >::Size(_obj.m_lTodayCnt);
		return dwSize;
	}

	static bool Load(CGamePlayTime* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONGLONG >::Load(&(_obj->m_llPlayTime), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llJoinTime), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llTotalPlayTime), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llFirstPlayDate), ppBuf, pdwSize))
			return false;
		if(!BER<LONGLONG >::Load(&(_obj->m_llLastLogonData), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lTotalCnt), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lTodayCnt), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const CGamePlayTime& _obj )
	{
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llPlayTime ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llJoinTime ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llTotalPlayTime ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llFirstPlayDate ))
			return false;
		if(!BER<LONGLONG >::Store(ppBuf, pdwSize, _obj.m_llLastLogonData ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lTotalCnt ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lTodayCnt ))
			return false;
		return true;
	}
	static bool Copy(CGamePlayTime* _obj, const CGamePlayTime& src)
	{
		if(!BER<LONGLONG >::Copy(&(_obj->m_llPlayTime), src.m_llPlayTime))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llJoinTime), src.m_llJoinTime))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llTotalPlayTime), src.m_llTotalPlayTime))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llFirstPlayDate), src.m_llFirstPlayDate))
			return false;
		if(!BER<LONGLONG >::Copy(&(_obj->m_llLastLogonData), src.m_llLastLogonData))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lTotalCnt), src.m_lTotalCnt))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lTodayCnt), src.m_lTodayCnt))
			return false;
		return true;
	}

};

};

#endif //!