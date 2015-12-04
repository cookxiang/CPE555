#include "package.hpp"
mutex n;

void send_client() {
    n.lock();
    Client c1(1510);
    c1.clientinit();
    c1.clientconn();
    n.unlock();
    c1.str_send();
    c1.clientclose();

}

void recieve_client() {
    n.lock();
    Client c2(1515);
    c2.clientinit();
    c2.clientconn();
    n.unlock();
    c2.str_recieve();
    c2.clientclose();

}

int main(){
    thread thread_send(send_client);
    thread thread_recieve(recieve_client);
    thread_send.join();
    thread_recieve.join();
}