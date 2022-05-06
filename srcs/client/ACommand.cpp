/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:18 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/28 17:42:54by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/ACommand.hpp"
#include "client/command/NIMP.hpp"
#include "socket/SocketConnection.hpp"
#include "irc/Server.hpp"
#include "client/Client.hpp"

ACommand::ACommand(Server *serv, Client & clicli, std::string msg) : _arg(0), _serv(serv), _client(clicli)
{
	size_t i = 0;
	size_t pos;

	while (pos = msg.find(' ', i), pos != std::string::npos)
	{
		_arg.push_back(msg.substr(i, pos - i));
		i = pos + 1;
	}
	_arg.push_back(msg.substr(i));
}

ACommand::ACommand(ACommand const& src)  : _arg(src._arg), _serv(src._serv), _client(src._client)
{
    #ifdef DEBUG
        std::cout << "Copy Constructeur Called" << std::endl;
    #endif
}
ACommand::~ACommand()
{
    #ifdef DEBUG
        std::cout << "Destructeur Called" << std::endl;
    #endif
}

ACommand&   ACommand::operator=(ACommand const& rhs)
{
	if (this != &rhs)
	{
		this->_arg = rhs._arg;
		this->_serv = rhs._serv;
		this->_client = rhs._client;
	}
	return *this;
}

const args_t &   		ACommand::getMsg() const
{
	return this->_arg;
}
const Server *				ACommand::getServ() const
{
	return this->_serv;
}
const Client &				ACommand::getClient() const
{
	return this->_client;
}
