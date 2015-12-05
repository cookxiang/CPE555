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
#include <vector>
#include <string>
#include <mutex>

#define bufsize 1024
//Client member function
using namespace std;

class Client {
private:
    int sockfd;
    int portNum;
    struct sockaddr_in server_addr;
public:
    Client(int portNum);
    void clientinit();
    void clientconn();
    int get_sockfd();
    //static void str_cli();
    //void clientclose();
    static void str_send(int sockfd);
    static void str_recieve(int sockfd);
};

//Server member function
class Server{
private:
    int listenfd, connfd;
    int portNum;
    struct sockaddr_in server_addr, client_addr;
    socklen_t size;
public:
    Server(int portNum);
    void server_addr_init();
    void bind_listen();
    int accept_client();
    //void closelisten();
    //void closeconnect();
    static void str_echo(int sockfd); // string echo
    static void str_read(int sockfd); // string read
    static void str_write(int sockfd); // string write
};


#endif