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

class Channel;
class EventLoop;
#include <vector>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

namespace YNet{
namespace net{
class Epoll {
 private:
  static const int MaxEventNum = 100;
  int epfd_;
  struct epoll_event events_[MaxEventNum];
 public:
  Epoll();
  ~Epoll();
  int epfd();
  std::vector<epoll_event> loop(int timeout = -1);    // 封装 epoll_wait
  // 封装 epoll_ctl
  void addfd(int sockfd,int op);
  void delfd(int sockfd);
  void updatefd(int sockfd);

};
}
}


#endif //YNETPROJECT_YNET_NET_EPOLL_H_
