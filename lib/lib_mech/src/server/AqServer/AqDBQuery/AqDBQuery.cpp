// AqQuery.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "AqDBQuery.h"
#include "network/protocal/PT_DBQueryServer_Enum.h"
using namespace nDBQueryServer;

//void Use_Town_jSQLGetData(nODBC::jPatcher& p,nAQ::Use_Town& d){for_each_nAQ_Use_Town_STRUCT_FIELD(excel_jSQLGetData);}
#define jSQLGetData_UseTABLE_def432(table,help,root_ns,ns) \
	void table##_jSQLGetData ( jISqRecord* pR, ns::table& d){_jJOIN_3(for_each_nAQ_,table,_STRUCT_FIELD)(excel_jSQLGetData);}

#define def_xls_getDatafunc234(files) _jJOIN_3(for_each_nAQ_,files,_Use_STRUCT_LIST)(jSQLGetData_UseTABLE_def432);
for_each_excel_file_list(def_xls_getDatafunc234);

_jDBEventNode* g_func[PT_DBQueryServer_END];
void _jRegistNamedPointer(int num, _jDBEventNode* v)
{
	g_func[num] = v;
}
nMech::nDB::jISafeDB*	g_pDB=0;
Aq_NetDLL* g_pjConsoleDLL=0;

jIPlugIn_Connection* g_pCurrPlugInBE=0;

extern "C"
{
	__declspec(dllexport) void* jCreateInterface(jIE* pE)
	{
		init_common_AQ();
		//jCSV_Manager::Get()->Load_CSV();

		if(g_pjConsoleDLL)return g_pjConsoleDLL;
		//nInterface::g_pjINet_OGS->RunMessageThread();
		//nInterface::g_pjINet_OGS->SetCallback_PacketSize_UsageInfo(_OnPacketSize_UsageInfo);

		g_pjConsoleDLL = new Aq_NetDLL();
		g_pDB = jCREATE_INTERFACE(nMech::nDB::jISafeDB);
		

		return g_pjConsoleDLL;

	}
	__declspec(dllexport) void jDeleteInterface()
	{
		SAFE_RELEASE(g_pDB);
		SAFE_DELETE(g_pjConsoleDLL);
	}
	__declspec(dllexport) acstr jGetModuleOwnerName()
	{
		return "icandoit";
	}

}


bool Aq_NetDLL::ParseCmd(tcstr szCommand) 
{
	if( parent_t::ParseCmd(szCommand) ) return true;
	//여기에 코드를 추가하시오

	return false;
}
HANDLE g_hThread_run_dq;
static unsigned __stdcall _run_dq( void* pThreadParam)
{
	Aq_NetDLL* pAq_NetDLL= (Aq_NetDLL*)pThreadParam;

	jNamedEventTable* pPHT = (jNamedEventTable*)nMech::jBase::FindNamedPointer(_T("nNET"),_T("DBQueryServer") );

	nswb1024_t buf;
	pAq_NetDLL->WritePacket(WRITE_DQ2DC_CONNECT(buf
		,pv_WORLD_NAME->Get_cstr()
		,pv_SM_QUERY2CACHE_NAME->Get_cstr()
		,pv_SM_CACHE2QUERY_NAME->Get_cstr()
		,pv_SM_USER_INFO_NAME->Get_cstr()
		,pv_GAMEDB_NAME->Get_cstr()
		));

	nMech::nUtil::nSharedMem::jPacket_Base pk;
	BYTE readBuf[nMech::nUtil::nSharedMem::MAX_PKTSIZE];
	pk.buf = readBuf;

	pAq_NetDLL->m_isQuit=0;
	while(pAq_NetDLL->m_isQuit==0 ) 
	{
		if( !pAq_NetDLL->m_RecvQueue.ReadPacket( pk ) ) 
		{
			Sleep(13);
			continue;
		}

		if(pk.num>=PT_DBQueryServer_END || pk.num <=PT_VERSION	)
		{
			GetjILog()->Warning(_T("Unkown packet recvied : %d"),pk.num );
			continue;
		}
		if(g_func[pk.num])
		{
			g_func[pk.num]->Call(pAq_NetDLL, readBuf, pk.len,0);
		}
		else
		{
			jNamedEventNode* pPHN = pPHT->GetByNum(pk.num);
			GetjILog()->Warning(_T("recv : %s callback is not found"),pPHN->m_szName);
		}
		memset( &readBuf, 0, sizeof(readBuf) );
	}
	pAq_NetDLL->m_isQuit=2;

	_endthread();
	return 0;
}

