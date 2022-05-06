/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:44:27 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/06 17:59:14 by bmangin          ###   ########lyon.fr   */
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
    // NIMP *nimp = new NIMP(this, dynamic_cast<Client&>(connection), message);
	ACommand nimp = parseCommand(dynamic_cast<Client&>(connection), message);
	nimp->execute();
	delete nimp;
}

ACommand* 		Server::parseCommand(Client& client, std::string const& msg)
{
	std::vector<std::string> cmd_list = {
		"NIMP",
		"NICK",
		"NAME",
		"PASS"
	};
	typedef void(ACommand::*tpf)(Server *serv, Client &clicli, std::string message);
	tpf fct_list[] = {cmd::NIMP, cmd::NICK, cmd::NAME, cmd::PASS};
	for (int i = 0; i < 4; i++)
	{
		if (::iterator.begin()->compare(cmd_list[i]) == 0)
		{
			return new (fct_list[i])(this, client, msg);
	}
	return new NIMP(this, client, str);
	
}