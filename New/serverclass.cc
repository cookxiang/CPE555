#include "package.hpp"

vector<string> queue;
map<string,int> client_list;
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

void Server::recieve_client_list(int sockfd) {
    char buffer[bufsize];
    read(sockfd, buffer, bufsize);
    string name(buffer);
    client_list[name] = sockfd;
    for (map<string,int>::iterator itr = client_list.begin(); itr != client_list.end(); ++itr) {
        cout << "\nname: " << itr->first << endl;
        cout << "connfd :" << itr->second << endl;
    }
}

void Server::send_client_list(int sockfd) {
    char buffer[bufsize];
    for (map<string,int>::iterator itr = client_list.begin(); itr != client_list.end(); ++itr) {
        string info = '*' + to_string(itr->second) + itr->first;
        strcpy(buffer, info.c_str());
        write(sockfd, buffer, bufsize);
    }
}

void Server::str_read(int sockfd) {
    while(1){
        char buffer[bufsize];
        read(sockfd, buffer, bufsize); //read()>=0 means client is not closed
        rw.lock();
        string re(buffer);
        cout << "read:buffer:" << re << endl; ////////////
        queue.push_back(re);
        for(int i=0; i<queue.size(); i++) {  ///////////
            cout << "read:queue[" << i << "]:" << queue[i] << endl;
        }
        rw.unlock();
        
        if (buffer[1] == '#') {
            cout << "read: ready to quit" << endl;
            for (map<string,int>::iterator itr = client_list.begin(); itr != client_list.end(); ++itr) {
                if (itr->second == sockfd) {
                    client_list.erase(itr);
                }
            }
            return;
        }
    }
}

void Server::str_write(int sockfd) {
    while(1)
    {
        rw.lock();
        if(!queue.empty())
        {
            char buffer[bufsize];
            strcpy(buffer, queue[0].c_str());
            if((int)(buffer[0]-'0') == sockfd) {
                cout << "\n[write get in critical: connfd: " << sockfd << "]" << endl;
                cout << "write:connfd:" << sockfd << endl; ////////
                for(int i=0; i<queue.size(); i++) {  ///////////
                    cout << "write:before erase:queue[" << i << "]:" << queue[i] << endl;
                }
                cout << "write:buffer copied from queue[0]:" << buffer << endl;
                queue.erase( queue.begin() );
                write(sockfd, buffer, bufsize);
                if (buffer[1] == '#') {
                    cout << "write: ready to quit" << endl;
                    close(sockfd);
                    rw.unlock();
                    return;
                }
            }
            cout << "[write get out critical: connfd: " << sockfd << "]\n" << endl;
        }
        rw.unlock();
    }
}


