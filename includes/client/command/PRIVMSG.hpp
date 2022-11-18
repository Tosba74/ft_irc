/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSGPRIV.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:13:41 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/18 14:34:08 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

// Rappel :
	// Le but principal du protocole IRC est de fournir une base afin que des clients
	// puissent communiquer entre eux.
	// PRIVMSG et NOTICE sont les seuls messages disponibles qui réalisent effectivement
	// l'acheminement d'un message textuel d'un client à un autre - le reste le rend
	// juste possible et assure que cela se passe de façon fiable et structurée.

// Commande: PRIVMSG <destinataire>{,<destinataire>} <texte à envoyer >

// PRIVMSG est utilisé pour envoyer un message privé entre des utilisateurs.
// <destinataire> est le pseudonyme du destinataire du message.
// <destinataire> peut aussi être une liste de noms ou de canaux, séparés par des virgules.

// Le paramètre <destinataire> peut aussi être un masque d'hôte (masque #) ou un masque
// de serveur (masque $). Le masque doit contenir au moins un (1) ".", et aucun joker
// après le dernier ".".
// Cette limitation a pour but d'empêcher les gens d'envoyer des messages à "#*" ou à "$*",
// ce qui provoquerait la diffusion à tous les utilisateurs; l'expérience montre qu'on
// en abuse plus qu'on en use intelligemment, de façon responsable.
// Les jokers sont les caractères '*' et '?'.
// Ces extensions de PRIVMSG ne sont accessibles qu'aux opérateurs.

// REPLY :
	// ERR_NORECIPIENT
	// ERR_NOTEXTTOSEND
	// ERR_CANNOTSENDTOCHAN
	// ERR_NOTOPLEVEL
	// ERR_WILDTOPLEVEL
	// ERR_TOOMANYTARGETS
	// ERR_NOSUCHNICK
	// RPL_AWAY

// Exemples:
	// :Angel PRIVMSG Wiz :Salut, est-ce que tu reçois ce message ? ; Message d'Angel à Wiz.
	// PRIVMSG Angel :oui, je le reçois ! ; Message à Angel.
	// PRIVMSG jto@tolsun.oulu.fi :Hello ! ; Message à un client du serveur tolsun.oulu.fi dont le nom est "jto".
	// PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting. ; Message à tous sur les serveurs dont les noms correspondent à *.fi.
	// PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions ; Message à tous les utilisateurs qui viennent d'un hôte dont le nom correspond à *.edu.

class PRIVMSG : public ACommand
{
	public:
		PRIVMSG(Server *serv);
		PRIVMSG(PRIVMSG const& src);
		~PRIVMSG();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};