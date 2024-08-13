/**
  ******************************************************************************
  * @file           : Channel.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-08-01
  ******************************************************************************
  */

#ifndef YNETPROJECT_YNET_NET_CHANNEL_H_
#define YNETPROJECT_YNET_NET_CHANNEL_H_

#include <iostream>
#include <functional>
#include <unistd.h>
#include "Socket.h"
//#include "EventLoop.h"

namespace YNet{
namespace net{

class Epoll;
class EventLoop;

class Channel {
 private:
  int fd_ = -1;
  bool inepoll_ = false;   // fd 是否已经添加到 epoll 树上
  uint32_t events_ = 0;   // 感兴趣的事件
  uint32_t revents_ = 0;  // 已发生的事件
  EventLoop *loop_=nullptr;
  std::function<void()> readCallback_;
  std::function<void()> closeCallback_;
  std::function<void()> errorCallback_;
  std::function<void()> writeCallback_;
 public:
  Channel(EventLoop *loop,int fd);
  ~Channel();

  [[nodiscard]] int fd() const;
  [[nodiscard]] bool inepoll() const;
  void setET(); // 设置边缘触发
  void enableReading();
  void disableReading();
  void enableWriting();
  void disableWriting();

  void setInEpoll();
  void setRevents(uint32_t  ev);
  void setReadCallback_(std::function<void()> fn);
  void setcloseCallback_(std::function<void()> fn);
  void seterrorCallback_(std::function<void()> fn);
  void setwriteCallback_(std::function<void()> fn);
  [[nodiscard]] uint32_t events() const;
  [[nodiscard]] uint32_t revents() const;
  void handleEvent();
};
}
}


#endif //YNETPROJECT_YNET_NET_CHANNEL_H_
