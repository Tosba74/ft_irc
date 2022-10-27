/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLY.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:39:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/26 15:38:11 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# define RPL_WELCOME(nick, user, host) (host + " 001 " + nick + " Hi ! Welcome to this awesome IRC server !")
# define RPL_YOURHOST(nick) (SERVERNAMEHEAD + " 002 " + "Your host is " + SERVERNAME + " running version " + VERSION + "\r\n")
# define RPL_CREATED(nick) (SERVERNAMEHEAD + " 003 " + "This server was created " + CREATED + "\r\n")
# define RPL_MYINFO(nick) (SERVERNAMEHEAD + " 004 " + nick + " " + SERVERNAME + " " + VERSION + " none " + "none." + "\r\n")

// #define RPL_WELCOME(nick, user, host) "001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host

// #define ERR_NEEDMOREPARAMS(command) "461 " + command " :Not enough parameters"

