#ifndef PACKAGE_HPP_
#define PACKAGE_HPP_


#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <thread>

#define bufsize 1024
//Client member function
class Client {
private:
    int sockfd;
    int portNum;
    char buffer[bufsize];
    struct sockaddr_in server_addr;
public:
    Client(int portNum);
    void clientinit();
    void clientconn();
    void str_cli();
    void clientclose();
};
//Server member function
class Server{
private:
    int listenfd, connfd;
    int portNum;
    char buffer[bufsize];
    struct sockaddr_in server_addr, client_addr;
    socklen_t size;
public:
    Server(int portNum);
    void server_addr_init();
    void bind_listen();
    int accept_client();
    void send2client(int connfd);
    void readclient(int connfd);
    void closelisten();
    void closeconnect();
    static void str_echo(int sockfd);
};


#endif