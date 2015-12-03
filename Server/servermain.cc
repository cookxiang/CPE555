#include "package.hpp"
using namespace std;

int main(){
    //thread_read = thread();
    //thread_write = thread();
    int connfd;
    Server s1(1510);
    s1.server_addr_init();
    s1.bind_listen();
#if 1  //Thread
    connfd = s1.accept_client();
    thread t1(Server::str_echo,connfd);
    connfd = s1.accept_client();
    thread t2(Server::str_echo,connfd);
    t1.join();
    t2.join();
#endif
    
#if 0
    connfd = s1.accept_client();
    s1.str_echo(connfd);
    s1.closelisten();
    s1.closeconnect();
#endif

}