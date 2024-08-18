/**
  ******************************************************************************
  * @file           : Buffer.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-08-12
  ******************************************************************************
  */

#ifndef YNETPROJECT_YNET_NET_BUFFER_H_
#define YNETPROJECT_YNET_NET_BUFFER_H_

#include <string>

namespace YNet{
namespace net{
class Buffer {
 private:
  std::string buf_;
 public:
  Buffer();
  ~Buffer();

  size_t size();
  void clear();
  const char* data(); // 返回 buf_ 的首地址
  void append(const char* data,size_t size);
  void appendHead(const char *data,size_t size);
  void erase(size_t pos,size_t len);
  
};
}
}


#endif //YNETPROJECT_YNET_NET_BUFFER_H_
