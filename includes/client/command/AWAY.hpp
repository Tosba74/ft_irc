/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWAY.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:28:33 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/07 18:34:14 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

// Commande: AWAY [message]
// 
// Avec le message AWAY, les clients peuvent définir une chaîne de réponse
// automatique pour toute commande PRIVMSG qui ledur est destinée (et non pas
// à un canal sur lequel ils sont).
// La réponse est envoyée directement par le serveur au client envoyant une commande PRIVMSG.
// Le seul serveur à répondre est celui sur lequel le client émetteur est situé.
// 
// Le message AWAY est utilisé soit avec un paramètre (pour définir un message AWAY)
// ou sans (pour retirer le message AWAY).
// 
// Réponses numériques :
        //    RPL_UNAWAY
		//    RPL_NOWAWAY
// Exemples:
// 
// AWAY :Parti déjeuner. De retour à 2 heures. ; définit le message d'absence en "Parti déjeuner. De retour à 2 heures.".
// :WiZ AWAY ; supprime l'absence de WiZ.

class AWAY : public ACommand
{
	public:
		AWAY(Server *serv);
		AWAY(AWAY const& src);
		~AWAY();
		int execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};