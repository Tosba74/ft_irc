/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/15 01:45:02 by bmangin          ###   ########lyon.fr   */
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


int JOIN::secureArgs(Client &clicli, std::vector<std::string> args) {
    // Check Ban ERR #474
    for (std::map<int, Client&>::const_iterator it = _serv->getChannel(args[1])->getBan().begin(); it != _serv->getChannel(args[1])->getBan().end(); it++) {
        if (it->second == clicli) {
           clicli << ERR_BANNEDFROMCHAN(args[1]);
           return 1;
        }
    }
    // Check How many channels have a client & Channel-s limits ERR #405 #471
    if (clicli.getChannels().size() > CHAN_PER_USER) {
        clicli << ERR_TOOMANYCHANNELS(args[1]);
        return 1;
    } else if (_serv->getChannel(args[1])->getLimit() <= _serv->getChannel(args[1])->getClients().size()) {
        clicli << ERR_CHANNELISFULL(args[1]);
        return 1;
    }
    
    // Check MODE ERR #474 #475
    if (_serv->getChannel(args[1])->_mod != 0) {
        int tmp = 0;
        if (!(tmp | (_serv->getChannel(args[1])->_mod & MOD_CHAN_VIP))) {
            // if (clicli._mod & MOD_USER_VIP) {
                clicli << ERR_INVITEONLYCHAN(args[1]);
                return 1;
            // }
        // } else if (_serv->getChannel(args[1])->_mod & MOD_CHAN_KEY ) {
        } else if (!(tmp | (_serv->getChannel(args[1])->_mod & MOD_CHAN_KEY))) {
            if (_serv->getChannel(args[1])->getKey() != args[2]) {
                clicli << ERR_BADCHANNELKEY(args[1]);
                return 1;
            }
        }
    }
    return 0;
}
    
int JOIN::execute(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 2 || args.size() > 3) {
        clicli << ERR_NEEDMOREPARAMS(args[0]);
        return 1;
    }
    if (args[1].size() < 2 || args[1].at(0) != '#') {
        clicli << ERR_NOSUCHCHANNEL(args[1]);
        return 1;
    }
    // New Channel or not !?
	if (_serv->getChannel(args[1]) == NULL) {
	    _serv->joinChannel(args[1], clicli);
        if (args.size() == 3)
            _serv->getChannel(args[1])->setKey(args[2]);
    } else {
        if (!secureArgs(clicli, args)) {
            if (clicli.getCurrchan().compare(""))
                _serv->leaveChannel(clicli.getCurrchan(), clicli);
            _serv->joinChannel(args[1], clicli);
        } else
            return 1;
    }
    clicli << RPL_TOPIC(args[1], ("Welcome " + clicli.getNickname()));
    return 0;
}

void    JOIN::descr(Client& clicli) {
    clicli << "Usage: JOIN <canal>{,<canal>} [<clé>{,<clé>}]\n";
}
