using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using nNWM;
using user_id_t = System.Int64;

namespace nNWM
{
	namespace nRPS
	{
		public enum EUserGPS
		{
			eUGPS_LOGOUT					, //- ��Ʈ����������")
			eUGPS_LOGIN					, // -UserGate����������-)")
			eUGPS_DB_LOAD					, // -UserGate����������-)")

			eUGPS_UserGateServer			, //��������� ��������Ʈ���������� ����")
			eUGPS_x2ug_goto_match, //��ġâ(��Ƽ�÷���â)")
			eUGPS_GAMEROOM				, //BaseballServer������ �������")
			eUGPS_LABEL_GAME_NOT_QUIT		, // ")
			eUGPS_GAME_READY				, //���� ���� �� ����")
			eUGPS_GAME_START				, //���ӽ���")
			eUGPS_GAME_END				, //������ ��� ������ ����������Ŷ ans_game_end �� ���´�")
			eUGPS_GAMEROOM_PRE_LEAVE		, //�κ�� ������ ������� ����-")
			eUGPS_BS_USER_IS_ILLEGAL		, //���Ӽ����� ���ӵ� ���������� ������ ������ ������ �ƴ� ����������")
			eUGPS_BS_ABNORMAL_DISCONNECT	, //�ش� ������ Ŭ���̾�Ʈ�� ���������� TCP DISCONNECT�����̴�.")

			eUGPS_GameServer			, //��������� ���Ӽ������ӻ���")

		}

		public class User_rps 
		{
			public EUserGPS m_eEUserGPS = EUserGPS.eUGPS_LOGOUT;
			public NetEventPlugin_rps m_Plugin;
			public nProtoGLrps.GameRoomInfo m_GameRoomInfo; // gameLogic.proto÷�� �Ұ�.
			public nProtoGLrps.GameInfo m_GameInfo = new nProtoGLrps.GameInfo();
			public Dictionary<string, int> m_ServerInfoRecvState = new Dictionary<string, int>();

			public User_rps(NetEventPlugin_rps plugin) { m_Plugin = plugin; }
			public void Set_GameRoomInfo(nProtoGLrps.GameRoomInfo gri)
			{
				m_eEUserGPS = EUserGPS.eUGPS_GAMEROOM;
				m_GameRoomInfo = gri;
			}

		}//public class User_rps 

	}//namespace nRPS
}//namespace nNWM
