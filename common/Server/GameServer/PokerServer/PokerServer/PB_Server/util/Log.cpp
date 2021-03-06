//------------------------------------------------------------------------------------
// Module Name			: Log(.cpp)
// First Modified Date	: 2010/07/16
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: A log class work with file.
//------------------------------------------------------------------------------------
#include "stdafx.h"
#include "Log.h"

//------------------------------------------------------------------------------------
CLog& _LOG()
//------------------------------------------------------------------------------------
{
	static CLog log;
	return log;
}
//------------------------------------------------------------------------------------
CLog::CLog()
//------------------------------------------------------------------------------------
{
	CreateLogFile();
}
//------------------------------------------------------------------------------------
CLog::~CLog()
//------------------------------------------------------------------------------------
{
	if ( m_hLog!=NULL )
		CloseHandle( m_hLog );
}
//------------------------------------------------------------------------------------
void CLog::CreateLogFile()
//------------------------------------------------------------------------------------
{
	m_hLog=CreateFile( _T("ProjectLog.txt"), GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0 );
	if ( ! m_hLog )
	{
		return;
	}
}
//------------------------------------------------------------------------------------
void CLog::SetLog( std::string message )
//------------------------------------------------------------------------------------
{
	DWORD dwWritten;
	if ( m_hLog )
	{
		WriteFile( m_hLog, message.c_str(), static_cast<DWORD>(message.length()), &dwWritten, NULL );
	}
	else
	{
	}
}