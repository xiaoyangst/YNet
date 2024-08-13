#ifndef YNETPROJECT_YNET_NET_THREADPOOL_H_
#define YNETPROJECT_YNET_NET_THREADPOOL_H_

#include <thread>
#include <vector>
#include <memory>
#include <atomic>
#include <functional>
#include <condition_variable>
#include "Thread.h"
#include "TaskQueue.h"

namespace YNet {
namespace net {
class ThreadPool {
 private:
  using taskCallback = std::function<void()>;
  int size_;
  std::vector<std::unique_ptr<Thread>> threadVec_;
  std::unique_ptr<TaskQueue> taskQue_;
  std::mutex mtx_;
  std::condition_variable have_;    // 只要有任务就提醒
  std::atomic_bool isRun_;          // 用于关闭任务的循环执行
 private:
  void init();    // 创建线程池
 public:
  explicit ThreadPool();
  ~ThreadPool();
  void start();   // 启动线程池
  void stop();    // 停止线程池
  void addTask(taskCallback fn);  // 添加任务
  bool isEmpty(); // 任务队列是否为空
};
}
}

#endif //YNETPROJECT_YNET_NET_THREADPOOL_H_
