#ifndef YNETPROJECT_YNET_NET_THREAD_H_
#define YNETPROJECT_YNET_NET_THREAD_H_

#include <thread>
#include <mutex>
#include <functional>
#include <atomic>

namespace YNet{
namespace net {
class Thread {
 private:
  using taskCallback = std::function<void()>;
 private:
  int id_;
  taskCallback taskCB_;
  std::atomic_bool isDoWorking_;  // 判断是否正在执行任务
  std::thread t_;
  std::atomic_bool isRun_;  // 用于控制线程的循环执行
  std::mutex taskMutex_;    // 保护 taskCB_ 和 isDoWorking_
 public:
  explicit Thread(int id);
  ~Thread();
  void run();
  void stop();
  void toTask(taskCallback cb);  // 传递任务进来
  bool isDoWorking();
  int id();
};
}
}

#endif //YNETPROJECT_YNET_NET_THREAD_H_
