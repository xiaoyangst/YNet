#include "Epoll.h"

YNet::net::Epoll::Epoll()
{
  epfd_ = epoll_create1(EPOLL_CLOEXEC);
  if (epfd_ < 0) {
    perror("epoll_create error");
    exit(-1);
  }
}

YNet::net::Epoll::~Epoll() {
  close(epfd_);
}

void YNet::net::Epoll::addfd(int sockfd,int op) {
  struct epoll_event evt;
  evt.events = op;
  evt.data.fd = sockfd;
  if (epoll_ctl(epfd_, EPOLL_CTL_ADD, sockfd, &evt) < 0) {
    perror("epoll_ctl EPOLL_CTL_ADD error");
    exit(-1);
  }
}

void YNet::net::Epoll::delfd(int sockfd) {
  if(epoll_ctl(epfd_, EPOLL_CTL_DEL, sockfd, nullptr) < 0){
    perror("epoll_ctl EPOLL_CTL_DEL error");
    exit(-1);
  }
}

void YNet::net::Epoll::updatefd(int sockfd) {

}

std::vector<epoll_event> YNet::net::Epoll::loop(int timeout) {
  std::vector<epoll_event> evs;
  memset(events_,0, sizeof(events_));
  int eventNum = epoll_wait(epfd_, events_, MaxEventNum, timeout);
  if (eventNum < 0) {
    perror("epoll_wait failed");
    exit(-1);
  }
  if (eventNum == 0){
    perror("epoll_wait timeout");
    exit(-1);
  }

  for (int i = 0; i < eventNum; ++i) {
    evs.push_back(events_[i]);
  }

  return evs;
}
int YNet::net::Epoll::epfd() {
  return epfd_;
}
