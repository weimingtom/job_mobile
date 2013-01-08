// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: presence.proto

#ifndef PROTOBUF_presence_2eproto__INCLUDED
#define PROTOBUF_presence_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_presence_2eproto();
void protobuf_AssignDesc_presence_2eproto();
void protobuf_ShutdownFile_presence_2eproto();

class PReqProtocol;
class PAnsProtocol;

enum PresenceCommand {
  NONE = 0,
  LOGIN = 1,
  LOGOUT = 2,
  GAMEENTER = 3,
  GAMELEAVE = 4,
  DETACH = 5,
  PLUG = 6,
  CATEGORY = 7,
  ROOMLIST = 8
};
bool PresenceCommand_IsValid(int value);
const PresenceCommand PresenceCommand_MIN = NONE;
const PresenceCommand PresenceCommand_MAX = ROOMLIST;
const int PresenceCommand_ARRAYSIZE = PresenceCommand_MAX + 1;

// ===================================================================

class PReqProtocol : public ::google::protobuf::MessageLite {
 public:
  PReqProtocol();
  virtual ~PReqProtocol();
  
  PReqProtocol(const PReqProtocol& from);
  
  inline PReqProtocol& operator=(const PReqProtocol& from) {
    CopyFrom(from);
    return *this;
  }
  
  static const PReqProtocol& default_instance();
  
  void Swap(PReqProtocol* other);
  
  // implements Message ----------------------------------------------
  
  PReqProtocol* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const PReqProtocol& from);
  void MergeFrom(const PReqProtocol& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::std::string GetTypeName() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required .PresenceCommand command = 1;
  inline bool has_command() const;
  inline void clear_command();
  static const int kCommandFieldNumber = 1;
  inline PresenceCommand command() const;
  inline void set_command(PresenceCommand value);
  
  // required int32 seqID = 2;
  inline bool has_seqid() const;
  inline void clear_seqid();
  static const int kSeqIDFieldNumber = 2;
  inline ::google::protobuf::int32 seqid() const;
  inline void set_seqid(::google::protobuf::int32 value);
  
  // required int64 gameID = 3;
  inline bool has_gameid() const;
  inline void clear_gameid();
  static const int kGameIDFieldNumber = 3;
  inline ::google::protobuf::int64 gameid() const;
  inline void set_gameid(::google::protobuf::int64 value);
  
  // required int32 svcID = 4;
  inline bool has_svcid() const;
  inline void clear_svcid();
  static const int kSvcIDFieldNumber = 4;
  inline ::google::protobuf::int32 svcid() const;
  inline void set_svcid(::google::protobuf::int32 value);
  
  // required int32 category = 5;
  inline bool has_category() const;
  inline void clear_category();
  static const int kCategoryFieldNumber = 5;
  inline ::google::protobuf::int32 category() const;
  inline void set_category(::google::protobuf::int32 value);
  
  // optional int32 arg1 = 6;
  inline bool has_arg1() const;
  inline void clear_arg1();
  static const int kArg1FieldNumber = 6;
  inline ::google::protobuf::int32 arg1() const;
  inline void set_arg1(::google::protobuf::int32 value);
  
  // optional int32 arg2 = 7;
  inline bool has_arg2() const;
  inline void clear_arg2();
  static const int kArg2FieldNumber = 7;
  inline ::google::protobuf::int32 arg2() const;
  inline void set_arg2(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:PReqProtocol)
 private:
  inline void set_has_command();
  inline void clear_has_command();
  inline void set_has_seqid();
  inline void clear_has_seqid();
  inline void set_has_gameid();
  inline void clear_has_gameid();
  inline void set_has_svcid();
  inline void clear_has_svcid();
  inline void set_has_category();
  inline void clear_has_category();
  inline void set_has_arg1();
  inline void clear_has_arg1();
  inline void set_has_arg2();
  inline void clear_has_arg2();
  
  int command_;
  ::google::protobuf::int32 seqid_;
  ::google::protobuf::int64 gameid_;
  ::google::protobuf::int32 svcid_;
  ::google::protobuf::int32 category_;
  ::google::protobuf::int32 arg1_;
  ::google::protobuf::int32 arg2_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];
  
  friend void  protobuf_AddDesc_presence_2eproto();
  friend void protobuf_AssignDesc_presence_2eproto();
  friend void protobuf_ShutdownFile_presence_2eproto();
  
  void InitAsDefaultInstance();
  static PReqProtocol* default_instance_;
};
// -------------------------------------------------------------------

