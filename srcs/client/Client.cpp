/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:40:56 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/20 00:08:21 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/Client.hpp"

Client::Client(int sock, sockaddr_in &addr) : SocketConnection(sock, addr),
											_username(""), _nickname(""),
											_password(""), _mode(""),
											_register(false), _op(false)
{
}

Client::~Client() throw()
{	
}

void                                Client::setNickname(std::string nickname)
{
	_nickname = nickname;
}
void                                Client::setPassword(std::string password)
{
	_password = password;
}

std::string                         Client::getUsername() const
{
	return _username;
}
std::string                         Client::getNickname() const
{
	return _nickname;
}
std::string                         Client::getPassword() const
{
	return _password;
}
std::string                         Client::getMode() const
{
	return _mode;
}
std::map<std::string ,Channel*>     Client::getChannels() const
{
	return _channels;
}
bool                                Client::getRegister() const
{
	return _register;
}
bool                                Client::getOp() const
{
	return _op;
}

bool                                Client::isInChannel(std::string name) const
{
	for (std::map<std::string ,Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
		if (it->first == name)
			return true;
	return false;
}

std::ostream &                     operator<<(std::ostream & o, Client const &rhs)
{
	o << "Client(" << rhs.getNickname() << "): User=" << rhs.getUsername();
	if (rhs.getRegister())
		o << " \033[32m[\033[0mConnected\033[32m]\033[0m ";
	else
		o << " \033[31m/!\\\033[0m ";
	return o;
}