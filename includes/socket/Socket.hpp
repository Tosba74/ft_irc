#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket
{
    protected:
        int sock;

    public:
        Socket(int type = SOCK_STREAM, int opt = SOCK_NONBLOCK, int proto = IPPROTO_IP);
        Socket(int sock);
        Socket(Socket const &src);
        virtual Socket &operator=(Socket const &rhs);
        virtual ~Socket();

        int getSock();
        void setSock(int sock);
        void close();
};