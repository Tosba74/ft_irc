/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:53:39 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/12 14:54:30 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Channel.hpp"


Channel::Channel(std::string name) : _name(name)
{
}
Channel::Channel(Channel const &src)
{
	*this = src;
	for (clients_t::const_iterator it = src.begin(); it != src.end(); it++)
		_clients.insert(std::pair<int, Client>(it->first, it->second));
}
Channel & Channel::operator=(Channel const &rhs)
{
	if (this != &rhs)
	{
		_name = rhs._name;
		for (clients_t::const_iterator it = rhs.begin(); it != rhs.end(); ++it)
			_clients.insert(std::pair<int, Client>(it->first, it->second));
	}
	return *this;
}
Channel::~Channel()
{
}

std::string	const				Channel::getName() const
{
	return _name;
}

std::map<int, Client>::const_iterator Channel::begin() const
{
	return _clients.begin();
}

std::map<int, Client>::const_iterator Channel::end() const
{
	return _clients.end();
}

void							Channel::setName(std::string name)
{
	_name = name;
}
void							Channel::addClient(Client& client)
{
	for (clients_t::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second == client)
			return ;
	_clients.insert(std::pair<int, Client>(client.getSock(), client));
}
void							Channel::removeClient(Client& client)
{
	_clients.erase(client.getSock());
}

std::ostream&                       operator<<(std::ostream& o, Channel const& rhs)
{
	o << "Channel [" << rhs.getName() << "]:" << std::endl;
	for (std::map<int, Client>::const_iterator it = rhs.begin(); it != rhs.end(); ++it)
		o << "\t" << it->second.getNickname() << "(" << it->first << ")"<< std::endl;
	return o;
}