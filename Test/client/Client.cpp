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
    std::cout << "Usage: " << " ./Test/client/Client 139.196.235.91 8080"<< std::endl;
    return -1;
  }

  std::string server_ip = argv[1];
  int server_port = std::stoi(argv[2]);


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



  for (int i = 0; i < 10; ++i) {
    // 封裝数据 数据长度+数据
    std::string message = "sssbbb";
    int len = message.size();
    char outbuf[1024];
    memset(outbuf,0, sizeof(outbuf));
    memcpy(outbuf,&len,4);
    memcpy(outbuf + 4,message.c_str(),len);
    ssize_t bytes_sent = send(sock_fd, outbuf, len + 4, 0);
    if (bytes_sent < 0) {
      perror("send error");
      return -1;
    } else {
      std::cout << "Sent message: " << message << std::endl;
    }
    sleep(1);
  }

  char inputbuf[1024];
  for (int i = 0; i < 10; ++i) {
    bzero(inputbuf,sizeof(inputbuf));
    ssize_t bytes_recv = recv(sock_fd,inputbuf,sizeof(inputbuf),0);
    if (bytes_recv < 0) {
      perror("recv error");
      return -1;
    } else {
      std::cout << "Recv message: " << std::string(inputbuf) << std::endl;
    }
  }

  close(sock_fd);
  return 0;
}
