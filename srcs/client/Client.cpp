/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:40:56 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 17:48:44 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/Client.hpp"
#include <string>

Client::Client(int sock, sockaddr_in &addr) : SocketConnection(sock, addr), _nickname(""),
										_username(""), _hostname(""), _servername("ircserv"), _version("1.3"),
										_realname(""), _pass("lol"), _register(false), _op(false) {}

Client::Client(Client const &rhs) : SocketConnection(rhs), _nickname(rhs._nickname), _username(rhs._username),
									_hostname(rhs._hostname), _servername(rhs._servername), _version(rhs._version),
									_realname(rhs._realname), _pass(rhs._pass), _register(rhs._register), _op(rhs._op) {
	_channels.insert(rhs.getChannels().begin(), rhs.getChannels().end());
}

Client::~Client() throw() {}

Client								&Client::operator=(Client const &rhs) {
	(void)rhs;
	return (*this);
}

void								Client::setRegister(bool b) { _register = b; }
void                                Client::setNickname(std::string nickname) { _nickname = nickname; }
void                                Client::setUsername(std::string username) { _username = username; }
void                                Client::setHostname(std::string hostname) { _hostname = hostname; }
void                                Client::setNameserver(std::string nameserver) { _servername = nameserver; }
void                                Client::setVersion(std::string version) { _version = version; };
void                                Client::setRealName(std::string realname) { _realname = realname; }
void                                Client::setPass(std::string pass) { _pass= pass; }
void                                Client::setOp(bool op) { _op = op; };
bool 							  	Client::getRegister() const { return (_register); }
std::string							Client::getUsername() const { return _username; }
std::string							Client::getNickname() const { return _nickname; }
std::string							Client::getHostname() const { return _hostname; }
std::string							Client::getNameserver() const { return _servername; }
std::string							Client::getVersion() const { return _version; }
std::string							Client::getRealName() const { return _realname; }
std::string							Client::getPass() const { return _pass; }
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
	std::cout << "\e[34m" << "* ------------" << std::endl;
	std::cout << "| isRegister: " << std::endl;
	std::cout << "* ------------" << "\e[0m" << std::endl;

    std::cout << "\e[34m" << "| NameServer: " << "\e[0m";
    std::cout << (!this->getNameserver().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!this->getNameserver().empty())
		std::cout << " (" << getNameserver() << ")";
	std::cout << "\e[0m" << std::endl;
	
    std::cout << "\e[34m" << "| Hostname: " << "\e[0m";
    std::cout << (!this->getHostname().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!this->getHostname().empty()) {
		std::cout << " (" << getHostname();
		if (!this->getVersion().empty())
			std::cout << " v. " << this->getVersion();
		std::cout << ")";
	}
	std::cout << "\e[0m" << std::endl;
	
    std::cout << "\e[34m" << "| Pass: " << "\e[0m";
    std::cout << (!this->getPass().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!this->getPass().empty())
		std::cout << " (" << getPass() << ")";
	std::cout << "\e[0m" << std::endl;
	
	std::cout << "\e[34m" << "* ------------" << "\e[0m" << std::endl;
	
    std::cout << "\e[34m" << "| Nickname: " << "\e[0m";
    std::cout << (!this->getNickname().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!this->getNickname().empty())
		std::cout << " (" << getNickname() << ")";
	std::cout << "\e[0m" << std::endl;
	
    std::cout << "\e[34m" << "| Username: " << "\e[0m";
    std::cout << (!this->getUsername().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!this->getUsername().empty())
		std::cout << " (" << getUsername() << ")";
	std::cout << "\e[0m" << std::endl;
	
    std::cout << "\e[34m" << "| RealName: " << "\e[0m";
    std::cout << (!this->getRealName().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!this->getRealName().empty())
		std::cout << " (" << getRealName() << ")";
	std::cout << "\e[0m" << std::endl;

	std::cout << "\e[34m" << "* ------------" << "\e[0m" << std::endl;
    // if (this->getNickname().empty() || this->getPass().empty() || this->getUsername().empty() || this->getRealName().empty() || this->getHostname().empty())
    if (!this->getHostname().empty() && !this->getRealName().empty()
		&& !this->getNickname().empty() && !this->getPass().empty()) {
    	this->setRegister(true);
		// *(this) << RPL_WELCOME(this->getNickname(), this->getUsername(), this->getHostname());
		*(this) << RPL_WELCOME(this->getNickname());
		*(this) << RPL_YOURHOST(this->getNameserver(), this->getVersion());
		*(this) << RPL_CREATED(this->getRealName());
		*(this) << RPL_MYINFO(this->getNickname(), this->getNameserver(), this->getVersion());
	}
	return ;
}

Client &Client::operator<<(std::string const &reply)
{
	std::string		msg = getHostname() + reply + "\r\n";
	std::cout << "\e[33m" << "Reply : " << "\e[0m" << msg;
	SocketConnection::operator<<(msg);
	flush();
	// std::string		msg = reply + "\n";
	// std::cout << "Message to " << *(this) << ": " << msg;
	// SocketConnection::operator<<(msg);
	// flush();
	return *this;
}