class PAnsProtocol : public ::google::protobuf::MessageLite {
 public:
  PAnsProtocol();
  virtual ~PAnsProtocol();
  
  PAnsProtocol(const PAnsProtocol& from);
  
  inline PAnsProtocol& operator=(const PAnsProtocol& from) {
    CopyFrom(from);
    return *this;
  }
  
  static const PAnsProtocol& default_instance();
  
  void Swap(PAnsProtocol* other);
  
  // implements Message ----------------------------------------------
  
  PAnsProtocol* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const PAnsProtocol& from);
  void MergeFrom(const PAnsProtocol& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::std::string GetTypeName() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required .PresenceCommand command = 1;
  inline bool has_command() const;
  inline void clear_command();
  static const int kCommandFieldNumber = 1;
  inline PresenceCommand command() const;
  inline void set_command(PresenceCommand value);
  
  // required int32 seqID = 2;
  inline bool has_seqid() const;
  inline void clear_seqid();
  static const int kSeqIDFieldNumber = 2;
  inline ::google::protobuf::int32 seqid() const;
  inline void set_seqid(::google::protobuf::int32 value);
  
  // required int64 gameID = 3;
  inline bool has_gameid() const;
  inline void clear_gameid();
  static const int kGameIDFieldNumber = 3;
  inline ::google::protobuf::int64 gameid() const;
  inline void set_gameid(::google::protobuf::int64 value);
  
  // required int32 svcID = 4;
  inline bool has_svcid() const;
  inline void clear_svcid();
  static const int kSvcIDFieldNumber = 4;
  inline ::google::protobuf::int32 svcid() const;
  inline void set_svcid(::google::protobuf::int32 value);
  
  // required int32 category = 5;
  inline bool has_category() const;
  inline void clear_category();
  static const int kCategoryFieldNumber = 5;
  inline ::google::protobuf::int32 category() const;
  inline void set_category(::google::protobuf::int32 value);
  
  // required bool result = 6;
  inline bool has_result() const;
  inline void clear_result();
  static const int kResultFieldNumber = 6;
  inline bool result() const;
  inline void set_result(bool value);
  
  // required string status = 7;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 7;
  inline const ::std::string& status() const;
  inline void set_status(const ::std::string& value);
  inline void set_status(const char* value);
  inline void set_status(const char* value, size_t size);
  inline ::std::string* mutable_status();
  inline ::std::string* release_status();
  
  // required bool detached = 8;
  inline bool has_detached() const;
  inline void clear_detached();
  static const int kDetachedFieldNumber = 8;
  inline bool detached() const;
  inline void set_detached(bool value);
  
  // optional string ip = 9;
  inline bool has_ip() const;
  inline void clear_ip();
  static const int kIpFieldNumber = 9;
  inline const ::std::string& ip() const;
  inline void set_ip(const ::std::string& value);
  inline void set_ip(const char* value);
  inline void set_ip(const char* value, size_t size);
  inline ::std::string* mutable_ip();
  inline ::std::string* release_ip();
  
  // optional int32 port = 10;
  inline bool has_port() const;
  inline void clear_port();
  static const int kPortFieldNumber = 10;
  inline ::google::protobuf::int32 port() const;
  inline void set_port(::google::protobuf::int32 value);
  
  // optional int32 roomID = 11;
  inline bool has_roomid() const;
  inline void clear_roomid();
  static const int kRoomIDFieldNumber = 11;
  inline ::google::protobuf::int32 roomid() const;
  inline void set_roomid(::google::protobuf::int32 value);
  
  // optional int32 arg1 = 12;
  inline bool has_arg1() const;
  inline void clear_arg1();
  static const int kArg1FieldNumber = 12;
  inline ::google::protobuf::int32 arg1() const;
  inline void set_arg1(::google::protobuf::int32 value);
  
  // optional int32 arg2 = 13;
  inline bool has_arg2() const;
  inline void clear_arg2();
  static const int kArg2FieldNumber = 13;
  inline ::google::protobuf::int32 arg2() const;
  inline void set_arg2(::google::protobuf::int32 value);
  
  // optional string info = 14;
  inline bool has_info() const;
  inline void clear_info();
  static const int kInfoFieldNumber = 14;
  inline const ::std::string& info() const;
  inline void set_info(const ::std::string& value);
  inline void set_info(const char* value);
  inline void set_info(const char* value, size_t size);
  inline ::std::string* mutable_info();
  inline ::std::string* release_info();
  
  // @@protoc_insertion_point(class_scope:PAnsProtocol)
 private:
  inline void set_has_command();
  inline void clear_has_command();
  inline void set_has_seqid();
  inline void clear_has_seqid();
  inline void set_has_gameid();
  inline void clear_has_gameid();
  inline void set_has_svcid();
  inline void clear_has_svcid();
  inline void set_has_category();
  inline void clear_has_category();
  inline void set_has_result();
  inline void clear_has_result();
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_detached();
  inline void clear_has_detached();
  inline void set_has_ip();
  inline void clear_has_ip();
  inline void set_has_port();
  inline void clear_has_port();
  inline void set_has_roomid();
  inline void clear_has_roomid();
  inline void set_has_arg1();
  inline void clear_has_arg1();
  inline void set_has_arg2();
  inline void clear_has_arg2();
  inline void set_has_info();
  inline void clear_has_info();
  
  int command_;
  ::google::protobuf::int32 seqid_;
  ::google::protobuf::int64 gameid_;
  ::google::protobuf::int32 svcid_;
  ::google::protobuf::int32 category_;
  ::std::string* status_;
  bool result_;
  bool detached_;
  ::google::protobuf::int32 port_;
  ::std::string* ip_;
  ::google::protobuf::int32 roomid_;
  ::google::protobuf::int32 arg1_;
  ::std::string* info_;
  ::google::protobuf::int32 arg2_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(14 + 31) / 32];
  
  friend void  protobuf_AddDesc_presence_2eproto();
  friend void protobuf_AssignDesc_presence_2eproto();
  friend void protobuf_ShutdownFile_presence_2eproto();
  
  void InitAsDefaultInstance();
  static PAnsProtocol* default_instance_;
};
// ===================================================================


