/* file : Recv_fromDC.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 15:51:20
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDBQuery.h"
#include "PlugIn_DBCache.h"
#include "base/Random.h"
#include "Interface/db/jidb.h"

using namespace nMech::nDB;


#define READ_PACKET_fromDC(X) READ_PACKET(X);nswb1024_t buf;

#define READ_PACKET_fromDC_User(X) READ_PACKET_fromDC(X);\
	jPlayerDBSM* pUser=0; \
	jDB_CODE_START()\
	pUser = g_PS.find(Data.pid);\
	if(!pUser) throw jError(SR_t(X),CR_t(DQ_user_pid_not_found));\



jDBQ_EVENT_RECEIVER(DC2DQ_CONNECT)//PlugIn_DBCache* pDC, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_fromDC(DC2DQ_CONNECT);//Data, buf
	pDC->m_ProcessID= (DWORD)Data.processid;
	jAssert0(sizeof(DWORD)  == sizeof(uint32));
	jNET_SEND2(g_PS,DQ2DC_CONNECT_OK,jError(0,0) ,(int32)GetCurrentProcessId());

}


jDBQ_EVENT_RECEIVER(DQ_ECHO)//PlugIn_DBCache* pDC, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_fromDC(DQ_ECHO);//Data, buf
	jNET_SEND2(g_PS,DQ_ECHO,Data);
}


jDBQ_EVENT_RECEIVER(DC2DQ_USER_LOGIN)//PlugIn_DBCache* pDC, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_fromDC_User(DC2DQ_USER_LOGIN);//Data, buf,jPlayerDBSM*pUser, WCHAR szSQL[2048];

#if 1
#define jLAMDA_q_DC2DQ_USER_LOGIN(X,Z) X(TCHAR*,ret) Z(jPlayerDBSM*, pUser)
	jLAMDA_begin2(q_DC2DQ_USER_LOGIN,jISqlJob);
	void Bind(jISqlParameter* pSP) 
	{
		jAssert0(pSP->Bind(SP_IN, pUser->m_User.Get_name()));
		jAssert0(pSP->Bind(SP_IN, L"NULL"));
		jAssert0(pSP->Bind(SP_OUT, ret, 256) );
	}
	void Fetch(jISqlRecord* pR)
	{
		if(pR->Next())
		{
			//Use_User_jSQLGetData(pR,pUser->m_User);
		}
	}
	jLAMDA_end();

	fname_t ret;
	g_pDB->RunSQL(_T("{call Login_Use_User(?,?,?)}"), &q_DC2DQ_USER_LOGIN(ret,pUser) );
	jNET_SEND2(g_PS,DQ2DC_USER_LOGIN_RESULT, Data.pid, e);
#endif

	jDB_CODE_END_AUTO(eEAT_NOTIFY_TO_CLIENT);

}

void make_default_Hero(IN jPlayerDBSM* pUser, IN Sys_Hero* pH , OUT Use_Hero* pHero);

jDBQ_EVENT_RECEIVER(DC2DQ_GET_TOWN_LIST)//PlugIn_DBCache* pDC, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_fromDC_User(DC2DQ_GET_TOWN_LIST);//Data, buf ,jPlayerDBSM*pUser, WCHAR szSQL[2048];
#ifdef TSERVER_PREPARE
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
			jWARN1(_T(#table) _T(" 데이타 비정상. : user(%s)"),jT(pUser->m_szID));\
				break;\
			}\
			nODBC::jPatcher p(hstmt);\
			_jJOIN_3(Use_,table,_jSQLGetData)(p,pUser->m_##table[pUser->m_iTot##table]);\
			++pUser->m_iTot##table;\
		}\
		jLOG1(_T("%s : load count : %d"),jS(table) , pUser->m_iTot##table);\
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
			jWARN("error : DEFAULT HERO REGIST ERROR : DB" );
		}
*/
	}
#endif //TSERVER_PREPARE
	jDB_CODE_END_AUTO(eEAT_NOTIFY_TO_CLIENT);

	jNET_SEND2(g_PS,DQ2DC_SEND_TOWN_LIST, Data.pid, e);
}


jDBQ_EVENT_RECEIVER(DC2DQ_TOWN_CREATE)//PlugIn_DBCache* pDC, BYTE*pReadBuff,jPacketNum_t dwLen
{
#ifdef TSERVER_PREPARE
	READ_PACKET_fromDC_User(DC2DQ_TOWN_CREATE);//Data, buf, jPlayerDBSM*pUser, WCHAR szSQL[2048];

	jw_sprintf(szSQL, L"exec Insert_Use_Channel %I64d , %d , %d, N'%s'", pUser->Get_db_uid().m_db_id, Data.csid ,Data.tpsid, Data.name );
	jSQL_RUN(szSQL); // SQLHSTMT hstmt, SQLRETURN sqlRet
	if( (sqlRet = SQLFetch(hstmt)) == SQL_SUCCESS || sqlRet== SQL_SUCCESS_WITH_INFO )
	{
		nODBC::jPatcher p(hstmt);
		Use_Channel* pChannel  = pUser->m_Channel + pUser->m_iTotChannel;
		Use_Channel_jSQLGetData(p,*pChannel);
		++pUser->m_iTotChannel;
		
		if(pUser->m_iTotChannel==1)
		{// 최초 생성되는 마을이다.
			assert(pUser->m_iTotHero==1);
			pUser->m_Hero[0].Set_tuid(pChannel->Get_tuid());
#if 0
			jw_sprintf(szSQL, L"UPDATE Use_Hero SET [tuid]=%I64d WHERE [huid] = %I64d "
				, pChannel->Get_tuid().m_db_id , pUser->m_Hero[0].Get_huid().m_db_id);
			jSQL_RUN(szSQL);
#endif
		}
	}
	else
	{
		// throw를 하지 않는 이유는 로그에 남기지 않기 위해서이다.
		e = jError(SR_t(DC2DQ_TOWN_CREATE),CR_t(EXEC_Select_Use_Channel_imsi_FAIL) );
	}

	jDB_CODE_END();
	if(e.isError())
	{
		jNET_SEND2(g_PS,DQ2DC_TOWN_CREATE_ERROR,Data.pid,e);\
		return;
	}


	
	//pUser->m_iTotChannel : channelid_t는 1부터 시작 한다.
	jNET_SEND2(g_PS,DQ2DC_TOWN_CREATE_OK, Data.pid, pUser->m_iTotChannel);
#endif
}

