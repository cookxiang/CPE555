#include "package.hpp"



int main(){
    int sockfd;
    Client c1(1510);
    c1.clientinit();
    c1.clientconn();
    sockfd = c1.get_sockfd();
    thread t1_send(Client::str_send, sockfd);
    thread t1_recieve(Client::str_recieve, sockfd);
    t1_send.join();
    t1_recieve.join();
}