/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:53:39 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/07 13:10:20 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Channel.hpp"


Channel::Channel(std::string name) : _name(name), _mode(""), _key(""), _limit(0) {}

Channel::Channel(Channel const &src) {
	if (this != &src)
		*this = src;
}

Channel & Channel::operator=(Channel const &rhs) {
	if (this != &rhs) {
		_name = rhs._name;
		_mode = rhs._mode;
		_limit = rhs._limit;
		for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
			_clients.insert(std::pair<int, Client&>(it->first, it->second));
	}
	return *this;
}

Channel::~Channel() {}

std::string	const&				Channel::getName() const { return _name; }

std::map<int, Client&> const&	Channel::getClients() const { return _clients; }

std::string						Channel::getMode() const { return _mode; }

std::string						Channel::getKey() const { return _key; }

unsigned int					Channel::getLimit() const { return _limit; }

void							Channel::setName(std::string name) { _name = name; }

void							Channel::addClient(Client& client) {
	for (std::map<int, Client&>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second == client)
			return ;
	client.setCurrchan(_name);
	_clients.insert(std::pair<int, Client&>(client.getSock(), client));
}

void							Channel::removeClient(Client& client) {
	_clients.erase(client.getSock());
}

std::ostream&                       operator<<(std::ostream& o, Channel const& rhs) {
	o << "Channel [" << rhs.getName() << "]:" << std::endl;
	for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
		o << "\t" << it->second.getNickname() << "(" << it->first << ")"<< std::endl;
	return o;
}