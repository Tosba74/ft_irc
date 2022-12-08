/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.hpp                                           :+:      :+:    :+:   */
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

// Commande: TOPIC
// Paramètres: <canal> [<sujet>]

// Le message TOPIC est utilisé pour modifier ou voir le sujet d'un canal. Le sujet du canal <canal>
// est renvoyé s'il n'y a pas de <sujet> fourni en paramètre. Si le paramètre <sujet> est présent,
// le  du canal changera si le mode du canal le permet.

// Réponses numériques :
          //  ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
          //  RPL_NOTOPIC                     RPL_TOPIC
          //  ERR_CHANOPRIVSNEEDED

// Exemples:
// :Wiz TOPIC #test :New topic ; L'utilisateur Wiz définit le sujet.
// TOPIC #test :another topic ; Change le sujet du canal #test en "another topic".
// TOPIC #test ; Vérifie le sujet de #test.

class TOPIC : public ACommand
{
    public:
      TOPIC(Server *serv);
      TOPIC(TOPIC const& src);
      ~TOPIC();
      int   secureArgs(Client &clicli, std::vector<std::string> args);
      int   execute(Client &clicli, std::vector<std::string> args);
      void	descr(Client& clicli);
};