// ===================================================================

// PReqProtocol

// required .PresenceCommand command = 1;
inline bool PReqProtocol::has_command() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PReqProtocol::set_has_command() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PReqProtocol::clear_has_command() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PReqProtocol::clear_command() {
  command_ = 0;
  clear_has_command();
}
inline PresenceCommand PReqProtocol::command() const {
  return static_cast< PresenceCommand >(command_);
}
inline void PReqProtocol::set_command(PresenceCommand value) {
  GOOGLE_DCHECK(PresenceCommand_IsValid(value));
  set_has_command();
  command_ = value;
}

// required int32 seqID = 2;
inline bool PReqProtocol::has_seqid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PReqProtocol::set_has_seqid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PReqProtocol::clear_has_seqid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PReqProtocol::clear_seqid() {
  seqid_ = 0;
  clear_has_seqid();
}
inline ::google::protobuf::int32 PReqProtocol::seqid() const {
  return seqid_;
}
inline void PReqProtocol::set_seqid(::google::protobuf::int32 value) {
  set_has_seqid();
  seqid_ = value;
}

// required int64 gameID = 3;
inline bool PReqProtocol::has_gameid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PReqProtocol::set_has_gameid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PReqProtocol::clear_has_gameid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PReqProtocol::clear_gameid() {
  gameid_ = GOOGLE_LONGLONG(0);
  clear_has_gameid();
}
inline ::google::protobuf::int64 PReqProtocol::gameid() const {
  return gameid_;
}
inline void PReqProtocol::set_gameid(::google::protobuf::int64 value) {
  set_has_gameid();
  gameid_ = value;
}

