#include "EventLoop.h"


namespace YNet {
namespace net {
EventLoop::EventLoop():ep_(new Epoll()) {
}
EventLoop::~EventLoop() {
  delete ep_;
}
void EventLoop::run() {   // 循环处理 事件
  while (true) {
    std::vector<Channel*> Channels = ep_->loop(10*1000);
    if (Channels.size() == 0){
      epollTimeoutCallback_(this);
    } else{
      for (auto & ch : Channels) {
        ch->handleEvent();
      }
    }
  }
}
Epoll *EventLoop::ep() {
  return ep_;
}
void EventLoop::updateChannel(Channel *ch) {
  ep_->updateChannel(ch);
}
void EventLoop::setepollTimeoutCallback(std::function<void(EventLoop *)> fn) {
  epollTimeoutCallback_ = fn;
}
}
}