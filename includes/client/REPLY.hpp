/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLY.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:39:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/26 15:44:42 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RPL_WELCOME(nick) " 001 " + nick + " Hi ! Welcome to this awesome IRC server !, " + nick
#define RPL_YOURHOST(serv, version) " 002 Your host is " + serv + " running version " + version
#define RPL_CREATED(created) " 003 This server was created " + created
#define RPL_MYINFO(nick, serv, version) " 004 " + nick + " " + serv + " " + version + " none " + "none."

// #define RPL_JOIN(nick, serv, channel) ":0 " + nick + "!" + nick + "@" + serv + " JOIN #" + channel
#define RPL_JOIN(nick, chan) ":" + nick + " JOIN :" + chan

// Pour répondre à une requête au sujet du mode du client, RPL_UMODEIS est renvoyé.
#define RPL_UMODEIS(mode) " 221 " + mode

// Pour répondre à une requête au sujet du mode du client, RPL_UMODEIS est renvoyé.
// 251 RPL_LUSERCLIENT
// ":There are <entier> users and <entier> invisible on <entier> servers"
// 252 RPL_LUSEROP
// "<entier> :operator(s) online"
// 253 RPL_LUSERUNKNOWN
// "<entier> :unknown connection(s)"
// 254 RPL_LUSERCHANNELS
// "<entier> :channels formed"
// 255 RPL_LUSERME
// ":I have <entier> clients and <integer> servers"

#define RPL_AWAY(target) " 301 " + target + " :<message d'absence>"

// Les réponses RPL_LISTSTART, RPL_LIST, RPL_LISTEND marquent le début, les réponses
// proprement dites, et la fin du traitement d'une commande LIST.
// S'il n'y a aucun canal disponible, seules les réponses de début et de fin sont envoyées.
#define RPL_LISTSTART() " 321 Channel :Users Name"
#define RPL_LIST(canal, visible, sujet) " 322 " + canal + " " + visible > " :" + sujet
#define RPL_LISTEND() " 323 :End of /LIST"

// "<canal> <mode> <paramètres de mode>"
#define RPL_CHANNELMODEIS(canal, mode, param) " 324 " + canal + " " + mode + " " + param

// Lors de l'envoi d'un message TOPIC pour déterminer le sujet d'un canal, une de ces deux
// réponses est envoyée. Si le sujet est défini, RPL_TOPIC est renvoyée, sinon c'est RPL_NOTOPIC.
#define RPL_NOTOPIC(chan) " 331 " + chan + " :No topic is set"
#define RPL_TOPIC(chan, sujet, nick) " 332 " + nick + " " + chan + " :" + sujet

// Réponse du serveur indiquant les détails de sa version. <version> est la version actuelle
// du programme utilisé (comprenant le numéro de mise à jour) et <debuglevel> est utilisé
// pour indiquer si le serveur fonctionne en mode débugage.
// Le champ <commentaire> peut contenir n'importe quel commentaire au sujet de la version,
// ou des détails supplémentaires sur la version.
#define RPL_VERSION(version, debug, serv, commit) " 351 " + version + "." + debug + " " + serv + " :" + commit

// En réponse à un message NAMES, une paire consistant de RPL_NAMREPLY et RPL_ENDOFNAMES est
// renvoyée par le serveur au client.
// S'il n'y a pas de canal résultant de la requête, seul RPL_ENDOFNAMES est retourné.
// L'exception à cela est lorsqu'un message NAMES est env

// Reponse du server indiquant les utilisateurs connectes a un channel lors d'un JOIN
#define RPL_NAMREPLY(chan, nick, list) " 353 " + nick + " = " + chan + " :" + list 

// Reponse du server indiquant la fin de liste des utilisateurs lors d'un JOIN
#define RPL_ENDOFNAMES(chan, nick) " 366 " + nick + " " + chan + " :End of NAMES list"

// "<canal> <identification de bannissement>"
#define RPL_BANLIST(canal, id) " 367 " + canal + " " + id

// Quand il liste les bannissements actifs pour un canal donné, un serveur doit renvoyer
// la liste en utilisant les messages RPL_BANLIST et RPL_ENDOFBANLIST.
// Un RPL_BANLIST différent doit être utilisé pour chaque identification de bannissement.
// Après avoir listé les identifications de bannissement (s'il y en a),
// un RPL_ENDOFBANLIST doit être renvoyé.

