#ifndef __BASEBALL_ROOM_H_6UJLOOQZ__
#define __BASEBALL_ROOM_H_6UJLOOQZ__

#include <boost/asio.hpp> 
#include <boost/foreach.hpp> 

#include "game2/room_logic.h" 

#include "proto.h"


#include "baseball_user.h"
#include "excel/db_uid_type.h"
#include "excel/code/table_type.h"
#include "excel/code/table_const_excel_enum.h"

#include "jUser_GameRoomInfo.h" 
#include "logdef.h"

/// 마이그레이션 특이사항
/// 1. MOB_Timer를 제거하고 Room 타이머 사용
///		- MSG::Server의 io_service API 제거 예정
///		- 룸은 main 스레드와 별도의 스레드에서 돌기 때문에 안정성 문제 있음
///		- 타이머에 콜백 넣는 기능이 제거되었기 때문에 
///		  룸에서 콜백을 관리하도록 변경함
/// 2. g_mapRoom 을 별도 클래스로 분리함
///		- 각각의 룸이 여러 스레드에서 동시에 수행될 수 있기 때문에 
///		  룸이 공유하는 객체는 thread safe 해야함
///		- todo : 룸 목록을 별도로 관리해야 하는 이유는?
///	3. 게임 프로토콜 처리 함수의 반환값 제거.
///		- 기존에는 false를 반환하면 연결을 종료시켰으나 이 기능이 사라짐
///		- 연결 종료를 위해서는 직접 kick_out을 호출해야 함

void timer_TIME_GAME_ROUND_TEAMCHANGE(baseball::Room* pRoom);

