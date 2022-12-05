/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */
/*   Updated: 2022/12/05 23:31:12 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"
#include "irc/Channel.hpp"

// Commande: PART <canal>{,< canal >}

// Le message PART provoque le retrait du client expéditeur de la liste des
// utilisateurs actifs pour tous les canaux listés dans la chaîne de paramètres.

// Réponses numériques:
    // ERR_NEEDMOREPARAMS
    // ERR_NOSUCHCHANNEL
    // ERR_NOTONCHANNEL

// Exemples:

// PART #twilight_zone ; quitte le canal "#twilight_zone"
// PART #oz-ops,&group5 ; quitte les canaux "&group5" et "#oz-ops".

class PART : public ACommand
{
    public:
        PART(Server *serv);
        PART(PART const& src);
        ~PART();
        
        int     secureArgs(Client &clicli, std::vector<std::string> args);
        int     execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
