/**
  ******************************************************************************
  * @file           : TcpServer.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-08-11
  ******************************************************************************
  */

#ifndef YNETPROJECT_YNET_NET_TCPSERVER_H_
#define YNETPROJECT_YNET_NET_TCPSERVER_H_

#include "EventLoop.h"
#include "Acceptor.h"

namespace YNet{
namespace net{
class TcpServer {
 private:
  EventLoop* loop_;
  Acceptor* acceptor_;
 public:
  TcpServer(const std::string& ip,int port);
  ~TcpServer();
  void start();
  void newConnection(Socket* clientSocket);
};
}
}


#endif //YNETPROJECT_YNET_NET_TCPSERVER_H_
