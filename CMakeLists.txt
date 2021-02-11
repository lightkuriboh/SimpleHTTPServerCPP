cmake_minimum_required(VERSION 3.13)
project(SimpleCPPServer)

set(CMAKE_CXX_COMPILER "g++-9")
set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_FLAGS "-pthread -I..")

add_executable(SimpleCPPServer
        main.cpp
        libs/EPollUtility.h
        libs/EPollUtility.cpp
        libs/SocketUtility.h
        libs/SocketUtility.cpp
        libs/UnixStandardUtility.h
        libs/UnixStandardUtility.cpp
        HTTPServer/RESTInformation.h
        HTTPServer/RESTInformation.cpp
        libs/RFCWrapper.h
        libs/RFCWrapper.cpp
        HTTPServer/ServerConstants.h
        HTTPServer/HTTPServer.h
        HTTPServer/HTTPServer.cpp
        HTTPServer/TCPSocket.h
        HTTPServer/TCPSocket.cpp
        utils/ConfigParser.h
        utils/ConfigParser.cpp
        utils/FileUtils.h
        utils/FileUtils.cpp
        utils/OtherUtils.h
        utils/OtherUtils.cpp
        HTTPServer/HardConfig.h
)
