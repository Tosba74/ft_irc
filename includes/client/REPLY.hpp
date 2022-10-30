/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLY.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:39:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/30 19:48:18 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once


// #define ERR_NEEDMOREPARAMS(command) "461 " + command " :Not enough parameters"

// #define RPL_WELCOME(nick, user, host) " 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host
# define RPL_WELCOME(nick) " 001 " + nick + " Hi ! Welcome to this awesome IRC server !"
#define RPL_YOURHOST(serv, version) " 002 Your host is " + serv + " running version " + version
#define RPL_CREATED(created) " 003 This server was created " + created
#define RPL_MYINFO(nick, serv, version) " 004 " + nick + " " + serv + " " + version + " none " + "none."