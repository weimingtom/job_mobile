/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqConnectedServerNode)
{

	int i=0;
	++i;
}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd)
{

}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqConnectedServerNode);


PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
{
}

bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCommand)
{
	//nswb1024_t buf;
	std::tstring str = _T("FromAqCentral:");
	str += szCommand;
	net_string256 sendStr = str.c_str();
	//jPacket_Base pk = nTestCentralServer::WRITE_TS_ECHO(buf, sendStr );
	//jIPacketSocket_IOCP* p =0;
	//send_all(&pk, p );	
	return false;
}

void jSocketDebugger(jIPacketSocket_IOCP* pS)
{

}



// CIocp의 가상함수들
serverid_t jSERVER_sid()
{ 
	jBE_ret(0);
	while(!pBE->m_sid);
	return pBE->m_sid;
}
//serverid_t jSERVER_sid(){ jBE_ret(0);while(!pBE->m_sid){};return pBE->m_sid;}
VOID PlugIn_ToFrontEnd::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromServer(DC_HELLO);//AqConnectedServerNode* pServer;nswb256_t buf; fname_t szIP
}

VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //AqConnectedServerNode* pServer
	
	erase(pServer);
}
