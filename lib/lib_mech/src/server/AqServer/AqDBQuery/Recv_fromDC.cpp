/* file : Recv_fromDC.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 15:51:20
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqDBQuery.h"
#include "base/Random.h"


jDBQ_EVENT_RECEIVER(DC2DQ_CONNECT)// Aq_NetDLL* pDLL, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_DQ(DC2DQ_CONNECT);//Data, buf
	GetjILog()->Log(_T("DC2DQ_CONNECT\n"));
	pDLL->WritePacket(WRITE_DQ2DC_CONNECT_OK(buf,jError(0,0) ));
}


jDBQ_EVENT_RECEIVER(DQ_ECHO)//Aq_NetDLL* pDLL, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_DQ(DQ_ECHO);//Data, buf
	pDLL->WritePacket(WRITE_DQ_ECHO(buf,Data));
}


jDBQ_EVENT_RECEIVER(DC2DQ_USER_LOGIN)//Aq_NetDLL* pDLL, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_DQ_U(DC2DQ_USER_LOGIN);//Data, buf,jUserZoneInfo_DC*pUser, WCHAR szSQL[2048];

#define jLAMDA_q_DC2DQ_USER_LOGIN(X,Z) X(aname32_t , ret) X(jUserZoneInfo_DC*, pUser) ,Z(S_DC2DQ_USER_LOGIN&,Data)
	jLAMDA_begin2(q_DC2DQ_USER_LOGIN,jISqlJob);
	void Bind(jISqlParameter* pSP) 
	{
		jAssert0(pSP->Bind(1, SP_IN, Data.uid));
		jAssert0(pSP->Bind(2, SP_IN, L"NULL"));
		jAssert0(pSP->Bind(1, SP_OUT, ret, _countof(ret)) );
	}
	void Fetch(jISqRecord* pR)
	{
		if(pR->Next())
		{
			Use_User_jSQLGetData(pR,pUser->m_User);
		}
	}
	jLAMDA_end();
	g_pDB->RunSQL(_T("{call Login_Use_User(?,?,?)}"), &q_DC2DQ_USER_LOGIN(pUser,Data) );
	pDLL->WritePacket(WRITE_DQ2DC_USER_LOGIN_RESULT(buf, Data.uid, e));
}

void make_default_Hero(IN jUserZoneInfo_DC* pUser, IN Sys_Hero* pH , OUT Use_Hero* pHero);

jDBQ_EVENT_RECEIVER(DC2DQ_GET_TOWN_LIST)//Aq_NetDLL* pDLL, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_DQ_U(DC2DQ_GET_TOWN_LIST);//Data, buf ,jUserZoneInfo_DC*pUser, WCHAR szSQL[2048];

#define User_table_load_DB34(table)\
	{\
		jw_sprintf(szSQL, L"exec Load_Use_%s %I64d", _T(#table),pUser->Get_db_uid().m_db_id);\
		jSQL_RUN(szSQL);\
		memset(pUser->m_##table, 0, sizeof(pUser->m_##table));\
		pUser->m_iTot##table=0;\
		while( (sqlRet = SQLFetch(hstmt)) == SQL_SUCCESS || sqlRet== SQL_SUCCESS_WITH_INFO )\
		{\
			if(pUser->m_iTot##table>=iMAX_USER_##table)\
			{\
			GetjILog()->Warning(jFUNC1 _T(#table) _T(" 데이타 비정상. : user(%s)"),jT(pUser->m_szID));\
				break;\
			}\
			nODBC::jPatcher p(hstmt);\
			_jJOIN_3(Use_,table,_jSQLGetData)(p,pUser->m_##table[pUser->m_iTot##table]);\
			++pUser->m_iTot##table;\
		}\
		GetjILog()->Log(_T("%s : load count : %d"),jS(table) , pUser->m_iTot##table);\
	}\

	for_each_User_table(User_table_load_DB34);

	if(pUser->m_iTotHero==0)
	{
		// 디펄트 장수 생성.
		int rd = nUtil::Randomi(1,jCSV(Sys_Hero).size() );
		Sys_Hero* pH = jCSV(Sys_Hero).at(rd);
		Use_Hero* pHero = pUser->m_Hero+0;
		make_default_Hero(pUser, pH, pHero);
		++pUser->m_iTotHero;

/*
		나중에 일괄적으로 DB에 업데이트 시킬것이기 때문.
		jw_sprintf(szSQL, L"exec Insert_Use_Hero %d  ,%I64d", pHero->Get_hsid() , pHero->Get_uid().m_db_id);
		jSQL_RUN(szSQL);
		if( (sqlRet = SQLFetch(hstmt)) == SQL_SUCCESS || sqlRet== SQL_SUCCESS_WITH_INFO )
		{
			nODBC::jPatcher p(hstmt);
			Use_Hero_jSQLGetData(p,*pHero);
			++pUser->m_iTotHero;
		}
		else
		{
			GetjILog()->Warning(jFUNC1 _T("error : DEFAULT HERO REGIST ERROR : DB") );
		}
*/
	}

	db_code_end_auto(eSEND_jError_ToClient);

	pDLL->WritePacket(WRITE_DQ2DC_SEND_TOWN_LIST(buf, Data.uid, e));
}


