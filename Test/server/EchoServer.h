/**
  ******************************************************************************
  * @file           : EchoServer.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-08-18
  ******************************************************************************
  */

#ifndef YNETPROJECT_TEST_SERVER_ECHOSERVER_H_
#define YNETPROJECT_TEST_SERVER_ECHOSERVER_H_

#include "TcpServer.h"
#include "Connection.h"
#include "Acceptor.h"
#include "EventLoop.h"

using namespace YNet::net;

class EchoServer {
 private:
  TcpServer* tcpServer_;
 public:
  EchoServer(const std::string& ip,int port);
  ~EchoServer();
  void start();

  void newConnectionHandle(Connection *conn);
  void closeConnectionHandle(Connection* conn);
  void errorConnectionHandle(Connection* conn);
  void onMessageHandle(Connection* conn,std::string &message);
  void sendCompleteHandle(Connection *conn);
  void epollTimeoutHandle(EventLoop *loop);
};

#endif //YNETPROJECT_TEST_SERVER_ECHOSERVER_H_
