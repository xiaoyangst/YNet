//
// Created by xy on 2024-07-27.
//

#ifndef YNET_INCLUDE_SINGLETON_H_
#define YNET_INCLUDE_SINGLETON_H_

#include "NonCopyable.h"
#include <mutex>

namespace YNet {
namespace base {
template<typename T>
class Singleton : public NonCopyable {
 public:
  static T &getInstance() {
    std::call_once(initInstanceFlag_, init);
    return *instance_;
  }
 protected:
  Singleton() = default;
  virtual ~Singleton() = default;
 private:
  static void init() {
    instance_ = new T();
    // 可以在此处注册一个析构函数，以便在程序结束时释放单例对象
    std::atexit(&Singleton::destroySingleton);
  }
  static void destroySingleton() {
    delete instance_;
    instance_ = nullptr;
  }

  static T *instance_;
  static std::once_flag initInstanceFlag_;
};
// 静态成员变量初始化
template<typename T>
std::once_flag Singleton<T>::initInstanceFlag_;

template<typename T>
T *Singleton<T>::instance_ = nullptr;
}
}

#endif //YNET_INCLUDE_SINGLETON_H_
