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
  std::map<int,Connection*> connMap_;

  std::function<void(Connection*)> newConnectionCB_;
  std::function<void(Connection*)> closeConnectionCB_;
  std::function<void(Connection*)> errorConnectionCB_;
  std::function<void(Connection*,std::string &message)> onMessageCB_;
  std::function<void(Connection*)> sendCompleteCB_;
  std::function<void(EventLoop*)>  timeoutCB_;
 public:
  TcpServer(const std::string& ip,int port);
  ~TcpServer();
  void start();
  void newConnection(Socket* clientSocket);
  void closeConnection(Connection* conn);
  void errorConnection(Connection* conn);
  void onMessage(Connection* conn,std::string &message);
  void sendComplete(Connection *conn);
  void epollTimeout(EventLoop *loop);

  void setNewConnectionCB(std::function<void(Connection*)> fn);
  void setCloseConnectionCB(std::function<void(Connection*)> fn);
  void setErrorConnectionCB(std::function<void(Connection*)> fn);
  void setOnMessageCB(std::function<void(Connection*,std::string &message)> fn);
  void setSendCompleteCB(std::function<void(Connection*)> fn);
  void setEpollTimeoutCB(std::function<void(EventLoop*)> fn);

};
}
}


#endif //YNETPROJECT_YNET_NET_TCPSERVER_H_
