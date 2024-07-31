set(NET_SRC
    ../../YNet/net/InetAddress.cpp
)

add_executable(Server Server.cpp ${NET_SRC})

