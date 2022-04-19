/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:31:47 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/19 23:36:47 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/poll.h>
#include "socket/SocketConnection.hpp"
#include "socket/SocketListener.hpp"

#define TIMEOUT 3*60*1000


class SocketServer: public SocketListener
{
     private:
        int isRunning;
        void pushFd(int fd, int events);
        void popFd(int fd);
    protected:
        typedef SocketConnection                Connection;
        typedef	std::pair<int, Connection*>     ConnectionPair;
	    typedef	std::map<int, Connection*>		ConnectionMap;
	    typedef	std::queue<int>					ConnectionQueue;

        std::string                             hostname;
        int                                     service;
        
        struct sockaddr_in                      addr;
        socklen_t                               addrsize;
        ConnectionMap		                    fdConnectionMap;
	    ConnectionQueue		                    disconnectedFds;

        std::vector<pollfd>                     pollFds;
        int                                     timeout;



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
        void receiveAndSend(Connection* connection);
        void poll();
};