#include "TcpServer.h"

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
  std::cout << "Client connected: " << conn->ip() << ":"<<conn->port()<< std::endl;
  connMap_[conn->fd()] = conn;
  conn->setcloseCallback_(std::bind(&TcpServer::closeConnection, this,std::placeholders::_1));
  conn->seterrorCallback_(std::bind(&TcpServer::errorConnection, this,std::placeholders::_1));
  conn->setonMessageCallback_(std::bind(&TcpServer::onMessage, this,std::placeholders::_1,std::placeholders::_2));
  conn->setsendCompleteCallback_(std::bind(&TcpServer::sendComplete, this,std::placeholders::_1));
}
void TcpServer::closeConnection(Connection *conn) {
  std::cout<<conn->ip()<<":"<<conn->port()<<"--->"<<"disconnected"<<std::endl;
  connMap_.erase(conn->fd());
}
void TcpServer::errorConnection(Connection *conn) {
  std::cout<<conn->ip()<<":"<<conn->port()<<"--->"<<"error"<<std::endl;
  connMap_.erase(conn->fd());
}

void TcpServer::onMessage(Connection *conn,std::string message) {
  std::cout<<"recv data = "<<message<<std::endl;
  conn->send(message, message.size());  // 本质是在做 message 加入到 outputBuffer_ 并注册写事件
}
void TcpServer::sendComplete(Connection *conn) {
  std::cout<<"send complete"<<std::endl;
}
void TcpServer::epollTimeout(EventLoop *loop) {
  std::cout<<"epoll Timeout"<<std::endl;
}
}
}