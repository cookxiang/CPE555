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
#define bufsize 1024
class Client{
private:
	int sockfd;
	int portNum;
    char buffer[bufsize];
    struct sockaddr_in server_addr;
public:
    Client(int portNum): portNum(portNum){
    	//socket()
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    	if (sockfd < 0) {
        	cout << "\nError establishing socket..." << endl;
        	exit(1);
    	}
  		cout << "\n=> Socket client has been created..." << endl;
   	}
    
    void clientinit(){
    	bzero(&server_addr, sizeof(server_addr));
   		server_addr.sin_family = AF_INET;
    	server_addr.sin_port = htons(portNum);
    }

    void clientconn(){
    	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) 
        	cout << "=> Connection to the server port number: " << portNum << endl;
    }
    void str_cli(){
    		//client write to socket
    		cout << "client: ";
    		cin >> buffer;
    		write(sockfd, buffer, bufsize);
    		//client read from socket
    		cout << "server: ";
    		read(sockfd, buffer, bufsize);
    		cout << buffer << " ";				
    }
    void clientclose(){
    	close(sockfd);
    }
};

int main(){
	Client c1(1510);
    c1.clientinit();
    c1.clientconn();
    c1.str_cli();
    c1.clientclose();
}