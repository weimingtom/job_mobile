/* file : player_id_t.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-08 20:47:44
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __player_iasdfdaf_sdtasfdfa_sdfasdheader__
#define __player_iasdfdaf_sdtasfdfa_sdfasdheader__
#pragma once

namespace nMech
{


	struct player_id_t
	{
		union
		{
			struct 
			{
				union
				{
					struct  
					{
						unsigned int m_w_handle		: 16;//WorldServer yVectorNode handle. �ѿ���� maxuser = 2^16 = 6�� , 2^20 =1�鸸
						unsigned int m_temp			: 6;
						unsigned int m_statCookie	: 1;//���������� �ٲ����� ���� �ٳ�.
						unsigned int m_visualCookie	: 1;// ������� �ٲ����� ���� �ٳ�.
						unsigned int m_w_sid		: 8; //world server  sid   
					};
					nMech::uint32 m_wid32;//world handle
				};
				union
				{
					struct 
					{
						nMech::uint16 m_dc_handle;//dbcache shared memory handle. �� DBĳ���� maxuser= 2^16 = 6��
						serverid_t	  m_dc_sid;//dbcache server sid
					};
					nMech::uint32 m_did;
				};
			};
			nMech::int64 m_id;
		};
		inline bool IsEqualVisualCookie(player_id_t _uid){ return m_visualCookie==_uid.m_visualCookie;}
		inline void ToggleVisualCookie(){ m_visualCookie = !m_visualCookie;}//���������� �ٲ����� ���Ⱚ�� �ٲ۴�.

#if 0
		bool operator ==(const player_id_t& uid)const {return (m_w_handle==uid.m_w_handle) && (m_did==uid.m_did);}
		bool operator <(const player_id_t& uid)const {return (m_w_handle<uid.m_w_handle) && (m_did<uid.m_did);}
		struct less
		{
			bool operator()( const player_id_t& uid1, const player_id_t& uid2) const
			{
				return (uid1.m_w_handle<uid2.m_w_handle) && (uid1.m_did<uid2.m_did);
			}
		};
#else
		bool operator ==(const player_id_t& uid)const {return (m_did==uid.m_did);}
		bool operator <(const player_id_t& uid)const {return (m_did<uid.m_did);}
		struct less
		{
			bool operator()( const player_id_t& uid1, const player_id_t& uid2) const
			{
				return (uid1.m_did<uid2.m_did);
			}
		};
#endif

	};

	inline tcstr ToString(player_id_t &uid,fname_t buf)
	{
		jt_sprintf_s(buf, 256 ,_T("[%d:%d]"), uid.m_dc_sid,uid.m_dc_handle);
		return buf;
	}


} // nMech
#endif // __player_iasdfdaf_sdtasfdfa_sdfasdheader__
