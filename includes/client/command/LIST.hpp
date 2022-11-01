/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */
/*   Updated: 2022/11/01 17:12:51 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"
#include "irc/Channel.hpp"

// Commande: LIST [<canal>{,<canal>} [<serveur>]]
// 
// Le message LIST est utilisé pour lister les canaux et leur sujet.
// Si le paramètre <canal> est utilisé, seul le statut de ces canaux est affiché.
// Les canaux privés sont listés (sans leur sujet) comme canal "Prv" à moins que
// le client qui génère la requête soit effectivement sur le canal.
// De même, les canaux secrets ne sont pas listés du tout, à moins que le client
// soit un membre du canal en question.

// REPLY :
    // ERR_NOSUCHSERVER
    // RPL_LISTSTART
    // RPL_LIST
    // RPL_LISTEND
    
// Exemples:
    // LIST ; Liste tous les canaux.
    // LIST #twilight_zone,#42 ; Liste les canaux #twilight_zone et #42

class LIST : public ACommand
{
    public:
        LIST(Server *serv);
        LIST(LIST const& src);
        ~LIST();
        int     execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
