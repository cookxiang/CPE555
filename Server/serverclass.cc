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
    cout << "read:buffer:" << re << endl; ////////////
    queue.push_back(re);
    for(int i=0; i<queue.size(); i++) {  ///////////
        cout << "read:queue[" << i << "]:" << queue[i] << endl;
    }
    rw.unlock();
}

void Server::str_write(int sockfd) {
    while(true)
    {
        rw.lock();
        if(!queue.empty())
        {
            cout << "write get in critical: connfd: " << sockfd << "---------------------------------------" << endl;
            cout << "write:connfd:" << sockfd << endl; ////////
            for(int i=0; i<queue.size(); i++) {  ///////////
                cout << "write:before erase:queue[" << i << "]:" << queue[i] << endl;
            }
            char buffer[bufsize];
            strcpy(buffer, queue[0].c_str());
            cout << "write:buffer copied from queue[0]:" << buffer << endl;
            cout << "write:buffer[0]:" << buffer[0] <<endl;
            if((int)(buffer[0]-'0') == sockfd) {
                cout << "write: get in if(bufer[0] == sockfd)!" << endl;
                queue.erase( queue.begin() );
                for(int i=0; i<queue.size(); i++) {  ///////////
                    cout << "write:after erase:queue[" << i << "]:" << queue[i] << endl;
                }
                write(sockfd, buffer, bufsize);
            }
        cout << "---------------------------------------" << "write get out critical: connfd: " << sockfd <<endl;
        }
        rw.unlock();
    }
}


