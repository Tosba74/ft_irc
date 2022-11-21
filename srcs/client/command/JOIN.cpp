/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/21 15:53:50 by bmangin          ###   ########lyon.fr   */
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
    if (clicli.isBanned(args[1])) {
        clicli << ERR_BANNEDFROMCHAN(args[1]);
        return 1;
    }
    if (!verifNameChan(clicli, args[1])) {
        return 1;
    }
    // Check How many channels have a client & Channel-s limits ERR #405 #471
    if (clicli.getChannels().size() > CHAN_PER_USER) {
        clicli << ERR_TOOMANYCHANNELS(args[1]);
        return 1;
    }
    if (_serv->getChannel(args[1])->getLimit() >= _serv->getChannel(args[1])->getClients().size()) {
        clicli << ERR_CHANNELISFULL(args[1]);
        return 1;
    }
    if (clicli.isBanned(args[1])) {
        clicli << ERR_BANNEDFROMCHAN(args[1]);
        return 1;
    }
    int tmp = 0;
    if (_serv->getChannel(args[1])->_mod != 0) {
        if (!(tmp | (_serv->getChannel(args[1])->_mod & MOD_CHAN_VIP))) {
            // if (clicli._mod & MOD_USER_VIP) {
                clicli << ERR_INVITEONLYCHAN(args[1]);
                return 1;
            // }
        // } else if (_serv->getChannel(args[1])->_mod & MOD_CHAN_KEY ) {
        } else if (!(tmp | (_serv->getChannel(args[1])->_mod & MOD_CHAN_KEY))) {
            std::cout << (tmp | (_serv->getChannel(args[1])->_mod & MOD_CHAN_KEY)) << std::endl;
            if (args.size() != 3 || !_serv->getChannel(args[1])->getKey().compare(args[2])) {
                clicli << ERR_BADCHANNELKEY(args[1]);
                return 1;
            } else
                return 0;
        }
    }
    return 0;
}
    
int JOIN::execute(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 2 || args.size() > 3) {
        clicli << ERR_NEEDMOREPARAMS(args[0]);
        return 1;
    }
    // if (!secureArgs(clicli, args))
        // return 1;
    // if (args[1].size() < 2 || args[1].at(0) != '#') {
        // clicli << ERR_NOSUCHCHANNEL(args[1]);
        // return 1;
    // }

    // New Channel or not !?
	if (_serv->getChannel(args[1]) == NULL) {
        if (!verifNameChan(clicli, args[1])) {
	        _serv->joinChannel(args[1], clicli);
		_serv->getChannel(args[1])->addModo(clicli.getNickname()); // si new chan, passer le createur modo
	}
        if (args.size() == 3)
            _serv->getChannel(args[1])->setKey(args[2]);
    } else {
        if (!secureArgs(clicli, args)) {
            if (clicli.getCurrchan().compare(""))
                _serv->leaveChannel(clicli.getCurrchan(), clicli);
            _serv->joinChannel(args[1], clicli);
        }
    }
	std::string validation = ":" + clicli.getNickname() + " JOIN :" + args[1];
	//clicli.simpleMessage(validation);
	_serv->getChannel(args[1])->msgToUsers(validation);
	clicli << RPL_TOPIC(args[1], "Welcome", clicli.getNickname());
	std::string	reply = RPL_NAMREPLY(args[1], clicli.getNickname());
	reply += _serv->getChannel(args[1])->getStringUser();
	clicli << reply;
	clicli << RPL_ENDOFNAMES(args[1], clicli.getNickname());
    return 0;
}

void    JOIN::descr(Client& clicli) {
    clicli << "Usage: JOIN <canal>{,<canal>} [<clé>{,<clé>}]\n";
}
