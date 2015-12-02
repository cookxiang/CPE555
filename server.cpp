#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main() {
//global variables
    int listenfd, connfd;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
//addr struct
    struct sockaddr_in server_addr, client_addr;
    socklen_t size;
//socket()
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    cout << "\nSocket server has been created..." << endl;
//init addr struct
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    server_addr.sin_addr.s_addr = htons (INADDR_ANY);
//bind()
    if ( bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cout << "\nError binding connection, the socket has already been established..." << endl;
        exit(1);
    }
    
    cout << "ready to listen" << endl;
//listen()
    listen(listenfd, 5);
//accept()
    size = sizeof(client_addr);
    connfd = accept(listenfd, (struct sockaddr*)&client_addr, &size);
    if(connfd < 0) {
        cout << "\nError on accepting..." << endl;
    }
    
//transfer!!!!!!!!!!!
    while (connfd > 0) {
        strcpy(buffer, "Server connected!!!");
        write(connfd, buffer, bufsize);
        cout << "Connected with the client1 #, good to go!!!" << endl;
        
        
        cout << "Client: ";
        do {
            read(connfd, buffer, bufsize);
            cout << buffer << " ";
            if(*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '*');
        
        do {
            cout << "\nServer: ";
            do {
                cin >> buffer;
                write(connfd, buffer, bufsize);
                if (*buffer == '#') {
                    write(connfd, buffer, bufsize);
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');
            
            cout << "Client: ";
            do {
                read(connfd, buffer, bufsize);
                cout << buffer << " ";
                if (*buffer == '#') {
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');
        } while (!isExit);
    
    
        cout << "\n\n=> Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
        close(connfd);
        cout << "\nGoodbye..." << endl;
        isExit = false;
        exit(1);
    }

    close(listenfd);

    return 0;


}