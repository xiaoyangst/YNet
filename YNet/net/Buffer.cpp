#include "Buffer.h"

namespace YNet{
namespace net{
Buffer::Buffer() {

}
Buffer::~Buffer() {

}
void Buffer::append(const char *data, size_t size) {
  buf_.append(data,size);
}
size_t Buffer::size() {
  return buf_.size();
}
void Buffer::clear() {
  buf_.clear();
}
const char *Buffer::data() {
  return buf_.data();   // data() 方法和 c_str() 方法在 C++ 中都可以用来获取指向字符串内容的指针
}
void Buffer::erase(size_t pos, size_t len) {
  buf_.erase(pos,len);
}
void Buffer::appendHead(const char *data, size_t size) {
  buf_.append((char*)&size,4);
  buf_.append(data,size);
}
}
}