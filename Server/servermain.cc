#include "package.hpp"




int main() {
    int connfd;
    Server s1(555);
    s1.server_addr_init();
    s1.bind_listen();
    while(1) {
        connfd = s1.accept_client();
        char buffer[50];
        cin >> buffer;
        write(connfd, buffer, 50);
        close(connfd);
        cout << "Transfer complete!" << endl;
    }
    
}