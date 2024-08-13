#include <iostream>
#include "ThreadPool.h"

namespace YNet {
namespace net {

ThreadPool::ThreadPool()
    : size_(std::thread::hardware_concurrency())
    , isRun_(false), taskQue_(std::make_unique<TaskQueue>())
{
  std::cout<<size_;
  init();
}

ThreadPool::~ThreadPool() {
  stop();
}

void ThreadPool::init() {
  if (size_ == 0) {
    std::cerr << "please set threadpool size!!!" << std::endl;
    return;
  }
  for (int i = 1; i <= size_; ++i) {
    threadVec_.emplace_back(std::make_unique<Thread>(i));
  }
}

void ThreadPool::start() {
  isRun_ = true;
  for (auto &t : threadVec_) {
    std::cout << "thread id = " << t->id() << " is run ..." << std::endl;
    t->run();
  }

  while (isRun_) {
    std::unique_lock<std::mutex> ul(mtx_);
    have_.wait(ul, [this]() {
      return !isEmpty();
    });

    if (!isRun_) break;  // 如果线程池已停止，退出循环

    auto task = taskQue_->getTask();

    static int count = 0;
    do {
      count = (count + 1) % size_;
      if (!threadVec_[count]->isDoWorking()) {
        threadVec_[count]->toTask(task);
        task = nullptr;
      }
    } while (threadVec_[count]->isDoWorking());
  }
}

void ThreadPool::addTask(taskCallback fn) {
  taskQue_->addTask(fn);
  have_.notify_one();
}

bool ThreadPool::isEmpty() {
  return taskQue_->isEmpty();
}

void ThreadPool::stop() {
  {
    std::lock_guard<std::mutex> lg(mtx_);
    isRun_ = false;
  }
  have_.notify_all();  // 唤醒所有等待中的线程

  for (auto &t : threadVec_) {
    t->stop();
  }
}

}
}
