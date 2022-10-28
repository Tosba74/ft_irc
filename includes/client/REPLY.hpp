/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLY.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:39:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/28 12:24:42 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RPL_WELCOME(nick, user, host) "001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host

// #define ERR_NEEDMOREPARAMS(command) "461 " + command " :Not enough parameters"

// # define RPL_WELCOME(nick, host) (host + " 001 " + nick + " Hi ! Welcome to this awesome IRC server !" + "\r\n")
// # define RPL_YOURHOST(nickname) (host + " 002 " + "Your host is " + SERVERNAME + " running version " + VERSION + "\r\n")
// # define RPL_CREATED(nickname) (host + " 003 " + "This server was created " + CREATED + "\r\n")
// # define RPL_MYINFO(nickname) (host + " 004 " + nick + " " + SERVERNAME + " " + VERSION + " none " + "none." + "\r\n")