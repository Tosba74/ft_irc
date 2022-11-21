/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:28:33 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/15 00:34:41 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

// Commande: KICK [message]
// 
// Avec le message KICK, les clients peuvent définir une chaîne de réponse
// automatique pour toute commande PRIVMSG qui ledur est destinée (et non pas
// à un canal sur lequel ils sont).
// La réponse est envoyée directement par le serveur au client envoyant une commande PRIVMSG.
// Le seul serveur à répondre est celui sur lequel le client émetteur est situé.
// 
// Le message KICK est utilisé soit avec un paramètre (pour définir un message KICK)
// ou sans (pour retirer le message KICK).
// 
// Réponses numériques :
        //    RPL_UNKICK
		//    RPL_NOWKICK
// Exemples:
// 
// KICK :Parti déjeuner. De retour à 2 heures. ; définit le message d'absence en "Parti déjeuner. De retour à 2 heures.".
// :WiZ KICK ; supprime l'absence de WiZ.

class KICK : public ACommand
{
	public:
		KICK(Server *serv);
		KICK(KICK const& src);
		~KICK();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
