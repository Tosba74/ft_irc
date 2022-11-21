/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:44:27 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/21 18:08:52 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Server.hpp"
#include "client/command/NICK.hpp"
#include "client/command/PASS.hpp"
#include "client/command/JOIN.hpp"
#include "client/command/USER.hpp"
#include "client/command/LIST.hpp"
#include "client/command/MODE.hpp"
#include "client/command/OPER.hpp"
#include "client/command/AWAY.hpp"
#include "client/command/PRIVMSG.hpp"
#include "client/command/ME.hpp"
#include "client/command/PING.hpp"
// #include "client/command/HELP.hpp"
#include "client/command/KICK.hpp"
// #include "client/command/QUIT.hpp"
// #include "client/command/BAN.hpp"
// #include "/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/i386/types.h"
#include <unistd.h>

#include "client/Client.hpp"

Server::Server(int port, std::string password) : SocketServer("0.0.0.0", port), _password(password) {
	_commandes["NICK"] = new NICK(this);
	_commandes["PRIVMSG"] = new PRIVMSG(this);
	_commandes["PASS"] = new PASS(this);
	_commandes["JOIN"] = new JOIN(this);
	_commandes["MSG"] = new PRIVMSG(this);
	_commandes["USER"] = new USER(this);
	_commandes["MODE"] = new MODE(this);
	_commandes["LIST"] = new LIST(this);
	_commandes["OPER"] = new OPER(this);
	_commandes["AWAY"] = new AWAY(this);
	_commandes["PING"] = new PING(this);
	_commandes["ME"] = new ME(this);
//	_commandes["HELP"] = new HELP(this);
	_commandes["KICK"] = new KICK(this);
//	_commandes["QUIT"] = new QUIT(this);
//	_commandes["BAN"] = new BAN(this);
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

Client*			Server::getClient(const std::string& name) const {
	for (ConnectionMap::const_iterator it = fdConnectionMap.begin(); it != fdConnectionMap.end(); ++it) {
		Client*		clicli = static_cast<Client*>(it->second);
		if (!clicli->getNickname().compare(name))
			return clicli;
	}
	return NULL;
}
Channel*		Server::getChannel(const std::string& name) const {
	if (_channels.find(name) != _channels.end())
		return _channels.at(name);
	// for (ChannelMap::const_iterator it = _channels.begin(); it != _channels.end(); ++it) {
		// Channel*		chan = static_cast<Channel*>(it->second);
		// if (!chan->getName().compare(name))
			// return chan;
	// }
	return NULL;
}

void			Server::setPassword(std::string password) { _password = password; }
		
void			Server::onConnection(int connectionFd, sockaddr_in& address) {
	SocketServer::onConnection(connectionFd, address);
    Client *tmp = new Client(connectionFd, address);
	tmp->setHostname(getHostname());
	isAuthenticate(*tmp);
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
	if (!message.compare("EXIT"))
		stop();
	Client &client = static_cast<Client&>(connection);
	std::cout << "Message from " << client << ": " << message << std::endl;
	parseCommand(message, client);
	if (!client.getRegister()) {
		isAuthenticate(client);
		return ;
	}
	SocketServer::onMessage(connection, message);
}

void			Server::parseCommand(std::string const &message, Client& client) {
	size_t i = 0;
	size_t pos;
	std::vector<std::string> str;

    std::cout << "\e[31mMSG: " << message << "\e[0m" << std::endl;
	while (pos = message.find(' ', i), pos != std::string::npos) {
		str.push_back(message.substr(i, pos - i));
		i = pos + 1;
	}
	str.push_back(message.substr(i, pos - i));
	
	//print split
	std::cout << "\e[34msplit : " << message << std::endl;
	for (std::vector<std::string>::iterator it = str.begin(); it != str.end(); ++it)
		std::cout << *it << std::endl;	
	std::cout << "**********" << std::endl;	
	// a delete apres

	CommandMap::iterator it = _commandes.find(str[0]);
	if (it != _commandes.end()) {
		ACommand *command = it->second;
		if (str[1].compare("-help") == true)
			command->descr(client);
		else
			command->execute(client, str);
	}
	else
		client << ERR_UNKNOWNCOMMAND(str[0]);
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
	// if (!client.isInChannel(name))
	_channels.at(name)->addClient(client);
	client.setCurrchan(name);
	std::cout << "\e[94mClient(" << client << ")addressChan :" << _channels.at(name) << "\e[0m" << std::endl;
	return 0;
}

int				Server::leaveChannel(std::string const &name, Client& client) {
	if (_channels.find(name) != _channels.end()) {
		_channels.at(name)->removeClient(client);
		client.setCurrchan(name);
		return 1;
	}
	return 0;
}

bool			Server::isAuthenticate(Client& client) {
	//Check password
	if (!getPassword().compare(client.getPass()))
		client.updateRegister();
	else
		std::cout << "\e[31mIncorrect Password\e[0m" << std::endl;
	// log console + bool
	if (client.getRegister() == true) {
		std::cout << "\e[34mLe client est register\e[0m" << std::endl;
		// client << RPL_WELCOME(client.getNickname(), client.getUsername(), client.getHostname());
		return true;
	} else {
		std::cout << "\e[31mLe client est pas du tout register\e[0m" << std::endl;
		return false;
	}
}

std::ostream&                       operator<<(std::ostream& o, Server const& rhs) {
	if (!rhs._channels.empty()) {
		o << "\e[34m" << "* ------------" << std::endl << "List des Channels :"<< std::endl << "* ------------" << "\e[0m" << std::endl;
		std::map<std::string, Channel*>::const_iterator ite = rhs._channels.end();
		for (std::map<std::string, Channel*>::const_iterator it = rhs._channels.begin(); it != ite; ++it)
			o << "\t" << it->first <<std::endl;
			o << "\e[34m" << "* ------------"  << "\e[0m" << std::endl;
	}
	/*try {
	if (!rhs.getOp().empty()) {
		o << "\e[34m" << "* ------------" << std::endl << "List de Operateur :"<< std::endl << "* ------------" << "\e[0m" << std::endl;
		// std::set<int>::iterator ite = rhs.getOp().end();
		// for (std::set<int>::iterator it = rhs.getOp().begin(); it != ite; ++it) {
		int i = 0;
		// std::set<const int>::const_iterator ite = rhs.getOp().end();
		for (std::set<const int>::const_iterator it = rhs.getOp().begin(); it != rhs.getOp().end(); ++it) {
			// Client	*clicli = static_cast<Client &>(rhs.fdConnectionMap.at(*it));
			// o << "\t\e[32m" << clicli->getUsername() << std::endl;
			o << "\t\e[32m" << (static_cast<Client *>(rhs.fdConnectionMap.at(*it)))->getUsername() << std::endl;
			// o << "\t\e[32m" << (static_cast<Client *>(rhs.fdConnectionMap.at(*it)))->getUsername() << std::endl;
			i++;
		}
		o << "| iteration = " << i << std::endl;
		o << "\e[34m" << "* ------------"  << "\e[0m" << std::endl;
	}
    } catch(std::exception &e) {
        std::cerr << "fucking exception: " << e.what() << std::endl;
    }*/
	o << "\e[0m";
	return o;
}
