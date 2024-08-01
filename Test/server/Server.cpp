#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "InetAddress.h"
#include "Socket.h"
#include "Epoll.h"
using namespace YNet::net;

#define LISTEN_NUM 10
#define EVENT_NUM 20

void handle_client(int epfd, int client_fd);
void accept_connection(int epfd, Socket &serverSocket);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " 172.17.32.175 8080" << std::endl;
    return -1;
  }

  std::string ip = argv[1];
  int port = std::stoi(argv[2]);

  Socket serverSocket(createNonblocking());
  serverSocket.setReuseAddr(true);
  serverSocket.setReusePort(true);
  serverSocket.setTcpNoDelay(true);
  serverSocket.setKeepAlive(true);
  InetAddress inet_address(ip, port);
  serverSocket.bind(inet_address);
  serverSocket.listen(LISTEN_NUM);

  Epoll epoll;

  int socket_fd = serverSocket.fd();

  epoll.addfd(socket_fd, EPOLLIN | EPOLLET);


  while (true) {

    std::vector<epoll_event> evs = epoll.loop();
    for (auto & ev : evs) {
      if (ev.data.fd == socket_fd) {
        accept_connection(epoll.epfd(), serverSocket);
      } else {
        handle_client(epoll.epfd(), ev.data.fd);
      }
    }
  }


  return 0;
}

void accept_connection(int epfd, Socket &serverSocket) {
  static int count = 1;
  InetAddress c_addr;
  Socket *clientSocket = new Socket(serverSocket.accept(c_addr));
  int client_fd = clientSocket->fd();
  std::cout << count++ << " --> Client connected: " << c_addr.toIp() << ":" << c_addr.port() << std::endl;
  std::cout << count++ << " --> Client connected: " << c_addr.toIpPort() << std::endl;
  struct epoll_event evt;
  evt.events = EPOLLIN | EPOLLET;
  evt.data.fd = client_fd;
  if (epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &evt) < 0) {
    perror("epoll_ctl error");
    close(client_fd);
  }
}

void handle_client(int epfd, int client_fd) {
  char buf[4];
  ssize_t bytes_read = recv(client_fd, buf, sizeof(buf) - 1, 0);
  if (bytes_read < 0) {
    perror("recv error");
    close(client_fd);
    epoll_ctl(epfd, EPOLL_CTL_DEL, client_fd, nullptr);
  } else if (bytes_read == 0) {
    std::cout << "Client disconnected." << std::endl;
    close(client_fd);
    epoll_ctl(epfd, EPOLL_CTL_DEL, client_fd, nullptr);
  } else {
    buf[bytes_read] = '\0';
    std::cout << "Received data: " << buf << std::endl;

    // 发送响应消息
    const char *response = "Message received!";
    ssize_t bytes_sent = send(client_fd, response, strlen(response), 0);
    if (bytes_sent < 0) {
      perror("send error");
      close(client_fd);
      epoll_ctl(epfd, EPOLL_CTL_DEL, client_fd, nullptr);
    }
  }
}
