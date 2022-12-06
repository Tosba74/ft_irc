/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:18 by bmangin           #+#    #+#             */
/*   Updated: 2022/12/06 10:15:37 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/ACommand.hpp"
#include "irc/Server.hpp"
#include <cstring>
#include <iomanip>

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

Server const*   ACommand::getServ() const { return this->_serv; }

int		        ACommand::checkChannel(Client &clicli, std::string arg) {
	if ((arg[0] != '#' && arg[0] != '&' ) || (arg.size() < 2 || arg.size() > 20)) {
		clicli << ERR_NOSUCHCHANNEL(arg);
		return 1;
	}
	// } else if (!getServ()->getChannel(clicli.getCurrchan()) || arg.compare(clicli.getCurrchan())) {
		// clicli << ERR_NOTONCHANNEL(arg);
		// return 1;
	// }
	return 0;
}

// Protected Usage:
// if (splitArgs(arg).empty()) { 
	// clicli << ERR_NEEDMOREPARAMS(args[0]); // this->decr();
// } else {
	// std::vector<std::string> newargs = splitArgs(arg);
	// newargs.insert(newargs.begin(), args[0]);
// }
std::vector<std::string>	ACommand::splitArgs(std::string arg) {
	std::vector<std::string> args;
    size_t i = 0;
    int pos = 0;

    args.push_back(arg);
	while (args[pos].find(",") != std::string::npos) {
        i = args[pos].find(",");
        if (i == 0)
			return args;
			// return std::vector<std::string>();
        args.push_back(args[pos].substr(i + 1, std::string::npos));
        args[pos].erase(i);
        for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
            if (!it->compare(",") || !it->compare(""))
                args.erase(it);
        pos++;
    }
    return args;
}