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
#include "/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/sys/_types/_size_t.h"
#include "client/ACommand.hpp"


Channel::Channel(std::string name) : _name(name), _key(""),  _sujet(""), _limit(4096), _mod(0) {}

Channel::Channel(Channel const &src) {
	if (this != &src)
		*this = src;
}

Channel & Channel::operator=(Channel const &rhs) {
	if (this != &rhs) {
		_name = rhs._name;
		_key = rhs._key;
		_mod = rhs._mod;
		_sujet = rhs._sujet;
		_limit = rhs._limit;
		for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
			_clients.insert(std::pair<int, Client&>(it->first, it->second));
		for (std::map<int, Client&>::const_iterator it = rhs.getModo().begin(); it != rhs.getModo().end(); ++it)
			_vip.insert(std::pair<int, Client&>(it->first, it->second));
		for (std::map<int, Client&>::const_iterator it = rhs.getBan().begin(); it != rhs.getBan().end(); ++it)
			_ban.insert(std::pair<int, Client&>(it->first, it->second));
		for (std::map<int, Client&>::const_iterator it = rhs.getVip().begin(); it != rhs.getVip().end(); ++it)
			_vip.insert(std::pair<int, Client&>(it->first, it->second));
	}
	return *this;
}

Channel::~Channel() {}

std::string	const&				Channel::getName() const { return _name; }

std::string						Channel::getSujet() const { return _sujet; }

std::map<int, Client&> const&	Channel::getClients() const { return _clients; }

std::map<int, Client&> const&	Channel::getModo() const { return _modo; }

std::map<int, Client&> const&	Channel::getBan() const { return _ban; }

std::map<int, Client&> const&	Channel::getVip() const { return _vip; }

std::string						Channel::getKey() const { return _key; }

size_t							Channel::getLimit() const { return _limit; }

std::string const 				Channel::getStringBan() const {
	std::string ret;
	if (!getBan().empty()) {
		for (std::map<int, Client&>::const_iterator it = getBan().begin(); it != getBan().end(); it++) {
			if (!(it->second._mod & MOD_USER_INVIS))
				it->second.getNickname();
		}
	}
	return ret;
}

std::string const				Channel::getStringUser() const {
	std::string ret;
	if (!_clients.empty()) {
		for (std::map<int, Client&>::const_iterator it = _clients.begin(); it != _clients.end(); it++) {
			if (!(it->second._mod & MOD_USER_INVIS)) {
				if (isModo(it->second) == false)
					ret += "@";
				if (isBan(it->second))
					ret += "*";
				ret += it->second.getNickname();
				ret += " ";
			}
		}
	}
	return ret;
} 

void							Channel::setName(std::string name) { _name = name; }

void							Channel::setSujet(std::string sujet) { _sujet = sujet; }

void							Channel::setKey(std::string key) {
	_key = key;
	if (!_key.compare(""))
		_mod ^= (1 << 5);
	else
		_mod |= (1 << 5);
}

void							Channel::setLimit(size_t nb) { _limit = nb; } 

void							Channel::addClient(Client& client) {
	if (_clients.find(client.getSock()) != _clients.end())
		return ;
	_clients.insert(std::pair<int, Client&>(client.getSock(), client));
	if (_clients.size() == 1)
		addModo(client);
}

	//ATTENTION ADD BANCLIENT
void							Channel::removeClient(Client& client) {
	// attention si le client est seule dans le channel
	// if (_clients.size() > 1)
		_clients.erase(client.getSock());
}

void							Channel::addBan(Client& client) {
	if (_ban.find(client.getSock()) != _ban.end())
		return ;
	_ban.insert(std::pair<int, Client&>(client.getSock(), client));
}
	
void							Channel::removeBan(Client& client) {
	if (_ban.find(client.getSock()) != _ban.end())
		_ban.erase(client.getSock());
}

bool							Channel::isBan(Client& client) const {
	if (!_ban.empty())
		for (std::map<int, Client&>::const_iterator it = getBan().begin(); it != getBan().end(); ++it)
			if (it->second == client)
				return true;
	return false;
}
	
void							Channel::addModo(Client& client) {
	if (_modo.find(client.getSock()) != _modo.end())
		return ;
	_modo.insert(std::pair<int, Client&>(client.getSock(), client));
}
	
void							Channel::removeModo(Client& client) {
	if (_modo.find(client.getSock()) != _modo.end())
		_modo.erase(client.getSock());
}

bool							Channel::isModo(Client& client) const {
	if (!_modo.empty())
		for (std::map<int, Client&>::const_iterator it = getModo().begin(); it != getModo().end(); ++it)
			if (it->second == client)
				return true;
	return false;
}
// void							Channel::addModo(std::string newModo)
// {
//     for (std::vector<std::string>::iterator it = _modo.begin(); it != _modo.end(); it++)
//         if ((*it) == newModo)
//             return;
// 	std::cout << std::endl << "Debug: push new modo\n\n";
//     _modo.push_back(newModo);
// }

// void							Channel::removeModo(std::string modo) {
//     for (std::vector<std::string>::iterator it = _modo.begin(); it != _modo.end(); it++)
// 		if ((*it) == modo) {
// 			_modo.erase(it);
// 		}
// }

// bool							Channel::isModo(std::string const& name) const {
//     for (std::vector<std::string>::const_iterator it = _modo.begin(); it != _modo.end(); it++) {
//         if ((*it) == name)
//             return 0;
//     }
//     return 1;
// }

void							Channel::addVip(Client& client) {
	if (_vip.find(client.getSock()) != _vip.end())
		return ;
	_vip.insert(std::pair<int, Client&>(client.getSock(), client));
}
	
void							Channel::removeVip(Client& client) {
	if (_vip.find(client.getSock()) != _vip.end())
		_vip.erase(client.getSock());
}

bool							Channel::isVip(Client& client) const {
	if (!_vip.empty())
		for (std::map<int, Client&>::const_iterator it = getVip().begin(); it != getVip().end(); ++it)
			if (it->second == client)
				return true;
	return false;
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
			it->second << reply;
			// it->second.simpleMessage(reply);
		}
	}
	return *this;
}

std::ostream &						operator<<(std::ostream & o, Channel const &rhs) {
	if (rhs.getClients().size() > 0) {
		for (std::map<int, Client&>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it) {
			//ADD if () to string user too
			if (it->second._mod & MOD_USER_INVIS) {
				rhs.isModo(it->second) == false ? o << "@" : o << "";
				o << "mysterious user" << std::endl;
			} else {
				rhs.isModo(it->second) == false ? o << "@" : o << "";
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
