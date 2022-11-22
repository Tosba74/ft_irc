/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/22 16:26:23 by bmangin          ###   ########lyon.fr   */
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
	//	clicli << ERR_NOTOPLEVEL(masque);
	// 	clicli << ERR_WILDTOPLEVEL(masque);
	//	clicli << ERR_CANNOTSENDTOCHAN(canal);
	//	clicli << ERR_NOTEXTTOSEND();
	//	clicli << ERR_NORECIPIENT(args[0]);
	//	clicli << ERR_TOOMANYTARGETS(args[1]);
	// 	clicli << ERR_NOSUCHNICK(args[1]);
	// 	clicli << RPL_AWAY(args[1]);

int     PRIVMSG::secureArgs(Client &clicli, std::vector<std::string> args) {
	(void)clicli;
	(void)args;
	return 0;
}

void PRIVMSG::sendMsg(Client &clicli, std::string target, std::string msg) {
	Client	*user = _serv->getClient(target);
	Channel *chan = _serv->getChannel(target);
	std::string away;
	std::string tmp;

	if (!user && !chan)
	{
		if (target[0] != '#')
			clicli << ERR_NOSUCHNICK(target);
		else
			clicli << ERR_CANNOTSENDTOCHAN(target);
	}
	else if (user)
	{
		if (user->getAway())
		{
			away = " 301 " + user->getNickname() + " :" + user->getAwayMsg();
			user->simpleMessage(away); //TODO: Probablement pas fonctionnel, c'est un placeholder
		}
		else
		{
			tmp = ":" + clicli.getNickname() + " " + "PRIVMSG " + " " + user->getNickname() + " " + msg;
			user->simpleMessage(tmp);
		}
	}
	else
		chan->msgToUsers(msg); //TODO: need fix
}

int PRIVMSG::execute(Client &clicli, std::vector<std::string> args) {
	std::string message;
	for(int i = 2; args.size() >= (size_t)i; i++)
	{
		if (i != 2)
			message += " ";
		message += args[i];
	}

	if (args[1].at(0) == ':'){
		clicli << ERR_NORECIPIENT(args[0]);
		return 1;
	}
	else if (args[2].length() <= 1){
		clicli << ERR_NOTEXTTOSEND();
		return 1;
	}

	size_t pos = 0;
	std::string token;
	while ((pos = args[1].find(",")) != std::string::npos) {
		token = args[1].substr(0, pos);
		sendMsg(clicli, token, message);
		args[1].erase(0, pos + 1);
	}
	sendMsg(clicli, args[1], message);
	return 0;
}

void	PRIVMSG::descr(Client& clicli) {
	clicli << "Usage: PRIVMSG <destinataire>{,<destinataire>} <texte à envoyer>\n";
}