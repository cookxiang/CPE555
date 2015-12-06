#include "package.hpp"
using namespace std;

map <string, int> usermap;
map<string,int>::iterator it;

Client::Client(int portNum, const char* IP): portNum(portNum),IP(IP){
    //socket()
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    cout << "\n=> Socket client has been created..." << endl;
}

void Client::clientinit(){

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET,IP,&server_addr.sin_addr);
}

void Client::clientconn(){
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server port number: " << portNum << endl;
    else{
        cout<<"=>error connecting to server,please restart.\n";
        close(sockfd);
        exit(1);
    }
}

int Client::get_sockfd() {
    return sockfd;
}
void Client::clientclose(){
    close(sockfd);
}
/*
void Client::str_cli(){
    //client write to socket
    cout << "client: ";
    cin >> buffer;
    write(sockfd, buffer, bufsize);
    //client read from socket
    cout << "server: ";
    read(sockfd, buffer, bufsize);
    cout << buffer << " ";
}
 */

void Client::str_send(int sockfd) {
    while(1) {
        char buffer[bufsize];
       // cout << "Client: ";
        cin >> buffer;
        if(buffer[0]=='@'){
            string name(buffer+1);
            it = usermap.find(name);
          //  if (it != usermap.end())
            //    usermap.erase (it);
            continue;
        }
        string message(buffer);
        message = to_string(it->second) + message;
        strcpy(buffer, message.c_str());
        write(sockfd, buffer, bufsize);
        if(buffer[1] == '#'){
            cout << "thread_send is closed"<<endl;
            return;
        }
    }   
}

void Client::str_recieve(int sockfd) {
    while(1) {
        char buffer[bufsize];
        read(sockfd, buffer, bufsize);
        int fd;
        //cout << "done reading" << endl;
        if(buffer[0]=='*' && buffer[1]!='#'){
            int fd=buffer[1]-'0';
            string name(buffer+3);
            usermap[name]=fd;
        }
        if(buffer[0]!='*' && buffer[1]!='#'){
            cout << "server: ";
            cout << buffer << endl;
        }
        if(buffer[1]=='!'){
            cout<< "users online: "<<endl;
            for(map<string, int >::iterator i=usermap.begin(); i!=usermap.end(); ++i)
                cout<<"User: "<<i->first<<"  ID: "<<i->second<<endl;;
            usermap.clear();
            cout<<"Choose the user you want to communicate with(start with @, e.g. @Tim): ";
        }
        if(buffer[1]=='#') {
            close(sockfd);
            cout<<"thread_recieve is closed"<<endl;
            cout<<"client closed."<<endl;
            return;
        }
    }
}

void Client::login_info(string username){
    char buffer[bufsize];
    buffer[0]='@';
    strcpy(buffer+1, username.c_str());
    write(sockfd, buffer, bufsize);
}






