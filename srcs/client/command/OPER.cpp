/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:50:05 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 10:50:49by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/OPER.hpp"
// #include "client/command/Server.hpp"

OPER::OPER(Server *serv) : ACommand(serv) {}

OPER::OPER(OPER const& src) : ACommand(src) {
	if (this != &src)
		this->_serv = src._serv; 
}

OPER::~OPER() {}

// Le message OPER est utilisé par un utilisateur normal pour obtenir le privilège d'opérateur.
// La combinaison de <utilisateur> et <mdp> est nécessaire pour obtenir le privilège Opérateur.
// Si le client envoyant la commande OPER fournit un mot de passe correct pour l'utilisateur donné,
// le serveur informe le reste du réseau du nouvel opérateur en envoyant un "MODE +o"
// pour le pseudonyme.
// Le message OPER n'a lieu qu'entre un client et un serveur.
// 
// Réponses numériques : ERR_NEEDMOREPARAMS              RPL_YOUREOPER
        			//   ERR_NOOPERHOST                  ERR_PASSWDMISMATCH
// Exemple:
// OPER foo bar;
// Tentative d'enregistrement en tant qu'opérateur, de l'utilisateur "foo" utilisant "bar" comme mot de passe.

int		OPER::execute(Client &clicli, std::vector<std::string> args) {
	if (args.size() != 3) {
		clicli << ERR_NEEDMOREPARAMS(args[0]); 
		return 1;
	} else {
		;
	}
	clicli << RPL_YOUREOPER();
	return 0;
}

void	OPER::descr(Client& clicli) {
	clicli << "Usage: OPER <utilisateur> <mot de passe>\n";
}