jDBQ_EVENT_RECEIVER(DC2DQ_TOWN_CREATE)//Aq_NetDLL* pDLL, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_DQ_U(DC2DQ_TOWN_CREATE);//Data, buf, jUserZoneInfo_DC*pUser, WCHAR szSQL[2048];
	jw_sprintf(szSQL, L"exec Insert_Use_Town %I64d , %d , %d, N'%s'", pUser->Get_db_uid().m_db_id, Data.csid ,Data.tpsid, Data.name );
	jSQL_RUN(szSQL); // SQLHSTMT hstmt, SQLRETURN sqlRet
	if( (sqlRet = SQLFetch(hstmt)) == SQL_SUCCESS || sqlRet== SQL_SUCCESS_WITH_INFO )
	{
		nODBC::jPatcher p(hstmt);
		Use_Town* pTown  = pUser->m_Town + pUser->m_iTotTown;
		Use_Town_jSQLGetData(p,*pTown);
		++pUser->m_iTotTown;
		
		if(pUser->m_iTotTown==1)
		{// 최초 생성되는 마을이다.
			assert(pUser->m_iTotHero==1);
			pUser->m_Hero[0].Set_tuid(pTown->Get_tuid());
#if 0
			jw_sprintf(szSQL, L"UPDATE Use_Hero SET [tuid]=%I64d WHERE [huid] = %I64d "
				, pTown->Get_tuid().m_db_id , pUser->m_Hero[0].Get_huid().m_db_id);
			jSQL_RUN(szSQL);
#endif
		}
	}
	else
	{
		// throw를 하지 않는 이유는 로그에 남기지 않기 위해서이다.
		e = jError(SR_t(DC2DQ_TOWN_CREATE),CR_t(EXEC_Select_Use_Town_imsi_FAIL) );
	}

	db_code_end();
	if(e.isError())
	{
		pDLL->WritePacket(WRITE_DQ2DC_TOWN_CREATE_ERROR(buf,Data.uid,e));\
		return;
	}


	
	//pUser->m_iTotTown : townid_t는 1부터 시작 한다.
	pDLL->WritePacket(WRITE_DQ2DC_TOWN_CREATE_OK(buf, Data.uid, pUser->m_iTotTown));
}

jDBQ_EVENT_RECEIVER(DC2DQ_TOWN_DELETE)//Aq_NetDLL* pDLL, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_DQ_U(DC2DQ_TOWN_DELETE);//Data, buf, jUserZoneInfo_DC*pUser, WCHAR szSQL[2048];

	if(pUser->Town_size() <Data.index || Data.index<=0)
	{
		throw jError(SR_t(TOWN_INDEX_ERROR),CR_t(DC2DQ_TOWN_DELETE));
	}
	jw_sprintf(szSQL, L"exec Delete_Use_Town @tuid = %I64d",pUser->Town_at(Data.index)->Get_tuid().m_db_id);
	jSQL_RUN(szSQL); // SQLHSTMT hstmt, SQLRETURN sqlRet
#if 0
	if( (sqlRet = SQLFetch(hstmt)) == SQL_SUCCESS || sqlRet== SQL_SUCCESS_WITH_INFO )
	{
	}
	else
	{
		//jTODO jError  아바타 삭제 실패.
		throw jError(SR_t(LOGIN_OSP_ERROR_NormalLogin_CALLBACK),0);
	}
#endif

	db_code_end_auto(eSEND_jError_ToClient);
	pDLL->WritePacket(WRITE_DQ2DC_TOWN_DELETE_OK(buf, Data.uid, Data.index));
}





