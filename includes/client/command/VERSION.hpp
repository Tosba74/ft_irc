/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VERSION.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:08:34 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/15 00:35:53 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/ACommand.hpp"

#pragma once

// Commande: VERSION [<serveur>]

// Le message VERSION est utilisé pour déterminer la version du programme serveur.
// Un paramètre optionnel <serveur> est utilisé pour obtenir la version d'un programme
// serveur sur lequel un client n'est pas connecté directement.

// REPLY :
	// ERR_NOSUCHSERVER
	// RPL_VERSION
	
// Exemples:
	// :Wiz VERSION *.se ; message de Wiz pour vérifier la version d'un serveur correspondant à "*.se"
	// VERSION tolsun.oulu.fi ; vérifie la version du serveur "tolsun.oulu.fi".
	
class VERSION : public ACommand
{
	public:
		VERSION(Server *serv);
		VERSION(VERSION const& src);
		~VERSION();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
