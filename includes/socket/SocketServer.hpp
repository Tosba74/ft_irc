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
#include "SocketListener.hpp"


class SocketServer: public SocketListener
{
     private:
        int isRunning;
    protected:
        typedef SocketConnection                connection;
        typedef	std::pair<int, connection*>     connectionPair;
	    typedef	std::map<int, connection*>		connectionMap;
	    typedef	std::queue<int>					connectionQueue;

        std::string     hostname;
        int             service;
        
        struct sockaddr_in                      addr;
        socklen_t                               addrsize;
        connectionMap		                    fdConnectionMap;
	    connectionQueue		                    disconnectedFds;



    public:
        SocketServer(std::string const& hostname, int service);
        SocketServer(SocketServer const &src);
        SocketServer &operator=(SocketServer const &rhs);
        ~SocketServer() throw();

        virtual connection*	onConnection(int connectionFd, sockaddr_in& address);
	    virtual void		onDisconnection(connection* connection);
	    virtual void		onMessage(connection* connection, std::string const& message);

        void start();
        void stop();
};