/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:46:34 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 12:30:54y bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

// Rappel:

	// Pour permettre de maintenir un niveau d'ordre raisonnable dans un réseau IRC, une catégorie de clients
	// spéciale (les opérateurs) est autorisée à exécuter des fonctions de maintenance générale sur le réseau.
	// Bien que les pouvoirs donnés aux opérateurs puissent être considérés comme 'dangereux', ils sont
	// néanmoins indispensables. Les opérateurs doivent être capables de faire certaines tâches de base,
	// telles que la déconnexion et la reconnexion de serveurs, ce qui est nécessaire pour prévenir les problèmes
	// à long terme de mauvais routage réseau. Étant donnée cette nécessité, le protocole décrit ici n'autorise
	// que les opérateurs à effectuer ces fonctions. Voir cmd SQUIT / CONNECT.
	
	// Un pouvoir plus controversé des opérateurs est la possibilité de retirer par la force un utilisateur connecté
	// au réseau, c'est à dire que les opérateurs peuvent clore une connexion entre un client et un serveur.
	// La justification à cela est délicate puisque son abus est à la fois destructif et agaçant. Voir cmd KILL.
	
// Commande: OPER <utilisateur> <mot de passe>	

// Le message OPER est utilisé par un utilisateur normal pour obtenir le privilège d'opérateur*.
// La combinaison de <utilisateur> et <mot de passe> est nécessaire pour obtenir le privilège Opérateur.

// Si le client envoyant la commande OPER fournit un mot de passe correct pour l'utilisateur donné,
// le serveur informe le reste du réseau du nouvel opérateur en envoyant un "MODE +o"
// pour le pseudonyme.

// Le message OPER n'a lieu qu'entre un client et un serveur.

// REPLY :
	// ERR_NEEDMOREPARAMS
	// ERR_NOOPERHOST
	// ERR_PASSWDMISMATCH
	// RPL_YOUREOPER

// Exemple:
	// OPER foo bar; Tentative d'enregistrement en tant qu'opérateur, de l'utilisateur "foo" utilisant "bar" comme mot de passe

class Server;

class OPER : public ACommand {
	public:
		OPER(Server *serv);
		OPER(OPER const& src);
		~OPER();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};