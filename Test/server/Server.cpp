#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "InetAddress.h"
using namespace YNet::net;

#define LISTEN_NUM 10
#define EVENT_NUM 20

void handle_client(int epfd, int client_fd);
void accept_connection(int epfd, int socket_fd);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " 172.17.32.175 8080" << std::endl;
    return -1;
  }

  std::string ip = argv[1];
  int port = std::stoi(argv[2]);

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("socket error");
    return -1;
  }

  InetAddress* inet_address = new InetAddress(ip,port);

//  struct sockaddr_in server_addr;
//  memset(&server_addr, 0, sizeof(server_addr));
//  server_addr.sin_family = AF_INET;
//  server_addr.sin_port = htons(port);
//  server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

  if (bind(socket_fd, inet_address->addr(), sizeof(*inet_address->addr())) < 0) {
    perror("bind error");
    close(socket_fd);
    return -1;
  }

  if (listen(socket_fd, LISTEN_NUM) < 0) {
    perror("listen error");
    close(socket_fd);
    return -1;
  }

  int epfd = epoll_create(1);
  if (epfd < 0) {
    perror("epoll_create error");
    close(socket_fd);
    return -1;
  }

  struct epoll_event evt;
  evt.events = EPOLLIN | EPOLLET;
  evt.data.fd = socket_fd;
  if (epoll_ctl(epfd, EPOLL_CTL_ADD, socket_fd, &evt) < 0) {
    perror("epoll_ctl error");
    close(socket_fd);
    close(epfd);
    return -1;
  }

  while (true) {
    struct epoll_event events[EVENT_NUM];
    int eventNum = epoll_wait(epfd, events, EVENT_NUM, -1);
    if (eventNum < 0) {
      perror("epoll_wait error");
      close(socket_fd);
      close(epfd);
      return -1;
    }

    for (int i = 0; i < eventNum; ++i) {
      if (events[i].data.fd == socket_fd) {
        accept_connection(epfd, socket_fd);
      } else {
        handle_client(epfd, events[i].data.fd);
      }
    }
  }

  close(socket_fd);
  close(epfd);

  return 0;
}

void accept_connection(int epfd, int socket_fd) {
  static int count = 1;
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  InetAddress* c_addr = new InetAddress(client_addr);
  int client_fd = accept(socket_fd, c_addr->addr(), &client_len);
  if (client_fd < 0) {
    perror("accept error");
    return;
  }
  std::cout <<count++<<" --> Client connected: " << c_addr->toIp() << ":" << c_addr->port() << std::endl;
  std::cout <<count++<<" --> Client connected: " << c_addr->toIpPort() << std::endl;
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