// required int32 svcID = 4;
inline bool PReqProtocol::has_svcid() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PReqProtocol::set_has_svcid() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PReqProtocol::clear_has_svcid() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PReqProtocol::clear_svcid() {
  svcid_ = 0;
  clear_has_svcid();
}
inline ::google::protobuf::int32 PReqProtocol::svcid() const {
  return svcid_;
}
inline void PReqProtocol::set_svcid(::google::protobuf::int32 value) {
  set_has_svcid();
  svcid_ = value;
}

// required int32 category = 5;
inline bool PReqProtocol::has_category() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void PReqProtocol::set_has_category() {
  _has_bits_[0] |= 0x00000010u;
}
inline void PReqProtocol::clear_has_category() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void PReqProtocol::clear_category() {
  category_ = 0;
  clear_has_category();
}
inline ::google::protobuf::int32 PReqProtocol::category() const {
  return category_;
}
inline void PReqProtocol::set_category(::google::protobuf::int32 value) {
  set_has_category();
  category_ = value;
}

// optional int32 arg1 = 6;
inline bool PReqProtocol::has_arg1() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void PReqProtocol::set_has_arg1() {
  _has_bits_[0] |= 0x00000020u;
}
inline void PReqProtocol::clear_has_arg1() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void PReqProtocol::clear_arg1() {
  arg1_ = 0;
  clear_has_arg1();
}
inline ::google::protobuf::int32 PReqProtocol::arg1() const {
  return arg1_;
}
inline void PReqProtocol::set_arg1(::google::protobuf::int32 value) {
  set_has_arg1();
  arg1_ = value;
}

// optional int32 arg2 = 7;
inline bool PReqProtocol::has_arg2() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void PReqProtocol::set_has_arg2() {
  _has_bits_[0] |= 0x00000040u;
}
inline void PReqProtocol::clear_has_arg2() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void PReqProtocol::clear_arg2() {
  arg2_ = 0;
  clear_has_arg2();
}
inline ::google::protobuf::int32 PReqProtocol::arg2() const {
  return arg2_;
}
inline void PReqProtocol::set_arg2(::google::protobuf::int32 value) {
  set_has_arg2();
  arg2_ = value;
}

// -------------------------------------------------------------------

// PAnsProtocol

// required .PresenceCommand command = 1;
inline bool PAnsProtocol::has_command() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PAnsProtocol::set_has_command() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PAnsProtocol::clear_has_command() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PAnsProtocol::clear_command() {
  command_ = 0;
  clear_has_command();
}
inline PresenceCommand PAnsProtocol::command() const {
  return static_cast< PresenceCommand >(command_);
}
inline void PAnsProtocol::set_command(PresenceCommand value) {
  GOOGLE_DCHECK(PresenceCommand_IsValid(value));
  set_has_command();
  command_ = value;
}

// required int32 seqID = 2;
inline bool PAnsProtocol::has_seqid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PAnsProtocol::set_has_seqid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PAnsProtocol::clear_has_seqid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PAnsProtocol::clear_seqid() {
  seqid_ = 0;
  clear_has_seqid();
}
inline ::google::protobuf::int32 PAnsProtocol::seqid() const {
  return seqid_;
}
inline void PAnsProtocol::set_seqid(::google::protobuf::int32 value) {
  set_has_seqid();
  seqid_ = value;
}

// required int64 gameID = 3;
inline bool PAnsProtocol::has_gameid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PAnsProtocol::set_has_gameid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PAnsProtocol::clear_has_gameid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PAnsProtocol::clear_gameid() {
  gameid_ = GOOGLE_LONGLONG(0);
  clear_has_gameid();
}
inline ::google::protobuf::int64 PAnsProtocol::gameid() const {
  return gameid_;
}
inline void PAnsProtocol::set_gameid(::google::protobuf::int64 value) {
  set_has_gameid();
  gameid_ = value;
}