bool Aq_NetDLL::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
{
	//if(!parent_t::Start(szNetConfigFile,szNetConfig_Name)) return false;

	if(!m_SendQueue.InitailizeMMF( sizeof(nMech::nUtil::nSharedMem::jSmqPacket_UNIT)
		, pv_SM_QUEUE_MAX_COUNT->Get_int(), pv_SM_QUERY2CACHE_NAME->Get_cstr(), FALSE ))
	{
		GetjILog()->Warning(_T("m_SendQueue.InitailizeMMF(%d,%s ,false)error")
			,pv_SM_QUEUE_MAX_COUNT->Get_int()
			,pv_SM_QUERY2CACHE_NAME->Get_cstr());
		return false;
	}

	if(!m_RecvQueue.InitailizeMMF( sizeof(nMech::nUtil::nSharedMem::jSmqPacket_UNIT)
		, pv_SM_QUEUE_MAX_COUNT->Get_int(), pv_SM_CACHE2QUERY_NAME->Get_cstr(), FALSE ))
	{
		GetjILog()->Warning(_T("m_RecvQueue.InitailizeMMF(%d, %s,false) error")
			,pv_SM_QUEUE_MAX_COUNT->Get_int()
			,pv_SM_CACHE2QUERY_NAME->Get_cstr());
		return false;
	}

	if( !m_UsersSM.Init(pv_SM_USER_INFO_NAME->Get_cstr(), pv_SM_USER_MAX->Get_int(), sizeof(jUserZoneInfo_DC)) )
	{
		GetjILog()->Warning(_T("m_UsersSM.Init(%s , %d,sizeof(jUserZoneInfo_DC)) error")
			,pv_SM_USER_INFO_NAME->Get_cstr() 
			,pv_SM_USER_MAX->Get_int());
		return false;
	}

	m_vecUsersMS.resize(pv_SM_USER_MAX->Get_int());
	for(int i = 0; i < pv_SM_USER_MAX->Get_int() ; i++)
	{
		m_vecUsersMS[i] = m_UsersSM.GetUnit(i);
	}
	

	//if(g_pDB->IsOpen())	return false;
	if(!g_pDB->OpenDirect(_T("50.10.250.113,1433\\sam_db"), _T("")
		, pv_GAMEDB_ID->Get_cstr(),pv_GAMEDB_PWD->Get_cstr(),pv_GAMEDB_NAME->Get_cstr(),0,nDB::protoWinSock))
	{
		GetjILog()->Warning(_T("g_pDB->OpenDirect(%s,%s:%s) error"),pv_GAMEDB_NAME->Get_cstr(), pv_GAMEDB_ID->Get_cstr(), pv_GAMEDB_PWD->Get_cstr());
		return false;
	}
	else
	{
		GetjILog()->Log(_T("g_pDB->Open(%s,%s) OK"),pv_GAMEDB_NAME->Get_cstr(), pv_GAMEDB_ID->Get_cstr());
	}

	g_hThread_run_dq = (HANDLE)_beginthreadex(NULL, 0, _run_dq, this, 0, 0);
	return true;

}

void Aq_NetDLL::End() 
{
	m_isQuit=1;
	while(m_isQuit!=2)
	{
		printf(".");
	}
	CloseHandle(g_hThread_run_dq);
	//parent_t::End();
}


jUserZoneInfo_DC* Aq_NetDLL::find_by_yhandle(userid_t uid)
{
	if(uid.m_dc_handle >= m_vecUsersMS.size())
	{
		return 0;
	}
	return m_vecUsersMS[uid.m_dc_handle];
}


namespace nMech
{
	namespace nODBC
	{
		int jSQLGetData(jISqRecord* pR,db_uid_type& val, int)
		{
			++p.m_iCol;
			SQLRETURN ret = SQLGetData(p.m_hstmt, p.m_iCol , SQL_C_SBIGINT, &val.m_db_id, 0 , &p._cbParmRet);
			return p._cbParmRet;
		}

		#define jSQLGetData_ENUM_TABLE_def(enum_tbl,help,root_ns,ns) \
		int jSQLGetData(jPatcher& p,ns::enum_tbl& _val, int)\
		{\
			++p.m_iCol;	int8 val;\
			SQLRETURN ret = SQLGetData(p.m_hstmt, p.m_iCol , SQL_C_TINYINT, &val, 0 , &p._cbParmRet);\
			_val = (ns::enum_tbl)val;\
			return p._cbParmRet;\
		}


		#define decl_xls_jSQLGetData767(files) _jJOIN_3(for_each_nAQ_,files,_ENUM)(jSQLGetData_ENUM_TABLE_def);
		for_each_excel_file_list(decl_xls_jSQLGetData767);


	}
}

