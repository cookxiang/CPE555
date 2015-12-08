#include "package.hpp"




int main() {
    int connfd;
    Server s1(10500);
    s1.server_addr_init();
    s1.bind_listen();
    while(1) {
        connfd = s1.accept_client();
        cout << "Connected!" << endl;
        char buffer1[50]="1.5";
        char buffer2[50]="2.4";
        write(connfd, buffer1, 50);
        write(connfd, buffer2, 50);
        close(connfd);
        cout << "Transfer complete!" << endl;
    }
    
}