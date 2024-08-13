#include "Channel.h"
#include "Epoll.h"
#include "EventLoop.h"
#include "Connection.h"
#include <sys/epoll.h>

#include <utility>

using namespace YNet::net;

namespace YNet{
namespace net{
Channel::Channel(EventLoop *loop, int fd)
    :loop_(loop),fd_(fd)
{

}

Channel::~Channel() {
  // 在析构函数中，不要销毁 ep_，也不能关闭 fd_，因为这两个东西不属于Channel类
  // Channel类只是需要它们，使用它们而已
}

int Channel::fd() const {
  return fd_;
}

bool Channel::inepoll() const {
  return inepoll_;
}

uint32_t Channel::events() const {
  return events_;
}

uint32_t Channel::revents() const {
  return revents_;
}

void Channel::setInEpoll() {
  inepoll_ = !inepoll_;
}

void Channel::setET() {
  events_ |= EPOLLET;
}

void Channel::enableReading() {
  events_ |= EPOLLIN;
  loop_->updateChannel(this);
}

void Channel::disableReading() {
  events_ &=~ EPOLLIN;
  loop_->updateChannel(this);
}
void Channel::enableWriting() {
  events_ |= EPOLLOUT;
  loop_->updateChannel(this);
}
void Channel::disableWriting() {
  events_ &=~ EPOLLOUT;
  loop_->updateChannel(this);
}

void Channel::setRevents(uint32_t  ev) {
  revents_ = ev;
}
void Channel::handleEvent() {
  if (revents_ & EPOLLRDHUP){   // 表示对端关闭连接或半关闭连接，常用于检测对端的关闭
    closeCallback_();
  } else if (revents_ & (EPOLLIN | EPOLLPRI)){  // 可读事件
    readCallback_();
  } else if (revents_ & EPOLLOUT){
    writeCallback_();
  }else{
    errorCallback_();
  }
}
void Channel::setReadCallback_(std::function<void()> fn) {
  readCallback_ = std::move(fn);
}
void Channel::setcloseCallback_(std::function<void()> fn) {
  closeCallback_ = std::move(fn);
}
void Channel::seterrorCallback_(std::function<void()> fn) {
  errorCallback_ = std::move(fn);
}
void Channel::setwriteCallback_(std::function<void()> fn) {
  writeCallback_ = std::move(fn);
}

}
}

