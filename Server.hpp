#ifndef Server_hpp_
#define Server_hpp_

class Server{
private:
	int sockfd;
	int portNum;
	//...
public:
  Server();   
  socket();
  bind();
  listen();
  accept();
  send();
  recv();
  close();
//...
};

#endif
