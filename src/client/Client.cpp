//
// Created by xy on 2024-07-27.
//

#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <server_ip> <server_port> <message>" << std::endl;
    return -1;
  }

  std::string server_ip = argv[1];
  int server_port = std::stoi(argv[2]);
  std::string message;
  std::cout<<"input message : ";
  std::cin>>message;

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    perror("socket error");
    return -1;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(server_port);
  inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr);

  int ret = connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret < 0) {
    perror("connect error");
    return -1;
  }

  ssize_t bytes_sent = send(sock_fd, message.c_str(), message.size(), 0);
  if (bytes_sent < 0) {
    perror("send error");
    return -1;
  } else {
    std::cout << "Sent message: " << message << std::endl;
  }

  close(sock_fd);
  return 0;
}
