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

void Channel::setRevents(uint32_t  ev) {
  revents_ = ev;
}
void Channel::handleEvent() {
  if (revents_ & EPOLLRDHUP){   // 表示对端关闭连接或半关闭连接，常用于检测对端的关闭
    std::cout<<"client eventfd = "<<fd_<<"disconnected"<<std::endl;
  } else if (revents_ & (EPOLLIN | EPOLLPRI)){  // 可读事件
    readCallback_();
  } else if (revents_ & EPOLLOUT){

  }else{
    std::cout<<"client eventfd = "<<fd_<<"error"<<std::endl;
    close(fd_);
  }
}
void Channel::setReadCallback_(std::function<void()> fn) {
  readCallback_ = std::move(fn);
}

void Channel::onMessage() {
  char buf[4];
  ssize_t bytes_read = recv(fd_, buf, sizeof(buf) - 1, 0);
  if (bytes_read < 0) {
    perror("recv error");
    epoll_ctl(loop_->ep()->epfd(), EPOLL_CTL_DEL, fd_, nullptr);
  } else if (bytes_read == 0) {
    std::cout << "Client disconnected." << std::endl;
    epoll_ctl(loop_->ep()->epfd(), EPOLL_CTL_DEL, fd_, nullptr);
  } else {
    buf[bytes_read] = '\0';
    std::cout << "Received data: " << buf << std::endl;

    // 发送响应消息
//    const char *response = "Message received!";
//    ssize_t bytes_sent = send(fd_, response, strlen(response), 0);
//    if (bytes_sent < 0) {
//      perror("send error");
//      close(fd_);
//      epoll_ctl(ep_->epfd(), EPOLL_CTL_DEL, fd_, nullptr);
//    }
  }
}
}
}

