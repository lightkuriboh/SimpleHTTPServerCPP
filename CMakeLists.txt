cmake_minimum_required(VERSION 3.13)
project(SimpleCPPServer)

set(CMAKE_CXX_COMPILER "g++-9")
set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_FLAGS "-pthread -I..")

add_executable(SimpleCPPServer
        main.cpp
        Socket/Socket.h
        Socket/Socket.cpp
        Socket/TCPSocket.h
        Socket/TCPSocket.cpp
        SignalHandler/SignalHandler.h
        SignalHandler/SignalHandler.cpp
        libs/EPollUtility.h
        libs/EPollUtility.cpp
        libs/SocketUtility.h
        libs/SocketUtility.cpp
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
