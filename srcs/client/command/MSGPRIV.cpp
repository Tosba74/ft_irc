/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSGPRIV.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/30 23:00:21 by bmangin          ###   ########lyon.fr   */
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

// Réponses numériques:
// 
        //    ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
        //    ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
        //    ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
        //    ERR_NOSUCHNICK
        //    RPL_AWAY

int MSGPRIV::execute(Client &clicli, std::vector<std::string> args) {
	Client	*target = _serv->getClient(args[0]);
	std::string message = "PRIVMSG " + args[0] + " :" + args[1];
	
	if (!target)
		clicli << ERR_NOSUCHNICK(args[0]);
	else
		*target << message;
	return 0;
}

void	MSGPRIV::descr(Client& clicli) {
	clicli << "Commande: PRIVMSG\nParamètres: <destinataire>{,<destinataire>} <texte à envoyer>\n";
}