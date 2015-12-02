#include "package.hpp"

int main(){
    int connfd;
    pid_t childpit;
    Server s1(1511);
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