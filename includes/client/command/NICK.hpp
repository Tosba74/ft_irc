/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:57:20 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/15 00:35:22 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

// Commande : NICK <pseudonyme> [ <compteur de distance> ]

// Le message NICK est utilisé pour donner un pseudonyme à un utilisateur,
// ou pour changer le pseudonyme précédent.
// Le paramètre <compteur de distance> n'est utilisé que par les serveurs,
// et sert à indiquer quelle est la distance entre un utilisateur et son serveur local.
// Une connexion locale a un compteur de distance de zéro.
// Si un client fournit un compteur de distance, il doit être ignoré.

// Si un message NICK arrive à un serveur qui connaît déjà un autre client de pseudo identique,
// une collision de pseudonymes a lieu. Le résultat d'une collision de pseudonymes est
// la suppression de toutes les instances du pseudonyme de la base du serveur,
// et l'envoi d'un message KILL afin de retirer le pseudonyme des bases de données
// de tous les autres serveurs.
// Si le message NICK à l'origine de la collision de pseudonymes est un changement de
// pseudonyme, alors le pseudo originel (l'ancien) doit aussi être retiré.

// Si le serveur reçoit un NICK identique d'un client auquel il est connecté directement,
// il peut envoyer un ERR_NICKCOLLISION au client local, ignorer la commande NICK, et
// ne pas générer de KILLs.

// REPLY :
	// ERR_NONICKNAMEGIVEN
	// ERR_ERRONEUSNICKNAME
	// ERR_NICKNAMEINUSE
	// ERR_NICKCOLLISION

// Exemples:
	// NICK Wiz ; Ajout d'un nouveau pseudo "Wiz".
	// :WiZ NICK Kilroy ; WiZ change son pseudo en Kilroy.

class NICK : public ACommand {
	public:
		NICK(Server *serv);
		NICK(NICK const& src);
		~NICK();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
