/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:51:52 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/26 18:14:14 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

// RAPPEL :
	// La commande MODE est une commande à utilisation duale sur IRC.
	// Elle permet aussi bien de changer les modes des utilisateurs que ceux des canaux.
	// La raison à ce choix est qu'un jour les pseudonymes deviendront obsolètes et
	// la propriété équivalente sera le canal.
	// Lors du traitement des messages MODE, il est recommandé de commencer par décomposer
	// le message en entier, puis de réaliser les modifications résultantes.
	
// Les modes des canaux
	// Commande: MODE <canal> {[+|-]|o|p|s|i|t|n|b|v} [<limite>] [<utilisateur>] [<masque de bannissement >]

	// La commande MODE permet aux opérateurs de canal de changer les caractéristiques de 'leur' canal.
	// Les serveurs doivent aussi pouvoir changer les modes du canal, de façon à pouvoir créer
	// des opérateurs.

	// Les modes disponibles pour les canaux sont les suivants :
		// o - donne/retire les privilèges d'opérateur de canal
		// p - drapeau de canal privé
		// s - drapeau de canal secret
		// i - drapeau de canal accessible uniquement sur invitation
		// t - drapeau de sujet de canal modifiable uniquement par les opérateurs
		// n - pas de messages dans un canal provenant de clients à l'extérieur du canal
		// m - canal modéré
		// l - définit le nombre maximal de personnes dans un canal
		// b - définit un masque de bannissement pour interdire l'accès à des utilisateurs
		// v - donne/retire la possibilité de parler dans un canal modéré
		// k - définit la clé du canal (mot de passe)

// Lors de l'utilisation des options 'o' et 'b', le nombre de paramètres est restreint à trois
// par commande, et ce pour n'importe quelle combinaison de 'o' et de 'b'.

// Modes des utilisateurs
	// Commande: MODE <pseudonyme> {[+|-]|i|w|s|o}

	// Les modes utilisateurs sont typiquement des modifications qui affectent la façon dont
	// le client est vu par les autres, ou quels types de messages sont reçus.
	// Une commande MODE n'est acceptée que si l'expéditeur du message et le pseudonyme donné
	// en paramètre sont les mêmes.

	// Les modes disponibles sont :
		// i - marque un utilisateur comme invisible ;
		// s - marque un utilisateur comme recevant les notifications du serveur ;
		// w - l'utilisateur reçoit les WALLOPs ;
		// o - drapeau d'opérateur.

	// D'autres modes seront disponibles plus tard.
	// Si un utilisateur tente de devenir opérateur en utilisant le drapeau "+o",
	// la tentative doit être ignorée. Par contre, il n'y a pas de restriction
	// à ce que quelqu'un se 'deoppe' (en utilisant "-o").

// REPLY :
	// ERR_NEEDMOREPARAMS
	// RPL_CHANNELMODEIS
	// ERR_CHANOPRIVSNEEDED
	// ERR_NOSUCHNICK
	// ERR_NOTONCHANNEL
	// ERR_KEYSET
	// RPL_BANLIST
	// RPL_ENDOFBANLIST
	// ERR_UNKNOWNMODE
	// ERR_NOSUCHCHANNEL
	// ERR_USERSDONTMATCH
	// RPL_UMODEIS
	// ERR_UMODEUNKNOWNFLAG

// Exemples:
	// Utilisation des modes de canal:
		// MODE #Finnish +im ; Rend le canal #Finnish modéré et 'uniquement sur invitation'.
		// MODE #Finnish +o Kilroy ; Donne le privilège de 'chanop' à Kilroy sur le canal #Finnish.
		// MODE #Finnish +v Wiz ; Autorise WiZ à parler sur #Finnish.
		// MODE #Fins -s ; Annule le drapeau 'secret' du canal #Fins.
		// MODE #42 +k oulu ; Définit la clé comme "oulu".
		// MODE #eu-opers +l 10 ; Définit le nombre maximal d'utilisateurs dans le canal à 10.
		// MODE &oulu +b ; Liste les masques de bannissement du canal.
		// MODE &oulu +b *!*@* ; Interdit à quiconque de venir sur le canal.
		// MODE &oulu +b *!*@*.edu ; Interdit à tout utilisateur dont le nom d'hôte correspond à *.edu d'accéder au canal.
	// Utilisation des modes d'utilisateur :
		// :MODE WiZ -w ; supprime la réception des messages WALLOPS pour WiZ.
		// :Angel MODE Angel +i ; Message d'Angel pour se rendre invisible.
		// MODE WiZ -o ; WiZ se 'deoppe' (retire son statut d'opérateur). Le contraire ("MODE WiZ +o") ne doit pas être autorisé car cela court-circuiterait la commande OPER.


class MODE : public ACommand {
	private:
		int		checkChannel(Client &clicli, std::string args);
		// int		checkMode(Client &clicli, std::string args);
		int		checkMode(Client &clicli, std::string args, const char *cmp);
		// int		verifArgs(Client &clicli, std::vector<std::string> args);
		int		checkClient(Client &clicli, std::string client);
		// int		checkClient(Client &clicli, std::vector<std::string> client);
		int		indexage(char c, const char *ismode);
		bool	passNoGood(std::string pass);
	public:
		MODE(Server *serv);
		MODE(MODE const& src);
		~MODE();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};

