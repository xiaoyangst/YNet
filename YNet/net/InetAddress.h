/**
  ******************************************************************************
  * @file           : InetAddress.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-07-31
  ******************************************************************************
  */

#ifndef YNET_YNET_NET_INETADDRESS_H_
#define YNET_YNET_NET_INETADDRESS_H_

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace YNet {
namespace net {
class InetAddress {
 private:
  std::string ip_;
  uint16_t port_{};
  struct sockaddr_in addr_{};
 public:
  InetAddress(const std::string& ip, uint16_t port);     // 监听 fd 所需的，用于服务端
  explicit InetAddress(const struct sockaddr_in& addr);  // 接收 fd 所需的，用于客户端
  ~InetAddress() = default;

  [[nodiscard]] std::string toIp() const;
  [[nodiscard]] std::string toIpPort() const;
  [[nodiscard]] uint16_t port() const;

  struct sockaddr* addr();
};
}
}

#endif //YNET_YNET_NET_INETADDRESS_H_
