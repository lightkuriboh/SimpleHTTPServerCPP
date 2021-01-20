cmake_minimum_required(VERSION 3.13)
project(SimpleCPPServer)

set(CMAKE_CXX_COMPILER "g++-9")
set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_FLAGS "-pthread -I..")

add_executable(SimpleCPPServer
        main.cpp
        SignalHandler/SignalHandler.h
        SignalHandler/SignalHandler.cpp
        libs/EPollUtility.h
        libs/EPollUtility.cpp
        libs/SocketUtility.h
        libs/SocketUtility.cpp
        ApplicationServer/Server.h
        ApplicationServer/MyServer.h
        ApplicationServer/MyServer.cpp
        ApplicationServer/Requests/RESTInformation.h
        ApplicationServer/Requests/RESTInformation.cpp
        ApplicationServer/Requests/RequestHandlers.h
        ApplicationServer/Requests/RequestHandlers.cpp
        utils/OtherUtils.h
        utils/OtherUtils.cpp
        constants.h
        ApplicationServer/ServerConstants.h
        HTTPServer/HTTPServer.h
        HTTPServer/HTTPServer.cpp
        HTTPServer/TCPSocket.h
        HTTPServer/TCPSocket.cpp
)
