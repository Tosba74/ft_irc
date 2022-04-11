// include socket
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "Socket.hpp"

class SocketConnection: public Socket
{
    protected:
        struct sockaddr_in addr;
        socklen_t       addrsize;
        std::string     writeBuffer;
    public:
        std::string     readBuffer;
        SocketConnection(int sock, sockaddr_in addr);
        SocketConnection(SocketConnection const &src);
        SocketConnection &operator=(SocketConnection const &rhs);
        ~SocketConnection();

        std::string getAddr();
        socklen_t getAddrsize();

        void flush();
        int  receive();

        SocketConnection &operator<<(std::string const &msg);
        SocketConnection &operator>>(std::string &msg);
};