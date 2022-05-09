/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:44:27 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/09 16:24:41 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Server.hpp"

Server::Server(int port, std::string password) : SocketServer("127.0.0.1", port), _password(password)
{
	_commandes["NICK"] = new NICK(this);
}

Server::~Server() throw()
{
	for (ConnectionMap::iterator it = fdConnectionMap.begin(); it != fdConnectionMap.end(); ++it)
	{
		delete it->second;
	}
	for (CommandMap::iterator it = _commandes.begin(); it != _commandes.end(); ++it)
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
	std::cout << "New connection IRC from " << *tmp << std::endl;
    fdConnectionMap.insert(std::pair<int, Client*>(connectionFd, tmp));
}
void Server::onDisconnection(Connection& connection)
{
	Client &client = static_cast<Client&>(connection);
	std::cout << "Disconnection IRC of " << client << std::endl;
	SocketServer::onDisconnection(connection);
	fdConnectionMap.erase(connection.getSock());
}
void Server::onMessage(Connection& connection, std::string const& message)
{
	SocketServer::onMessage(connection, message);
	if (message == "EXIT")
	{
		stop();
	}
	Client &client = static_cast<Client&>(connection);
	std::cout << "Message from " << client << ": " << message << std::endl;
	parseCommand(message, client);
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