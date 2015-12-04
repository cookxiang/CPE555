#include "package.hpp"

mutex m;

void read_server() {
    int connfd1, connfd2;
    m.lock();
    Server s1(1510); // read port.
    s1.server_addr_init();
    s1.bind_listen();
    m.unlock();
//t1 read
    connfd1 = s1.accept_client();
    thread t1_read(Server::str_read, connfd1);
//t2 read
    connfd2 = s1.accept_client();
    thread t2_read(Server::str_read, connfd2);
//t1,t2 join
    t1_read.join();
    t2_read.join();
}


void write_server() {
    int connfd1,connfd2;
    m.lock();
    Server s2(1515);
    s2.server_addr_init();
    s2.bind_listen();
    m.unlock();
//t1 write
    connfd1 = s2.accept_client();
    //thread t1_write(Server::str_write,connfd1);
//t2 write
    connfd2 = s2.accept_client();
    cout << "connfd1:" << connfd1 << endl;
    cout << "connfd2:" << connfd2 << endl;
    thread t1_write(Server::str_write,connfd1);
    thread t2_write(Server::str_write,connfd2);
    t1_write.join();
    t2_write.join();
}




int main() {
    thread thread_read(read_server);
    thread thread_write(write_server);
    thread_read.join();
    thread_write.join();
    
}
