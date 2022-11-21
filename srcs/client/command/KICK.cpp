/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:29:04 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/21 13:39:02 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/KICK.hpp"
#include "irc/Server.hpp"

// ERR_NOSUCHCHANNEL
// ERR_NOTONCHANNEL
// ERR_NEEDMOREPARAMS
// ERR_BADCHANMASK
// ERR_CHANOPRIVSNEEDED

KICK::KICK(KICK const& src) : ACommand(src) {
	if (this != &src) {
        this->_serv = src._serv;
	}
}

KICK::KICK(Server *serv) : ACommand(serv) {}

KICK::~KICK() {}

int		KICK::secureArgs(Client &clicli, std::vector<std::string> args) {
	(void)clicli;
	(void)args;
	return 0;
}

int		KICK::execute(Client &clicli, std::vector<std::string> args) {
        std::vector<std::string> targets;
        std::string             msgPart;
        size_t pos = 0;
        while ((pos = args[2].find(",")) != std::string::npos) {
                msgPart = args[2].substr(0, pos);
                targets.push_back(msgPart);
                args[2].erase(0, pos + 1);
        }
	targets.push_back(args[2]);
	if (!_serv->getChannel(args[1]))
	{
		clicli << ERR_NOSUCHCHANNEL(args[1]);
		return 1;
	}

	// TODO, impossible sans avoir acces a un getClient() d'un chan
	//if (_serv->getChannel(args[1]).userIsInChan(clicli.getNickname()) != 0)
	//	clicli << ERR_NOTONCHANNEL(args[1]);
	if (args.size() < 3)
	{
		clicli << ERR_NEEDMOREPARAMS(args[0]);
		return 1;
	}
	if (_serv->getChannel(args[1])->isModo(clicli.getNickname()))
	{
		clicli << ERR_CHANOPRIVSNEEDED(args[1]);
		return 1;
	}

	for (std::vector<std::string>::iterator i = targets.begin(); i != targets.end(); i++)
	{
		_serv->getChannel(args[1])->removeClient(*(_serv->getClient(*i)));
		std::string	msg = ":" + clicli.getNickname() + " KICK " + args[1] + " " + (*i);
		if (args.size() == 4)
			msg += " :" + args[4];
		else
			msg += " :" + clicli.getNickname();
		_serv->getChannel(args[1])->msgToUsers(msg);
	}
        return 0;
}

void	KICK::descr(Client& clicli) {
	clicli << "Commande: KICK [message]\n";
}