// required int32 svcID = 4;
inline bool PAnsProtocol::has_svcid() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PAnsProtocol::set_has_svcid() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PAnsProtocol::clear_has_svcid() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PAnsProtocol::clear_svcid() {
  svcid_ = 0;
  clear_has_svcid();
}
inline ::google::protobuf::int32 PAnsProtocol::svcid() const {
  return svcid_;
}
inline void PAnsProtocol::set_svcid(::google::protobuf::int32 value) {
  set_has_svcid();
  svcid_ = value;
}

// required int32 category = 5;
inline bool PAnsProtocol::has_category() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void PAnsProtocol::set_has_category() {
  _has_bits_[0] |= 0x00000010u;
}
inline void PAnsProtocol::clear_has_category() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void PAnsProtocol::clear_category() {
  category_ = 0;
  clear_has_category();
}
inline ::google::protobuf::int32 PAnsProtocol::category() const {
  return category_;
}
inline void PAnsProtocol::set_category(::google::protobuf::int32 value) {
  set_has_category();
  category_ = value;
}

// required bool result = 6;
inline bool PAnsProtocol::has_result() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void PAnsProtocol::set_has_result() {
  _has_bits_[0] |= 0x00000020u;
}
inline void PAnsProtocol::clear_has_result() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void PAnsProtocol::clear_result() {
  result_ = false;
  clear_has_result();
}
inline bool PAnsProtocol::result() const {
  return result_;
}
inline void PAnsProtocol::set_result(bool value) {
  set_has_result();
  result_ = value;
}

