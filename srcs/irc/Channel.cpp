/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:30:24 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/14 22:26:48 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Channel.hpp"
#include "user/Client.hpp"

Channel::Channel() : _name("undefined")
{
}
Channel::Channel(std::string name) : _name(name)
{
	
}
Channel::Channel(Channel const &src)
{
	 if (this != &src)
    {
        _name = src.getName();
		for (std::vector<Client*>::const_iterator it = src.getClients().begin(); it != src.getClients().end(); ++it)
			_clients.push_back(*it);
    }
}
Channel::~Channel()
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		delete *it;
		_clients.erase(it);
	}
}

Channel &	Channel::operator=(Channel const &rhs)
{
	 if (this != &rhs)
    {
        _name = rhs.getName();
		for (std::vector<Client*>::const_iterator it = rhs._clients.begin(); it != rhs._clients.end(); ++it)
			_clients.push_back(*it);
    }
	return *this;
}

//setters
void Channel::setName(std::string name)
{
	_name = name;
}

//getters
std::string Channel::getName() const
{
	return (this->_name);
}
std::vector<Client*>	Channel::getClients() const
{
	return (this->_clients);
}

//methods
void Channel::addClient(Client &client)
{
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), &client);
	if (it == _clients.end())
		_clients.push_back(&client);
}
void Channel::removeClient(Client *client)
{
	(void)client;
}
void Channel::sendMessage(std::string message)
{
	(void)message;
}

std::ostream &operator<<(std::ostream &o, Channel const &rhs)
{
	unsigned int i = 0;
	o << "##############################" << std::endl; 
	o << "Channel: " << rhs.getName() << std::endl;
	o << "#============================#" << std::endl; 
	o << "Clients List: " << std::endl;
	for (std::vector<Client*>::const_iterator it = rhs.getClients().begin(); it != rhs.getClients().end(); ++it)
		o <<  i++ << "	" << *it << std::endl;
	o << "##############################" << std::endl; 
	return o;
};