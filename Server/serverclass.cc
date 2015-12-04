#include "package.hpp"
vector<string> queue;
mutex rw;


Server::Server(int portNum):portNum(portNum){
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    cout << "\nSocket server has been created..." << endl;
}
void Server::server_addr_init(){
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    server_addr.sin_addr.s_addr = htons (INADDR_ANY);
}

void Server::bind_listen(){
    if ( bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cout << "\nError binding connection, the socket has already been established..." << endl;
        exit(1);
    }
    cout << "ready to listen" << endl;
    listen(listenfd, 5);
}

int Server::accept_client(){
    size = sizeof(client_addr);
    connfd = accept(listenfd, (struct sockaddr*)&client_addr, &size);
    if(connfd < 0) {
        cout << "\nError on accepting client..." << endl;
    }
    cout << "Client connected! Port Number: " << portNum << endl;
    return connfd;
}

void Server::closelisten(){
    close(listenfd);
}

void Server::closeconnect(){
    close(connfd);
}

void Server::str_echo(int sockfd){
    char buffer[bufsize];
    ssize_t n;
    n=read(sockfd, buffer, bufsize);
    write(sockfd,buffer,n);
    if(n<0)
        cout<<"read error"<<endl;
}

void Server::str_read(int sockfd) {
    char buffer[bufsize];
    read(sockfd, buffer, bufsize);
    rw.lock();
    string re(buffer);
    queue.push_back(re);
    cout << re << endl;
    rw.unlock();
}

void Server::str_write(int sockfd) {
    //char buffer[bufsize];
    //strcpy(buffer, queue[0].c_str());
    //queue.erase( queue.begin() );
    //write(sockfd, buffer, bufsize);
    while(true)
    {
        rw.lock();
        if(!queue.empty())
        {
            char buffer[bufsize];
            strcpy(buffer, queue[0].c_str());
            queue.erase( queue.begin() );
            write(sockfd, buffer, bufsize);
        }
        rw.unlock();
    }
}


