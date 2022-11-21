/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */
/*   Updated: 2022/11/18 01:28:17 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand/KILL.hpp"
#include "irc/Channel.hpp"

// Commande: KILL <pseudonyme> <commentaire>

// Le message KILL est utilisé pour provoquer la fermeture de la connexion client/serveur
// par le serveur qui gère cette connexion. KILL est aussi utilisé par les serveurs qui
// rencontrent un doublon dans la liste des entrées de pseudonymes valides, afin de retirer
// les deux entrées. Elle est également accessible aux opérateurs.

// Les clients qui ont des reconnexions automatiques rendent cette commande inefficace,
// car la déconnexion est brève. Cela permet tout de même d'interrompre un flux de données
// et est utile pour arrêter un flux abusif (trop important). Tout utilisateur peut
// demander à recevoir les messages KILL générés pour d'autres clients afin de garder
// un oeil sur les fauteurs de trouble éventuels.

// Dans une arène où les pseudonymes doivent être globalement uniques, les messages KILL
// sont envoyés à chaque fois qu'un doublon est détecté (c'est-à-dire une tentative
// d'enregistrer deux utilisateurs avec le même pseudonyme) dans l'espoir qu'ils
// disparaîtront tous les deux, et qu'un seul réapparaîtra.

// Le commentaire doit refléter la véritable raison du KILL. Pour les messages issus
// de serveurs, il est habituellement constitué des détails concernant les origines
// des deux pseudonymes en conflit. Les utilisateurs, eux, sont libres de fournir une
// raison adéquate, de façon à satisfaire ceux qui le voient. Afin de prévenir/d'éviter
// des KILL maquillés pour cacher l'identité de l'auteur d'être générés, le commentaire
// contient également un 'chemin de KILL' qui est mis à jour par tous les serveurs par
// lequel il passe, chacun ajoutant son nom au chemin.

// Réponses numériques :
          // ERR_NOPRIVILEGES                
          // ERR_NEEDMOREPARAMS
          // ERR_NOSUCHNICK                  
          // ERR_CANTKILLSERVER
          
// Exemple:

// KILL David (csd.bu.edu <- tolsun.oulu.fi) ; Collision de pseudonymes entre csd.bu.edu
// et tolson.oulu.fi
// NOTE:
// Il est recommandé que seuls les opérateurs soient autorisés à déconnecter d'autres
// utilisateurs avec un message KILL. Dans un monde parfait, même les opérateurs ne 
// devraient pas avoir besoin de cette commande, et on laisserait les serveurs se débrouiller.


class KILL : public ACommand
{
    public:
      KILL(Server *serv);
      KILL(KILL const& src);
      ~KILL();
      virtual int   secureArgs(Client &clicli, std::vector<std::string> args) = 0;
      int           execute(Client &clicli, std::vector<std::string> args);
		  void          descr(Client& clicli);
};
