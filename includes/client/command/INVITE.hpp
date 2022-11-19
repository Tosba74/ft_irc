/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */
/*   Updated: 2022/11/01 17:12:51 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand/INVITE.hpp"
#include "irc/Channel.hpp"

// Commande: INVITE <pseudonyme> <canal>

// Le message INVITE est utilisé pour inviter des utilisateurs dans un canal.
// Le paramètre <pseudonyme> est le pseudonyme de la personne à inviter dans le
// canal destination <canal>. Il n'est pas nécessaire que le canal dans lequel
// la personne est invitée existe, ni même soit valide. Pour inviter une personne
// dans un canal en mode sur invitation (MODE +i), le client envoyant l'invitation
// doit être opérateur sur le canal désigné.

// Réponses numériques :
    // ERR_NEEDMOREPARAMS
    // ERR_NOSUCHNICK
    // ERR_NOTONCHANNEL
    // ERR_USERONCHANNEL
    // ERR_CHANOPRIVSNEEDED
    // RPL_INVITING
    // RPL_AWAY

// Exemples:
// 
// :Angel INVITE Wiz #Dust ; L'utilisateur Angel invite WiZ sur le canal #Dust
// INVITE Wiz #Twilight_Zone ; Commande pour inviter WiZ sur #Twilight_zone


class INVITE : public ACommand
{
    public:
        INVITE(Server *serv);
        INVITE(INVITE const& src);
        ~INVITE();

        virtual int             secureArgs(Client &clicli, std::vector<std::string> args) = 0;
        int     execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
