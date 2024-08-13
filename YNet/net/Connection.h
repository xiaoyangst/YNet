/**
  ******************************************************************************
  * @file           : Connection.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-08-11
  ******************************************************************************
  */

#ifndef YNETPROJECT_YNET_NET_CONNECTION_H_
#define YNETPROJECT_YNET_NET_CONNECTION_H_

#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"

#include <map>

namespace YNet {
namespace net {
class Connection {
 private:
  EventLoop *loop_;
  Socket *clientSocket_;
  Channel *clientChannel_;
  Buffer inputBuffer_;
  Buffer outputBuffer_;
  std::function<void(Connection *)> closeCallback_;
  std::function<void(Connection *)> errorCallback_;
  std::function<void(Connection *,std::string)> onMessageCallback_;
  std::function<void(Connection *)> sendCompleteCallback_;
  std::function<void(EventLoop *loop)> epollTimeoutCallback_;
 public:
  Connection(EventLoop *loop, Socket *clientSocket);
  ~Connection();

  std::string ip();
  uint16_t port();
  int fd();

  void setcloseCallback_(std::function<void(Connection *)> fn);
  void seterrorCallback_(std::function<void(Connection *)> fn);
  void setonMessageCallback_(std::function<void(Connection *,std::string)> fn);
  void setepollTimeoutCallback_(std::function<void(EventLoop *loop)> fn);
  void setsendCompleteCallback_(std::function<void(Connection *)> fn);

  void closeCB();
  void errorCB();
  void onMessage();
  void writeCB();
  void send(std::string data,size_t size);
};
}
}

#endif //YNETPROJECT_YNET_NET_CONNECTION_H_
