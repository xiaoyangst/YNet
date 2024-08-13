#include "TaskQueue.h"

namespace YNet {
namespace net {

TaskQueue::TaskQueue() {
}

TaskQueue::~TaskQueue() {

}

void TaskQueue::addTask(TaskQueue::taskCallback fn) {
  {
    std::lock_guard<std::mutex> lk(mtx_);
    taskQue_.push(fn);
  }
}

TaskQueue::taskCallback TaskQueue::getTask() {
  std::unique_lock<std::mutex> ul(mtx_);
  auto task = taskQue_.front();
  taskQue_.pop();
  return task;
}

bool TaskQueue::isEmpty() {
  std::lock_guard<std::mutex> lk(mtx_);
  return taskQue_.empty();
}

}
}
