/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:40:56 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/21 15:40:43 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/Client.hpp"
#include <string>

Client::Client(int sock, sockaddr_in &addr) : SocketConnection(sock, addr), _nickname(""), _username(""),
											_hostname(""), _servername("ircserv"), _version("1.3"), _realname(""),
											_pass(""), _currChan(""), _awayMsg(""), _register(false), _away(false), _mod(0) {}

Client::Client(Client const &rhs) : SocketConnection(rhs), _nickname(rhs._nickname), _username(rhs._username),
									_hostname(rhs._hostname), _servername(rhs._servername), _version(rhs._version),
									_realname(rhs._realname), _pass(rhs._pass), _currChan(rhs._currChan), _awayMsg(rhs._awayMsg),
									_register(rhs._register), _away(rhs._away), _mod(rhs._mod) {
	*this = rhs;
	_channels.insert(rhs.getChannels().begin(), rhs.getChannels().end());
}

Client::~Client() throw() {
	for (listChannel::iterator it = _channels.begin(); it != _channels.end(); it++)
		it->second->removeClient(*this);
	_channels.clear();
}

Client								&Client::operator=(Client const &rhs) {
	if (this != &rhs) {
    	_nickname = rhs.getNickname();
    	_username = rhs.getUsername();
    	_hostname = rhs.getHostname();
    	_servername = rhs.getNameserver();
    	_version = rhs.getVersion();
    	_realname = rhs.getRealName();
    	_pass = rhs.getPass();
    	_mod = rhs._mod;
    	_awayMsg =  rhs.getAwayMsg(); 
    	_register = rhs.getRegister();
		_channels.insert(rhs.getChannels().begin(), rhs.getChannels().end());
	}
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
void								Client::setCurrchan(std::string name) { _currChan = name; }
void                                Client::setAway(bool away) { _away = away;}
void                                Client::setAwayMsg(std::string msg) { _awayMsg = msg;}
// void                                Client::setOp(bool op) { _op = op; };
bool 							  	Client::getRegister() const { return (_register); }
bool                                Client::getAway() const {return _away; }
std::string                         Client::getAwayMsg() const {return _awayMsg; }
std::string							Client::getUsername() const { return _username; }
std::string							Client::getNickname() const { return _nickname; }
std::string							Client::getHostname() const { return _hostname; }
std::string							Client::getNameserver() const { return _servername; }
std::string							Client::getVersion() const { return _version; }
std::string							Client::getRealName() const { return _realname; }
std::string							Client::getPass() const { return _pass; }
std::string							Client::getCurrchan() const { return _currChan; }
char								Client::getMode() const { return _mod; }
std::map<std::string ,Channel*>     Client::getChannels() const { return _channels; }
// bool                                Client::getOp() const { return _op; }

void                                Client::readChannels() const {
	for (std::map<std::string, Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it) {
		std::cout << it->first << std::endl;
	}
}

bool								Client::isInChannel(std::string name) const {
	if (!_currChan.compare(name)) 
			return true;
	return false;
}

// typedef std::map<std::string, Channel*>     listChannel;
bool                                Client::isBanned(std::string chan) const {
	if (_channels.find(chan) != _channels.end())
		return _channels.at(chan)->isBan(*this);
	// for (std::map<std::string ,Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it)
		// if (!it->first.compare(chan))
			// for (std::map<int, Client&>::const_iterator it2 = it->second->getBan().begin(); it2 != it->second->getBan().end(); it2++)
				// if (it2->second == *this)
					// return true;
	return false;
}

void Client::updateRegister() {
	if (_register)
		return ;
    if (!this->getHostname().empty() && !this->getRealName().empty()
		&& !this->getNickname().empty() && !this->getPass().empty()) {
    	this->setRegister(true);
		*(this) << RPL_WELCOME(this->getNickname());
		*(this) << RPL_YOURHOST(this->getNameserver(), this->getVersion());
		*(this) << RPL_CREATED(this->getRealName());
		*(this) << RPL_MYINFO(this->getNickname(), this->getNameserver(), this->getVersion());
	}
	printC(*this);
	return ;
}

Client &Client::operator<<(std::string const &reply)
{
	std::string		msg_send = ":" + getHostname() + " " + reply + "\r\n";
	std::string		msg = getHostname() + reply + "\n";
	std::cout << "\e[33m" << "Reply : " << "\e[0m" << msg;
	SocketConnection::operator<<(msg_send);
	flush();
	// std::string		msg = reply + "\n";
	// std::cout << "Message to " << *(this) << ": " << msg;
	// SocketConnection::operator<<(msg);
	// flush();
	return *this;
}

Client &Client::simpleMessage(std::string &reply)
{
	// tentative bypass le ": getHostName()"
	std::cout << "\e[33m" << "Reply : " << "\e[0m" << reply << std::endl;
	reply += "\r\n";
	SocketConnection::operator<<(reply);
	return *this;

}

std::ostream &						operator<<(std::ostream & o, Client const &rhs) {
	o << "Client(" << rhs.getNickname() << "): User=" << rhs.getUsername();
	if (rhs.getRegister())
		o << " \033[32m[\033[0mConnected\033[32m]\033[0m ";
	else
		o << " \033[31m/!\\\033[0m ";
	return o;
}

int					ft_putbytes(int nb) {
	if (nb == 1) {
		std::cout << "1";
		return (0);
	} else if (nb == 0) {
		std::cout << "0";
		return (0);
	} else {
		ft_putbytes(nb / 2);
		if ((nb % 2) > 0)
			std::cout << "1";
		else
			std::cout << "0";
	}
	return (1);
}
// int     ft_putbytes(int nb) {
	// if (nb == 1) {
		// write(1, '1', 1);
		// return (0);
	// } else if (nb == 0) {
		// write(1, '0', 1);
		// return (0);
	// } else {
		// ft_putbytes(nb / 2);
		// if ((nb % 2) > 0)
			// write(1, '1', 1);
		// else
			// write(1, '0', 1);
	// }
	// return (1);
// }

void	printC(Client const& rhs) {
	std::cout << "\e[34m" << "* ------------" << std::endl;
	std::cout << "\e[34m" << "| isRegister: " << (rhs.getRegister() ? "\e[32mY" : "\e[31mN") << std::endl;
	std::cout << "\e[34m" << "* ------------" << std::endl;

    std::cout << "\e[34m" << "| NameServer: " << "\e[0m";
    std::cout << (!rhs.getNameserver().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!rhs.getNameserver().empty())
		std::cout << " (" << rhs.getNameserver() << ")";
	std::cout << "\e[0m" << std::endl;

    std::cout << "\e[34m" << "| Hostname: " << "\e[0m";
    std::cout << (!rhs.getHostname().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!rhs.getHostname().empty()) {
		std::cout << " (" << rhs.getHostname();
		if (!rhs.getVersion().empty())
			std::cout << " - v." << rhs.getVersion();
		std::cout << ")";
	}
	std::cout << "\e[0m" << std::endl;

    std::cout << "\e[34m" << "| Pass: " << "\e[0m";
    std::cout << (!rhs.getPass().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!rhs.getPass().empty())
		std::cout << " (" << rhs.getPass() << ")";
	std::cout << "\e[0m" << std::endl;

	std::cout << "\e[34m" << "* ------------" << "\e[0m" << std::endl;

    std::cout << "\e[34m" << "| Nickname: " << "\e[0m";
    std::cout << (!rhs.getNickname().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!rhs.getNickname().empty())
		std::cout << " (" << rhs.getNickname() << ")";
	std::cout << "\e[0m" << std::endl;

    std::cout << "\e[34m" << "| Username: " << "\e[0m";
    std::cout << (!rhs.getUsername().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!rhs.getUsername().empty())
		std::cout << " (" << rhs.getUsername() << ")";
	std::cout << "\e[0m" << std::endl;

    std::cout << "\e[34m" << "| RealName: " << "\e[0m";
    std::cout << (!rhs.getRealName().empty() ? "\e[32mOK" : "\e[31mKO");
    if (!rhs.getRealName().empty())
		std::cout << " (" << rhs.getRealName() << ")";
	std::cout << "\e[0m" << std::endl;

    std::cout << "\e[32m" << "| Droit User: " << "\e[34m";
	ft_putbytes(rhs._mod);
	std::cout << "\e[0m" << std::endl;
	
	// std::cout << "\e[34m" << "| isServerOperateur: " << (rhs.getOp() ? "\e[32mY" : "\e[31mN") << std::endl;

	std::cout << "\e[34m" << "* ------------" << "\e[0m" << std::endl;
}
