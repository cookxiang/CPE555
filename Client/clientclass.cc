#include "package.hpp"
using namespace std;


Client::Client(int portNum): portNum(portNum){
    //socket()
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    cout << "\n=> Socket client has been created..." << endl;
}

void Client::clientinit(){
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
}

void Client::clientconn(){
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server port number: " << portNum << endl;
}
void Client::str_cli(){
    //client write to socket
    cout << "client: ";
    cin >> buffer;
    write(sockfd, buffer, bufsize);
    //client read from socket
    cout << "server: ";
    read(sockfd, buffer, bufsize);
    cout << buffer << " ";
}
void Client::clientclose(){
    close(sockfd);
}
