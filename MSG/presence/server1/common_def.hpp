//
// common_def.hpp
// ~~~~~~~~~~
//
// presence 프로젝트에서 사용하는 공통 definition 모음
//
// 최초 작성 : 2012.07.30. kts123@neowiz.com
// ~~~~~~~~~~
//

#ifndef PRESENCE_COMMON_DEF_HPP
#define PRESENCE_COMMON_DEF_HPP

#include <stdint.h>
#include <string>
#include "boost/shared_ptr.hpp"


namespace presence {

  // error 판단문 가독성 향상을 위한 매크로
#define no_error(e) (!(e))
#define is_error(e) (e)

  // 아이디 타입
  typedef int64_t GameUserID;

  typedef int32_t ServiceID;
  typedef int32_t CategoryID;
  typedef int32_t RoomID;

  typedef int32_t RoomServerID;

  // 기타 타입
  typedef int32_t Port;
  typedef size_t  UserCnt;


  // 유효하지 않은 초기값 정의
  static const GameUserID kInvalidGameId         = GameUserID(-1);
  static const ServiceID kInvalidSvcId           = ServiceID(-1);
  static const CategoryID kInvalidCategoryId     = CategoryID(-1);
  static const RoomID kInvalidRoomId             = RoomID(-1);
  static const RoomServerID kInvalidRoomserverId = RoomServerID(-1);
  static const Port kInvalidPort                 = Port(-1);

#define kUnknownState  "U"
#define kLobbyState   "L"
#define kGameRoomState "G"




} // namespace presence
#endif // PRESENCE_COMMON_DEF_HPP
