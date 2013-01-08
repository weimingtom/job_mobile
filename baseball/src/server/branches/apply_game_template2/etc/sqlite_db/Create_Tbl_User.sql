

DROP TABLE IF EXISTS Tbl_User;
CREATE TABLE Tbl_User (
	-- 총전적_승 : 토탈 승 카운트
		 win_tot 	 INTEGER 	 
	-- 총전적_패 : 토탈 패 카운트
	,	 lose_tot 	 INTEGER 	 
	-- 시즌전적_승 : 시즌 승 카운트(3개월)
	,	 win_season 	 INTEGER 	 
	-- 시즌전적_패 : 시즌 패 카운트(3개월)
	,	 lose_season 	 INTEGER 	 
	-- 연승 : 연속으로 승리한 개수. 음수면 연패
	,	 win_continue 	 SMALLINT 	 
	-- 싱글-총전적_승 : 토탈 승 카운트
	,	 win_tot_single 	 INTEGER 	 
	-- 싱글-총전적_패 : 토탈 패 카운트
	,	 lose_tot_single 	 INTEGER 	 
	-- 싱글-시즌전적_승 : 시즌 승 카운트(3개월)
	,	 win_season_single 	 INTEGER 	 
	-- 싱글-시즌전적_패 : 시즌 패 카운트(3개월)
	,	 lose_season_single 	 INTEGER 	 
	-- 싱글-연승패 : 연속으로 승리한 개수. 음수면 연패
	,	 win_continue_single 	 SMALLINT 	 
-- 고유번호 : db pk 피망에서 온 id를 그대로 사용
	 db_id 	 INTEGER 	 PRIMARY KEY
-- 닉네임 : 베이스볼에서의 유저닉네임
,	 uname 	 VARCHAR(32) 	 
-- 총Disconnect수 : 게임중간에 나간수
,	 discon_tot 	 INTEGER 	 
-- 탈삼진수 : 투수총_탈삼진
,	 pitcher_tot_strikeout 	 SMALLINT 	 
-- 투수총평균_레벨 : 투수총평균_레벨 멀로 평균을 낼것인가
,	 pitcher_tot_average_level 	 SMALLINT 	 
-- 총_홈런수 : 타자총_홈런
,	 better_tot_homerun 	 SMALLINT 	 
-- 타자총평균_레벨 : 타자총평균_레벨
,	 better_tot__average_level 	 SMALLINT 	 
-- 캐쉬템구매갯수 : 캐쉬템구매갯수
,	 cash_item_buy_count 	 SMALLINT 	 
-- 마지막로긴시간 : 마지막로긴시간
,	 time_last_login 	 DATETIME 	 
-- 마지막로그아웃시간 : 마지막 로그아웃시간
,	 time_last_logout 	 DATETIME 	 
-- 연속출석일수 : 연속출석한 일수
,	 day_continue_attend 	 SMALLINT 	 
-- 등록시간 : 최초게임등록일
,	 date_insert 	 DATETIME 	 
-- 수정된시간 : 마지막수정시간
,	 date_update 	 DATETIME 	 
-- 기본팀번호 : 기본팀 index
,	 default_tid 	 INTEGER 	 
-- 옵션 : 옵션(클라에서임의로저장할내용)
,	 option 	 VARCHAR(1024) 	 
-- 싱글플레이보상카운트 : 하루에 발급된 싱글플레이 보상경험치 횟수
,	 singleplay_gift_count 	 SMALLINT 	 
-- 삭제플레그 : 아이템이 삭제된것.또는 어뷰징으로 제제상태
,	 is_deleted 	 SMALLINT 	 
-- 게임머니
,	 game_money 	 INTEGER 	 
-- client_os : 클라 OS ( IOS / ANDROID )
,	 client_os 	 VARCHAR(32) 	 
-- client_networ : 클라 네트웍(3G, 4G, WIFI)
,	 client_networ 	 VARCHAR(32) 	 
-- 총_플레이_타임 : 총_플레이_타임(분)
,	 playtime_tot 	 INTEGER 	 
);