/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:18 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/22 16:19:11 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/ACommand.hpp"
#include "irc/Server.hpp"

ACommand::ACommand(Server *serv) : _serv(serv) {}

ACommand::ACommand(ACommand const& src)  : _serv(src._serv) {
    #ifdef DEBUG
        std::cout << "Copy Constructeur Called" << std::endl;
    #endif
}
ACommand::~ACommand() {
    #ifdef DEBUG
        std::cout << "Destructeur Called" << std::endl;
    #endif
}

ACommand&       ACommand::operator=(ACommand const& rhs) {
	if (this != &rhs) {
		this->_serv = rhs._serv;
	}
	return *this;
}

Server const*   ACommand::getServ() const {
	return this->_serv;
}

int		        ACommand::checkChannel(Client &clicli, std::string arg) {
	if (arg.size() < 2 || ((arg[0] != '#' && arg[0] != '&' )) || arg.size() > 20) {
		clicli << ERR_NOSUCHCHANNEL(arg);
		return true;
	}
	// } else if (!getServ()->getChannel(clicli.getCurrchan()) || arg.compare(clicli.getCurrchan())) {
		// clicli << ERR_NOTONCHANNEL(arg);
		// return 1;
	// }
	return false;
}
