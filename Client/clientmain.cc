#include "package.hpp"
int main(){
    Client c1(1510);
    c1.clientinit();
    c1.clientconn();
    c1.str_cli();
    c1.clientclose();
}