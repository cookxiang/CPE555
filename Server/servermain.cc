#include "package.hpp"




int main() {
    
    vector<int> connfd;
    vector<thread> t_read;
    vector<thread> t_write;
    int i=0;
    
    
    Server s1(1510); // read port
    s1.server_addr_init();
    s1.bind_listen();
    
    while(1) {
        connfd.push_back(s1.accept_client());
        cout << "connfd[" << i << "] = " << connfd.back() << endl;
        s1.recieve_client_list(connfd.back());
        s1.send_client_list(connfd.back());
        t_read.push_back(thread(Server::str_read, connfd.back()));
        t_write.push_back(thread(Server::str_write, connfd.back()));
        i++;
    }

    
}