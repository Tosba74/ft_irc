/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:44:27 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/04 19:42:31 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Server.hpp"
#include "client/ACommand.hpp"
#include "client/command/NIMP.hpp"

Server::Server(int port, std::string password) : SocketServer("127.0.0.1", port), _password(password)
{
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
	std::cout << "Message IRC from " << connection.getAddr() << ":" << connection.getPort() << " = " << message;
	ACommand *command = parseCommand(dynamic_cast<Client&>(connection), message);
	command->execute();
	delete command;
}

ACommand 		*Server::parseCommand(Client &client, std::string const &message)
{
	size_t i = 0;
	size_t pos;
	std::vector<std::string> command;

	while (pos = message.find(' ', i), pos != std::string::npos)
	{
		command.push_back(message.substr(i, pos - i));
		i = pos + 1;
	}
	command.push_back(message.substr(i));
	for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it)
	{
		std::cout << "From: " << client.getAddr() << " >> "<< *it << std::endl;
	}
	return new NIMP(this, dynamic_cast<Client&>(client), message);;
}