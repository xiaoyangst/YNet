set(NET_SRC
    ../../YNet/net/InetAddress.cpp
    ../../YNet/net/Socket.cpp
    ../../YNet/net/Epoll.cpp
    ../../YNet/net/Channel.cpp
        ../../YNet/net/EventLoop.cpp
        ../../YNet/net/TcpServer.cpp
        ../../YNet/net/Acceptor.cpp
        ../../YNet/net/Connection.cpp
)

add_executable(Server Server.cpp ${NET_SRC})

