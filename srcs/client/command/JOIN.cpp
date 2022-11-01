/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/01 17:32:59 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/JOIN.hpp"
#include "irc/Server.hpp"

JOIN::JOIN(Server *serv): ACommand(serv) {}

JOIN::JOIN(JOIN const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

JOIN::~JOIN() {}

// clicli << ERR_CHANNELISFULL(args[1]);
// clicli << ERR_BANNEDFROMCHAN(args[1]);
// clicli << ERR_INVITEONLYCHAN(args[1]);
// clicli << ERR_BADCHANMASK(args[1]);
// clicli << ERR_BADCHANNELKEY(args[1]);
// clicli << RPL_TOPIC(args[1], "Welcome " + clicli->getNickname());
// clicli << ERR_NEEDMOREPARAMS(args[0]);
// clicli << ERR_NOSUCHCHANNEL(args[1]);
// clicli << ERR_TOOMANYCHANNELS(args[1]);

int JOIN::execute(Client &clicli, std::vector<std::string> args) {
    if (clicli.getRegister() == true)
        _serv->joinChannel(args[1], clicli);
    else
        clicli << "You must be authenticated to join a channel\n";
    return 0;
}

void    JOIN::descr(Client& clicli) {
    clicli << "\e[31mExemple\e[0m\n";
}