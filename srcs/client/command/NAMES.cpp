/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NAMES.hpp"
#include "irc/Server.hpp"

NAMES::NAMES(Server *serv): ACommand(serv) {}

NAMES::NAMES(NAMES const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

NAMES::~NAMES() {}

int             NAMES::secureArgs(Client &clicli, std::vector<std::string> args) {
    (void)clicli;
    (void)args;
	clicli << RPL_NAMREPLY(args[1], clicli.getNickname(), _serv->getChannel(args[1])->getStringUser());
	clicli << RPL_ENDOFNAMES(args[1], clicli.getNickname());
    return 0;
}

int NAMES::execute(Client &clicli, std::vector<std::string> args) {
    if (args.size() == 1) {
        for (std::map<std::string, Channel*>::iterator it = _serv->_channels.begin(); it != _serv->_channels.end(); ++it)
            if (!(it->second->_mod & MOD_CHAN_SECRET || it->second->_mod & MOD_CHAN_VIP)) {
                clicli << it->second->getName();
                clicli << it->second->getStringUser();
            }
    } else {
        std::vector<std::string> chans= splitArgs(args[1]);
        if (!chans.empty()) { 
        	clicli << ERR_NEEDMOREPARAMS(args[0]); // this->decr();
            return 1;
        }
        for (size_t i = 1; i != chans.size(); ++i) {
            if (!_serv->getChannel(chans[i])) {
                clicli << _serv->getChannel(chans[i])->getName();
                clicli << _serv->getChannel(chans[i])->getStringUser();
            } else {
                clicli << ERR_NOSUCHCHANNEL(chans[i]);
                return 1;
            } 
        } 
    }
	// clicli << RPL_NAMREPLY(args[1], clicli.getNickname(), _serv->getChannel(args[1])->getStringUser());
	// clicli << RPL_ENDOFNAMES(args[1], clicli.getNickname());
    return 0;
}


void    NAMES::descr(Client& clicli) {
    clicli << "Commande: NAMES [<canal>{,<canal>}]";
}
