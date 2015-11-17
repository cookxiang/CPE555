#ifndef Client_hpp_
#define Clinet_hpp_

class Client{ 
private:
  int sockfd;
  int portNum;
public:
  Client(){}; 
  int socket();
  int connect();
  write();
  read();
  int close();
  //...       
};

#endif
