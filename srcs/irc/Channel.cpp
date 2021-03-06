/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:53:39 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/10 16:50:33 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Channel.hpp"


Channel::Channel(std::string name) : _name(name)
{
}
Channel::Channel(Channel const &src)
{
	*this = src;
	for (std::map<int, Client&>::const_iterator it = src.getClients().begin(); it != src.getClients().end(); ++it)
		_clients.insert(std::pair<int, Client&>(it->first, it->second));
}
Channel & Channel::operator=(Channel const &rhs)
{
	if (this != &rhs)
	{
		_name = rhs._name;
		for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
			_clients.insert(std::pair<int, Client&>(it->first, it->second));
	}
	return *this;
}
Channel::~Channel()
{
}

std::string	const&				Channel::getName() const
{
	return _name;
}
std::map<int, Client&> const&	Channel::getClients() const
{
	return _clients;
}

void							Channel::setName(std::string name)
{
	_name = name;
}
void							Channel::addClient(Client& client)
{
	for (std::map<int, Client&>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second == client)
			return ;
	_clients.insert(std::pair<int, Client&>(client.getSock(), client));
}
void							Channel::removeClient(Client& client)
{
	_clients.erase(client.getSock());
}

std::ostream&                       operator<<(std::ostream& o, Channel const& rhs)
{
	o << "Channel [" << rhs.getName() << "]:" << std::endl;
	for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
		o << "\t" << it->second.getNickname() << "(" << it->first << ")"<< std::endl;
	return o;
}