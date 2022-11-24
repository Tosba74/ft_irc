/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:53:39 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/20 16:53:14bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Channel.hpp"
#include "client/ACommand.hpp"


Channel::Channel(std::string name) : _name(name), _key(""), _vip(false), _limit(4096), _mod(0) {}

Channel::Channel(Channel const &src) {
	if (this != &src)
		*this = src;
}

Channel & Channel::operator=(Channel const &rhs) {
	if (this != &rhs) {
		_name = rhs._name;
		_key = rhs._key;
		_mod = rhs._mod;
		_vip = rhs._vip;
		_limit = rhs._limit;
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

// std::string						Channel::getMode() const { return _mode; }

std::string						Channel::getKey() const { return _key; }

unsigned int					Channel::getLimit() const { return _limit; }

bool							Channel::getVip() const { return _vip; }

std::string						Channel::getStringUser() const {
	std::string ret;
	if (_clients.size() > 0) {
		for (std::map<int, Client&>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
			// if (!(it->second._mod & MOD_USER_INVIS)) {
				ret += " ";
				if (isModo(it->second.getNickname()) == false)
					ret += "@";
				if (isBan(it->second))
					ret += "*";
				ret += it->second.getNickname();
			// }
		}
	}
	return ret;
} 

void							Channel::setName(std::string name) { _name = name; }

void							Channel::setKey(std::string key) {
	_key = key;
	if (!_key.compare(""))
		_mod ^= (1 << 6);
	else
		_mod |= (1 << 6);
}

void							Channel::setLimit(unsigned long nb) { _limit = nb; } 

void							Channel::addClient(Client& client) {
	if (_clients.find(client.getSock()) != _clients.end())
		return ;
	_clients.insert(std::pair<int, Client&>(client.getSock(), client));
	if (_clients.size() == 1)
		addModo(client.getNickname());
}

	//ATTENTION ADD BANCLIENT
void							Channel::removeClient(Client& client) {
	// attention si le client est seule dans le channel
	if (_clients.size() > 1)
		_clients.erase(client.getSock());
}

void							Channel::addBan(Client& client) {
	if (_ban.find(client.getSock()) != _ban.end())
		return ;
	_ban.insert(std::pair<int, Client&>(client.getSock(), client));
}
	
void							Channel::removeBan(Client& client) {
	_ban.erase(client.getSock());
}

bool							Channel::isBan(Client& client) const {
	if (!_ban.empty())
		for (std::map<int, Client&>::const_iterator it = _ban.begin(); it != _ban.end(); ++it)
			if (it->second == client)
				return true;
	return false;
}
	
void							Channel::addModo(std::string newModo)
{
    for (std::vector<std::string>::iterator it = _modo.begin(); it != _modo.end(); it++)
    {
            if ((*it) == newModo)
                    return;
    }
	std::cout << std::endl << "Debug: push new modo\n\n";
    _modo.push_back(newModo);
}

// bool                                                    Channel::isModo(std::string queried)
// {
        // for (std::vector<std::string>::iterator it = _modo.begin(); it != _modo.end(); it++)
        // {
                // if ((*it) == queried)
                        // return 0;
        // }
        // return 1;
// }

bool							Channel::isModo(std::string const& queried) const {
        for (std::vector<std::string>::const_iterator it = _modo.begin(); it != _modo.end(); it++) {
                if ((*it) == queried)
                        return 0;
        }
        return 1;
}

void							Channel::msgToUsers(std::string msg) {
	std::map<int, Client&>	clients = getClients();
	 for (std::map<int, Client&>::iterator it = clients.begin(); it != clients.end(); ++it) {
		 it->second.simpleMessage(msg);
	}
	 return;
}
	
Channel &						Channel::operator<<(std::string const& reply) {
	for (std::map<int, Client&>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (!(it->second._mod & MOD_USER_INVIS)) {
			it->second.simpleMessage(reply);
		}
		// it->second << reply;
	}
	return *this;
}

std::ostream &						operator<<(std::ostream & o, Channel const &rhs) {
	if (rhs.getClients().size() > 0) {
		for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it) {
			//ADD if () to string user too
			if (it->second._mod & MOD_USER_INVIS) {
				rhs.isModo(it->second.getNickname()) == false ? o << "@" : o << "";
				o << "mysterious user" << std::endl;
			} else {
				rhs.isModo(it->second.getNickname()) == false ? o << "@" : o << "";
				o << it->second.getNickname() << std::endl;
			}
		}
	}
	return o;
}

// Channel&						operator<<(Channel& chan, std::string const& msg) {
	// for (std::map<int, Client&>::iterator it = chan._clients.begin(); it != chan._clients.end(); ++it)
		// it->second << msg;
	// return *this;	
// }

// std::ostream&					operator<<(std::ostream& o, Channel const& rhs) {
	// o << "Channel [" << rhs.getName() << "]:" << std::endl;
	// for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
		// o << "\t" << it->second.getNickname() << "(" << it->first << ")"<< std::endl;
	// return o;
// }
