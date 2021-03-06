/* file : cmd_Central.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-04 20:38:12
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TCentral.h"

#if 0

#define jLAMDA_jxGet_server_list(X,Z) \
	X(EServerType ,eType)\
	Z(vector<tstring>&,servers)
jLAMDA_for_each(jxGet_server_list, jIGridNode*)
{
	jSI(it);
	name1024_t buf;
	if(eType != EServerType_END &&  !si->IsServer(eType) ) 
		return;
	servers.push_back(ToString(si,buf));
}
jLAMDA_end();


#define jLAMDA_jxGet_server_list_by_world(X,Z) \
	X(tcstr ,szWorld)\
	Z(vector<tstring>&,servers)
jLAMDA_for_each(jxGet_server_list_by_world, jIGridNode*)
{
	jSI(it);
	name1024_t buf;
	if( jt_strcmp(si->m_szDomain , szWorld)) return;
	servers.push_back(ToString(si,buf));
}
jLAMDA_end();


namespace __gm__
{
	jCONSOLE_CMD_AUTO(jSERVER_NAME , world,0,"print world","<file | con> [world_name] [file_tag]")
	{
		#define jCONSOLE_PARAM_world(X,Y) X(outType,tcstr) Y(world_name,tcstr,0) Y(file_tag,tcstr,0)
		jCONSOLE_PARAM_END(world);
		jPS_ret(false);

		vector<tstring> servers;

		if(!world_name)
		{
			jIE* it = pPS->m_eServers->begin();
			jrFOR(it)
			{
				if( it->IsName(jS(UserServer)) || it->IsName(jS(LoginServer)) ) continue;
				servers.push_back(it->GetTagName());
			}
		}
		else
		{
			pPS->for_each(jxGet_server_list_by_world(world_name,servers));
			std::sort(servers.begin(), servers.end());
		}
		
		return g_TCommon.output_string_to_file_or_con(outType, jS(world_list), file_tag, servers);
	}

	jCONSOLE_CMD_AUTO(jSERVER_NAME , server_list,0,"print server list","<file | con> <all | L | T | D | DC | M | U | T> [file_tag]")
	{
		#define jCONSOLE_PARAM_server_list(X,Y) X(outType,tcstr) X(serverTag,tcstr) Y(file_tag,tcstr,0)
		jCONSOLE_PARAM_END(server_list);
		jPS_ret(false);

		vector<tstring> servers;
		EServerType eType = jServerInfo::GetServerTypeByTag(serverTag);
		pPS->for_each(jxGet_server_list(eType,servers));
		std::sort(servers.begin(), servers.end());

		if(tstring(outType)==jS(file))
		{
			fname_t szFileName;
			fname_t szOutFile;
			if(file_tag)
				js_sprintf(szOutFile, _T("server_list_%s"), file_tag);
			else
				js_sprintf(szOutFile, _T("server_list"));

			FILE* fp = g_TCommon.open_file_for_console_cmd_logging(szOutFile,szFileName);
			if(!fp) return false;
			jt_fprintf(fp, _T("Get_PacketUsage : %I64d\n") , g_TCommon.Get_PacketUsage() );

			jFOR_EACH(servers, vector_string_to_file(fp));
			fclose(fp);

			g_TCommon.file_open_by_notepad(szFileName, !(file_tag&&jt_strlen(file_tag)) );
			return true;
		}
		if(tstring(outType)==jS(con))
		{
			jLOG1(_T("Get_PacketUsage : %I64d") , g_TCommon.Get_PacketUsage() );
			jFOR_EACH(servers, vector_string_to_console());
			return true;
		}
		return false;
	}

	//jCONSOLE_CMD_AUTO(jSERVER_NAME,notice,0,"notice send","<type> <msg> [color] [reserve_min] [repeat_count]")
	jCONSOLE_CMD_AUTO(jSERVER_NAME,notice,0,"notice send","<type> <msg> [T | D | ALL | sid] [color]")
	{
#define jCONSOLE_PARAM_gm_notice(X,Y) X(iType,int) X(szMsg,tcstr) X(serverTag,tcstr) Y(color,int,0)
		jCONSOLE_PARAM_END(gm_notice);
		jPS_ret(false);

		nswb1024_t buf;
		tstring msg = szMsg;
		nSTL::replace(msg,_T("_"), _T(" "));
		jNoticeInfo info;
		jCLEAR(info);
		info.type = iType;
		info.color = color;

		jPacket_Base pk = nCentralServer::WRITE_C2_NOTICE(buf, info ,jW(msg.c_str()),"");

		tstring sTag  = serverTag;
		bool isChecked =false;
		if( sTag == _T("T") || sTag == _T("ALL"))			
		{
			isChecked =true;
			pPS->for_each(jxSendToServers(pk,eChannel,0));
		}
		if( sTag == _T("D") || sTag == _T("ALL"))		
		{
			isChecked =true;
			pPS->for_each(jxSendToServers(pk,eGame,0));
		}
		if(!isChecked )
		{
			jIGridNode* it = pPS->find_if(jxFindServer(jt_atoi(serverTag)));
			if(it) 
				it->Write_Packet(pk);
		}
		return true;
	}

	jCONSOLE_CMD_AUTO(jSERVER_NAME,log_console,0,"On/off log excepted waring/error","<bool> <all | C | L | T | D | DC | M | U | T>")
	{
#define jCONSOLE_PARAM_log(X,Y) X(is,bool) X(serverTag,tcstr)
		jCONSOLE_PARAM_END(log);

		jPS_ret(false);
		nswb1024_t buf;
		jPacket_Base pk = nCentralServer::WRITE_C2_SERVER_LOG_LEVEL(buf, jS(console), is);

		tstring sTag = serverTag;
		if(sTag ==jS(all))
		{
			jSET_CON_FLAG(exe,LOG_OFF,true);
			g_SG.WritePacket(pk);
		}
		else if(sTag ==jS(C))
		{
			jSET_CON_FLAG(exe,LOG_OFF,true);
		}
		#define set_log_byserver(name,idStart,TAG)\
		else if( sTag == _T(#TAG) ){pPS->for_each(jxSendToServers(pk,eChannel,0));}
		for_each_SERVER_TYPE_F(set_log_byserver)
		for_each_SERVER_TYPE_B(set_log_byserver);
		return true;
	}

#if 0

	jCONSOLE_CMD_AUTO(jSERVER_NAME,notice_file,0,"send notice from tag in xml file","<r:\\xml\\TNotice.xml> [tag]")
	{
		jCENTRAL_ret(pP,false);
		jID* pD = GetjIXml()->Load(arg[0].c_str());
		if(!pD)
		{
			jWARN1(_T("notice file not found : %s"),arg[0].c_str());
			return false;
		}

		try
		{
			jIE* pE = pD->BaseI()->begin();
			if(arg.size()>=2)
			{
				pE = pD->Find(arg[1].c_str());
				if(!pE)
				{
					jWARN1(_T("notice file category(%s) not found : "),arg[1].c_str());
					throw false;
				}
			}
			pPS->Send__C2_NOTICE(pE);

			if(pD)
				GetjIXml()->UnLoad(pD);
			return true;
		}
		catch(...)
		{
		}

		if(pD)
			GetjIXml()->UnLoad(pD);
		return false;

	}

	jCONSOLE_CMD_AUTO(jSERVER_NAME,user,0,"Print user info @gm.user name test12 @gm.user uid 1234 @gm.user kick 1234","<count | nickname | uid | kick > [user_nickname]")
	{
		jCENTRAL_ret(pP,false);
		if(arg[0]==_T("count"))
		{
			jLOG1(_T("user.count = %d") , pPS->m_UserZoneList.size() );
			return true;
		}
		if(arg[0]==jS(kick))
		{
			//userdb_id_t uid = jt_atoi(arg[1].c_str());
			if( arg.size() < 2)
				return false;

			jPlayerBase* pUser = pPS->Find_NickName(jW(arg[1].c_str()));
			if(!pUser) return false;		

			pPS->Do_Disconnect_User(pUser->m_udb);
			return true;
		}
		if(arg[0]==_T("name"))
		{
			if(arg.size()<2) 
			{
				jLOG1(_T("USE: @gm.user name test12"));
				return false;
			}

			jPlayerBase* pUser = pPS->Find_NickName(jW(arg[1].c_str()));
			if(!pUser)
			{
				jLOG1(_T("user not found: %s") , arg[1].c_str() );
				return false;
			}
			tname1024_t buf;
			jLOG1(ToString(pUser, buf));
			return true;
		}
		if(arg[0] == _T("uid"))
		{
			if(arg.size()<2) 
			{
				jLOG1(_T("USE: @gm.user uid 1234"));
				return false;
			}
			userdb_id_t uid = jt_atoi(arg[1].c_str());
			jPlayerBase* pUser = pPS->Find_User(uid);
			if(!pUser)
			{
				jLOG1(_T("user not found : %s"), arg[1].c_str() );
				return false;
			}
			tname1024_t buf;
			jLOG1(ToString(pUser, buf));
			return true;
		}
		return false;
	}





#endif
}//namespace __gm__

#if 0
namespace __server__
{
	jCONSOLE_CMD_AUTO(jSERVER_NAME,console_cmd,0,"서버들에게 jConsoleCmd를 실행시킨다.공백있으면안됨"
		,"<L|LG|R|ALL> <category> <cmd> [1] [2] [3] [4] [5] [6] [7] [8]")
	{
		vector<tstring> send_arg;
		for(int i=3; i<arg.size(); ++i)
		{
			send_arg.push_back(arg[i]);
		}

		nswb2048_t buf;
		jPacket_Base pk = nCentralServer::WRITE_C2_RUN_CONSOLE_CMD(buf, arg[1].c_str(), arg[2].c_str(), send_arg);

		jCENTRAL_ret(pP,false);
		if(!g_SG.Send_Packet_ToServers(arg[0],pk))
		{
			serverid_t sid = jt_atoi(arg[0].c_str());
			if(!sid)
			{
				jIGridNode* pFServer= g_SG.find_if(jxFindServer(sid));
				if(!pFServer)  return false;
				pFServer->Write_Packet(&pk);
				return true;
			}
			return false;
		}
		return true;
	}

	jCONSOLE_CMD_AUTO(jSERVER_NAME, chat_list,0,"View lobby  chat list ","<isPublic> <file | console> [file_tag]")
	{
#define jCONSOLE_PARAM_chat_list(X,Y) 	X(isPublic,bool) X(szFile,tcstr) Y(file_tag,tcstr,0)
		jCONSOLE_PARAM_END(chat_list);

		return false;
	}

	jCONSOLE_CMD_AUTO(jSERVER_NAME, room_list,0,"View gameroom list","<isFileOpen>")
	{
#define jCONSOLE_PARAM_room_list(X,Y) X(isFileOpen,bool)
		jCONSOLE_PARAM_END(room_list);

		jCENTRAL_ret(pP,false);
#define jLAMDA_jxGet_gameroom_list(X,Z) \
	Z(vector<tstring>&,rooms)
		jLAMDA_for_each(jxGet_gameroom_list, jGameRoomDataCache&)
		{
			name1024_t buf;
			rooms.push_back(ToString(&it,buf));
		}
		jLAMDA_end();

		vector<tstring> rooms;
		g_SG.m_GameRoomCache.for_each(jxGet_gameroom_list(rooms));

		std::sort(rooms.begin(), rooms.end());

		fname_t szOutFile;
		FILE* fp = g_TCommon.open_file_for_console_cmd_logging(_T("game_list"),szOutFile);
		if(!fp) return false;

		jt_fprintf(fp, _T("rooms=%d\n"),rooms.size());
		jFOR_EACH(rooms, vector_string_to_file(fp));
		fclose(fp);

		g_TCommon.file_open_by_notepad(szOutFile, isFileOpen);
		return true;
	}

}//namespace __server__

#endif

#endif