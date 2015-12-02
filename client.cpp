#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
using namespace std;

int main() {
//global variables
    int sockfd;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char* ip = "127.0.0.1";
//addr struct
    struct sockaddr_in server_addr;
//socket()
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    cout << "\n=> Socket client has been created..." << endl;
//init addr struct
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
//connect()
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
        cout << "=> Connection to the server port number: " << portNum << endl;
    }
//transfer
    cout << "=> Awaiting confirmation from the server..." << endl;
    read(sockfd, buffer, bufsize);
    cout << "=> Connection confirmed, you are good to go...";
    cout << "\n\n=> Enter # to end the connection\n" << endl;
    
    do {
        cout << "Client: ";
        do {
            cin >> buffer;
            write(sockfd, buffer, bufsize);
            if (*buffer == '#') {
                read(sockfd, buffer, bufsize);
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != 42);
        
        cout << "Server: ";
        do {
            read(sockfd, buffer, bufsize);
            cout << buffer << " ";
            if (*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }
            
        } while (*buffer != 42);
        cout << endl;
        
    } while (!isExit);
    cout << "\n=> Connection terminated.\nGoodbye...\n";
    
    close(sockfd);
    return 0;
    
    
}