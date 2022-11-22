/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BAN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/BAN.hpp"
#include "irc/Server.hpp"

BAN::BAN(Server *serv): ACommand(serv) {}

BAN::BAN(BAN const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

BAN::~BAN() {}

int		BAN::secureArgs(Client &clicli, std::vector<std::string> args) { 
    (void)clicli;
    (void)args;
    return 0;
}

int BAN::execute(Client &clicli, std::vector<std::string> args) {
	size_t pos = 0;
	if ((pos = args[1].find("-")) == std::string::npos)
	{
		std::vector<std::string> targets;
	       	std::string             tarPart;
	       	size_t pos = 0;
	        while ((pos = args[2].find(",")) != std::string::npos) {
	                tarPart = args[2].substr(0, pos);
	                targets.push_back(tarPart);
	                args[2].erase(0, pos + 1);
	        }
	        targets.push_back(args[2]);
	        
		for (std::vector<std::string>::iterator i = targets.begin(); i != targets.end(); i++)
	        {
	                _serv->getChannel(args[1])->removeClient(*(_serv->getClient(*i)));
			_serv->getChannel(args[1])->addBan(*(_serv->getClient(*i)));
	                std::string     msg = ":" + clicli.getNickname() + " KICK " + args[1] + " " + (*i);
	                if (args.size() == 4)
	                        msg += " " + args[3];
	                else
	                        msg += " :" + clicli.getNickname();
	                //_serv->getChannel(args[1])->msgToUsers(msg);
	                *(_serv->getChannel(args[1])) << msg;
	                // ni l'un ni l'autre n'envoie a un user NC, a tester avec 2 clients weechat
	        }
	}
	/*else
	{
		if (pos = args[1].find("r") != std::string:npos)
			_serv->getChannel(args[1])->addBan(*(_serv->getclient(*i)));
	}*/
        return 0;
}

void    BAN::descr(Client& clicli) {
	clicli << "Commande: BAN [message]\n";
}
