#pragma once

#include "socket/SocketServer.hpp"
#include "irc/Channel.hpp"
#include "user/Client.hpp"

class Server: public SocketServer
{
	private:
		std::string _password;
	public:
	Server(int port, std::string password);
	Server(SocketServer const &src);
	Server &operator=(SocketServer const &rhs);
	~Server() throw();

	Connection*	onConnection(int connectionFd, sockaddr_in& address);
	void		onDisconnection(Connection* connection);
	void		onMessage(Connection* connection, std::string const& message);
};