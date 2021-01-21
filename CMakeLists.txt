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
        ApplicationServer/ApplicationServer.h
        ApplicationServer/ApplicationServer.cpp
        ApplicationServer/Requests/RESTInformation.h
        ApplicationServer/Requests/RESTInformation.cpp
        ApplicationServer/Requests/RequestHandlers.h
        ApplicationServer/Requests/RequestHandlers.cpp
        ApplicationServer/ServerConstants.h
        HTTPServer/HTTPServer.h
        HTTPServer/HTTPServer.cpp
        HTTPServer/TCPSocket.h
        HTTPServer/TCPSocket.cpp
        utils/OtherUtils.h
        utils/OtherUtils.cpp
        utils/ConfigParser.h
        utils/ConfigParser.cpp
        constants.h
)
