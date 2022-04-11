#pragma once
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
#include <queue>
#include "Socket.hpp"
#include "SocketConnection.hpp"


class SocketServer: public Socket
{
    protected:
        typedef SocketConnection                connection;
        typedef	std::pair<int, connection*>     connectionPair;
	    typedef	std::map<int, connection*>		connectionMap;
	    typedef	std::queue<int>					connectionQueue;

        struct sockaddr_in                      addr;
        socklen_t                               addrsize;
        connectionMap		                    fdConnectionMap;
	    connectionQueue		                    disconnectedFds;



    public:
        SocketServer(int port);
        SocketServer(SocketServer const &src);
        SocketServer &operator=(SocketServer const &rhs);
        ~SocketServer();

        virtual connection*	onConnection(int connectionFd, sockaddr_in const& address);
	    virtual void		onDisconnection(connection* connection);
	    virtual void		onMessage(connection* connection, std::string const& message);

        void start();
        void stop();
};