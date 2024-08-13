#ifndef YNETPROJECT_YNET_NET_TASKQUEUE_H_
#define YNETPROJECT_YNET_NET_TASKQUEUE_H_

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace YNet {
namespace net {
class TaskQueue {
 private:
  using taskCallback = std::function<void()>;
  std::queue<taskCallback> taskQue_;
  std::mutex mtx_;
 public:
  TaskQueue();
  ~TaskQueue();
  void addTask(taskCallback fn);
  taskCallback getTask();
  bool isEmpty();
};
}
}

#endif //YNETPROJECT_YNET_NET_TASKQUEUE_H_