namespace baseball 
{

void time_out_req_team_match_ready(Room* pRoom);
Sys_Runner_State_id_t _get_random_Sys_Runner_State_id(vector<Sys_Runner_State*> &vec );
ERunnerStateRound get_round_state(round_t iRoundCount, Sys_Runner_State_id_t sid);
void timer_job_ans_game_start(Room* pRoom);
void timer_job_ans_game_round_start(Room* pRoom);

// 비정상 종료 시 게임 결과 처리
// 게임 시작 시 미리 계산해 두었다가 비정상 종료가 발생하면 사용한다.
struct ABNORMAL_END
{
	int64 db_id_A;			// 유저 A
	int64 db_id_B;			// 유저 B
	int Win_elo_A;			// A 승리 시 elo_point
	int Win_elo_B;			// B 승리 시 elo_point
	int Lose_elo_A;			// A 패배 시 elo_point
	int Lose_elo_B;			// B 패배 시 elo_point
};

class Room : 
	public MSG::RoomLogic,
	public jUser_GameRoomInfo
{
private:
	typedef std::map<MSG::GameID, User*>	UserMapType;

public:
	// callback 함수명 앞에 E_를 붙이는 것을 규칙으로 만들었음

// 종료 조건
#define END_GAME_START_ROUND	15
#define LAST_ROUND				17
#define CALLED_GAME_SCORE		10



#define for_each_ETimerKey(X)\
	X(E_TIME_OUT_REQ_TEAM_MATCH_READY,"플레이어 레디를 대기하는 타이머")\
	X(E_TIMER_JOB_ANS_GAME_START,"게임 시작 대기 타임머")\
	X(E_TIMER_JOB_ANS_GAME_ROUND_START,"라운드 시작 대기 타이머")\
	X(E_TIME_OUT_REQ_PITCHER_THROW,"투수 투구 타임아웃")\
	X(E_TIME_OUT_REQ_BETTER_HIT,"타자 타격 타임아웃")\
	X(E_TIMER_TIME_GAME_ROUND_TEAMCHANGE,"")\
	X(E_TIMER_USER_GOTO_LOBBY,"게임 종료 후 리매치 거절")\
	X(E_TIMER_AUTO_GOTO_LOBBY,"게임 종료 후 리매치 하지 않을 때")\
	X(E_TIMER_JOB_REQ_TIMER_START,"")\
	X(E_SEND_ANS_ANSWER_RESTART_GAME,"")\
	X(E_TIMER_TIME_GAME_ROUND_END,"")\
	X(E_TIME_OUT_REQ_RESULT_BETTER_HIT,"")\
	
	jDEFINE_ENUM_CODE2(ETimerKey);

	Room();

	~Room();

	/// @brief          방이 생성되는 시점에 호출됨
	virtual void        on_create();

	/// @brief          방이 삭제되는 시점에 호출됨
	virtual void        on_destroy();

	/// @brief          세션이 방에 참여함
	///
	/// @param game_id  참여한 유저 id
	/// @param enter    클라이언트로부터 전달된 입장 요청 메시지
	/// @param kick_type 입장을 거부하는 경유 그 사유를 넣어줌.(하위 호환성을 위함)
	///
	/// @return         true : 요청을 허용함.
	///                 false : 요청을 거부함
	///
	/// @remark         이 함수가 호출되는 시점에는 유저가 방에 참여한 상태이다.
	virtual bool		on_join(MSG::GameID game_id, const std::string& room_user_info, std::string& room_info, MSG::KICK_TYPE& kick_type, std::string& leave_info);

	/// @brief          세션이 방에서 퇴장을 요청함
	///                 방에서 퇴장을 승인하는 경우, 
	///                 Room::on_leave 함수가 뒤이어 호출됨 
	///
	/// @param session  퇴장을 요청하는 세션
	/// @param leave_info 클라이언트에서 퇴장 요청시 전달된 추가 정보
	///
	/// @return         true : 요청을 허용함
	///                 false : 요청을 거부함
	///
	/// @remark         이 함수가 호출되는 시점에는 유저가 방에 참여한 상태이다.
	virtual bool        on_request_leave(MSG::GameID /*game_id*/, const std::string& /*leave_info*/) { return true; }

	/// @brief          세션이 방에서 퇴장함
	///
	/// @param session  방에서 퇴장한 세션
	/// @param reason   방 퇴장 사유. leave가 NULL이 아닌 경우, 사용자 요청에 의한 것임
	///                 leave->kick()의 파라미터와 동일한 값
	///                 상세 퇴장 사유는 enum 값 설명 참조.
	/// @param leave_info 1. 클라이언트 요청에 의한 퇴장 : 클라이언트에서 퇴장 요청시 전달된 추가 정보 
	///					2. kick_out 함수 호출에 의한 퇴장 : kick_out 함수에 전달된 info 필드
	///				    이 값이 클라이언트 응답으로 전달됨	
	///
	/// @remark         이 함수가 호출되는 시점에는 유저가 방에 포함되지 않은 상태이다.
	///                 즉, 이 함수 내에서 참여하려는 유저에게 전송하는 메시지는 전달되지 않는다.
	virtual void        on_leave(MSG::GameID game_id, MSG::KICK_TYPE reason, const std::string& leave_info);

	/// @brief          유저가 detach되었을 때 호출됨
	/// @desc           mobile 디바이스와 user gateway 간의 통신이 일시적으로 안되는 경우. detach 로 처리.
	///                 감지 방법
	///                  1. tcp connection 의 비정상 종료
	///                  2. gateway의 ping 요청에 일정 시간(gateway 설정) 응답하지 않음
	///                 detach 상태가 있는 이유
	///                  모바일환경의 특성상 발생할 수 있는 일시적인 네트워크 불안정을 연결 종료로 처리하기엔 부적절함.
	/// @param session  detach된 유저 id 
	/// @param detach   detach 메시지
	/// @remark         해당 game id 는 룸의 사용자목록에서 제외되지 않는다.
	///                 detach 된 사용자를 room 에서 내보낼 필요가 있는 경우, 
	///                 logic 에서 kick_out 을 이용해서 해당 사용자를 능동적으로 내보내야 한다,
	///                 사용자의 detach 여부는 MSG 에서 별도 관리하지 않는다.
	virtual void        on_detach(MSG::GameID game_id);

	/// @brief          유저가 plug되었을 때 호출됨
	/// @desc           detach 상태의 사용자가 다시 연결이 된 것을 plug라고 한다.
	///                 plug 시, detach 시점에 사용자가 참여하고 있던 방이 남아있으면, 이 방으로 다시 들어오는데 이 경우 on_plug가 호출된다.
	/// @param session  플러그된 유저 id
	/// @param plug     plug 메시지
	virtual void        on_plug(MSG::GameID game_id);

	/// @brief          게임 프로토콜 메시지가 수신됨
	///
	/// @param session  메시지를 보낸 유저 id
	/// @param message  시리얼라이즈 된 게임 프로토콜 메시지
	virtual void        on_game_protocol(MSG::GameID game_id, const std::string& message);

	/// @brief          DB 처리 요청에 대한 응답이 도착함
	///
	/// @param gdme_id  DB 작업을 수행한 유저의 id
	/// @param db       응답
	virtual void        on_database(MSG::GameID game_id, 
							int32_t seq, 
							const std::string& query,
							int32_t	ret_code,
							const std::string& result);

	/// @brief          타이머가 만료될 후 호출되는 함수
	///
	/// @param          timer_id    타이머 핸들
	/// @param          token 타이머 등록 시, 전달한 token
	/// @param          param 타이머 등록 시, 전달한 param
	/// @remark         Room::add_timer 를 통해 등록한 timer 에 대한 callback 이다.
	virtual void        on_timer(MSG::RoomTimerID timer_id, int32_t token, void* param);

	/// @brief          tick 마다 자동으로 호출되는 함수 
	///                 1초에 최소 4회 호출되는 것을 보장한다.
	/// @param          diff_ms 이전 tick 으로 부터 지난 시간. 단위 밀리초.
	virtual void        on_tick(uint32_t diff_ms) {}

    /// @brief          시스템 에러가 발생한 경우 알려준다
    /// @param game_id  메시지를 안보내는 유저 id
	/// @param error_code 발생한 에러 코드. basekit/errorcode.hpp 참조
	///								
	/// @remark			SOCKET_READ_TIMEOUT 을 제외한 다른 에러가 발생하면
	///					MSG 내부에서 해당 연결을 종료시키고, on_leave 함수를 호출한다.
    virtual void        on_error(MSG::GameID game_id, int error_code) {}

	void add_timer_wrapper(ETimerKey key, uint32_t duration_sec, boost::function<void (Room*)> callback)
	{
		std::map<ETimerKey, MSG::RoomTimerID>::iterator itr = timer_ids_.find(key);
		if (timer_ids_.end() != itr)
		{
			LOG_DEBUG("remove timer : " << ToString(key));
			remove_timer(itr->second);
		}

		MSG::RoomTimerID timer_id = MSG::RoomLogic::add_timer(duration_sec * 1000, key);
		timer_ids_[key] = timer_id;
		timer_callbacks_[key] = callback;
		LOG_DEBUG("add timer : " << ToString(key) << " = " << duration_sec);
	}

	void remove_timer_wrapper(ETimerKey key)
	{
		std::map<ETimerKey, MSG::RoomTimerID>::iterator itr = timer_ids_.find(key);
		if (timer_ids_.end() != itr)
		{
			remove_timer(itr->second);
		}
		timer_ids_.erase(key);
		timer_callbacks_.erase(key);
		LOG_DEBUG("remove timer : " << ToString(key));
	}

	/// @brief 핸들러 함수들이 global 함수이고, 
	///		RoomLogic의 callable 함수들은 protected 이기 때문에
	///		이 함수들을 노출시키기 위해 이렇게 함..
	bool kick_out(MSG::GameID game_id, MSG::KICK_TYPE kick_type, const std::string& leave_info)
	{
		return MSG::RoomLogic::kick_out(game_id, kick_type, leave_info);
	}

	/// @brief 
	/// @tparam _Predicate void (User*)
	template <class _Predicate> 
	void for_each_User(_Predicate __pred)
	{
		BOOST_FOREACH (UserMapType::value_type& kv, user_map_)
		{
			__pred(kv.second);
		}
	}

	bool is_all_user_ready();

	bool is_full_user();

	/// @brief 게임플레이정보 초기화작업.
	void reset_user_info(); 

	/// @brief 경기시작 & 재경기시작전에 초기화작업(공수선택)
	Tbl_User_id_t select_first_attack_user(); 

	void send_ans_pitcher_throw(const s_req_pitcher_throw& rd,bool is_auto);
	void send_bs2x_auto_match_ready2(Tbl_User_id_t uid);

	game_money_t calc_game_money(EBatterHitType e, score_t curr_score,bool isWin);

	//#--------------------------------------------------------------------------
	// Room's memeber variable
	//#--------------------------------------------------------------------------
	s_req_pitcher_throw m_req_pitcher_throw;
	s_req_better_hit	m_req_better_hit;
	Tbl_User_id_t m_first_attack_user; //첫공격을 누가 하는지 저장
	Tbl_User_id_t get_attack_user()  //  현재 라운드의 공격유저.
	{
		return m_GameRoomInfo.m_attack_user(); 
	}

	void calc_game_result();									// 정상 종료 시 결과 처리 
	bool abnormal_calc_game_result(int64 winner);				// 비정상 종료 시 결과 처리
	bool IsTurnTheGameAround(baseball::Room* pRoom);			// 역전승인가?
	void GameEndProc(baseball::Room* pRoom, User* pUser);		// 정상 게임 종료
	void abnormalGameEnd(baseball::Room* pRoom, int64 winner);	// 비정상 게임 종료 처리

	int check_withoutattack_loser();							// WITHOUT_ATTACK ( loser 입장 )
	int check_withoutattack_winner();							// WITHOUT_ATTACK ( winner 입장 )
	int calc_game_score();										// 게임 점수 계산
	int calc_max_remain_score();								// 남은 회에서 획득 가능한 최대 점수( not use )
	int	calc_RSTypeWhenHomerun(ERunnerStateRound eRSType);		// 홈런을 쳤을 때 주자 상태 -> 점수로 환산( not use )
	
	Tbl_User_id_t get_curr_winner();							// 현재 까지의 승자 산출

	// 게임시작시간.
	int64 m_timer_game_start;

	bool GetisNotJoin()				// 룸 입장 플래그 값 설정 함수
	{
		return m_isNotJoin_;
	}

	void SetisNotJoin( bool bJoin )
	{
		m_isNotJoin_ = bJoin;
	}
	
	bool GetGame_End_DB()				// 룸 입장 플래그 값 설정 함수
	{
		return m_game_end_db_;			// 방 안 유저들의 DB 저장 동기화를 위한 플래그 설정 함수
	}

	void SetGame_End_DB( bool bEnd )
	{
		m_game_end_db_ = bEnd;
	}

	int GetGameEndType()				// Set 게임 종료 타입
	{
		return m_game_end_type_;		
	}

	void SetGameEndType( int endtype )				// Set 게임 종료 타입
	{
		m_game_end_type_ = endtype;	
		LOG_DEBUG("endtype = " << endtype);
	}
	//#--------------------------------------------------------------------------
	// 랜덤 주자배치처리.
	//#--------------------------------------------------------------------------
	jLIST_TYPEDEF_map(Tbl_User_id_t,Sys_Runner_State_id_t,m_sid_RunnerState );
	int m_sid_RunnerState_index;
	Sys_Runner_State_id_t Get_Curr_RSR() // Random State Runner
	{
		int idx = m_sid_RunnerState_index; 
		if (idx > 1 || idx < 0)
		{
			LOG_WARNING("idx = " << idx);
			idx = 0; 
		}
		Tbl_User_id_t attack_uid = m_GameRoomInfo.m_attack_user();
		jRETURN_ret(1, m_sid_RunnerState.count(attack_uid));

		LOG_DEBUG("attack_user(" << attack_uid <<
				") -> m_sid_RunnerState = " << m_sid_RunnerState[attack_uid]);
		return m_sid_RunnerState[attack_uid];
	}

	//#--------------------------------------------------------------------------
	// 공격 주자 배치 상태를 알기 위한 sid 값 조회 함수
	//#--------------------------------------------------------------------------
	Sys_Runner_State_id_t Get_Other_RSR() // Random State Runner
	{
		int idx = m_sid_RunnerState_index; 
		if (idx > 1 || idx < 0)
		{
			LOG_WARNING("idx = " << idx);
			idx = 0; 
		}
		Tbl_User_id_t attack_uid = m_GameRoomInfo.m_attack_user();
		jRETURN_ret(1, m_sid_RunnerState.count(attack_uid));

		s_game_play_info* gpi_other = get_s_game_play_info_Other(attack_uid);
		if (gpi_other)
		{
			Tbl_User_id_t uid_other = gpi_other->m_tbl_user().db_id();
			jCHECK(uid_other != attack_uid );

			LOG_DEBUG("other user (" << uid_other <<
				") -> m_sid_RunnerState = " << m_sid_RunnerState[uid_other]);
			return m_sid_RunnerState[uid_other];
		}

		LOG_DEBUG("attack_uid (" << attack_uid <<
			") -> m_sid_RunnerState = " << m_sid_RunnerState[attack_uid]);
		return m_sid_RunnerState[attack_uid];
	}

	//#--------------------------------------------------------------------------
	// 라운드별 공수 체인지.
	//#--------------------------------------------------------------------------
	round_t m_i_TOTAL_ROUND;
	round_t m_i_ATTACK_CHANGE_ROUND;
	round_t m_i_CheckRound;

	/// @brief 현제라운드의 투수 유저.
	User* get_current_pitcher();

	/// @brief 현재 라운드의 타자유저.
	User* get_current_better(); 

	/// @brief 상대방 유저를 가져옴
	User* get_other_user(MSG::GameID game_id);

	/// @brief 닉네임으로 유저 검색
	///		존재하지 않으면 NULL 반환
	User* find_user(MSG::GameID game_id);

	void send(MSG::GameID game_id, const BaseballServer_Client& sendMsg)
	{
		std::string buffer;
		sendMsg.SerializeToString(&buffer);
		MSG::RoomLogic::send(game_id, buffer);
	}

	void send_all(const BaseballServer_Client& sendMsg)
	{
		send_all_except_me(sendMsg, MSG::NULL_GAME_ID);
	}

	void send_all_except_me(const BaseballServer_Client& sendMsg, MSG::GameID game_id)
	{
		std::string buffer;
		sendMsg.SerializeToString(&buffer);
		MSG::RoomLogic::send_all(buffer, game_id);
	}

	void send_to_ug(MSG::GameID game_id, const BaseballServer_UserGateServer& sendMsg)
	{
		ReqDB db;
		db.set_seq(IS_BS2UG_PACKET);
		db.set_query("BaseballServer_UserGateServer");
		sendMsg.SerializeToString(db.mutable_options());	

		std::string buffer;
		db.SerializeToString(&buffer);

		req_database(game_id, buffer);
	}

	void send_all_to_ug(const BaseballServer_UserGateServer& sendMsg)
	{
		send_all_except_me_to_ug(sendMsg, MSG::NULL_GAME_ID);
	}

	void send_all_except_me_to_ug(const BaseballServer_UserGateServer& sendMsg, MSG::GameID game_id)
	{
		BOOST_FOREACH (UserMapType::value_type& kv, user_map_)
		{
			if (kv.first != game_id)
				send_to_ug(kv.first, sendMsg);
		}
	}

	int calc_abnormal_elo( INOUT  s_tbl_user* userA, INOUT  s_tbl_user* userB );

	ABNORMAL_END abnormalEnd;			// 비정상 게임 종료 시 게임 종료 데이터

private:

	/// @brief 유저를 추가하고 포인터를 반환함.
	///		동일 ID 유저가 이미 있는 경우, NULL 반환
	User* insert_user_(MSG::GameID game_id);

	/// @brief 인덱스로 유저 검색
	/// @remark 유저 수 변화에 따라 동일 인덱스가 반환하는 유저가 달라질 수 있음
	User* get_user_(int iOrder);

	/// @brief 유저 삭제. 메모리도 해제됨
	void delete_user_(MSG::GameID game_id);

	/// @brief 방에 참여한 사용자 목록
	UserMapType	user_map_;

	jLIST_TYPEDEF_map(ETimerKey,MSG::RoomTimerID,timer_ids_);
	typedef boost::function<void (Room*)> timer_callback_t;
	jLIST_TYPEDEF_map(ETimerKey,timer_callback_t,timer_callbacks_);

	bool m_isNotJoin_;					// 입장 금지 상태 flag
	bool m_game_end_db_;				// DB 게임 종료 동기화 flag

	int m_game_end_type_;				// 게임 종료 타입
	
};//class Room : 
	
} /* baseball */

#endif /* end of include guard: __BASEBALL_ROOM_H_6UJLOOQZ__ */