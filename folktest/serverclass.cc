#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define bufsize 1024

using namespace std;


class Server{

private:
	int listenfd, connfd;
    int portNum;
    char buffer[bufsize];  
    struct sockaddr_in server_addr, client_addr;
    socklen_t size;

public:
	Server(int portNum):portNum(portNum){
		listenfd = socket(AF_INET, SOCK_STREAM, 0);
    	if (listenfd < 0) {
        	cout << "\nError establishing socket..." << endl;
        	exit(1);
    	}
      	cout << "\nSocket server has been created..." << endl;
	}

	void Serverinit(){
		bzero(&server_addr, sizeof(server_addr));
    	server_addr.sin_family = AF_INET;
   		server_addr.sin_port = htons(portNum);
   		server_addr.sin_addr.s_addr = htons (INADDR_ANY);
	}

	void getready(){
		if ( bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        	cout << "\nError binding connection, the socket has already been established..." << endl;
       		exit(1);
       	}
        cout << "ready to listen" << endl;
        listen(listenfd, 5);
	}

	int waitforclient(){
		size = sizeof(client_addr);
   	    connfd = accept(listenfd, (struct sockaddr*)&client_addr, &size);
    	if(connfd < 0) {
        	cout << "\nError on accepting client..." << endl;
   		}
   		return connfd;
	}

    void send2client(int connfd){
		write(connfd, buffer, bufsize);
	}

	void readclient(int connfd){
		read(connfd, buffer, bufsize);
	}

    void closelisten(){
    	close(listenfd);
    }

    void closeconnect(){
    	close(connfd);
    }

    void str_echo(int sockfd){
    	ssize_t n;
		n=read(sockfd,buffer,bufsize);
    	write(sockfd,buffer,n);
		if(n<0)
    		cout<<"read error"<<endl;
    }
};

int main(){
	int connfd;
	pid_t childpit;
    Server s1(1510);
    s1.Serverinit();
    s1.getready();
    for(; ;){
    	connfd=s1.waitforclient();
        if((childpit=fork())==0){
        	s1.closelisten();
        	s1.str_echo(connfd);
        	exit(0);
        }
        s1.closeconnect();
    }
}