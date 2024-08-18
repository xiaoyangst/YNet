#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "InetAddress.h"
#include "TcpServer.h"
#include "ThreadPool.h"

using namespace YNet::net;

//void func() {
//  std::cout << "task" << std::endl;
//}
//
//int main() {
//  ThreadPool* thread_pool = new ThreadPool();
//
//  // 将线程池的启动放在一个单独的线程中
//  std::thread pool_thread([&thread_pool]() {
//    thread_pool->start();
//  });
//
//  sleep(2);
//
//  std::cout << "传递任务" << std::endl;
//  for (int i = 0; i < 10; ++i) {
//    thread_pool->addTask(func);
//  }
//
//  // 继续进行其他操作
//  for (int i = 0; i < 10; ++i) {
//    std::cout<<"继续进行其他操作"<<std::endl;
//    sleep(1);
//  }
//  // 最后停止线程池并等待线程池的启动线程结束
//  thread_pool->stop();
//  pool_thread.join();  // 等待线程池的启动线程结束
//
//  delete thread_pool;
//
//  return 0;
//}

#include "EchoServer.h"


int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " ./Test/server/Server 172.17.32.175 8080" << std::endl;
    return -1;
  }

  std::string ip = argv[1];
  int port = std::stoi(argv[2]);

  EchoServer echo_server(ip,port);
  echo_server.start();

  return 0;
}
