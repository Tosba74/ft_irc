/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:44:27 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/07 15:05:58 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Server.hpp"
#include "client/command/NIMP.hpp"
#include "client/command/NICK.hpp"

Server::Server(int port, std::string password) : SocketServer("127.0.0.1", port), _password(password)
{
	_commandes["NIMP"] = new NIMP(this);
	_commandes["NICK"] = new NICK(this);
}

Server::~Server() throw()
{
	for (ConnectionMap::iterator it = fdConnectionMap.begin(); it != fdConnectionMap.end(); ++it)
	{
		delete it->second;
	}

}

std::string 	Server::getPassword() const
{
	return _password;
}

void			Server::setPassword(std::string password)
{
	_password = password;
}

void Server::onConnection(int connectionFd, sockaddr_in& address)
{
	SocketServer::onConnection(connectionFd, address);
    Client *tmp = new Client(connectionFd, address);
    fdConnectionMap.insert(std::pair<int, Client*>(connectionFd, tmp));
	std::cout << "New connection IRC from " << inet_ntoa(address.sin_addr) << ":" << address.sin_port << std::endl;
}
void Server::onDisconnection(Connection& connection)
{
	std::cout << "Disconnection IRC of " << connection.getAddr() << ":" << connection.getPort() << std::endl;
	SocketServer::onDisconnection(connection);
}
void Server::onMessage(Connection& connection, std::string const& message)
{
	SocketServer::onMessage(connection, message);
	std::cout << "Message IRC from " << connection.getAddr() << ":" << connection.getPort() << " = " << message << std::endl;
	parseCommand(message, dynamic_cast<Client&>(connection));
}

void 		Server::parseCommand(std::string const &message, Client& client)
{
	size_t i = 0;
	size_t pos;
	std::vector<std::string> str;

	while (pos = message.find(' ', i), pos != std::string::npos)
	{
		str.push_back(message.substr(i, pos - i));
		i = pos + 1;
	}
	str.push_back(message.substr(i));
	CommandMap::iterator it = _commandes.find(str[0]);
	if (it != _commandes.end())
	{
		ACommand *command = it->second;
		command->execute(client, str.begin(), str.end());
	}
	
}