#include "Connection.h"
namespace YNet{
namespace net{
Connection::Connection(EventLoop* loop,Socket* clientSocket)
  :loop_(loop)
  ,clientSocket_(clientSocket)
{
  clientChannel_ = new Channel(loop_,clientSocket->fd());
  clientChannel_->setReadCallback_(std::bind(&Connection::onMessage, this));
  clientChannel_->setcloseCallback_(std::bind(&Connection::closeCB, this));
  clientChannel_->seterrorCallback_(std::bind(&Connection::errorCB, this));
  clientChannel_->setwriteCallback_(std::bind(&Connection::writeCB, this));
  clientChannel_->setET();
  clientChannel_->enableReading();   // epoll树监听读事件
}
Connection::~Connection() {
  delete clientChannel_;
  delete clientSocket_;
}
std::string Connection::ip() {
  return clientSocket_->ip();
}
uint16_t Connection::port() {
  return clientSocket_->port();
}
int Connection::fd() {
  return clientSocket_->fd();
}
void Connection::closeCB() {
  closeCallback_(this);
}
void Connection::errorCB() {
  errorCallback_(this);
}
void Connection::setcloseCallback_(std::function<void(Connection *)> fn) {
  closeCallback_ = fn;
}
void Connection::seterrorCallback_(std::function<void(Connection *)> fn) {
  errorCallback_ = fn;
}
void Connection::setonMessageCallback_(std::function<void(Connection *,std::string&)> fn) {
  onMessageCallback_ = fn;
}

void Connection::onMessage() {
  char buf[1024];
  while (true) {    // 因为是非阻塞 I/O，因此在循环中把数据全部读完
    memset(&buf, 0, sizeof(buf));
    ssize_t bytes_read = recv(fd(), buf, sizeof(buf) - 1, 0);
    if (bytes_read > 0) { // 有数据来，可读
      inputBuffer_.append(buf,bytes_read);
    } else if (bytes_read == 0) { // 客户端断开连接
      closeCB();
      break;
    } else if (bytes_read == -1 && errno == EINTR){ //调用被信号中断。通常可以忽略此错误并再次调用 recv
      continue;
    } else if (bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){  // EAGAIN 或 EWOULDBLOCK: 套接字设置为非阻塞模式，但没有数据可读取。此时可以选择稍后重试（数据读取完毕）
      while (true) {  // 处理 inputBuffer_ 中的数据
        int len;
        memcpy(&len, inputBuffer_.data(), 4);
        if (inputBuffer_.size() < len + 4) {   // 说明数据不完整，下次处理
          break;
        }
        std::string data(inputBuffer_.data() + 4, len);  // 获取有效数据
        inputBuffer_.erase(0, len + 4);  // 删除已读取到的数据
        onMessageCallback_(this, data);
      }
      break;
    } else if (bytes_read == -1 && errno == ECONNRESET){  // 连接被对方重置。此时可以关闭套接字并进行适当的错误处理
      errorCB();
      break;
    }
  }
}

void Connection::send(std::string& data, size_t size) {
  outputBuffer_.appendHead(data.c_str(),size);  // 发出去的数据，会自动封装成 头部+数据 格式
  clientChannel_->enableWriting();  // 注册写事件
}

void Connection::writeCB() {
  // 尝试发出所有数据
  int writen = ::send(fd(),outputBuffer_.data(),outputBuffer_.size(),0);
  if (writen>0){
    outputBuffer_.erase(0,writen);
  }
  if (outputBuffer_.size() == 0){ // 发送缓冲区没有事件，表示数据已发送完成，不再关注写事件
    clientChannel_->disableWriting();
    sendCompleteCallback_(this);
  }
}
void Connection::setepollTimeoutCallback_(std::function<void(EventLoop *)> fn) {
  epollTimeoutCallback_ = fn;
}
void Connection::setsendCompleteCallback_(std::function<void(Connection *)> fn) {
  sendCompleteCallback_ = fn;
}
}
}