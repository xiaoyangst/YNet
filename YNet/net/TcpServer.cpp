#include "TcpServer.h"

#define LISTEN_NUM 10

namespace YNet {
namespace net {
TcpServer::TcpServer(const std::string &ip, int port)
    : loop_(new EventLoop()) {
  acceptor_ = new Acceptor(loop_,ip,port);
  acceptor_->setnewConnectionCB(std::bind(&TcpServer::newConnection, this,std::placeholders::_1));
}
TcpServer::~TcpServer() {
  delete loop_;
  delete acceptor_;
}
void TcpServer::start() {
  loop_->run();
}
void TcpServer::newConnection(Socket *clientSocket) {
  Connection* conn = new Connection(loop_,clientSocket);
}
}
}