/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:40:56 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/18 14:01:10 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/Client.hpp"

Client::Client(int sock, sockaddr_in &addr) : SocketConnection(sock, addr),
											_nickname(""), _username(""),
											_hostname(""), _servername(""),
											_realname(""), _password(""),
											_register(false), _op(false) {
}

Client::Client(Client const &rhs) : SocketConnection(rhs) {}

Client::~Client() throw() {}

Client								&Client::operator=(Client const &rhs) {
	(void)rhs;
	return (*this);
}

void								Client::setRegister(bool b) { _register = b; }
void                                Client::setNickname(std::string nickname) { _nickname = nickname; }
void                                Client::setUsername(std::string username) { _username = username; }
void                                Client::setHostname(std::string hostname) { _hostname = hostname; }
void                                Client::setServerName(std::string nameserver) { _servername = nameserver; }
void                                Client::setRealName(std::string realname) { _realname = realname; }
void                                Client::setPassword(std::string password) { _password = password; }
bool 							  	Client::getRegister() const { return (_register); }
std::string							Client::getUsername() const { return _username; }
std::string							Client::getNickname() const { return _nickname; }
std::string							Client::getHostname() const { return _hostname; }
std::string							Client::getNameServer() const { return _servername; }
std::string							Client::getRealName() const { return _realname; }
std::string							Client::getPassword() const { return _password; }
std::string							Client::getMode() const { return _mode; }
std::map<std::string ,Channel*>     Client::getChannels() const { return _channels; }
bool                                Client::getOp() const { return _op; }

void                                Client::readChannels() const {
	for (std::map<std::string, Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it) {
		std::cout << it->first << std::endl;
	}
}
		
bool								Client::isInChannel(std::string name) const {
	for (std::map<std::string ,Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
		if (it->first == name)
			return true;
	return false;
}

std::ostream &						operator<<(std::ostream & o, Client const &rhs) {
	o << "Client(" << rhs.getNickname() << "): User=" << rhs.getUsername();
	if (rhs.getRegister())
		o << " \033[32m[\033[0mConnected\033[32m]\033[0m ";
	else
		o << " \033[31m/!\\\033[0m ";
	return o;
}
void Client::updateRegister()
{
	if (_register)
		return ;
    if (this->getNickname().empty() || this->getPassword().empty() || this->getUsername().empty() || this->getRealName().empty() || this->getHostname().empty())
		return ;
    this->setRegister(true);
	std::string tmp = RPL_WELCOME(this->getNickname(), this->getUsername(), this->getHostname());
	std::cout << "\e[32m" << tmp << "\e[0m" << std::endl;
	send(getSock(), tmp.c_str(), tmp.length(), 0);
	// *(this) << RPL_WELCOME(this->getNickname(), this->getUsername(), this->getHostname());
}

Client &Client::operator<<(std::string const &reply)
{
	std::string		msg = reply + "\n";
	std::cout << "Message to " << *(this) << ": " << msg;
	SocketConnection::operator<<(msg);
	flush();
	return *this;
}