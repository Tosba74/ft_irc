/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:28:25 by emenella          #+#    #+#             */
/*   Updated: 2022/10/31 17:26:31y bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "socket/SocketServer.hpp"

SocketServer::SocketServer(std::string const& hostname, int port): SocketListener(), isRunning(false), hostname(hostname), port(port), timeout(TIMEOUT) {
   pushFd(sock, POLLIN);
}

SocketServer::SocketServer(SocketServer const &src): SocketListener(src) {
    pushFd(src.sock, POLLIN);
}

SocketServer &SocketServer::operator=(SocketServer const &rhs) {
    SocketListener::operator=(rhs);
    return *this;
}

SocketServer::~SocketServer() {
    popFd(sock);
    #ifdef DEBUG
        std::cout << "SocketServer::~SocketServer()" << std::endl;
    #endif
}

std::string         SocketServer::getHostname() const { return hostname; }

int                 SocketServer::getPort() const { return port; }

std::set<const int>       SocketServer::getOp() const { return opConnection; };

void                SocketServer::setOp(Connection& connection) {
    opConnection.insert(connection.getSock());
}

void	SocketServer::onConnection(int connectionFd, sockaddr_in& address) {
    (void)address;
    #ifdef DEBUG
        std::cout << "New connection from " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
    #endif
    pushFd(connectionFd, POLLIN | POLLHUP);
}

void	SocketServer::onDisconnection(Connection& connection) {
    #ifdef DEBUG
        std::cout << "Disconnection from " << connection.getAddr()<< ":" << connection.getPort() << std::endl;
    #endif
    opConnection.erase(connection.getSock());
    popFd(connection.getSock());
}

void	SocketServer::onMessage(Connection& connection, std::string const& message) {
    (void)connection;
    if (message.empty())
        return;
    // connection << message;
    #ifdef DEBUG
        std::cout << "Message from " << connection.getAddr() << ":" << connection.getPort() << ": " << message << std::endl;
    #endif
}

void SocketServer::start() {
    bind(this->hostname, this->port);
    listen();
    isRunning = true;
    while (isRunning)
    {
        poll();
        try
        {
            std::vector<pollfd>::iterator ite = pollFds.end();
            for (std::vector<pollfd>::iterator it = pollFds.begin(); it != ite; ++it)
            {
                if (it->revents & POLLHUP) {
                    Connection* connection = fdConnectionMap[it->fd];
                    if (connection)
                        onDisconnection(*connection);
                } else if (it->revents & POLLIN) {
                    if (it->fd == sock) {
                        int connectionFd = accept(addr);
                        if (connectionFd != -1)
                            onConnection(connectionFd, addr);
                    } else {
                        Connection* connection = fdConnectionMap[it->fd];
                        receiveAndSend(*connection);
                    }
                }
            }
        }
        catch (SocketException const& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

void SocketServer::stop() {
    std::cout << "Stopping ..." << std::endl;
    isRunning = false;
}

void SocketServer::receiveAndSend(Connection &connection) {
    try {
	    size_t i = 0;
	    size_t pos = 0;
        std::string message;
        
        connection >> message;
        if (message.find("\r\n", i) != std::string::npos) {
    	    while (pos = message.find("\r\n", i), pos != std::string::npos) {
                onMessage(connection, message.substr(i, pos - i));
                message.erase(i, pos - i + 2);
    	    	i = pos + 1;
    	    }
        } else {
            onMessage(connection, message.substr(0, message.size() - 1));
            message.erase(0, message.size());
        }
    } catch (SocketException const& e) {
        std::cerr << e.what() << std::endl;
    } try {
        connection.flush();
    } catch (SocketException const& e) {
        std::cerr << e.what() << std::endl;
    }
}

void SocketServer::pushFd(int fd, int events) {
    pollfd pollfd;
    pollfd.fd = fd;
    pollfd.events = events;
    pollFds.push_back(pollfd);
}

void SocketServer::popFd(int fd) {
    for (std::vector<pollfd>::iterator it = pollFds.begin(); it != pollFds.end(); ++it) {
        if (it->fd == fd) {
            pollFds.erase(it);
            break;
        }
    }
}

void SocketServer::poll() {
    std::cout << "Waiting Resquest" << std::endl;
    std::vector<pollfd>::iterator end = pollFds.end();
    for (std::vector<pollfd>::iterator it = pollFds.begin(); it != end; ++it)
        std::cout << "fd: " << it->fd << " events: " << it->events << " revents " << it->revents << std::endl;
    int ret = ::poll((pollfd *)&pollFds[0], pollFds.size(), -1);
    if (ret == -1)
        throw SocketException("poll");
}

void SocketServer::listen() {
    SocketListener::listen();
    std::cout << "Listening on " << hostname << ":" << port << std::endl;

}
