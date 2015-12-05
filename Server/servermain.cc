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
        t_read.push_back(thread(Server::str_read, connfd.back()));
        t_write.push_back(thread(Server::str_write, connfd.back()));
        i++;
    }
    /*
    int connfd1, connfd2, connfd3;

    connfd1 = s1.accept_client();
    connfd2 = s1.accept_client();
    connfd3 = s1.accept_client();
    //cout connfd1, connfd2
    cout << "connfd1:" << connfd1 << endl;
    cout << "connfd2:" << connfd2 << endl;
    cout << "connfd3:" << connfd3 << endl;
    thread t1_read(Server::str_read, connfd1);
    thread t2_read(Server::str_read, connfd2);
    thread t3_read(Server::str_read, connfd3);
    thread t1_write(Server::str_write,connfd1);
    thread t2_write(Server::str_write,connfd2);
    thread t3_write(Server::str_write,connfd3);
    //t1,t2 join
    t1_read.join();
    t2_read.join();
    t3_read.join();
    t1_write.join();
    t2_write.join();
    t3_write.join();
     */
}