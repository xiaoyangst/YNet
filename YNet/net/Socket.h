/**
  ******************************************************************************
  * @file           : Socket.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-07-31
  ******************************************************************************
  */

#ifndef YNETPROJECT_YNET_NET_SOCKET_H_
#define YNETPROJECT_YNET_NET_SOCKET_H_

#include "InetAddress.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/tcp.h>

int createNonblocking();

namespace YNet{
namespace net{
class Socket {
 private:
  const int sockfd_;
 public:
  explicit Socket(int sockfd);
  ~Socket();
  int fd();
  void bind(InetAddress& address);
  void listen(int num);
  int accept(InetAddress& clientaddr);

  void setTcpNoDelay(bool on);
  void setReuseAddr(bool on);
  void setReusePort(bool on);
  void setKeepAlive(bool on);
};
}
}



#endif //YNETPROJECT_YNET_NET_SOCKET_H_
