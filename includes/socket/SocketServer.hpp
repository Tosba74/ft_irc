#pragma once
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
#include <queue>
#include <pthread.h>
#include "Socket.hpp"
#include "SocketConnection.hpp"
#include "SocketListener.hpp"


class SocketServer: public SocketListener
{
     private:
        int isRunning;
    protected:
        typedef SocketConnection                Connection;
        typedef	std::pair<int, Connection*>     ConnectionPair;
	    typedef	std::map<int, Connection*>		ConnectionMap;
	    typedef	std::queue<int>					ConnectionQueue;
        typedef void * (*THREADFUNCPTR)(void *);

        std::string                             hostname;
        int                                     service;
        
        struct sockaddr_in                      addr;
        socklen_t                               addrsize;
        ConnectionMap		                    fdConnectionMap;
	    ConnectionQueue		                    disconnectedFds;



    public:
        SocketServer(std::string const& hostname, int service);
        SocketServer(SocketServer const &src);
        SocketServer &operator=(SocketServer const &rhs);
        ~SocketServer() throw();

        virtual Connection*	onConnection(int connectionFd, sockaddr_in& address);
	    virtual void		onDisconnection(Connection* connection);
	    virtual void		onMessage(Connection* connection, std::string const& message);

        void start();
        void stop();
        void threadConnection(Connection* connection);
};