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
        pthread_t       thread;
        std::string     readBuffer;
        SocketConnection(int sock, sockaddr_in &addr) throw();
        SocketConnection(SocketConnection const &src) throw();
        SocketConnection &operator=(SocketConnection const &rhs);
        ~SocketConnection();

        std::string getAddr();
        socklen_t getAddrsize();
        int getPort();

        void flush();
        int  receive();
        int isConnected(){return this->getSock() != -1;}

        SocketConnection &operator<<(std::string const &msg);
        SocketConnection &operator>>(std::string &msg);
};