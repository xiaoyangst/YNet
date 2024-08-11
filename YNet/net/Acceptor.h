/**
  ******************************************************************************
  * @file           : Acceptor.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-08-11
  ******************************************************************************
  */

#ifndef YNETPROJECT_YNET_NET_ACCEPTOR_H_
#define YNETPROJECT_YNET_NET_ACCEPTOR_H_

#include "EventLoop.h"
#include "Connection.h"
#include <functional>
namespace YNet{
namespace net{
class Acceptor {
 private:
  EventLoop* loop_;
  Socket* serverSocket_;
  Channel* acceptChannel_;
  std::function<void(Socket *clientSocket)> connCB_;
 public:
  Acceptor(EventLoop* loop,const std::string& ip,int port);
  ~Acceptor();
  void newConnection();
  void setnewConnectionCB(std::function<void(Socket *clientSocket)> connCB);
};
}
}



#endif //YNETPROJECT_YNET_NET_ACCEPTOR_H_
