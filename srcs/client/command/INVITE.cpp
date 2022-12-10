/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/INVITE.hpp"
#include "irc/Server.hpp"

INVITE::INVITE(Server *serv): ACommand(serv) {}

INVITE::INVITE(INVITE const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

INVITE::~INVITE() {}

    // clicli << ERR_NEEDMOREPARAMS(args[0]);
    // clicli << ERR_NOSUCHNICK(args[2]);
    // clicli << RPL_AWAY(args[1]);
    // clicli << ERR_CHANOPRIVSNEEDED(args[2]);
    // clicli << ERR_NOTONCHANNEL(args[2]);
    // clicli << ERR_USERONCHANNEL();
    // clicli << RPL_INVITING();
    
int     INVITE::secureArgs(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 3) {
        clicli << ERR_NEEDMOREPARAMS(args[0]);
        return 1;
    }
    if (!_serv->getClient(args[1])) {
        clicli << ERR_NOSUCHNICK(args[1]);
        return 1;
    } else if (_serv->getClient(args[1])->_mod & MOD_AWAY) {
        clicli << RPL_AWAY(args[1], _serv->getClient(args[1])->getAway());
        return 1;
    }

    if (!_serv->getChannel(args[2])) {
        clicli << ERR_NOSUCHNICK(args[2]);
        return 1;
    } else if (!clicli.isInChannel(args[2])) {
        clicli << ERR_NOTONCHANNEL(args[2]);
        return 1;
    } else if (!_serv->getChannel(args[2])->isModo(clicli)) {
        clicli << ERR_CHANOPRIVSNEEDED(args[2]);
        return 1;
    } else if (_serv->getChannel(args[2])->isVip(*_serv->getClient(args[1]))) {
        clicli << ERR_USERONCHANNEL(args[1], args[2]);
        return 1;
    }
    return 0;

}

int     INVITE::execute(Client &clicli, std::vector<std::string> args) {
    if (secureArgs(clicli, args))
        return 1;
    // _serv->getChannel(args[2])->addModo(*_serv->getClient(args[1]));
    _serv->getChannel(args[2])->addVip(*_serv->getClient(args[1]));
    *_serv->getClient(args[1]) << RPL_INVITING(args[1], args[2]);
    return 0;
}


void    INVITE::descr(Client& clicli) {
    clicli << "usage: INVITE <pseudonyme> <canal>";
}
