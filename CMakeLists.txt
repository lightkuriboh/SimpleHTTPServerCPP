cmake_minimum_required(VERSION 3.15)
project(DTLMiniProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(DTLMiniProject
        main.cpp
        SocketUtility/Socket.h
        SocketUtility/Socket.cpp
        SocketUtility/TCPSocket.h
        SocketUtility/TCPSocket.cpp
        constants.h
)
#add_executable(DTLMiniProject multiConnectionsSocket.cpp)
