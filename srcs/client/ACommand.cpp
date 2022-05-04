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

ACommand::ACommand(Server *serv, Client & clicli, std::string msg) : _msg(msg), _serv(serv), _client(clicli)
{
	// this->execute();
};
	// try
	// {
	// 	_client = dynamic_cast<Client&>(clicli);
	// }
	// catch (std::bad_cast &e)
	// {
	// 	std::cerr << "ACommand::ACommand(Server *serv, SocketConnection & clicli, std::string msg) : _msg(msg), _serv(serv) : " << e.what() << std::endl;
	// }
// {
    // #ifdef DEBUG
        // std::cout << "Default Constructeur Called" << std::endl;
    // #endif
// }
ACommand::ACommand(ACommand const& src)  : _msg(src._msg), _serv(src._serv), _client(src._client)
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
		this->_msg = rhs._msg;
		this->_serv = rhs._serv;
		this->_client = rhs._client;
	}
	return *this;
}

const std::string &    		ACommand::getMsg() const
{
	return this->_msg;
}
const Server *				ACommand::getServ() const
{
	return this->_serv;
}
const Client &				ACommand::getClient() const
{
	return this->_client;
}
