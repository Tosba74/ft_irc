#pragma once
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket
{
    protected:
        int sock;

    public:
        Socket(int sock);
        Socket(int type, int opt, int proto);
        Socket(Socket const &src);
        virtual Socket &operator=(Socket const &rhs);
        virtual ~Socket();

        class SocketException: public std::exception
        {
            private:
                std::string msg;
            public:
                SocketException(std::string const &message) throw(): msg(message) {}
                virtual ~SocketException() throw() {}
                virtual const char *what() const throw(){ return msg.c_str();}
        };
        int getSock();
        void setSock(int sock);
        void close();
};