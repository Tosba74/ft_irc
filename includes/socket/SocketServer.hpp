/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:31:47 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/03 01:22:16 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/poll.h>
#include "socket/SocketConnection.hpp"
#include "socket/SocketListener.hpp"
#include "client/REPLY.hpp"

#define TIMEOUT 3*60*1000


class SocketServer: public SocketListener
{
    private:
        int     isRunning;
        void    pushFd(int fd, int events);
        void    popFd(int fd);
        std::string                             hostname;
        int                                     port;
        
    protected:
        typedef SocketConnection                Connection;
        typedef	std::pair<int, Connection*>     ConnectionPair;
	    typedef	std::map<int, Connection*>		ConnectionMap;
	    typedef	std::queue<int>					ConnectionQueue;
        typedef std::set<const int>             ConnectionOperator;

        struct sockaddr_in                      addr;
        socklen_t                               addrsize;
    public:
        ConnectionMap		                    fdConnectionMap;
	    ConnectionQueue		                    disconnectedFds;
        ConnectionOperator                      opConnection;

        std::vector<pollfd>                     pollFds;
        int                                     timeout;

    public:
        SocketServer(std::string const& hostname, int port);
        SocketServer(SocketServer const &src);
        SocketServer &operator=(SocketServer const &rhs);
        ~SocketServer();

        std::string         getHostname() const;
        int                 getPort() const;
        std::set<const int> getOp() const;
        
        void                setOp(Connection& connection);        
        
        virtual void	    onConnection(int connectionFd, sockaddr_in& address);
	    virtual void		onDisconnection(Connection& connection);
	    virtual void		onMessage(Connection& connection, std::string const& message);

        void                start();
        void                stop();
        void                receiveAndSend(Connection& connection);
        void                poll();
        void                listen();
        
        
};