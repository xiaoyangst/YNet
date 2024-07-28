#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_NUM 10

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "./server 172.17.32.175 8888" << std::endl;
    return -1;
  }

  std::string ip = argv[1];
  int port = std::stoi(argv[2]);

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("socket error");
    return -1;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

  int ret = bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret < 0) {
    perror("bind error");
    return -1;
  }

  ret = listen(socket_fd, LISTEN_NUM);
  if (ret < 0) {
    perror("listen error");
    return -1;
  }

  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  int listen_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
  if (listen_fd < 0) {
    perror("accept error");
    return -1;
  }

  char buf[1024] = {0};
  ssize_t bytes_read = read(listen_fd, buf, sizeof(buf) - 1);
  if (bytes_read < 0) {
    perror("read error");
  } else if (bytes_read == 0) {
    std::cout << "Client disconnected." << std::endl;
  } else {
    buf[bytes_read] = '\0'; // Ensure null-termination
    std::cout << "Received data: " << buf << std::endl;
  }

  close(listen_fd);
  close(socket_fd);

  return 0;
}