#define RPL_ENDOFBANLIST(canal) " 368 " + canal + " :End of channel ban list"
// RPL_YOUREOPER est renvoyé à un client qui vient d'émettre un message OPER
// et a obtenu le statut d'opérateur.

#define RPL_YOUREOPER() " 381 :You are now an IRC operator"

// Utilisé pour indiquer que le pseudonyme passé en paramètre à la commande
// n'est pas actuellement utilisé.
#define ERR_NOSUCHNICK(target) " 401 " + target + " :No such nick/channel"

// Utilisé pour indiquer que le nom du serveur donné n'existe pas actuellement.
#define ERR_NOSUCHSERVER(serv) " 402 " + serv + ":No such server"

// Utilisé pour indiquer que le nom de canal donné est invalide.
#define ERR_NOSUCHCHANNEL(canal) " 403 " + canal + " :No such channel:"

// Envoyé à un utilisateur qui (a) soit n'est pas dans un canal
// en mode +n ou (b) n'est pas opérateur (ou mode +v) sur un canal
// en mode +m ; et essaie d'envoyer un PRIVMSG à ce canal.
#define ERR_CANNOTSENDTOCHAN(canal) " 404 " + canal + " :Cannot send to channel"

// Envoyé à un utilisateur quand il a atteint le nombre maximal de canaux
// qu'il est autorisé à accéder simultanément, s'il essaie d'en rejoindre un autre.
#define ERR_TOOMANYCHANNELS(canal) " 405 " + canal + " :You have joined too many channels"

// Renvoyé à un client qui essaie d'envoyer un PRIVMSG/NOTICE utilisant le format de
// destination utilisateur@hôte pour lequel utilisateur@hôte a plusieurs occurrences.
#define ERR_TOOMANYTARGETS(dest) " 407 " + dest + " :Duplicate recipients. No message delivered"

// Pas de destinataire.
#define ERR_NORECIPIENT(cmd) " 411 :No recipient given (" + cmd + ")"

// Pas de texte à envoyer.
#define ERR_NOTEXTTOSEND() " 412 :No text to send"

// Domaine principal non spécifié.
#define ERR_NOTOPLEVEL(masque) " 413 " + masque + " :No toplevel domain specified"

// Joker dans le domaine principal
#define ERR_WILDTOPLEVEL(masque) " 414 " + masque + " :Wildcard in toplevel domain"

// Renvoyé à un client enregistré pour indiquer que la commande envoyée est inconnue du serveur.
#define ERR_UNKNOWNCOMMAND(command) " 421 " + command + " :Unknown command"

// Renvoyé quand un paramètre pseudonyme attendu pour une commande n'est pas fourni.
#define ERR_NONICKNAMEGIVEN() " 431 :No nickname given"

// Renvoyé après la réception d'un message NICK qui contient des caractères qui ne font pas
// partie du jeu autorisé. Voir les sections 1 et 2.2 pour les détails des pseudonymes valides.
#define ERR_ERRONEUSNICKNAME(pseudo) " 432 " + pseudo + " :Erroneus nickname"

// Renvoyé quand le traitement d'un message NICK résulte en une tentative de changer de
// pseudonyme en un déjà existant.
#define ERR_NICKNAMEINUSE(nick) " 433 " + nick + " :Nickname is already in use"

// Renvoyé par un serveur à un client lorsqu'il détecte une collision de pseudonymes
// (enregistrement d'un pseudonyme qui existe déjà sur un autre serveur).
#define ERR_NICKCOLLISION(nick) " 436 " + nick + " :Nickname collision KILL"

// Renvoyé par le serveur quand un client essaie une commande affectant un canal dont il ne fait pas partie.
#define  ERR_NOTONCHANNEL(canal) " 442 " + canal + " :You're not on that channel"

// Retourné en réponse à une commande USERS si la commande est désactivée.
// Tout serveur qui ne gère pas les USERS doit retourner cette valeur.
#define  ERR_USERSDISABLED() " 446 :USERS has been disabled"

// Retourné par le serveur pour indiquer à un client qu'il doit être enregistré
// avant que ses commandes soient traitées.
#define  ERR_NOTREGISTERED() " 451 :You have not registered"

// Renvoyé par un serveur par de nombreuses commandes, afin d'indiquer que le client
// n'a pas fourni assez de paramètres.
#define  ERR_NEEDMOREPARAMS(cmd) " 461 " + cmd + " :Not enough parameters"

// Retourné par le serveur à tout lien qui tente de changer les détails enregistrés
// (tels que mot de passe et détails utilisateur du second message USER)
#define ERR_ALREADYREGISTRED() " 462 :You may not reregister"

