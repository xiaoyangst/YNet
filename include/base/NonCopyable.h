//
// Created by xy on 2024-07-27.
//

#ifndef YNET_INCLUDE_NONCOPYABLE_H_
#define YNET_INCLUDE_NONCOPYABLE_H_

namespace YNet {
namespace base {
class NonCopyable {
 protected:
  NonCopyable(const NonCopyable &) = delete; // 阻止拷贝
  NonCopyable &operator=(const NonCopyable &) = delete;  // 阻止赋值
  NonCopyable() = default;
  ~NonCopyable() = default;
};
}
} // namespace YNet

#endif //YNET_INCLUDE_NONCOPYABLE_H_


/*
 * 任何需要防止被拷贝和赋值都需要删除拷贝构造函数和赋值运算符函数，为了方便，继承 NonCopyable 即可
 */

/*
 * 为什么采用 protected？ NonCopyable 只是用来作为其他类的基类
 */