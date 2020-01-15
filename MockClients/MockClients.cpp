//
// Created by kuribohkute on 15/01/2020.
//

#include "MockClients.h"

void child_process()
{
    sleep(2);
    char msg[1024] = "hieu pro";
    sockaddr_in addr = {0};
    int sockfd, num = 0;
    srandom(getpid());
    /* Create socket and connect to server */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SocketUtility::PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
//#ifdef Timer
    auto start = std::chrono::steady_clock::now();
//#endif
    std::cout << "child " << getpid() << " connected" << std::endl;
    char buffer[1024] = {0};
    while(true){
//        auto sl = (int)(random() % 10) +  1;
        ++num;
        sprintf (msg, "Test message %d from client %d", num, getpid());
        int n = write(sockfd, msg, strlen(msg));	/* Send message */
        auto valread = read( sockfd , buffer, 1024);
        if (num == 100002) {std::exit(EXIT_FAILURE);}
        if (num == 100001) {
            std::cout << "Number of request reached" << std::endl;
//#ifdef Timer
            auto end = std::chrono::steady_clock::now();
            std::cerr << "In milliseconds : "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cerr << '\n' << "In seconds : "
                      << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << std::endl;
//#endif
        }
//        printf("Response from server for client %d: %s\n",getpid(), buffer );
//        sleep(sl);
    }
}

void Client::MockClients::spawningClient(int numberClients) {
    for(int i = 0; i < numberClients; i++) {
        if (fork() == 0) {
            child_process();
            exit(0);
        }
    }
}

