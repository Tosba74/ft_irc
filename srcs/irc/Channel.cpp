/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:53:39 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/07 16:06:40 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Channel.hpp"


Channel::Channel(std::string name) : _name(name), _mode(""), _key(""), _limit(4096), _vip(false) {}

Channel::Channel(Channel const &src) {
	if (this != &src)
		*this = src;
}

Channel & Channel::operator=(Channel const &rhs) {
	if (this != &rhs) {
		_name = rhs._name;
		_mode = rhs._mode;
		_limit = rhs._limit;
		_vip = rhs._vip;
		for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
			_clients.insert(std::pair<int, Client&>(it->first, it->second));
		for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
			_clients.insert(std::pair<int, Client&>(it->first, it->second));
	}
	return *this;
}

Channel::~Channel() {}

std::string	const&				Channel::getName() const { return _name; }

std::map<int, Client&> const&	Channel::getClients() const { return _clients; }

std::map<int, Client&> const&	Channel::getBan() const { return _ban; }

std::string						Channel::getMode() const { return _mode; }

std::string						Channel::getKey() const { return _key; }

unsigned int					Channel::getLimit() const { return _limit; }

bool							Channel::getVip() const { return _vip; }

void							Channel::setName(std::string name) { _name = name; }

void							Channel::setKey(std::string key) { _key = key; }

void							Channel::addClient(Client& client, std::map<int, Client&> lst) {
	for (std::map<int, Client&>::iterator it = lst.begin(); it != lst.end(); ++it)
		if (it->second == client)
			return ;
	lst.insert(std::pair<int, Client&>(client.getSock(), client));
}

void							Channel::removeClient(Client& client, std::map<int, Client&> lst) {
	lst.erase(client.getSock());
}

std::ostream&                       operator<<(std::ostream& o, Channel const& rhs) {
	o << "Channel [" << rhs.getName() << "]:" << std::endl;
	for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
		o << "\t" << it->second.getNickname() << "(" << it->first << ")"<< std::endl;
	return o;
}