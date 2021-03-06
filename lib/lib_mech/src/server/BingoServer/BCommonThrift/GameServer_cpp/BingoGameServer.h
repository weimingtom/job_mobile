/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef BingoGameServer_H
#define BingoGameServer_H

#include <thrift/TDispatchProcessor.h>
#include "BingoGameServer_types.h"

namespace nBingo {

class BingoGameServerIf {
 public:
  virtual ~BingoGameServerIf() {}
  virtual void X2LG_LOGIN(s_LG2X_LOGIN& _return, const s_X2LG_LOGIN& Data) = 0;
};

class BingoGameServerIfFactory {
 public:
  typedef BingoGameServerIf Handler;

  virtual ~BingoGameServerIfFactory() {}

  virtual BingoGameServerIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(BingoGameServerIf* /* handler */) = 0;
};

class BingoGameServerIfSingletonFactory : virtual public BingoGameServerIfFactory {
 public:
  BingoGameServerIfSingletonFactory(const boost::shared_ptr<BingoGameServerIf>& iface) : iface_(iface) {}
  virtual ~BingoGameServerIfSingletonFactory() {}

  virtual BingoGameServerIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(BingoGameServerIf* /* handler */) {}

 protected:
  boost::shared_ptr<BingoGameServerIf> iface_;
};

class BingoGameServerNull : virtual public BingoGameServerIf {
 public:
  virtual ~BingoGameServerNull() {}
  void X2LG_LOGIN(s_LG2X_LOGIN& /* _return */, const s_X2LG_LOGIN& /* Data */) {
    return;
  }
};

typedef struct _BingoGameServer_X2LG_LOGIN_args__isset {
  _BingoGameServer_X2LG_LOGIN_args__isset() : Data(false) {}
  bool Data;
} _BingoGameServer_X2LG_LOGIN_args__isset;

class BingoGameServer_X2LG_LOGIN_args {
 public:

  BingoGameServer_X2LG_LOGIN_args() {
  }

  virtual ~BingoGameServer_X2LG_LOGIN_args() throw() {}

  s_X2LG_LOGIN Data;

  _BingoGameServer_X2LG_LOGIN_args__isset __isset;

  void __set_Data(const s_X2LG_LOGIN& val) {
    Data = val;
  }

  bool operator == (const BingoGameServer_X2LG_LOGIN_args & rhs) const
  {
    if (!(Data == rhs.Data))
      return false;
    return true;
  }
  bool operator != (const BingoGameServer_X2LG_LOGIN_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const BingoGameServer_X2LG_LOGIN_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class BingoGameServer_X2LG_LOGIN_pargs {
 public:


  virtual ~BingoGameServer_X2LG_LOGIN_pargs() throw() {}

  const s_X2LG_LOGIN* Data;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _BingoGameServer_X2LG_LOGIN_result__isset {
  _BingoGameServer_X2LG_LOGIN_result__isset() : success(false) {}
  bool success;
} _BingoGameServer_X2LG_LOGIN_result__isset;

class BingoGameServer_X2LG_LOGIN_result {
 public:

  BingoGameServer_X2LG_LOGIN_result() {
  }

  virtual ~BingoGameServer_X2LG_LOGIN_result() throw() {}

  s_LG2X_LOGIN success;

  _BingoGameServer_X2LG_LOGIN_result__isset __isset;

  void __set_success(const s_LG2X_LOGIN& val) {
    success = val;
  }

  bool operator == (const BingoGameServer_X2LG_LOGIN_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const BingoGameServer_X2LG_LOGIN_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const BingoGameServer_X2LG_LOGIN_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _BingoGameServer_X2LG_LOGIN_presult__isset {
  _BingoGameServer_X2LG_LOGIN_presult__isset() : success(false) {}
  bool success;
} _BingoGameServer_X2LG_LOGIN_presult__isset;

class BingoGameServer_X2LG_LOGIN_presult {
 public:


  virtual ~BingoGameServer_X2LG_LOGIN_presult() throw() {}

  s_LG2X_LOGIN* success;

  _BingoGameServer_X2LG_LOGIN_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class BingoGameServerClient : virtual public BingoGameServerIf {
 public:
  BingoGameServerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  BingoGameServerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void X2LG_LOGIN(s_LG2X_LOGIN& _return, const s_X2LG_LOGIN& Data);
  void send_X2LG_LOGIN(const s_X2LG_LOGIN& Data);
  void recv_X2LG_LOGIN(s_LG2X_LOGIN& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class BingoGameServerProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<BingoGameServerIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (BingoGameServerProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_X2LG_LOGIN(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  BingoGameServerProcessor(boost::shared_ptr<BingoGameServerIf> iface) :
    iface_(iface) {
    processMap_["X2LG_LOGIN"] = &BingoGameServerProcessor::process_X2LG_LOGIN;
  }

  virtual ~BingoGameServerProcessor() {}
};

class BingoGameServerProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  BingoGameServerProcessorFactory(const ::boost::shared_ptr< BingoGameServerIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< BingoGameServerIfFactory > handlerFactory_;
};

class BingoGameServerMultiface : virtual public BingoGameServerIf {
 public:
  BingoGameServerMultiface(std::vector<boost::shared_ptr<BingoGameServerIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~BingoGameServerMultiface() {}
 protected:
  std::vector<boost::shared_ptr<BingoGameServerIf> > ifaces_;
  BingoGameServerMultiface() {}
  void add(boost::shared_ptr<BingoGameServerIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void X2LG_LOGIN(s_LG2X_LOGIN& _return, const s_X2LG_LOGIN& Data) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->X2LG_LOGIN(_return, Data);
    }
    ifaces_[i]->X2LG_LOGIN(_return, Data);
    return;
  }

};

} // namespace

#endif
