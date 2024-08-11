/**
  ******************************************************************************
  * @file           : Epoll.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-08-01
  ******************************************************************************
  */

#ifndef YNETPROJECT_YNET_NET_EPOLL_H_
#define YNETPROJECT_YNET_NET_EPOLL_H_

#include <vector>
#include <sys/epoll.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Channel.h"

namespace YNet{
namespace net{
class Channel;
class Epoll {
 private:
  static const int MaxEventNum = 100;
  int epfd_;
  struct epoll_event events_[MaxEventNum]{};
 public:
  Epoll();
  ~Epoll();
  int epfd() const;
  std::vector<Channel *> loop(int timeout = -1);    // 封装 epoll_wait
  // 封装 epoll_ctl
  void updateChannel(Channel *channel) const;

};
}
}


#endif //YNETPROJECT_YNET_NET_EPOLL_H_
