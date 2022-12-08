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
    // clicli << ERR_NOTONCHANNEL(args[2]);

    // clicli << ERR_USERONCHANNEL();

    // clicli << ERR_CHANOPRIVSNEEDED(args[2]);
    // clicli << RPL_AWAY(args[1]);

    // clicli << RPL_INVITING();
    
int     INVITE::secureArgs(Client &clicli, std::vector<std::string> args) {
    // args.size == 3
    // check args[1] == nickName;
    // check args[2] == Channnel;
}

int     INVITE::execute(Client &clicli, std::vector<std::string> args) {
    if (secureArgs(clicli, args))
        return 1;
    return 0;
}


void    INVITE::descr(Client& clicli) {
    clicli << "usage: INVITE <pseudonyme> <canal>"
}
