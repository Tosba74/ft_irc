/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:33:29 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 15:38:50 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

// Commande: USER <nom d'utilisateur> <hôte> <nom de serveur> <nom réel>

// Le message USER est utilisé au début d'une connexion pour spécifier le nom d'utilisateur,
// le nom d'hôte, le nom de serveur, et le véritable nom d'un nouvel utilisateur.
// Il est aussi utilisé lors de la communication entre les serveurs pour indiquer
// l'arrivée d'un nouvel utilisateur sur IRC, puisque c'est seulement après avoir envoyé
// et le USER et le NICK qu'un utilisateur devient enregistré.

// Entre serveurs, USER doit être préfixé du pseudonyme du client. Notez que le nom d'hôte
// et le nom de serveur sont généralement ignorés par le serveur IRC quand la commande USER
// vient directement d'un client (pour des raisons de sécurité), mais sont utilisés dans
// la communication de serveur à serveur.
// Cela signifie que NICK doit toujours être envoyé à un serveur distant quand un
// nouvel utilisateur est ajouté au reste du réseau, avant que le USER correspondant soit envoyé.

// Notez aussi que le paramètre 'vrai nom' doit être le dernier paramètre, car il peut
// contenir des espaces, et il doit être préfixé par deux points (':') de façon à être
// reconnu comme tel.

// Puisqu'il est facile pour un client de mentir sur son nom si on se base uniquement sur
// le message USER, il est recommandé d'utiliser un "serveur d'identité".
// Si l'hôte dont l'utilisateur se connecte a un serveur de ce type activé, le nom
// d'utilisateur est défini par la réponse de ce "serveur d'identité".

// REPLY :
	// ERR_NEEDMOREPARAMS
	// ERR_ALREADYREGISTRED

// Exemples:
// USER guest tolmoon tolsun :Ronnie Reagan ; Utilisateur s'enregistrant avec un nom d'utilisateur de "guest" et un vrai nom de "Ronnie Reagan". :testnick USER guest tolmoon tolsun :Ronnie Reagan ; message entre les serveurs contenant le pseudonyme à qui appartient la commande USER.


class USER : public ACommand
{
	public:
		USER(Server *serv);
		USER(USER const& src);
		~USER();
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};

