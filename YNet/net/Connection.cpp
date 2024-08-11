#include "Connection.h"
namespace YNet{
namespace net{
Connection::Connection(EventLoop* loop,Socket* clientSocket)
  :loop_(loop)
  ,clientSocket_(clientSocket)
{
  Channel* clientChannel = new Channel(loop_,clientSocket->fd());
  clientChannel->setReadCallback_(std::bind(&Channel::onMessage, clientChannel));
  clientChannel->setET();
  clientChannel->enableReading();   // epoll树监听读事件
}
Connection::~Connection() {
  delete clientChannel_;
  delete clientSocket_;
}
}
}