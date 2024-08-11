#include "Epoll.h"


namespace YNet{
namespace net{
Epoll::Epoll()
{
  epfd_ = epoll_create1(EPOLL_CLOEXEC);
  if (epfd_ < 0) {
    perror("epoll_create error");
    exit(-1);
  }
}

Epoll::~Epoll() {
  close(epfd_);
}

void Epoll::updateChannel(Channel *channel) const {
  struct epoll_event evt{};
  evt.events = channel->events();
  evt.data.ptr = channel;
  if (!channel->inepoll()) {
    if (epoll_ctl(epfd_, EPOLL_CTL_ADD, channel->fd(), &evt) < 0) {
      perror("epoll_ctl EPOLL_CTL_ADD error");
      exit(-1);
    }
    channel->setInEpoll(); // channel 已添加到树上
  }else{
    if (epoll_ctl(epfd_, EPOLL_CTL_MOD, channel->fd(), &evt) < 0) {
      perror("epoll_ctl EPOLL_CTL_MOD error");
      exit(-1);
    }
  }
}


std::vector<Channel *> Epoll::loop(int timeout) {
  std::vector<Channel*> Channels;
  memset(events_,0, sizeof(events_));
  int eventNum = epoll_wait(epfd_, events_, MaxEventNum, timeout);
  if (eventNum < 0) {
    perror("epoll_wait failed");
    exit(-1);
  }
  if (eventNum == 0){
    perror("epoll_wait timeout");
    return Channels;
  }

  for (int i = 0; i < eventNum; ++i) {
    auto ch = (Channel*)events_[i].data.ptr;
    ch->setRevents(events_[i].events);    // 设置 发生的事件
    Channels.push_back(ch);
  }

  return Channels;
}
int Epoll::epfd() const {
  return epfd_;
}

}
}

