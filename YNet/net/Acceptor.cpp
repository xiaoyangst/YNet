#include "Acceptor.h"


#define LISTEN_NUM 10

using namespace YNet::net;

namespace YNet{
namespace net{
Acceptor::Acceptor(EventLoop *loop, const std::string &ip, int port)
  :loop_(loop)
{
  serverSocket_ = new Socket(createNonblocking());
  serverSocket_->setReuseAddr(true);
  serverSocket_->setReusePort(true);
  serverSocket_->setTcpNoDelay(true);
  serverSocket_->setKeepAlive(true);
  InetAddress inet_address(ip, port);
  serverSocket_->bind(inet_address);
  serverSocket_->listen(LISTEN_NUM);

  acceptChannel_ = new Channel(loop_,serverSocket_->fd());
  acceptChannel_->setReadCallback_(std::bind(&Acceptor::newConnection, this));
  acceptChannel_->enableReading();       // 让epoll_wait()监视servchannel的读事件。
}
Acceptor::~Acceptor() {
  delete acceptChannel_;
  delete serverSocket_;
}

void Acceptor::newConnection() {
  static int count = 1;
  InetAddress c_addr;
  Socket *clientSocket = new Socket(serverSocket_->accept(c_addr));
  std::cout << count++ << " --> Client connected: " << c_addr.toIpPort() << std::endl;

  connCB_(clientSocket);
}
void Acceptor::setnewConnectionCB(std::function<void(Socket *)> connCB) {
  connCB_ = connCB;
}
}
}