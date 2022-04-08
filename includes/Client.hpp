#pragma once
#include <iostream>
#include <string>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class Client
{
    private:
        int port;
        int client_fd;
        int server_fd;
        socklen_t client_in_size;
        std::string address;
        struct sockaddr_in client_in;
    
    public:
        Client(int id, int sock, std::string address);
        Client(Client const &src);
        Client &operator=(Client const &rhs);
        ~Client();

        int send(std::string msg);
        int recv(std::string &msg);

        // getters
        int getFd();
        std::string getAddress();
         // setters
        void setFd(int id);
        void setAddress(std::string address);



};