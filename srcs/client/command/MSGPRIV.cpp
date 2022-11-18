/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSGPRIV.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/18 15:54:46 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/MSGPRIV.hpp"
#include "irc/Server.hpp"

MSGPRIV::MSGPRIV(MSGPRIV const& src) : ACommand(src) {
	if (this != &src) {
        this->_serv = src._serv;
	}
}

MSGPRIV::MSGPRIV(Server *serv) : ACommand(serv) {}

MSGPRIV::~MSGPRIV() {}

// REPLY :
	//	clicli << ERR_NOTOPLEVEL(masque);
	// 	clicli << ERR_WILDTOPLEVEL(masque);
	//	clicli << ERR_CANNOTSENDTOCHAN(canal);

	//	clicli << ERR_NOTEXTTOSEND();
	//	clicli << ERR_NORECIPIENT(args[0]);
	//	clicli << ERR_TOOMANYTARGETS(args[1]);
	// 	clicli << ERR_NOSUCHNICK(args[1]);
	// 	clicli << RPL_AWAY(args[1]);

int     MSGPRIV::secureArgs(Client &clicli, std::vector<std::string> args) {
	(void)clicli;
	(void)args;
	return 0;
}

int MSGPRIV::execute(Client &clicli, std::vector<std::string> args) {
	Client	*target = _serv->getClient(args[1]);
	std::string message = "PRIVMSG " + clicli.getNickname() + " :";
	for(int i = 2; args.size() <= (size_t)i; i++)
	{
		if (i != 2)
			message += " ";
		message += args[i];
	}

	if (!target)
		clicli << ERR_NOSUCHNICK(args[0]);
	else
		*target << message;
	return 0;
}

void	MSGPRIV::descr(Client& clicli) {
	clicli << "Usage: PRIVMSG <destinataire>{,<destinataire>} <texte à envoyer>\n";
}