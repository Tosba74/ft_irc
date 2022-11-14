/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */
/*   Updated: 2022/11/14 21:45:47 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"
#include "irc/Channel.hpp"

// Commande: JOIN <canal>{,<canal>} [<clé>{,<clé>}]
// 
// La commande JOIN est utilisée par un client pour commencer à écouter un canal spécifique.
// L'accès à un canal est autorisé ou non uniquement par le serveur auquel le client est connecté;
// tous les autres serveurs ajoutent automatiquement l'utilisateur au canal quand la demande vient
// d'un autre serveur. Les conditions qui affectent ceci sont les suivantes :
    // 1. L'utilisateur doit être invité si le canal est en mode "sur invitation seulement"
    // 2. Le pseudo/nom d'utilisateur/nom d'hôte ne doit pas correspondre à un bannissement actif.
    // 3. La bonne clé (mot de passe) doit être fournie si elle est définie.

// Voir cmd MODE.

// Une fois qu'un utilisateur a accès à un canal, il reçoit des notifications de toutes les
// commandes que son serveur reçoit et qui affectent le canal. Cela inclut MODE, KICK, PART,
// QUIT, et bien sûrPRIVMSG/NOTICE.
// La commande JOIN doit être diffusée à tous les serveurs du réseau pour qu'ils sachent
// où trouver qui est dans chaque canal. Cela permet une distribution optimale des messages
// PRIVMSG/NOTICE du canal.

// Si un JOIN a lieu avec succès, on envoie à l'utilisateur le sujet du canal (en utilisant
// RPL_TOPIC) et la liste des utilisateurs du canal (en utilisant RPL_NAMREPLY), y compris
// lui-même.

// REPLY :
    // ERR_NEEDMOREPARAMS
    // ERR_BANNEDFROMCHAN
    // ERR_INVITEONLYCHAN
    // ERR_BADCHANNELKEY
    // ERR_CHANNELISFULL
    // ERR_BADCHANMASK
    // ERR_NOSUCHCHANNEL
    // ERR_TOOMANYCHANNELS
    // RPL_TOPIC

// Exemples:
    // JOIN #foobar ; accède au canal #foobar.
    // JOIN &foo fubar ; accède au canal &foo en utilisant la clé "fubar".
    // JOIN #foo,&bar fubar ; accède au canal #foo en utilisant la clé "fubar", et &bar en n'utilisant pas de clé.
    // JOIN #foo,#bar fubar,foobar ; accède au canal #foo en utilisant la clé "fubar", et au canal #bar en utilisant la clé "foobar".
    // JOIN #foo,#bar ; accède au canaux #foo and #bar.
    // :WiZ JOIN #Twilight_zone ; message JOIN de WiZ

class JOIN : public ACommand {
    private:
        int     secureArgs(Client &clicli, std::vector<std::string> args);

    public:
        JOIN(Server *serv);
        JOIN(JOIN const& src);
        ~JOIN();
        int     execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
