/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/12/08 16:02:08 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/PRIVMSG.hpp"
#include "irc/Server.hpp"

PRIVMSG::PRIVMSG(PRIVMSG const& src) : ACommand(src) {
	if (this != &src) {
		this->_serv = src._serv;
	}
}

PRIVMSG::PRIVMSG(Server *serv) : ACommand(serv) {}

PRIVMSG::~PRIVMSG() {}

// REPLY :
	//	clicli << ERR_CANNOTSENDTOCHAN(canal);
	// 	clicli << ERR_NOSUCHNICK(args[1]);
	//	clicli << ERR_NOTOPLEVEL(masque);
	// 	clicli << RPL_AWAY(args[1]);
	//	clicli << ERR_NOTEXTTOSEND();
	//	clicli << ERR_NORECIPIENT(args[0]);
	//	clicli << ERR_TOOMANYTARGETS(args[1]);

int     PRIVMSG::secureArgs(Client &clicli, std::vector<std::string> args) {
	if (args.size() < 3) {
		if (args.size() < 2)
			clicli << ERR_NOTEXTTOSEND();
		else
			clicli << ERR_NEEDMOREPARAMS(args[0]); 
		return 1;
	}
	if (args[1][0] == '&' || args[1][0] == '#') {
		if (!splitArgs(args[1]).empty()) {
			clicli << ERR_NORECIPIENT(args[0]);
			return 1;
		}
		std::vector<std::string> tmp = splitArgs(args[1]);
		std::vector<std::string>::iterator it = tmp.begin();
		for (; it != tmp.end(); ++it) {
			if (!_serv->getChannel(*it)) {
				clicli << ERR_NOSUCHNICK(args[1]);
				return 1;
			} else if (_serv->getChannel(*it)->_mod & MOD_CHAN_EXTMSG && !clicli.isInChannel(*it)) {
				clicli << ERR_CANNOTSENDTOCHAN(*it);
				return 1;
			}
		}

	} else {
		std::vector<std::string> tmp = splitArgs(args[1]);
		std::vector<std::string>::iterator it = tmp.begin();
		for (; it != tmp.end(); ++it) {
			if (_serv->getClient(*it)->_mod & MOD_AWAY) {
				clicli << RPL_AWAY(_serv->getClient(*it)->getNickname(), _serv->getClient(*it)->getAway());
				return 1;
			} else if (!_serv->getClient(*it)) {
				clicli << ERR_NOSUCHNICK(args[1]);
				return 1;
			}
		}
	}
	return 0;
}

int		PRIVMSG::execute(Client &clicli, std::vector<std::string> args) {
	if (secureArgs(clicli, args))
		return 1;
	std::string msg = args[2];
	if (args.size() > 2) {
		for (size_t i = 2; i < args.size(); ++i) {
			msg += " " + args[i];
		}
	}
	if (args[1][0] == '&' || args[1][0] == '#') {
		*_serv->getChannel(args[1]) << msg;
	} else {
		// _serv->getClient(args[1])->simpleMessage(msg);
		*_serv->getClient(args[1]) << (msg);
		// _serv->getClient(args[1]) << (":" + clicli.getNickname() + " PRIVMSG " + args[1] + " :" + msg);
	}
	return 0;
	
}
void	PRIVMSG::descr(Client& clicli) {
	clicli << "Usage: PRIVMSG <destinataire>{,<destinataire>} <texte à envoyer>\n";
}