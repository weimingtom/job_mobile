// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define jSERVER_NAME test_Server
#define jsSERVER_NAME _T("test_Server")

#include "../TestCommon/TestCommon.h"


#define _xmlid_LIST(X)\
	X(TestServer_DLL)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(func)\
	func(TestServer,TEST_ID_START_NUM,500,0,"Test Account start number")\
	func(TestServer,DummyCount,50,0,"default TestClient Dummy count ")\
	func(TestServer,DefaultLoginIP,_T("127.0.0.1"), 0,"Default AqLoginServer IP")\
	func(TestServer,DefaultLoginPort ,33100,0,"default AqLoginServer Port")\
	func(TestServer,TEST_ID_NAME,_T("test"),0,"test user id start name")\


var_enum(jCV_DECLARE);



#define READ_PACKET_TS(X) READ_PACKET(X);\
	PlugIn_ToFrontEnd*pFE = (PlugIn_ToFrontEnd*)pPlugIn;if(!pFE) return;\
	nswb1024_t buf;\
	AqTestClientNode* pUser= pFE->get_user(pS);\
	if(!pUser){jWARN(_T(#X) _T(" pUser==NULL"));	return;}\


