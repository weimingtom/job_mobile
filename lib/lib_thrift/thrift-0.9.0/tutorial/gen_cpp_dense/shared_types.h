/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef shared_TYPES_H
#define shared_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>



namespace shared {

typedef struct _SharedStruct__isset {
  _SharedStruct__isset() : key(false), value(false) {}
  bool key;
  bool value;
} _SharedStruct__isset;

class SharedStruct {
 public:

  static const char* ascii_fingerprint; // = "3F5FC93B338687BC7235B1AB103F47B3";
  static const uint8_t binary_fingerprint[16]; // = {0x3F,0x5F,0xC9,0x3B,0x33,0x86,0x87,0xBC,0x72,0x35,0xB1,0xAB,0x10,0x3F,0x47,0xB3};

  SharedStruct() : key(0), value() {
  }

  virtual ~SharedStruct() throw() {}

  static ::apache::thrift::reflection::local::TypeSpec* local_reflection;

  int32_t key;
  std::string value;

  _SharedStruct__isset __isset;

  void __set_key(const int32_t val) {
    key = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  bool operator == (const SharedStruct & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    return true;
  }
  bool operator != (const SharedStruct &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SharedStruct & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(SharedStruct &a, SharedStruct &b);

// i32
extern ::apache::thrift::reflection::local::TypeSpec
trlo_typespec_shared_F89EDB52B075B8BD95989BD3D0A04C0A;

// string
extern ::apache::thrift::reflection::local::TypeSpec
trlo_typespec_shared_B45CFFE084DD3D20D928BEE85E7B0F21;

// void
extern ::apache::thrift::reflection::local::TypeSpec
trlo_typespec_shared_CAB8111FD0B710A336C898E539090E34;

// {1:i32;2:string;}
extern ::apache::thrift::reflection::local::TypeSpec
trlo_typespec_shared_3F5FC93B338687BC7235B1AB103F47B3;

} // namespace

#endif