// Retourné pour indiquer l'échec d'une tentative d'enregistrement d'une connexion dû
// à un mot de passe incorrect ou manquant.
#define ERR_PASSWDMISMATCH() " 464 :Password incorrect"

// Clé de canal déjà définie.
#define ERR_KEYSET(canal) " 467 " + canal + " :Channel key already set"

// Impossible de joindre le canal (+l)
#define ERR_CHANNELISFULL(canal) "  471 " + canal + " :Cannot join channel (+l)"

// Mode Inconnu.
#define ERR_UNKNOWNMODE(char) " 472 " + char + " :is unknown mode char to me"

// Impossible de joindre le canal (+i).
#define ERR_INVITEONLYCHAN(canal) "  474 " + canal + " :Cannot join channel (+i)"

// Impossible de joindre le canal (+b).
#define ERR_BANNEDFROMCHAN(canal) "  474 " + canal + " :Cannot join channel (+b)"

// Impossible de joindre le canal (+k).
#define ERR_BADCHANNELKEY(canal) " 475 " + canal + " :Cannot join channel (+k)"

// introuvable
#define ERR_BADCHANMASK(canal) " 476 " + canal + " :Cannot use this mask"

// Toute commande qui requiert le privilège d'opérateur pour opérer doit retourner
// cette erreur pour indiquer son échec.
#define ERR_NOPRIVILEGES() " 481 :Permission Denied- You're not an IRC operator"

// Toute commande qui requiert les privilèges 'chanop' (tels les messages MODE) doit
// retourner ce message à un client qui l'utilise sans être chanop sur le canal spécifié.
#define ERR_CHANOPRIVSNEEDED(canal) " 482 " + canal + " :You're not channel operator"

// Toute tentative d'utiliser la commande KILL sur un serveur doit être refusée et
// cette erreur renvoyée directement au client.
#define ERR_CANTKILLSERVER()" 483 :You cant kill a server!"


// Si un client envoie un message OPER et que le serveur n'a pas été configuré pour autoriser
// les connexions d'opérateurs de cet hôte, cette erreur doit être retournée.
#define ERR_NOOPERHOST() " 491 :No O-lines for your host"

// Renvoyé par un serveur pour indiquer que le message MODE a été envoyé avec un pseudonyme et que le mode spécifié n'a pas été identifié.
#define ERR_UMODEUNKNOWNFLAG() " 501 :Unknown MODE flag"

// Erreur envoyée à tout utilisateur qui essaie de voir ou de modifier le mode utilisateur
// d'un autre client.
#define ERR_USERSDONTMATCH()" 502 :Cant change mode for other users"


    // ERR_NOSUCHSERVER
    // RPL_LISTSTART
    // RPL_LIST
    // RPL_LISTEND
	// ERR_ERRONEUSNICKNAME
	// ERR_NICKNAMEINUSE
	// ERR_NICKCOLLISION
	// ERR_NOSUCHSERVER
	// RPL_VERSION
	// ERR_NONICKNAMEGIVEN
	// ERR_ERRONEUSNICKNAME
	// ERR_NICKNAMEINUSE
	// ERR_NICKCOLLISION
    // ERR_NOSUCHSERVER
    // RPL_LISTSTART
    // RPL_LIST
    // RPL_LISTEND
	// RPL_CHANNELMODEIS
	// ERR_CHANOPRIVSNEEDED
	// ERR_NOTONCHANNEL
	// ERR_KEYSET
	// RPL_BANLIST
	// RPL_ENDOFBANLIST
	// ERR_UNKNOWNMODE
	// ERR_USERSDONTMATCH
	// RPL_UMODEIS
	// ERR_UMODEUNKNOWNFLAG
	// ERR_NEEDMOREPARAMS
    // ERR_BANNEDFROMCHAN
    // ERR_INVITEONLYCHAN
    // ERR_BADCHANNELKEY
    // ERR_CHANNELISFULL
    // ERR_BADCHANMASK
    // ERR_NOSUCHCHANNEL
    // ERR_TOOMANYCHANNELS
    // RPL_TOPIC
	// ERR_NORECIPIENT
	// ERR_NOTEXTTOSEND
	// ERR_CANNOTSENDTOCHAN
	// ERR_NOTOPLEVEL
	// ERR_WILDTOPLEVEL
	// ERR_TOOMANYTARGETS
	// ERR_NOSUCHNICK
	// RPL_AWAY
	