jDBQ_EVENT_RECEIVER(DC2DQ_USER_DISCONNECT)//Aq_NetDLL* pDLL, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_DQ(DC2DQ_USER_DISCONNECT);//Data, buf, WCHAR szSQL[2048];
	WCHAR szSQL[2048*2];

	jUserZoneInfo_DC* pUser=0;

	for(int i=0; i< Data.uid.size(); ++i)
	{

		db_code_start();
		{
			pUser = pDLL->find_by_yhandle(Data.uid[i]);

			if(!pUser || pUser->m_eUsingState!= jUserZoneInfo_DC::eNOW_DELETING) 
			{
				fname_t szBuf;
				GetjILog()->Warning(jFUNC1 _T("!pUser || pUser->m_eUsingState!=eNOW_DELETING : %s"), ToString(Data.uid[i],szBuf) );
				continue;
			}

			void make_update_table(WCHAR* szSQL,nAQ::Use_User* );
			make_update_table(szSQL,&pUser->m_User);
			jSQL_RUN(szSQL);

#if 0
#define User_table_update434(table)\
			for(int i=0; i< pUser->m_iTot##table; ++i)\
			{\
				nAQ::Use_##table* p= &pUser->m_##table[i];\
				{\
					if(p->Get_fuid().m_db_id==0)	make_Insert_table(szSQL,p);\
					else													make_update_table(szSQL,p);\
					jAssert0(jt_strlen(szSQL)<ARRAY_SIZE(szSQL));\
					jSQL_RUN(szSQL);\
				}\
			}\

			for_each_User_table(User_table_update434);

#else

			for(int i=0; i< pUser->m_iTotHero; ++i)
			{
				void make_update_table(WCHAR*szSQL , nAQ::Use_Hero* p);
				nAQ::Use_Hero* p = &pUser->m_Hero[i];
				{
					if(p->Get_huid().m_db_id==0)	make_Insert_table(szSQL,p);
					else													make_update_table(szSQL,p);
					jAssert0(jt_strlen(szSQL)<ARRAY_SIZE(szSQL));
					jSQL_RUN(szSQL);
				}
			}

			for(int i=0; i< pUser->m_iTotForce; ++i)
			{
				void make_update_table(WCHAR*szSQL , nAQ::Use_Force* p);
				nAQ::Use_Force* p = &pUser->m_Force[i];
				{
					if(p->Get_fuid().m_db_id==0)	make_Insert_table(szSQL,p);
					else													make_update_table(szSQL,p);
					jAssert0(jt_strlen(szSQL)<ARRAY_SIZE(szSQL));
					jSQL_RUN(szSQL);
				}
			}

			for(int i=0; i< pUser->m_iTotTown; ++i)
			{
				void make_update_table(WCHAR*szSQL , nAQ::Use_Town* p);
				nAQ::Use_Town* p = &pUser->m_Town[i];
				{
					if(p->Get_tuid().m_db_id==0)	make_Insert_table(szSQL,p);
					else													make_update_table(szSQL,p);
					jAssert0(jt_strlen(szSQL)<ARRAY_SIZE(szSQL));
					jSQL_RUN(szSQL);
				}
			}
#endif
		}
		db_code_end();
		if(e.isError())
		{
			pDLL->WritePacket(WRITE_DQ_ERROR(buf,e,eSEND_jError_ToClient, __FUNCTION__,Data.uid[i]));
		}
	}

	//pDLL->WritePacket(WRITE_DQ2DC_USER_LOGIN_RESULT(buf, Data.uid, e));
	for(int i=0; i< Data.uid.size(); ++i)
	{
		pUser = pDLL->find_by_yhandle(Data.uid[i]);
		if(!pUser )
		{
			GetjILog()->Warning(jFUNC1 _T("user not found : %I64d"), Data.uid[i].m_id);
		}
		else if( pUser->m_eUsingState!=jUserZoneInfo_DC::eNOW_DELETING)
		{
			GetjILog()->Warning(jFUNC1 _T("user state is not eNOW_DELETING : %s(%I64d)"), pUser->m_szID, Data.uid[i].m_id);
		}
		else
		{
			pUser->m_eUsingState = jUserZoneInfo_DC::eNOT_USE;
		}
	}
}


/* *_* by icandoit : 2009-08-25 22:03:17

jDBQ_EVENT_RECEIVER(aaa)//Aq_NetDLL* pDLL, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_DQ_U(aaa);//Data, buf, jUserZoneInfo_DC*pUser, WCHAR szSQL[2048];

	jw_sprintf(szSQL, L"exec USER_LOGIN_SESSION @user_name = N'%s', @user_pwd = N'NULL'", jW(pUser->m_szID) );
	jSQL_RUN(szSQL); // SQLHSTMT hstmt, SQLRETURN sqlRet

	db_code_end_auto(eSEND_jError_ToClient);
	//pDLL->WritePacket(WRITE_DQ2DC_USER_LOGIN_RESULT(buf, Data.uid, e));
}


*/ //*_* by icandoit : 2009-08-25 22:03:18
