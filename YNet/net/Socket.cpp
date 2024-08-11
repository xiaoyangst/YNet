#include "Socket.h"

int createNonblocking(){
  int listenfd = socket(AF_INET,SOCK_STREAM|SOCK_NONBLOCK,IPPROTO_TCP);
  if (listenfd < 0){
    perror("socket failed");
    exit(-1);
  }
  return listenfd;
}

namespace YNet{
namespace net{
Socket::Socket(int sockfd):sockfd_(sockfd) {

}

Socket::~Socket() {
  close(sockfd_);
}

int Socket::fd() {
  return sockfd_;
}

void Socket::bind(YNet::net::InetAddress &address) {
  if (::bind(sockfd_, address.addr(), sizeof(*address.addr())) < 0) {
    perror("bind error");
    exit(-1);
  }
}

void Socket::listen(int num) {
  if (::listen(sockfd_, num) < 0) {
    perror("listen error");
    exit(-1);
  }
}

int Socket::accept(YNet::net::InetAddress &clientaddr) {
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  int client_fd = ::accept4(sockfd_, (struct sockaddr *)&client_addr, &client_len,SOCK_NONBLOCK);
  if (client_fd < 0) {
    perror("accept error");
    exit(-1);
  }
  clientaddr.setaddr(client_addr);
  return client_fd;
}

void Socket::setKeepAlive(bool on) {
  int optval = on ? 1 : 0;
  ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE,
               &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::setReuseAddr(bool on) {
  int optval = on ? 1 : 0;
  ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR,
               &optval, static_cast<socklen_t>(sizeof optval));
}
void Socket::setTcpNoDelay(bool on) {
  int optval = on ? 1 : 0;
  ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY,
               &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::setReusePort(bool on) {
  int optval = on ? 1 : 0;
  int ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT,
                         &optval, static_cast<socklen_t>(sizeof optval));
  if (ret < 0 && on)
  {
    perror("SO_REUSEPORT failed.");
  }
}
}
}

