/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */
/*   Updated: 2022/11/18 01:27:16 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand/KICK.hpp"
#include "irc/Channel.hpp"

// Commande: KICK <canal> <utilisateur> [<commentaire>]

// La commande KICK est utilisée pour retirer par la force un utilisateur d'un canal (PART forcé).

// Seul un opérateur de canal peut kicker un autre utilisateur hors d'un canal.
// Tout serveur qui reçoit un message KICK vérifie si le message est valide
// (c'est-à-dire si l'expéditeur est bien un opérateur du canal) avant
// d'ôter la victime du canal.

// Réponses numériques :
    // ERR_NEEDMOREPARAMS
    // ERR_NOSUCHCHANNEL
    // ERR_BADCHANMASK
    // ERR_CHANOPRIVSNEEDED
    // ERR_NOTONCHANNEL

// Exemples:

// KICK &Melbourne Matthew ; Kick Matthew de &Melbourne
// KICK #Finnish John :Speaking English ; Kick John de #Finnish en spécifiant
// "Speaking English" comme raison (commentaire).
// :WiZ KICK #Finnish John ; Message KICK de WiZ pour retirer John du canal #Finnish
// NOTE:

// Il est possible d'étendre les paramètres de la commande KICK ainsi :
// <canal>{,<canal>} <utilisateur>{,<utilisateur>} [<commentaire>]

class KICK : public ACommand
{
    public:
        KICK(Server *serv);
        KICK(KICK const& src);
        ~KICK();
          virtual int             secureArgs(Client &clicli, std::vector<std::string> args) = 0;
        int     execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
