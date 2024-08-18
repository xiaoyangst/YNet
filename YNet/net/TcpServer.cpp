#include "TcpServer.h"

#include <utility>

#define LISTEN_NUM 10

namespace YNet {
namespace net {
TcpServer::TcpServer(const std::string &ip, int port)
    : loop_(new EventLoop()) {
  acceptor_ = new Acceptor(loop_,ip,port);
  acceptor_->setnewConnectionCB(std::bind(&TcpServer::newConnection, this,std::placeholders::_1));
  loop_->setepollTimeoutCallback(std::bind(&TcpServer::epollTimeout, this,std::placeholders::_1));
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
  conn->setcloseCallback_(std::bind(&TcpServer::closeConnection, this,std::placeholders::_1));
  conn->seterrorCallback_(std::bind(&TcpServer::errorConnection, this,std::placeholders::_1));
  conn->setonMessageCallback_(std::bind(&TcpServer::onMessage, this,std::placeholders::_1,std::placeholders::_2));
  conn->setsendCompleteCallback_(std::bind(&TcpServer::sendComplete, this,std::placeholders::_1));

  std::cout << "Client connected: " << conn->ip() << ":"<<conn->port()<< std::endl;
  connMap_[conn->fd()] = conn;

  newConnectionCB_(conn);
}
void TcpServer::closeConnection(Connection *conn) {
  if (closeConnectionCB_) closeConnectionCB_(conn);
  connMap_.erase(conn->fd());
}
void TcpServer::errorConnection(Connection *conn) {
  if (errorConnectionCB_) errorConnectionCB_(conn);
  connMap_.erase(conn->fd());
}

void TcpServer::onMessage(Connection *conn,std::string &message) {
  if (onMessageCB_) onMessageCB_(conn,message);
}
void TcpServer::sendComplete(Connection *conn) {
  if (sendCompleteCB_) sendCompleteCB_(conn);
}
void TcpServer::epollTimeout(EventLoop *loop) {
  if (timeoutCB_) timeoutCB_(loop);
}
void TcpServer::setNewConnectionCB(std::function<void(Connection *)> fn) {
  newConnectionCB_ = std::move(fn);
}
void TcpServer::setCloseConnectionCB(std::function<void(Connection *)> fn) {
  closeConnectionCB_ = std::move(fn);
}
void TcpServer::setErrorConnectionCB(std::function<void(Connection *)> fn) {
  errorConnectionCB_ = std::move(fn);
}
void TcpServer::setOnMessageCB(std::function<void(Connection *, std::string &)> fn) {
  onMessageCB_ = std::move(fn);
}
void TcpServer::setSendCompleteCB(std::function<void(Connection *)> fn) {
  sendCompleteCB_ = std::move(fn);
}
void TcpServer::setEpollTimeoutCB(std::function<void(EventLoop *)> fn) {
  timeoutCB_ = std::move(fn);
}
}
}