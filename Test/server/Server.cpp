#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "InetAddress.h"
#include "Socket.h"
#include "Channel.h"
#include "Epoll.h"
#include "EventLoop.h"
#include "TcpServer.h"

using namespace YNet::net;

#define LISTEN_NUM 10
#define EVENT_NUM 20


int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " 172.17.32.175 8080" << std::endl;
    return -1;
  }

  std::string ip = argv[1];
  int port = std::stoi(argv[2]);

  TcpServer tcp_server(ip,port);
  tcp_server.start();

  return 0;
}
