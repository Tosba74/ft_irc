/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:44:27 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/25 17:43:29 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Server.hpp"
#include "client/command/NICK.hpp"
#include "client/command/JOIN.hpp"
#include "client/command/PASSWORD.hpp"
// #include "client/command/USER.hpp"
// #include "client/command/LIST.hpp"
// #include "client/command/HELP.hpp"
// #include "client/command/KICK.hpp"
// #include "client/command/QUIT.hpp"
// #include "client/command/BAN.hpp"
// #include "client/command/OP.hpp"
#include "/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/i386/types.h"
#include <unistd.h>

Server::Server(int port, std::string password) : SocketServer("127.0.0.1", port), _password(password) {
	_commandes["NICK"] = new NICK(this);
	_commandes["PASSWORD"] = new PASSWORD(this);
	_commandes["JOIN"] = new JOIN(this);
//	_commandes["USER"] = new USER(this);
//	_commandes["LIST"] = new LIST(this);
//	_commandes["HELP"] = new HELP(this);
//	_commandes["KICK"] = new KICK(this);
//	_commandes["QUIT"] = new QUIT(this);
//	_commandes["BAN"] = new BAN(this);
//	_commandes["OP"] = new OP(this);
}

Server::~Server() throw() {
	for (ConnectionMap::iterator it = fdConnectionMap.begin(); it != fdConnectionMap.end(); ++it) {
		delete it->second;
	}
	for (CommandMap::iterator it = _commandes.begin(); it != _commandes.end(); ++it) {
		delete it->second;
	}
}

std::string 	Server::getPassword() const { return _password; }
void			Server::setPassword(std::string password) { _password = password; }

// Le nouveau clents aparait-t-il dans un channel("global") ?
void			Server::onConnection(int connectionFd, sockaddr_in& address) {
	SocketServer::onConnection(connectionFd, address);
    Client *tmp = new Client(connectionFd, address);
	tmp->updateRegister();
	if (tmp->getRegister() == true)
		*tmp << RPL_WELCOME(tmp->getNickname(), tmp->getUsername(), tmp->getHostname());
	std::cout << "New connection IRC from " << *tmp << std::endl;
    fdConnectionMap.insert(std::pair<int, Client*>(connectionFd, tmp));
}

void			Server::onDisconnection(Connection& connection) {
	SocketServer::onDisconnection(connection);
	Client &client = static_cast<Client&>(connection);
	std::cout << "Disconnection IRC of " << client << std::endl;
	fdConnectionMap.erase(connection.getSock());
	delete &client;
}

void			Server::onMessage(Connection& connection, std::string const& message) {
	if (message == "EXIT")
		stop();
	Client &client = static_cast<Client&>(connection);
	client.updateRegister();
	if (client.getRegister() == true)
		client << RPL_WELCOME(client.getNickname(), client.getUsername(), client.getHostname());
	std::cout << "Message from " << client << ": " << message << std::endl;
	parseCommand(message, client);
	SocketServer::onMessage(connection, message);
}

void			Server::parseCommand(std::string const &message, Client& client) {
    std::cout << "\e[34m" << "youpi sa parse !" << std::endl;
	size_t i = 0;
	size_t pos;
	std::vector<std::string> str;

	while (pos = message.find(' ', i), pos != std::string::npos) {
		str.push_back(message.substr(i, pos - i));
		i = pos + 1;
	}
	str.push_back(message.substr(i));
	//print split
	std::cout << "split :" << std::endl;
	for (std::vector<std::string>::iterator it = str.begin(); it != str.end(); ++it)
		std::cout << *it << std::endl;	
	std::cout << "\e[0m";
	
	CommandMap::iterator it = _commandes.find(str[0]);
	if (it != _commandes.end()) {
		ACommand *command = it->second;
		command->execute(client, str);
	}
}

int				Server::createChannel(std::string const &name) {
	if (_channels.find(name) == _channels.end()) {
		_channels.insert(std::pair<std::string, Channel*>(name, new Channel(name)));
		return 1;
	}
	return 0;
}

int				Server::joinChannel(std::string const &name, Client& client) {
	if (_channels.find(name) == _channels.end())
		createChannel(name);
	if (!client.isInChannel(name))
		_channels.at(name)->addClient(client);
	return 0;
}

int				Server::leaveChannel(std::string const &name, Client& client) {
	if (_channels.find(name) != _channels.end()) {
		_channels.at(name)->removeClient(client);
		return 1;
	}
	return 0;
}
