/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/09 16:20:51 by bmangin          ###   ########lyon.fr   */
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

// clicli << ERR_BADCHANMASK(args[1]);

// clicli << ERR_BANNEDFROMCHAN(args[1]);
// clicli << ERR_BADCHANNELKEY(args[1]);
// clicli << ERR_TOOMANYCHANNELS(args[1]);
// clicli << ERR_INVITEONLYCHAN(args[1]);
// clicli << ERR_CHANNELISFULL(args[1]);
// clicli << ERR_NOSUCHCHANNEL(args[1]);
// clicli << ERR_NEEDMOREPARAMS(args[0]);

int JOIN::execute(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 2) {
        clicli << ERR_NEEDMOREPARAMS(args[0]);
        return 1;
    }
    if (args[1].size() < 2 || args[1].at(0) != '#') {
        clicli << ERR_NOSUCHCHANNEL(args[1]);
        return 1;
    }
	if (_serv->getChannel(args[1]) == NULL) {
	    _serv->createChannel(args[1]);
        if (!(_serv->getChannel(args[1])->_mod & MOD_CHAN_KEY))
           ; 
        else if (args.size() == 3 && _serv->getChannel(args[1])->getKey().compare(""))
            _serv->getChannel(args[1])->setKey(args[2]);
    }
    
    for (std::map<int, Client&>::const_iterator it = _serv->getChannel(args[1])->getBan().begin(); it != _serv->getChannel(args[1])->getBan().end(); it++) {
        if (it->second == clicli) {
            clicli << ERR_BANNEDFROMCHAN(args[1]);
            return 1;
        }
    }

    if (_serv->getChannel(args[1])->getClients().size() > 10000000) {
        clicli << ERR_TOOMANYCHANNELS(args[1]);
        return 1;
    } else if (_serv->getChannel(args[1])->getLimit() <= _serv->getChannel(args[1])->getClients().size()) {
        clicli << ERR_CHANNELISFULL(args[1]);
        return 1;
    } else if (_serv->getChannel(args[1])->getVip() == true) {
        clicli << ERR_INVITEONLYCHAN(args[1]);
        return 1;
    }
    if (args.size() == 3 || (_serv->getChannel(args[1])->_mod | MOD_CHAN_KEY && _serv->getChannel(args[1])->getKey() != "")) {
        if (_serv->getChannel(args[1])->getKey() != args[2]) {
            clicli << ERR_BADCHANNELKEY(args[1]);
            return 1;
        }
    }
	clicli.setCurrchan(args[1]);
    _serv->joinChannel(args[1], clicli);
    clicli << RPL_TOPIC(args[1], ("Welcome " + clicli.getNickname()));
    // _serv->getChannel(args[1])->addClient(clicli);
    // else
        // clicli << "You must be authenticated to join a channel\n";
    return 0;
}

void    JOIN::descr(Client& clicli) {
    clicli << "Usage: JOIN <canal>{,<canal>} [<clé>{,<clé>}]\n";
}