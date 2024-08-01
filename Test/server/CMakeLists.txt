set(NET_SRC
    ../../YNet/net/InetAddress.cpp
    ../../YNet/net/Socket.cpp
    ../../YNet/net/Epoll.cpp
)

add_executable(Server Server.cpp ${NET_SRC})

