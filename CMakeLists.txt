cmake_minimum_required(VERSION 3.13)
project(SimpleCPPServer)

set(CMAKE_CXX_COMPILER "g++-9")
set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_FLAGS "-pthread -I..")

add_executable(SimpleCPPServer
        main.cpp
        HTTPServer/HardConfig.h
        HTTPServer/HTTPServer.h
        HTTPServer/HTTPServer.cpp
        HTTPServer/TCPSocket.h
        HTTPServer/TCPSocket.cpp
        libs/EPollUtility.h
        libs/EPollUtility.cpp
        libs/RFCWrapper.h
        libs/RFCWrapper.cpp
        libs/SocketUtility.h
        libs/SocketUtility.cpp
        libs/UnixStandardUtility.h
        libs/UnixStandardUtility.cpp
        utils/CommonUtils.h
        utils/ConfigParser.h
        utils/FileUtils.h
        utils/ReturnStatus.h
        utils/SignalHandlers.h
)
