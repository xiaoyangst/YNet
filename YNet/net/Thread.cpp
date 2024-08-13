#include <iostream>
#include <chrono>
#include "Thread.h"

namespace YNet{
namespace net {
Thread::Thread(int id): id_(id), taskCB_(nullptr), isDoWorking_(false), isRun_(false) {

}

Thread::~Thread() {
  if (t_.joinable()) {
    stop();  // 确保线程能够安全退出
    t_.join();
  }
}

void Thread::run() {
  isRun_ = true;
  t_ = std::thread([this](){
    while (isRun_) {
      std::unique_lock<std::mutex> lock(taskMutex_);
      if (taskCB_ && !isDoWorking_) {
        isDoWorking_ = true;
        auto task = taskCB_;
        taskCB_ = nullptr;
        lock.unlock();  // 释放锁以避免任务执行时的锁竞争
        std::cout<<"thread = "<<id();
        task();
        std::this_thread::sleep_for(std::chrono::microseconds(300));  // 睡眠一会儿，防止 while循环持续占用CPU
        lock.lock();
        isDoWorking_ = false;
      }
    }
  });
}

int Thread::id() {
  return id_;
}

void Thread::toTask(taskCallback cb) {
  std::unique_lock<std::mutex> lock(taskMutex_);
  taskCB_ = cb;
}

void Thread::stop() {
  std::unique_lock<std::mutex> lock(taskMutex_);
  isRun_ = false;
}

bool Thread::isDoWorking() {
  return isDoWorking_;
}
}
}
