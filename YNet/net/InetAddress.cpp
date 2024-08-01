#include "InetAddress.h"

YNet::net::InetAddress::InetAddress() {

}

YNet::net::InetAddress::InetAddress(const std::string& ip, uint16_t port)
    : ip_(ip), port_(port) {
  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port_);
  addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

YNet::net::InetAddress::InetAddress(const struct sockaddr_in& addr)
    : addr_(addr) {
}

std::string YNet::net::InetAddress::toIp() const {
  return inet_ntoa(addr_.sin_addr);
}

uint16_t YNet::net::InetAddress::port() const {
  return ntohs(addr_.sin_port);
}

struct sockaddr* YNet::net::InetAddress::addr() {
  return (struct sockaddr*)(&addr_);
}

std::string YNet::net::InetAddress::toIpPort() const {
  return toIp() + ":" + std::to_string(port());
}

void YNet::net::InetAddress::setaddr(sockaddr_in clientaddr) {
  addr_ = clientaddr;
}

