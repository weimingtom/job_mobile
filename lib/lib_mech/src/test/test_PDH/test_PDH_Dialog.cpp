// test_template.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "header/jDefine.h"

#include <windows.h>
#include <pdh.h>
#include <tchar.h>
#include <stdio.h>


#pragma comment(lib, "Pdh.lib")

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