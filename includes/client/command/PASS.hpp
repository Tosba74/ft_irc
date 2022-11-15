/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:37 by emenella          #+#    #+#             */
/*   Updated: 2022/11/15 00:35:37 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"

// Commande : PASS <mot de passe>

// La commande PASS est utilisée pour définir le 'mot de passe de connexion'.
// Le mot de passe peut et doit être défini avant toute tentative de connexion.
// A l'heure actuelle, cela signifie que les clients doivent envoyer une commande PASS
// avant d'envoyer la combinaison NICK/USER, et que les serveurs doivent envoyer une
// commande PASS avant toute commande SERVER.
// Le mot de passe fourni doit correspondre à celui contenu dans les
// lignes C/N (pour les serveurs) ou dans les lignes I (pour les clients).
// Il est possible d'envoyer plusieurs commandes PASS avant de s'enregistrer,
// mais seule la dernière est utilisée pour la vérification, et elle ne peut
// plus changer une fois la connexion établie.

// REPLY :
    // ERR_NEEDMOREPARAMS
    // ERR_ALREADYREGISTRED

// Exemple:
    // PASS motdepasssecretici

class PASS: public ACommand
{
    public:
        PASS(Server *serv);
        PASS(PASS const& src);
        ~PASS();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
        int     execute(Client &clicli, std::vector<std::string> args);
        void    descr(Client& clicli);
};