jDBQ_EVENT_RECEIVER(DC2DQ_TOWN_DELETE)//PlugIn_DBCache* pDC, BYTE*pReadBuff,jPacketNum_t dwLen
{
#ifdef TSERVER_PREPARE

	READ_PACKET_fromDC_User(DC2DQ_TOWN_DELETE);//Data, buf, jPlayerDBSM*pUser, WCHAR szSQL[2048];

	if(pUser->Channel_size() <Data.index || Data.index<=0)
	{
		throw jError(SR_t(TOWN_INDEX_ERROR),CR_t(DC2DQ_TOWN_DELETE));
	}
	jw_sprintf(szSQL, L"exec Delete_Use_Channel @tuid = %I64d",pUser->Channel_at(Data.index)->Get_tuid().m_db_id);
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

	jDB_CODE_END_AUTO(eEAT_NOTIFY_TO_CLIENT);
	jNET_SEND2(g_PS,DQ2DC_TOWN_DELETE_OK, Data.pid, Data.index);
#endif
}





jDBQ_EVENT_RECEIVER(DC2DQ_USER_DISCONNECT)//PlugIn_DBCache* pDC, BYTE*pReadBuff,jPacketNum_t dwLen
{
#ifdef TSERVER_PREPARE

	READ_PACKET_fromDC(DC2DQ_USER_DISCONNECT);//Data, buf, WCHAR szSQL[2048];
	WCHAR szSQL[2048*2];

	jPlayerDBSM* pUser=0;

	for(int i=0; i< Data.pid.size(); ++i)
	{

		jDB_CODE_START();
		{
			pUser = pDLL->find(Data.pid[i]);

			if(!pUser || pUser->m_eUsingState!= jPlayerDBSM::eNOW_DELETING) 
			{
				fname_t szBuf;
				jWARN("!pUser || pUser->m_eUsingState!=eNOW_DELETING : %s", ToString(Data.pid[i],szBuf) );
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

			for(int i=0; i< pUser->m_iTotChannel; ++i)
			{
				void make_update_table(WCHAR*szSQL , nAQ::Use_Channel* p);
				nAQ::Use_Channel* p = &pUser->m_Channel[i];
				{
					if(p->Get_tuid().m_db_id==0)	make_Insert_table(szSQL,p);
					else													make_update_table(szSQL,p);
					jAssert0(jt_strlen(szSQL)<ARRAY_SIZE(szSQL));
					jSQL_RUN(szSQL);
				}
			}
#endif
		}
		jDB_CODE_END();
		if(e.isError())
		{
			jNET_SEND2(g_PS,DQ_ERROR,e,eEAT_NOTIFY_TO_CLIENT, __FUNCTION__,Data.pid[i]);
		}
	}

	//pDLL->WritePacket(WRITE_DQ2DC_USER_LOGIN_RESULT(buf, Data.pid, e));
	for(int i=0; i< Data.pid.size(); ++i)
	{
		pUser = pDLL->find(Data.pid[i]);
		if(!pUser )
		{
			jWARN("user not found : %I64d", Data.pid[i].m_id);
		}
		else if( pUser->m_eUsingState!=jPlayerDBSM::eNOW_DELETING)
		{
			jWARN("user state is not eNOW_DELETING : %s(%I64d)", pUser->m_szID, Data.pid[i].m_id);
		}
		else
		{
			pUser->m_eUsingState = jPlayerDBSM::eNOT_USE;
		}
	}
#endif
}


/* *_* by icandoit : 2009-08-25 22:03:17

jDBQ_EVENT_RECEIVER(aaa)//PlugIn_DBCache* pDC, BYTE*pReadBuff,jPacketNum_t dwLen
{
	READ_PACKET_fromDC_User(aaa);//Data, buf, jPlayerDBSM*pUser, WCHAR szSQL[2048];

	jw_sprintf(szSQL, L"exec USER_LOGIN_SESSION @user_name = N'%s', @user_pwd = N'NULL'", jW(pUser->m_szID) );
	jSQL_RUN(szSQL); // SQLHSTMT hstmt, SQLRETURN sqlRet

	jDB_CODE_END_AUTO(eEAT_NOTIFY_TO_CLIENT);
	//jNET_SEND2(g_PS,DQ2DC_USER_LOGIN_RESULT, Data.pid, e);
}


*/ //*_* by icandoit : 2009-08-25 22:03:18
