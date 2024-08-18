#include "EchoServer.h"

EchoServer::EchoServer(const std::string &ip, int port) {
  tcpServer_ = new TcpServer(ip,port);
  tcpServer_->setCloseConnectionCB(std::bind(&EchoServer::closeConnectionHandle, this,std::placeholders::_1));
  tcpServer_->setEpollTimeoutCB(std::bind(&EchoServer::epollTimeoutHandle, this,std::placeholders::_1));
  tcpServer_->setErrorConnectionCB(std::bind(&EchoServer::errorConnectionHandle, this,std::placeholders::_1));
  tcpServer_->setNewConnectionCB(std::bind(&EchoServer::newConnectionHandle, this,std::placeholders::_1));
  tcpServer_->setSendCompleteCB(std::bind(&EchoServer::sendCompleteHandle, this,std::placeholders::_1));
  tcpServer_->setOnMessageCB(std::bind(&EchoServer::onMessageHandle, this,std::placeholders::_1,std::placeholders::_2));
}
EchoServer::~EchoServer() {

}
void EchoServer::start() {
  tcpServer_->start();
}
void EchoServer::newConnectionHandle(Connection *conn) {
  std::cout << "New Connection Come in." << std::endl;
}
void EchoServer::closeConnectionHandle(Connection *conn) {
  std::cout << "EchoServer conn closed." << std::endl;
}
void EchoServer::errorConnectionHandle(Connection *conn) {
  std::cout << "EchoServer conn error." << std::endl;
}
void EchoServer::onMessageHandle(Connection *conn, std::string &message) {
  std::cout<<"recv data = "<<message<<std::endl;
  conn->send(message, message.size());  // 本质是在做 message 加入到 outputBuffer_ 并注册写事件
}
void EchoServer::sendCompleteHandle(Connection *conn) {
  std::cout << "Message send complete." << std::endl;
}
void EchoServer::epollTimeoutHandle(EventLoop *loop) {
  std::cout << "EchoServer timeout." << std::endl;
}
