/**
  ******************************************************************************
  * @file           : EventLoop.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-08-11
  ******************************************************************************
  */

#ifndef YNETPROJECT_YNET_NET_EVENTLOOP_H_
#define YNETPROJECT_YNET_NET_EVENTLOOP_H_

#include "Epoll.h"
#include "Channel.h"


namespace YNet {
namespace net {
class EventLoop {
 private:
  Epoll* ep_;
 public:
  EventLoop();
  ~EventLoop();
  void run();
  void updateChannel(Channel* ch);
  Epoll* ep();
};
}
}

#endif //YNETPROJECT_YNET_NET_EVENTLOOP_H_
