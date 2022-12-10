/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/TOPIC.hpp"
#include "irc/Server.hpp"

TOPIC::TOPIC(Server *serv): ACommand(serv) {}

TOPIC::TOPIC(TOPIC const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

TOPIC::~TOPIC() {}

int             TOPIC::secureArgs(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 2) {
        clicli << ERR_NEEDMOREPARAMS(args[0]);
        return 1;
    }
    if (_serv->getChannel(args[1])->getClients().find(clicli.getSock()) == _serv->getChannel(args[1])->getClients().end()) {
        clicli << ERR_NOTONCHANNEL(args[1]);
        return 1;
    }
    if (_serv->getChannel(args[1])->isModo(clicli)) {
        clicli << ERR_CHANOPRIVSNEEDED(args[1]);
        return 1;
    }
    return 0;
        
}

int TOPIC::execute(Client &clicli, std::vector<std::string> args) {
    if (secureArgs(clicli, args))
        return 1;
    if (args.size() == 2) {
        if (_serv->getChannel(args[1])->getSujet() == "")
            clicli << RPL_NOTOPIC(args[1]);
        else
            clicli << RPL_TOPIC(clicli.getNickname(), args[1], _serv->getChannel(args[1])->getSujet());
        return 0;
    } else if (args.size() > 2) {
    	std::string msg = args[2];
    	for (unsigned long i = 3; i < args.size(); ++i)
    		msg.append(" " + args[i]);
            _serv->getChannel(args[1])->setSujet(msg);
            clicli << RPL_TOPIC(clicli.getNickname(), args[1], msg);
            return 0;
    }
    return 1;
}

    // clicli << RPL_NOTOPIC();
    // clicli << RPL_TOPIC();

void    TOPIC::descr(Client& clicli) {
    clicli << "Usage: TOPIC <canal> [<sujet>]";
}
