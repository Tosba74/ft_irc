/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.hpp                                           :+:      :+:    :+:   */
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

// Commande: NOTICE
// Paramètres: <pseudonyme> <texte>

// Le message NOTICE s'utilise de la même façon que PRIVMSG.
// La différence entre NOTICE et PRIVMSG est qu'aucune réponse automatique ne doit
// être envoyée en réponse à un message NOTICE. Ceci est aussi valable pour les
// serveurs - ils ne doivent pas renvoyer de message d'erreur à la réception
// d'un message NOTICE. Le but de cette règle est d'éviter les boucles entre
// les clients qui enverraient automatiquement quelque chose en réponse à une
// requête. Cela est typiquement utilisé par des automates (des clients qui
// ont une intelligence artificielle ou un autre programme interactif contrôlant
// leurs actions) qui répondent systématiquement aux réponses d'autres automates.

// Voir PRIVMSG pour les détails sur les réponses, et pour les exemples.


class NOTICE : public ACommand
{
    public:
        NOTICE(Server *serv);
        NOTICE(NOTICE const& src);
        ~NOTICE();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
        int     execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
