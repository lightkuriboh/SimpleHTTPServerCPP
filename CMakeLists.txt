cmake_minimum_required(VERSION 3.13)
project(DTLMiniProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

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
        Server/Server.h
        Server/MyServer.h
        Server/MyServer.cpp
        Server/Requests/RESTInformation.h
        Server/Requests/RESTInformation.cpp
        Server/Requests/RequestHandlers.h
        Server/Requests/RequestHandlers.cpp
        utils/OtherUtils.h
        utils/OtherUtils.cpp
        constants.h
        Server/ServerConstants.h)
