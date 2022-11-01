/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLY.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:39:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 11:15:32 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once


// #define ERR_NEEDMOREPARAMS(command) "461 " + command " :Not enough parameters"

// #define RPL_WELCOME(nick, user, host) " 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host
#define RPL_WELCOME(nick) " 001 " + nick + " Hi ! Welcome to this awesome IRC server !"
#define RPL_YOURHOST(serv, version) " 002 Your host is " + serv + " running version " + version
#define RPL_CREATED(created) " 003 This server was created " + created
#define RPL_MYINFO(nick, serv, version) " 004 " + nick + " " + serv + " " + version + " none " + "none."


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

// Réponse du serveur indiquant les détails de sa version. <version> est la version actuelle
// du programme utilisé (comprenant le numéro de mise à jour) et <debuglevel> est utilisé
// pour indiquer si le serveur fonctionne en mode débugage.
// Le champ <commentaire> peut contenir n'importe quel commentaire au sujet de la version,
// ou des détails supplémentaires sur la version.
#define RPL_VERSION(version, debug, serv, commit) " 351 " + version + "." + debug + " " + serv + " :" + commit

// Utilisé pour indiquer que le pseudonyme passé en paramètre à la commande
// n'est pas actuellement utilisé.
#define ERR_NOSUCHNICK(target) " 401 " + target + " :No such nick/channel"

// Utilisé pour indiquer que le nom de canal donné est invalide.
#define ERR_NOSUCHCHANNEL(canal) " 403 " + canal + " :No such channel:"

// Envoyé à un utilisateur qui (a) soit n'est pas dans un canal
// en mode +n ou (b) n'est pas opérateur (ou mode +v) sur un canal
// en mode +m ; et essaie d'envoyer un PRIVMSG à ce canal.
#define ERR_CANNOTSENDTOCHAN(canal) " 404 " + canal + " :Cannot send to channel"

// Envoyé à un utilisateur quand il a atteint le nombre maximal de canaux
// qu'il est autorisé à accéder simultanément, s'il essaie d'en rejoindre un autre.
#define ERR_TOOMANYCHANNELS(canal) " 405 " + canal + " :You have joined too many channels"

// Renvoyé à un client enregistré pour indiquer que la commande envoyée est inconnue du serveur.
#define ERR_UNKNOWNCOMMAND(command) " 421 " + command + " :Unknown command"

// Renvoyé quand un paramètre pseudonyme attendu pour une commande n'est pas fourni.
#define ERR_NONICKNAMEGIVEN() " 431 :No nickname given"

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

// RPL_YOUREOPER est renvoyé à un client qui vient d'émettre un message OPER
// et a obtenu le statut d'opérateur.
#define RPL_YOUREOPER() " 381 :You are now an IRC operator"

// Retourné pour indiquer l'échec d'une tentative d'enregistrement d'une connexion dû
// à un mot de passe incorrect ou manquant.
#define ERR_PASSWDMISMATCH() " 464 :Password incorrect"

