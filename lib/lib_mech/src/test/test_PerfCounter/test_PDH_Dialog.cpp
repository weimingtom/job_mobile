/* file : test_PDH_Dialog.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-02 10:59:27
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"



// PDH Dialog Box가 호출하는 callback 함수
static PDH_STATUS __stdcall pdh_callback(DWORD)
// 팁: 변수 이름을 제거하면 사용되지 않는 변수라는 warning메시지가 사라진다.
{
	return ERROR_SUCCESS;
}

void main_show_pdh_dialog()
{
	// Counter name string을 담을 버퍼 설정
	// PDH_BROWSE_DLG_CONFIG 구조체 초기화
	pdh_init(NULL, &gszReturnPath[0], 1024);
	// PDH Dialog Box 띄움
	PdhBrowseCounters(&pdhconf);
	// PDH가 만들어준 Counter name string 출력
	jt_printf(_T("The counter string is :₩n %s₩n"), gszReturnPath);
}