// required string status = 7;
inline bool PAnsProtocol::has_status() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void PAnsProtocol::set_has_status() {
  _has_bits_[0] |= 0x00000040u;
}
inline void PAnsProtocol::clear_has_status() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void PAnsProtocol::clear_status() {
  if (status_ != &::google::protobuf::internal::kEmptyString) {
    status_->clear();
  }
  clear_has_status();
}
inline const ::std::string& PAnsProtocol::status() const {
  return *status_;
}
inline void PAnsProtocol::set_status(const ::std::string& value) {
  set_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    status_ = new ::std::string;
  }
  status_->assign(value);
}
inline void PAnsProtocol::set_status(const char* value) {
  set_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    status_ = new ::std::string;
  }
  status_->assign(value);
}
inline void PAnsProtocol::set_status(const char* value, size_t size) {
  set_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    status_ = new ::std::string;
  }
  status_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PAnsProtocol::mutable_status() {
  set_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    status_ = new ::std::string;
  }
  return status_;
}
inline ::std::string* PAnsProtocol::release_status() {
  clear_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = status_;
    status_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required bool detached = 8;
inline bool PAnsProtocol::has_detached() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void PAnsProtocol::set_has_detached() {
  _has_bits_[0] |= 0x00000080u;
}
inline void PAnsProtocol::clear_has_detached() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void PAnsProtocol::clear_detached() {
  detached_ = false;
  clear_has_detached();
}
inline bool PAnsProtocol::detached() const {
  return detached_;
}
inline void PAnsProtocol::set_detached(bool value) {
  set_has_detached();
  detached_ = value;
}

// optional string ip = 9;
inline bool PAnsProtocol::has_ip() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void PAnsProtocol::set_has_ip() {
  _has_bits_[0] |= 0x00000100u;
}
inline void PAnsProtocol::clear_has_ip() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void PAnsProtocol::clear_ip() {
  if (ip_ != &::google::protobuf::internal::kEmptyString) {
    ip_->clear();
  }
  clear_has_ip();
}
inline const ::std::string& PAnsProtocol::ip() const {
  return *ip_;
}
inline void PAnsProtocol::set_ip(const ::std::string& value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void PAnsProtocol::set_ip(const char* value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void PAnsProtocol::set_ip(const char* value, size_t size) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  ip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PAnsProtocol::mutable_ip() {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  return ip_;
}
inline ::std::string* PAnsProtocol::release_ip() {
  clear_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = ip_;
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional int32 port = 10;
inline bool PAnsProtocol::has_port() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void PAnsProtocol::set_has_port() {
  _has_bits_[0] |= 0x00000200u;
}
inline void PAnsProtocol::clear_has_port() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void PAnsProtocol::clear_port() {
  port_ = 0;
  clear_has_port();
}
inline ::google::protobuf::int32 PAnsProtocol::port() const {
  return port_;
}
inline void PAnsProtocol::set_port(::google::protobuf::int32 value) {
  set_has_port();
  port_ = value;
}

// optional int32 roomID = 11;
inline bool PAnsProtocol::has_roomid() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void PAnsProtocol::set_has_roomid() {
  _has_bits_[0] |= 0x00000400u;
}
inline void PAnsProtocol::clear_has_roomid() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void PAnsProtocol::clear_roomid() {
  roomid_ = 0;
  clear_has_roomid();
}
inline ::google::protobuf::int32 PAnsProtocol::roomid() const {
  return roomid_;
}
inline void PAnsProtocol::set_roomid(::google::protobuf::int32 value) {
  set_has_roomid();
  roomid_ = value;
}

// optional int32 arg1 = 12;
inline bool PAnsProtocol::has_arg1() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void PAnsProtocol::set_has_arg1() {
  _has_bits_[0] |= 0x00000800u;
}
inline void PAnsProtocol::clear_has_arg1() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void PAnsProtocol::clear_arg1() {
  arg1_ = 0;
  clear_has_arg1();
}
inline ::google::protobuf::int32 PAnsProtocol::arg1() const {
  return arg1_;
}
inline void PAnsProtocol::set_arg1(::google::protobuf::int32 value) {
  set_has_arg1();
  arg1_ = value;
}

// optional int32 arg2 = 13;
inline bool PAnsProtocol::has_arg2() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void PAnsProtocol::set_has_arg2() {
  _has_bits_[0] |= 0x00001000u;
}
inline void PAnsProtocol::clear_has_arg2() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void PAnsProtocol::clear_arg2() {
  arg2_ = 0;
  clear_has_arg2();
}
inline ::google::protobuf::int32 PAnsProtocol::arg2() const {
  return arg2_;
}
inline void PAnsProtocol::set_arg2(::google::protobuf::int32 value) {
  set_has_arg2();
  arg2_ = value;
}

// optional string info = 14;
inline bool PAnsProtocol::has_info() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void PAnsProtocol::set_has_info() {
  _has_bits_[0] |= 0x00002000u;
}
inline void PAnsProtocol::clear_has_info() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void PAnsProtocol::clear_info() {
  if (info_ != &::google::protobuf::internal::kEmptyString) {
    info_->clear();
  }
  clear_has_info();
}
inline const ::std::string& PAnsProtocol::info() const {
  return *info_;
}
inline void PAnsProtocol::set_info(const ::std::string& value) {
  set_has_info();
  if (info_ == &::google::protobuf::internal::kEmptyString) {
    info_ = new ::std::string;
  }
  info_->assign(value);
}
inline void PAnsProtocol::set_info(const char* value) {
  set_has_info();
  if (info_ == &::google::protobuf::internal::kEmptyString) {
    info_ = new ::std::string;
  }
  info_->assign(value);
}
inline void PAnsProtocol::set_info(const char* value, size_t size) {
  set_has_info();
  if (info_ == &::google::protobuf::internal::kEmptyString) {
    info_ = new ::std::string;
  }
  info_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PAnsProtocol::mutable_info() {
  set_has_info();
  if (info_ == &::google::protobuf::internal::kEmptyString) {
    info_ = new ::std::string;
  }
  return info_;
}
inline ::std::string* PAnsProtocol::release_info() {
  clear_has_info();
  if (info_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = info_;
    info_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_presence_2eproto__INCLUDED