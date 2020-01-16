cmake_minimum_required(VERSION 3.15)
project(DTLMiniProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(DTLMiniProject
        main.cpp
        SocketUtility/Socket.h
        SocketUtility/Socket.cpp
        SocketUtility/TCPSocket.h
        SocketUtility/TCPSocket.cpp
        SignalHandler/SignalHandler.h
        SignalHandler/SignalHandler.cpp
        EPollUtility/EPollUtilities.h
        EPollUtility/EPollUtilities.cpp
        MockClients/MockClients.h
        MockClients/MockClients.cpp
        Server/Server.h
        Server/Server.cpp
        Server/MyServer.h
        Server/MyServer.cpp
        utils/Timer.h
        utils/Timer.cpp
        constants.h
)
