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

namespace YNet{
namespace net{
class Connection {
 private:
 EventLoop* loop_;
 Socket* clientSocket_;
 Channel* clientChannel_;
 public:
  Connection(EventLoop* loop,Socket* clientSocket);
  ~Connection();
};
}
}


#endif //YNETPROJECT_YNET_NET_CONNECTION_H_
