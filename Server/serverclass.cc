#include "package.hpp"
using namespace std;


Server::Server(int portNum):portNum(portNum){
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    cout << "\nSocket server has been created..." << endl;
}
void Server::Serverinit(){
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    server_addr.sin_addr.s_addr = htons (INADDR_ANY);
}

void Server::getready(){
    if ( bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cout << "\nError binding connection, the socket has already been established..." << endl;
        exit(1);
    }
    cout << "ready to listen" << endl;
    listen(listenfd, 5);
}

int Server::waitforclient(){
    size = sizeof(client_addr);
    connfd = accept(listenfd, (struct sockaddr*)&client_addr, &size);
    if(connfd < 0) {
        cout << "\nError on accepting client..." << endl;
    }
    return connfd;
}

void Server::send2client(int connfd){
    write(connfd, buffer, bufsize);
}

void Server::readclient(int connfd){
    read(connfd, buffer, bufsize);
}

void Server::closelisten(){
    close(listenfd);
}

void Server::closeconnect(){
    close(connfd);
}

void Server::str_echo(int sockfd){
    ssize_t n;
    n=read(sockfd,buffer,bufsize);
    write(sockfd,buffer,n);
    if(n<0)
        cout<<"read error"<<endl;
}


