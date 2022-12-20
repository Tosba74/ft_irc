/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/12/20 22:28:39 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/JOIN.hpp"
#include "irc/Server.hpp"
#include <unistd.h>

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

static int static_fd = 12;

Client* JOIN::TESTEUSE(std::string name) {
    struct sockaddr_in  addr = {};
    Client *Testeuse = new Client((int)static_fd, addr);
    Testeuse->setNickname(name);
    Testeuse->setUsername(name);
    Testeuse->setRealName(name);
    Testeuse->setHostname("0");
    Testeuse->setNameserver("ircserv");
    Testeuse->setVersion("1.3");
    Testeuse->setPass("lol");
    Testeuse->setRegister(true);
    Testeuse->_mod = MOD_USER_INVIS;
    static_fd++;

    return Testeuse;
}

int JOIN::secureArgs(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 2 || args.size() > 3) {
        clicli << ERR_NEEDMOREPARAMS(args[0]);
        return 1;
    }

	std::vector<std::string> tmp = splitArgs(args[1]);
	std::vector<std::string>::const_iterator it = tmp.begin();
    if (args.size() == 3)
	    std::vector<std::string> ktmp = splitArgs(args[2]);
    int i = 0;
    
	for (; it != tmp.end(); ++it) {
        // Check How many channels have a client & Channel-s limits ERR #405 #471
        if ((clicli.getChannels().size() + tmp.size()) >= CHAN_PER_USER) {
            clicli << ERR_TOOMANYCHANNELS(*it);
            return 1;
        }
        if (checkChannel(clicli, *it)) {
            return 1;
        }
        if (_serv->getChannel(*it)) {
            if (_serv->getChannel(*it)->getLimit() <= _serv->getChannel(*it)->getClients().size()) {
                clicli << ERR_CHANNELISFULL(*it);
                return 1;
            }
            if (_serv->getChannel(*it)->isBan(clicli)) { // Check Ban ERR #474
                clicli << ERR_BANNEDFROMCHAN(*it);
                return 1;
            }
            if ((_serv->getChannel(*it)->_mod & MOD_CHAN_VIP) && !_serv->getChannel(*it)->isVip(clicli)) {
                    clicli << ERR_INVITEONLYCHAN(*it);
                    return 1;
            }
            if ((_serv->getChannel(*it)->_mod & MOD_CHAN_KEY)) {
	            std::vector<std::string> ktmp = splitArgs(args[2]);
                if (args.size() != 3 || _serv->getChannel(*it)->getKey().compare(ktmp[i])) {
                    clicli << ERR_BADCHANNELKEY(ktmp[i]);
                    return 1; 
                }
            }
        }
        i++;
    }
    return 0;
}
    
int JOIN::execute(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 2) {
        clicli << ERR_NEEDMOREPARAMS(args[0]);
        return 1;
    }
    if (secureArgs(clicli, args))
        return 1;
	std::vector<std::string> tmp = splitArgs(args[1]);
	std::vector<std::string>::const_iterator it = tmp.begin();
    int i = 0;
    
	for (; it != tmp.end(); ++it) {
	    if (_serv->getChannel(*it) == NULL) {
            if (checkChannel(clicli, *it))
                return 1;
	        _serv->joinChannel(*it, clicli);
	    	_serv->getChannel(*it)->addModo(clicli);
            if (args.size() == 3) {
	            std::vector<std::string> ktmp = splitArgs(args[2]);
                if (!ktmp[i].empty()) {
                    _serv->getChannel(*it)->setKey(ktmp[i]);
                }
            }
        } else {
            if (checkChannel(clicli, *it))
                return 1;
            _serv->joinChannel(*it, clicli);
            if (args.size() == 3) {
	            std::vector<std::string> ktmp = splitArgs(args[2]);
                if (!ktmp[i].empty()) {
                    _serv->getChannel(*it)->setKey(ktmp[i]);
                }
            }
        }
        i++;
	    _serv->getChannel(*it)->msgToUsers(clicli, RPL_JOIN(clicli.getNickname(), *it));
	    clicli.simpleMessage(RPL_JOIN(clicli.getNickname(), *it));
        if (!_serv->getChannel(*it)->getSujet().compare(""))
            clicli << RPL_TOPIC(*it, "Welcome", clicli.getNickname());
        else
            clicli << RPL_TOPIC(*it, _serv->getChannel(*it)->getSujet(), clicli.getNickname());
	    clicli << RPL_NAMREPLY(*it, clicli.getNickname(), _serv->getChannel(*it)->getStringUser());
    }
    
    return 0;
    std::cout << "\e[32m--------J'AI PLEIN DE COPINE--------\e[0m" << std::endl;
    
    // Client *Julie = TESTEUSE("Julie");
    // Julie->setCurrchan(args[1]);
    // _serv->joinChannel(args[1], *Julie);
    // std::cout << Julie;
    
    // Client *Sophie = TESTEUSE("Sophie");
    // Sophie->setCurrchan(args[1]);
    // _serv->joinChannel(args[1], *Sophie);
    
    // Client *Martine = TESTEUSE("Martine");
    // Martine->setCurrchan(args[1]);
    // _serv->joinChannel(args[1], *Martine);
    
    // Client *Edwige = TESTEUSE("Edwige");
    // Edwige->setCurrchan(args[1]);
    // _serv->getChannel(args[1])->addModo(Edwige->getNickname());
    // _serv->joinChannel(args[1], *Edwige);
    
    std::cout << "\e[32m------------------------------------\e[0m" << std::endl;
    
	// std::cout << *_serv->getChannel(args[1]);

	_serv->getChannel(args[1])->msgToUsers(clicli, RPL_JOIN(clicli.getNickname(), args[1]));
	clicli.simpleMessage(RPL_JOIN(clicli.getNickname(), args[1]));
    if (!_serv->getChannel(args[1])->getSujet().compare(""))
        clicli << RPL_TOPIC(args[1], "Welcome", clicli.getNickname());
        // clicli << RPL_NOTOPIC(args[1]);
    else
        clicli << RPL_TOPIC(args[1], _serv->getChannel(args[1])->getSujet(), clicli.getNickname());
	clicli << RPL_NAMREPLY(args[1], clicli.getNickname(), _serv->getChannel(args[1])->getStringUser());
	clicli << RPL_ENDOFNAMES(args[1], clicli.getNickname());
    return 0;
}

void    JOIN::descr(Client& clicli) {
    clicli << "Usage: JOIN <canal>{,<canal>} [<clé>{,<clé>}]\n";
}
